//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"
#include "GameHead.h"
#include "GameL/Audio.h"

#include "ObjMenu.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjMenu::Init()
{
	//選択キーを0（右）で初期化
	m_key = 0;
	//キーフラグの初期化
	m_key_f = false;
	m_choice_key_f = false;	
	m_Tra = 0.0f;
	m_f = false;
}

//アクション
void CObjMenu::Action()
{
	//キーを一度離さないと入力を受け付けない
	if (Input::GetVKey('Q') == false)
	{
		m_key_f = true;
	}
	//Qキーが再度押された場合
	if (Input::GetVKey('Q') == true && m_key_f == true)
	{
		Audio::Start(1);	//エフェクト音を鳴らす
		g_move_stop_flag = false;	//ストップフラグをオフ
		this->SetStatus(false);		//オブジェクトを削除
	}

	if (Input::GetVKey(VK_RIGHT) && m_choice_key_f == true)//キーフラグがオンの状態で、矢印キー（右）が入力されたとき
	{
		Audio::Start(1);	//エフェクト音を鳴らす
		m_key = 0;	//０番をセット
		m_choice_key_f = false;	//フラグをオン
	}
	else if (Input::GetVKey(VK_LEFT) && m_choice_key_f == false)//キーフラグがオフの状態で、矢印キー（左）が入力されたとき
	{
		Audio::Start(1);	//エフェクト音を鳴らす
		m_key = 1;	//１番をセット
		m_choice_key_f = true;	//フラグをオン
	}


	//Zキーが押された場合
	if (Input::GetVKey('Z') == true || Input::GetVKey(VK_RETURN) == true)
	{
		//０番の場合
		if (m_key == 0)
		{
			g_move_stop_flag = false;	//ストップフラグをオフ
			this->SetStatus(false);		//オブジェクトを削除
		}
		//１番の場合
		else if (m_key == 1)
		{
			g_move_stop_flag = false;	//ストップフラグをオフ
			m_push_flag = true;

			
		}
		g_key_flag = false;
	}

	if (m_push_flag == true)
	{
		if (m_f == false)
		{
			Audio::Start(2);	//エフェクト音を鳴らす
			m_f = true;
		}
		
		
		m_Tra += 0.03;
		if (m_Tra >= 1)
		{
			if (g_stage == Space)
			{
				Scene::SetScene(new CSceneTitle());	//タイトル選択へ戻る

			}
			else
			{
				this->SetStatus(false);		//オブジェクトを削除

				g_stage = Space;
				Scene::SetScene(new CSceneStageChoice());	//ステージ選択へ戻る

			}
		}
	}

}

//ドロー
void CObjMenu::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };	//メッセージフォントカラー
	float backc[4] = { 1.0f,1.0f,0.0f,1.0f };	
	float a[4] = { 1.0f,1.0f,1.0f,0.5f };
	float c2[4] = { 1.0f,1.0f,1.0f,m_Tra };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

//背景用画像-----------------------------------

	//シーン切り替え用
	if (m_push_flag == true)
	{

		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 350.0f;
		src.m_right = 400.0f;
		src.m_bottom = 50.0f;

		//表示位置の設定
		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 600.0f;

		Draw::Draw(9, &src, &dst, c2, 0.0f);
	}
	
	//切り取り位置の設定
	src.m_top    = 0.0f;
	src.m_left   = 0.0f;
	src.m_right  = 822.0f;
	src.m_bottom = 218.0f;

	//表示位置の設定
	dst.m_top    = 100.0f;
	dst.m_left   = 50.0f;
	dst.m_right  = 750.0f;
	dst.m_bottom = 500.0f;
	//表示
	Draw::Draw(40, &src, &dst, backc, 0.0f);

	


//----------------------------------------------

//文字描画用------------------------------------
	if (g_stage == Space)
	{
		Font::StrDraw(L"タイトルへ戻る", 110, 250, 32, c);
		Font::StrDraw(L"ゲームへ戻る", 470, 250, 32, c);
	}
	else
	{
		Font::StrDraw(L"ステージ選択へ戻る", 110, 250, 32, c);
		Font::StrDraw(L"ゲームへ戻る", 470, 250, 32, c);
	}
	//番号によって選択を変更
	if (m_key == 0)
		Font::StrDraw(L"→", 440, 250, 32, c);
	else if (m_key == 1)
		Font::StrDraw(L"→", 80, 250, 32, c);

//----------------------------------------------


}
