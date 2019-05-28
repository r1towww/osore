#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�w�i
class CObjFadein : public CObj
{
	public:
		CObjFadein() {};
		~CObjFadein() {};
		void Init();	//�C�j�V�����C�Y
		void Action();	//�A�N�V����
		void Draw();	//�h���[

	private:
		int	m_ani_time;
		int m_ani_frame;

		float m_ani_max_time;	//�A�j���[�V��������Ԋu�ő�l

		bool m_flag;			//�؂�ւ��p�t���O
		bool m_fade_flag;		//�t�F�C�h�C���̐؂�ւ��p�t���O
		bool m_next_flag;		//���̊K�w�ւ̈ڍs�p
		bool m_main_flag;		//�^�C�g������̈ڍs�p
		bool m_death_flag;		//�Q�[���I�[�o�[�V�[���ւ̈ڍs�p
		bool m_clear_flag;		//�Q�[���N���A�ւ̈ڍs�p
};
