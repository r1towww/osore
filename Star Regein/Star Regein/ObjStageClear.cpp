//使用するヘッダー
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\SceneManager.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "ObjStageClear.h"

//使用するネームスペース
using namespace GameL;


//イニシャライズ
void CObjStageClear::Init()
{
	m_time = 0;	//描画までのタイム感覚の初期化
	m_Tra = 0.0f;
	m_Eff_Tra = 1.0f;
	m_push_flag = false;
	m_end_start = false;
	m_end_f = false;
	m_end_s_f = false;
	m_ani = 0;			//チャージアニメーション用
	m_ani_time = 0;	//チャージアニメーション間隔タイム
	m_ani_flag = false;

	m_cnt_f = true;	//評価数をカウントするかどうかのフラグ
	//地球以外の場合
	if (g_stage != EarthStar)
	{
		//敵を倒した数の評価基準
		if (g_enemy_cnt == g_kill_cnt)
			m_kill_grade = 3;		//キル数の評価
		else if (g_kill_cnt == 0)
			m_kill_grade = 0;
		else if (g_kill_cnt / g_enemy_cnt >= 0.5)
			m_kill_grade = 2;
		else
			m_kill_grade = 1;
	}
	else if (g_stage == EarthStar)//地球
	{
		m_kill_grade = 3;
	}

	m_kill_star_cnt = 0;	//キル評価のカウント

	//メッセージの情報を持ってくる
	CObjMessage* objmes = (CObjMessage*)Objs::GetObj(OBJ_MESSAGE);

	//クリアタイムの評価基準
	if (g_minute < 1)		//1分以内にクリア
		m_time_grade = 3;
	else if(g_minute < 2)	//2分以内にクリア
		m_time_grade = 2;
	else if (g_minute < 3)	//3分以内にクリア
		m_time_grade = 1;
	else					//それ以外の場合
		m_time_grade = 0;

	m_time_star_cnt = 0;		//タイムグレード数用のカウント

	////チュートリアルステージはノーダメージクリアをオフにする
	//if (g_stage == EarthStar && g_Boss_Spawn == false)
	//	g_no_damage = true;


	//ダメージの評価基準	
	if (g_stage == EarthStar)	//地球の場合
		m_damage_grade = 3;
	else if (g_no_damage == false)	//ダメージを受けていない場合
		m_damage_grade = 3;
	else
		m_damage_grade = 0;

	m_damage_star_cnt = 0;		//被ダメージの評価

	

	m_next_cnt = 0;		//次へ進む用のカウント
	m_key_f = true;	//キー入力制御用フラグ
	m_grade_cnt_f = false;
	m_grade_draw_f = false;
	m_grade_cnt = 0;
	m_cnt = 0;		//評価星カウントの初期化
	m_eff.m_top = 0;
	m_eff.m_left = 0;
	m_eff.m_right = 192;
	m_eff.m_bottom = 192;

	//ボス戦以外の場合
	if (g_Boss_Spawn == false)
	{
		Audio::Stop(8);		//戦闘BGMを止める
		Audio::Start(23);	//クリアBGMを鳴らす
	}
}

