//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

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

	//���e�t���O������
	m_hit_flag = false;
	m_f = false;	//�G�t�F�N�g���t���O�̏�����
	m_bullet_f = false;	//���eSE�t���O�̏�����
	m_flag = false;
	//��l���̌������擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	m_posture = hero->GetPos();

	m_ani_frame = 0;
	m_ani_time = 0;

	m_eff.m_top = 0;
	m_eff.m_left = 0;
	m_eff.m_right = 220;
	m_eff.m_bottom = 203;
	m_ani = 0;
	m_ani_time = 0;
	m_ani_stop = 0;

	//��l���̌����ɂ���ăn�[�g�e���o�������C������ς���
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
		Hits::SetHitBox(this, m_x + m_pos_x, m_y + m_pos_y, 32, 28, ELEMENT_SKILL_VIRGO, OBJ_SKILL_VIRGO, 1);
	else if (g_posture == 2) //��
		Hits::SetHitBox(this, m_x + m_pos_x, m_y + m_pos_y, 32, 28, ELEMENT_SKILL_VIRGO, OBJ_SKILL_VIRGO, 1);
	else if (g_posture == 3) //��
		Hits::SetHitBox(this, m_x + m_pos_x, m_y + m_pos_y, 32, 28, ELEMENT_SKILL_VIRGO, OBJ_SKILL_VIRGO, 1);
	else if (g_posture == 4) //�E
		Hits::SetHitBox(this, m_x + m_pos_x, m_y + m_pos_y, 32, 28, ELEMENT_SKILL_VIRGO, OBJ_SKILL_VIRGO, 1);

}

//�A�N�V����
void CObjSkillVirgo::Action()
{
	//�t���O���I�t�̏ꍇ
	if (m_f == false)
	{
		Audio::Start(14);	//SE��炷
		m_f = true;	//�P�x�������悤�Ƀt���O���I���ɂ���
	}



	//���e�A�j���[�V����
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

	//��l���̌����ɂ���Ēe�̏o�������ς���
	if (m_posture == 1)//��
	{
		m_vy -= MOVE;
		m_y += m_vy;
	}
	if (m_posture == 2)//��
	{
		m_vx -= MOVE;
		m_x += m_vx;
	}
	if (m_posture == 3)//��
	{
		m_vy += MOVE;
		m_y += m_vy;
	}
	 if (m_posture == 4)//�E
	{
		m_vx += MOVE;
		m_x += m_vx;
	}


	//���g��HitBox�������Ă���
	CHitBox* hit = Hits::GetHitBox(this);
	CObjBlock* pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);


	//�e�G�Ɠ������Ă��邩�m�F
	if (hit->CheckObjNameHit(OBJ_COW)        != nullptr ||
		hit->CheckObjNameHit(OBJ_LIBRA)      != nullptr ||
		hit->CheckObjNameHit(OBJ_TWINS_BLUE) != nullptr ||
		hit->CheckObjNameHit(OBJ_TWINS_RED)  != nullptr ||
		hit->CheckObjNameHit(OBJ_WOMAN)      != nullptr ||
		hit->CheckObjNameHit(OBJ_LEO)        != nullptr || 
		hit->CheckObjNameHit(OBJ_BOSS)		 != nullptr || 
		hit->CheckObjNameHit(OBJ_SNAKE)		 != nullptr)//�������Ă�����擾  
	{
		//1���ɂ��P�񂾂��񕜂���悤�ɒ���
		if (m_flag == false)
		{
			//�t���O���I���̏ꍇ
			if (m_bullet_f == false)
			{
				Audio::Start(15);	//���eSE��炷
				m_bullet_f = true;	//�t���O���I���ɂ��āA�P�x�����炷
			}

			m_hit_flag = true;//�A�j���[�V�����J�n
			m_vx = 0.0f;
			m_vy = 0.0f;

			//HP�������Ă�����30��
			if (g_hp < 100.0f)
			{
				//70.0f�ȏ�̏ꍇ
				if (g_hp >= 70.0f)
				{
					g_hp = g_max_hp;	//�ő�܂ŉ񕜂�����
				}
				else
				{
					g_hp += 30.0f;	//����ȊO��30.0f�񕜂�����
				}

			}
			m_flag = true;
		}
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

			}
		}
		else
		{
			m_ani_time++;
		}

		
	}

	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�쐬����HitBox�X�V�p�̓���������o��
	hit->SetPos(m_x + m_pos_x + block->GetScrollx(), m_y + m_pos_y + block->GetScrolly());//���������V�����ʒu�i��l���̈ʒu�j���ɒu��������
	m_time++;
	if (m_time >= 25)
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
		dst.m_top = 0.0f + m_y + m_pos_y + block->GetScrolly();
		dst.m_left = 0.0f + m_x + m_pos_x + block->GetScrollx();
		dst.m_right = 32.0f + m_x + m_pos_x + block->GetScrollx();
		dst.m_bottom = 32.0f + m_y + m_pos_y + block->GetScrolly();

		//�\��
		Draw::Draw(50, &src, &dst, c, 0.0f);
	}
}
