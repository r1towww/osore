//使用するヘッダー
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\SceneManager.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "ObjPerformanceRoom.h"

//使用するネームスペース
using namespace GameL;
#define CLEAR_F false
//敵をすべて倒した------------------
bool g_Taurus_Enemy_AllKill= CLEAR_F;
bool g_Libra_Enemy_AllKill= CLEAR_F;
bool g_Gemini_Enemy_AllKill= CLEAR_F;
bool g_Viego_Enemy_AllKill= CLEAR_F;
bool g_Leo_Enemy_AllKill= CLEAR_F;
//ラスボスを倒した------------------
bool g_Earth_BossKill= CLEAR_F;
//ノーダメージクリア----------------
bool g_Taurus_NoDamage_Clear= CLEAR_F;
bool g_Libra_NoDamage_Clear= CLEAR_F;
bool g_Gemini_NoDamage_Clear= CLEAR_F;
bool g_Viego_NoDamage_Clear= CLEAR_F;
bool g_Leo_NoDamage_Clear= CLEAR_F;


//イニシャライズ
void CObjPerformanceRoom::Init()
{
	m_page = 0;
	m_next_f = false;
	m_back_f = false;
}

//アクション
void CObjPerformanceRoom::Action()
{
	//Xで選択画面へ戻る
	if (Input::GetVKey('X'))
	{
		g_stage = Space;
		this->SetStatus(false);    //自身に削除命令を出す
	}
	//Zキーで次のページへ
	if (Input::GetVKey('Z'))
	{
		if (m_next_f == true)
		{
			m_page++;
			m_next_f = false;
		}
	}

	else
	{
		m_next_f = true;
	}
	//Cキーで前のページへ
	if (Input::GetVKey('C'))
	{
		if (m_back_f == true)
		{
			if (m_page <= 0)
			{
				;
			}
			else
			{
				m_page--;
			}
			m_back_f = false;
		}
	}
	else
	{
		m_back_f = true;
	}

}

//ドロー
void CObjPerformanceRoom::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	float a[4] = { 1.0f,1.0f,1.0f,0.8f };
	float y[4] = { 1.0f,1.0f,0.0f,1.0f };
	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置
	//背景用画像-----------------------------------
	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 822.0f;
	src.m_bottom = 218.0f;

	//表示位置の設定
	dst.m_top = 100.0f;
	dst.m_left = 50.0f;
	dst.m_right = 750.0f;
	dst.m_bottom = 500.0f;
	//表示
	Draw::Draw(40, &src, &dst, a, 0.0f);
	//----------------------------------------------

	//説明用のメッセージの表示
	Font::StrDraw(L"解放した実績", 75, 120, 27, c);
	//実績達成画面で表示させるためのフラグ処理
	if (m_page == 0)
	{
		Font::StrDraw(L"ノーダメージクリア", 75, 155, 27, c);
	}
	else if (m_page == 1)
	{
		Font::StrDraw(L"ALL KILL", 75, 155, 27, c);
	}
	Font::StrDraw(L"Zキーで次の項目へ", 518, 460, 27, c);
	if (m_page >= 1)
	{
		Font::StrDraw(L"Cキーで前の項目へ", 75, 460, 28, c);
	}
	Font::StrDraw(L"Xキーで閉じる", 570, 120,28, c);


	//ノーダメージクリア
	if (g_Taurus_NoDamage_Clear == true)
	{
		Font::StrDraw(L"牡牛座：ノーダメージクリア！", 75, 190, 28, y);

	}
	else
	{
		Font::StrDraw(L"牡牛座：未達成", 75, 190, 28, c);
	}
	if (g_Libra_NoDamage_Clear == true)
	{
		Font::StrDraw(L"天秤座：ノーダメージクリア！", 75, 225, 28, y);

	}
	else
	{
		Font::StrDraw(L"天秤座：未達成", 75, 225, 28, c);

	}
	if (g_Gemini_NoDamage_Clear == true)
	{
		Font::StrDraw(L"双子座：ノーダメージクリア！", 75, 260, 28, y);

	}
	else
	{
		Font::StrDraw(L"双子座：未達成", 75, 260, 28, c);

	}
	 if (g_Viego_NoDamage_Clear == true)
	{
		Font::StrDraw(L"乙女座：ノーダメージクリア！", 75, 295, 28, y);
	}
	else
	{
		Font::StrDraw(L"乙女座：未達成", 75, 295, 28, c);

	}
	if (g_Leo_NoDamage_Clear == true)
	{
		Font::StrDraw(L"獅子座：ノーダメージクリア！", 75, 330, 28, y);
	}
	else
	{
		Font::StrDraw(L"獅子座：未達成", 75, 330, 28, c);

	}


}
