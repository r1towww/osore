//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"
#include "GameHead.h"

#include "ObjMenu.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjMenu::Init()
{
	m_key = 0;
	m_key_f = false;
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
		g_move_stop_flag = false;	//ストップフラグをオフ
		this->SetStatus(false);		//オブジェクトを削除
	}

	if (Input::GetVKey(VK_RIGHT))//矢印キー（右）が入力されたとき
	{
		m_key = 0;	//０番をセット
	}
	else if (Input::GetVKey(VK_LEFT))//矢印キー（左）が入力されたとき
	{
		m_key = 1;	//１番をセット
	}


	//Zキーが押された場合
	if (Input::GetVKey('Z') == true)
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
			Scene::SetScene(new CSceneStageChoice());	//ステージ選択へ戻る
		}
	}



}

//ドロー
void CObjMenu::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };	//メッセージフォントカラー
	float backc[4] = { 1.0f,1.0f,0.0f,1.0f };	
	float a[4] = { 1.0f,1.0f,1.0f,0.5f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

//背景用画像-----------------------------------
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
	
	Font::StrDraw(L"ステージ選択へ戻る", 110, 250, 32, c);
	Font::StrDraw(L"ゲームへ戻る", 470, 250, 32, c);

	//番号によって選択を変更
	if (m_key == 0)
		Font::StrDraw(L"→", 440, 250, 32, c);
	else if (m_key == 1)
		Font::StrDraw(L"→", 80, 250, 32, c);

//----------------------------------------------


}
