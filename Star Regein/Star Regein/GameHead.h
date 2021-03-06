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
	OBJ_BREAK_ROCK,
	OBJ_BREAK_BIGROCK,

	OBJ_FADE_IN,

	OBJ_WHITEHOLE,

	OBJ_PERFORMANCE_ROOM,

	OBJ_WORNING,

	OBJ_COW,
	OBJ_TWINS_BLUE,
	OBJ_TWINS_RED,
	OBJ_BLUE_BULLET,
	OBJ_RED_BULLET,
	OBJ_WOMAN,
	OBJ_HOMING_HEART,
	OBJ_LIBRA,
	OBJ_LEO,
	OBJ_BOSS,
	OBJ_BEAM,
	OBJ_SNAKE,
	OBJ_POISON,

	OBJ_MENU,
	OBJ_HELP,
	OBJ_BEAMSABER,
	OBJ_ED,

	OBJ_SKILL,
	OBJ_SKILL_LIBRA,
	OBJ_SKILL_GEMINI,
	OBJ_SKILL_GEMINIB,
	OBJ_SKILL_VIRGO,
	OBJ_SKILL_LEO,

	OBJ_SKILL_TWINS_B,

	OBJ_SKILL_BULLET,

	OBJ_STATUS,
	OBJ_SKILL_ITEM,


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
	cc,
	ELEMENT_BLACK,
	ELEMENT_WHITE,

	ELEMENT_BLOCK,
	ELEMENT_STAR,
	ELEMENT_BEAMSABER,
	ELEMENT_SUB,
	ELEMENT_SKILL_VIRGO,
	ELEMENT_SKILL_LEO,

	ELEMENT_SKILL_ITEM,
};
//------------------------------------------------

//------------------------------------------------
//セーブ＆ロードとシーン間のやり取りするデータ
struct UserData
{
	int mSeveData;	//サンプルセーブデータ
	
};
//------------------------------------------------


//ゲーム内で使用されるグローバル変数・定数・列挙-------------------------------------------

//定数
#define MAPSIZE 50
#define ALLSIZE 64.0f

#define TIMELIMIT 50	//キー入力タイム用、間隔設定

//ハート弾の速度
#define MOVE 1
	
//主人公の向き
#define HERO_UP		1
#define HERO_LEFT	2
#define HERO_DOWN	3
#define HERO_RIGHT	4

//アニメーション用
#define ANITIME 1

//ダッシュ速度
#define DASH_SPEED 3.0f
//通常速度
#define NORMAL_SPEED 1.5f

//スキルを進ませる値
#define NEXTSKILL 1

//主人公の移動ベクトルの+値
#define HERO_VEC    4

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
	Performance,	//実績			11

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

typedef enum Rank
{/*各惑星ランク保存用*/
	None,
	C,
	B,
	A,
	S,
}Rank;

extern int   g_StarCount;	//星を数える変数
extern float g_posture; //主人公の向き

//各キャラ位置管理--------------------------
extern float g_stage_px;  //ステージ選択時の位置X
extern float g_stage_py;  //ステージ選択時の位置Y

extern float* g_cow_x[20];//全ての牛のX位置を把握する
extern float* g_cow_y[20];//全ての牛のY位置を把握する
extern float* g_twinsblue_x[20];//全ての双子（青）のX位置を把握する
extern float* g_twinsblue_y[20];//全ての双子（青）のY位置を把握する
extern float* g_twinsred_x[20];//全ての双子（赤）のX位置を把握する
extern float* g_twinsred_y[20];//全ての双子（赤）のY位置を把握する
extern float* g_woman_x[20];//すべての乙女のX位置を把握する
extern float* g_woman_y[20];//すべての乙女のY位置を把握する
extern float* g_libra_x[20];//すべての天秤のX位置を把握する
extern float* g_libra_y[20];//すべての天秤のY位置を把握する
extern float* g_leo_x[60];//全ての獅子のX位置を把握する
extern float* g_leo_y[60];//全ての獅子のY位置を把握する
extern float* g_boss_x;//ボスのX位置を把握する
extern float* g_boss_y;//ボスのY位置を把握する
extern float* g_snake_x[20];//蛇のX位置を把握する
extern float* g_snake_y[20];//蛇のY位置を把握する
extern float g_star_x[5];
extern float g_star_y[5];

