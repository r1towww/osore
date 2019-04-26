//STLデバッグ機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"

//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "SceneStageClear.h"
#include "GameHead.h"

//コンストラクタ
CSceneStageClear::CSceneStageClear()
{

}

//デストラクタ
CSceneStageClear::~CSceneStageClear()
{

}

//初期化メソッド
void CSceneStageClear::InitScene()
{
	Draw::LoadImageW(L"宇宙背景.png", 1, TEX_SIZE_1024);


	//クリアオブジェクト作成
	CObjStageClear* oc = new CObjStageClear();
	Objs::InsertObj(oc, OBJ_STAGECLEAR, 1);

}
//実行中メソッド
void CSceneStageClear::Scene()
{

}