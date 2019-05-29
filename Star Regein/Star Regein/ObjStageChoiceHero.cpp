//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\DrawFont.h"
#include "GameHead.h"
#include "ObjStageChoiceHero.h"
#include "ObjStageChoice.h"

//使用するネームスペース
using namespace GameL;


ObjStageChoiceHero::ObjStageChoiceHero(float x, float y)
{//オブジェ作成時に渡されたx,y座標をメンバ変数に代入
	g_stage_px = x;
	g_stage_py = y;
}

//イニシャライズ
void ObjStageChoiceHero::Init()
{
	//移動ベクトル
	m_vx = 0.0f;		
	m_vy = 0.0f;
	m_f = false;
	//初期姿勢
	g_posture = HERO_DOWN;

	m_ani_time = 0;
	m_ani_frame = 1;
	m_time = false;
	m_alpha = ALPHAORIGIN;

	//ステージ開始を認識させる
	m_stage_start = true;
	m_Tra = 1.0f;

}


//アクション
void ObjStageChoiceHero::Action()
{
	//シーン切り替え用
	if (m_alpha >= 1.0f)
	{
		m_alpha = 1.0f;
	}
	else
	{
		m_alpha += 0.03f;
	}

	g_gemini_check = false;
	//星座選択時に入力制御する
	if(g_stage!=Space)
	{
		return;
	}

	//チュートリアルフラグ、操作制御用フラグが立っていないとき動くようにする
	if (g_tutorial_flag == true || g_move_stop_flag == true )
	{
		m_vx = 0.0f;
		m_vy = 0.0f;
		return;
	}

	//主人公機が領域外行かない処理
	if (g_stage_px + 80.0f > 800.0f)
	{
		g_stage_px = 800.0f - 80.0f;
	}
	if (g_stage_py + 80.0f > 600.0f)
	{
		g_stage_py = 600.0f - 80.0f;
	}
	if (g_stage_py < 0.0f)
	{
		g_stage_py = 0.0f;
	}
	if (g_stage_px < 0.0f)
	{
		g_stage_px = 0.0f;
	}

	//移動ベクトルの破棄
	m_vx = 0.0f;
	m_vy = 0.0f;

	//Shiftキーが入力されたらダッシュ
	if ((Input::GetVKey('X')))
	{
		m_speed_power = STAGE_DASH_SPEED;
	}
	else//通常速度
	{
		m_speed_power = STAGE_NORMAL_SPEED;
	}

	if (Input::GetVKey(VK_UP))//矢印キー（上）が入力されたとき
	{
		m_vy -= m_speed_power;
		g_posture = HERO_UP;
		m_ani_time += ANITIME;
	}
	else if (Input::GetVKey(VK_DOWN))//矢印キー（下）が入力されたとき
	{
		m_vy += m_speed_power;
		g_posture = HERO_DOWN;
		m_ani_time += ANITIME;
	}
	else if (Input::GetVKey(VK_LEFT))//矢印キー（左）が入力されたとき
	{
		m_vx -= m_speed_power;
		g_posture = HERO_LEFT;
		m_ani_time += ANITIME;
	}
	else if (Input::GetVKey(VK_RIGHT))//矢印キー（右）が入力されたとき
	{
		m_vx += m_speed_power;
		g_posture = HERO_RIGHT;
		m_ani_time += ANITIME;
	}
	else//移動キーの入力が無い場合
	{
		m_ani_frame = 1;	//静止フレームにする
		m_ani_time = 0;		//アニメーション時間リセット
	}

	//アニメーション用
	if (m_ani_time > 4)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}

	if (m_ani_frame == 4)
	{
		m_ani_frame = 0;
	}

	//ステージ選択画面の情報を取得
	CObjStageChoice* stagec = (CObjStageChoice*)Objs::GetObj(OBJ_STAGECHOICE);
	//ステージ選択(星座)オブジェクト作成
	CObjStarChoice* star = new CObjStarChoice();

	CObjTextBox* text = (CObjTextBox*)Objs::GetObj(OBJ_TEXTBOX);

	//キー入力を長押しで出来ないようにする
	if (Input::GetVKey('Z') == false && Input::GetVKey(VK_RETURN) == false || text != nullptr)
	{
		g_key_flag = true;	//離したらオンにする
	}

	//Qキーが入力された場合
	if (Input::GetVKey('Q'))
	{
		if (m_f == true)
		{
			Audio::Start(1);	//エフェクト音を鳴らす
								//ベクトルを０にする
			m_vx = 0.0f;
			m_vy = 0.0f;
			//Menuオブジェクトを作成
			CObjMenu *objmenu = new CObjMenu();
			Objs::InsertObj(objmenu, OBJ_MENU, 150);
			g_move_stop_flag = true;	//ストップフラグをオン

			m_f = false;
		}
	}
	else
	{
		m_f = true;
	}

	// Zキーを入力かつ、キーフラグがオンの時に実行
	if ((Input::GetVKey('Z') == true && g_key_flag == true || Input::GetVKey(VK_RETURN) == true) && g_key_flag == true)
	{
		//地球へ
		if (g_stage_px >= EarthX && g_stage_px + 80.0f <= EarthX2 && g_stage_py >= EarthY&&g_stage_py + 80.0f <= EarthY2)
		{
			//▼前シーンからZキー押し続けでこれを押さないように、
			//このシーンに入って一度も押してない状態に移行しないと
			//実行出来ないようにしている。
			g_stage = Earth;	//ステージの値を地球に変更
			Audio::Start(1);
			g_key_flag = false;	//キーフラグをオフ
			//ステージ選択(星座)オブジェクト作成
			CObjStarChoice* star = new CObjStarChoice();

			Objs::InsertObj(star, OBJ_STARCHOICE, 20);
		}
		//金星へ
		else if (g_stage_px >= VenusX && g_stage_px + 80.0f <= VenusX2 && g_stage_py >= VenusY&&g_stage_py + 80.0f <= VenusY2)
		{
			if (g_Earth_clear == true)
			{
				//▼前シーンからZキー押し続けでこれを押さないように、
				//このシーンに入って一度も押してない状態に移行しないと
				//実行出来ないようにしている。
				//金星に設定
				g_stage = Venus;
				Audio::Start(1);
				g_key_flag = false;	//キーフラグをオフ
				//ステージ選択(星座)オブジェクト作成
				Objs::InsertObj(star, OBJ_STARCHOICE, 20);
			}
		}
		//水星へ
		else if (g_stage_px >= MercuryX && g_stage_px + 80.0f <= MercuryX2 && g_stage_py >= MercuryY&&g_stage_py + 80.0f <= MercuryY2)
		{
			if (g_Venus_clear == true)
			{
				//	//▼前シーンからZキー押し続けでこれを押さないように、
				//	//このシーンに入って一度も押してない状態に移行しないと
				//	//実行出来ないようにしている。
				//	//水星に設定
				g_stage = Mercury;
				Audio::Start(1);
				g_key_flag = false;	//キーフラグをオフ
				//ステージ選択(星座)オブジェクト作成
				Objs::InsertObj(star, OBJ_STARCHOICE, 20);
			}
		}
		//太陽へ
		else if (g_stage_px >= SunX && g_stage_px + 80.0f <= SunX2 && g_stage_py >= SunY&&g_stage_py + 80.0f <= SunY2)
		{
			if (g_Mercury_clear == true)
			{
				Audio::Start(1);
				//太陽に設定
				g_stage = Sun;
				g_key_flag = false;	//キーフラグをオフ
				//ステージ選択(星座)オブジェクト作成
				Objs::InsertObj(star, OBJ_STARCHOICE, 20);
			}
		}
		//実績確認へ
		else if (g_stage_px >= 550 && g_stage_px <= 700 && g_stage_py >= 400&&g_stage_py  <= 550)
		{
			g_stage = Performance;
			Audio::Start(1);
			g_key_flag = false;	//キーフラグをオフ

			//実績オブジェクト作成
			CObjPerformanceRoom* per = new CObjPerformanceRoom();
			Objs::InsertObj(per, OBJ_PERFORMANCE_ROOM, 20);

		}
		//ショートカット
		else if (g_stage_px >= 50 && g_stage_px <= 100 && g_stage_py >= 50 && g_stage_py <= 100)
		{
			Audio::Start(1);

			g_key_flag = false;	//キーフラグをオフ
			g_Earth_clear = true;	//地球	
			g_Venus_clear = true;	//金星
			g_Mercury_clear = true;	//水星
			g_Sun_clear = true;	//太陽

			g_Taurus_clear = true;	//牡牛座	
			g_Libra_clear = true;	//天秤座
			g_Gemini_clear = true;	//双子座
			g_Virgo_clear = true;	//乙女座
			g_Leo_clear = true;	//獅子座
			g_Boss_Spawn = true;
			g_Taurus = true;	//牡牛座	
			g_Libra = true;	//天秤座
			g_Gemini = true;	//双子座
			g_Virgo = true;	//乙女座
			g_Leo = true;	//獅子座

		}

	}

	//位置の更新
	g_stage_px += m_vx;
	g_stage_py += m_vy;
}

