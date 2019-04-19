//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"

#include "GameHead.h"
#include "ObjStatus.h"

//使用するネームスペース
using namespace GameL;

float g_hp;
float g_max_hp;
float g_mp;
float g_max_mp;

CObjStatus::CObjStatus()
{

}

//イニシャライズ
void CObjStatus::Init()
{
	m_red = 1.0f;		//HP用カラー 赤	の初期化
	m_gleen = 1.0f;		//HP用カラー 緑	の初期化
	m_blue = 1.0f;		//HP用カラー 青	の初期化


}

//アクション
void CObjStatus::Action()
{
	if (g_hp >= 30.0f)
	{
		m_red = 1.0f;
		m_gleen = 1.0f;	
		m_blue = 1.0f;
	}
}

//ドロー
void CObjStatus::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	float hpc[4] = { m_red,m_gleen,m_blue,1.0f };
	float mpc[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

//HP,MPの背景用--------------------------------

	//切り取り位置の設定
	src.m_top    = 0.0f;
	src.m_left   = 360.0f;
	src.m_right  = 390.0f;
	src.m_bottom = 50.0f;

	//表示位置の設定
	dst.m_top    =  10.0f + STATUS_PY;
	dst.m_left   =   0.0f ;
	dst.m_right  = 324.0f + STATUS_PX;
	dst.m_bottom =  53.0f + STATUS_PY;

	//描画
	Draw::Draw(9, &src, &dst, c, 0.0f);

//----------------------------------------------

//HP、MPの文字の描画----------------------------

	Font::StrDraw(L"HP", 2, 12, 21, c);	//HP
	Font::StrDraw(L"MP", 2, 33, 21, c);	//MP

//----------------------------------------------

//HP描画用--------------------------------------
	//切り取り位置の設定
	src.m_top    = 0.0f;
	src.m_left   = 0.0f;
	src.m_right  = (g_hp / g_max_hp)*1600.0f;
	src.m_bottom = 112.0f;

	//表示位置の設定
	dst.m_top    = 13.0f + STATUS_PY;
	dst.m_left   =  4.0f + STATUS_PX;
	dst.m_right  = (g_hp / g_max_hp)*320.0f + STATUS_PX;
	dst.m_bottom = 28.0f + STATUS_PY;

	//描画
	Draw::Draw(10, &src, &dst, hpc, 0.0f);
//----------------------------------------------

//MP描画用--------------------------------------
	//切り取り位置の設定
	src.m_top    = 0.0f;
	src.m_left   = 0.0f;
	src.m_right  = (g_mp / g_max_mp)*1600.0f;
	src.m_bottom = 112.0f;

	//表示位置の設定
	dst.m_top    = 35.0f + STATUS_PY;
	dst.m_left   =  4.0f + STATUS_PX;
	dst.m_right  = (g_mp / g_max_mp)*320.0f + STATUS_PX;
	dst.m_bottom = 50.0f + STATUS_PY;

	//描画
	Draw::Draw(11, &src, &dst, mpc, 0.0f);
//----------------------------------------------


}