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
	g_hp = g_max_hp;	//hpを最大hpで初期化
	g_skill = NoSkill;	//スキルの値を牡牛座で初期化
	g_blackhole_cnt = 0;//ブラックホールのカウントの初期化


}

//デストラクタ
CSceneStageChoice::~CSceneStageChoice()
{

}

//ゲームタイトル初期化メソッド
void CSceneStageChoice::InitScene()
{
	Draw::LoadImageW(L"主人公.png", 1, TEX_SIZE_512);
	Draw::LoadImageW(L"ステージ背景1.png", 2, TEX_SIZE_512);
	Draw::LoadImageW(L"ステージ選択地球.png", 3, TEX_SIZE_512);
	Draw::LoadImageW(L"ステージ選択金星.png", 4, TEX_SIZE_512);
	Draw::LoadImageW(L"ステージ選択水星.png", 5, TEX_SIZE_512);
	Draw::LoadImageW(L"ステージ選択太陽.png", 6, TEX_SIZE_512);
	Draw::LoadImageW(L"惑星.png", 8, TEX_SIZE_512);
	Draw::LoadImageW(L"星座立ち絵総合.png", 7, TEX_SIZE_1024);
	Draw::LoadImageW(L"ミニマップ各種点.png", 9, TEX_SIZE_512);
	Draw::LoadImageW(L"テキストボックス .png", 40, TEX_SIZE_512);
	Draw::LoadImageW(L"テキストボックス 透過.png", 41, TEX_SIZE_512);
	Draw::LoadImageW(L"名前用枠.png", 42, TEX_SIZE_512);
	Draw::LoadImageW(L"リザルトスター.png", 70, TEX_SIZE_1024);
	Draw::LoadImageW(L"WARNING!!.png", 50, TEX_SIZE_2048);
	Draw::LoadImageW(L"!.png", 51, TEX_SIZE_2048);



	//Audio
	Audio::LoadAudio(1, L"ピコ！.wav", EFFECT);
	Audio::LoadAudio(2, L"決定音.wav", EFFECT);
	Audio::LoadAudio(4, L"警告音.wav", EFFECT);

	Audio::LoadAudio(3, L"ステージ選択_BGM.wav", SOUND_TYPE::BACK_MUSIC);

	Audio::Start(3);

	CObjWorning* worning = (CObjWorning*)Objs::GetObj(OBJ_WORNING);

	//ステージ選択オブジェクト作成
	CObjStageChoice* o = new CObjStageChoice();
	Objs::InsertObj(o, OBJ_STAGECHOICE, 0);
	
	//ステージ選択用ヒーローオブジェクト作成
	ObjStageChoiceHero* oh = new ObjStageChoiceHero(g_stage_px,g_stage_py);
	Objs::InsertObj(oh, OBJ_STAGECHOICEHERO, 10);
}

//ゲームタイトル実行中メソッド
void CSceneStageChoice::Scene()
{

}
