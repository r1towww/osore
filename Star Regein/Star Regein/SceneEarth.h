#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�萔
#define EARTHMAXSTAR	5	//�n���̐��̐�

//�V�[���F���C��
class CSceneEarth :public CScene
{
	public:
		CSceneEarth();
		~CSceneEarth();
		void InitScene(); //���������\�b�h
		void Scene();     //���s�����\�b�h
		void ClearCheck(bool a);
	private:

		int cnt;
};

