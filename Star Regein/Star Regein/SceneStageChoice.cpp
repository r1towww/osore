//STL�f�o�b�O�@�\��OFF�ɂ���
#define _SECURE_SCL	(0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL/DrawTexture.h"
#include "GameL\Audio.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p�w�b�_�[
#include "GameHead.h"
#include "SceneStageChoice.h"

//�R���X�g���N�^
CSceneStageChoice::CSceneStageChoice()
{
	g_hp = g_max_hp;	//hp���ő�hp�ŏ�����
	g_skill = NoSkill;	//�X�L���̒l���������ŏ�����
	g_blackhole_cnt = 0;//�u���b�N�z�[���̃J�E���g�̏�����
}

//�f�X�g���N�^
CSceneStageChoice::~CSceneStageChoice()
{

}

//�Q�[���^�C�g�����������\�b�h
void CSceneStageChoice::InitScene()
{
	Draw::LoadImageW(L"��l��.png", 1, TEX_SIZE_512);
	Draw::LoadImageW(L"�X�e�[�W�w�i1.png", 2, TEX_SIZE_512);
	Draw::LoadImageW(L"�X�e�[�W�I��n��.png", 3, TEX_SIZE_512);
	Draw::LoadImageW(L"�X�e�[�W�I������.png", 4, TEX_SIZE_512);
	Draw::LoadImageW(L"�X�e�[�W�I�𐅐�.png", 5, TEX_SIZE_512);
	Draw::LoadImageW(L"�X�e�[�W�I�𑾗z.png", 6, TEX_SIZE_512);
	Draw::LoadImageW(L"�f��.png", 8, TEX_SIZE_512);
	Draw::LoadImageW(L"���������G����.png", 7, TEX_SIZE_1024);


	//Audio
	Audio::LoadAudio(1, L"�s�R�I.wav", EFFECT);
	Audio::LoadAudio(2, L"���艹.wav", EFFECT);

	Audio::LoadAudio(3, L"�X�e�[�W�I��_BGM.wav", SOUND_TYPE::BACK_MUSIC);

	Audio::Start(3);
	//�X�e�[�W�I���I�u�W�F�N�g�쐬
	CObjStageChoice* o = new CObjStageChoice();
	Objs::InsertObj(o, OBJ_STAGECHOICE, 0);
	
	//�X�e�[�W�I��p�q�[���[�I�u�W�F�N�g�쐬
	ObjStageChoiceHero* oh = new ObjStageChoiceHero(g_stage_px,g_stage_py);
	Objs::InsertObj(oh, OBJ_STAGECHOICEHERO, 10);

	//�X�e�[�W�I��(����)�I�u�W�F�N�g�쐬
	CObjStarChoice* star = new CObjStarChoice();
	Objs::InsertObj(star, OBJ_STARCHOICE, 20);
}

//�Q�[���^�C�g�����s�����\�b�h
void CSceneStageChoice::Scene()
{

}
