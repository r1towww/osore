//使用するヘッダー
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\SceneManager.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "ObjTextBox.h"


//----------------------------------
//使用するネームスペース
using namespace GameL;




//イニシャライズ
void CObjTextBox::Init()
{
	m_f = true;
	m_text = 0;
}

//アクション
void CObjTextBox::Action()
{

	if (Input::GetVKey('Z') == true)
	{
		if (m_f == false)
		{
			m_text += 1;
		}
		else
		{
			m_f = true;
		}
	}
	else
	{
		m_f = false;
	}

}

//ドロー
void CObjTextBox::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置
	//地球
	if (g_stage == EarthStar)
	{
		if (m_text == 0)
		{
			Font::StrDraw(L"テスト", 150, 450, 32, c);
		}
		else if (m_text == 1)
		{
			Font::StrDraw(L"テスト2", 150, 450, 32, c);
		}
		else if (m_text == 2)
		{
			Font::StrDraw(L"テスト2", 150, 450, 32, c);
		}
	}
	

}
