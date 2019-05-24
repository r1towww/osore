//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjHero.h"

//使用するネームスペース
using namespace GameL;

float g_posture;
int g_skill = NoSkill;
int g_attack_power = 1;

CObjHero::CObjHero(float x, float y)
{//オブジェ作成時に渡されたx,y座標をメンバ変数に代入
	m_px = x;
	m_py = y;
}

//イニシャライズ
void CObjHero::Init()
{
	m_vx = 0.0f;		//移動ベクトル
	m_vy = 0.0f;

	m_SE_on = 0;
	//初期姿勢
	if (g_Boss_Spawn == true)
	{
		g_posture = HERO_UP;
	}
	else
	{
		g_posture = HERO_DOWN;
	}
	//最大HPの初期化
	g_max_hp = 100.0f;
	//HPの初期化
	g_hp = 100.0f;

	//最大ＭＰの初期化
	g_max_mp = 100.0f;
	//ＭＰの初期化
	g_mp = 100.0f;

	//アニメーション用変数初期化
	m_ani_time = 0;
	m_ani_frame = 1;

	//blockとの衝突状態確認
	m_hit_up    = false;
	m_hit_down  = false;
	m_hit_left  = false;
	m_hit_right = false;

	//無敵フラグ初期化
	m_invincible_flag = false;
	//無敵時間初期化
	m_time = 100;

	//透明度初期化
	m_alpha = ALPHAORIGIN;

	//ＭＰのタイムカウント用初期化
	m_MP_time = 0;

	//ＭＰリジェネカウント用初期化
	m_regene_time = 0;

	//HPリジェネカウント用初期化
	m_hp_regene_time = 0;

	//火傷継続時間
	m_burn_time = 0;
	//火傷合計継続時間
	m_burn_max_time = 0;

	//キーフラグの初期化
	m_key_f = true;
	m_help_key_f = true;
	//ダッシュフラグ初期化
	m_dash_flag = false;
	m_cool_flag = false;
	m_cool_time = 0;

	m_dash_eff_f = false;

	//攻撃制御フラグ
	m_a_flag = true;
	//攻撃力の初期化
	g_attack_power = 1;

	//死亡フラグ
	dead_flag = false;

	//獅子攻撃ヒットフラグ
	m_eff_flag = false;
	m_libra_eff_f = false;
	m_menu_key_f = false;

	//火傷時主人公カラー変更用フラグ
	m_burn_f =false;
	//毒時主人公カラー変更用フラグ
	m_poison_f = false;

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px+15, m_py +15, 50, 50, ELEMENT_PLAYER, OBJ_HERO, 1);

	m_ani = 0;			//アニメーション用
	m_ani2 = 0;
	m_ani3 = 0;
	m_ani_time = 0;		//アニメーション間隔タイム
	m_eff_time = 0;
	m_eff_time2 = 0;
	m_eff_time3 = 0;
	m_eff.m_top    = 0;		//エフェクトの初期化
	m_eff.m_left   = 0;	
	m_eff.m_right  = 240;
	m_eff.m_bottom = 240;
	m_eff2.m_top = 0;		//エフェクトの初期化
	m_eff2.m_left = 0;
	m_eff2.m_right = 192;
	m_eff2.m_bottom = 192;
	m_eff3.m_top = 0;		//死亡エフェクトの初期化
	m_eff3.m_left = 0;
	m_eff3.m_right = 192;
	m_eff3.m_bottom = 192;

}