//ドロー
void ObjStageChoiceHero::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,m_alpha };
	float red[4] = { 1.0f,0.0f,0.0f,m_alpha };


	//アニメーション
	int AniData[5] =
	{
		0,1,2,3,0,
	};
	//各惑星が何の惑星かわかるように描画
	//地球
	if (g_stage_px >= EarthX && g_stage_px + 80.0f <= EarthX2 && g_stage_py >= EarthY&&g_stage_py + 80.0f <= EarthY2)
	{
		if (g_Sun_clear == true)
		{
			Font::StrDraw(L"地球ステージ", 32, 32, 32, red);
		}
		else
			Font::StrDraw(L"地球ステージ", 32, 32, 32, c);
	}
	
	//地球をクリアしていない場合このメッセージを表示する
	if (g_stage_px >= VenusX && g_stage_px + 80.0f <= VenusX2 && g_stage_py >= VenusY&&g_stage_py + 80.0f <= VenusY2&&g_Earth_clear == false)
	{
		Font::StrDraw(L"前のステージをすべてクリアしてきてね", 32, 32, 28, red);
	}
	//金星
	else if (g_stage_px >= VenusX && g_stage_px + 80.0f <= VenusX2 && g_stage_py >= VenusY&&g_stage_py + 80.0f <= VenusY2&&g_Earth_clear == true)
	{
		Font::StrDraw(L"金星ステージ", 32, 32, 32, c);
	}	
	//金星をクリアしていない場合このメッセージを表示する
	if (g_stage_px >= MercuryX && g_stage_px + 80.0f <= MercuryX2 && g_stage_py >= MercuryY&&g_stage_py + 80.0f <= MercuryY2&&g_Venus_clear==false)
	{
		Font::StrDraw(L"前のステージをすべてクリアしてきてね", 32, 32, 28, red);
	}
	//水星
	else if (g_stage_px >= MercuryX && g_stage_px + 80.0f <= MercuryX2 && g_stage_py >= MercuryY&&g_stage_py + 80.0f <= MercuryY2&&g_Venus_clear == true)
	{
		Font::StrDraw(L"水星ステージ", 32, 32, 32, c);
	}
	//水星をクリアしていない場合このメッセージを表示する
	if (g_stage_px >= SunX && g_stage_px + 80.0f <= SunX2 && g_stage_py >= SunY&&g_stage_py + 80.0f <= SunY2&&g_Mercury_clear == false)
	{
		Font::StrDraw(L"前のステージをすべてクリアしてきてね", 32, 32, 28, red);
	}
	//太陽
	else if (g_stage_px >= SunX && g_stage_px + 80.0f <= SunX2 && g_stage_py >= SunY&&g_stage_py + 80.0f <= SunY2&&g_Mercury_clear == true)
	{
		Font::StrDraw(L"太陽ステージ", 32, 32, 32, c);
	}
	if (g_stage_px >= 550 && g_stage_px <= 700 && g_stage_py >= 400&&g_stage_py  <= 550)
	{
		Font::StrDraw(L"実績", 32, 32, 32, c);
	}

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	//切り取り位置の設定
	src.m_top    = 64.0f * g_posture;
	src.m_left   =  0.0f + (AniData[m_ani_frame] * 64);
	src.m_right  = 64.0f + (AniData[m_ani_frame] * 64);
	src.m_bottom = src.m_top + 64.0f;

	//表示位置の設定
	dst.m_top    =  0.0f + g_stage_py;
	dst.m_left   = 80.0f + g_stage_px;
	dst.m_right  =  0.0f + g_stage_px;
	dst.m_bottom = 80.0f + g_stage_py;

	//表示
	Draw::Draw(1, &src, &dst, c, 0.0f);
	float Stage[4] = { 1.0f,1.0f,1.0f,m_Tra };

	//シーン移行用
	if (m_stage_start == true)
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
	
		m_Tra -= 0.03f;
		if (m_Tra <= 0.0f)
		{
			m_stage_start = false;
		}

		Draw::Draw(9, &src, &dst, Stage, 0.0f);
	}

}
