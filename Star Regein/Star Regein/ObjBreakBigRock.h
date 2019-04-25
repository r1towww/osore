#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�u���b�N���w�i
class CObjBreakBigRock : public CObj
{
	public:
		CObjBreakBigRock(float x, float y, int i, int j);
		~CObjBreakBigRock() {};
		void Init();		//�C�j�V�����C�Y
		void Action();		//�A�N�V����
		void Draw();		//�h���[

	private:
		float m_px;			//�ʒu
		float m_py;
		int m_i;		//�}�b�v��̍��W�擾�p
		int m_j;

		int m_cnt;		//���ł܂ł̃J�E���g�p
		bool m_f;		//���G�p�t���O

		float m_bom_x;	//�����G�t�F�N�g�̕\���ʒu
		float m_bom_y;

		bool m_eff_flag;	//�G�t�F�N�g�p�t���O
		int	 m_ani;			//�A�j���[�V�����p
		int	 m_ani_time;	//�A�j���[�V�����Ԋu�^�C��
		RECT_F m_eff;		//�G�t�F�N�g�`��p

};