//アクション
void CObjStageClear::Action()
{


	//キー入力タイムが一定に達した場合、キー入力を許可する
	if ((Input::GetVKey('Z') == true  || Input::GetVKey(VK_RETURN) == true))
	{
		if (m_key_f == true)
		{
			Audio::Start(1);	//エフェクト音を鳴らす

			//1度目のZキーを入力した際
			if (m_next_cnt == 0)
			{
				m_ani_flag = false;	//アニメーションフラグをオフにする

				//すべての評価の取得
				for (int i = 0; i < 4; i++)
				{
					m_grade_f[i] = true;	//各評価を表示し終えたかどうかのフラグをオン
				}
				for (int i = 0; i < m_time_grade; i++)	//タイムグレード分回す
				{
					m_time_star_f[i] = true;	//クリアタイム評価のグレード分表示し終えたかどうかのフラグをオン
				}
				for (int i = 0; i < m_kill_grade; i++)	//キルグレード分回す
				{
					m_kill_star_f[i] = true;	//キル数評価のグレード分表示し終えたかどうかのフラグをオン
				}
				for (int i = 0; i < m_damage_grade; i++)//被ダメージグレード分回す
				{
					m_damage_star_f[i] = true;	//被ダメージ評価のグレード分表示し終えたかどうかのフラグをオン
				}

				//すべての評価メッセージを表示
				m_alpha[0] = 1.0f;	//透明度を戻す
				m_alpha[1] = 1.0f;
				m_alpha[2] = 1.0f;
				m_alpha[3] = 1.0f;
				m_alpha[4] = 1.0f;

				
				m_time_star_cnt = m_time_grade;	//タイムスターグレードの星の数を合わせる
				m_kill_star_cnt = m_kill_grade;
				m_damage_star_cnt = m_damage_grade;

				

				m_cnt_f = false;
				m_grade_cnt_f = false;
				m_cnt = CLEARGRADE + m_time_grade + m_kill_grade + m_damage_grade;		//アニメーションに入らないため、スコアを評価分代入
				//↑ CLEARGRADEはクリアした状態で評価されるので、必ず取得
				m_grade_cnt = m_cnt;	//最終評価用カウントにすべての評価を代入
			}
			//すべての評価が描画された場合
			else if (m_next_cnt == 1 && m_alpha[5] == 1.0f)
			{
				m_push_flag = true;	//ステージ選択へ戻るようにする
			}
			m_key_f = false;

			m_end_start = true;

			//カウントの値が同じ時
			if (m_cnt == m_grade_cnt) {
				//最終アニメーションフラグがオンの時
				if (m_end_f == true)
				{
					//最終アニメーションを止めて星を表示させるフラグ
					m_end_start = false;		//エフェクトを止める
					m_end_s_f = true;			//星を描画する
				}
				else
					m_grade_draw_f = true;		//最終評価の星の描画
			}
		}
	}
	else
	{
		m_key_f = true;
	}



	//Zキーを押すと徐々に暗転し、シーン移行
	if (m_push_flag == true)
	{
		m_Tra += 0.03f;		//暗転の透過度を戻す
		//各メッセージの透過度を減らす
		m_Eff_Tra -= 0.03f;
		m_alpha[0] -= 0.03f;
		m_alpha[1] -= 0.03f;
		m_alpha[2] -= 0.03f;
		m_alpha[3] -= 0.03f;
		m_alpha[4] -= 0.03f;
		m_alpha[5] -= 0.03f;
		m_alpha[6] -= 0.03f;

		//暗転の透過度が1.0fを超えた場合
		if (m_Tra >= 1.0f)
		{
			//ボス戦後の場合
			if(g_Boss_Spawn == true)
				Scene::SetScene(new CSceneTitle());	//タイトルに戻す
			else //それ以外の場合
				Scene::SetScene(new CSceneStageChoice());//ステージ選択画面に戻す
			g_stage = Space;		//ステージの値をSpace（ステージ選択）に変更
			g_stage_clear = false;		//星座取得フラグを戻す
			g_move_stop_flag = false;	//入力制御フラグを戻す
		}
	}

	//タイムを60になるまでプラス
	m_time++;
	if (m_time >= 60)
		m_time = 60;

	//前のメッセージが表示され、アニメーションフラグがオフになった際（エフェクト、評価が終わった際）、メッセージを表示する
	if (m_alpha[3] == 1.0f&& m_grade_f[2] == true) {		//被ダメージ評価用
		m_alpha[4] += 0.05f;
		if (m_alpha[4] >= 1.0f) {
			m_alpha[4] = 1.0f;
			if(m_damage_grade > 0)	//評価がある場合
				m_ani_flag = true;
		}
	}
	//前のメッセージが表示され、アニメーションフラグがオフになった際（エフェクト、評価が終わった際）、メッセージを表示する
	else if (m_alpha[2] == 1.0f && m_grade_f[1] == true) {	//キル数評価用
		m_alpha[3] += 0.05f;
		if (m_alpha[3] >= 1.0f) {
			m_alpha[3] = 1.0f;
			if(m_kill_grade > 0)	//評価がある場合
				m_ani_flag = true;
		}
	}
	//前のメッセージが表示された際
	else if (m_alpha[1] == 1.0f) {							//クリアタイム評価用
		m_alpha[2] += 0.05f;
		if (m_alpha[2] >= 1.0f) {
			m_alpha[2] = 1.0f;
			if (m_time_grade > 0)	//評価がある場合
				m_ani_flag = true;
		}
	}
	//前のメッセージが表示され、アニメーションフラグがオフになった際（エフェクト、評価が終わった際）、メッセージを表示する
	else if (m_alpha[0] == 1.0f && m_grade_f[0] == true) {	//取得星座用
		m_alpha[1] += 0.05f;
		if (m_alpha[1] >= 1.0f)
			m_alpha[1] = 1.0f;
	}
	else if (m_time == 60) {	//タイムが60になったらアルファ値を増やす	ステージクリア用
		m_alpha[0] += 0.05f;
		if (m_alpha[0] >= 1.0f) {
			m_alpha[0] = 1.0f;	//1.0fになったら次のメッセージの表示
			m_ani_flag = true;
		}
	}

	//エフェクト動作処理用
	Star_eff_ani();
}

