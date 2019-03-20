//使用するヘッダー
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\SceneManager.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "ObjTitle.h"

//使用するネームスペース
using namespace GameL;
/*		Planet列挙型
	Earth			地球			0
	VenusCow		金星（牡牛座）	1
	MercuryGemini	水星（双子座）	2
	MercuryVirgo	水星（乙女座）	3
	SunLeo			太陽（獅子座）	4
	* ステージ選択の際変更する *
*/
int g_stage = VenusCow;	//ステージの値の初期化
int g_image_right = 0;
int g_image_reft  = 0;

//イニシャライズ
void CObjTitle::Init()
{
	m_up=false;
	m_down=false;
	m_start=false;
	m_end=false;
}

//アクション
void CObjTitle::Action()
{

}

//ドロー
void CObjTitle::Draw()
{
	float c[4] = { 1,1,1,1 };
	//上キーを押したとき
	if (Input::GetVKey(VK_UP) == true)
	{
		m_up = true;
		m_down = false;

	}
	//下キーを押したとき
	if (Input::GetVKey(VK_DOWN) == true)
	{
		m_down = true;
		m_up = false;
	}
	//ゲーム開始
	if (m_start == true)
	{
		Scene::SetScene(new CSceneStageChoice());
	}
	//ゲーム終了
	if (m_end == true)
	{
		exit(4);
	}
	//カーソルが動く
	if (m_up == true)
	{
		Font::StrDraw(L"→ゲームスタート", 280, 300, 32, c);
		Font::StrDraw(L"ゲーム終了", 280, 340, 32, c);
		//Ｚキーで始める
		if (Input::GetVKey('Z') == true)
		{
			m_start = true;
		}

	}
	else if (m_down == true)
	{
		Font::StrDraw(L"ゲームスタート", 280, 300, 32, c);
		Font::StrDraw(L"→ゲーム終了", 280, 340, 32, c);
		//Zキーで終わる
		if (Input::GetVKey('Z') == true)
		{
			m_end = true;
		}


	}
	//始めはこの状態
	else
	{
		Font::StrDraw(L"ゲームスタート", 280, 300, 32, c);
		Font::StrDraw(L"ゲーム終了", 280, 340, 32, c);
	}


}
