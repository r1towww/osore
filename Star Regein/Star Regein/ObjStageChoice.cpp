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
	src.m_left   = 660.0f;
	src.m_right  = 880.0f;
	src.m_bottom = 220.0f;

	//表示位置の設定
	dst.m_top    = 380.0f;
	dst.m_left   = 15.0f;
	dst.m_right  = 175.0f;
	dst.m_bottom = 550.0f;

	//表示
	Draw::Draw(8, &src, &dst, c, 0.0f);
	if (g_Earth_clear == true)
	{
		Font::StrDraw(L"CLEAR!", 40, 550, 40, y);
	}

	//----------------------------------------

	//金星------------------------------------
	//切り取り位置の設定
	src.m_top    = 0.0f;
	src.m_left   = 440.0f;
	src.m_right  = 660.0f;
	src.m_bottom = 220.0f;

	//表示位置の設定
	dst.m_top    = 250.0f;
	dst.m_left   = 200.0f;
	dst.m_right  = 400.0f;
	dst.m_bottom = 450.0f;


	//表示
	Draw::Draw(8, &src, &dst, c, 0.0f);
	if (g_Venus_clear == true)
	{
		Font::StrDraw(L"CLEAR!", 245, 450, 40, y);
	}

	//----------------------------------------

	//水星------------------------------------
	//切り取り位置の設定
	src.m_top    = 0.0f;
	src.m_left   = 220.0f;
	src.m_right  = 440.0f;
	src.m_bottom = 220.0f;

	//表示位置の設定
	dst.m_top    = 150.0f;
	dst.m_left   = 410.0f;
	dst.m_right  = 560.0f;
	dst.m_bottom = 300.0f;

	//表示
	Draw::Draw(8, &src, &dst, c, 0.0f);
	if (g_Mercury_clear == true)
	{
		Font::StrDraw(L"CLEAR!", 435, 300, 40, y);
	}

	//----------------------------------------

	//太陽------------------------------------
	//切り取り位置の設定
	src.m_top    = 0.0f;
	src.m_left   = 0.0f;
	src.m_right  = 220.0f;
	src.m_bottom = 220.0f;

	//表示位置の設定
	dst.m_top    = -150.0f;
	dst.m_left   = 550.0f;
	dst.m_right  = 900.0f;
	dst.m_bottom = 200.0f;

	//表示
	Draw::Draw(8, &src, &dst, c, 0.0f);
	if (g_Sun_clear == true)
	{
		Font::StrDraw(L"CLEAR!", 650, 180, 40, y);
	}

	//----------------------------------------

}