//ドロー
void CObjStageClear::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,m_Tra };
	float Stage[4] = { 0.5f,0.5f,0.5f,1.0f };
	float effc[4] = { 1.0f,1.0f,1.0f,m_Eff_Tra };
	float c3[4] = { 1.0f,1.0f,1.0f,m_alpha[2] };	//クリアタイムメッセージカラー
	float c3y[4] = { 1.0f,1.0f,0.0f,m_alpha[2] };	//クリアタイムメッセージカラー（黄）
	float c3r[4] = { 1.0f,0.0f,0.0f,m_alpha[2] };	//クリアタイムメッセージカラー（赤）
	float c4[4] = { 1.0f,1.0f,1.0f,m_alpha[3] };	//敵殲滅数メッセージカラー
	float c4y[4] = { 1.0f,1.0f,0.0f,m_alpha[3] };	//敵殲滅数メッセージカラー（黄）
	float c4r[4] = { 1.0f,0.0f,0.0f,m_alpha[3] };	//敵殲滅数メッセージカラー（赤）
	float c5[4] = { 1.0f,1.0f,1.0f,m_alpha[4] };	//被ダメージメッセージカラー
	float c5y[4] = { 1.0f,1.0f,0.0f,m_alpha[4] };	//被ダメージメッセージカラー（黄）
	float c5r[4] = { 1.0f,0.0f,0.0f,m_alpha[4] };	//被ダメージメッセージカラー（赤）

	float c6s[4] = { 0.0f,0.5f,1.0f,m_alpha[5] };	//最終評価メッセージカラー（S）
	float c6a[4] = { 1.0f,0.0f,0.0f,m_alpha[5] };	//最終評価メッセージカラー（A）
	float c6b[4] = { 0.0f,1.0f,0.0f,m_alpha[5] };	//最終評価メッセージカラー（B）
	float c6c[4] = { 1.0f,1.0f,1.0f,m_alpha[5] };	//最終評価メッセージカラー（C）

	float y[4] = { 1.0f,1.0f,0.0f,1.0f };		//ステージクリア等のメッセージカラー

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	//クリア背景画像の切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 790.0f;
	src.m_bottom = 590.0f;

	//表示位置の設定
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;

	//表示
	Draw::Draw(60, &src, &dst, Stage, 0.0f);

	Font::StrDraw(L"STAGE CLEAR", CLEAR_X, CLEAR_Y, CLEAR_SIZE, y);

	if(g_End_flag==true)
		Font::StrDraw(L"Zキーでタイトルへ戻る", BACK_X, BACK_Y, BACK_SIZE, y);
	else
		Font::StrDraw(L"Zキーでステージ選択へ戻る", BACK_X, BACK_Y, BACK_SIZE, y);

	//クリア情報
	wchar_t KILLCNT[128];	//キルカウント表示用
	wchar_t TIME[128];	//タイムの描画


	//m_time_mesから秒分を求める
	//分：秒の値を文字列化
	if (g_second < 10)
		swprintf_s(TIME, L"クリアタイム：%d分0%d秒", g_minute, g_second);//秒の1桁目に0を用意
	else
		swprintf_s(TIME, L"クリアタイム：%d分%d秒", g_minute, g_second);

	swprintf_s(KILLCNT, L"敵を%.0f体倒した！", g_kill_cnt);

	Star_clear();//リザルトスターエフェクトの表示

	if(m_time_grade == 3)
		Font::StrDraw(TIME, PER_ALL_X, FIRST_Y, PER_ALL_SIZE, c3y);
	else if(m_time_grade == 2)
		Font::StrDraw(TIME, PER_ALL_X, FIRST_Y, PER_ALL_SIZE, c3);
	else 
		Font::StrDraw(TIME, PER_ALL_X, FIRST_Y, PER_ALL_SIZE, c3r);



	//星切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 184.0f;
	src.m_bottom = 175.0f;

	//クリアタイム評価の描画用----------------------------------------
	ani_flag();		//アニメーションのオンオフ切り替え用
	//各評価のエフェクトの描画
	Star_grade_eff(m_ani_flag, m_time_star_cnt, m_grade_f[0], m_grade_f[1], 220.0f, 280.0f);
	//各評価の数分スターを描画
	Star_grade_draw(m_time_star_f, m_time_star_cnt, 245.0f, 305.0f);

	//-----------------------------------------------------------------

	//ボス戦後の場合
	if (g_stage == EarthStar && g_Boss_Spawn == true)
	{
		//１番目のメッセージ
		Font::StrDraw(L"地球を危機から救った！", PER_ALL_X, SECOND_Y, PER_ALL_SIZE, c4y);
		ani_flag();		//アニメーションのオンオフ切り替え用
		//各評価のエフェクトの描画
		Star_grade_eff(m_ani_flag, m_kill_star_cnt, m_grade_f[1], m_grade_f[2], 220.0f, 310.0f);
		//各評価の数分スターを描画
		Star_grade_draw(m_kill_star_f, m_kill_star_cnt, 245.0f, 335.0f);

		//２番目のメッセージ
		Font::StrDraw(L"君は英雄だ！", PER_ALL_X, THIRD_Y, PER_ALL_SIZE, c5y);

		ani_flag();		//アニメーションのオンオフ切り替え用
		//各評価のエフェクトの描画
		Star_grade_eff(m_ani_flag, m_damage_star_cnt, m_grade_f[2], m_grade_f[3], 220.0f, 340.0f);
		//各評価の数分スターを描画
		Star_grade_draw(m_damage_star_f, m_damage_star_cnt, 245.0f, 365.0f);
	}
	else if (g_stage == EarthStar)
	{
		Font::StrDraw(L"移動方法を覚えた！", PER_ALL_X, SECOND_Y, PER_ALL_SIZE, c4y);
		ani_flag();		//アニメーションのオンオフ切り替え用
		//各評価のエフェクトの描画
		Star_grade_eff(m_ani_flag, m_kill_star_cnt, m_grade_f[1], m_grade_f[2], 220.0f, 310.0f);
		//各評価の数分スターを描画
		Star_grade_draw(m_kill_star_f, m_kill_star_cnt, 245.0f, 335.0f);

		//チュートリアル中の場合
		Font::StrDraw(L"チュートリアルクリア！", PER_ALL_X, THIRD_Y, PER_ALL_SIZE, c5y);

		ani_flag();		//アニメーションのオンオフ切り替え用
		//各評価のエフェクトの描画
		Star_grade_eff(m_ani_flag, m_damage_star_cnt, m_grade_f[2], m_grade_f[3], 220.0f, 340.0f);
		//各評価の数分スターを描画
		Star_grade_draw(m_damage_star_f, m_damage_star_cnt, 245.0f, 365.0f);
	}
	//地球以外の星の場合
	else if (g_stage != EarthStar)
	{
		//1体以上敵を倒している場合
		if (g_kill_cnt > 0)
		{
			//敵殲滅用メッセージの表示
			if (g_kill_cnt == g_enemy_cnt)
			{
				Font::StrDraw(L"敵を全滅させた！", PER_ALL_X, SECOND_Y, PER_ALL_SIZE, c4y);
				//実績達成画面で表示させるためのフラグ処理
				if (g_stage == VenusTaurus)
				{
					g_Taurus_Enemy_AllKill = true;
					g_new_Performance = true;
				}
				else if (g_stage == VenusLibra)
				{
					g_Libra_Enemy_AllKill = true;
					g_new_Performance = true;

				}
				else if (g_stage == MercuryGemini)
				{
					g_Gemini_Enemy_AllKill = true;
					g_new_Performance = true;

				}
				else if (g_stage == MercuryVirgo)
				{
					g_Viego_Enemy_AllKill = true;
					g_new_Performance = true;

				}
				else if (g_stage == SunLeo)
				{
					g_Leo_Enemy_AllKill = true;
					g_new_Performance = true;

				}

			}
			else if (g_kill_cnt > 0)
				Font::StrDraw(KILLCNT, PER_ALL_X, SECOND_Y, PER_ALL_SIZE, c4);


			//キル数評価の描画用----------------------------------------
			if (g_Boss_Spawn == true || g_stage != EarthStar)	//チュートリアル中じゃない場合
			{
				ani_flag();		//アニメーションのオンオフ切り替え用
				//各評価のエフェクトの描画
				Star_grade_eff(m_ani_flag, m_kill_star_cnt, m_grade_f[1], m_grade_f[2], 220.0f, 310.0f);
				//各評価の数分スターを描画
				Star_grade_draw(m_kill_star_f, m_kill_star_cnt, 245.0f, 335.0f);

			}
		}
		else if (g_kill_cnt == 0)	//キルしなかった場合
		{
			Font::StrDraw(L"誰も倒さなかった！", PER_ALL_X, SECOND_Y, PER_ALL_SIZE, c4r);
		}

		//-----------------------------------------------------------------


		//ノーダメージクリアメッセージの表示
		if (g_no_damage == false)	//ダメージを受けなかった場合
		{
			Font::StrDraw(L"ノーダメージクリア！", PER_ALL_X, THIRD_Y, PER_ALL_SIZE, c5y);

			ani_flag();		//アニメーションのオンオフ切り替え用
			//各評価のエフェクトの描画
			Star_grade_eff(m_ani_flag, m_damage_star_cnt, m_grade_f[2], m_grade_f[3], 220.0f, 340.0f);
			//各評価の数分スターを描画
			Star_grade_draw(m_damage_star_f, m_damage_star_cnt, 245.0f ,365.0f);

			//実績達成画面で表示させるためのフラグ処理
			if (g_stage == VenusTaurus)
			{
				g_Taurus_NoDamage_Clear = true;
				g_new_Performance = true;

			}
			else if (g_stage == VenusLibra)
			{
				g_Libra_NoDamage_Clear = true;
				g_new_Performance = true;

			}
			else if (g_stage == MercuryGemini)
			{
				g_Gemini_NoDamage_Clear = true;
				g_new_Performance = true;

			}
			else if (g_stage == MercuryVirgo)
			{
				g_Viego_NoDamage_Clear = true;
				g_new_Performance = true;

			}
			else if (g_stage == SunLeo)
			{
				g_Leo_NoDamage_Clear = true;
				g_new_Performance = true;

			}
		}
	}
	
	//ダメージまでの評価を表示し終えた際
	if (m_grade_f[3] == true && m_end_start == true)
	{
		m_cnt_f = false;		//エフェクトを描画した数のカウントをオフにする
		m_ani_flag = true;		//アニメーションフラグをオンにして、エフェクトを始める

		//全評価分のエフェクトの描画
		for (int i = 0; i < m_cnt; i++)	//カウント分回す
		{
			//表示位置の設定
			dst.m_top    = 400.0f;
			dst.m_left   =  20.0f + (50.0f * i);
			dst.m_right  = 100.0f + (50.0f * i);
			dst.m_bottom = dst.m_top + 80.0f;
			Draw::Draw(71, &m_eff, &dst, effc, 0.0f);
		}
		//最終アニメーションフラグをオンにする
		m_end_f = true;
		//今まで数えた星の数を一番下に出す星のカウントと同じにする
		m_grade_cnt = m_cnt;

		m_grade_cnt_f = false;
		
	}
	//最終評価のエフェクト描画が終わった際
	if (m_end_s_f == true)
	{
		//最終評価分回す
		for (int i = 0; i < m_grade_cnt; i++)
		{
			//表示位置の設定
			dst.m_top    = 425.0f;
			dst.m_left   = 45.0f + (50.0f * i);
			dst.m_right  = 80.0f + (50.0f * i);
			dst.m_bottom = 460.0f;
			if (m_grade_draw_f == true) {
				Draw::Draw(70, &src, &dst, effc, 0.0f);
			}
		}
		//ランクの透過度を戻す
		m_alpha[5] += 0.05f;
		if (m_alpha[5] >= 1.0f) {
			m_alpha[5] = 1.0f;
		}
		//星の数に応じてランクづけ
		if (m_grade_cnt == 10)
		{
			if (m_next_cnt == 0)
				Audio::Start(20);	//エフェクト音を鳴らす

			Font::StrDraw(L"S", 550, 390, 120, c6s);
			//ランクデータ保存
			if (g_stage == VenusTaurus)
			{
				g_Taurus_Grade = S;
			}
			else if (g_stage == VenusLibra)
			{
				g_Libra_Grade = S;
			}
			else if (g_stage == MercuryGemini)
			{
				g_Gemini_Grade = S;
			}
			else if (g_stage == MercuryVirgo)
			{
				g_Viego_Grade = S;
			}
			else if (g_stage == SunLeo)
			{
				g_Leo_Grade = S;
			}
		}
		else if (m_grade_cnt >= 6)
		{
			if (m_next_cnt == 0)
				Audio::Start(21);	//エフェクト音を鳴らす

			Font::StrDraw(L"A", 550, 390, 120, c6a);
			//ランクデータ保存
			if (g_stage == VenusTaurus)
			{
				g_Taurus_Grade = A;
			}
			else if (g_stage == VenusLibra)
			{
				g_Libra_Grade = A;
			}
			else if (g_stage == MercuryGemini)
			{
				g_Gemini_Grade = A;
			}
			else if (g_stage == MercuryVirgo)
			{
				g_Viego_Grade = A;
			}
			else if (g_stage == SunLeo)
			{
				g_Leo_Grade = A;
			}
		}
		else if (m_grade_cnt >= 4)
		{
			if (m_next_cnt == 0)
				Audio::Start(22);	//エフェクト音を鳴らす

			Font::StrDraw(L"B", 550, 390, 120, c6b);
			//ランクデータ保存
			if (g_stage == VenusTaurus)
			{
				g_Taurus_Grade = B;
			}
			else if (g_stage == VenusLibra)
			{
				g_Libra_Grade = B;
			}
			else if (g_stage == MercuryGemini)
			{
				g_Gemini_Grade = B;
			}
			else if (g_stage == MercuryVirgo)
			{
				g_Viego_Grade = B;
			}
			else if (g_stage == SunLeo)
			{
				g_Leo_Grade = B;
			}
		}
		else
		{
			if(m_next_cnt == 0)
				Audio::Start(22);	//エフェクト音を鳴らす

			Font::StrDraw(L"C", 550, 390, 120, c6c);
			//ランクデータ保存
			if (g_stage == VenusTaurus)
			{
				g_Taurus_Grade = C;
			}
			else if (g_stage == VenusLibra)
			{
				g_Libra_Grade = C;
			}
			else if (g_stage == MercuryGemini)
			{
				g_Gemini_Grade = C;
			}
			else if (g_stage == MercuryVirgo)
			{
				g_Viego_Grade = C;
			}
			else if (g_stage == SunLeo)
			{
				g_Leo_Grade = C;
			}
		}

		m_next_cnt = 1;	//キー入力でステージへ戻るようにする
	}

	

	//シーン移行用
	if (m_push_flag == true)
	{
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 350.0f;
		src.m_right = 400.0f;
		src.m_bottom = 50.0f;

		//表示位置の設定
		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 600.0f;

		Draw::Draw(9, &src, &dst, c, 0.0f);
	}

}
//アニメーションフラグ
bool CObjStageClear::ani_flag()
{
	//キルグレード用
	if (m_kill_star_cnt == 1 && m_grade_f[2] != true || m_kill_star_cnt == 2 && m_grade_f[2] != true)
	{
		m_ani_flag = true;
		return m_ani_flag;
	}
	else if (m_time_star_cnt == 1 && m_grade_f[1] != true || m_time_star_cnt == 2 && m_grade_f[1] != true)
	{
		m_ani_flag = true;
		return m_ani_flag;

	}
	else if (m_damage_star_cnt == 1 && m_grade_f[3] != true || m_damage_star_cnt == 2 && m_grade_f[3] != true) 
	{
		m_ani_flag = true;
		return m_ani_flag;
	}

}

