#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�V�[���F���C��
class CSceneMercuryVirgo :public CScene
{
	public:
		CSceneMercuryVirgo();
		~CSceneMercuryVirgo();
		void InitScene(); //���������\�b�h
		void Scene();     //���s�����\�b�h
		void ClearCheck(bool a);

	private:
		float Item_cnt;
		bool m_clear_f;

};

