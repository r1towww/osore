//STL�f�o�b�O�@�\��OFF�ɂ���
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"
#include"GameL\Audio.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p�w�b�_�[
#include "SceneSunLeo.h"
#include "GameHead.h"

//�R���X�g���N�^
CSceneSunLeo::CSceneSunLeo()

{
	g_StarCount = 0;	//���𐔂���ϐ��̏�����

}

//�f�X�g���N�^
CSceneSunLeo::~CSceneSunLeo()
{


}

//���������\�b�h
void CSceneSunLeo::InitScene()
{
	//�O���f�[�^�ǂݍ��݁i�X�e�[�W���j
	unique_ptr<wchar_t> p;	//�X�e�[�W���|�C���^�[
	int size;				//�X�e�[�W���̑傫��
	p = Save::ExternalDataOpen(L"SunLeo.csv", &size);//�O���f�[�^�ǂݍ���


	int map[MAPSIZE][MAPSIZE];
	int count = 1;

	for (int i = 0; i < MAPSIZE; i++)
	{
		for (int j = 0; j < MAPSIZE; j++)
		{

			int w = 0;
			swscanf_s(&p.get()[count], L"%d", &w);
			map[i][j] = w;
			if (w >= 10)
			{
				count += 1;
			}
			count += 2;
		}
	}

	//�O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"��l��.png", 1, TEX_SIZE_512);
	Draw::LoadImageW(L"�a���A�j���[�V����.png", 2, TEX_SIZE_512);
	Draw::LoadImageW(L"��.png", 3, TEX_SIZE_512);
	Draw::LoadImageW(L"覐�.png", 4, TEX_SIZE_512);
	Draw::LoadImageW(L"SpaceBack.png", 5, TEX_SIZE_1024);
	Draw::LoadImageW(L"�� �G�t�F�N�g����.png", 6, TEX_SIZE_1024);
	Draw::LoadImageW(L"Background.png", 7, TEX_SIZE_2048);
	Draw::LoadImageW(L"�~�j�}�b�v�w�i.png", 8, TEX_SIZE_512);
	Draw::LoadImageW(L"color.png", 9, TEX_SIZE_512);
	Draw::LoadImageW(L"HP.png", 10, TEX_SIZE_2048);
	Draw::LoadImageW(L"MP.png", 11, TEX_SIZE_2048);
	Draw::LoadImageW(L"blackhole.png", 12, TEX_SIZE_256);
	Draw::LoadImageW(L"�e��.png", 16, TEX_SIZE_128);
	Draw::LoadImageW(L"�X�L������.png", 13, TEX_SIZE_2048);
	Draw::LoadImageW(L"�񕜃G�t�F�N�g.png", 14, TEX_SIZE_2048);
	Draw::LoadImageW(L"�_�b�V��.png", 15, TEX_SIZE_1024);

	Draw::LoadImageW(L"box_blue.png", 40, TEX_SIZE_512);
	Draw::LoadImageW(L"box_blue_t.png", 41, TEX_SIZE_512);
	Draw::LoadImageW(L"box_mini.png", 42, TEX_SIZE_512);
	Draw::LoadImageW(L"�n�[�g�e.png", 50, TEX_SIZE_512);
	Draw::LoadImageW(L"���e�A�j���[�V����.png", 51, TEX_SIZE_512);


	//Audio
	Audio::LoadAudio(1, L"�����E�a��01.wav", EFFECT);		//�ߋ�����U�莞SE
	Audio::LoadAudio(2, L"�����E�a��07.wav", EFFECT);		//�ߋ����q�b�g��SE
	Audio::LoadAudio(3, L"�_���[�W��02.wav", EFFECT);		//�_���[�WSE
	Audio::LoadAudio(4, L"���E�L���[��06.wav", EFFECT);		//���擾��SE
	Audio::LoadAudio(5, L"��ʓ]���E�X���C�h�\��04.wav", EFFECT);//�u���b�N�z�[���ł̃��[�v��SE

    //block�I�u�W�F�N�g�쐬
	CObjBlock* objb = new CObjBlock(map);
	Objs::InsertObj(objb, OBJ_BLOCK, 1);

	//MiniMap�I�u�W�F�N�g�쐬
	CObjMiniMap* objminimap = new CObjMiniMap(map);
	Objs::InsertObj(objminimap, OBJ_MINIMAP, 100);

	//���b�Z�[�W�I�u�W�F�N�g�쐬
	CObjMessage* objmes = new CObjMessage();
	Objs::InsertObj(objmes, OBJ_MESSAGE, 120);

	//Status�Q�[�W�I�u�W�F�N�g�쐬
	CObjStatus* objstatus = new CObjStatus();
	Objs::InsertObj(objstatus, OBJ_STATUS, 100);

	//�X�L���؂�ւ��I�u�W�F�N�g�쐬
	CObjSkill* objSkill = new CObjSkill();
	Objs::InsertObj(objSkill, OBJ_SKILL, 150);

	//�`���[�g���A�������o���쐬
	CObjTutorial* objtutorialhukidashi = new CObjTutorial(0, 7);
	Objs::InsertObj(objtutorialhukidashi, OBJ_TUTORIAL, 151);
	//�`���[�g���A���I�u�W�F�N�g�쐬
	CObjTutorial* objtutorial = new CObjTutorial(1, 7);
	Objs::InsertObj(objtutorial, OBJ_TUTORIAL, 170);
	//�`���[�g���A���������̂ݍ쐬
	if (g_tutorial_flag == true)
	{
		//�e�L�X�g�{�b�N�X�I�u�W�F�N�g�쐬
		CObjTextBox* objtextbox = new CObjTextBox();
		Objs::InsertObj(objtextbox, OBJ_TEXTBOX, 160);
	}

}

//���s�����\�b�h
void CSceneSunLeo::Scene()
{
	//���z�Ő���14�W�߂��玟�ֈڍs
	if (g_StarCount == 1)
	{
		g_Leo = true;		//�X�L���i�V�����j���I���ɂ���
		//���q�����N���A�\��
		g_Sun_clear = true;

		Scene::SetScene(new CSceneStageChoice());
	}
}