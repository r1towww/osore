//使用するヘッダー
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\SceneManager.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "ObjTitle.h"
//各惑星・星座のクリア状況
bool g_Earth_clear=false;	//地球	
bool g_Venus_clear=false;	//金星
bool g_Mercury_clear=false;	//水星
bool g_Sun_clear=false;	//太陽

bool g_Taurus_clear=false;	//牡牛座	
bool g_Libra_clear=false;	//天秤座
bool g_Gemini_clear=false;	//双子座
bool g_Virgo_clear=false;	//乙女座
bool g_Leo_clear=false;	//獅子座

//使用するネームスペース
using namespace GameL;
/*		Planet列挙型
	Earth,			//地球			0
	EarthStar,		//地球			1
	Venus,			//金星			2
	VenusTaurus,	//金星（牡牛座）3
	VenusLibra,		//金星（天秤座）4
	Mercury,		//水星			5
	MercuryGemini,	//水星（双子座）6
	MercuryVirgo,	//水星（乙女座）7
	Sun,			//太陽			8
	SunLeo,			//太陽（獅子座）9
	Space,			//ステージ選択	10
	* ステージ選択の際変更する *
*/
int g_stage = Space;	//ステージの値の初期化
//各星座の取得情報
bool g_Taurus = true;	//牡牛座	
bool g_Libra  = true;	//天秤座
bool g_Gemini = true;	//双子座
bool g_Virgo  = true;	//乙女座
bool g_Leo    = true;	//獅子座
bool g_key_flag = false;	//キー入力制御フラグ

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
