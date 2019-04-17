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
#include "SceneVenusTaurus.h"
#include "GameHead.h"

//コンストラクタ
CSceneVenusTaurus::CSceneVenusTaurus()
{
	g_StarCount = 0;	//星を数える変数の初期化

}

//デストラクタ
CSceneVenusTaurus::~CSceneVenusTaurus()
{

}

//初期化メソッド
void CSceneVenusTaurus::InitScene()
{
	//外部データ読み込み（ステージ情報）
	unique_ptr<wchar_t> p;	//ステージ情報ポインター
	int size;				//ステージ情報の大きさ
	p = Save::ExternalDataOpen(L"VenusCow.csv", &size);//外部データ読み込み

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
	Draw::LoadImageW(L"HP.png", 10, TEX_SIZE_512);
	Draw::LoadImageW(L"MP.png", 11, TEX_SIZE_512);
	Draw::LoadImageW(L"blackhole.png", 12, TEX_SIZE_256);


	Draw::LoadImageW(L"スキル総合.png", 13, TEX_SIZE_2048);
	Draw::LoadImageW(L"ハート弾.png", 20, TEX_SIZE_512);

	Draw::LoadImageW(L"box_blue.png", 40, TEX_SIZE_512);
	Draw::LoadImageW(L"box_blue_t.png", 41, TEX_SIZE_512);
	Draw::LoadImageW(L"box_mini.png", 42, TEX_SIZE_512);



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
	Objs::InsertObj(objstatus, OBJ_STATUS, 130);

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
void CSceneVenusTaurus::Scene()
{
	//テスト（金星（おうし座）で星を18個集めたら次へ移行）
	if (g_StarCount == TAURUSMAXSTAR)
	{
		g_Taurus = true;		//スキル（牡牛座）をオンにする
		//おうし座にクリア表記
		g_Taurus_clear = true;
		//もし、金星の星座をどちらもクリアしていたなら金星にクリア表示
		if (g_Libra_clear == true && g_Taurus_clear == true)
		{
			g_Venus_clear = true;
		}
		Scene::SetScene(new CSceneStageChoice());	//ゲームメインシーンに移行
	}
}