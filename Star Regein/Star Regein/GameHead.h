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

	OBJ_BEAMSABER,

	OBJ_SKILL,

	OBJ_HEART,
	OBJ_MP,
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

#define HEROUP		1
#define HEROLEFT	2
#define HERODOWN	3
#define HERORIGHT	4

//�f�����Ƃ̒l
typedef enum Planet
{
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

//�X�L�����Ƃ̒l
typedef enum Skill
{
	Taurus,		//������		0
	Libra,		//�V����		1
	Gemini,		//�o�q��		2
	Virgo,		//������		3
	Leo,		//���q��		4
	NoSkill,	//�X�L������	5
}Skill;

extern int g_StarCount;	//���𐔂���ϐ�
extern float g_posture; //��l���̌���
extern float* g_cow_x[20];//�S�Ă̋���X�ʒu��c������
extern float* g_cow_y[20];//�S�Ă̋���Y�ʒu��c������
extern float* g_twinsblue_x[20];//�S�Ă̑o�q�i�j��X�ʒu��c������
extern float* g_twinsblue_y[20];//�S�Ă̑o�q�i�j��Y�ʒu��c������
extern float* g_twinsred_x[20];//�S�Ă̑o�q�i�ԁj��X�ʒu��c������
extern float* g_twinsred_y[20];//�S�Ă̑o�q�i�ԁj��Y�ʒu��c������
extern int g_blackhole_cnt; //�u���b�N�z�[���̐����J�E���g

extern float* g_blackhole_x[10];	//�u���b�N�z�[���̈ʒu�z��X
extern float* g_blackhole_y[10];	//�z���C�g�z�[���̈ʒu�z��Y
extern float* g_whitehole_x[10];	//�z���C�g�z�[���̈ʒu�z��X
extern float* g_whitehole_y[10];	//�z���C�g�z�[���̈ʒu�z��Y

extern float g_hp;     //���̂g�o
extern float g_max_hp; //�ő�g�o
extern float g_mp;     //���̂l�o
extern float g_max_mp; //�ő�l�o

extern int g_map[MAPSIZE][MAPSIZE]; //�~�j�}�b�v���
extern int g_mapsize;	//�}�b�v�̃T�C�Y
extern int g_stage;		//������X�e�[�W�̒l
extern int g_skill;		//�X�L�����
extern int g_image_right; //�X�L���摜�؂�ւ�
extern int g_image_reft;  //�X�L���摜�؂�ւ�


//------------------------------------------------
//�Q�[�����Ŏg�p����N���X�w�b�_------------------


//------------------------------------------------

//�Q�[���V�[���I�u�W�F�N�g�w�b�_------------------
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

//�Q�[���V�[���N���X�w�b�_------------------------
#include "SceneMain.h"
#include "SceneEarth.h"
#include "SceneVenusTaurus.h"
#include "SceneVenusLibra.h"

#include "SceneTitle.h"
#include "SceneStageChoice.h"
#include "SceneStarChoice.h"
#include "SceneStageClear.h"
#include "SceneGameOver.h"
//-----------------------------------------------

//�V�[���X�^�[�g�N���X---------------------------
//�Q�[���J�n���̃V�[���N���X�o�^
/*
	CSceneStageChoice �f���I��
	CSceneEarth		�n��
	CSceneVenus		����

*/
#define SET_GAME_START  CSceneStageChoice
//-----------------------------------------------