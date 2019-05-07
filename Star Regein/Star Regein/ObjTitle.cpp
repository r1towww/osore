//使用するヘッダー
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\SceneManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjTitle.h"

#define CLEARF	true

//各惑星・星座のクリア状況
bool g_Earth_clear= CLEARF;	//地球	
bool g_Venus_clear= CLEARF;	//金星
bool g_Mercury_clear= CLEARF;	//水星
bool g_Sun_clear= CLEARF;	//太陽

bool g_Taurus_clear= CLEARF;	//牡牛座	
bool g_Libra_clear= CLEARF;	//天秤座
bool g_Gemini_clear= CLEARF;	//双子座
bool g_Virgo_clear= CLEARF;	//乙女座
bool g_Leo_clear= CLEARF;	//獅子座

bool g_geminiattack_check = false;
bool g_gemini_bullet_check = false;
bool g_gemini_move = false;
bool g_gemini_check = false;
bool g_tutorial_flag = false;
bool g_move_stop_flag = false;

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
bool g_Taurus = CLEARF;	//牡牛座	
bool g_Libra  = CLEARF;	//天秤座
bool g_Gemini = CLEARF;	//双子座
bool g_Virgo  = CLEARF;	//乙女座
bool g_Leo    = CLEARF;	//獅子座
bool g_key_flag = false;	//キー入力制御フラグ

//ステージ選択画面の主人公の位置（初期位置）
float g_stage_px = 50;  //ステージ選択時の位置X
float g_stage_py = 500;  //ステージ選択時の位置Y

//イニシャライズ
void CObjTitle::Init()
{
	m_up=false;
	m_down=false;
	m_start=false;
	m_end=false;

	m_key_flag =true;	//キー制御フラグ
}

//アクション
void CObjTitle::Action()
{
	 g_Earth_clear = true;	//地球	
	 g_Venus_clear = true;	//金星
	 g_Mercury_clear = true;	//水星
	 g_Sun_clear = true;	//太陽

	 g_Taurus_clear = true;	//牡牛座	
	 g_Libra_clear = true;	//天秤座
	 g_Gemini_clear = true;	//双子座
	 g_Virgo_clear = true;	//乙女座
	 g_Leo_clear = true;	//獅子座

}

//ドロー
void CObjTitle::Draw()
{
	float c[4] = { 1,1,1,1 };
	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 800.0f;
	src.m_bottom = 600.0f;

	//表示位置の設定
	dst.m_top = 0.0f;	//描画に対してスクロールの影響を加える
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;

	//描画
	Draw::Draw(1, &src, &dst, c, 0.0f);

	//上キーを押したとき
	if (Input::GetVKey(VK_UP) == true)
	{
		if (m_key_flag == true)
		{
			Audio::Start(1);
			m_key_flag = false;
			m_up = true;
			m_down = false;
		}

	}
	//下キーを押したとき
	else if (Input::GetVKey(VK_DOWN) == true)
	{
		if (m_key_flag == true)
		{
			Audio::Start(1);
			m_key_flag = false;
			m_down = true;
			m_up = false;
		}
	}
	else
		m_key_flag = true;

	//ゲーム開始
	if (m_start == true)
	{
		//シーン遷移音
		Audio::Start(2);
		Sleep(500);
		Scene::SetScene(new CSceneStageChoice());
	}
	//ゲーム終了
	if (m_end == true)
	{
		//シーン遷移音
		Audio::Start(1);
		Sleep(500);
		exit(4);
	}
	//カーソルが動く
	if (m_up == true)
	{
		Font::StrDraw(L"→ゲームスタート", 280, 300, 32, c);
		Font::StrDraw(L"ゲーム終了", 280, 340, 32, c);
		//Ｚキーで始める
		if (Input::GetVKey('Z') == true || Input::GetVKey(VK_RETURN) == true)
		{
			m_start = true;
		}

	}
	else if (m_down == true)
	{
		Font::StrDraw(L"ゲームスタート", 280, 300, 32, c);
		Font::StrDraw(L"→ゲーム終了", 280, 340, 32, c);
		//Zキーで終わる
		if (Input::GetVKey('Z') == true || Input::GetVKey(VK_RETURN) == true)
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
