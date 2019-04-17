//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

//�g�p����w�b�_�[�t�@�C��
#include "GameHead.h"
#include "ObjSkillVirgo.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;


//�R���X�g���N�^
CObjSkillVirgo::CObjSkillVirgo(float x, float y)
{
	m_x = x;
	m_y = y;
}

//�C�j�V�����C�Y
void CObjSkillVirgo::Init()
{
	//�ړ��ʂ̏�����
	m_vx = 0.0f;
	m_vy = 0.0f;

	//�e�폜�̃J�E���g������
	m_time = 0.0f;


	//��l���̌����ɂ���ăr�[���T�[�x�����o�������C������ς���
	if (g_posture == 3)	//��
	{
		m_angle = 90.0f;	//�p�x����
		m_pos_x = 20.0f;		//X������
		m_pos_y = 45.0f;	//Y������
	}
	if (g_posture == 4)	//�E
	{
		m_angle = 180.0f;		//�p�x����
		m_pos_x = 38.0f;	//X������
		m_pos_y = 14.0f;		//Y������
	}
	if (g_posture == 2)	//��
	{
		m_angle = 0.0f;	//�p�x����
		m_pos_x = -28.0f;	//X������
		m_pos_y = 24.0f;		//Y������
	}
	if (g_posture == 1)	//��
	{
		m_angle = 270.0f;	//�p�x����
		m_pos_x = 10.0f;		//X������
		m_pos_y = -25.0f;	//Y������
	}
	//�����蔻����Z�b�g
	if (g_posture == 1)  //��
		Hits::SetHitBox(this, m_x+m_pos_x , m_y+m_pos_y, 32, 28, ELEMENT_VIRGO_SKILL, OBJ_SKILL_VIRGO, 1);
	else if (g_posture == 2) //��
		Hits::SetHitBox(this, m_x + m_pos_x, m_y+m_pos_y , 32, 28, ELEMENT_VIRGO_SKILL, OBJ_SKILL_VIRGO, 1);
	else if (g_posture == 3) //��
		Hits::SetHitBox(this, m_x + m_pos_x, m_y+m_pos_y , 32, 28, ELEMENT_VIRGO_SKILL, OBJ_SKILL_VIRGO, 1);
	else if (g_posture == 4) //�E
		Hits::SetHitBox(this, m_x + m_pos_x, m_y+m_pos_y, 32, 28, ELEMENT_VIRGO_SKILL, OBJ_SKILL_VIRGO, 1);

}

//�A�N�V����
void CObjSkillVirgo::Action()
{

	//���g��HitBox�������Ă���
	CHitBox* hit = Hits::GetHitBox(this);


	if (g_posture == 1)//��
	{
		m_vy += MOVE;
		m_y -= m_vy;
	}
	else if (g_posture == 2)//��
	{
		m_vx += MOVE;
		m_x -= m_vx;
	}
	else if (g_posture == 3)//��
	{
		m_vy += MOVE;
		m_y += m_vy;
	}
	else if (g_posture == 4)//�E
	{
		m_vx += MOVE;
		m_x += m_vx;
	}



	//�쐬����HitBox�X�V�p�̓���������o��
	hit->SetPos(m_x+m_pos_x, m_y+m_pos_y);//���������V�����ʒu�i��l���̈ʒu�j���ɒu��������

	m_time++;

	if (m_time >= 20)
	{
		m_time = 0.0f;

		this->SetStatus(false);    //���g�ɍ폜���߂��o��
		Hits::DeleteHitBox(this);  //��l���@�����L����HitBox�ɍ폜����
	}
}
//�h���[
void CObjSkillVirgo::Draw()
{

	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu


	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 32.0f;
	src.m_bottom = 28.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_y + m_pos_y;
	dst.m_left = 0.0f + m_x + m_pos_x;
	dst.m_right = 32.0f + m_x + m_pos_x;
	dst.m_bottom = 32.0f + m_y + m_pos_y;

	//�\��
	Draw::Draw(20, &src, &dst, c,0.0f);
}
