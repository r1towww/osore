//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

//�g�p����w�b�_�[�t�@�C��
#include "GameHead.h"
#include "ObjSkillBullet.h"
#include "UtilityModule.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjSkillBullet::CObjSkillBullet(float x, float y, float r)
{
	m_gx = x;
	m_gy = y;
	m_r = r;
}

//�C�j�V�����C�Y
void CObjSkillBullet::Init()
{
	//�ړ��ʂ̏�����
	m_vx = 0.0f;
	m_vy = 0.0f;

	//�e�폜�̃J�E���g������
	m_time = 0.0f;

	//���e�t���O������
	m_hit_flag = false;

	m_vx = cos(3.14f / 180.0f*m_r);
	m_vy = sin(3.14f / 180.0f*m_r);

	m_ani_frame = 0;
	m_ani_time = 0;

	m_ani = 0;
	m_ani_time = 0;
	m_ani_stop = 0;

	CObjBlock* pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_gx + pb->GetScrollx(), m_gy + pb->GetScrolly(), 25, 25, ELEMENT_SUB, OBJ_SKILL_BULLET, 1);
}

//�A�N�V����
void CObjSkillBullet::Action()
{
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

	//------------�o�q���e��----------------
	CObjBlock* pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBox�̓��e���X�V
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_gx + pb->GetScrollx(), m_gy + pb->GetScrolly());

	//�ړ�
	m_gx += m_vx * HERO_VEC;
	m_gy -= m_vy * HERO_VEC;

	m_time++;

	//�e�G�Ɠ������Ă��邩�m�F
	if (hit->CheckObjNameHit(OBJ_COW) != nullptr ||
		hit->CheckObjNameHit(OBJ_TWINS_BLUE) != nullptr ||
		hit->CheckObjNameHit(OBJ_TWINS_RED) != nullptr ||
		hit->CheckObjNameHit(OBJ_WOMAN) != nullptr ||
		hit->CheckObjNameHit(OBJ_LEO) != nullptr ||
		hit->CheckObjNameHit(OBJ_LIBRA) != nullptr)//�������Ă�����擾  
	{
		m_hit_flag = true;
		m_vx = 0;
		m_vy = 0;
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

	if (m_time >= 100)

	{
		m_time = 0.0f;

		this->SetStatus(false);    //���g�ɍ폜���߂��o��
		Hits::DeleteHitBox(this);  //��l���@�����L����HitBox�ɍ폜����
		m_hit_flag = false;
	}

	//�ʒu�̍X�V
	m_gx += m_vx;
	m_gy += m_vy;
}
//�h���[
void CObjSkillBullet::Draw()
{

	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//�e�ۂ����������Ƃ��̉摜�`��
	if (m_hit_flag == true)
	{
		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 32.0f;
		src.m_bottom = 32.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top = 0.0f + m_gy + block->GetScrolly();
		dst.m_left = 0.0f + m_gx + block->GetScrollx();
		dst.m_right = 64.0f + m_gx + block->GetScrollx();
		dst.m_bottom = 64.0f + m_gy + block->GetScrolly();

		//�\��
		Draw::Draw(51, &m_eff, &dst, c, 0.0f);
	}
	//
	else if (g_gemini_bullet_check == false)
	{
		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 16.0f;
		src.m_bottom = 16.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top = 0.0f + m_gy + block->GetScrolly();
		dst.m_left = 0.0f + m_gx + block->GetScrollx();
		dst.m_right = 25.0f + m_gx + block->GetScrollx();
		dst.m_bottom = 25.0f + m_gy + block->GetScrolly();

		//�O�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�Ec�̏������ɕ`��
		Draw::Draw(16, &src, &dst, c, 0);
	}
	else if (g_gemini_bullet_check == true)
	{
		//�؂���ʒu�̐ݒ�
		src.m_top = 16.0f;
		src.m_left = 0.0f;
		src.m_right = 16.0f;
		src.m_bottom = 32.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top = 0.0f + m_gy + block->GetScrolly();
		dst.m_left = 0.0f + m_gx + block->GetScrollx();
		dst.m_right = 25.0f + m_gx + block->GetScrollx();
		dst.m_bottom = 25.0f + m_gy + block->GetScrolly();

		//�O�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�Ec�̏������ɕ`��
		Draw::Draw(16, &src, &dst, c, 0);
	}
}
