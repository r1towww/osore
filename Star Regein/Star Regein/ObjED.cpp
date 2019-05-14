//使用するヘッダー
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\SceneManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjTitle.h"


//使用するネームスペース
using namespace GameL;

							//イニシャライズ
void CObjED::Init()
{
	m_y = 0.0;
}

//アクション
void CObjED::Action()
{
	float p[4] = { 1.0f,1.0f,1.0f,1.0f };

	m_y--;

	//エンターキーで早送り機能
	if (Input::GetVKey(VK_RETURN) == true)
	{
		m_y -= 10;
	}

	else
	{
		m_y -= 0.8f;
	}
	Font::StrDraw(L"END GAME"                  , GAME_CLEAR_X+25, GAME_CLEAR_Y + m_y   , GAME_CLEAR_FONT_SIZE+30, p);
	Font::StrDraw(L"ゲーム名 STAR REGEIN"      , GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 100, GAME_CLEAR_FONT_SIZE, p);
	Font::StrDraw(L"ゲーム作成者"              , GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 150, GAME_CLEAR_FONT_SIZE, p);
	Font::StrDraw(L"リーダー     菅原 圭太"    , GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 200, GAME_CLEAR_FONT_SIZE, p);
	Font::StrDraw(L"プランナー   清水  蓮"     , GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 250, GAME_CLEAR_FONT_SIZE, p);
	Font::StrDraw(L"プログラマー 田中 陸斗"    , GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 300, GAME_CLEAR_FONT_SIZE, p);
	Font::StrDraw(L"プログラマー 木村 唯人"    , GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 350, GAME_CLEAR_FONT_SIZE, p);
	Font::StrDraw(L"プログラマー 保地谷 広奈"  , GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 400, GAME_CLEAR_FONT_SIZE, p);
	if (m_y <= -500)
	{

	}

}

//ドロー
void CObjED::Draw()
{

}
