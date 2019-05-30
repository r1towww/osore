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
#include "SceneED.h"

//�R���X�g���N�^
CSceneED::CSceneED()
{
}

//�f�X�g���N�^
CSceneED::~CSceneED()
{
}

//�Q�[���^�C�g�����������\�b�h
void CSceneED::InitScene()
{
	//�^�C�g���I�u�W�F�N�g�쐬
	CObjED* obj = new CObjED();
	Objs::InsertObj(obj, OBJ_ED, 100);

	//Audio
	Audio::LoadAudio(1, L"�s�R�I.wav", EFFECT);
	Audio::LoadAudio(2, L"���艹.wav", EFFECT);
	Audio::LoadAudio(3, L"�^�C�g��_BGM.wav", SOUND_TYPE::BACK_MUSIC);

	Audio::LoadAudio(19, L"���U���g�X�^�[SE.wav", EFFECT);
	Audio::LoadAudio(20, L"S�����NSE.wav", EFFECT);
	Audio::LoadAudio(21, L"A�����NSE.wav", EFFECT);
	Audio::LoadAudio(22, L"BC�����NSE.wav", EFFECT);
	Audio::LoadAudio(23, L"�X�e�[�W�N���ABGM.wav", SOUND_TYPE::BACK_MUSIC);


	Audio::Start(3);
	//�摜
	Draw::LoadImageW(L"Fadein.png", 1, TEX_SIZE_512);
	Draw::LoadImageW(L"���U���g�X�^�[.png", 70, TEX_SIZE_1024);
	Draw::LoadImageW(L"���U���g�X�^�[�G�t�F�N�g.png", 71, TEX_SIZE_1024);

}

//�Q�[���^�C�g�����s�����\�b�h
void CSceneED::Scene()
{

}
