//使用するヘッダー
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\SceneManager.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "ObjTutorial.h"


//----------------------------------
//使用するネームスペース
using namespace GameL;

bool g_tutorial__flag=false;

//イニシャライズ
void CObjTutorial::Init()
{
	g_tutorial_flag = true;

	//キー入力用タイムの初期化
	m_keytime = 0.f;

	m_page = 0;		//渡されたページ数
	m_sec = 0;		//秒数カウント
	m_blink = 0;
	m_line = 0;		//行数カウント
	m_f = true;
	m_next_f = false;
}

//アクション
void CObjTutorial::Action()
{
	
	if (m_page == m_p) 
	{//渡されたページ数と現在のページ数が同じになったら
		g_tutorial_flag = false;
	}

	//Xキーを押してスキップ（移動キーを入力できなくしている）
	if (Input::GetVKey('X') == true && Input::GetVKey(VK_UP) == false && Input::GetVKey(VK_DOWN) == false 
									&& Input::GetVKey(VK_LEFT) == false && Input::GetVKey(VK_RIGHT) == false )
	{
		g_tutorial_flag = false;
	}
	
}



//ドロー
void CObjTutorial::Draw()
{
		//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置
	if (g_tutorial_flag == false)
	{
		return;
	}
	//チュートリアルフラグが立った時チュートリアルを開始する
	else if (g_tutorial_flag == true)
	{
		//テキストボックス表示
		if (m_tipe == 0)
		{

			//チュートリアル専用テキストボックス------------------------------------
			//切り取り位置の設定
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 822.0f;
			src.m_bottom = 218.0f;

			//表示位置の設定
			dst.m_top = 422.0f;
			dst.m_left = 10.0f;
			dst.m_right = 785.0f;
			dst.m_bottom = 600.0f;
			//表示
			Draw::Draw(40, &src, &dst, c, 0.0f);


		}
		//----------------------------------------
		else if (m_tipe == 1)
		{//tipe1は、コメントを隠す画像表示
			//チュートリアル専用miniボックス------------------------------------
			//切り取り位置の設定
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 287.0f;
			src.m_bottom = 97.0f;

			//表示位置の設定
			dst.m_top = 343.0f;
			dst.m_left = -30.0f;
			dst.m_right = 257.0f;
			dst.m_bottom = 440.0f;
			Draw::Draw(42, &src, &dst, c, 0.0f);

			if (m_sec <= 715)
			{//715(コメントの幅)まで時間経過
				m_sec += 20;	   //文字の表示スピード---------------------
				m_blink += 10;
			}				   //幅を超えると、行数を+1
			else
			{
				m_line += 1;
				m_sec = 0;
				m_blink = 0;
			}

			//切り取り位置の設定(画像の黒い部分に設定)
			src.m_top = 20.0f;
			src.m_left = 20.0f;
			src.m_right = 119.0f;
			src.m_bottom = 55.0f;

			if (m_p != 1)
			{
				//Z入力および制御フラグオンで次のぺージへ
				if (Input::GetVKey('Z') == true&& m_next_f==true)
				{
					if (m_f == false)
					{
						m_line += 1;
						m_f = true;
						//キー入力可能時間になったらZを押して進む
						if (m_line >= 3)
						{
							m_page += 1;
							m_line = 0;		//行数リセット
							m_sec = 0;		//秒数リセット
							m_next_f = false;
							g_tutorial_next_flag = true;

						}

					}

				}
				else
				{
					m_f = false;
				}

				if (m_line == 0)
				{//１行目ーーーーーーーーーーーーーーーーーーーーーーー
					//表示位置の設定
					dst.m_top = 450.0f;
					if (m_line == 0)//１行目の時のみ動作
						dst.m_left = 50.0f + (m_sec*1.0f);
					else
						dst.m_left = 50.0f;
					dst.m_right = 765.0f;
					dst.m_bottom = 490.0f;
					//描画
					Draw::Draw(41, &src, &dst, c, 0.0f);
				}//行が変わると、表示しない
				else { ; }
				if (m_line <= 1)
				{//２行目ーーーーーーーーーーーーーーーーーーーーーーーー
					//表示位置の設定
					dst.m_top = 491.0f;
					if (m_line == 1)//２行目の時のみ動作
						dst.m_left = 20.0f + (m_sec*1.0f);
					else
						dst.m_left = 20.0f;
					dst.m_right = 765.0f;
					dst.m_bottom = 520.0f;
					//描画
					Draw::Draw(41, &src, &dst, c, 0.0f);
				}//行が変わると、表示しない
				else { ; }
				if (m_line <= 2 && m_p != 1)
				{//３行目ーーーーーーーーーーーーーーーーーー
					//表示位置の設定
					dst.m_top = 521.0f;
					if (m_line == 2)//３行目の時のみ動作
						dst.m_left = 20.0f + (m_sec*1.0f);
					else
						dst.m_left = 20.0f;
					dst.m_right = 765.0f;
					dst.m_bottom = 570.0f;
					//描画
					Draw::Draw(41, &src, &dst, c, 0.0f);
				}//行が変わると、表示しない
				else { ; }
			}

			if (m_line <= 3 || m_p == 1)
			{//・・・ーーーーーーーーーーーーーーーー
				dst.m_top = 540.0f;
				//if (m_line > 2 || m_p == 1)//３行目以降、動作
				//	if (m_blink <= 160)//表示位置を段階的に変更
				//		dst.m_left = 780.0f;
				//	else if (m_blink <= 250)
				//		dst.m_left = 600.0f;
				//	else { dst.m_left = 600.0f; m_blink = 0; m_sec = 0; }//カウントを０にして、元に戻す
				//else
					dst.m_left = 780.0f;
				dst.m_right = 750.0f;
				dst.m_bottom = 575.0f;
				//描画
				Draw::Draw(41, &src, &dst, c, 0.0f);
				m_next_f = true;

			}
			else 
			{ ; }
		}
		Font::StrDraw(L"チュートリアル", 10, 380, 30, c);




	}

}
