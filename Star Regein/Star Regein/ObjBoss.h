#pragma once
//�g�p����w�b�_�[�t�@�C��
#include"GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�G
class CObjBoss :public CObj
{
public:
	CObjBoss(float x, float y);
	~CObjBoss() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[

	float* GetPX() { return &m_px; }
	float* GetPY() { return &m_py; }

	float GetX() { return m_px; }
	float GetY() { return m_py; }
	float GetVY() { return m_vy; }
	float GetVX() { return m_vx; }

	void SetX(float x) { m_px = x; }
	void SetY(float y) { m_py = y; }
	void SetVY(float vy) { m_vy = vy; }
	void SetVX(float vx) { m_vx = vx; }


private:
	float m_px;		//�ʒu
	float m_py;
	float m_vx;		//�ړ��x�N�g��
	float m_vy;
	float m_posture;//�p��
	float m_alpha;

	//���[�v�A�j���[�V����
	RECT_F m_warp_eff;		//�G�t�F�N�g�`��p
	int	 m_warp_ani;			//���[�v�A�j���[�V�����p
	int	 m_warp_ani_time;		//���[�v�A�j���[�V�����Ԋu�^�C��
	int m_warp_time;			//���[�v���ԑ���
	bool m_warp_flag;



	int m_ani_time;	//�A�j���[�V�����t���[������Ԋu
	int m_ani_frame;//�`��t���[��
	int m_hp;//�̗�

	int m_rand;
	int m_attack_pattern;

	int m_snake_c;
	int m_bullet_t;//�e���p�^�C��

	int m_time;//���G���ԑ���
	int m_key_f;//���G���ԍs������
	int m_imposition_t;//�U���������Ԓ����p
	int count;
	int e_time;//�G�s������
	int enemy_move;//�G�ړ�

	float m_speed_power;	//�ʏ푬�x
	float m_ani_max_time;	//�A�j���[�V��������Ԋu�ő�l

	//block�Ƃ̏Փˏ�Ԋm�F�p
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	bool m_invincible_flag;//���G�t���O

	//�ړ��p�̌�������p
	bool m_movex;//���E
	bool m_movey;//�㉺

	bool m_f;//���G����

	bool m_beam_f;//�r�[���t���O
	bool m_attack_f;

	bool m_do_f;//�G�U���t���O

	bool m_df;//�~�j�}�b�v����̍폜�t���O


};
