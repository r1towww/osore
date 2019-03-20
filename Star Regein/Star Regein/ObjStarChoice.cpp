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
	m_key_flag = true;
	m_Left = false;
	m_Right = false;
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
	//左の星座
	float o[4] = { 1.0f,1.0f,1.0f,m_Tra1 };
	//右の星座
	float t[4] = { 1.0f,1.0f,1.0f,m_Tra2 };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	//金星選択時に表示される画像---------------------------------------------------------
	if (g_stage == Venus)
	{
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
	}
	//水星選択時に表示される画像---------------------------------------------------------
	else if (g_stage == Mercury)
	{
		//双子座の画像-----------------------------------------------------------------
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 870.0f;
		src.m_right = 1700.0f;
		src.m_bottom = 600.0f;

		//表示位置の設定
		dst.m_top = 150.0f;
		dst.m_left = 100.0f;
		dst.m_right = 350.0f;
		dst.m_bottom = 400.0f;
		//表示
		Draw::Draw(1, &src, &dst, o, 0.0f);
		//-------------------------------------------------------------------------------
		//乙女座---------------------------------------------------------------------
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 1700.0f;
		src.m_right = 2620.0f;
		src.m_bottom = 600.0f;

		//表示位置の設定
		dst.m_top = 150.0f;
		dst.m_left = 430.0f;
		dst.m_right = 680.0f;
		dst.m_bottom = 400.0f;
		//表示
		Draw::Draw(1, &src, &dst, t, 0.0f);
		//----------------------------------------------------------------------------------

	}
	
	//右キー押して選択
	if (Input::GetVKey(VK_RIGHT) == true )
	{
		m_Right = true;
		m_Left = false;

	}
	//左キー押して選択
	else if (Input::GetVKey(VK_LEFT) == true)
	{
		m_Left = true;
		m_Right = false;

	}

	//左のほうを明るくして右のほうを暗くする
	if (m_Left == true)
	{
		m_Tra1 = 1.0f;
		m_Tra2 = 0.5f;

		if (Input::GetVKey('Z') == true)
		{
			if (g_stage == Venus)
			{
				//ステージをおうし座に設定
				g_stage = VenusTaurus;
				Scene::SetScene(new CSceneVenus());
			}
			else if (g_stage == Mercury)
			{
				//ステージを双子座に設定
				g_stage = MercuryGemini;
				Scene::SetScene(new CSceneVenus());
			}
		}

	}
	//右のほうのほうを明るくして左のほうを暗くする
	else if (m_Right == true)
	{
		m_Tra2 = 1.0f;
		m_Tra1 = 0.5f;

		if (Input::GetVKey('Z') == true)
		{
			if (g_stage == Venus)
			{
				//ステージをてんびん座に設定
				g_stage = VenusLibra;
				Scene::SetScene(new CSceneEarth());
			}
			else if (g_stage == Mercury)
			{
				//ステージを乙女座に設定
				g_stage = MercuryVirgo;
				Scene::SetScene(new CSceneEarth());
			}
		}

	}

}
