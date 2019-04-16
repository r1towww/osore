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
	OBJ_TUTORIAL,
	OBJ_TEXTBOX,
	OBJ_GAMEOVER,
	OBJ_BLOCK,
	OBJ_STAR,
	OBJ_STARCHOICE,
	OBJ_METEO,
	OBJ_ASTEROID,
	OBJ_BLACKHOLE,
	OBJ_BLACKHOLE2,
	OBJ_BLACKHOLE3,
	OBJ_BLACKHOLE4,

	OBJ_WHITEHOLE,

	OBJ_COW,
	OBJ_TWINS_BLUE,
	OBJ_TWINS_RED,
	OBJ_BLUE_BULLET,
	OBJ_RED_BULLET,

	OBJ_BEAMSABER,

	OBJ_SKILL,
	OBJ_SKILL_GEMINI,

	OBJ_SKILL_TWINS_B,

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

#define TIMELIMIT 50	//キー入力タイム用、間隔設定
	
//主人公の向き
#define HERO_UP		1
#define HERO_LEFT	2
#define HERO_DOWN	3
#define HERO_RIGHT	4

//惑星ごとの値
typedef enum Planet
{	/* ステージごとの値 */
	Earth,			//地球			0
	EarthStar,		//地球			1
	Venus,			//金星			2
	VenusTaurus,	//金星（牡牛座）3
	VenusLibra,		//金星（天秤座）4
	Mercury,		//水星			5
	MercuryGemini,	//水星（双子座）6
	MercuryVirgo,	//水星（乙女座）7
	Sun,			//太陽			8
	SunLeo,			//太陽（獅子座）9
	Space,			//ステージ選択	10

}Planet;

typedef enum Skill
{	/* スキルごとの値 */
	NoSkill,	//スキル無し	0
	Taurus,		//牡牛座		1
	Libra,		//天秤座		2
	Gemini,		//双子座		3
	Virgo,		//乙女座		4
	Leo,		//獅子座		5

}Skill;


extern float g_stage_px;  //ステージ選択時の位置X
extern float g_stage_py;  //ステージ選択時の位置Y

extern int g_StarCount;	//星を数える変数
extern float g_posture; //主人公の向き
extern float* g_cow_x[20];//全ての牛のX位置を把握する
extern float* g_cow_y[20];//全ての牛のY位置を把握する
extern float* g_twinsblue_x[20];//全ての双子（青）のX位置を把握する
extern float* g_twinsblue_y[20];//全ての双子（青）のY位置を把握する
extern float* g_twinsred_x[20];//全ての双子（赤）のX位置を把握する
extern float* g_twinsred_y[20];//全ての双子（赤）のY位置を把握する

extern float* g_blackhole_x[10];	//ブラックホールのX座標を把握する
extern float* g_blackhole_y[10];	//ブラックホールのY座標を把握する
extern float* g_whitehole_x[10];	//ホワイトホールのX座標を把握する
extern float* g_whitehole_y[10];	//ホワイトホールのY座標を把握する
extern int g_blackholecnt;	//ブラックホールカウント用

extern float g_hp;     //今のＨＰ
extern float g_max_hp; //最大ＨＰ
extern float g_mp;     //今のＭＰ
extern float g_max_mp; //最大ＭＰ

extern bool g_key_flag;	//キー入力制御フラグ

extern int g_asteroid;		//マップのランダム化用変数（小惑星）
extern int g_block;			//マップのランダム化用変数（隕石ブロック）

extern int g_map[MAPSIZE][MAPSIZE]; //ミニマップ情報
extern int g_mapsize;	//マップのサイズ
extern int g_stage;		//今いるステージの値
extern int g_skill;		//各星座スキルの値

//各星座の取得情報
extern bool g_Taurus;	//牡牛座	
extern bool g_Libra;	//天秤座
extern bool g_Gemini;	//双子座
extern bool g_Virgo;	//乙女座
extern bool g_Leo;		//獅子座

//各惑星・星座のクリア状況
extern bool g_Earth_clear;	//地球	
extern bool g_Venus_clear;	//金星
extern bool g_Mercury_clear;	//水星
extern bool g_Sun_clear;	//太陽

extern bool g_Taurus_clear;	//牡牛座	
extern bool g_Libra_clear;	//天秤座
extern bool g_Gemini_clear;	//双子座
extern bool g_Virgo_clear;	//乙女座
extern bool g_Leo_clear;	//獅子座

extern bool g_tutorial_flag;//チュートリアルの表示制御用

extern bool g_attack_flag; //攻撃アニメーションフラグ
extern int g_slash_time;
extern int g_slash_frame;
extern int g_cow_id[20];//牛の識別ID


//------------------------------------------------
//ゲーム内で使用するクラスヘッダ------------------


//------------------------------------------------

//ゲームシーンオブジェクトヘッダ------------------
#include "ObjHero.h"
#include "ObjStageChoiceHero.h"
#include "ObjCow.h"
#include "Objtwinsblue.h"
#include "Objtwinsred.h"
#include "ObjBlueBullet.h"
#include "ObjRedBullet.h"

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
#include "ObjTutorial.h"
#include "ObjTextBox.h"
#include "ObjGameOver.h"
#include "ObjMessage.h"
#include "ObjMiniMap.h"

#include "ObjHeart.h"
#include "ObjMP.h"
#include "ObjBeamSaber.h"
#include "ObjSkill.h"

#include "ObjSkillTwinsB.h"
#include "ObjSkillLibra.h"
#include "ObjSkillGemini.h"

//------------------------------------------------

//ゲームシーンクラスヘッダ------------------------
#include "SceneMain.h"
#include "SceneEarth.h"
#include "SceneVenusTaurus.h"
#include "SceneVenusLibra.h"
#include "SceneMercuryGemini.h"


#include "SceneTitle.h"
#include "SceneStageChoice.h"
#include "SceneStageClear.h"
#include "SceneGameOver.h"
//-----------------------------------------------

//シーンスタートクラス---------------------------
//ゲーム開始時のシーンクラス登録
/*
	CSceneStageChoice	惑星選択
	CSceneEarth			地球
	CSceneVenusTaurus	金星（牡牛座）
	CSceneVenusLibra	金星（天秤座）
*/
#define SET_GAME_START  CSceneStageChoice
//-----------------------------------------------