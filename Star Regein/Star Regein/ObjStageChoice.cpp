//使用するヘッダー
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\SceneManager.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "ObjStageChoice.h"

//----------------------------------
//使用するネームスペース
using namespace GameL;


//イニシャライズ
void CObjStageChoice::Init()
{
	g_no_damage = false;	//ノーダメージクリア用変数の初期化
	g_kill_cnt = 0;			//敵殲滅数の初期化

	m_alpha = ALPHAORIGIN;		//アルファ値の初期化
	m_time = true;
}

//アクション
void CObjStageChoice::Action()
{
	if (m_alpha >= 1.0f)
	{
		m_alpha = 1.0f;
	}
	else
	{
		m_alpha += 0.03f;
	}
}

//ドロー
void CObjStageChoice::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,m_alpha };
	float y[4] = { 1.0f,1.0f,0.0f,m_alpha };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	//背景------------------------------------
	//切り取り位置の設定
	src.m_top    = 0.0f;
	src.m_left   = 0.0f;
	src.m_right  = 1920.0f;
	src.m_bottom = 1080.0f;

	//表示位置の設定
	dst.m_top    = 0.0f ;
	dst.m_left   = 0.0f ;
	dst.m_right  = 800.0f ;
	dst.m_bottom = 600.0f ;

	//表示
	Draw::Draw(2, &src, &dst, c, 0.0f);
	//----------------------------------------

	//地球------------------------------------
	//切り取り位置の設定
	src.m_top    = 0.0f;
	src.m_left   = 0.0f;
	src.m_right  = 300.0f;
	src.m_bottom = 283.0f;

	//表示位置の設定
	dst.m_top    = 450.0f;
	dst.m_left   = 0.0f;
	dst.m_right  = 150.0f;
	dst.m_bottom = 600.0f;

	//表示
	Draw::Draw(3, &src, &dst, c, 0.0f);
	if (g_Earth_clear == true)
	{
		Font::StrDraw(L"CLEAR!", 10, 410, 40, y);
	}

	//----------------------------------------

	//金星------------------------------------
	//切り取り位置の設定
	src.m_top    = 0.0f;
	src.m_left   = 0.0f;
	src.m_right  = 303.0f;
	src.m_bottom = 303.0f;

	//表示位置の設定
	dst.m_top    = 350.0f;
	dst.m_left   = 200.0f;
	dst.m_right  = 350.0f;
	dst.m_bottom = 500.0f;


	//表示
	Draw::Draw(4, &src, &dst, c, 0.0f);
	if (g_Venus_clear == true)
	{
		Font::StrDraw(L"CLEAR!", 220, 310, 40, y);
	}

	//----------------------------------------

	//水星------------------------------------
	//切り取り位置の設定
	src.m_top    = 0.0f;
	src.m_left   = 0.0f;
	src.m_right  = 325.0f;
	src.m_bottom = 325.0f;

	//表示位置の設定
	dst.m_top    = 180.0f;
	dst.m_left   = 450.0f;
	dst.m_right  = 600.0f;
	dst.m_bottom = 330.0f;

	//表示
	Draw::Draw(5, &src, &dst, c, 0.0f);
	if (g_Mercury_clear == true)
	{
		Font::StrDraw(L"CLEAR!", 470, 150, 40, y);
	}

	//----------------------------------------

	//太陽------------------------------------
	//切り取り位置の設定
	src.m_top    = 0.0f;
	src.m_left   = 0.0f;
	src.m_right  = 335.0f;
	src.m_bottom = 350.0f;

	//表示位置の設定
	dst.m_top    = 0.0f;
	dst.m_left   = 650.0f;
	dst.m_right  = 800.0f;
	dst.m_bottom = 150.0f;

	//表示
	Draw::Draw(6, &src, &dst, c, 0.0f);
	if (g_Sun_clear == true)
	{
		Font::StrDraw(L"CLEAR!", 680, 150, 40, y);
	}

	//----------------------------------------

}
