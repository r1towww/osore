//STLデバッグ機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"

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
	Draw::LoadImageW(L"宇宙背景.png", 1, TEX_SIZE_1024);

	//Audio
	Audio::LoadAudio(1, L"ゲームオーバー.wav", EFFECT);
	Audio::LoadAudio(2, L"ピコ！.wav", EFFECT);
	Audio::LoadAudio(3, L"決定音.wav", EFFECT);

	//クリアオブジェクト作成
	CObjGameOver* o = new CObjGameOver();
	Objs::InsertObj(o, OBJ_GAMEOVER, 1);
}
//実行中メソッド
void CSceneGameOver::Scene()
{

}