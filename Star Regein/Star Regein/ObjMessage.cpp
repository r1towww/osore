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

	m_MaxStar = 5;	//星の最大の数の初期化（星座を集める場所によって変化）
}

//アクション
void CObjMessage::Action()
{
	
}

//ドロー
void CObjMessage::Draw()
{
	float c[4] = { 1.0f,1.0f,0.4f,1.0f };	//メッセージフォントカラー

	wchar_t STAR[128];	//星の数を数えるメッセージ用

	//星のカウントが増えた場合
	if (g_StarCount > m_memory)
	{
		m_time++;	//timeをプラスしている時だけメッセージを表示
		swprintf_s(STAR, L"%d個目の★を取得、残り%d個！", g_StarCount, m_MaxStar - g_StarCount);
		Font::StrDraw(STAR, 150, 240, 25, c);//HPを表示
		if (m_time == 100) {
			m_memory = g_StarCount;	//現在の星の数を代入
			m_time = 0;	//timeの初期化
		}
	}
}
