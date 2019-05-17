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
	m_ani = 0;
	m_ani_stop = 0;



	m_ani_time2 = 0;
	m_ani_frame2 = 1;
	m_ani_stop2 = 0;

	m_time = 150;
	m_del = false;

	m_vx = cos(3.14f / 180.0f*m_r);
	m_vy = sin(3.14f / 180.0f*m_r);

	m_ani_max_time = 7;	//�A�j���[�V�����Ԋu��
	m_ani_max_time2 = 10;

	m_vx = cos(3.14f / 180.0f*m_r);
	m_vy = sin(3.14f / 180.0f*m_r);

	m_hero_hit = false;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_x, m_y, 25, 25, ELEMENT_ENEMY, OBJ_BLUE_BULLET, 1);
}

//�A�N�V����
void CObjBlueBullet::Action()
{
	//�s�������䂳��Ă���ꍇ�i���j���[��ʁj
	if (g_move_stop_flag == true || g_tutorial_flag == true)
		return;	//�s���𐧌�

	m_time++;

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


	//��l���ƐڐG������A�j���[�V�����̌�폜
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		m_hero_hit = true;

	}
	//�u���b�N�I�u�W�F�N�g�ƐڐG����莞�ԂŒe�ۍ폜
	if ( hit->CheckElementHit(ELEMENT_BLOCK)==true || m_time <=150 )
	{
		this->SetStatus(false);    //���g�ɍ폜���߂��o��
		Hits::DeleteHitBox(this);  //��l���@�����L����HitBox�ɍ폜����
	}



	//��l���Ƀq�b�g������R�}���P�i�߂�
	if (m_hero_hit == true)
	{
		m_ani_frame2 += ANITIME;
	}

	//�A�j���[�V�����p
	if (m_ani_time2 > m_ani_max_time2)
	{
		m_ani_frame2 += 1;
		m_ani_time2 = 0;
	}
	if (m_ani_frame2 == 8)//�Ō�̃R�}�ɂȂ�ƒe�ۍ폜
	{
		m_ani_frame2 = 0;
		m_hero_hit = false;
		this->SetStatus(false);    //���g�ɍ폜���߂��o��
		Hits::DeleteHitBox(this);  //��l���@�����L����HitBox�ɍ폜����
	
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

	int HitAniData[11] =
	{
		1,2,3,4,5,6,7,8
	};

	//�`�ʃJ���[���@R=RED�@G=Green�@B=Blue�@A=alpha�i���ߏ��j
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	//�u���b�N���������Ă���
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	if (m_hero_hit == false)
	{
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
		Draw::Draw(16, &src, &dst, c, 0);
	}
	else
	{
		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f + (HitAniData[m_ani_frame2] * 72);
		src.m_right = 72.0f + (HitAniData[m_ani_frame2] * 72);
		src.m_bottom = 72.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top = 0.0f + m_y + block->GetScrolly();
		dst.m_left = 0.0f + m_x + block->GetScrollx();
		dst.m_right = 80.0f + m_x + block->GetScrollx();
		dst.m_bottom = 80.0f + m_y + block->GetScrolly();

		//�O�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�Ec�̏������ɕ`��
		Draw::Draw(52, &src, &dst, c, 0);
	
	}
}