//アクション
void CObjHero::Action()
{
	//シーン切り替えに使用
	if (m_alpha >= 1.0f)
	{
		m_alpha = 1.0f;
	}
	else
	{
		m_alpha += 0.03;
	}

	//ブラックホールの数を入れる
	if (g_stage == VenusLibra) {	//天秤座
		m_blackhole_num = 4;
	}
	else if (g_stage == MercuryVirgo) {	//乙女座
		m_blackhole_num = 2;
	}
	else if (g_stage == SunLeo) {	//獅子座
		m_blackhole_num = 2;
	}
	else
	{
		m_blackhole_num = 0;
	}

	//ステージクリアの情報を持ってくる
	CObjStageClear* objclear = (CObjStageClear*)Objs::GetObj(OBJ_STAGECLEAR);
	//チュートリアルフラグ、操作制御用フラグが立っていないとき動くようにする
	if (g_tutorial_flag == true || g_move_stop_flag == true || objclear != nullptr)
	{
		m_vx = 0.0f;
		m_vy = 0.0f;
		return;
	}
	//移動ベクトルの破棄
	m_vx = 0.0f;
	m_vy = 0.0f;

		//デバック用
		if (Input::GetVKey('L'))
		{
			g_hp -= 1.0f;
		}
		//デバック用
		if (Input::GetVKey('K'))
		{
			g_hp += 1.0f;
		}
		//デバック用
		if (Input::GetVKey('J'))
		{
			g_mp += 1.0f;
		}
		if (Input::GetVKey('W'))
		{
			//オブジェクト作成
			CObjStageClear* objs = new CObjStageClear();
			Objs::InsertObj(objs, OBJ_STAGECLEAR, 130);
		}
		if (Input::GetVKey('T'))
		{
			g_mp -= 1.0f;
		}

		//移動系統情報--------------------------------------------------

	if (Input::GetVKey(VK_UP))//矢印キー（上）が入力されたとき
	{
		m_vy -= m_speed_power;
		m_dash_flag = true;
		g_posture = HERO_UP;
		m_ani_time += ANITIME;
	}
	else if (Input::GetVKey(VK_DOWN))//矢印キー（下）が入力されたとき
	{
		m_vy += m_speed_power;
		m_dash_flag = true;
		g_posture = HERO_DOWN;
		m_ani_time += ANITIME;
	}
	else if (Input::GetVKey(VK_LEFT))//矢印キー（左）が入力されたとき
	{
		m_vx -= m_speed_power;
		m_dash_flag = true;
		g_posture = HERO_LEFT;
		m_ani_time += ANITIME;
	}
	else if (Input::GetVKey(VK_RIGHT))//矢印キー（右）が入力されたとき
	{
		m_vx += m_speed_power;
		m_dash_flag = true;
		g_posture = HERO_RIGHT;
		m_ani_time += ANITIME;
	}
	else//移動キーの入力が無い場合
	{
		//押していないときに初期化
		m_dash_flag = false;
		m_ani_frame = 1;	//静止フレームにする
		m_ani_time = 0;		//アニメーション時間リセット
	}

	//---------------------------------------------------------------

	//通常攻撃情報---------------------------------------------------

	//Zキーが入力された場合	
	if (Input::GetVKey('Z'))
	{
		if (m_a_flag == true)
		{

			//ブロック情報を持ってくる
			CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

			//ビームサーベルオブジェクト作成
			CObjBeamSaber* objb = new CObjBeamSaber(m_px - block ->GetScrollx(), m_py - block->GetScrolly());
			Objs::InsertObj(objb, OBJ_BEAMSABER, 2);

			m_a_flag = false;
		}
	}
	else
	{
		m_a_flag = true;
	}


	//---------------------------------------------------------------

	//スキル系統情報-------------------------------------------------

		//Xキーが入力されたらダッシュ
		if (Input::GetVKey('X') && g_skill == Taurus
			&& g_Taurus == true && m_dash_flag==true && m_cool_flag == false)
		{
			//ダッシュエフェクト音フラグがオフの場合エフェクト音を鳴らす
			if (m_dash_eff_f == false)
			{
				Audio::Start(11);
				m_dash_eff_f = true;
			}
				m_MP_time++;
				if (m_MP_time > 15)
				{
					m_MP_time = 0;
					g_mp -= 1.0f;
				}
			m_speed_power = DASH_SPEED;

		//ダッシュエフェクト用処理------------------------------
		RECT_F ani_src[6] =
		{
			{   0,    0,  240, 240 },
			{   0,  240,  480, 240 },
			{   0,  480,  720, 240 },
			{ 240,    0,  240, 480 },
			{ 240,  240,  480, 480 },
			{ 240,  480,  720, 480 },
		};
		
		//ダッシュエフェクトのコマ間隔制御
		if (m_eff_time > 4)
		{
			m_ani++;		//ダッシュエフェクトのコマを1つ進める
			m_eff_time = 0;

			m_eff = ani_src[m_ani];//ダッシュエフェクトのRECT配列からm_ani番目のRECT情報取得
		}
		else
		{
			m_eff_time++;	//エフェクトタイムをプラス
		}
		// 5番目（画像最後）まで進んだら、0に戻す
		if (m_ani == 5)
		{
			m_ani = 0;
			m_eff_time = 0;
		}
	}
	else//通常速度
	{	
		Audio::Stop(11);	//ダッシュをしていない際エフェクト音を止める
		m_dash_eff_f = false;	//ダッシュエフェクト音フラグをオフにする(音が鳴るようにする)
		m_dash_flag = false;
		m_speed_power = NORMAL_SPEED;
	}

	//MPが0になったら1ゲージ回復するまで使用不可
	if (g_mp == 0.0f)
		m_cool_flag = true;

	if (m_cool_flag == true)
	{
		m_cool_time++;
		if (m_cool_time >= 200)
		{
			m_cool_time = 0;
			m_cool_flag = false;
		}
	}

	//天秤座の場合（パッシブ）
	if (g_skill == Libra)
	{
		//エフェクトを１度だけ出すようにする
		if (m_libra_eff_f == false)
		{
			m_libra_eff_f = true;	//trueにして入らない用に
			//天秤エフェクトの作成
			CObjSkillLibra* libra = new CObjSkillLibra(m_px, m_py);
			Objs::InsertObj(libra, OBJ_SKILL_LIBRA, 11);
		}
		//残りHPに応じて攻撃力を変更
		if (g_mp <= 0.0f)
		{
			g_attack_power = 1;
		}
		else if (g_hp <= 20.0f)	//20.0f以下
		{
			g_attack_power = 5;	//攻撃力変更
		}
		else if (g_hp <= 50.0f) //50.0f以下
		{
			g_attack_power = 3;	//攻撃力変更
		}
		else if (g_hp > 50.0f)//それ以外（50.0fより大きい場合）
		{
			g_attack_power = 2;	//攻撃力変更
		}
	}
	else
	{
		m_libra_eff_f = false;	//フラグを戻す
	}

	//Xキーが入力された場合、スキルを使用
	if (Input::GetVKey('X'))
	{
		if (m_key_f == true)
		{
			//双子座の場合
			if (g_skill == Gemini&& g_gemini_check == false && g_mp == g_max_mp)
			{
				//ブロック情報を持ってくる
				CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

				//サブ機オブジェクト作成
				CObjSkillGemini* objg = new CObjSkillGemini(m_px - block->GetScrollx(), m_py - block->GetScrolly());
				Objs::InsertObj(objg, OBJ_SKILL_GEMINI, 20);
				//サブ機オブジェクト作成
				CObjSkillGeminiB* objgb = new CObjSkillGeminiB(m_px - block->GetScrollx(), m_py - block->GetScrolly());
				Objs::InsertObj(objgb, OBJ_SKILL_GEMINIB, 20);
				g_mp -= g_max_mp;	//mp消費
				g_gemini_check = true;
			}
			//乙女座の場合
			else if (g_skill == Virgo && g_mp >= 10.0f && g_Virgo == true && g_mp >= 30.0f)
			{
				//ブロック情報を持ってくる
				CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

				//ハート弾オブジェクト作成
				CObjSkillVirgo* objv = new CObjSkillVirgo(m_px - block->GetScrollx(), m_py - block->GetScrolly());
				Objs::InsertObj(objv, OBJ_SKILL_VIRGO, 100);

				g_mp -= 50.0f;	//mp消費

			}
			//獅子座の場合
			else if (g_skill == Leo && g_Leo == true && g_mp >= 30.0f)
			{
				//スタンオブジェクト作成
				CObjSkillLeo* objl = new CObjSkillLeo(m_px, m_py);
				Objs::InsertObj(objl, OBJ_SKILL_LEO, 20);
				Audio::Start(16);
				g_mp -= 30.0f;
			}
			m_key_f = false;
		}
	}
	//Cキーが入力された場合
	else if (Input::GetVKey('C'))
	{
		if (m_key_f == true)
		{
			Audio::Start(1);	//エフェクト音を鳴らす
			g_skill -= NEXTSKILL;	//スキルの画像を次へ送る
			m_key_f = false;
		}
	}
	else if (Input::GetVKey('V'))
	{
		if (m_key_f == true)
		{
			Audio::Start(1);	//エフェクト音を鳴らす
			g_skill += NEXTSKILL;	//スキルの画像を次へ送る
			m_key_f = false;
		}
	}
	else
	{
		m_key_f = true;
	}

	//ボス戦の場合、星の上にいるときHP持続回復
	if (g_Boss_Spawn == true && g_stage == EarthStar)
	{
		//自身のHitBoxを持ってくる
		CHitBox* hit = Hits::GetHitBox(this);
		if (hit->CheckObjNameHit(OBJ_STAR) != nullptr)
		{

			if (g_hp < 100.0f)
			{

				m_hp_regene_time++;
				if (m_hp_regene_time > 15)
				{
					m_hp_regene_time = 0;
					g_hp += 1.0f;
					Audio::Start(24);

				}
			}
		}
	}


	//HPが最大を超えないようにする（回復スキル）
	if (g_hp >= g_max_hp)	//HPが最大を超えたら
	{
		g_hp = g_max_hp;	//最大HPに戻す
	}
	//MPが最大を超えないようにする（リジェネ）
	if (g_mp >= g_max_mp)	//MPが最大を超えたら
	{
		g_mp = g_max_mp;	//最大MPに戻す
	}
	//HPが0を下回らないようにする（火傷によるHPのオーバー）
	if (g_hp <= 0.0f)
	{
		g_hp = 0.0f;
	}
	//MPが0を下回らないようにする（スキルによるMPのオーバー）
	if (g_mp <= 0.0f)
	{
		g_mp = 0.0f;	//0に戻す
	}


	//MPが100未満になったら一定間隔で増える（リジェネ）
	if (m_dash_flag == false && g_skill != Libra)//選択スキルがLibraじゃない、ダッシュしていなかったら増える
	{
		if (g_mp < 100.0f)
		{
			m_regene_time++;
			if (m_regene_time > 15)
			{
				m_regene_time = 0;
				g_mp += 1.0f;
			}
		}
	}

	//----------------------------------------------------------------

		//ヘルプの情報を持ってくる
		CObjHelp* objhelp = (CObjHelp*)Objs::GetObj(OBJ_HELP);
		//ヘルプオブジェクトが存在する場合、入力の許可
		if (objhelp == nullptr)
		{
			//Hキーが入力された場合
			if (Input::GetVKey('H'))
			{
				if (m_help_key_f == true)
				{
					Audio::Start(1);	//エフェクト音を鳴らす
					//HELPオブジェクトを作成
					CObjHelp *objhelp = new CObjHelp();
					Objs::InsertObj(objhelp, OBJ_HELP, 150);
					m_help_key_f = false;
				}
			}
			else
			{
				m_help_key_f = true;
			}
		}

		//Qキーが入力された場合
		if (Input::GetVKey('Q'))
		{
			if (m_menu_key_f == true)
			{
				Audio::Start(1);	//エフェクト音を鳴らす
				//ベクトルを０にする
				m_vx = 0.0f;
				m_vy = 0.0f;
				g_stage = Space;
				//Menuオブジェクトを作成
				CObjMenu *objmenu = new CObjMenu();
				Objs::InsertObj(objmenu, OBJ_MENU, 150);
				g_move_stop_flag = true;	//ストップフラグをオン

			m_menu_key_f = false;
		}
	}
	else
	{
		m_menu_key_f = true;
	}
	//HitBoxの内容を更新
	CHitBox*hit = Hits::GetHitBox(this);

	//ブラックホールの情報を持ってくる
	CObjBlackhole* blackhole = (CObjBlackhole*)Objs::GetObj(OBJ_BLACKHOLE);

	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//ブラックホールの数forループを回す
	for (int i = 0; i < m_blackhole_num; i++)
	{
		//ブラックホールと当たった場合
		if (hit->CheckObjNameHit(OBJ_BLACKHOLE + i) != nullptr)
		{
			//ワープ音
			Audio::Start(7);

			//同じ値のホワイトホール位置に移動させる
			block->SetScrollx(-g_whitehole_x[i][0] + m_px);
			block->SetScrolly(-g_whitehole_y[i][0] + m_py);

			g_gemini_move = true;
		}
	}

	//主人公とBLOCK系統との当たり判定
	if (hit->CheckElementHit(ELEMENT_BLOCK) == true)
	{
		//主人公がブロックとどの角度で当たっているのかを確認
		HIT_DATA** hit_data;							//当たった時の細かな情報を入れるための構造体
		hit_data = hit->SearchElementHit(ELEMENT_BLOCK);	//hit_dataに主人公と当たっている他全てのHitBoxとの情報を入れる
		float r = 0;

		for (int i = 0; i < 10; i++)
		{
			if (hit_data[i] != nullptr)
			{
				r = hit_data[i]->r;

				//角度で上下左右を判定
				if ((r <= 45 && r >= 0) || r >= 315)
				{
					m_vx = -0.15f; //右
				}
				if (r > 45 && r < 135)
				{
					m_vy = 0.15f;//上
				}
				if (r >= 135 && r < 225)
				{
					m_vx = 0.15f;//左
				}
				if (r >= 225 && r < 315)
				{
					m_vy = -0.15f; //下
				}
			}
		}
	}

	if (m_invincible_flag == false)
	{
		if (hit->CheckElementHit(ELEMENT_NULL) == true || hit->CheckElementHit(ELEMENT_ENEMY) == true)
		{
			//敵が主人公とどの角度で当たっているかを確認
			HIT_DATA**hit_data;							//当たった時の細かな情報を入れるための構造体
			hit_data = hit->SearchElementHit(ELEMENT_NULL);//hit_dataに主人公と当たっている他全てのHitBoxとの情報を入れる

			for (int i = 0; i < 10; i++)
			{
				if (hit_data[i] == nullptr)
					continue;

				float r = hit_data[i]->r;

				if ((r < 45 && r >= 0) || r > 315)
				{
					m_vx = -10.0f;//左に移動させる
				}
				if (r >= 45 && r < 135)
				{
					m_vy = 10.0f;//上に移動させる
				}
				if (r >= 135 && r < 225)
				{
					m_vx = 10.0f;//右に移動させる
				}
				if (r >= 225 && r < 315)
				{
					m_vy = -10.0f;//したに移動させる
				}
			}

			//乙女の弾丸と当たった場合MP減少
			if (hit->CheckObjNameHit(OBJ_HOMING_HEART) != nullptr)
				g_mp -= 25.0f;

				//ダメージ音を鳴らす
				Audio::Start(5);
				g_no_damage = true;	//ノーダメージフラグをオンにする
				g_hp -= 10.0f;
				m_f = true;
				m_key_f = true;
				m_invincible_flag = true;
			}
		}

	//獅子と当たった場合火傷状態を付与
	if (hit->CheckObjNameHit(OBJ_LEO) != nullptr)
	{
		Audio::Start(24);
		//敵が主人公とどの角度で当たっているかを確認
		HIT_DATA**hit_data;							//当たった時の細かな情報を入れるための構造体
		hit_data = hit->SearchObjNameHit(OBJ_LEO);//hit_dataに主人公と当たっている他全てのHitBoxとの情報を入れる

		//もし火傷中に再度攻撃を喰らった時継続時間初期化
		m_burn_max_time = 0;
		m_burn_time = 0;

		m_burn_f = true;
		m_eff_flag = true;

	}
	//フラグがオンのとき火傷状態になり、持続ダメージ
	if (m_burn_f == true)
	{
		m_burn_max_time++;
		if (m_burn_time >= 50)
		{
			g_hp -= 2.0f;
			m_burn_time = 0;
		}
		else
		{
			m_burn_time++;
		}

		if (m_burn_max_time > 300)
		{
			m_burn_max_time = 0;
			m_burn_f = false;
		}
	}

	//毒弾と当たった場合毒状態を付与
	if (hit->CheckObjNameHit(OBJ_POISON) != nullptr)
	{
		Audio::Start(22);
		//敵が主人公とどの角度で当たっているかを確認
		HIT_DATA**hit_data;							//当たった時の細かな情報を入れるための構造体
		hit_data = hit->SearchObjNameHit(OBJ_POISON);//hit_dataに主人公と当たっている他全てのHitBoxとの情報を入れる

		//もし毒弾丸に再度攻撃を喰らった時継続時間初期化
		m_burn_max_time = 0;
		m_burn_time = 0;

		m_poison_f = true;
		m_eff_flag = true;

	}
	//フラグがオンのとき毒状態になり、持続ダメージ
	if (m_poison_f == true)
	{
		m_burn_max_time++;
		if (m_burn_time >= 70)
		{
			g_hp -= 2.0f;
			m_burn_time = 0;
		}
		else
		{
			m_burn_time++;
		}

		if (m_burn_max_time > 700)
		{
			m_burn_max_time = 0;
			m_poison_f = false;
		}
	}

	//アイテムが作成されたら無敵にする
	if (g_Make_Item == true)
	{
		m_invincible_flag = true;
	}

	if (m_eff_flag == true)
	{
		//エフェクト用
		RECT_F ani_src2[15] =
		{
			{ 0,    0,  192, 192 },
			{ 0,  192,  384, 192 },
			{ 0,  384,  576, 192 },
			{ 0,  576,  768, 192 },
			{ 0,  768,  960, 192 },
			{ 192,    0,  192, 384 },
			{ 192,  192,  384, 384 },
			{ 192,  384,  576, 384 },
			{ 192,  576,  768, 384 },
			{ 192,  768,  960, 384 },
			{ 384,    0,  384, 576 },
			{ 384,  192,  384, 384 },
			{ 384,  384,  576, 384 },
			{ 384,  576,  768, 384 },
			{ 384,  768,  960, 384 },
		};
		//アニメーションのコマ間隔制御
		if (m_eff_time2 > 2)
		{
			m_ani2++;		//アニメーションのコマを1つ進める
			m_eff_time2 = 0;

			m_eff2 = ani_src2[m_ani2];//アニメーションのRECT配列からm_ani番目のRECT情報取得
		}
		else
		{
			m_eff_time2++;
		}
		// 14番目（画像最後）まで進んだら、0に戻す
		if (m_ani2 == 14)
		{
			m_ani2 = 0;
			m_eff_time2 = 0;

			m_eff_flag = false;
		}
	}

	if (m_f == true)
	{
		m_time--;
		m_alpha = ALPHAUNDER;

	}
	if (m_time <= 0)
	{
		m_f = false;
		m_invincible_flag = false;
		m_alpha = ALPHAORIGIN;

		m_time = 100;
	}

	//移動アニメーション用
	if (m_ani_time > 4)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}
	if (m_ani_frame == 4)
	{
		m_ani_frame = 0;
	}

	//位置の更新
	m_px += m_vx;
	m_py += m_vy;
	//ブロックとの当たり判定実行	
	block->BlockHit(&m_px, &m_py, true,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy
	);

	//作成したHitBox更新用の入り口を取り出す
	hit->SetPos(m_px + 15, m_py + 15);//入り口から新しい位置（主人公の位置）情報に置き換える

	//HPが０になったら削除
	if (g_hp <= 0.0f)
	{
		m_alpha = 0.0f;
		dead_flag = true;
		m_SE_on++ ;

	}
	if (m_SE_on ==1)
	{
		Audio::Start(25);
	}

	if (dead_flag == true)
	{
		//エフェクト用
		RECT_F ani_src3[12] =
		{
			{ 0,    0,  192, 192 },
			{ 0,  192,  384, 192 },
			{ 0,  384,  576, 192 },
			{ 0,  576,  768, 192 },
			{ 0,  768,  960, 192 },
			{ 192,    0,  192, 384 },
			{ 192,  192,  384, 384 },
			{ 192,  384,  576, 384 },
			{ 192,  576,  768, 384 },
			{ 192,  768,  960, 384 },
			{ 384,    0,  384, 576 },
			{ 384,  192,  384, 384 },
		};

		//アニメーションのコマ間隔制御
		if (m_eff_time3 > 2)
		{
			m_ani3++;		//アニメーションのコマを1つ進める
			m_eff_time3 = 0;

			m_eff3 = ani_src3[m_ani3];//アニメーションのRECT配列からm_ani番目のRECT情報取得
		}
		else
		{
			m_eff_time3++;
		}
		// 12番目（画像最後）まで進んだら、0に戻す
		if (m_ani3 == 12)
		{

			m_ani3 = 0;
			m_eff_time3 = 0;

			dead_flag = false;
			g_Death_cnt++;//デスカウントを+する
			Scene::SetScene(new CSceneGameOver());
		}
	}
}

