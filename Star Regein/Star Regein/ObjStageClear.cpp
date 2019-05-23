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
	m_kill_star_cnt = 0;	//キル評価のカウント

	//メッセージの情報を持ってくる
	CObjMessage* objmes = (CObjMessage*)Objs::GetObj(OBJ_MESSAGE);

	//クリアタイムの評価基準
	if (objmes->GetMINUTE() < 1)
		m_time_grade = 3;
	else if(objmes->GetMINUTE() < 2)
		m_time_grade = 2;
	else if (objmes->GetMINUTE() < 3)
		m_time_grade = 1;
	else
		m_time_grade = 0;

	m_time_star_cnt = 0;		//タイムグレード数用のカウント

	//ダメージの評価基準
	if (g_no_damage == false)
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
}

//アクション
void CObjStageClear::Action()
{
	//キー入力タイムが一定に達した場合、キー入力を許可する
	if ((Input::GetVKey('Z') == true && m_key_f == true || Input::GetVKey(VK_RETURN) == true) && m_key_f == true)
	{
		if (m_next_cnt == 0)
		{
			
			
			
			
			
			
			
			m_next_cnt++;
			
		}
		else if (m_next_cnt == 1)
		{
			m_push_flag = true;
		}
		m_key_f = false;
	}
	else
	{
		m_key_f = true;
	}
	//Zキーを押すと徐々に暗転し、シーン移行
	if (m_push_flag == true)
	{
		m_Tra += 0.03f;
		m_Eff_Tra = 0.03f;
		m_alpha[0] = 0.03f;
		m_alpha[1] = 0.03f;
		m_alpha[2] = 0.03f;
		m_alpha[3] = 0.03f;
		m_alpha[4] = 0.03f;
		m_alpha[5] = 0.03f;
		m_alpha[6] = 0.03f;

		if (m_Tra >= 1.0f)
		{
			Scene::SetScene(new CSceneStageChoice());//ステージ選択
			g_stage_clear = false;
			g_move_stop_flag = false;

		}
	}

	//タイムを60になるまでプラス
	m_time++;
	if (m_time >= 60)
		m_time = 60;




	
	if (m_alpha[3] == 1.0f) {			//被ダメージ評価用
		m_alpha[4] += 0.05f;
		if (m_alpha[4] >= 1.0f) {
			m_alpha[4] = 1.0f;
			m_ani_flag = true;
		}
	}
	else if (m_alpha[2] == 1.0f&& m_ani_flag == false) {	//キル数評価用
		m_alpha[3] += 0.05f;
		if (m_alpha[3] >= 1.0f) {
			m_alpha[3] = 1.0f;
			m_ani_flag = true;
		}
	}
	else if (m_alpha[1] == 1.0f) {							//クリアタイム評価用
		m_alpha[2] += 0.05f;
		if (m_alpha[2] >= 1.0f) {
			m_alpha[2] = 1.0f;
			m_ani_flag = true;
		}
	}
	else if (m_alpha[0] == 1.0f && m_ani_flag == false) {		//取得星座用
		m_alpha[1] += 0.05f;
		if (m_alpha[1] >= 1.0f)
			m_alpha[1] = 1.0f;
	}
	else if (m_time == 60) {	//タイムが60になったらアルファ値を増やす	ステージクリア用
		m_alpha[0] += 0.05f;
		if (m_alpha[0] >= 1.0f) {
			m_alpha[0] = 1.0f;	//1.0fになったら次へ
			m_ani_flag = true;
		}
	}

	

	if (m_ani_flag == true)
	{
		//エフェクト用
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
		if (m_ani_time > 1)
		{
			m_ani++;		//アニメーションのコマを1つ進める
			m_ani_time = 0;

			m_eff = ani_src[m_ani];//アニメーションのRECT配列からm_ani番目のRECT情報取得
		}
		else
		{
			m_ani_time++;
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
			//ステージクリア用グレード
			if (m_grade_f[0] == false)
				m_grade_f[0] = true;
			//クリアタイム評価の分、星を表示
			if (m_time_grade == m_time_star_cnt && m_grade_f[0] == true)
				m_grade_f[1] = true;
			//キル評価の分、星を表示
			if (m_kill_grade == m_kill_star_cnt && m_grade_f[1] == true)
				m_grade_f[2] = true;
			//ダメージ評価の分、星を表示
			if (m_damage_grade == m_damage_star_cnt && m_grade_f[2] == true)
				m_grade_f[3] = true; m_end_start = true;

			if (m_cnt == m_grade_cnt) {
				//最終アニメーションフラグがオンの時
				if (m_end_f == true)
				{
					//最終アニメーションを止めて星を表示させるフラグ
					m_end_start = false;
					m_end_s_f=true;
				}
				else
				{
					m_grade_draw_f = true;
					m_grade_cnt_f = true;
				}
			}
			//フラグがオンの際、星（評価）をいくつ取得できたか
			if (m_cnt_f == true)
				m_cnt++;
			else if (m_cnt_f == false && m_grade_cnt_f == true)
				m_grade_cnt++;


			
			m_ani = 0;
			m_ani_flag = false;
			
			
		}
	}
}

