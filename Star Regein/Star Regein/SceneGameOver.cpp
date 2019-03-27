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
#include "SceneGameOver.h"
#include "GameHead.h"

//コンストラクタ
CSceneGameOver::CSceneGameOver()
{

}

//デストラクタ
CSceneGameOver::~CSceneGameOver()
{

}

//初期化メソッド
void CSceneGameOver::InitScene()
{
	Draw::LoadImageW(L"SpaceBack.png", 1, TEX_SIZE_1024);


	//クリアオブジェクト作成
	CObjGameOver* o = new CObjGameOver();
	Objs::InsertObj(o, OBJ_STAGECLEAR, 1);
}
//実行中メソッド
void CSceneGameOver::Scene()
{

}