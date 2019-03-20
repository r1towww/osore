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
#include "SceneStarChoice.h"

//コンストラクタ
CSceneStarChoice::CSceneStarChoice()
{

}

//デストラクタ
CSceneStarChoice::~CSceneStarChoice()
{

}

//ゲームタイトル初期化メソッド
void CSceneStarChoice::InitScene()
{
	Draw::LoadImageW(L"スキル総合.png", 1, TEX_SIZE_2048);
	Draw::LoadImageW(L"天秤スキル.png", 2, TEX_SIZE_512);

	//ステージ選択オブジェクト作成
	CObjStarChoice* o = new CObjStarChoice();
	Objs::InsertObj(o, OBJ_STARCHOICE, 0);

	////ステージ選択用ヒーローオブジェクト作成
	//ObjStageChoiceHero* oh = new ObjStageChoiceHero(50, 500);
	//Objs::InsertObj(oh, OBJ_STAGECHOICEHERO, 10);

}

//ゲームタイトル実行中メソッド
void CSceneStarChoice::Scene()
{

}
