#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F
class CObjMenu :public CObj
{
	public:
		CObjMenu() {};
		~CObjMenu() {};
		void Init();	//�C�j�V�����C�Y
		void Action();	//�A�N�V����
		void Draw();	//�h���[

	private:
		int m_key;	//�L�[���͗p
		bool m_key_f;	//�L�[���͐���t���O
		bool m_choice_key_f;	//�I��p�̃L�[�t���O
		bool m_push_flag;
		float m_Tra;

};