extern float* g_blackhole_x[10];	//ブラックホールのX座標を把握する
extern float* g_blackhole_y[10];	//ブラックホールのY座標を把握する
extern float* g_whitehole_x[10];	//ホワイトホールのX座標を把握する
extern float* g_whitehole_y[10];	//ホワイトホールのY座標を把握する

extern int    g_blackhole_cnt;		//ブラックホールのカウント用
extern int    g_whitehole_cnt;

extern bool g_gemini_move;//双子座ブラックホール移動

//主人公ステータス管理-------------------
extern float  g_hp;     //今のＨＰ
extern float  g_max_hp; //最大ＨＰ
extern float  g_mp;     //今のＭＰ
extern float  g_max_mp; //最大ＭＰ
extern int    g_attack_power;	//主人公の攻撃力

extern bool g_key_flag;	//キー入力制御フラグ

extern int g_stage;		   //今いるステージの値
extern int g_skill;		   //各星座スキルの値

//ミニマップ用敵生存確認------------------
extern bool g_cow_d_flag[20];//牛削除フラグ
extern bool g_blue_d_flag[20];//双子（青）削除フラグ
extern bool g_red_d_flag[20];//双子（赤）削除フラグ
extern bool g_woman_d_flag[20];//乙女削除フラグ
extern bool g_libra_d_flag[20];//天秤削除フラグ
extern bool g_leo_d_flag[60];//獅子削除フラグ
extern bool g_boss_d_flag;//ボス削除フラグ
extern bool g_snake_d_flag[20];//蛇削除フラグ

//敵スタン管理-----------------------
extern float  g_Leo_cnt;//獅子座スタンカウント
extern bool g_stan_cow_flag[20];//スタン牛個別認識用
extern bool g_stan_blue_flag[20];//スタン双子（青）個別認識用
extern bool g_stan_red_flag[20];//スタン双子（赤）個別認識用
extern bool g_stan_woman_flag[20];//スタン乙女個別認識用
extern bool g_stan_libra_flag[20];//スタン天秤個別認識用
extern bool g_stan_leo_flag[60];//スタン獅子個別認識用
extern bool g_stan_boss_flag;//スタンボス用
extern bool g_stan_snake_flag[20];//スタン蛇個別認識用
extern bool g_move_libra_flag[20];//天秤座動かすためのもの

extern int g_asteroid;		//マップのランダム化用変数（小惑星）
extern int g_block;			//マップのランダム化用変数（隕石ブロック）

extern int g_map[MAPSIZE][MAPSIZE]; //ミニマップ情報
extern int g_mapsize;	   //マップのサイズ

//スキル関連--------------------
extern bool g_gemini_check;       //サブ機の生成の為の値
extern bool g_gemini_bullet_check;//双子座スキル弾丸
extern bool g_geminiattck_check;  //双子座スキル弾丸制御
extern bool g_gemini_check;       //サブ機の弾丸生成の為の値
extern bool g_skill_item_flag;    //スキルアイテム所持フラグ

//各星座の取得情報
extern bool g_stage_clear;

extern bool g_Taurus;	//牡牛座	
extern bool g_Libra;	//天秤座
extern bool g_Gemini;	//双子座
extern bool g_Virgo;	//乙女座
extern bool g_Leo;		//獅子座

extern bool g_contact_star_f[5];//主人公が接触している星の確認フラグ

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

//チュートリアル制御
extern bool g_tutorial_flag;//チュートリアルの表示制御用
extern bool g_tutorial_next_flag;//チュートリアルのページ制御用
extern bool g_move_stop_flag;//主人公の操作制御用フラグ

//各星座の星を集めきったかどうか
extern bool g_Earth_Max; 
extern bool g_Taurus_Max;
extern bool g_Libra_Max;
extern bool g_Gemini_Max;
extern bool g_Virgo_Max;
extern bool g_Leo_Max;

extern bool g_Make_Item;//アイテムが生成されたかどうか

extern float g_enemy_cnt;	//敵の総数のカウント用
extern float g_kill_cnt;	//敵を倒した数
extern bool g_no_damage;	//攻撃を受けたかどうかのフラグ

extern bool g_hero_hit;

//ボス管理----------------
extern bool g_Boss_Spawn;
extern bool g_dead_flag;  //ボスが死んだかどうかのフラグ
extern bool g_Voice_flag; //ボス撃破後の天の声フラグ
extern bool g_End_flag;   //天の声が終わったかどうかのフラグ
extern bool g_last_key_f;//ボス討伐後の主人公制御

