#pragma once
//�g�p����w�b�_�[
#include "GameL\DrawTexture.h"
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g:��l��
class CObjHero :public CObj
{
	public:
		CObjHero(float x, float y) ;
		~CObjHero() {};
		void Init();    //�C�j�V�����C�Y
		void Action();  //�A�N�V����
		void Draw();    //�h���[

		float GetX() { return m_px; }
		float GetY() { return m_py; }
		float GetVY() { return m_vy; }
		float GetVX() { return m_vx; }
		float GetPos() { return g_posture; }
		void SetX(float x) { m_px = x; }
		void SetY(float y) { m_py = y; }
		void SetVY(float vy) { m_vy = vy; }
		void SetVX(float vx) { m_vx = vx; }
		float GetDashF() { return m_dash_flag; } //�_�b�V���t���O�̎擾

	
	private:
		float m_px;  //�ʒu
		float m_py;
		float m_vx;  //�ړ��x�N�g��
		float m_vy;

		float m_alpha;//�����x
	
		int m_blackhole_num;	//�f�����Ƃ̃u���b�N�z�[���̐��̒l������

		float m_speed_power; //�X�s�[�h�p���[

		int m_ani_time; //�A�j���[�V�����t���[������Ԋu
		int m_ani_frame;//�`��t���[��

		int	 m_ani;			//�A�j���[�V�����p
		int  m_ani2;
		int	 m_eff_time;	//�A�j���[�V�����Ԋu�^�C��
		int  m_eff_time2;
		RECT_F m_eff;		//�G�t�F�N�g�`��p
		RECT_F m_eff2;		//���q�U���G�t�F�N�g�`��p

		bool m_libra_eff_f;	//�V�����X�L���G�t�F�N�g�p�t���O
		int m_f;//�U������p
		bool m_key_f;
		bool m_help_key_f;	//help�L�[�p�̃t���O

		int m_time;//���G���ԃJ�E���g
		int m_MP_time;//�l�o�����J�E���g
		int m_regene_time;//�l�o���W�F�l�J�E���g

	int m_burn_time;//�Ώ��Ԋu�^�C��
	int m_burn_max_time;//�Ώ����v�p������

	bool m_dash_flag;  //�_�b�V���t���O
	bool m_move_flag;  //�ړ��t���O

		bool m_a_flag;//�U������p

	bool m_burn_f;//�Ώ�����l���J���[�ύX�p�t���O

	//block�Ƃ̏Փˏ�Ԋm�F�p
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

		bool m_invincible_flag;//���G�t���O

		bool m_eff_flag;

	
};


