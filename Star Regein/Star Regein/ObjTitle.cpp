//使用するヘッダー
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\SceneManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjTitle.h"

//通常プレイの際は false
#define CLEARF	false


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
bool g_Boss_Spawn = CLEARF;

bool g_geminiattack_check = false;	
bool g_gemini_bullet_check = false;
bool g_gemini_move = false;
bool g_gemini_check = false;

bool g_tutorial_flag = false;	//主人公の入力制御フラグ
bool g_move_stop_flag = false;	//主人公の入力制御フラグ

int g_second = 0;		//秒
int g_minute = 0;		//分


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
float g_stage_px = 55;  //ステージ選択時の位置X
float g_stage_py = 420;  //ステージ選択時の位置Y


float g_enemy_cnt = 0;//敵の総数のカウント用変数の初期化
float g_kill_cnt = 0;	//敵殲滅用変数の初期化
bool g_no_damage = false;	//ノーダメージクリア用変数の初期化

//イニシャライズ
void CObjTitle::Init()
{
	g_stage = Space;	//ステージ値の初期化
	m_up=false;
	m_down=false;
	m_start=false;
	m_end=false;
	m_time = true;
	m_Tra = 1.0f;
	m_key_flag =true;	//キー制御フラグ
	m_Allclear = false;
	m_f = true;

}

//アクション
void CObjTitle::Action()
{

}

//ドロー
void CObjTitle::Draw()
{
	float c[4] = { 1,1,1,m_Tra };
	float t[4] = { 0,1,0,m_Tra };

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
	if(m_Allclear!=true)
		Draw::Draw(1, &src, &dst, c, 0.0f);
	else
		Draw::Draw(1, &src, &dst, t, 0.0f);

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 800.0f;
	src.m_bottom = 353.0f;

	//表示位置の設定
	dst.m_top = 50.0f;	//描画に対してスクロールの影響を加える
	dst.m_left = 50.0f;
	dst.m_right =750.0f;
	dst.m_bottom = 350.0f;

	Draw::Draw(2, &src, &dst, c, 0.0f);

	//タイトルでスペース+Zキーでチートオン
	if (Input::GetVKey(VK_SPACE) == true && Input::GetVKey('Z') == true)
	{
		if (m_f == false)
		{
			if (m_Allclear == true)
				m_Allclear = false;
			else
				m_Allclear = true;

			m_f = true;
		}
	}
	else
	{
		m_f = false;
	}

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

	//チートフラグオン
	if (m_Allclear == true)
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
		g_Boss_Spawn = true;
		g_Taurus = true;	//牡牛座	
		g_Libra = true;	//天秤座
		g_Gemini = true;	//双子座
		g_Virgo = true;	//乙女座
		g_Leo = true;	//獅子座
	}
	else
	{
		g_Earth_clear = false;	//地球	
		g_Venus_clear = false;	//金星
		g_Mercury_clear = false;	//水星
		g_Sun_clear = false;	//太陽

		g_Taurus_clear = false;	//牡牛座	
		g_Libra_clear = false;	//天秤座
		g_Gemini_clear = false;	//双子座
		g_Virgo_clear = false;	//乙女座
		g_Leo_clear = false;	//獅子座
		g_Boss_Spawn = false;
		g_Taurus = false;	//牡牛座	
		g_Libra = false;	//天秤座
		g_Gemini = false;	//双子座
		g_Virgo = false;	//乙女座
		g_Leo = false;	//獅子座

	}

	//ゲーム開始
	if (m_start == true)
	{
		if (m_time == true)
		{
			Audio::Start(2);
			m_time = false;
		}
		m_Tra -= 0.03f;
		if (m_Tra <= 0.0f)
		{
			Scene::SetScene(new CSceneStageChoice());
		}
	}
	//ゲーム終了
	if (m_end == true)
	{
		if (m_time == true)
		{
			Audio::Start(2);
			m_time = false;
		}
		m_Tra -= 0.03f;
		if (m_Tra <= 0.0f)
		{
			exit(4);
		}
	}
	//カーソルが動く
	if (m_up == true)
	{
		Font::StrDraw(L"→ゲームスタート", 300, 380, 32, c);
		Font::StrDraw(L"ゲーム終了", 300, 420, 32, c);
		//Ｚキーで始める
		if (Input::GetVKey('Z') == true || Input::GetVKey(VK_RETURN) == true)
		{
			m_start = true;
		}

	}
	else if (m_down == true)
	{
		Font::StrDraw(L"ゲームスタート", 300, 380, 32, c);
		Font::StrDraw(L"→ゲーム終了", 300, 420, 32, c);
		//Zキーで終わる
		if (Input::GetVKey('Z') == true || Input::GetVKey(VK_RETURN) == true)
		{
			m_end = true;
		}


	}
	//始めはこの状態
	else
	{
		Font::StrDraw(L"ゲームスタート", 300, 380, 32, c);
		Font::StrDraw(L"ゲーム終了", 300, 420, 32, c);
	}


}
