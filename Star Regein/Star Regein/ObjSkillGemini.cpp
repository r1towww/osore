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

CObjSkillGemini::CObjSkillGemini(float x, float y)
{
	m_gx = x;	//�ʒu
	m_gy = y;
}

//�C�j�V�����C�Y
void CObjSkillGemini::Init()
{
	m_vx = 0.0f;	//�ړ��x�N�g��
	m_vy = 0.0f;
	m_posture = 0.0f;//����(0.0f) ��(1.0f) �E(2.0f) �w��(3.0f)

	m_ani_time = 0;
	m_ani_frame = 1;	//�Î~�t���[���������ɂ���

	m_ani_max_time = 15;	//�A�j���[�V�����Ԋu��

	alpha = 1.0;

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_gx, m_gy, 40, 40, ELEMENT_NULL, OBJ_TWINS_BLUE, 1);
}

//�A�N�V����
void CObjSkillGemini::Action()
{
	//��l���̈ʒu���擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	//��l���̈ړ��x�N�g������
	 m_vx = hero->GetVX()*HERO_VEC;
	 m_vy = hero->GetVY()*HERO_VEC;

	//�u���b�N�Ƃ̓����蔻����s
	CObjBlock* pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockHit(&m_gx, &m_gy, false,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy
	);

	//HitBox�̓��e���X�V
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_gx + 19 + pb->GetScrollx(), m_gy + 15 + pb->GetScrolly());

	//�ʒu�̍X�V
	m_gx += m_vx;
	m_gy += m_vy;
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
	dst.m_top    =  0.0f + m_gy + block->GetScrolly();
	dst.m_left   = 32.0f + m_gx + block->GetScrollx();
	dst.m_right  =  0.0f + m_gx + block->GetScrollx();
	dst.m_bottom = 32.0f + m_gy + block->GetScrolly();

	//�\��
	Draw::Draw(20, &src, &dst, c, 0.0f);
}