//使用するヘッダー
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\SceneManager.h"
#include "GameL\Audio.h"
#include "GameHead.h"
#include "ObjTextBox.h"
#include "ObjTutorial.h"

//----------------------------------
//使用するネームスペース
using namespace GameL;



//イニシャライズ
void CObjTextBox::Init()
{
	m_key_time = 0;
	m_f = true;
	m_text = 0;
}

//アクション
void CObjTextBox::Action()
{
	//惑星が選択され、戦闘画面への移行の際
	if (g_stage == EarthStar)
	{

		//画像が表示された際の、キー入力タイム処理
		if (m_key_time >= 300)
			m_key_time = 300;	//タイムが50になった際、50で止める
		else
			m_key_time++;	//キー入力タイムを増やす

	}
	else
	{
		m_key_time = 0;	//それ以外の場合、キー入力タイムを0にする
	}
	//キータイムが300を超えるとZ可能
		//Zキー入力
		if (Input::GetVKey('Z') == true)
		{
			
			if (m_f == false)
			{
				if (g_tutorial_flag == true)
				{
					Audio::Start(1);
					m_text++;//テキストを進める
					m_key_time = 0;//キータイムをリセットする
					m_f = true;
				}
			}
			else
			{
				m_f = true;
			}
		}
		else
		{
			m_f = false;
		}

}