//ドロー
void CObjStageClear::Draw()
{


	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,m_Tra };
	float Stage[4] = { 0.5f,0.5f,0.5f,1.0f };
	float effc[4] = { 1.0f,1.0f,1.0f,m_Eff_Tra };
	float c1[4] = { 1.0f,1.0f,1.0f,m_alpha[0] };	//星座クリアメッセージカラー
	float c2[4] = { 1.0f,1.0f,1.0f,m_alpha[1] };	//取得スキルメッセージカラー
	float c3[4] = { 1.0f,1.0f,1.0f,m_alpha[2] };	//クリアタイムメッセージカラー
	float c4[4] = { 1.0f,1.0f,1.0f,m_alpha[3] };	//敵殲滅数メッセージカラー
	float c4y[4] = { 1.0f,1.0f,0.0f,m_alpha[3] };	//敵殲滅数メッセージカラー（黄）
	float c4r[4] = { 1.0f,0.0f,0.0f,m_alpha[3] };	//敵殲滅数メッセージカラー（赤）
	float c5[4] = { 1.0f,1.0f,1.0f,m_alpha[4] };	//被ダメージメッセージカラー
	float c5y[4] = { 1.0f,1.0f,0.0f,m_alpha[4] };	//被ダメージメッセージカラー（黄）
	float c5r[4] = { 1.0f,0.0f,0.0f,m_alpha[4] };	//被ダメージメッセージカラー（赤）

	float c6s[4] = { 0.0f,0.5f,1.0f,m_alpha[5] };
	float c6a[4] = { 1.0f,0.0f,0.0f,m_alpha[5] };
	float c6b[4] = { 0.0f,1.0f,0.0f,m_alpha[5] };
	float c6c[4] = { 1.0f,1.0f,1.0f,m_alpha[5] };




	float c7[4] = { 1.0f,1.0f,1.0f,m_alpha[6] };


	float y[4] = { 1.0f,1.0f,0.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置




	if (g_stage == EarthStar)
	{
		//地球-------------------------------
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 790.0f;
		src.m_bottom = 590.0f;

		//表示位置の設定
		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 600.0f;

	}
	if (g_stage == VenusTaurus)
	{
		//金星（牡牛座）--------------------------
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 790.0f;
		src.m_bottom = 590.0f;

		//表示位置の設定
		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 600.0f;


	}
	if (g_stage == VenusLibra)
	{
		//金星（牡牛座）--------------------------
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 790.0f;
		src.m_bottom = 590.0f;

		//表示位置の設定
		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 600.0f;


	}
	if (g_stage == MercuryGemini)
	{
		//金星（牡牛座）--------------------------
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 790.0f;
		src.m_bottom = 590.0f;

		//表示位置の設定
		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 600.0f;


	}
	if (g_stage == MercuryVirgo)
	{
		//金星（牡牛座）--------------------------
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 790.0f;
		src.m_bottom = 590.0f;

		//表示位置の設定
		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 600.0f;
	}
	if (g_stage == SunLeo)
	{
		//金星（牡牛座）--------------------------
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 790.0f;
		src.m_bottom = 590.0f;

		//表示位置の設定
		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 600.0f;
	}

	//表示
	Draw::Draw(60, &src, &dst, Stage, 0.0f);

	Font::StrDraw(L"STAGE CLEAR", 120, 150, 100, y);

	Font::StrDraw(L"Zキーでステージ選択へ戻る", 200, 510, 32, y);




	//メッセージの情報を持ってくる
	CObjMessage* objmes = (CObjMessage*)Objs::GetObj(OBJ_MESSAGE);
	//クリア情報
	wchar_t KILLCNT[128];	//キルカウント表示用
	wchar_t DAMAGECNT[128];	//被ダメージの描画
	wchar_t TIME[128];	//タイムの描画


	//m_time_mesから秒分を求める
	//分：秒の値を文字列化
	if (objmes->GetSECOND() < 10)
		swprintf_s(TIME, L"クリアタイム：%d分0%d秒", objmes->GetMINUTE(), objmes->GetSECOND());//秒の1桁目に0を用意
	else
		swprintf_s(TIME, L"クリアタイム：%d分%d秒", objmes->GetMINUTE(), objmes->GetSECOND());

	swprintf_s(KILLCNT, L"敵を%.0f体倒した！", g_kill_cnt);

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 184.0f;
	src.m_bottom = 175.0f;

	//各星座ごとのメッセージ
	if (g_stage == EarthStar)
	{
		Font::StrDraw(L"地球をクリアした！", 15, 250, 21, c1);
		Font::StrDraw(L"取得したスキル：無し", 15, 280, 21, c2);
	}
	if (g_stage == VenusTaurus)
	{
		Font::StrDraw(L"牡牛座をクリアした！", 15, 250, 21, c1);

		//表示位置の設定
		dst.m_top = 220.0f;
		dst.m_left = 220.0f;
		dst.m_right = dst.m_left + 80.0f;
		dst.m_bottom = dst.m_top + 80.0f;
		if (m_ani_flag == true && m_grade_f[0] == false)
			Draw::Draw(71, &m_eff, &dst, effc, 0.0f);

		//表示位置の設定
		dst.m_top = 245.0f;
		dst.m_left = 245.0f;
		dst.m_right = 275.0f;
		dst.m_bottom = 275.0f;
		if (m_grade_f[0] == true)
			Draw::Draw(70, &src, &dst, effc, 0.0f);

		Font::StrDraw(L"取得したスキル：牡牛座", 15, 280, 21, c2);
	}
	if (g_stage == VenusLibra)
	{
		Font::StrDraw(L"天秤座をクリアした！", 15, 250, 21, c1);
		Font::StrDraw(L"取得したスキル：天秤座", 15, 280, 21, c2);
	}
	if (g_stage == MercuryGemini)
	{
		Font::StrDraw(L"双子座をクリアした！", 15, 250, 21, c1);
		Font::StrDraw(L"取得したスキル：双子座", 15, 280, 21, c2);
	}
	if (g_stage == MercuryVirgo)
	{
		Font::StrDraw(L"乙女座をクリアした！", 15, 250, 21, c1);
		Font::StrDraw(L"取得したスキル：乙女座", 15, 280, 21, c2);
	}
	if (g_stage == SunLeo)
	{
		Font::StrDraw(L"獅子座をクリアした！", 15, 250, 21, c1);
		Font::StrDraw(L"取得したスキル：獅子座", 15, 280, 21, c2);
	}

	Font::StrDraw(TIME, 15, 310, 21, c3);


	//クリアタイム評価の描画用----------------------------------------
	if (m_time_star_cnt == 1 && m_grade_f[1] != true || m_time_star_cnt == 2 && m_grade_f[1] != true) 
	{
		m_ani_flag = true;
	}
	if (m_ani_flag == true && m_time_star_cnt == 0 && m_grade_f[0] == true && m_grade_f[1] != true
		|| m_ani_flag == true && m_time_star_cnt == 1 && m_grade_f[0] == true && m_grade_f[1] != true
		|| m_ani_flag == true && m_time_star_cnt == 2 && m_grade_f[0] == true && m_grade_f[1] != true)
	{
		//表示位置の設定
		dst.m_top = 280.0f;
		dst.m_left = 220.0f + (40.0f * m_time_star_cnt);
		dst.m_right = 300.0f + (40.0f * m_time_star_cnt);
		dst.m_bottom = dst.m_top + 80.0f;
		Draw::Draw(71, &m_eff, &dst, effc, 0.0f);
	}
	for (int i = 0; i < m_time_star_cnt; i++)
	{
		//表示位置の設定
		dst.m_top = 305.0f;
		dst.m_left = 245.0f + (40.0f * i);
		dst.m_right = 275.0f + (40.0f * i);
		dst.m_bottom = 335.0f;
		if (m_time_star_f[i] == true) 
		{
			Draw::Draw(70, &src, &dst, effc, 0.0f);
		}
	}
	//-----------------------------------------------------------------


	//地球以外の星の場合
	if (g_stage != EarthStar)
	{
		//敵殲滅用メッセージの表示
		if (g_kill_cnt == g_enemy_cnt)
		{
			Font::StrDraw(L"敵を全滅させた！", 15, 340, 21, c4y);
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
		else if (g_kill_cnt == 0)
		{
			Font::StrDraw(L"誰も倒さなかった！", 15, 340, 21, c4r);
		}
		else if (g_kill_cnt > 0)
			Font::StrDraw(KILLCNT, 15, 340, 21, c4);
	}
	

	//キル数評価の描画用----------------------------------------
	if (m_kill_star_cnt == 1 && m_grade_f[2] != true || m_kill_star_cnt == 2 && m_grade_f[2] != true)
	{
		m_ani_flag = true;
	}
	if (m_ani_flag == true && m_kill_star_cnt == 0 && m_grade_f[1] == true && m_grade_f[2] != true && m_kill_grade != 0
		|| m_ani_flag == true && m_kill_star_cnt == 1 && m_grade_f[1] == true && m_grade_f[2] != true
		|| m_ani_flag == true && m_kill_star_cnt == 2 && m_grade_f[1] == true && m_grade_f[2] != true)
	{
		//表示位置の設定
		dst.m_top    = 310.0f;
		dst.m_left   = 220.0f + (40.0f * m_kill_star_cnt);
		dst.m_right  = 300.0f + (40.0f * m_kill_star_cnt);
		dst.m_bottom = dst.m_top + 80.0f;
		Draw::Draw(71, &m_eff, &dst, effc, 0.0f);
	}
	//else if (m_grade_f[1] == true && m_kill_grade == 0)
	//{
	//	m_grade_f[2] = true;
	//	m_ani_flag = false;
	//}
	for (int i = 0; i < m_kill_grade; i++)
	{
		//表示位置の設定
		dst.m_top    = 335.0f;
		dst.m_left   = 245.0f + (40.0f * i);
		dst.m_right  = 275.0f + (40.0f * i);
		dst.m_bottom = 365.0f;
		if (m_kill_star_f[i] == true) {
			Draw::Draw(70, &src, &dst, effc, 0.0f);
		}
	}

	//-----------------------------------------------------------------


	//ノーダメージクリアメッセージの表示
	if (g_no_damage == false)
	{
		Font::StrDraw(L"ノーダメージクリア！", 15, 370, 21, c5y);

		if (m_damage_star_cnt == 1 && m_grade_f[3] != true || m_damage_star_cnt == 2 && m_grade_f[3] != true) {
			m_ani_flag = true;
		}
		if (m_ani_flag == true && m_damage_star_cnt == 0 && m_grade_f[2] == true && m_grade_f[3] != true
			|| m_ani_flag == true && m_damage_star_cnt == 1 && m_grade_f[2] == true && m_grade_f[3] != true
			|| m_ani_flag == true && m_damage_star_cnt == 2 && m_grade_f[2] == true && m_grade_f[3] != true)
		{
			//表示位置の設定
			dst.m_top    = 340.0f;
			dst.m_left   = 220.0f + (40.0f * m_damage_star_cnt);
			dst.m_right  = 300.0f + (40.0f * m_damage_star_cnt);
			dst.m_bottom = dst.m_top + 80.0f;
			Draw::Draw(71, &m_eff, &dst, effc, 0.0f);
		}
		for (int i = 0; i < m_damage_star_cnt; i++)
		{
			//表示位置の設定
			dst.m_top = 365.0f;
			dst.m_left = 245.0f + (40.0f * i);
			dst.m_right = 275.0f + (40.0f * i);
			dst.m_bottom = 395.0f;
			if (m_damage_star_f[i] == true) {
				Draw::Draw(70, &src, &dst, effc, 0.0f);
			}
		}

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
	


	//ダメージまでの評価を表示し終えた際
	if (m_grade_f[3] == true && m_alpha[4] == 1.0f&& m_end_start == true)
	{
		m_cnt_f = false;
	
		for (int i = 0; i < m_cnt; i++)
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
	
	if (m_end_s_f == true)
	{
		for (int i = 0; i < m_grade_cnt; i++)
		{
			//表示位置の設定
			dst.m_top = 425.0f;
			dst.m_left = 45.0f + (50.0f * i);
			dst.m_right = 80.0f + (50.0f * i);
			dst.m_bottom = 460.0f;
			if (m_grade_draw_f == true) {
				Draw::Draw(70, &src, &dst, effc, 0.0f);
			}
		}
		m_alpha[5] += 0.05f;
		if (m_alpha[5] >= 1.0f) {
			m_alpha[5] = 1.0f;
		}
		if (m_grade_cnt == 10)
			Font::StrDraw(L"S", 550, 390, 120, c6s);
		else if (m_grade_cnt >= 7)
			Font::StrDraw(L"A", 550, 390, 120, c6a);
		else if (m_grade_cnt >= 4)
			Font::StrDraw(L"B", 550, 390, 120, c6b);
		else
			Font::StrDraw(L"C", 550, 390, 120, c6c);
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