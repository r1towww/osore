//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"
#include "GameHead.h"

#include "ObjMessage.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjMessage::Init()
{
	m_memory = 0;	//星の数を計る変数の初期化
	m_time = 0;		//メッセージ時間用の変数の初期化
	//星の最大の数の初期化（星座を集める場所によって変化）
	if (g_stage == EarthStar)
		m_MaxStar = EARTHMAXSTAR;	//地球
	else if (g_stage == VenusTaurus)
		m_MaxStar = TAURUSMAXSTAR;	//金星（牡牛座）
	else if (g_stage == VenusLibra)
		m_MaxStar = LIBRAMAXSTAR;	//金星（天秤座）
	else if (g_stage == MercuryGemini)
		m_MaxStar = GEMINIMAXSTAR;	//水星（双子座）
	else if (g_stage == MercuryVirgo)
		m_MaxStar = VIRGOMAXSTAR;	//水星（乙女座）
	else if (g_stage == SunLeo)
		m_MaxStar = LEOMAXSTAR;		//太陽（獅子座）

}

//アクション
void CObjMessage::Action()
{
	
}

//ドロー
void CObjMessage::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };	//メッセージフォントカラー

	float sc[4] = { 1.0f,1.0f,0.4f,1.0f };
	float b[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	wchar_t STARMES[128];	//星の数を数えるメッセージ用
	wchar_t STAR[128];	//星の数を常に表示する

	swprintf_s(STAR, L"%d/%d", g_StarCount, m_MaxStar);
	Font::StrDraw(STAR, 400, 20, 25, sc);//メッセージを表示

	Font::StrDraw(L"Q:メニュー", 465, 12, 21, c);	//HP
	Font::StrDraw(L"H:ヘルプ", 465, 33, 21, c);	//MP


	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 232.0f;
	src.m_bottom = 203.0f;

	//表示位置の設定
	dst.m_top = 16.0f;
	dst.m_left = 365.0f;
	dst.m_right = 395.0f;
	dst.m_bottom = 46.0f;

		//描画
		Draw::Draw(6, &src, &dst, c, 0.0f);
	
	//星のカウントが増えた場合
	if (g_StarCount > m_memory)
	{
		m_time++;	//timeをプラスしている時だけメッセージを表示
		swprintf_s(STARMES, L"%d個目の★を取得、残り%d個！", g_StarCount, m_MaxStar - g_StarCount);
		Font::StrDraw(STARMES, 150, 240, 25, sc);//メッセージを表示
		if (m_time == 100) {
			m_memory = g_StarCount;	//現在の星の数を代入
			m_time = 0;	//timeの初期化
		}
	}


}
