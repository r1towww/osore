//使用するヘッダー
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\SceneManager.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "ObjStageChoice.h"
//星座位置関連----------------------
#define EarthX	  0
#define EarthY	  380
#define EarthX2	  100
#define EarthY2	  800
#define VenusX	  180

#define VenusX2	  320
#define VenusY	  300
#define VenusY2	  445
#define MercuryX  420
#define MercuryX2 570
#define MercuryY  120
#define MercuryY2 270
#define SunX	  615
#define SunX2	  800
#define SunY	  0
#define SunY2	  90
//----------------------------------
//使用するネームスペース
using namespace GameL;


//イニシャライズ
void CObjStageChoice::Init()
{
	m_key_flag = false;
}

//アクション
void CObjStageChoice::Action()
{
	//主人公位置取得
	ObjStageChoiceHero* hero = (ObjStageChoiceHero*)Objs::GetObj(OBJ_STAGECHOICEHERO);
	float hx = hero->GetX();
	float hy = hero->GetY();

	//地球へ
	if (hx >= EarthX && hx<= EarthX2 && hy >= EarthY&&hy<= EarthY2)
	{
		//▼前シーンからZキー押し続けでこれを押さないように、
		//このシーンに入って一度も押してない状態に移行しないと
		//実行出来ないようにしている。
		if (Input::GetVKey('Z') == true && m_key_flag == true)
		{
			g_stage = Earth;	//ステージの値を地球に変更
			Scene::SetScene(new CSceneEarth());
		}
	}
	//金星へ
	else if (hx >= VenusX && hx <= VenusX2 && hy >= VenusY&&hy <= VenusY2)
	{
		//▼前シーンからZキー押し続けでこれを押さないように、
		//このシーンに入って一度も押してない状態に移行しないと
		//実行出来ないようにしている。
		if (Input::GetVKey('Z') == true && m_key_flag == true)
		{
			//金星に設定
			g_stage = Venus;
			Scene::SetScene(new CSceneStarChoice());
		}
	}
	//水星へ
	else if (hx >= MercuryX && hx <= MercuryX2 && hy >= MercuryY&&hy <= MercuryY2)
	{
		//▼前シーンからZキー押し続けでこれを押さないように、
		//このシーンに入って一度も押してない状態に移行しないと
		//実行出来ないようにしている。
		if (Input::GetVKey('Z') == true && m_key_flag == true)
		{
			//水星に設定
			g_stage = Mercury;
			Scene::SetScene(new CSceneStarChoice());
		}

	}
	//太陽へ
	else if (hx >= SunX && hx <= SunX2 && hy >= SunY&&hy <= SunY2)
	{
		if (Input::GetVKey('Z') == true && m_key_flag == true)
		{
			//仮でタイトルに行くようにしてるからあとでちゃんと太陽にしておいてね
			//太陽に設定
			//g_stage = SunLeo;←ステージが完成したらコメント外してね
			Scene::SetScene(new CSceneTitle());
		}

	}
	else
	{
		m_key_flag = true;
	}

}

//ドロー
void CObjStageChoice::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	//背景------------------------------------
	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1920.0f;
	src.m_bottom = 1080.0f;

	//表示位置の設定
	dst.m_top = 0.0f ;
	dst.m_left = 0.0f ;
	dst.m_right = 800.0f ;
	dst.m_bottom = 600.0f ;

	//表示
	Draw::Draw(2, &src, &dst, c, 0.0f);
	//----------------------------------------

	//地球------------------------------------
	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 300.0f;
	src.m_bottom = 283.0f;

	//表示位置の設定
	dst.m_top =	450.0f;
	dst.m_left = 0.0f;
	dst.m_right = 150.0f;
	dst.m_bottom = 600.0f;

	//表示
	Draw::Draw(3, &src, &dst, c, 0.0f);
	//----------------------------------------


	//金星------------------------------------
	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 303.0f;
	src.m_bottom =303.0f;

	//表示位置の設定
	dst.m_top = 350.0f;
	dst.m_left = 200.0f;
	dst.m_right = 350.0f;
	dst.m_bottom = 500.0f;

	//表示
	Draw::Draw(4, &src, &dst, c, 0.0f);
	//----------------------------------------

	//水星------------------------------------
	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 325.0f;
	src.m_bottom =325.0f;

	//表示位置の設定
	dst.m_top = 180.0f;
	dst.m_left = 450.0f;
	dst.m_right = 600.0f;
	dst.m_bottom =330.0f;

	//表示
	Draw::Draw(5, &src, &dst, c, 0.0f);
	//----------------------------------------

	//太陽------------------------------------
	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 335.0f;
	src.m_bottom = 350.0f;

	//表示位置の設定
	dst.m_top = 0.0f;
	dst.m_left = 650.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 150.0f;

	//表示
	Draw::Draw(6, &src, &dst, c, 0.0f);
	//----------------------------------------

}