//ドロー
void CObjHero::Draw()
{
	//アニメーション
	int AniData[5] =
	{
		0,1,2,3,0,
	};

	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,m_alpha };
	float c2[4] = { 1.0f,0.7f,0.7f,m_alpha };
	float c3[4] = { 1.0f,1.0f,1.0f,1.0f };
	float c4[4] = { 1.0f,0.7f,1.0f,m_alpha };
	

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置


	//ブロック情報を持ってくる
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//切り取り位置の設定
	src.m_top    = 65.0f * g_posture;
	src.m_left   =  0.0f + (AniData[m_ani_frame] * 64);
	src.m_right  = 64.0f + (AniData[m_ani_frame] * 64);
	src.m_bottom = src.m_top + 65.0f;
	//表示位置の設定
	dst.m_top    = 0.0f	 + m_py;
	dst.m_left   = 80.0f   + m_px;
	dst.m_right  = 0.0f   + m_px;
	dst.m_bottom = 80.0f + m_py;
	//描画
	Draw::Draw(1, &src, &dst, c, 0.0f);

	//火傷状態のとき主人公を赤色に
	if (m_burn_f == true)
		Draw::Draw(1, &src, &dst, c2, 0.0f);
	else if(m_poison_f == true)
		Draw::Draw(1, &src, &dst, c4, 0.0f);
	else
		Draw::Draw(1, &src, &dst, c, 0.0f);

	if (g_stage_clear == false)
	{
		//表示位置の設定
		dst.m_top = 0.0f + m_py;
		dst.m_left = 80.0f + m_px;
		dst.m_right = 0.0f + m_px;
		dst.m_bottom = 80.0f + m_py;
	}
	else
	{
		//表示位置の設定
		dst.m_top = 0.0f + m_py;
		dst.m_left = 40.0f + m_px;
		dst.m_right = 0.0f + m_px;
		dst.m_bottom = 40.0f + m_py;
	}

	//ダッシュフラグがオンの場合
	if (m_dash_flag == true)
	{
		/* g_posture  HERO_UP 1  HERO_LEFT 2  HERO_DOWN 3  HERO_RIGHT 4 */

		//エフェクトの描画
		if (g_posture == HERO_LEFT || g_posture == HERO_RIGHT)	//左右の際、画像が反転してしまうための対策
			Draw::Draw(15, &m_eff, &dst, c, (g_posture * 270.0f + 180.0f));
		else
			Draw::Draw(15, &m_eff, &dst, c, (g_posture * 270.0f));
	}
	else
	{
		m_ani = 0;
	}
	//スタン
	if (m_eff_flag == true)
	{
		//エフェクト用表示位置の設定
		dst.m_top = 0.0f + m_py;	//描画に対してスクロールの影響を加える
		dst.m_left = 0.0f + m_px;
		dst.m_right = 94.0f + m_px;
		dst.m_bottom = 94.0f + m_py;
		//描画
		Draw::Draw(18, &m_eff2, &dst, c, 90.0f);
	}
	if (dead_flag == true)
	{
		//透明の主人公を表示
		dst.m_top = 0.0f + m_py;
		dst.m_left = 80.0f + m_px;
		dst.m_right = 0.0f + m_px;
		dst.m_bottom = 80.0f + m_py;

		Draw::Draw(1, &src, &dst, c, 0.0f);

		//エフェクト用表示位置の設定
		dst.m_top = 0.0f + m_py;	//描画に対してスクロールの影響を加える
		dst.m_left = 0.0f + m_px;
		dst.m_right = 94.0f + m_px;
		dst.m_bottom = 94.0f + m_py;
		//描画
		Draw::Draw(35, &m_eff3, &dst, c3, 90.0f);
	}

}
