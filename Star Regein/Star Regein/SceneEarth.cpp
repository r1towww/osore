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

int g_StarCount = 0;	//���𐔂���ϐ��̏�����

//�g�p�w�b�_�[
#include "SceneEarth.h"
#include "GameHead.h"

//�R���X�g���N�^
CSceneEarth::CSceneEarth()
{
	g_StarCount = 0;
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
	p = Save::ExternalDataOpen(L"Earth test.csv", &size);//�O���f�[�^�ǂݍ���
	
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
	Draw::LoadImageW(L"�r�[���T�[�x��.png", 2, TEX_SIZE_512);
	Draw::LoadImageW(L"��.png", 3, TEX_SIZE_512);
	Draw::LoadImageW(L"覐�.png", 4, TEX_SIZE_64);
	Draw::LoadImageW(L"SpaceBack.png", 5, TEX_SIZE_1024);
	Draw::LoadImageW(L"��.png", 6, TEX_SIZE_1024);
	Draw::LoadImageW(L"Background.png", 7, TEX_SIZE_2048);
	Draw::LoadImageW(L"�~�j�}�b�v�w�i.png", 8, TEX_SIZE_512);
	Draw::LoadImageW(L"color.png", 9, TEX_SIZE_512);
	Draw::LoadImageW(L"HP.png",10, TEX_SIZE_512);
	Draw::LoadImageW(L"MP.png", 11, TEX_SIZE_512);
	Draw::LoadImageW(L"box_blue.png", 12, TEX_SIZE_512);
	Draw::LoadImageW(L"box_blue_t.png", 13, TEX_SIZE_512);
	Draw::LoadImageW(L"box_mini.png", 14, TEX_SIZE_512);

	//�e�X�g�p
	Draw::LoadImageW(L"�o�q1.png", 20, TEX_SIZE_512);
	Draw::LoadImageW(L"�o�q2.png", 21, TEX_SIZE_512);
	
	//block�I�u�W�F�N�g�쐬
	CObjBlock* objb = new CObjBlock(map);
	Objs::InsertObj(objb, OBJ_BLOCK, 1);
	
	//MiniMap�I�u�W�F�N�g�쐬
	CObjMiniMap* objminimap = new CObjMiniMap(map);
	Objs::InsertObj(objminimap, OBJ_MINIMAP, 100);

	//���b�Z�[�W�I�u�W�F�N�g�쐬
	CObjMessage* objmes = new CObjMessage();
	Objs::InsertObj(objmes, OBJ_MESSAGE, 120);

	//HP�Q�[�W�I�u�W�F�N�g�쐬
	CObjHeart* objheart = new CObjHeart();
	Objs::InsertObj(objheart, OBJ_HEART, 130);

	//MP�Q�[�W�I�u�W�F�N�g�쐬
	CObjMP* objMP = new CObjMP();
	Objs::InsertObj(objMP, OBJ_MP, 140);

	//�`���[�g���A�������o���쐬
	CObjTutorial* objtutorialhukidashi = new CObjTutorial(0,4);
	Objs::InsertObj(objtutorialhukidashi, OBJ_TUTORIAL, 150);
	//�`���[�g���A���I�u�W�F�N�g�쐬
	CObjTutorial* objtutorial = new CObjTutorial(1, 4);
	Objs::InsertObj(objtutorial, OBJ_TUTORIAL, 170);
	//�e�L�X�g�{�b�N�X�I�u�W�F�N�g�쐬
	CObjTextBox* objtextbox = new CObjTextBox();
	Objs::InsertObj(objtextbox, OBJ_TEXTBOX, 160);

}


//���s�����\�b�h
void CSceneEarth::Scene()
{
	//�e�X�g�i�n���Ő���5�W�߂��玟�ֈڍs�j
	if (g_StarCount == EARTHMAXSTAR)
	{
		Scene::SetScene(new CSceneStageClear());	//�Q�[�����C���V�[���Ɉڍs
	}
	
}