extern float g_boss_hp;//ボスHP

extern bool g_beam_f;
extern int g_count;//ボスイベント回数制御
/*実績達成状況*/
//新しく実績を解除したとき----------
extern bool g_new_Performance;
//敵をすべて倒した------------------
extern bool g_Taurus_Enemy_AllKill;	
extern bool g_Libra_Enemy_AllKill;
extern bool g_Gemini_Enemy_AllKill;
extern bool g_Viego_Enemy_AllKill;
extern bool g_Leo_Enemy_AllKill;
//ノーダメージクリア----------------
extern bool g_Taurus_NoDamage_Clear;
extern bool g_Libra_NoDamage_Clear;
extern bool g_Gemini_NoDamage_Clear;
extern bool g_Viego_NoDamage_Clear;
extern bool g_Leo_NoDamage_Clear;
//その他
extern int g_All_Killcnt;
extern int g_Death_cnt;
//各星座ランク読み込み用
extern int g_Taurus_Grade;
extern int g_Libra_Grade;
extern int g_Gemini_Grade;
extern int g_Viego_Grade;
extern int g_Leo_Grade;
//シークレット系
extern bool g_Tutorial_Clear; //チュートリアルクリア
extern bool g_Earth_BossKill; //ラスボスを倒した
extern bool g_All_Skill_Get;  //すべてのスキルを獲得
extern int g_TRank;		//ランク管理用
extern int g_LiRank;		//ランク管理用
extern int g_GRank;		//ランク管理用
extern int g_VRank;		//ランク管理用
extern int g_LeRank;		//ランク管理用

//タイムカウント用
extern int g_second;		//秒
extern int g_minute;		//分

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
#include "ObjWoman.h"
#include "ObjHomingHeart.h"
#include "ObjLibra.h"
#include "ObjLeo.h"
#include "ObjBoss.h"
#include "ObjBeam.h"
#include "ObjSnake.h"
#include "ObjPoison.h"
#include "ObjFadein.h"

#include "ObjBlock.h"
#include "ObjStar.h"
#include "ObjMeteo.h"
#include "ObjAsteroid.h"
#include "ObjBlackhole.h"
#include "ObjWhitehole.h"
#include "ObjBreakRock.h"
#include "ObjBreakBigRock.h"
#include "ObjWorning.h"

#include "ObjPerformanceRoom.h"
#include "ObjTitle.h"
#include "ObjStageChoice.h"
#include "ObjStarChoice.h"
#include "ObjStageClear.h"
#include "ObjTutorial.h"
#include "ObjTextBox.h"
#include "ObjGameOver.h"
#include "ObjMessage.h"
#include "ObjMiniMap.h"
#include "ObjHelp.h"
#include "ObjMenu.h"
#include "ObjED.h"

#include "ObjStatus.h"
#include "ObjBeamSaber.h"
#include "ObjSkill.h"

#include "ObjSkillLibra.h"
#include "ObjSkillGemini.h"
#include "ObjskillgeminiB.h"
#include "ObjSkillVirgo.h"
#include "ObjSkillBullet.h"
#include "ObjSkillLeo.h"

#include "ObjSkillItem.h"
//------------------------------------------------

//ゲームシーンクラスヘッダ------------------------
#include "SceneEarth.h"
#include "SceneVenusTaurus.h"
#include "SceneVenusLibra.h"
#include "SceneMercuryGemini.h"
#include "SceneMercuryVirgo.h"
#include "SceneSunLeo.h"


#include "SceneTitle.h"
#include "SceneStageChoice.h"
#include "SceneStageClear.h"
#include "SceneGameOver.h"
#include "SceneED.h"
//-----------------------------------------------

//シーンスタートクラス---------------------------
//ゲーム開始時のシーンクラス登録
/*
	CSceneStageChoice	惑星選択
	CSceneEarth			地球
	CSceneVenusTaurus	金星（牡牛座）
	CSceneVenusLibra	金星（天秤座）
	CSceneMercuryGemini	水星（双子座）
	CSceneMercuryVirgo	水星（乙女座）
	CSceneSunLeo		太陽（獅子座）

*/
#define SET_GAME_START  CSceneTitle
//-----------------------------------------------