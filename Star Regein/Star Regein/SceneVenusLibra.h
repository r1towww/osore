#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�萔
#define LIBRAMAXSTAR	6	//�V�����̐��̐�

//�V�[���F���C��
class CSceneVenusLibra :public CScene
{
	public:
		CSceneVenusLibra();
		~CSceneVenusLibra();
		void InitScene(); //���������\�b�h
		void Scene();     //���s�����\�b�h
		void ClearCheck(bool a);
	private:
		bool m_clear_f;
};

