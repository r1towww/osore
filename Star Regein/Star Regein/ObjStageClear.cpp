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
		Scene::SetScene(new CSceneStageChoice());
	}
}

//ドロー
void CObjStageClear::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	Font::StrDraw(L"ステージクリア", 100, 100, 50, c);

}
