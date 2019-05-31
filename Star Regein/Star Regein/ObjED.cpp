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
	m_ani_time = 0;
	m_ani_frame = 0;
	m_ani_max_time = 3;		//アニメーション間隔幅
	m_key = 0;
	//キーフラグの初期化
	m_key_f = false;
	flag = false;
	m_f = true;		//オブジェクト作成用フラグ

	//２週目系統
	g_End_flag = false;
	g_Voice_flag = false;
	g_count = 0;
	g_last_key_f = false;	//２週目の主人公が動かす用

}

//アクション
void CObjED::Action()
{

	float p[4] = { 1.0f,0.0f,0.0f,1.0f };
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	//フォント描画-------------------------------------------
	if (m_key == 0)
	{
		Font::StrDraw(L"END GAME", GAME_CLEAR_X - 20, GAME_CLEAR_Y + 110, GAME_CLEAR_FONT_SIZE + 70, p);
	}
	if (m_key == 1)
	{
		Font::StrDraw(L"ゲーム名", GAME_CLEAR_X - 10, GAME_CLEAR_Y - 10, GAME_CLEAR_FONT_SIZE + 60, c);
		Font::StrDraw(L"STAR REGEIN", GAME_CLEAR_X - 75, GAME_CLEAR_Y + 200, GAME_CLEAR_FONT_SIZE + 60, c);
	}
	if (m_key == 2)
	{
		Font::StrDraw(L"音楽提供", GAME_CLEAR_X -10, GAME_CLEAR_Y -10, GAME_CLEAR_FONT_SIZE + 60, c);
		Font::StrDraw(L"魔王魂様", GAME_CLEAR_X -10, GAME_CLEAR_Y + 200, GAME_CLEAR_FONT_SIZE + 60, c);
	}
	if (m_key == 3)
	{
		Font::StrDraw(L"プレイして頂き", GAME_CLEAR_X - 45, GAME_CLEAR_Y +70, GAME_CLEAR_FONT_SIZE + 30, c);
		Font::StrDraw(L"ありがとうございました", GAME_CLEAR_X - 160, GAME_CLEAR_Y + 180, GAME_CLEAR_FONT_SIZE + 30, c);
	}
	//-----------------------------------------------------------

	//Enterが押されたらフラグオン
	if (Input::GetVKey('Z') && m_key_f == false ||Input::GetVKey(VK_RETURN) == true && m_key_f == false)
	{
		m_key_f = true;
	}
	//---------------------------

	//アニメーション表示----
	if (m_key_f == true && flag==false)
	{
		m_ani_time += 1;

		if (m_ani_time > m_ani_max_time)
		{
			m_ani_frame += 1;
			m_ani_time = 0;
		}
		if (m_ani_frame == 10)
		{
			flag = true;
			m_key += 1;
		}
	}
	if (flag == true)
	{
		m_ani_time += 1;

		if (m_ani_time > m_ani_max_time)
		{
			m_ani_frame -= 1;
			m_ani_time = 0;
		}
		if (m_ani_frame == 0)
		{
			m_key_f = false;
			flag = false;
		}
	}
	//------------------------

	if (m_key == 4 && m_f == true)
	{
		//オブジェクト作成
		CObjStageClear* objs = new CObjStageClear();	//実績の表示
		Objs::InsertObj(objs, OBJ_STAGECLEAR, 130);
		m_f = false;
	}

}

//ドロー
void CObjED::Draw()
{
	float bc[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;		//描画元切り取り位置
	RECT_F dst;		//描画先表示位置

					//背景切り取り
	src.m_top = 0.0f;
	src.m_left = 0.0f + (800.0f * m_ani_frame);
	src.m_right = 800.0f + (800.0f * m_ani_frame);
	src.m_bottom = 600.0f;

	//描画
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;
	Draw::Draw(1, &src, &dst, bc, 0.0f);
}
