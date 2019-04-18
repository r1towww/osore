//STL�f�o�b�O�@�\��OFF�ɂ���
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p�w�b�_�[
#include "SceneMercuryVirgo.h"
#include "GameHead.h"

//�R���X�g���N�^
CSceneMercuryVirgo::CSceneMercuryVirgo()
{
	g_StarCount = 0;	//���𐔂���ϐ��̏�����

}

//�f�X�g���N�^
CSceneMercuryVirgo::~CSceneMercuryVirgo()
{

}

//���������\�b�h
void CSceneMercuryVirgo::InitScene()
{
	//�O���f�[�^�ǂݍ��݁i�X�e�[�W���j
	unique_ptr<wchar_t> p;	//�X�e�[�W���|�C���^�[
	int size;				//�X�e�[�W���̑傫��
	p = Save::ExternalDataOpen(L"MercuryVirgo.csv", &size);//�O���f�[�^�ǂݍ���

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
	Draw::LoadImageW(L"HP.png", 10, TEX_SIZE_512);
	Draw::LoadImageW(L"MP.png", 11, TEX_SIZE_512);
	Draw::LoadImageW(L"blackhole.png", 12, TEX_SIZE_256);
	Draw::LoadImageW(L"�X�L������.png", 13, TEX_SIZE_2048);
	Draw::LoadImageW(L"�e��.png", 16, TEX_SIZE_128);

	Draw::LoadImageW(L"�o�q1.png", 20, TEX_SIZE_512);
	Draw::LoadImageW(L"�o�q2.png", 21, TEX_SIZE_512);
	Draw::LoadImageW(L"�n�[�g�e.png", 22, TEX_SIZE_512);

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
	Objs::InsertObj(objstatus, OBJ_STATUS, 130);

	//�X�L���؂�ւ��I�u�W�F�N�g�쐬
	CObjSkill* objSkill = new CObjSkill();
	Objs::InsertObj(objSkill, OBJ_SKILL, 150);
}

//���s�����\�b�h
void CSceneMercuryVirgo::Scene()
{
	//�����i�������j�Ő���18�W�߂��玟�ֈڍs
	if (g_StarCount == VIRGOMAXSTAR)
	{
		//�������̃X�L���J��
		g_Gemini = true;
		//�������̃N���A�\�L
		g_Gemini_clear = true;
		//�����A�����̐������ǂ�����N���A���Ă����琅�����N���A�\�L
		if (g_Gemini_clear == true && g_Virgo_clear == true)
		{
			g_Mercury_clear = true;
		}
		Scene::SetScene(new CSceneStageClear());	//�Q�[���N���A�Ɉڍs
	}
}