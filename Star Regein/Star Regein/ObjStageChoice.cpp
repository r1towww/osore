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
	m_alpha = 1.0f;		//アルファ値の初期化
}

//アクション
void CObjStageChoice::Action()
{


}

//ドロー
void CObjStageChoice::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,m_alpha };

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
