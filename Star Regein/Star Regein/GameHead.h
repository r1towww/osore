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

	OBJ_WHITEHOLE,

	OBJ_COW,
	OBJ_TWINS_BLUE,
	OBJ_TWINS_RED,
	OBJ_BLUE_BULLET,
	OBJ_RED_BULLET,
	OBJ_WOMAN,
	OBJ_HOMING_HEART,
	OBJ_LIBRA,

	OBJ_BEAMSABER,

	OBJ_SKILL,
	OBJ_SKILL_LIBRA,
	OBJ_SKILL_GEMINI,
	OBJ_SKILL_VIRGO,

	OBJ_SKILL_TWINS_B,

	OBJ_STATUS,


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
	ELEMENT_BLUE,
	ELEMENT_BLACK,
	ELEMENT_WHITE,

	ELEMENT_BLOCK,
	ELEMENT_STAR,
	ELEMENT_BEAMSABER,
	ELEMENT_SUB,
	ELEMENT_VIRGO_SKILL,
};
//------------------------------------------------

//------------------------------------------------
//�Z�[�u�����[�h�ƃV�[���Ԃ̂���肷��f�[�^
struct UserData
{
	int mSeveData;	//�T���v���Z�[�u�f�[�^
	
};
//------------------------------------------------


//�Q�[�����Ŏg�p�����O���[�o���ϐ��E�萔�E��--
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

extern int g_StarCount;	//���𐔂���ϐ�
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

extern float* g_blackhole_x[10];	//�u���b�N�z�[����X���W��c������
extern float* g_blackhole_y[10];	//�u���b�N�z�[����Y���W��c������
extern float* g_whitehole_x[10];	//�z���C�g�z�[����X���W��c������
extern float* g_whitehole_y[10];	//�z���C�g�z�[����Y���W��c������

extern float g_hp;     //���̂g�o
extern float g_max_hp; //�ő�g�o
extern float g_mp;     //���̂l�o
extern float g_max_mp; //�ő�l�o

extern bool g_key_flag;	//�L�[���͐���t���O

extern bool g_cow_d_flag[20];//���폜�t���O
extern bool g_blue_d_flag[20];//�o�q�i�j�폜�t���O
extern bool g_red_d_flag[20];//�o�q�i�ԁj�폜�t���O
extern bool g_woman_d_flag[20];//�����폜�t���O
extern bool g_libra_d_flag[20];//�V���폜�t���O

extern int g_asteroid;		//�}�b�v�̃����_�����p�ϐ��i���f���j
extern int g_block;			//�}�b�v�̃����_�����p�ϐ��i覐΃u���b�N�j

extern int g_map[MAPSIZE][MAPSIZE]; //�~�j�}�b�v���
extern int g_mapsize;	//�}�b�v�̃T�C�Y
extern int g_stage;		//������X�e�[�W�̒l
extern int g_skill;		//�e�����X�L���̒l

//�e�����̎擾���

extern bool g_Taurus;	//������	
extern bool g_Libra;	//�V����
extern bool g_Gemini;	//�o�q��
extern bool g_Virgo;	//������
extern bool g_Leo;		//���q��

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

extern int g_cow_id[20];//���̎���ID


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

#include "ObjStatus.h"
#include "ObjBeamSaber.h"
#include "ObjSkill.h"

#include "ObjSkillTwinsB.h"
#include "ObjSkillLibra.h"
#include "ObjSkillGemini.h"
#include "ObjSkillVirgo.h"



//------------------------------------------------

//�Q�[���V�[���N���X�w�b�_------------------------
#include "SceneMain.h"
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
//-----------------------------------------------

//�V�[���X�^�[�g�N���X---------------------------
//�Q�[���J�n���̃V�[���N���X�o�^
/*
	CSceneStageChoice	�f���I��
	CSceneEarth			�n��
	CSceneVenusTaurus	�����i�������j
	CSceneVenusLibra	�����i�V�����j
*/
#define SET_GAME_START  CSceneTitle
//-----------------------------------------------