//スターアニメーション
void CObjStageClear::Star_eff_ani()
{
	if (m_ani_flag == true)
	{
		//最終リザルト以外
		if (m_end_s_f != true)
			Audio::Start(19);	//エフェクトを鳴らす

		//エフェクト用画像の切り取り
		RECT_F ani_src[15] =
		{
			{   0,   0, 192, 192 },
			{   0, 192, 384, 192 },
			{   0, 384, 576, 192 },
			{   0, 576, 768, 192 },
			{   0, 768, 960, 192 },
			{ 192,   0, 192, 384 },
			{ 192, 192, 384, 384 },
			{ 192, 384, 576, 384 },
			{ 192, 576, 768, 384 },
			{ 192, 768, 960, 384 },
			{ 384,   0, 192, 576 },
			{ 384, 192, 384, 576 },
			{ 384, 384, 576, 576 },
			{ 384, 576, 768, 576 },
			{ 384, 768, 960, 576 },
		};

		//アニメーションのコマ間隔制御
		if (m_ani_time > 1)	//タイムが１より大きい場合
		{
			m_ani++;		//アニメーションのコマを1つ進める
			m_ani_time = 0;	//タイムを0に戻す

			m_eff = ani_src[m_ani];//アニメーションのRECT配列からm_ani番目のRECT情報取得
		}
		else	//それ以外の場合
		{
			m_ani_time++;		//タイムをプラス
		}
		//画像最後まで進んだら、0番目に戻す
		if (m_ani == 14)
		{

			//クリアタイム用グレード
			if (m_grade_f[0] == true && m_grade_f[1] == false) {
				m_time_star_f[m_time_star_cnt] = true;
				m_time_star_cnt++;
			}
			//キル数用グレード
			if (m_grade_f[1] == true && m_grade_f[2] == false) {
				m_kill_star_f[m_kill_star_cnt] = true;
				m_kill_star_cnt++;
			}
			//ダメージ用グレード
			if (m_grade_f[2] == true && m_grade_f[3] == false) {
				m_damage_star_f[m_damage_star_cnt] = true;
				m_damage_star_cnt++;
			}
			//ステージクリア用グレードがオフの場合（エフェクトが１度目の場合）
			if (m_grade_f[0] == false)
				m_grade_f[0] = true;								//ステージクリア用グレードをオンにする（終わったかどうかの比較用）
			//タイムグレードとカウントが同じで、ステージクリア用グレードがオンの場合
			if (m_time_grade == m_time_star_cnt && m_grade_f[0] == true)
				m_grade_f[1] = true;									//タイムグレードをオンにする（終わったかどうかの比較用）
			//キルグレードとカウントが同じで、タイムグレードがオンの場合
			if (m_kill_grade == m_kill_star_cnt && m_grade_f[1] == true)
				m_grade_f[2] = true;									//キルグレードをオンにする（終わったかどうかの比較用）
			//ダメージグレードとカウントが同じで、キルグレードがオンの場合
			if (m_damage_grade == m_damage_star_cnt && m_grade_f[2] == true)
				m_grade_f[3] = true; m_end_start = true;				//ダメージグレードをオンにする（終わったかどうかの比較用）

			//カウントの値が同じ時
			if (m_cnt == m_grade_cnt) {
				//最終アニメーションフラグがオンの時
				if (m_end_f == true)
				{
					//最終アニメーションを止めて星を表示させるフラグ
					m_end_start = false;		//エフェクトを止める
					m_end_s_f = true;			//星を描画する
				}
				else
					m_grade_draw_f = true;		//最終評価の星の描画
			}
			//フラグがオンの際、星（評価）をいくつ取得できたか
			if (m_cnt_f == true)
				m_cnt++;
			else if (m_cnt_f == false && m_grade_cnt_f == true)
				m_grade_cnt++;			//最終評価のアニメーションの数をカウントする

			m_ani = 0;				//アニメーションを１枚目に戻す
			m_ani_flag = false;		//アニメーションフラグをオフにする
			Audio::Stop(19);		//エフェクト音を止める（多重に鳴らないよう）

		}
	}

}

