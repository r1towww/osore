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

}

//�f�X�g���N�^
CSceneStageChoice::~CSceneStageChoice()
{

}

//�Q�[���^�C�g�����������\�b�h
void CSceneStageChoice::InitScene()
{
	Draw::LoadImageW(L"HeroTouka.png", 1, TEX_SIZE_512);
	Draw::LoadImageW(L"�X�e�[�W�w�i1.png", 2, TEX_SIZE_512);
	Draw::LoadImageW(L"�X�e�[�W�I��n��.png", 3, TEX_SIZE_512);
	Draw::LoadImageW(L"�X�e�[�W�I������.png", 4, TEX_SIZE_512);
	Draw::LoadImageW(L"�X�e�[�W�I�𐅐�.png", 5, TEX_SIZE_512);
	Draw::LoadImageW(L"�X�e�[�W�I�𑾗z.png", 6, TEX_SIZE_512);

	//�X�e�[�W�I���I�u�W�F�N�g�쐬
	CObjStageChoice* o = new CObjStageChoice();
	Objs::InsertObj(o, OBJ_STAGECHOICE, 0);

	//�X�e�[�W�I��p�q�[���[�I�u�W�F�N�g�쐬
	ObjStageChoiceHero* oh = new ObjStageChoiceHero(50,500);
	Objs::InsertObj(oh, OBJ_STAGECHOICEHERO, 10);

}

//�Q�[���^�C�g�����s�����\�b�h
void CSceneStageChoice::Scene()
{

}
