//�g�p����w�b�_�[�t�@�C��
#include <stdlib.h>
#include <time.h>
#include"GameL\DrawTexture.h"
#include"GameL\WinInputs.h"
#include"GameL\SceneManager.h"
#include"GameL\HitBoxManager.h"
#include"GameL\UserData.h" 

#include"GameHead.h"
#include"ObjHomingHeart.h"
#include "UtilityModule.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjHomingHeart::CObjHomingHeart(float x, float y, float speed)
{
	m_px = x;	//�ʒu
	m_py = y;

	m_speed = speed;
}

//�C�j�V�����C�Y
void CObjHomingHeart::Init()
{
	m_vx = 0.0f;	//�ړ��x�N�g��
	m_vy = 0.0f;

	m_time = 300;

	alpha = 1.0f;

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 32, 28, ELEMENT_ENEMY, OBJ_HOMING_HEART, 1);
}

//�A�N�V����
void CObjHomingHeart::Action()
{

	m_time--;

	//�e�ێ��s�����@-----
	//��l���@�ƗU���e�ۂŊp�x�����
	CObjHero* obj = (CObjHero*)Objs::GetObj(OBJ_HERO);

	CObjBlock* pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//��l���@�����݂���ꍇ�A�U���p�x�̌v�Z����
	if (obj != nullptr)
	{

		float x;
		float y;

		x = 375 - (m_px + pb->GetScrollx());
		y = 275 - (m_py + pb->GetScrolly());

		float ar = GetAtan2Angle(x, y);

		//�G�̌��݂̌����Ă���p�x�����
		float br = GetAtan2Angle(m_vx, m_vy);

		//��l���@�ƓG�p�x������܂�ɂ��������ꂽ��
		m_vx = cos(3.14 / 180 * ar) * 2;
		m_vy = sin(3.14 / 180 * ar) * 2;
	}

	//�ړ�
	m_px += m_vx*m_speed;
	m_py += m_vy*m_speed;

	//HitBox�̓��e���X�V
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + block->GetScrollx(), m_py + block->GetScrolly());

	//��l���@�I�u�W�F�N�g�ƐڐG������e�ۍ폜
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr || hit->CheckElementHit(ELEMENT_BLOCK) || m_time <= 0)
	{
		this->SetStatus(false);    //���g�ɍ폜���߂��o��
		Hits::DeleteHitBox(this);  //��l���@�����L����HitBox�ɍ폜����
	}
}

//�h���[
void CObjHomingHeart::Draw()
{
	int AniData[4] =
	{ 1,0,2,0, };

	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,alpha };

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu

	 //�u���b�N���������Ă���
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 32.0f;
	src.m_bottom = 28.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py + block->GetScrolly();
	dst.m_left = 32.0f + m_px + block->GetScrollx();
	dst.m_right = 0.0f + m_px + block->GetScrollx();
	dst.m_bottom = 28.0f + m_py + block->GetScrolly();


	//�`��
	Draw::Draw(22, &src, &dst, c, 0.0f);
}