//惑星クリアメッセージ、エフェクト、スターの描画
void CObjStageClear::Star_clear()
{
	//描画カラー情報
	float c1[4] = { 1.0f,1.0f,1.0f,m_alpha[0] };	//星座クリアメッセージカラー
	float c1y[4] = { 1.0f,1.0f,0.0f,m_alpha[0] };	//星座クリアメッセージカラー（黄）
	float c2[4] = { 1.0f,1.0f,1.0f,m_alpha[1] };	//取得スキルメッセージカラー												
	float effc[4] = { 1.0f,1.0f,1.0f,m_Eff_Tra };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	//星切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 184.0f;
	src.m_bottom = 175.0f;

	//各星座ごとのメッセージ 
	if (g_stage == EarthStar && g_Boss_Spawn)	//地球（ボス出現時）
	{
		Font::StrDraw(L"ボスを撃破！", PER_ALL_X, PER_CLEAR_1, PER_ALL_SIZE, c1y);
		//Font::StrDraw(L"", PER_ALL_X, PER_CLEAR_2, PER_ALL_SIZE, c2);
	}
	else if (g_stage == EarthStar)		//地球（チュートリアル時）
	{
		Font::StrDraw(L"地球をクリアした！", PER_ALL_X, PER_CLEAR_1, PER_ALL_SIZE, c1);
		Font::StrDraw(L"取得したスキル：無し", PER_ALL_X, PER_CLEAR_2, PER_ALL_SIZE, c2);
	}
	if (g_stage == VenusTaurus)
	{
		Font::StrDraw(L"牡牛座をクリアした！", PER_ALL_X, PER_CLEAR_1, PER_ALL_SIZE, c1);
		Font::StrDraw(L"取得したスキル：牡牛座", PER_ALL_X, PER_CLEAR_2, PER_ALL_SIZE, c2);
	}
	if (g_stage == VenusLibra)
	{
		Font::StrDraw(L"天秤座をクリアした！", PER_ALL_X, PER_CLEAR_1, PER_ALL_SIZE, c1);
		Font::StrDraw(L"取得したスキル：天秤座", PER_ALL_X, PER_CLEAR_2, PER_ALL_SIZE, c2);
	}
	if (g_stage == MercuryGemini)
	{
		Font::StrDraw(L"双子座をクリアした！", PER_ALL_X, PER_CLEAR_1, PER_ALL_SIZE, c1);
		Font::StrDraw(L"取得したスキル：双子座", PER_ALL_X, PER_CLEAR_2, PER_ALL_SIZE, c2);
	}
	if (g_stage == MercuryVirgo)
	{
		Font::StrDraw(L"乙女座をクリアした！", PER_ALL_X, PER_CLEAR_1, PER_ALL_SIZE, c1);
		Font::StrDraw(L"取得したスキル：乙女座", PER_ALL_X, PER_CLEAR_2, PER_ALL_SIZE, c2);
	}
	if (g_stage == SunLeo)
	{
		Font::StrDraw(L"獅子座をクリアした！", PER_ALL_X, PER_CLEAR_1, PER_ALL_SIZE, c1);
		Font::StrDraw(L"取得したスキル：獅子座", PER_ALL_X, PER_CLEAR_2, PER_ALL_SIZE, c2);
	}

	//リザルトスターエフェクトの表示
	//表示位置の設定
	dst.m_top = 220.0f;
	dst.m_left = 220.0f;
	dst.m_right = dst.m_left + 80.0f;
	dst.m_bottom = dst.m_top + 80.0f;
	if (m_ani_flag == true && m_grade_f[0] == false)
		Draw::Draw(71, &m_eff, &dst, effc, 0.0f);
	//取得した評価（星）の表示
	//表示位置の設定
	dst.m_top = 245.0f;
	dst.m_left = 245.0f;
	dst.m_right = 275.0f;
	dst.m_bottom = 275.0f;
	if (m_grade_f[0] == true)
		Draw::Draw(70, &src, &dst, effc, 0.0f);

}

