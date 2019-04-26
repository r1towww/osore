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

int g_StarCount = 0;	//���𐔂���ϐ��̏�����
bool g_skill_item_flag;
bool g_Make_Item;

bool g_stage_clear = false;
//�g�p�w�b�_�[
#include "SceneEarth.h"
#include "GameHead.h"

//�R���X�g���N�^
CSceneEarth::CSceneEarth()
{
	g_StarCount = 0;
	Item_cnt = 0.0f;
	g_skill_item_flag = false;
	g_Make_Item = false;
	cnt = 0;
}

//�f�X�g���N�^
CSceneEarth::~CSceneEarth()
{

}

//���������\�b�h
void CSceneEarth::InitScene()
{
	//�O���f�[�^�ǂݍ��݁i�X�e�[�W���j
	unique_ptr<wchar_t> p;	//�X�e�[�W���|�C���^�[
	int size;				//�X�e�[�W���̑傫��
	p = Save::ExternalDataOpen(L"Earth.csv", &size);//�O���f�[�^�ǂݍ���

	int map[50][50];
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
	Draw::LoadImageW(L"��l���a���A�j���[�V����.png", 2, TEX_SIZE_512);

	Draw::LoadImageW(L"�V�����X�L���G�t�F�N�g.png", 14, TEX_SIZE_2048);
	Draw::LoadImageW(L"�_�b�V��.png", 15, TEX_SIZE_1024);
	Draw::LoadImageW(L"��ӂ��G�t�F�N�g.png", 17, TEX_SIZE_2048);
	Draw::LoadImageW(L"�n�[�g�e.png", 50, TEX_SIZE_512);
	Draw::LoadImageW(L"���e�A�j���[�V����.png", 51, TEX_SIZE_512);
	Draw::LoadImageW(L"���q���X�L���G�t�F�N�g.png", 23, TEX_SIZE_512);

	Draw::LoadImageW(L"覐�.png", 4, TEX_SIZE_64);
	Draw::LoadImageW(L"�� �G�t�F�N�g����.png", 6, TEX_SIZE_2048);

	Draw::LoadImageW(L"�X�e�[�W�N���A�摜_�n��.png", 16, TEX_SIZE_1024);

	Draw::LoadImageW(L"�F���w�i.png", 5, TEX_SIZE_1024);
	Draw::LoadImageW(L"���������G����.png", 13, TEX_SIZE_1024);

	Draw::LoadImageW(L"�~�j�}�b�v�g.png", 7, TEX_SIZE_2048);
	Draw::LoadImageW(L"�~�j�}�b�v�w�i.png", 8, TEX_SIZE_512);
	Draw::LoadImageW(L"�~�j�}�b�v�e��_.png", 9, TEX_SIZE_512);
	Draw::LoadImageW(L"HP.png", 10, TEX_SIZE_2048);
	Draw::LoadImageW(L"���������G����.png", 13, TEX_SIZE_1024);
	Draw::LoadImageW(L"�_�b�V��.png", 15, TEX_SIZE_1024);
	

	//Draw::LoadImageW(L"�L���L��.png", 16, TEX_SIZE_1024);


	Draw::LoadImageW(L"�e�L�X�g�{�b�N�X .png", 40, TEX_SIZE_512);
	Draw::LoadImageW(L"�e�L�X�g�{�b�N�X ����.png", 41, TEX_SIZE_512);
	Draw::LoadImageW(L"���O�p�g.png", 42, TEX_SIZE_512);


	//Audio
	Audio::LoadAudio(1, L"�s�R�I.wav", EFFECT);
	Audio::LoadAudio(2, L"���艹.wav", EFFECT);
	Audio::LoadAudio(3, L"�����E�a��01.wav", EFFECT);		//�ߋ�����U�莞SE
	Audio::LoadAudio(4, L"�����E�a��07.wav", EFFECT);		//�ߋ����q�b�g��SE
	Audio::LoadAudio(5, L"�葫�E����A�R��09.wav", EFFECT);		//�_���[�WSE
	Audio::LoadAudio(6, L"���E�L���[��06.wav", EFFECT);		//���擾��SE
	Audio::LoadAudio(7, L"��ʓ]���E�X���C�h�\��04.wav", EFFECT);//�u���b�N�z�[���ł̃��[�v��SE

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
	CObjTutorial* objtutorialhukidashi = new CObjTutorial(0, 5);
	Objs::InsertObj(objtutorialhukidashi, OBJ_TUTORIAL, 151);
	//�`���[�g���A���I�u�W�F�N�g�쐬
	CObjTutorial* objtutorial = new CObjTutorial(1, 5);
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
void CSceneEarth::Scene()
{

	//�e�X�g�i�n���Ő���5�W�߂��玟�ֈڍs�j
	if (g_StarCount == EARTHMAXSTAR)
	{

		g_Earth_clear = true;

		//�����W�߂���ƃI��
		g_Earth_Max = true;
	

		if (g_Earth_Max == true)
		{
			if (Item_cnt >= 1)
			{
				//���쐬�����ƏI��
				;
			}
			else
			{
				//�X�L���A�C�e���I�u�W�F�N�g�쐬
				CObjSkillItem* objsi = new CObjSkillItem(300, 10);
				Objs::InsertObj(objsi, OBJ_SKILL_ITEM, 300);
				g_Make_Item = true;
				Item_cnt++;
				
			}
		}

		//�X�L���A�C�e�����l��������
		if (g_skill_item_flag == true)
		{
			//�X�L���A�C�e���t���O�I�t
			g_skill_item_flag = false;
			g_stage_clear = true;
			ClearCheck(g_stage_clear);
		}
		
	}





	
}

void CSceneEarth::ClearCheck(bool a)
{
	if (a == true)
	{
		if (cnt >= 1)
		{
			return;
		}
		else
		{
			//�I�u�W�F�N�g�쐬
			CObjStageClear* objs = new CObjStageClear();
			Objs::InsertObj(objs, OBJ_STAGECLEAR, 100);
			cnt++;
		}
	}
}