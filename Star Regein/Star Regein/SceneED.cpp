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
#include "SceneED.h"

//コンストラクタ
CSceneED::CSceneED()
{
}

//デストラクタ
CSceneED::~CSceneED()
{
}

//ゲームタイトル初期化メソッド
void CSceneED::InitScene()
{
	//タイトルオブジェクト作成
	CObjED* obj = new CObjED();
	Objs::InsertObj(obj, OBJ_ED, 100);

	//Audio
	Audio::LoadAudio(1, L"ピコ！.wav", EFFECT);
	Audio::LoadAudio(2, L"決定音.wav", EFFECT);
	Audio::LoadAudio(3, L"タイトル_BGM.wav", SOUND_TYPE::BACK_MUSIC);

	Audio::LoadAudio(19, L"リザルトスターSE.wav", EFFECT);
	Audio::LoadAudio(20, L"SランクSE.wav", EFFECT);
	Audio::LoadAudio(21, L"AランクSE.wav", EFFECT);
	Audio::LoadAudio(22, L"BCランクSE.wav", EFFECT);
	Audio::LoadAudio(23, L"ステージクリアBGM.wav", SOUND_TYPE::BACK_MUSIC);


	Audio::Start(3);
	//画像
	Draw::LoadImageW(L"Fadein.png", 1, TEX_SIZE_512);
	Draw::LoadImageW(L"リザルトスター.png", 70, TEX_SIZE_1024);
	Draw::LoadImageW(L"リザルトスターエフェクト.png", 71, TEX_SIZE_1024);

}

//ゲームタイトル実行中メソッド
void CSceneED::Scene()
{

}
