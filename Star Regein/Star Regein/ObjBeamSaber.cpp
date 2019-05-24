//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

//�g�p����w�b�_�[�t�@�C��
#include "GameHead.h"
#include "ObjBeamSaber.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

bool g_attack_flag;
int g_slash_time;
int g_slash_frame;

//�R���X�g���N�^
CObjBeamSaber::CObjBeamSaber(float x, float y)
{
	m_x = x;
	m_y = y;
}

//�C�j�V�����C�Y
void CObjBeamSaber::Init()
{
	m_ani_frame = 0;	//�A�j���[�V�����t���[���̏�����
	m_ani_time = 0;		//�A�j���[�V�����^�C���̏�����

	m_f = false;	//�T�E���h�p�t���O�̏�����
	//��l���̌����ɂ���čU�����o�������C������ς���
	//�����蔻����Z�b�g
	if (g_posture == HERO_UP)  //��
	{
		m_angle = 270.0f;	//�p�x����
		m_pos_x = 10.0f;	//X������
		m_pos_y = -40.0f;	//Y������
	}
	else if (g_posture == HERO_LEFT) //��
	{
		m_angle = 0.0f;		//�p�x����
		m_pos_x = -35.0f;	//X������
		m_pos_y = 10.0f;	//Y������
	}
	else if (g_posture == HERO_DOWN) //��
	{
		m_angle = 90.0f;	//�p�x����
		m_pos_x = 10.0f;	//X������
		m_pos_y = 50.0f;	//Y������
	}
	else if (g_posture == HERO_RIGHT) //�E
	{
		m_angle = 180.0f;		//�p�x����
		m_pos_x = 50.0f;	//X������
		m_pos_y = 10.0f;		//Y������
	}

	Hits::SetHitBox(this, m_x + m_pos_x, m_y + m_pos_y, 60.0f, 60.0f, ELEMENT_BEAMSABER, OBJ_BEAMSABER, 11);

}

//�A�N�V����
void CObjBeamSaber::Action()
{
	//�u���b�N�̏��������Ă���
	CObjBlock* pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//���g��HitBox�������Ă���
	CHitBox* hit = Hits::GetHitBox(this);

	//�t���O���I�t�̏ꍇ
	if (m_f == false)
	{
		//�T�E���h��炷
		if (hit->CheckElementHit(ELEMENT_ENEMY) == true || hit->CheckElementHit(ELEMENT_NULL) == true)
		{
			Audio::Start(4);
		}		
		else
		{
			Audio::Start(3);
		}
		m_f = true;		//�I���ɂ���2�d�ɖ�Ȃ��悤�ɂ���
	}

	//�U���A�j���[�V�����p---------------------------------------

	m_ani_time++;		//�A�j���[�V�����^�C����i�܂���
	if (m_ani_time > 4)	//�^�C����4��葽���Ȃ�����
	{
		m_ani_frame += 1;	//�t���[����i�߂�
		m_ani_time = 0;		//�^�C����0�ɖ߂�
	}
	if (m_ani_frame == 5)	//�A�j���[�V�����t���[����5�ɂȂ�����
	{
		this->SetStatus(false);    //���g�ɍ폜���߂��o��
		Hits::DeleteHitBox(this);  //���L����HitBox�ɍ폜����
	}

	//�쐬����HitBox�X�V�p�̓���������o��
	hit->SetPos(m_x + m_pos_x + pb->GetScrollx(), m_y + m_pos_y + pb->GetScrolly());//���������V�����ʒu�i��l���̈ʒu�j���ɒu��������
}

//�h���[
void CObjBeamSaber::Draw()
{
	//�A�j���[�V����
	int AniData[5] =
	{
		0,1,2,3,4,
	};
	//�u���b�N�̏��������Ă���
	CObjBlock* pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	float r[4] = { 1.0f,0.3f,0.3f,1.0f };
	float y[4] = { 1.0f,0.7f,0.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top    =   0.0f;
	src.m_left   =   0.0f + (AniData[m_ani_frame] * 192.0f);
	src.m_right  = 192.0f + (AniData[m_ani_frame] * 192.0f);
	src.m_bottom = 192.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top    =  0.0f + m_y + m_pos_y + pb->GetScrolly();
	dst.m_left   =  0.0f + m_x + m_pos_x + pb->GetScrollx();
	dst.m_right  = 64.0f + m_x + m_pos_x + pb->GetScrollx();
	dst.m_bottom = 64.0f + m_y + m_pos_y + pb->GetScrolly();

	//�\��
	if (g_mp <= 0.0f)
	{
		Draw::Draw(2, &src, &dst, c, m_angle);
	}
	else if(g_hp <= 20.0f && g_skill == Libra)
		Draw::Draw(2, &src, &dst, r, m_angle);
	else if(g_hp <= 50.0f && g_skill == Libra)
		Draw::Draw(2, &src, &dst, y, m_angle);
	else 
		Draw::Draw(2, &src, &dst, c, m_angle);

}
