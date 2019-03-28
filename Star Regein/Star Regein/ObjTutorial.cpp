//使用するヘッダー
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\SceneManager.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "ObjTutorial.h"

bool g_tutorial_flag = false;

//----------------------------------
//使用するネームスペース
using namespace GameL;


//イニシャライズ
void CObjTutorial::Init()
{
	g_tutorial_flag = true;

	//キー入力用タイムの初期化
	m_keytime = 0;

	m_page = 0;		//渡されたページ数
	m_sec = 0;		//秒数カウント
	m_line = 0;		//行数カウント

}

//アクション
void CObjTutorial::Action()
{
	if (m_page == m_p) 
	{//渡されたページ数と現在のページ数が同じになったら
		g_tutorial_flag = false;
	}

	//惑星が選択され、戦闘画面への移行の際
	if (g_stage == EarthStar )
	{

		//画像が表示された際の、キー入力タイム処理
		if (m_keytime >= 50)
			m_keytime = 50;	//タイムが50になった際、50で止める
		else
			m_keytime++;	//キー入力タイムを増やす

	}
	else
	{
		m_keytime = 0;	//それ以外の場合、キー入力タイムを0にする
	}

}



//ドロー
void CObjTutorial::Draw()
{
		//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	//チュートリアルフラグが立った時チュートリアルを開始する
	if (g_tutorial_flag == true)
	{
		//地球
		if (g_stage == EarthStar)
		{
			//テキストボックス表示
			if (m_tipe == 0)
			{
				
				//チュートリアル専用テキストボックス------------------------------------
				//切り取り位置の設定
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 775.0f;
				src.m_bottom = 183.0f;

				//表示位置の設定
				dst.m_top = 400.0f;
				dst.m_left = 0.0f;
				dst.m_right = 775.0f;
				dst.m_bottom = 588.0f;
				//表示
				Draw::Draw(12, &src, &dst, c, 0.0f);
				if (m_p != 1) {//ページ数が1ではない場合
				//同じ画像を名前用に上から表示
				//表示位置の設定
					dst.m_top = 400.0f;
					dst.m_left = 0.0f;
					dst.m_right = 775.0f;
					dst.m_bottom = 588.0f;

					//描画
					Draw::Draw(12, &src, &dst, c, 0.0f);
				}
				else { ; }

			}
			//----------------------------------------
			else if (m_tipe == 1) {//tipe1は、コメントを隠す画像表示
				if (m_sec <= 700) {//715(コメントの幅)まで時間経過
					m_sec += 5;	   //文字の表示スピード---------------------
				}				   //幅を超えると、行数を+1
				else {
					m_line += 1;
					m_sec = 0;
				}

				//切り取り位置の設定(画像の黒い部分に設定)
				src.m_top = 20.0f;
				src.m_left = 20.0f;
				src.m_right = 119.0f;
				src.m_bottom = 55.0f;

				if (m_p != 1) {
					if (m_line == 0) 
					{//１行目ーーーーーーーーーーーーーーーーーーーーーーー
									  //表示位置の設定
						dst.m_top = 450.0f;
						if (m_line == 0)//１行目の時のみ動作
							dst.m_left = 50.0f + (m_sec*1.0f);
						else
							dst.m_left = 50.0f;
						dst.m_right = 765.0f;
						dst.m_bottom = 480.0f;
						//描画
						Draw::Draw(13, &src, &dst, c, 0.0f);
					}//行が変わると、表示しない
					else { ; }
					if (m_line <= 1) 
					{//２行目ーーーーーーーーーーーーーーーーーーーーーーーー
									  //表示位置の設定
						dst.m_top = 480.0f;
						if (m_line == 1)//２行目の時のみ動作
							dst.m_left = 50.0f + (m_sec*1.0f);
						else
							dst.m_left = 50.0f;
						dst.m_right = 765.0f;
						dst.m_bottom = 510.0f;
						//描画
						Draw::Draw(13, &src, &dst, c, 0.0f);
					}//行が変わると、表示しない
					else { ; }
					if (m_line <= 2 && m_p != 1) 
					{//３行目ーーーーーーーーーーーーーーーーーー
												  //表示位置の設定
						dst.m_top = 520.0f;
						if (m_line == 2)//３行目の時のみ動作
							dst.m_left = 50.0f + (m_sec*1.0f);
						else
							dst.m_left = 50.0f;
						dst.m_right = 765.0f;
						dst.m_bottom = 550.0f;
						//描画
						Draw::Draw(13, &src, &dst, c, 0.0f);
					}//行が変わると、表示しない
					else { ; }
				}

				if (m_line <= 3 || m_p == 1) 
				{//・・・ーーーーーーーーーーーーーーーー
					dst.m_top = 550.0f;
					if (m_line > 2 || m_p == 1)//３行目以降、動作
						if (m_sec <= 160)//表示位置を段階的に変更
							dst.m_left = 745.0f;
						else if (m_sec <= 280)
							dst.m_left = 760.0f;
						else if (m_sec <= 440)
							dst.m_left = 770.0f;
						else if (m_sec <= 600)
							dst.m_left = 730.0f;
						else { dst.m_left = 730.0f; m_sec = 0; }//カウントを０にして、元に戻す
					else
						dst.m_left = 730.0f;
					dst.m_right = 770.0f;
					dst.m_bottom = 575.0f;
					//描画
					Draw::Draw(13, &src, &dst, c, 0.0f);
				}
				else { ; }
			}
			Font::StrDraw(L"チュートリアル", 0, 410, 30, c);

			//キー入力可能時間になったらZを押して進む
			if (m_keytime == 50)
			{
				if (Input::GetVKey('Z') == true)
				{
					m_page += 1;
					m_line = 0;		//行数リセット
					m_sec = 0;		//秒数リセット
					m_keytime = 0;
				}
			}

		}



	//	if (g_stage == VenusTaurus)
	//	{
	//		//チュートリアル専用テキストボックス------------------------------------
	//		//切り取り位置の設定
	//		src.m_top = 0.0f;
	//		src.m_left = 0.0f;
	//		src.m_right = 775.0f;
	//		src.m_bottom = 183.0f;

	//		//表示位置の設定
	//		dst.m_top = 400.0f;
	//		dst.m_left = 0.0f;
	//		dst.m_right = 775.0f;
	//		dst.m_bottom = 588.0f;

	//		//表示
	//		Draw::Draw(12, &src, &dst, c, 0.0f);
	//		//----------------------------------------
	//		Font::StrDraw(L"チュートリアル", 0, 410, 30, c);
	//		//キー入力可能時間になったらZを押して進む
	//		if (m_keytime == 50)
	//		{
	//			if (Input::GetVKey('Z') == true)
	//			{
	//				m_page += 1;
	//			}
	//		}

	//	}
	//	if (g_stage == VenusLibra)
	//	{
	//		//チュートリアル専用テキストボックス------------------------------------
	//		//切り取り位置の設定
	//		src.m_top = 0.0f;
	//		src.m_left = 0.0f;
	//		src.m_right = 775.0f;
	//		src.m_bottom = 183.0f;

	//		//表示位置の設定
	//		dst.m_top = 400.0f;
	//		dst.m_left = 0.0f;
	//		dst.m_right = 775.0f;
	//		dst.m_bottom = 588.0f;

	//		//表示
	//		Draw::Draw(12, &src, &dst, c, 0.0f);
	//		//----------------------------------------
	//		Font::StrDraw(L"チュートリアル", 0, 410, 30, c);
	//		for (int i = 0; i < 5; i++)
	//		{

	//		}
	//		//キー入力可能時間になったらZを押して進む
	//		if (m_keytime == 50)
	//		{
	//			if (Input::GetVKey('Z') == true)
	//			{
	//				g_tutorial_flag = false;
	//			}
	//		}
	//	}
	//	if (g_stage == MercuryGemini)
	//	{
	//		//チュートリアル専用テキストボックス------------------------------------
	//		//切り取り位置の設定
	//		src.m_top = 0.0f;
	//		src.m_left = 0.0f;
	//		src.m_right = 775.0f;
	//		src.m_bottom = 183.0f;

	//		//表示位置の設定
	//		dst.m_top = 400.0f;
	//		dst.m_left = 0.0f;
	//		dst.m_right = 775.0f;
	//		dst.m_bottom = 588.0f;

	//		//表示
	//		Draw::Draw(12, &src, &dst, c, 0.0f);
	//		//----------------------------------------
	//		Font::StrDraw(L"チュートリアル", 0, 410, 30, c);
	//		for (int i = 0; i < 5; i++)
	//		{

	//		}
	//		//キー入力可能時間になったらZを押して進む
	//		if (m_keytime == 50)
	//		{
	//			if (Input::GetVKey('Z') == true)
	//			{
	//				g_tutorial_flag = false;
	//			}
	//		}
	//	}

	}


}
