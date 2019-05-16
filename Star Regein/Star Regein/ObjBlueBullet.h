#pragma once
//�g�p����w�b�_�[
#include "GameL\DrawTexture.h"
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�G�@�p�x�e��
class CObjBlueBullet : public CObj
{
public:
	CObjBlueBullet(float x, float y, float r, float speed);
	~CObjBlueBullet() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
private:
	float m_x;	//�I�u�W�F�N�g�̈ʒuX
	float m_y;	//�I�u�W�F�N�g�̈ʒuY
	float m_vx;	//�I�u�W�F�N�g�̈ړ��p�x�N�g��X
	float m_vy;	//�I�u�W�F�N�g�̈ړ��p�x�N�g��Y
	float m_r;	//�ړ�����p�x
	float m_speed;	//���x
	int m_ani_max_time;	//�A�j���[�V��������Ԋu�ő�l
	float m_ani_max_time2;

	int m_ani_time; //�A�j���[�V�����t���[������Ԋu
	int m_ani_frame;//�`��t���[��
	int m_ani_stop;
	int	   m_ani;		//�`���[�W�A�j���[�V�����p

	int m_posture;//��l���̌�����������ϐ�

	RECT_F m_eff;		//�`���[�W�G�t�F�N�g�`��p

	int m_time;//�폜�܂ł̎��ԑ���
	bool	m_del;		//�폜�`�F�b�N
	
	int m_ani_time2;
	int m_ani_frame2;
	int m_ani_stop2;

	

	bool m_hero_hit = false;

};
