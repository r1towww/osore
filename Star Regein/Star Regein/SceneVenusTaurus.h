#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�萔
#define TAURUSMAXSTAR	18	//�������̐��̐�

//�V�[���F���C��
class CSceneVenusTaurus :public CScene
{
	public:
		CSceneVenusTaurus();
		~CSceneVenusTaurus();
		void InitScene(); //���������\�b�h
		void Scene();     //���s�����\�b�h
	private:
		float Item_cnt;

};