//各評価のエフェクトの描画
void CObjStageClear::Star_grade_eff(bool ani,int starcnt, bool grade1, bool grade2, float x, float y )
{
	//描画カラー情報
	float effc[4] = { 1.0f,1.0f,1.0f,m_Eff_Tra };

	RECT_F dst; //描画先表示位置

	if (ani == true && starcnt == 0 && grade1 == true && grade2 == false
		|| ani == true && starcnt == 1 && grade1 == true && grade2 == false
		|| ani == true && starcnt == 2 && grade1 == true && grade2 == false)
	{
		//表示位置の設定
		dst.m_top = y;
		dst.m_left = x + (40.0f * starcnt);
		dst.m_right = x + 80.0f + (40.0f * starcnt);
		dst.m_bottom = dst.m_top + 80.0f;
		Draw::Draw(71, &m_eff, &dst, effc, 0.0f);
	}

}

//スターの描画
void CObjStageClear::Star_grade_draw(bool grade_f[3],int starcnt,float x , float y)
{
	//描画カラー情報
	float effc[4] = { 1.0f,1.0f,1.0f,m_Eff_Tra };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	//星切り取り位置の設定
	src.m_top    = 0.0f;
	src.m_left   = 0.0f;
	src.m_right  = 184.0f;
	src.m_bottom = 175.0f;

	for (int i = 0; i < starcnt; i++)	//評価（星）の表示
	{
		//表示位置の設定
		dst.m_top    = y;
		dst.m_left   = x + (40.0f * i);
		dst.m_right  = x + 30.0f + (40.0f * i);
		dst.m_bottom = y + 30.0f;
		if (grade_f[i] == true) {
			Draw::Draw(70, &src, &dst, effc, 0.0f);
		}
	}
}

