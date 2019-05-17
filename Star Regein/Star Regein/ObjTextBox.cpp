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

bool g_tutorial_next_flag = false;


//イニシャライズ
void CObjTextBox::Init()
{
	m_f = true;
	m_text = 0;
}

//アクション
void CObjTextBox::Action()
{
	//キータイムを超えるとZ可能
	//Zキー入力
	if (Input::GetVKey('Z') == true && g_tutorial_next_flag == true ||Input::GetVKey(VK_RETURN)==true&& g_tutorial_next_flag ==true)
	{
			
		if (m_f == false)
		{
			//チュートリアルフラグがオンのとき
			if (g_tutorial_flag == true)
			{
				Audio::Start(1);
				g_tutorial_next_flag = false;

				m_text++;//テキストを進める
				m_f = true;
			}
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
		if (g_stage == EarthStar)
		{
			Font::StrDraw(L"Xキーでチュートリアルをスキップ", 300, 350, 32, c);
		}
		else
			Font::StrDraw(L"Xキーで天の声を無視する", 350, 370, 32, c);

	}
	//チュートリアルフラグがオフで終了する
	if (g_tutorial_flag == false)
	{
		;
	}
	//地球
	else if (g_tutorial_flag == true)
	{
		if (g_stage == EarthStar)
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
				Font::StrDraw(L"もし、先にてんびん座のスキルを", TEXT_X, TEXT_Y1, TEXTSIZE, c);
				Font::StrDraw(L"獲得しているなら、天秤座のスキルを", TEXT_X, TEXT_Y2, TEXTSIZE, c);
				Font::StrDraw(L"セットすることで発動できます！", TEXT_X, TEXT_Y3, TEXTSIZE, c);
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
				Font::StrDraw(L"HPに応じて攻撃力の変わるパッシブスキル", TEXT_X, TEXT_Y2, TEXTSIZE, c);
				Font::StrDraw(L"を取得することができます", TEXT_X, TEXT_Y3, TEXTSIZE, c);

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
				Font::StrDraw(L"天秤座の敵は温厚で", TEXT_X, TEXT_Y1, TEXTSIZE, c);
				Font::StrDraw(L"基本的に戦う意思はないので、", TEXT_X, TEXT_Y2, TEXTSIZE, c);
				Font::StrDraw(L"平和にいきましょう…！", TEXT_X, TEXT_Y3, TEXTSIZE, c);


			}
			else if (m_text == 6)
			{
				Font::StrDraw(L"もし、攻撃してしまったら・・・", TEXT_X, TEXT_Y1, TEXTSIZE, c);
				Font::StrDraw(L"その時は頑張って生きてください・・・", TEXT_X, TEXT_Y2, TEXTSIZE, c);
			}
		}
		//ふたご座
		else if (g_stage == MercuryGemini)
		{
			if (m_text == 0)
			{
				Font::StrDraw(L"水星へようこそ！", TEXT_X, TEXT_Y1, TEXTSIZE, c);
				Font::StrDraw(L"ここ水星では双子座とおとめ座の", TEXT_X, TEXT_Y2, TEXTSIZE, c);
				Font::StrDraw(L"スキルを取得することができます", TEXT_X, TEXT_Y3, TEXTSIZE, c);

			}
			else if (m_text == 1)
			{
				Font::StrDraw(L"ここ、双子座で取得できるスキルは", TEXT_X, TEXT_Y1, TEXTSIZE, c);
				Font::StrDraw(L"サブ機出現スキルを取得することができます", TEXT_X, TEXT_Y2, TEXTSIZE, c);
				Font::StrDraw(L"（取得後Xキーで発動）", TEXT_X, TEXT_Y3, TEXTSIZE, c);

			}
			else if (m_text == 2)
			{
				Font::StrDraw(L"ここで獲得すべき星は全部で14個です", TEXT_X, TEXT_Y1, TEXTSIZE, c);
				Font::StrDraw(L"早速、集めていきましょう！", TEXT_X, TEXT_Y2, TEXTSIZE, c);

			}
		}
		//おとめ座
		else if (g_stage == MercuryVirgo)
		{
			if (m_text == 0)
			{
				Font::StrDraw(L"水星へようこそ！", TEXT_X, TEXT_Y1, TEXTSIZE, c);
				Font::StrDraw(L"ここ水星では双子座とおとめ座の", TEXT_X, TEXT_Y2, TEXTSIZE, c);
				Font::StrDraw(L"スキルを取得することができます", TEXT_X, TEXT_Y3, TEXTSIZE, c);

			}
			else if (m_text == 1)
			{
				Font::StrDraw(L"ここ、おとめ座で取得できるスキルは", TEXT_X, TEXT_Y1, TEXTSIZE, c);
				Font::StrDraw(L"HP吸収遠距離攻撃スキルを取得することができます", TEXT_X, TEXT_Y2, TEXTSIZE, c);
				Font::StrDraw(L"（取得後Xキーで発動）", TEXT_X, TEXT_Y3, TEXTSIZE, c);

			}
			else if (m_text == 2)
			{
				Font::StrDraw(L"ここで獲得すべき星は全部で15個です", TEXT_X, TEXT_Y1, TEXTSIZE, c);
				Font::StrDraw(L"早速、集めていきましょう！", TEXT_X, TEXT_Y2, TEXTSIZE, c);

			}

		}
		//太陽
		else if (g_stage == SunLeo)
		{
			if (m_text == 0)
			{
				Font::StrDraw(L"太陽へようこそ！", TEXT_X, TEXT_Y1, TEXTSIZE, c);
				Font::StrDraw(L"ここ太陽では獅子座の", TEXT_X, TEXT_Y2, TEXTSIZE, c);
				Font::StrDraw(L"スキルを取得することができます", TEXT_X, TEXT_Y3, TEXTSIZE, c);

			}
			else if (m_text == 1)
			{
				Font::StrDraw(L"獅子座で取得できるスキルは", TEXT_X, TEXT_Y1, TEXTSIZE, c);
				Font::StrDraw(L"周囲の敵をマヒさせるスキルを", TEXT_X, TEXT_Y2, TEXTSIZE, c);
				Font::StrDraw(L"取得することができます", TEXT_X, TEXT_Y3, TEXTSIZE, c);

			}
			else if (m_text == 2)
			{
				Font::StrDraw(L"ここで獲得すべき星は全部で15個です", TEXT_X, TEXT_Y1, TEXTSIZE, c);
				Font::StrDraw(L"ここにいる敵は、やけどを付与する", TEXT_X, TEXT_Y2, TEXTSIZE, c);
				Font::StrDraw(L"攻撃をしてきます！", TEXT_X, TEXT_Y3, TEXTSIZE, c);

			}
			else if (m_text == 3)
			{
				Font::StrDraw(L"やけど状態では一定時間", TEXT_X, TEXT_Y1, TEXTSIZE, c);
				Font::StrDraw(L"ダメージを受けてしまいます！", TEXT_X, TEXT_Y2, TEXTSIZE, c);

			}
			else if (m_text == 4)
			{
				Font::StrDraw(L"やけどは無効化できないので", TEXT_X, TEXT_Y1, TEXTSIZE, c);
				Font::StrDraw(L"スキルを駆使して", TEXT_X, TEXT_Y2, TEXTSIZE, c);
				Font::StrDraw(L"攻略していきましょう！", TEXT_X, TEXT_Y3, TEXTSIZE, c);

			}

		}
		
	}

}


