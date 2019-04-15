//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameHead.h"
#include "ObjBlueBullet.h"
#include "UtilityModule.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjBlueBullet::CObjBlueBullet(float x, float y, float r, float speed)
{
	m_x = x;
	m_y = y;
	m_r = r;
	m_speed = speed;
}

//�C�j�V�����C�Y
void CObjBlueBullet::Init()
{

	m_ani_time = 0;
	m_ani_frame = 2;

	m_time = 100;

	m_ani_max_time = 7;	//�A�j���[�V�����Ԋu��

	m_vx = cos(3.14f / 180.0f*m_r);
	m_vy = sin(3.14f / 180.0f*m_r);
	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_x, m_y, 25, 25, ELEMENT_ENEMY, OBJ_BLUE_BULLET, 1);
}

//�A�N�V����
void CObjBlueBullet::Action()
{
	m_time--;

	m_ani_time += ANITIME;

	//�e�ێ��s�����@-----

	//�ړ�
	m_x += m_vx * m_speed;
	m_y -= m_vy * m_speed;

	//�A�j���[�V�����p
	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}

	if (m_ani_frame == 5)
	{
		m_ani_frame = 0;
	}

	//�G�@�e�ۂ�HitBox�X�V�p�|�C���^�[�擾
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_x + block->GetScrollx(), m_y + block->GetScrolly());			//HitBox�̈ʒu��G�@�e�ۂ̈ʒu�ɍX�V

	//��l���@�I�u�W�F�N�g�ƐڐG������e�ۍ폜
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr || m_time <= 0)
	{
		this->SetStatus(false);    //���g�ɍ폜���߂��o��
		Hits::DeleteHitBox(this);  //��l���@�����L����HitBox�ɍ폜����

		m_time = 100;
	}
}

//�h���[
void CObjBlueBullet::Draw()
{
	//�A�j���[�V����
	int AniData[5] =
	{
		2,1,0,1,2,
	};

	//�`�ʃJ���[���@R=RED�@G=Green�@B=Blue�@A=alpha�i���ߏ��j
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	//�u���b�N���������Ă���
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�؂���ʒu�̐ݒ�
	src.m_top = 16.0f;
	src.m_left = 0.0f + (AniData[m_ani_frame] * 16);
	src.m_right = 16.0f + (AniData[m_ani_frame] * 16);
	src.m_bottom = 32.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_y + block->GetScrolly();
	dst.m_left = 0.0f + m_x + block->GetScrollx();
	dst.m_right = 25.0f + m_x + block->GetScrollx();
	dst.m_bottom = 25.0f + m_y + block->GetScrolly();

	//�O�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�Ec�̏������ɕ`��
	Draw::Draw(14, &src, &dst, c, 0);
}