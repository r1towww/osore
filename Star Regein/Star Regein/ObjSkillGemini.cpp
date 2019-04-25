//�g�p����w�b�_�[�t�@�C��
#include <stdlib.h>
#include <time.h>
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjSkillGemini.h"
#include "UtilityModule.h"

//�g�p����l�[���X�y�[�X

using namespace GameL;

bool g_geminiattck_check;

CObjSkillGemini::CObjSkillGemini(float x, float y)
{
	m_gx = x;	//�ʒu
	m_gy = y;
}

//�C�j�V�����C�Y
void CObjSkillGemini::Init()
{
	m_vx = 0.0f;//�ړ�x�x�N�g��
	m_vy = 0.0f;//�ړ�y�x�N�g��
	m_posture = 0.0f;//����(0.0f) ��(1.0f) �E(2.0f) �w��(3.0f)

	m_ani_time = 0;
	m_ani_frame = 1;//�Î~�t���[���������ɂ���

	m_ani_max_time = 10;//�A�j���[�V�����Ԋu��

	m_movey = true; //true=���ʁ@false=�w��
	m_movex = true;	//true=�E�@false=��
	
	m_bullet_time = 0;

	m_time = 1500;

	alpha = 5.0;

	m_pos_x = 0;//��l���Ɠ��������Ɍ�������
	m_pos_y = 0;//��l���Ɠ��������Ɍ�������
}

//�A�N�V����
void CObjSkillGemini::Action()
{
	//��l���ƃu���b�N�̈ʒu���擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	CObjBlock* pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	CObjCow*cow = (CObjCow*)Objs::GetObj(OBJ_COW);
	CObjWoman*woman = (CObjWoman*)Objs::GetObj(OBJ_WOMAN);
	CObjTwinsRed*red = (CObjTwinsRed*)Objs::GetObj(OBJ_TWINS_RED);
	CObjTwinsBlue*bule = (CObjTwinsBlue*)Objs::GetObj(OBJ_TWINS_BLUE);

	if (g_posture == HERO_UP)  //��
	{
		m_pos_x     = +40.0f;	//X������
		m_pos_y     = -5.0f;	//Y������
		m_ani_time += 1;    //max�܂Ő�����
        m_posture   = 1.0f;   //�p��
	}
	else if (g_posture == HERO_LEFT) //��
	{
		m_pos_x     = -15.0f;	//X������
		m_pos_y     = -20.0f;	//Y������
		m_ani_time += 1;    //max�܂Ő�����
		m_posture   = 2.0f;   //�p��
	}
	else if (g_posture == HERO_DOWN) //��
	{
		m_pos_x     = -20.0f;	//X������
		m_pos_y     = +40.0f;	//Y������
		m_ani_time += 1;    //max�܂Ő�����
		m_posture   = 3.0f;   //�p��
	}
	else if (g_posture == HERO_RIGHT) //�E
	{
		m_pos_x     = +35.0f;   //X������
		m_pos_y     = +45.0f;   //Y������
		m_ani_time += 1;    //max�܂Ő�����
		m_posture   = 4.0f;   //�p��
	}
	//time�̕����傫���Ȃ�Ə������t���[����i�߂�
	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}
	//�t���[����3�ɂȂ�Ə�����
	if (m_ani_frame == 3)
	{
		m_ani_frame = 0;
	}

	if (g_geminiattck_check ==true)
	{
		//20���Ԋu�Œe�۔���
		m_bullet_time++;

		if (m_bullet_time > 200)
		{
			m_bullet_time = 0;

			//�u���b�N���������Ă���
			CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

			//10����������
			for (int i = 0; i < 360; i += 36)
			{
				//�T�u�@�e�ۃI�u�W�F�N�g�쐬
				CObjSkillBullet* objB = new CObjSkillBullet(m_gx + m_pos_x, m_gy + m_pos_y, i);
				Objs::InsertObj(objB, OBJ_SKILL_BULLET, 150);
			}
			g_geminiattck_check = false;
		}
	}

	//��l���̈ړ��x�N�g������
	 m_vx = hero->GetVX()*HERO_VEC;
	 m_vy = hero->GetVY()*HERO_VEC;

	//�ʒu�̍X�V
	m_gx += m_vx;
	m_gy += m_vy;

	m_time--;

	if (m_time < 0)
	{
		this->SetStatus(false);
		g_gemini_check = false;
	}


}

//�h���[
void CObjSkillGemini::Draw()
{
	//�A�j���[�V����
	int AniData[4] =
	{ 1,0,2,0, };

	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,alpha };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	//�u���b�N���������Ă���
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�؂���ʒu�̐ݒ�
	src.m_top    = 64.0f * m_posture;
	src.m_left   = 0.0f  + (AniData[m_ani_frame] * 64);
	src.m_right  = 64.0f + (AniData[m_ani_frame] * 64);
	src.m_bottom = src.m_top + 64.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top    =  0.0f + m_gy + m_pos_y + block->GetScrolly();
	dst.m_left   = 70.0f + m_gx + m_pos_x + block->GetScrollx();
	dst.m_right  =  0.0f + m_gx + m_pos_x + block->GetScrollx();
	dst.m_bottom = 70.0f + m_gy + m_pos_y + block->GetScrolly();

	//�\��
	Draw::Draw(21, &src, &dst, c, 0.0f);
}