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
#include "SceneMercuryGemini.h"
#include "GameHead.h"

//コンストラクタ
CSceneMercuryGemini::CSceneMercuryGemini()
{
	g_StarCount = 0;	//星を数える変数の初期化
	Item_cnt = 0.0f;
	g_Make_Item = false;
}

//デストラクタ
CSceneMercuryGemini::~CSceneMercuryGemini()
{

}

//初期化メソッド
void CSceneMercuryGemini::InitScene()
{
	//外部データ読み込み（ステージ情報）
	unique_ptr<wchar_t> p;	//ステージ情報ポインター
	int size;				//ステージ情報の大きさ
	p = Save::ExternalDataOpen(L"MercuryGemini.csv", &size);//外部データ読み込み

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
	Draw::LoadImageW(L"主人公斬撃アニメーション.png", 2, TEX_SIZE_512);

	Draw::LoadImageW(L"天秤座スキルエフェクト.png", 14, TEX_SIZE_2048);
	Draw::LoadImageW(L"ダッシュ.png", 15, TEX_SIZE_1024);
	Draw::LoadImageW(L"岩砕きエフェクト.png", 17, TEX_SIZE_2048);
	Draw::LoadImageW(L"ハート弾.png", 50, TEX_SIZE_512);
	Draw::LoadImageW(L"着弾アニメーション.png", 51, TEX_SIZE_512);
	Draw::LoadImageW(L"獅子座スキルエフェクト.png", 23, TEX_SIZE_512);

	Draw::LoadImageW(L"双子1.png", 20, TEX_SIZE_512);
	Draw::LoadImageW(L"双子2.png", 21, TEX_SIZE_512);

	Draw::LoadImageW(L"双子用弾丸.png", 16, TEX_SIZE_128);

	Draw::LoadImageW(L"隕石.png", 4, TEX_SIZE_64);
	Draw::LoadImageW(L"星 エフェクト入り.png", 6, TEX_SIZE_2048);
	Draw::LoadImageW(L"ブラックホール.png", 30, TEX_SIZE_1024);
	Draw::LoadImageW(L"ホワイトホール.png", 31, TEX_SIZE_1024);

	Draw::LoadImageW(L"宇宙背景.png", 5, TEX_SIZE_1024);
	Draw::LoadImageW(L"星座立ち絵総合.png", 13, TEX_SIZE_1024);

	Draw::LoadImageW(L"ステージクリア画像_水星_双子座.png", 60, TEX_SIZE_2048);

	Draw::LoadImageW(L"ミニマップ枠.png", 7, TEX_SIZE_2048);
	Draw::LoadImageW(L"ミニマップ背景.png", 8, TEX_SIZE_512);
	Draw::LoadImageW(L"ミニマップ各種点.png", 9, TEX_SIZE_512);
	Draw::LoadImageW(L"HP.png", 10, TEX_SIZE_2048);

	Draw::LoadImageW(L"テキストボックス .png", 40, TEX_SIZE_512);
	Draw::LoadImageW(L"テキストボックス 透過.png", 41, TEX_SIZE_512);
	Draw::LoadImageW(L"名前用枠.png", 42, TEX_SIZE_512);

	Draw::LoadImageW(L"消滅アニメーション.png", 80, TEX_SIZE_1024);

	//Audio
	Audio::LoadAudio(1, L"ピコ！.wav", EFFECT);
	Audio::LoadAudio(2, L"決定音.wav", EFFECT);
	Audio::LoadAudio(3, L"刀剣・斬る01.wav", EFFECT);		//近距離空振り時SE
	Audio::LoadAudio(4, L"刀剣・斬る07.wav", EFFECT);		//近距離ヒット時SE
	Audio::LoadAudio(5, L"手足・殴る、蹴る09.wav", EFFECT);		//ダメージSE
	Audio::LoadAudio(6, L"星・キラーン06.wav", EFFECT);		//星取得時SE
	Audio::LoadAudio(7, L"場面転換・スライド表現04.wav", EFFECT);//ブラックホールでのワープ時SE

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
	CObjTutorial* objtutorialhukidashi = new CObjTutorial(0, 3);
	Objs::InsertObj(objtutorialhukidashi, OBJ_TUTORIAL, 151);
	//チュートリアルオブジェクト作成
	CObjTutorial* objtutorial = new CObjTutorial(1, 3);
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
void CSceneMercuryGemini::Scene()
{
	//水星（ふたご座）で星を14個集めたら次へ移行
	if (g_StarCount == GEMINIMAXSTAR)
	{
		//ふたご座のスキル開放
		g_Gemini = true;
		//ふたご座のクリア表記
		g_Gemini_clear = true;
		g_Gemini_Max = true;

		
		//もし、水星の星座をどちらもクリアしていたら水星をクリア表記
		if (g_Gemini_clear == true && g_Virgo_clear == true)
		{
			g_Mercury_clear = true;
		}


		//星を集めきったら
		if (g_Gemini_Max == true)
		{
			if (Item_cnt >= 1)
			{
				//一回作成されると終了
				;
			}
			else
			{
				//スキルアイテムオブジェクト作成
				CObjSkillItem* objsi = new CObjSkillItem(300, 10);
				Objs::InsertObj(objsi, OBJ_SKILL_ITEM, 300);
				g_Make_Item = true;
				Item_cnt++;
			}
		}
		//スキルアイテムを獲得したら
		if (g_skill_item_flag == true)
		{
			g_skill_item_flag = false;
			g_stage_clear = true;
			ClearCheck(g_stage_clear);
		}

	}

	

}

//クリアチェック
void CSceneMercuryGemini::ClearCheck(bool a)
{
	if (a == true)
	{
		if (m_clear_f == true)
		{
			return;
		}
		else
		{
			//オブジェクト作成
			CObjStageClear* objs = new CObjStageClear();
			Objs::InsertObj(objs, OBJ_STAGECLEAR, 130);
			m_clear_f = true;
		}
	}
}