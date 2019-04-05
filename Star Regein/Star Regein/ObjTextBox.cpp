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
			m_text ++;
			m_f = true;
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
			Font::StrDraw(L"Star Reginへようこそ！！", 20, 450, 32, c);
			Font::StrDraw(L"ここ、地球ステージでは基本的な操作と", 20, 480, 32, c);
			Font::StrDraw(L"ゲームのクリア条件をお伝えします！", 20, 510, 32, c);
		}
		else if (m_text == 1)
		{
			Font::StrDraw(L"まずは移動してみましょう", 20, 450, 32, c);
		}
		else if (m_text == 2)
		{
			Font::StrDraw(L"方向キーで移動することができます", 20, 450, 32, c);
		}
		else if (m_text == 3)
		{
			Font::StrDraw(L"次にこのゲームのクリア条件は", 20, 450, 32, c);
			Font::StrDraw(L"各ステージにある星を集めることです", 20, 450, 32, c);
		}
		else if (m_text == 4)
		{
			Font::StrDraw(L"星を集めきると星座が完成し、", 20, 450, 32, c);
			Font::StrDraw(L"新しくスキルを使うことができます", 20, 450, 32, c);
		}
		else if (m_text == 5)
		{
			Font::StrDraw(L"それでは星を集めてみましょう", 20, 450, 32, c);
		
		}
	}
	else if (g_stage == VenusTaurus)
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
			Font::StrDraw(L"テスト3", 150, 450, 32, c);
		}
		else if (m_text == 3)
		{
			Font::StrDraw(L"テスト4", 150, 450, 32, c);
		}
		else if (m_text == 4)
		{
			Font::StrDraw(L"テスト5", 150, 450, 32, c);
		}

	}
	

}
