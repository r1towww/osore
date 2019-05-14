#pragma once
#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;


//�I�u�W�F�N�g�F�u���b�N���w�i
class CObjSkillGeminiB : public CObj
{
public:
	CObjSkillGeminiB(float x, float y);
	~CObjSkillGeminiB() {};
	void Init();		//�C�j�V�����C�Y
	void Action();		//�A�N�V����
	void Draw();		//�h���[

	float GetX() { return m_gx; }
	float GetY() { return m_gy; }
	float GetVY() { return m_vy; }
	float GetVX() { return m_vx; }

private:
	float m_gx;		//�ʒu
	float m_gy;
	float m_vx;		//�ړ��x�N�g��
	float m_vy;
	float m_posture;//�p��
	float alpha;
	float m_ani_max_time;	//�A�j���[�V��������Ԋu�ő�l
	float m_angle;	//�p�x����
	float m_pos_x;	//X������
	float m_pos_y;	//Y������


	int m_ani_time;	//�A�j���[�V�����t���[������Ԋu
	int m_ani_frame;//�`��t���[��

	int m_blackhole_num;	//�f�����Ƃ̃u���b�N�z�[���̐��̒l������
	int m_time;//�o�q���X�L�����Ŏ��ԑ���
	int m_bullet_time;//�e�۔��ˎ��ԑ���

					  //block�Ƃ̏Փˏ�Ԋm�F�p
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	//�ړ��p�̌�������p
	bool m_movex;//���E
	bool m_movey;//�㉺
};