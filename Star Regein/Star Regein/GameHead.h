#pragma once

//�I�u�W�F�N�g�l�[��------------------------------
enum OBJ_NAME
{
	OBJ_NO_NAME,	//�I�u�W�F�N�g������(�֎~)
	//�Q�[���Ŏg���I�u�W�F�N�g�̖��O
	//OBJ_�����ƕ\�L
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

	OBJ_WHITEHOLE,

	OBJ_PERFORMANCE_ROOM,

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


//�����蔻�葮��----------------------------------
enum HIT_ELEMENTS
{
	ELEMENT_NULL,//�������� �S�Ă̑����Ɠ����蔻�肪���s�����
	//�ȉ��@�����������m�ł͓����蔻��͎��s����Ȃ�
	//�����͒ǉ��\�����A�f�o�b�N���̐F�͏����ݒ蕪��������
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
//�Z�[�u�����[�h�ƃV�[���Ԃ̂���肷��f�[�^
struct UserData
{
	int mSeveData;	//�T���v���Z�[�u�f�[�^
	
};
//------------------------------------------------


//�Q�[�����Ŏg�p�����O���[�o���ϐ��E�萔�E��-------------------------------------------

//�萔
#define MAPSIZE 50
#define ALLSIZE 64.0f

#define TIMELIMIT 50	//�L�[���̓^�C���p�A�Ԋu�ݒ�

//�n�[�g�e�̑��x
#define MOVE 1
	
//��l���̌���
#define HERO_UP		1
#define HERO_LEFT	2
#define HERO_DOWN	3
#define HERO_RIGHT	4

//�A�j���[�V�����p
#define ANITIME 1

//�_�b�V�����x
#define DASH_SPEED 3.0f
//�ʏ푬�x
#define NORMAL_SPEED 1.5f

//�X�L����i�܂���l
#define NEXTSKILL 1

//��l���̈ړ��x�N�g����+�l
#define HERO_VEC    4

//�f�����Ƃ̒l
typedef enum Planet
{	/* �X�e�[�W���Ƃ̒l */
	Earth,			//�n��			0
	EarthStar,		//�n��			1
	Venus,			//����			2
	VenusTaurus,	//�����i�������j3
	VenusLibra,		//�����i�V�����j4
	Mercury,		//����			5
	MercuryGemini,	//�����i�o�q���j6
	MercuryVirgo,	//�����i�������j7
	Sun,			//���z			8
	SunLeo,			//���z�i���q���j9
	Space,			//�X�e�[�W�I��	10
	Performance,	//����			11

}Planet;

typedef enum Skill
{	/* �X�L�����Ƃ̒l */
	NoSkill,	//�X�L������	0
	Taurus,		//������		1
	Libra,		//�V����		2
	Gemini,		//�o�q��		3
	Virgo,		//������		4
	Leo,		//���q��		5

}Skill;

extern float g_stage_px;  //�X�e�[�W�I�����̈ʒuX
extern float g_stage_py;  //�X�e�[�W�I�����̈ʒuY

extern int   g_StarCount;	//���𐔂���ϐ�
extern float g_posture; //��l���̌���
extern float* g_cow_x[20];//�S�Ă̋���X�ʒu��c������
extern float* g_cow_y[20];//�S�Ă̋���Y�ʒu��c������
extern float* g_twinsblue_x[20];//�S�Ă̑o�q�i�j��X�ʒu��c������
extern float* g_twinsblue_y[20];//�S�Ă̑o�q�i�j��Y�ʒu��c������
extern float* g_twinsred_x[20];//�S�Ă̑o�q�i�ԁj��X�ʒu��c������
extern float* g_twinsred_y[20];//�S�Ă̑o�q�i�ԁj��Y�ʒu��c������
extern float* g_woman_x[20];//���ׂẲ�����X�ʒu��c������
extern float* g_woman_y[20];//���ׂẲ�����Y�ʒu��c������
extern float* g_libra_x[20];//���ׂĂ̓V����X�ʒu��c������
extern float* g_libra_y[20];//���ׂĂ̓V����Y�ʒu��c������
extern float* g_leo_x[60];//�S�Ă̎��q��X�ʒu��c������
extern float* g_leo_y[60];//�S�Ă̎��q��Y�ʒu��c������
extern float* g_boss_x;//�{�X��X�ʒu��c������
extern float* g_boss_y;//�{�X��Y�ʒu��c������
extern float* g_snake_x[20];//�ւ�X�ʒu��c������
extern float* g_snake_y[20];//�ւ�Y�ʒu��c������
extern float g_star_x[5];
extern float g_star_y[5];

extern float* g_blackhole_x[10];	//�u���b�N�z�[����X���W��c������
extern float* g_blackhole_y[10];	//�u���b�N�z�[����Y���W��c������
extern float* g_whitehole_x[10];	//�z���C�g�z�[����X���W��c������
extern float* g_whitehole_y[10];	//�z���C�g�z�[����Y���W��c������
extern int    g_blackhole_cnt;		//�u���b�N�z�[���̃J�E���g�p
extern int    g_whitehole_cnt;
extern float  g_hp;     //���̂g�o
extern float  g_max_hp; //�ő�g�o
extern float  g_mp;     //���̂l�o
extern float  g_max_mp; //�ő�l�o
extern int    g_attack_power;	//��l���̍U����


extern bool g_key_flag;	//�L�[���͐���t���O
extern bool g_gemini_move;//�o�q���u���b�N�z�[���ړ�


extern bool g_cow_d_flag[20];//���폜�t���O
extern bool g_blue_d_flag[20];//�o�q�i�j�폜�t���O
extern bool g_red_d_flag[20];//�o�q�i�ԁj�폜�t���O
extern bool g_woman_d_flag[20];//�����폜�t���O
extern bool g_libra_d_flag[20];//�V���폜�t���O
extern bool g_leo_d_flag[60];//���q�폜�t���O
extern bool g_boss_d_flag;//�{�X�폜�t���O
extern bool g_snake_d_flag[20];//�֍폜�t���O

extern int g_asteroid;		//�}�b�v�̃����_�����p�ϐ��i���f���j
extern int g_block;			//�}�b�v�̃����_�����p�ϐ��i覐΃u���b�N�j

extern int g_map[MAPSIZE][MAPSIZE]; //�~�j�}�b�v���
extern int g_mapsize;	   //�}�b�v�̃T�C�Y
extern int g_stage;		   //������X�e�[�W�̒l
extern int g_skill;		   //�e�����X�L���̒l

extern bool g_gemini_check;       //�T�u�@�̐����ׂ̈̒l
extern bool g_gemini_bullet_check;//�o�q���X�L���e��
extern bool g_geminiattck_check;  //�o�q���X�L���e�ې���
extern bool g_gemini_check;       //�T�u�@�̒e�ې����ׂ̈̒l
extern bool g_skill_item_flag;    //�X�L���A�C�e�������t���O

extern float  g_Leo_cnt;//���q���X�^���J�E���g
extern bool g_stan_cow_flag[20];//�X�^�����ʔF���p
extern bool g_stan_blue_flag[20];//�X�^���o�q�i�j�ʔF���p
extern bool g_stan_red_flag[20];//�X�^���o�q�i�ԁj�ʔF���p
extern bool g_stan_woman_flag[20];//�X�^�������ʔF���p
extern bool g_stan_libra_flag[20];//�X�^���V���ʔF���p
extern bool g_stan_leo_flag[60];//�X�^�����q�ʔF���p
extern bool g_stan_boss_flag;//�X�^���{�X�p
extern bool g_stan_snake_flag[20];//�X�^���֌ʔF���p
extern bool g_move_libra_flag[20];//�V�������������߂̂���

//�e�����̎擾���
extern bool g_stage_clear;

extern bool g_Taurus;	//������	
extern bool g_Libra;	//�V����
extern bool g_Gemini;	//�o�q��
extern bool g_Virgo;	//������
extern bool g_Leo;		//���q��

extern bool g_contact_star_f[5];//��l�����ڐG���Ă��鐯�̊m�F�t���O

//�e�f���E�����̃N���A��
extern bool g_Earth_clear;	//�n��	
extern bool g_Venus_clear;	//����
extern bool g_Mercury_clear;	//����
extern bool g_Sun_clear;	//���z

extern bool g_Taurus_clear;	//������	
extern bool g_Libra_clear;	//�V����
extern bool g_Gemini_clear;	//�o�q��
extern bool g_Virgo_clear;	//������
extern bool g_Leo_clear;	//���q��

extern bool g_tutorial_flag;//�`���[�g���A���̕\������p
extern bool g_tutorial_next_flag;//�`���[�g���A���̃y�[�W����p
extern bool g_move_stop_flag;//��l���̑��쐧��p�t���O

//�e�����̐����W�߂��������ǂ���
extern bool g_Earth_Max; 
extern bool g_Taurus_Max;
extern bool g_Libra_Max;
extern bool g_Gemini_Max;
extern bool g_Virgo_Max;
extern bool g_Leo_Max;

extern bool g_Make_Item;//�A�C�e�����������ꂽ���ǂ���

extern int g_enemy_cnt;	//�G�̑����̃J�E���g�p
extern int g_kill_cnt;	//�G��|������
extern bool g_no_damage;	//�U�����󂯂����ǂ����̃t���O

extern int g_cow_id[20];//���̎���ID

extern bool g_hero_hit;

extern bool g_Boss_Spawn;
/*���ђB����*/
//�V�������т����������Ƃ�----------
extern bool g_new_Performance;
//�G�����ׂē|����------------------
extern bool g_Taurus_Enemy_AllKill;	
extern bool g_Libra_Enemy_AllKill;
extern bool g_Gemini_Enemy_AllKill;
extern bool g_Viego_Enemy_AllKill;
extern bool g_Leo_Enemy_AllKill;
//�m�[�_���[�W�N���A----------------
extern bool g_Taurus_NoDamage_Clear;
extern bool g_Libra_NoDamage_Clear;
extern bool g_Gemini_NoDamage_Clear;
extern bool g_Viego_NoDamage_Clear;
extern bool g_Leo_NoDamage_Clear;
//���̑�
extern int g_All_Killcnt;
extern int g_Death_cnt;
extern int g_Taurus_Grade;
extern int g_Libra_Grade;
extern int g_Gemini_Grade;
extern int g_Viego_Grade;
extern int g_Leo_Grade;

//�V�[�N���b�g�n
extern bool g_Tutorial_Clear; //�`���[�g���A���N���A
extern bool g_Earth_BossKill; //���X�{�X��|����
extern bool g_All_Skill_Get;  //���ׂẴX�L�����l��


//------------------------------------------------
//�Q�[�����Ŏg�p����N���X�w�b�_------------------


//------------------------------------------------

//�Q�[���V�[���I�u�W�F�N�g�w�b�_------------------
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

#include "ObjBlock.h"
#include "ObjStar.h"
#include "ObjMeteo.h"
#include "ObjAsteroid.h"
#include "ObjBlackhole.h"
#include "ObjWhitehole.h"
#include "ObjBreakRock.h"
#include "ObjBreakBigRock.h"

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

//�Q�[���V�[���N���X�w�b�_------------------------
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

//�V�[���X�^�[�g�N���X---------------------------
//�Q�[���J�n���̃V�[���N���X�o�^
/*
	CSceneStageChoice	�f���I��
	CSceneEarth			�n��
	CSceneVenusTaurus	�����i�������j
	CSceneVenusLibra	�����i�V�����j
	CSceneMercuryGemini	�����i�o�q���j
	CSceneMercuryVirgo	�����i�������j
	CSceneSunLeo		���z�i���q���j

*/
#define SET_GAME_START  CSceneTitle
//-----------------------------------------------