#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�V�[���F���C��
class CSceneMercuryGemini :public CScene
{
	public:
		CSceneMercuryGemini();
		~CSceneMercuryGemini();
		void InitScene(); //���������\�b�h
		void Scene();     //���s�����\�b�h
		void ClearCheck(bool a);
	private:
		bool m_clear_f;
		float Item_cnt;
};

