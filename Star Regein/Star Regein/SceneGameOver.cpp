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
#include "SceneGameOver.h"
#include "GameHead.h"

//�R���X�g���N�^
CSceneGameOver::CSceneGameOver()
{

}

//�f�X�g���N�^
CSceneGameOver::~CSceneGameOver()
{

}

//���������\�b�h
void CSceneGameOver::InitScene()
{
	Draw::LoadImageW(L"SpaceBack.png", 1, TEX_SIZE_1024);


	//�N���A�I�u�W�F�N�g�쐬
	CObjGameOver* o = new CObjGameOver();
	Objs::InsertObj(o, OBJ_STAGECLEAR, 1);
}
//���s�����\�b�h
void CSceneGameOver::Scene()
{

}