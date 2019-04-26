//使用するヘッダー
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\SceneManager.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "ObjGameOver.h"

//使用するネームスペース
using namespace GameL;


//イニシャライズ
void CObjGameOver::Init()
{
	m_keytime = 0;	//キー入力タイムの初期化
}

//アクション
void CObjGameOver::Action()
{

}

//ドロー
void CObjGameOver::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	float bl [4] = { 1.0f,0.0f,0.0f,1.0f };
	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	//背景------------------------------------
	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 800.0f;
	src.m_bottom = 600.0f;

	//表示位置の設定
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;

	//表示
	Draw::Draw(1, &src, &dst, c, 0.0f);
	//----------------------------------------

	Font::StrDraw(L"GAME OVER", 160, 150, 100, bl);

	//シーンに移ってきた際のキー入力タイム処理
	if (m_keytime >= 50)
		m_keytime = 50;	//タイムが50になった際、50で止める
	else
		m_keytime++;	//キー入力タイムを増やす

	//右キー入力
	if (Input::GetVKey(VK_RIGHT) == true)
	{
		m_Right = true;
		m_Left = false;
	}
	//左キー入力
	if (Input::GetVKey(VK_LEFT) == true)
	{
		m_Right = false;
		m_Left = true;
	}
	//右キー入力でフォント切り替え
	if (m_Right == true)
	{
		Font::StrDraw(L"◇ステージ選択へ戻る", 400, 400, 32, c);
		//この状態でＺキーでステージ選択へ
		if ((Input::GetVKey('Z') == true || Input::GetVKey(VK_RETURN) == true) && m_keytime == TIMELIMIT)	//キー入力タイムが一定に達した場合、キー入力を許可する
		{
			Scene::SetScene(new CSceneStageChoice());
		}

	}
	else
	{
		//そうでなかったら最初のフォントを表示する
		Font::StrDraw(L"ステージ選択へ戻る", 400, 400, 32, c);
	}
	//左キー入力でフォント切り替え
	if (m_Left == true)
	{
		Font::StrDraw(L"◇タイトルに戻る", 100, 400, 32, c);
		//この状態でＺキーでタイトルへ
		if ((Input::GetVKey('Z') == true||Input::GetVKey(VK_RETURN)==true) && m_keytime == TIMELIMIT)	//キー入力タイムが一定に達した場合、キー入力を許可する
		{
			Scene::SetScene(new CSceneTitle());
		}

	}
	else
	{
		//そうでなかったら最初のフォントを表示する
		Font::StrDraw(L"タイトルに戻る", 100, 400, 32, c);
	}

}