//ドロー
void CObjTextBox::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	if (g_tutorial_flag == true)
	{
		Font::StrDraw(L"Zキーで次へ", TEXT_ZX, TEXT_ZY, TEXTSIZE_Z, c);
		Font::StrDraw(L"Xキーでチュートリアルをスキップ", 300, 350, 32, c);

	}
	//チュートリアルフラグがオフで終了する
	if (g_tutorial_flag == false)
	{
		;
	}
	//地球
	else if (g_stage == EarthStar)
	{
		if (m_text == 0)
		{
			Font::StrDraw(L"Star Reginへようこそ！！", TEXT_X, TEXT_Y1, TEXTSIZE, c);
			Font::StrDraw(L"ここ、地球ステージでは基本的な操作と", TEXT_X, TEXT_Y2, TEXTSIZE, c);
			Font::StrDraw(L"ゲームのクリア条件をお伝えします！", TEXT_X, TEXT_Y3, TEXTSIZE, c);
		}
		else if (m_text == 1)
		{
			Font::StrDraw(L"まずは移動してみましょう", TEXT_X, TEXT_Y1, TEXTSIZE, c);
			Font::StrDraw(L"方向キーで移動することができます", TEXT_X, TEXT_Y2, TEXTSIZE, c);

		}
		else if (m_text == 2)
		{
			Font::StrDraw(L"次にこのゲームのクリア条件は", TEXT_X, TEXT_Y1, TEXTSIZE, c);
			Font::StrDraw(L"各ステージにある星を集めることです", TEXT_X, TEXT_Y2, TEXTSIZE, c);

		}
		else if (m_text == 3)
		{
			Font::StrDraw(L"星を集めきると星座が完成し、", TEXT_X, TEXT_Y1, TEXTSIZE, c);
			Font::StrDraw(L"新しくスキルを使うことができます", TEXT_X, TEXT_Y2, TEXTSIZE, c);

		}
		else if (m_text == 4)
		{
			Font::StrDraw(L"それでは星を集めてみましょう", TEXT_X, TEXT_Y1, TEXTSIZE, c);

		}
	}
	//おうし座
	else if (g_stage == VenusTaurus)
	{
		if (m_text == 0)
		{
			Font::StrDraw(L"ここ金星ではおうし座とてんびん座の", TEXT_X, TEXT_Y1, TEXTSIZE, c);
			Font::StrDraw(L"スキルを取得することができます", TEXT_X, TEXT_Y2, TEXTSIZE, c);
		}
		else if (m_text == 1)
		{
			Font::StrDraw(L"ここ、おうし座で取得できるスキルは", TEXT_X, TEXT_Y1, TEXTSIZE, c);
			Font::StrDraw(L"ダッシュスキルを取得することができます", TEXT_X, TEXT_Y2, TEXTSIZE, c);

		}
		else if (m_text == 2)
		{
			Font::StrDraw(L"ここで獲得すべき星は全部で１８個もあります", TEXT_X, TEXT_Y1, TEXTSIZE, c);
			Font::StrDraw(L"しかも、この金星から敵も出現します", TEXT_X, TEXT_Y2, TEXTSIZE, c);

		}
		else if (m_text == 3)
		{
			Font::StrDraw(L"Zキーで攻撃することが可能です", TEXT_X, TEXT_Y1, TEXTSIZE, c);
			Font::StrDraw(L"自分のHPが０になってしまうと", TEXT_X, TEXT_Y2, TEXTSIZE, c);
			Font::StrDraw(L"GAMEOVERになってしまいます", TEXT_X, TEXT_Y3, TEXTSIZE, c);

		}
		else if (m_text == 4)
		{
			Font::StrDraw(L"敵を見つけたら倒しに行くのもいいですが", TEXT_X, TEXT_Y1, TEXTSIZE, c);
			Font::StrDraw(L"星をすべて獲得するとクリアなので", TEXT_X, TEXT_Y2, TEXTSIZE, c);
			Font::StrDraw(L"星獲得を優先的に行動しましょう！", TEXT_X, TEXT_Y3, TEXTSIZE, c);

		}
		else if (m_text == 5)
		{
			Font::StrDraw(L"もし、先にてんびん座のヒールスキルを", TEXT_X, TEXT_Y1, TEXTSIZE, c);
			Font::StrDraw(L"獲得しているなら、", TEXT_X, TEXT_Y2, TEXTSIZE, c);
			Font::StrDraw(L"シフトキーで発動できます！", TEXT_X, TEXT_Y3, TEXTSIZE, c);
		}
		else if (m_text == 6)
		{
			Font::StrDraw(L"スキルを使うにはMP（青いゲージ）が必要です", TEXT_X, TEXT_Y1, TEXTSIZE, c);
			Font::StrDraw(L"MPは時間経過で回復していくので、", TEXT_X, TEXT_Y2, TEXTSIZE, c);
			Font::StrDraw(L"どんどん使っていきましょう！", TEXT_X, TEXT_Y3, TEXTSIZE, c);
		}
	}
	//てんびん座
	else if (g_stage == VenusLibra)
	{
		if (m_text == 0)
		{
			Font::StrDraw(L"ここ金星ではおうし座とてんびん座の", TEXT_X, TEXT_Y1, TEXTSIZE, c);
			Font::StrDraw(L"スキルを取得することができます", TEXT_X, TEXT_Y2, TEXTSIZE, c);

		}
		else if (m_text == 1)
		{
			Font::StrDraw(L"ここ、てんびん座で取得できるスキルは", TEXT_X, TEXT_Y1, TEXTSIZE, c);
			Font::StrDraw(L"ヒール（回復）スキルを取得することができます", TEXT_X, TEXT_Y2, TEXTSIZE, c);

		}
		else if (m_text == 2)
		{
			Font::StrDraw(L"ここで獲得すべき星は全部で６個です", TEXT_X, TEXT_Y1, TEXTSIZE, c);
			Font::StrDraw(L"この金星から敵も出現します", TEXT_X, TEXT_Y2, TEXTSIZE, c);

		}
		else if (m_text == 3)
		{
			Font::StrDraw(L"Zキーで攻撃することが可能です", TEXT_X, TEXT_Y1, TEXTSIZE, c);
			Font::StrDraw(L"自分のHPが０になってしまうと", TEXT_X, TEXT_Y2, TEXTSIZE, c);
			Font::StrDraw(L"GAMEOVERになってしまいます", TEXT_X, TEXT_Y3, TEXTSIZE, c);

		}
		else if (m_text == 4)
		{
			Font::StrDraw(L"敵を見つけたら倒しに行くのもいいですが", TEXT_X, TEXT_Y1, TEXTSIZE, c);
			Font::StrDraw(L"星をすべて獲得するとクリアなので", TEXT_X, TEXT_Y2, TEXTSIZE, c);
			Font::StrDraw(L"星獲得を優先的に行動しましょう！", TEXT_X, TEXT_Y3, TEXTSIZE, c);

		}
		else if (m_text == 5)
		{
			Font::StrDraw(L"もし、先におうし座のダッシュスキルを", TEXT_X, TEXT_Y1, TEXTSIZE, c);
			Font::StrDraw(L"獲得しているなら、", TEXT_X, TEXT_Y2, TEXTSIZE, c);
			Font::StrDraw(L"シフトキーで発動できます！", TEXT_X, TEXT_Y3, TEXTSIZE, c);


		}
		else if (m_text == 6)
		{
			Font::StrDraw(L"スキルを使うにはMP（青いゲージ）が必要です", TEXT_X, TEXT_Y1, TEXTSIZE, c);
			Font::StrDraw(L"MPは時間経過で回復していくので、", TEXT_X, TEXT_Y2, TEXTSIZE, c);
			Font::StrDraw(L"どんどん使っていきましょう！", TEXT_X, TEXT_Y3, TEXTSIZE, c);

		}
	}


}
