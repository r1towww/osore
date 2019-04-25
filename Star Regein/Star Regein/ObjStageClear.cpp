//使用するヘッダー
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\SceneManager.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "ObjStageClear.h"

//使用するネームスペース
using namespace GameL;


//イニシャライズ
void CObjStageClear::Init()
{
	m_keytime = 0;	//キー入力タイムの初期化
}

//アクション
void CObjStageClear::Action()
{
	//シーンに移ってきた際のキー入力タイム処理
	if (m_keytime >= 50)
		m_keytime = 50;	//タイムが50になった際、50で止める
	else
		m_keytime++;	//キー入力タイムを増やす

	if (Input::GetVKey('Z') == true && m_keytime == TIMELIMIT)	//キー入力タイムが一定に達した場合、キー入力を許可する
	{
		g_stage_clear = false;
		Scene::SetScene(new CSceneStageChoice());
	}
}

//ドロー
void CObjStageClear::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	float y[4] = { 1.0f,1.0f,0.0f,1.0f };
	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置
	if (g_stage == EarthStar)
	{
		//地球------------------------------------
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 790.0f;
		src.m_bottom = 590.0f;

		//表示位置の設定
		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 600.0f;

		//表示
		Draw::Draw(16, &src, &dst, c, 0.0f);
		//----------------------------------------
	}
	if (g_stage == VenusTaurus)
	{
		//金星（牡牛座）--------------------------
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 790.0f;
		src.m_bottom = 590.0f;

		//表示位置の設定
		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 600.0f;

		//表示
		Draw::Draw(16, &src, &dst, c, 0.0f);
		//---------------------------------------
	}
	if (g_stage == VenusLibra)
	{
		//金星（牡牛座）--------------------------
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 790.0f;
		src.m_bottom = 590.0f;

		//表示位置の設定
		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 600.0f;

		//表示
		Draw::Draw(18, &src, &dst, c, 0.0f);
		//---------------------------------------
	}

	Font::StrDraw(L"STAGE CLEAR", 120,150, 100,y);

	Font::StrDraw(L"Zキーでステージ選択へ戻る", 200, 510, 32, y);

}
