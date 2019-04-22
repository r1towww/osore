#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;
//�I�u�W�F�N�g�F�r�[���T�[�x��
class CObjSkillBullet : public CObj
{
public:
	CObjSkillBullet(float gx, float gy);
	~CObjSkillBullet() {};
	void Init();  //�C�j�V�����C�Y
	void Action();//�A�N�V����
	void Draw();  //�h���[
private:

	float m_gx;		//�ʒu
	float m_gy;

	float m_vx;
	float m_vy;

	float m_time;

	int m_pos_x;	//�q�b�g�{�b�N�X�̌����p�ϐ�
	int m_pos_y;
	int m_angle;	//�n�[�g�e�̊p�x�p�ϐ�

	bool m_hit_flag;//���e�t���O

	int m_ani_time; //�A�j���[�V�����t���[������Ԋu
	int m_ani_frame;//�`��t���[��

	int m_posture;//��l���̌�����������ϐ�

	int	   m_ani;		//�`���[�W�A�j���[�V�����p
	RECT_F m_eff;		//�`���[�W�G�t�F�N�g�`��p
	int m_ani_stop;

};