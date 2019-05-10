#pragma once
//�g�p����w�b�_�[�t�@�C��
#include"GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�G
class CObjWoman :public CObj
{
public:
	CObjWoman(float x, float y,int id);
	~CObjWoman() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[

	float* GetPX() { return &m_px; }
	float* GetPY() { return &m_py; }

	float GetX() { return m_px; }
	float GetY() { return m_py; }
	float GetVY() { return m_vy; }
	float GetVX() { return m_vx; }

	//int GetID() { return count; } //���̎��ʔԍ�

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

	int m_ani_time;	//�A�j���[�V�����t���[������Ԋu
	int m_ani_frame;//�`��t���[��
	int m_hp;//�̗�

	int m_woman_id;

	int m_ani_timeB;//�X�^�����A�j���[�V�����^�C��

	int m_time;//���G���ԑ���
	int m_bullet_time;//�n�[�g�e���ˎ��ԑ���
	int m_f;//���G����
	int m_key_f;//���G���ԍs������
	int count;
	int e_time;//�G�s������
	int enemy_move;//�G�ړ�

	float m_speed_power;	//�ʏ푬�x
	float m_ani_max_time;	//�A�j���[�V��������Ԋu�ő�l

	bool m_invincible_flag;//���G�t���O


	int	   m_ani;		//�`���[�W�A�j���[�V�����p
	RECT_F m_eff;		//�`���[�W�G�t�F�N�g�`��p
	int m_ani_stop;

	//block�Ƃ̏Փˏ�Ԋm�F�p
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;
	//�ړ��p�̌�������p
	bool m_movex;//���E
	bool m_movey;//�㉺

	bool m_do_f;//�G�U���t���O

	bool m_df;//�~�j�}�b�v����̍폜�t���O

	bool m_woman_delete; //�����폜�t���O

	//���ŃA�j���[�V�����p
	int m_ani_count;
	int m_ani_delete;
	int m_ani_max_count;
	int m_ani_frame_delete;


	bool m_kill_f;	//�L���J�E���g�p�t���O

};