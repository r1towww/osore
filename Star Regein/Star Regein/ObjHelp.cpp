//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"
#include "GameHead.h"

#include "ObjHelp.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjHelp::Init()
{
}

//アクション
void CObjHelp::Action()
{





	//Hキーが話された場合
	if (Input::GetVKey('H') == false)
	{
		this->SetStatus(false);
	}



}

//ドロー
void CObjHelp::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };	//メッセージフォントカラー
	float a[4] = { 1.0f,1.0f,1.0f,0.5f };	

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

//背景用画像-----------------------------------
	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 822.0f;
	src.m_bottom = 218.0f;

	//表示位置の設定
	dst.m_top    = 100.0f;
	dst.m_left   = 50.0f;
	dst.m_right  = 750.0f;
	dst.m_bottom = 500.0f;
	//表示
	Draw::Draw(40, &src, &dst, a, 0.0f);
//----------------------------------------------

//操作説明用メッセージ--------------------------

	//説明用のメッセージの表示
	Font::StrDraw(L"Zキー 前方に剣で攻撃", 65, 115, 25, c);	
	Font::StrDraw(L"Xキー 選択中のスキル発動", 65, 140, 25, c);	
	Font::StrDraw(L"Cキー スキルの切り替え", 65, 165, 25, c);



//----------------------------------------------
	//選択中のスキルによって説明文を変更
	if (g_skill == Taurus)	//牡牛座
	{
		//説明文
		Font::StrDraw(L"*牡牛座スキル*    MP消費 1ゲージ", 320, 320, 25, c);
		Font::StrDraw(L"Shiftキーを押しながら移動すると、", 320, 345, 25, c);
		Font::StrDraw(L"ダッシュが可能！！", 320, 370, 25, c);

		
		//切り取り位置の設定
		src.m_top    = 0.0f;
		src.m_left   = 300.0f;
		src.m_right  = 600.0f;
		src.m_bottom = 200.0f;

	}
	else if (g_skill == Libra)	//天秤座
	{
		src.m_top    = 0.0f;
		src.m_left   = 600.0f;
		src.m_right  = 900.0f;
		src.m_bottom = 200.0f;
	}
	else if (g_skill == Gemini)	//双子座
	{
		src.m_top    = 0.0f;
		src.m_left   = 900.0f;
		src.m_right  = 1200.0f;
		src.m_bottom = 200.0f;
	}
	else if (g_skill == Virgo)	//乙女座
	{
		src.m_top    = 0.0f;
		src.m_left   = 1200.0f;
		src.m_right  = 1500.0f;
		src.m_bottom = 200.0f;
	}
	else if (g_skill == Leo)	//獅子座
	{
		src.m_top    = 0.0f;
		src.m_left   = 1500.0f;
		src.m_right  = 1800.0f;
		src.m_bottom = 200.0f;
	}
	//表示位置の設定
	dst.m_top    = 290.0f;
	dst.m_left   = 80.0f;
	dst.m_right  = 280.0f;
	dst.m_bottom = 490.0f;
	//表示
	Draw::Draw(13, &src, &dst, a, 0.0f);
}
