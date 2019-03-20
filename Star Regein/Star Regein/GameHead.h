#pragma once

//オブジェクトネーム------------------------------
enum OBJ_NAME
{
	OBJ_NO_NAME,	//オブジェクト名無し(禁止)
	//ゲームで使うオブジェクトの名前
	//OBJ_○○と表記
	OBJ_TITLE,
	OBJ_STAGECHOICE,
	OBJ_MESSAGE,
	
	OBJ_MINIMAP,

	OBJ_HERO,
	OBJ_STAGECHOICEHERO,
	OBJ_STAGECLEAR,
	OBJ_BLOCK,
	OBJ_STAR,
	OBJ_STARCHOICE,
	OBJ_METEO,
	OBJ_ASTEROID,
	OBJ_BLACKHOLE,
	OBJ_WHITEHOLE,

	OBJ_COW,

	OBJ_BEAMSABER,

	OBJ_SKILL,

	OBJ_HEART,
	OBJ_MP,
};
//------------------------------------------------

//当たり判定属性----------------------------------
enum HIT_ELEMENTS
{
	ELEMENT_NULL,//属性無し 全ての属性と当たり判定が実行される
	//以下　同じ属性同士では当たり判定は実行されない
	//属性は追加可能だが、デバック時の色は初期設定分しか無い
	ELEMENT_PLAYER,
	ELEMENT_ENEMY,
	ELEMENT_ITEM,
	ELEMENT_MAGIC,
	ELEMENT_FIELD,
	ELEMENT_RED,
	ELEMENT_GREEN,
	ELEMENT_BLUE,
	ELEMENT_BLACK,
	ELEMENT_WHITE,

	ELEMENT_BLOCK,
	ELEMENT_STAR,
	ELEMENT_BEAMSABER,
};
//------------------------------------------------

//------------------------------------------------
//セーブ＆ロードとシーン間のやり取りするデータ
struct UserData
{
	int mSeveData;	//サンプルセーブデータ
	
};
//------------------------------------------------


//ゲーム内で使用されるグローバル変数・定数・列挙--
//定数
#define MAPSIZE 50
#define ALLSIZE 64.0f

//惑星ごとの値
typedef enum Planet
{
	Earth,			//地球			0
	Venus,			//金星			1
	VenusTaurus,	//金星（牡牛座）2
	VenusLibra,		//金星（天秤座）3
	Mercury,		//水星			4
	MercuryGemini,	//水星（双子座）5
	MercuryVirgo,	//水星（乙女座）6
	SunLeo,			//太陽（獅子座）7
}Planet;

extern int g_StarCount;	//星を数える変数
extern float g_posture; //主人公の向き
extern float* g_cow_x[20];//全ての牛のX位置を把握する
extern float* g_cow_y[20];//全ての牛のY位置を把握する

extern float g_hp;     //今のＨＰ
extern float g_max_hp; //最大ＨＰ
extern float g_mp;     //今のＭＰ
extern float g_max_mp; //最大ＭＰ


extern int g_map[MAPSIZE][MAPSIZE]; //ミニマップ情報
extern int g_mapsize;	//マップのサイズ
extern int g_stage;		//今いるステージの値
extern int g_image_right; //スキル画像切り替え
extern int g_image_reft;  //スキル画像切り替え


//------------------------------------------------
//ゲーム内で使用するクラスヘッダ------------------


//------------------------------------------------

//ゲームシーンオブジェクトヘッダ------------------
#include "ObjHero.h"
#include "ObjStageChoiceHero.h"

#include "ObjBlock.h"
#include "ObjStar.h"
#include "ObjMeteo.h"
#include "ObjAsteroid.h"
#include "ObjBlackhole.h"
#include "ObjWhitehole.h"


#include "ObjTitle.h"
#include "ObjStageChoice.h"
#include "ObjStarChoice.h"
#include "ObjStageClear.h"
#include "ObjMessage.h"
#include "ObjMiniMap.h"

#include "ObjHeart.h"
#include "ObjMP.h"
#include "ObjBeamSaber.h"
#include "ObjCow.h"
#include "ObjSkill.h"
//------------------------------------------------

//ゲームシーンクラスヘッダ------------------------
#include "SceneMain.h"
#include "SceneEarth.h"
#include "SceneVenus.h"


#include "SceneTitle.h"
#include "SceneStageChoice.h"
#include "SceneStarChoice.h"
#include "SceneStageClear.h"
//-----------------------------------------------

//シーンスタートクラス---------------------------
//ゲーム開始時のシーンクラス登録
/*
	CSceneEarth		地球
	CSceneVenus		金星

*/
#define SET_GAME_START  CSceneStageChoice
//-----------------------------------------------