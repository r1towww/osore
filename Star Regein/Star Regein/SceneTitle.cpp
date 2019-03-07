//STLデバッグ機能をOFFにする
#define _SECURE_SCL	(0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL/DrawTexture.h"
#include "GameL\Audio.h"


//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "GameHead.h"
#include "SceneTitle.h"

//コンストラクタ
CSceneTitle::CSceneTitle()
{
}

//デストラクタ
CSceneTitle::~CSceneTitle()
{
}

//ゲームタイトル初期化メソッド
void CSceneTitle::InitScene()
{
	//タイトルオブジェクト作成
	CObjTitle* obj = new CObjTitle();
	Objs::InsertObj(obj, OBJ_TITLE, 10);
}

//ゲームタイトル実行中メソッド
void CSceneTitle::Scene()
{

}
