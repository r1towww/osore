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

int g_StarCount = 0;	//星を数える変数の初期化

//使用ヘッダー
#include "SceneEarth.h"
#include "GameHead.h"

//コンストラクタ
CSceneEarth::CSceneEarth()
{
}

//デストラクタ
CSceneEarth::~CSceneEarth()
{

}

//初期化メソッド
void CSceneEarth::InitScene()
{
	//外部データ読み込み（ステージ情報）
	unique_ptr<wchar_t> p;	//ステージ情報ポインター
	int size;				//ステージ情報の大きさ
	p = Save::ExternalDataOpen(L"Earth test.csv", &size);//外部データ読み込み
	
	int map[50][50];
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
	Draw::LoadImageW(L"ビームサーベル.png", 2, TEX_SIZE_512);
	Draw::LoadImageW(L"牛.png", 3, TEX_SIZE_512);
	Draw::LoadImageW(L"隕石.png", 4, TEX_SIZE_64);
	Draw::LoadImageW(L"SpaceBack.png", 5, TEX_SIZE_1024);
	Draw::LoadImageW(L"星.png", 6, TEX_SIZE_1024);
	Draw::LoadImageW(L"Background.png", 7, TEX_SIZE_2048);
	Draw::LoadImageW(L"ミニマップ背景.png", 8, TEX_SIZE_512);
	Draw::LoadImageW(L"color.png", 9, TEX_SIZE_512);
	Draw::LoadImageW(L"HP.png",10, TEX_SIZE_512);
	Draw::LoadImageW(L"MP.png", 11, TEX_SIZE_512);
	Draw::LoadImageW(L"弾丸.png", 14, TEX_SIZE_128);

	//テスト用
	Draw::LoadImageW(L"双子1.png", 20, TEX_SIZE_512);
	Draw::LoadImageW(L"双子2.png", 21, TEX_SIZE_512);
	
	//blockオブジェクト作成
	CObjBlock* objb = new CObjBlock(map);
	Objs::InsertObj(objb, OBJ_BLOCK, 1);
	
	//MiniMapオブジェクト作成
	CObjMiniMap* objminimap = new CObjMiniMap(map);
	Objs::InsertObj(objminimap, OBJ_MINIMAP, 100);

	//メッセージオブジェクト作成
	CObjMessage* objmes = new CObjMessage();
	Objs::InsertObj(objmes, OBJ_MESSAGE, 120);

	//HPゲージオブジェクト作成
	CObjHeart* objheart = new CObjHeart();
	Objs::InsertObj(objheart, OBJ_HEART, 130);

	//MPゲージオブジェクト作成
	CObjMP* objMP = new CObjMP();
	Objs::InsertObj(objMP, OBJ_MP, 140);
}


//実行中メソッド
void CSceneEarth::Scene()
{
	//テスト（地球で星を5個集めたら次へ移行）
	if (g_StarCount == 5)
	{
		Scene::SetScene(new CSceneStageClear());	//ゲームメインシーンに移行
	}
	
}