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
#include "SceneStarChoice.h"

//�R���X�g���N�^
CSceneStarChoice::CSceneStarChoice()
{

}

//�f�X�g���N�^
CSceneStarChoice::~CSceneStarChoice()
{

}

//�Q�[���^�C�g�����������\�b�h
void CSceneStarChoice::InitScene()
{
	Draw::LoadImageW(L"�X�L������.png", 1, TEX_SIZE_2048);
	Draw::LoadImageW(L"�V���X�L��.png", 2, TEX_SIZE_512);

	//�X�e�[�W�I���I�u�W�F�N�g�쐬
	CObjStarChoice* o = new CObjStarChoice();
	Objs::InsertObj(o, OBJ_STARCHOICE, 0);

	////�X�e�[�W�I��p�q�[���[�I�u�W�F�N�g�쐬
	//ObjStageChoiceHero* oh = new ObjStageChoiceHero(50, 500);
	//Objs::InsertObj(oh, OBJ_STAGECHOICEHERO, 10);

}

//�Q�[���^�C�g�����s�����\�b�h
void CSceneStarChoice::Scene()
{

}
