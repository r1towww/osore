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
	if (Input::GetVKey('Z') == true && g_tutorial_next_flag == true || Input::GetVKey(VK_RETURN) == true && g_tutorial_next_flag == true)
	{

		if (m_f == false)
		{
			//チュートリアルフラグがオンのとき
			if (g_tutorial_flag == true || g_Voice_flag == true)
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
			if (g_Leo_clear == true)
			{
				;
			}
			else
			{
				Font::StrDraw(L"Xキーでチュートリアルをスキップ", 300, 350, 32, c);
			}
		}

		if (g_Voice_flag == true)
		{
			;
		}
		else if (g_Boss_Spawn == true)
		{
			Font::StrDraw(L"Xキーで天の声を無視する", 350, 370, 32, c);
		}
	
	}

	
	//チュートリアルフラグがオフで終了する
	if (g_tutorial_flag == false)
	{
		m_text = 0;
	}
	//地球
	else if (g_tutorial_flag == true)
	{
		if (g_stage == EarthStar || g_stage == Space)
		{
			//ラスボス撃破後
			if (g_Voice_flag == true)
			{
				if (m_text == 0)
				{
					Font::StrDraw(L"すべての星座の力を集め、", TEXT_X, TEXT_Y1, TEXTSIZE, c);
					Font::StrDraw(L"敵を倒したことで地球に平和が訪れました。", TEXT_X, TEXT_Y2, TEXTSIZE, c);
				}
				else if (m_text == 1)
				{
					Font::StrDraw(L"これでもう二度と地球の平和が", TEXT_X, TEXT_Y1, TEXTSIZE, c);
					Font::StrDraw(L"脅かされることはないでしょう。", TEXT_X, TEXT_Y2, TEXTSIZE, c);
				}
				else if (m_text == 2)
				{
					Font::StrDraw(L"おしまい", TEXT_X, TEXT_Y1, TEXTSIZE, c);
					g_End_flag = true;
					
				}
			
			}
			//ラスボス出現時（地球）
			else if (g_stage == EarthStar && g_Boss_Spawn == true)
			{
				if (m_text == 0)
				{
					Font::StrDraw(L"本部より通達です！", TEXT_X, TEXT_Y1, TEXTSIZE, c);
					Font::StrDraw(L"地球に侵攻してきたのは蛇使い座と思われます！", TEXT_X, TEXT_Y2, TEXTSIZE, c);
				}
				else if (m_text == 1)
				{
					Font::StrDraw(L"今まで手に入れた星座たちを駆使して", TEXT_X, TEXT_Y1, TEXTSIZE, c);
					Font::StrDraw(L"敵を討伐して下さい！！", TEXT_X, TEXT_Y2, TEXTSIZE, c);

				}
				else if (m_text == 2)
				{
					Font::StrDraw(L"光っている星の場所に行くと", TEXT_X, TEXT_Y1, TEXTSIZE, c);
					Font::StrDraw(L"支援班が体力を回復します！", TEXT_X, TEXT_Y2, TEXTSIZE, c);

				}
				else if (m_text == 3)
				{
					Font::StrDraw(L"ただし、ずっと同じ星にいると", TEXT_X, TEXT_Y1, TEXTSIZE, c);
					Font::StrDraw(L"敵が感知してワープしてくる可能性が", TEXT_X, TEXT_Y2, TEXTSIZE, c);
					Font::StrDraw(L"ありますのでご注意下さい！", TEXT_X, TEXT_Y3, TEXTSIZE, c);

				}
				else if (m_text == 4)
				{
					Font::StrDraw(L"地球の命運はあなたに掛かっています！", TEXT_X, TEXT_Y1, TEXTSIZE, c);
					Font::StrDraw(L"ご武運を！", TEXT_X, TEXT_Y2, TEXTSIZE, c);
					
				}
			}
			else if (g_Sun_clear == true)//ラスボス出現時（ステージ選択画面）
			{
				if (m_text == 0)
				{
					Font::StrDraw(L"緊急連絡！緊急連絡！", TEXT_X, TEXT_Y1, TEXTSIZE, c);
					Font::StrDraw(L"地球に謎の生命体出現！", TEXT_X, TEXT_Y2, TEXTSIZE, c);
				}
				else if (m_text == 1)
				{
					Font::StrDraw(L"即座に地球へ帰還して下さい！", TEXT_X, TEXT_Y1, TEXTSIZE, c);
					Font::StrDraw(L"繰り返します……", TEXT_X, TEXT_Y2, TEXTSIZE, c);
				}
			}
			else//チュートリアル
			{
				if (m_text == 0)
				{
					Font::StrDraw(L"Star Reginへようこそ！！", TEXT_X, TEXT_Y1, TEXTSIZE, c);
					Font::StrDraw(L"ここ、地球ステージでは基本的な操作と", TEXT_X, TEXT_Y2, TEXTSIZE, c);
					Font::StrDraw(L"ゲームのクリア条件をお伝えします", TEXT_X, TEXT_Y3, TEXTSIZE, c);
				}
				else if (m_text == 1)
				{
					Font::StrDraw(L"まずは移動してみましょう", TEXT_X, TEXT_Y1, TEXTSIZE, c);
					Font::StrDraw(L"方向キーで移動することができます", TEXT_X, TEXT_Y2, TEXTSIZE, c);

				}
				else if (m_text == 2)
				{
					Font::StrDraw(L"このゲームのクリア条件は", TEXT_X, TEXT_Y1, TEXTSIZE, c);
					Font::StrDraw(L"各ステージにある星を集めることです", TEXT_X, TEXT_Y2, TEXTSIZE, c);

				}
				else if (m_text == 3)
				{
					Font::StrDraw(L"星を集めきると星座が完成し、", TEXT_X, TEXT_Y1, TEXTSIZE, c);
					Font::StrDraw(L"その星座のスキルを使うことができます", TEXT_X, TEXT_Y2, TEXTSIZE, c);

				}
				else if (m_text == 4)
				{
					Font::StrDraw(L"スキルの切り替えはCキーで行えます", TEXT_X, TEXT_Y1, TEXTSIZE, c);
					Font::StrDraw(L"各スキルの説明はヘルプで確認して下さい", TEXT_X, TEXT_Y2, TEXTSIZE, c);
				}
				else if (m_text == 5)
				{
					Font::StrDraw(L"それでは星を集めてみましょう", TEXT_X, TEXT_Y1, TEXTSIZE, c);
				}
			}
		
		}

	}

}


