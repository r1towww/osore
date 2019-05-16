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
	m_time_mes = 0;	//タイムカウント用変数の初期化
	m_f = false;	//タイムカウント用フラグの初期化
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
	//スキルアイテムオブジェクトの情報を持ってくる
	CObjSkillItem* objskillitem = (CObjSkillItem*)Objs::GetObj(OBJ_SKILL_ITEM);
	//ステージクリアの情報を持ってくる
	CObjStageClear* objclear = (CObjStageClear*)Objs::GetObj(OBJ_STAGECLEAR);

	if (g_tutorial_flag == true) {
		;			//チュートリアルメッセージが表示されている際、タイムをカウントしない
	}
	else if(objskillitem != nullptr || objclear != nullptr){	//スキルオブジェクトが作成された際、またはクリアオブジェクトが作成されている際
		m_f = true;		//フラグをオンにする
	}
	else if(m_f == false){	//フラグがオフの際、タイムをカウント
		m_time_mes++;
	}
}

//ドロー
void CObjMessage::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };	//メッセージフォントカラー
	float ca[4] = { 1.0f,1.0f,1.0f,0.7f };	//メッセージフォントカラー

	float sc[4] = { 1.0f,1.0f,0.4f,1.0f };
	float b[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	wchar_t STARMES[128];	//星の数を数えるメッセージ用
	wchar_t STAR[128];	//星の数を常に表示する
	wchar_t TIME[128];	//タイムの描画

	//m_time_mesから描分を求める
	m_second = (m_time_mes / 60) % 60;	//秒
	m_minute = (m_time_mes / 60) / 60;	//分

	//分：秒の値を文字列化
	if (m_second<10)
		swprintf_s(TIME, L"%d分0%d秒", m_minute, m_second);//秒の1桁目に0を用意
	else
		swprintf_s(TIME, L"%d分%d秒", m_minute, m_second);

	Font::StrDraw(TIME, 10, 250, 20, c);	//タイムの表示

	swprintf_s(STAR, L"%d/%d", g_StarCount, m_MaxStar);
	Font::StrDraw(STAR, 400, 20, 25, sc);//メッセージを表示

	Font::StrDraw(L"Q:メニュー", 465, 12, 21, c);	//メニュー
	Font::StrDraw(L"H:ヘルプ", 465, 33, 21, c);	//ヘルプ
	Font::StrDraw(L"M:マップ切り替え", 635, 220, 20, ca);	//マップ拡大キー

	//金星のどちらかのスキルがオンの際描画する
	if (g_Taurus == true || g_Libra == true) {
		Font::StrDraw(L"スキル切り替え", 580, 400, 20, ca);	//スキル切り替えキー
		Font::StrDraw(L"Cで左へ、Vで右へ", 570, 420, 21, ca);	//スキル切り替えキー
	}
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
		//最後の星を取得した際
		if (m_MaxStar == g_StarCount) {
			Font::StrDraw(L"最後の星を取得！", 150, 240, 25, sc);	//別のメッセージを作成
		}
		else
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


}
