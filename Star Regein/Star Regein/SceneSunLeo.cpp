//STLデバッグ機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"
#include"GameL\Audio.h"

//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "SceneSunLeo.h"
#include "GameHead.h"

//コンストラクタ
CSceneSunLeo::CSceneSunLeo()

{
	g_StarCount = 0;	//星を数える変数の初期化

}

//デストラクタ
CSceneSunLeo::~CSceneSunLeo()
{


}

//初期化メソッド
void CSceneSunLeo::InitScene()
{
	//外部データ読み込み（ステージ情報）
	unique_ptr<wchar_t> p;	//ステージ情報ポインター
	int size;				//ステージ情報の大きさ
	p = Save::ExternalDataOpen(L"SunLeo.csv", &size);//外部データ読み込み


	int map[MAPSIZE][MAPSIZE];
	int count = 1;

	for (int i = 0; i < MAPSIZE; i++)
	{
		for (int j = 0; j < MAPSIZE; j++)
		{

			int w = 0;
			swscanf_s(&p.get()[count], L"%d", &w);
			map[i][j] = w;
			if (w >= 10)
			{
				count += 1;
			}
			count += 2;
		}
	}

	//グラフィック読み込み
	Draw::LoadImageW(L"主人公.png", 1, TEX_SIZE_512);
	Draw::LoadImageW(L"斬撃アニメーション.png", 2, TEX_SIZE_512);
	Draw::LoadImageW(L"牛.png", 3, TEX_SIZE_512);
	Draw::LoadImageW(L"隕石.png", 4, TEX_SIZE_512);
	Draw::LoadImageW(L"SpaceBack.png", 5, TEX_SIZE_1024);
	Draw::LoadImageW(L"星 エフェクト入り.png", 6, TEX_SIZE_1024);
	Draw::LoadImageW(L"Background.png", 7, TEX_SIZE_2048);
	Draw::LoadImageW(L"ミニマップ背景.png", 8, TEX_SIZE_512);
	Draw::LoadImageW(L"color.png", 9, TEX_SIZE_512);
	Draw::LoadImageW(L"HP.png", 10, TEX_SIZE_2048);
	Draw::LoadImageW(L"MP.png", 11, TEX_SIZE_2048);
	Draw::LoadImageW(L"弾丸.png", 16, TEX_SIZE_128);
	Draw::LoadImageW(L"スキル総合.png", 13, TEX_SIZE_2048);
	Draw::LoadImageW(L"回復エフェクト.png", 14, TEX_SIZE_2048);
	Draw::LoadImageW(L"ダッシュ.png", 15, TEX_SIZE_1024);
	Draw::LoadImageW(L"岩砕きエフェクト.png", 17, TEX_SIZE_2048);

	Draw::LoadImageW(L"blackhole.png", 30, TEX_SIZE_1024);
	Draw::LoadImageW(L"whitehole.png", 31, TEX_SIZE_1024);

	Draw::LoadImageW(L"box_blue.png", 40, TEX_SIZE_512);
	Draw::LoadImageW(L"box_blue_t.png", 41, TEX_SIZE_512);
	Draw::LoadImageW(L"box_mini.png", 42, TEX_SIZE_512);
	Draw::LoadImageW(L"ハート弾.png", 50, TEX_SIZE_512);
	Draw::LoadImageW(L"着弾アニメーション.png", 51, TEX_SIZE_512);


	//Audio
	Audio::LoadAudio(1, L"刀剣・斬る01.wav", EFFECT);		//近距離空振り時SE
	Audio::LoadAudio(2, L"刀剣・斬る07.wav", EFFECT);		//近距離ヒット時SE
	Audio::LoadAudio(3, L"ダメージ音02.wav", EFFECT);		//ダメージSE
	Audio::LoadAudio(4, L"星・キラーン06.wav", EFFECT);		//星取得時SE
	Audio::LoadAudio(5, L"場面転換・スライド表現04.wav", EFFECT);//ブラックホールでのワープ時SE

    //blockオブジェクト作成
	CObjBlock* objb = new CObjBlock(map);
	Objs::InsertObj(objb, OBJ_BLOCK, 1);

	//MiniMapオブジェクト作成
	CObjMiniMap* objminimap = new CObjMiniMap(map);
	Objs::InsertObj(objminimap, OBJ_MINIMAP, 100);

	//メッセージオブジェクト作成
	CObjMessage* objmes = new CObjMessage();
	Objs::InsertObj(objmes, OBJ_MESSAGE, 120);

	//Statusゲージオブジェクト作成
	CObjStatus* objstatus = new CObjStatus();
	Objs::InsertObj(objstatus, OBJ_STATUS, 100);

	//スキル切り替えオブジェクト作成
	CObjSkill* objSkill = new CObjSkill();
	Objs::InsertObj(objSkill, OBJ_SKILL, 150);

	//チュートリアル吹き出し作成
	CObjTutorial* objtutorialhukidashi = new CObjTutorial(0, 7);
	Objs::InsertObj(objtutorialhukidashi, OBJ_TUTORIAL, 151);
	//チュートリアルオブジェクト作成
	CObjTutorial* objtutorial = new CObjTutorial(1, 7);
	Objs::InsertObj(objtutorial, OBJ_TUTORIAL, 170);
	//チュートリアル発生時のみ作成
	if (g_tutorial_flag == true)
	{
		//テキストボックスオブジェクト作成
		CObjTextBox* objtextbox = new CObjTextBox();
		Objs::InsertObj(objtextbox, OBJ_TEXTBOX, 160);
	}

}

//実行中メソッド
void CSceneSunLeo::Scene()
{
	//太陽で星を14個集めたら次へ移行
	if (g_StarCount == 1)
	{
		g_Leo = true;		//スキル（天秤座）をオンにする
		//獅子座をクリア表示
		g_Sun_clear = true;

		Scene::SetScene(new CSceneStageChoice());
	}
}