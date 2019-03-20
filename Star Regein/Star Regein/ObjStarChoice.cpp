//使用するヘッダー
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\SceneManager.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "ObjStarChoice.h"



//使用するネームスペース
using namespace GameL;


//イニシャライズ
void CObjStarChoice::Init()
{
	m_oushi = false;
	m_tenbin = false;
	m_Tra1 = 0.5f;
	m_Tra2 = 0.5f;
}

//アクション
void CObjStarChoice::Action()
{

}

//ドロー
void CObjStarChoice::Draw()
{
	//描画カラー情報
	float o[4] = { 1.0f,1.0f,1.0f,m_Tra1 };
	float t[4] = { 1.0f,1.0f,1.0f,m_Tra2 };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置
	//おうし座の画像-----------------------------------------------------------------
	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 870.0f;
	src.m_bottom = 600.0f;

	//表示位置の設定
	dst.m_top = 150.0f;
	dst.m_left = 100.0f;
	dst.m_right = 350.0f;
	dst.m_bottom = 400.0f;
	//表示
	Draw::Draw(1, &src, &dst, o, 0.0f);
	//-------------------------------------------------------------------------------
	//てんびん座---------------------------------------------------------------------
	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 900.0f;
	src.m_bottom = 600.0f;

	//表示位置の設定
	dst.m_top = 150.0f;
	dst.m_left = 430.0f;
	dst.m_right = 680.0f;
	dst.m_bottom = 400.0f;
	//表示
	Draw::Draw(2, &src, &dst, t, 0.0f);
	//----------------------------------------------------------------------------------

	//右キー押して選択
	if (Input::GetVKey(VK_RIGHT) == true)
	{
		m_oushi = true;
		m_tenbin = false;
	}
	//左キー押して選択
	else if (Input::GetVKey(VK_LEFT) == true)
	{
		m_tenbin = true;
		m_oushi = false;
	}

	//おうし座のほうを明るくしててんびん座を暗くする
	if (m_oushi == true)
	{
		m_Tra2 = 1.0f;
		m_Tra1 = 0.5f;
		if (Input::GetVKey('Z') == true)
		{
			//ステージをおうし座に設定
			g_stage = VenusTaurus;
			Scene::SetScene(new CSceneVenus());
			
		}

	}
	//てんびん座のほうを明るくしておうし座を暗くする
	else if (m_tenbin == true)
	{
		m_Tra1 = 1.0f;
		m_Tra2 = 0.5f;
		if (Input::GetVKey('Z') == true)
		{
			//ステージをてんびん座に設定
			g_stage = VenusLibra;
			Scene::SetScene(new CSceneEarth());
		}

	}

}
