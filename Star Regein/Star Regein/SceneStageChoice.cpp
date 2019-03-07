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
#include "SceneStageChoice.h"

//コンストラクタ
CSceneStageChoice::CSceneStageChoice()
{

}

//デストラクタ
CSceneStageChoice::~CSceneStageChoice()
{

}

//ゲームタイトル初期化メソッド
void CSceneStageChoice::InitScene()
{
	Draw::LoadImageW(L"HeroTouka.png", 1, TEX_SIZE_512);

	//ステージ選択オブジェクト作成
	CObjStageChoice* o = new CObjStageChoice();
	Objs::InsertObj(o, OBJ_STAGECHOICE, 10);

}

//ゲームタイトル実行中メソッド
void CSceneStageChoice::Scene()
{

}
