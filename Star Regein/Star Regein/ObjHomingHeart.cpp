//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"


//�g�p����w�b�_�[�t�@�C��

#include "ObjHomingHeart.h"
#include "GameHead.h"
#include "UtilityModule.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;


//�R���X�g���N�^
CObjHomingHeart::CObjHomingHeart(float x, float y)
{
	m_x = x;
	m_y = y;
}

//�C�j�V�����C�Y
void CObjHomingHeart::Init()
{
	//�ړ��ʂ̏�����
	m_vx = 0.0f;
	m_vy = 0.0f;

	//�e�폜�̃J�E���g������
	m_time = 0.0f;

	//���e�t���O������
	m_hit_flag = false;

	m_ani_frame = 0;
	m_ani_time = 0;

	m_eff.m_top = 0;
	m_eff.m_left = 0;
	m_eff.m_right = 220;
	m_eff.m_bottom = 203;
	m_ani = 0;
	m_ani_time = 0;
	m_ani_stop = 0;

	//�����蔻����Z�b�g
	Hits::SetHitBox(this, m_x, m_y, 32, 28, ELEMENT_ENEMY, OBJ_HOMING_HEART, 1);

}

//�A�N�V����
void CObjHomingHeart::Action()
{
	//�s�������䂳��Ă���ꍇ�i���j���[��ʁj
	if (g_move_stop_flag == true)
		return;	//�s���𐧌�

	//�傩�珬
	RECT_F ani_src[12] =
	{
		{ 0,   0,    32, 32 },
		{ 0,  32,    64, 32 },
		{ 0,  64,    96, 32 },
		{ 0,  96,   128, 32 },
		{ 0, 128,   160, 32 },
		{ 0, 160,   192, 32 },
		{ 0, 192,   224, 32 },
		{ 0, 224,   256, 32 },
		{ 0, 256,   288, 32 },
		{ 0, 288,   320, 32 },
		{ 0, 320,   352, 32 },
	};

	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	CObjBlock* pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

		//��l���@�����݂���ꍇ�A�U���p�x�̌v�Z����
		if (hero != nullptr)
		{
			float x;
			float y;

			x = 375 - (m_x + pb->GetScrollx());
			y = 275 - (m_y + pb->GetScrolly());

			float ar = GetAtan2Angle(x, y);

			//��l���@�ƓG�p�x������܂�ɂ��������ꂽ��
			m_vx = cos(3.14 / 180 * ar) * 3;
			m_vy = sin(3.14 / 180 * ar) * 3;
		}


	//���g��HitBox�������Ă���
	CHitBox* hit = Hits::GetHitBox(this);

	//��l���Ɠ������Ă��邩�m�F
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr || hit->CheckObjNameHit(OBJ_BEAMSABER) != nullptr)
	{
		m_hit_flag = true;//�A�j���[�V�����J�n
		m_vx = 0.0f;
		m_vy = 0.0f;
	}

	if (m_hit_flag == true)
	{
		//�A�j���[�V�����̃R�}�Ԋu����
		if (m_ani_time > 0)
		{

			m_ani++;	//�A�j���[�V�����̃R�}���P�i�߂�
			m_ani_time = 0;

			m_eff = ani_src[m_ani];//�A�j���[�V������RECT�z�񂩂�m_ani�Ԗڂ�RECT���擾
			m_ani_stop++;
			if (m_ani_stop >= 11)
			{
				m_eff.m_top = 0;
				m_eff.m_left = 0;
				m_eff.m_right = 220;
				m_eff.m_bottom = 203;

				this->SetStatus(false);
				Hits::DeleteHitBox(this);

			}
		}
		else
		{
			m_ani_time++;
		}
	}

	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�쐬����HitBox�X�V�p�̓���������o��
	hit->SetPos(m_x + block->GetScrollx(), m_y + block->GetScrolly());//���������V�����ʒu�i��l���̈ʒu�j���ɒu��������

	//�ʒu�̍X�V
	m_x += m_vx*1.0;
	m_y += m_vy*1.0;

	m_time++;

	if (m_time >= 200)
	{
		m_time = 0.0f;

		this->SetStatus(false);    //���g�ɍ폜���߂��o��
		Hits::DeleteHitBox(this);  //��l���@�����L����HitBox�ɍ폜����
	}
}

//�h���[
void CObjHomingHeart::Draw()
{

	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,100.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);


	if (m_hit_flag == true)
	{
		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 32.0f;
		src.m_bottom = 32.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top = 0.0f + m_y + block->GetScrolly();
		dst.m_left = 0.0f + m_x + block->GetScrollx();
		dst.m_right = 64.0f + m_x + block->GetScrollx();
		dst.m_bottom = 64.0f + m_y + block->GetScrolly();

		//�\��
		Draw::Draw(51, &m_eff, &dst, c, 0.0f);

	}
	else {
		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 32.0f;
		src.m_bottom = 28.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top = 0.0f + m_y + block->GetScrolly();
		dst.m_left = 0.0f + m_x  + block->GetScrollx();
		dst.m_right = 32.0f + m_x  + block->GetScrollx();
		dst.m_bottom = 32.0f + m_y  + block->GetScrolly();

		//�\��
		Draw::Draw(50, &src, &dst, c, 0.0f);
	}
}
