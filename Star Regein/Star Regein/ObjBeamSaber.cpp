//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

//�g�p����w�b�_�[�t�@�C��
#include "GameHead.h"
#include "ObjBeamSaber.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjBeamSaber::CObjBeamSaber(float x, float y)
{
	m_x = x;
	m_y = y;
}

//�C�j�V�����C�Y
void CObjBeamSaber::Init()
{
	//��l���̌����ɂ���ăr�[���T�[�x�����o�������C������ς���
	if (g_posture == 3)	//��
	{
		m_angle = 270.0f;	//�p�x����
		m_pos_x = 20.0f;		//X������
		m_pos_y = 64.0f;	//Y������
	}
	if (g_posture == 4)	//�E
	{
		m_angle = 0.0f;		//�p�x����
		m_pos_x = 48.0f;	//X������
		m_pos_y = 24.0f;		//Y������
	}
	if (g_posture == 2)	//��
	{
		m_angle = 180.0f;	//�p�x����
		m_pos_x = -18.0f;	//X������
		m_pos_y = 24.0f;		//Y������
	}
	if (g_posture == 1)	//��
	{
		m_angle = 90.0f;	//�p�x����
		m_pos_x = 10.0f;		//X������
		m_pos_y = -28.0f;	//Y������
	}
	//�����蔻����Z�b�g
	if(g_posture == 0 || g_posture == 3)
		Hits::SetHitBox(this, m_x + m_pos_x +5, m_y + m_pos_y, 20, 32, ELEMENT_BEAMSABER, OBJ_BEAMSABER, 1);
	else
		Hits::SetHitBox(this, m_x + m_pos_x + 5, m_y + m_pos_y+5, 32, 20, ELEMENT_BEAMSABER, OBJ_BEAMSABER, 1);

}

//�A�N�V����
void CObjBeamSaber::Action()
{
	//���g��HitBox�������Ă���
	CHitBox* hit = Hits::GetHitBox(this);

	//�쐬����HitBox�X�V�p�̓���������o��
	hit->SetPos(m_x, m_y);//���������V�����ʒu�i��l���̈ʒu�j���ɒu��������
	
	this->SetStatus(false);    //���g�ɍ폜���߂��o��
	Hits::DeleteHitBox(this);  //��l���@�����L����HitBox�ɍ폜����

}

//�h���[
void CObjBeamSaber::Draw()
{


	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top    = 0.0f;
	src.m_left   = 0.0f;
	src.m_right  = 32.0f;
	src.m_bottom = 32.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top    =  0.0f + m_y + m_pos_y;
	dst.m_left   =  0.0f + m_x + m_pos_x;
	dst.m_right  = 32.0f + m_x + m_pos_x;
	dst.m_bottom = 32.0f + m_y + m_pos_y;
	

	//�\��
	Draw::Draw(2, &src, &dst, c, m_angle);
}
