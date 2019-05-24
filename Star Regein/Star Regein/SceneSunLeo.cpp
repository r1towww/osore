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

	Item_cnt = 0.0f;
	g_Make_Item = false;
	g_Virgo_Max = false;
	g_Leo_Max = false;
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
	Draw::LoadImageW(L"��l���a���A�j���[�V����.png", 2, TEX_SIZE_512);

	Draw::LoadImageW(L"�V�����X�L���G�t�F�N�g.png", 14, TEX_SIZE_2048);
	Draw::LoadImageW(L"�_�b�V��.png", 15, TEX_SIZE_1024);
	Draw::LoadImageW(L"��ӂ��G�t�F�N�g.png", 17, TEX_SIZE_2048);
	Draw::LoadImageW(L"�n�[�g�e.png", 50, TEX_SIZE_512);
	Draw::LoadImageW(L"���e�A�j���[�V����.png", 51, TEX_SIZE_512);
	Draw::LoadImageW(L"���q���X�L���G�t�F�N�g.png", 23, TEX_SIZE_512);

	Draw::LoadImageW(L"�o�q�p�e��.png", 16, TEX_SIZE_128);

	Draw::LoadImageW(L"�o�q1.png", 20, TEX_SIZE_512);
	Draw::LoadImageW(L"�o�q2.png", 21, TEX_SIZE_512);
	Draw::LoadImageW(L"���q.png", 52, TEX_SIZE_512);

	Draw::LoadImageW(L"����.png", 49, TEX_SIZE_512);

	Draw::LoadImageW(L"�o�q�p�e��.png", 16, TEX_SIZE_128);
	Draw::LoadImageW(L"���q�U���G�t�F�N�g.png", 18, TEX_SIZE_2048);
	Draw::LoadImageW(L"�X�e�[�W�N���A�摜_���z.png", 60, TEX_SIZE_2048);

	Draw::LoadImageW(L"覐�.png", 4, TEX_SIZE_64);
	Draw::LoadImageW(L"�� �G�t�F�N�g����.png", 6, TEX_SIZE_2048);
	Draw::LoadImageW(L"���G�t�F�N�g.png", 99, TEX_SIZE_512);

	Draw::LoadImageW(L"�u���b�N�z�[��.png", 30, TEX_SIZE_1024);
	Draw::LoadImageW(L"�z���C�g�z�[��.png", 31, TEX_SIZE_1024);

	Draw::LoadImageW(L"�F���w�i.png", 5, TEX_SIZE_1024);
	Draw::LoadImageW(L"���������G����.png", 13, TEX_SIZE_1024);

	Draw::LoadImageW(L"�~�j�}�b�v�g.png", 7, TEX_SIZE_2048);
	Draw::LoadImageW(L"�~�j�}�b�v�w�i.png", 8, TEX_SIZE_512);
	Draw::LoadImageW(L"�~�j�}�b�v�e��_.png", 9, TEX_SIZE_512);
	Draw::LoadImageW(L"HP.png", 10, TEX_SIZE_2048);

	Draw::LoadImageW(L"�e�L�X�g�{�b�N�X .png", 40, TEX_SIZE_512);
	Draw::LoadImageW(L"�e�L�X�g�{�b�N�X ����.png", 41, TEX_SIZE_512);
	Draw::LoadImageW(L"���O�p�g.png", 42, TEX_SIZE_512);

	Draw::LoadImageW(L"���ŃA�j���[�V����.png", 80, TEX_SIZE_1024);
	Draw::LoadImageW(L"���S�A�j���[�V����.png", 35, TEX_SIZE_1024);

	Draw::LoadImageW(L"���U���g�X�^�[.png", 70, TEX_SIZE_1024);
	Draw::LoadImageW(L"���U���g�X�^�[�G�t�F�N�g.png", 71, TEX_SIZE_1024);

	//Audio
	Audio::LoadAudio(1, L"�s�R�I.wav", EFFECT);
	Audio::LoadAudio(2, L"���艹.wav", EFFECT);
	Audio::LoadAudio(3, L"�����E�a��01.wav", EFFECT);		//�ߋ�����U�莞SE
	Audio::LoadAudio(4, L"�����E�a��07.wav", EFFECT);		//�ߋ����q�b�g��SE
	Audio::LoadAudio(5, L"�葫�E����A�R��09.wav", EFFECT);		//�_���[�WSE
	Audio::LoadAudio(6, L"���E�L���[��06.wav", EFFECT);		//���擾��SE
	Audio::LoadAudio(7, L"��ʓ]���E�X���C�h�\��04.wav", EFFECT);//�u���b�N�z�[���ł̃��[�v��SE
	Audio::LoadAudio(9, L"�X�e�[�W�N���A.wav", EFFECT);
	Audio::LoadAudio(10, L"�Q�[���I�[�o�[.wav", EFFECT);
	//�e�����X�L���pSE
	Audio::LoadAudio(11, L"�������X�L��SE.wav", EFFECT);
	Audio::LoadAudio(12, L"�V�����X�L��SE.wav", EFFECT);
	Audio::LoadAudio(13, L"�o�q���X�L��SE.wav", EFFECT);
	Audio::LoadAudio(14, L"�������X�L��SE.wav", EFFECT);
	Audio::LoadAudio(15, L"���������eSE.wav", EFFECT);
	Audio::LoadAudio(16, L"���q���X�L��SE.wav", EFFECT);
	Audio::LoadAudio(20, L"S�����NSE.wav", EFFECT);
	Audio::LoadAudio(21, L"A�����NSE.wav", EFFECT);
	Audio::LoadAudio(22, L"BC�����NSE.wav", EFFECT);

	Audio::LoadAudio(19, L"���U���g�X�^�[SE.wav", EFFECT);

	//BGM
	Audio::LoadAudio(8, L"�퓬���_BGM.wav", SOUND_TYPE::BACK_MUSIC);

	Audio::Start(8);

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
	Objs::InsertObj(objSkill, OBJ_SKILL, 110);
	//�N���A���ĂȂ�������`���[�g���A���\��
	if (g_Leo_clear != true)
	{
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

}

//���s�����\�b�h
void CSceneSunLeo::Scene()
{
	//���z�Ő���14�W�߂��玟�ֈڍs
	if (g_StarCount == 14)
	{
		g_Leo = true;		//�X�L���i�V�����j���I���ɂ���
		g_Leo_Max = true;
		g_All_Skill_Get = true;
		g_Boss_Spawn = true;
		//���q�����N���A�\��
		g_Sun_clear = true;
		g_new_Performance = true;


		//�����W�߂�������
		if (g_Leo_Max == true)
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
				g_Make_Item = true; //�A�C�e���쐬�t���O�I��
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
//�N���A�`�F�b�N
void CSceneSunLeo::ClearCheck(bool a)
{
	//�N���A�����Ȃ琯�������摜�\��t��
	if (a == true)
	{
		if (m_clear_f == true)
		{
			return;
		}
		else
		{
			Audio::Start(9);

			//�I�u�W�F�N�g�쐬
			CObjStageClear* objs = new CObjStageClear();
			Objs::InsertObj(objs, OBJ_STAGECLEAR, 130);
			m_clear_f = true;
		}
	}
}



