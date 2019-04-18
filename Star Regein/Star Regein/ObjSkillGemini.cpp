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
	m_px = x;	//�ʒu
	m_py = y;
}

//�C�j�V�����C�Y
void CObjSkillGemini::Init()
{
	m_vx = 0.0f;	//�ړ��x�N�g��
	m_vy = 0.0f;
	m_posture = 0.0f;//����(0.0f) ��(1.0f) �E(2.0f) �w��(3.0f)

	m_ani_time = 0;
	m_ani_frame = 1;	//�Î~�t���[���������ɂ���

	m_speed_power = 2.0f;//�ʏ푬�x
	m_ani_max_time = 15;	//�A�j���[�V�����Ԋu��
	
	m_movey = false; //true=���ʁ@false=�w��
	m_movex = false;	//true=�E�@false=��

	//block�Ƃ̏Փˏ�Ԋm�F�p
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px + 15, m_py + 15, 50, 50, ELEMENT_GREEN, OBJ_SKILL_GEMINI, 1);
}

//�A�N�V����
void CObjSkillGemini::Action()
{
	int Direction = 0; // �K���ȕϐ��A���ɂ���Ȃ�錾�K�v�Ȃ�

	srand(time(NULL)); // �����_������������

	Direction = rand() % 4; // ���̂悤�ɋL�q�����npc�ɂ͂O�`3�܂ł̒l������܂�

	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}

	if (m_ani_frame == 3)
	{
		m_ani_frame = 0;
	}

	//�u���b�N�Ƃ̓����蔻����s
	CObjBlock* pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockHit(&m_px, &m_py, false,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy
	);

	//��l���̈ʒu���擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	if (hero != nullptr)
	{
		float hx = hero->GetX();
		float hy = hero->GetY();
	}



	//UtilityModule�̃`�F�b�N�֐��ɏꏊ�Ɨ̈��n���A�̈�O������
	bool check;
	check = CheckWindow(m_px + pb->GetScrollx(), m_py + pb->GetScrolly(), 100.0f, 100.0f, 700.0f, 500.0f);
	if (check ==true)
	{
		//��l���@�����݂���ꍇ�A�U���p�x�̌v�Z����
		if (hero != nullptr)
		{
			float x;
			float y;

			x = 375 - (m_px + pb->GetScrollx());
			y = 275 - (m_py + pb->GetScrolly());

			float ar = GetAtan2Angle(x, y);

			//�G�̌��݂̌����Ă���p�x�����
			float br = GetAtan2Angle(m_vx, m_vy);

			//�p�x�ŏ㉺���E�𔻒�
			if ((ar < 45 && ar>0) || ar > 315)
			{
				//��
				m_posture = 4.0f;
				m_ani_time += 1;
			}

			if (ar > 45 && ar < 135)
			{
				//��
				m_posture = 3.0f;
				m_ani_time += 1;
			}
			if (ar > 135 && ar < 225)
			{
				//�E
				m_posture = 2.0f;
				m_ani_time += 1;
			}
			if (ar > 225 && ar < 315)
			{
				//��
				m_posture = 1.0f;
				m_ani_time += 1;

			}

			//��l���@�ƓG�p�x������܂�ɂ��������ꂽ��
			m_vx = cos(3.14 / 180 * ar) * 3;
			m_vy = sin(3.14 / 180 * ar) * 3;
		}
	}
	else
	{

	
	}
	
	//HitBox�̓��e���X�V
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + 15 + pb->GetScrollx(), m_py + 15 + pb->GetScrolly());

	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		//�G���u���b�N�Ƃǂ̊p�x�œ������Ă���̂����m�F
		HIT_DATA** hit_data;							//�����������ׂ̍��ȏ������邽�߂̍\����
		hit_data = hit->SearchObjNameHit(OBJ_HERO);	//hit_date�Ɏ�l���Ɠ������Ă��鑼�S�Ă�HitBox�Ƃ̏�������

		float r = 0;

		for (int i = 0; i < 10; i++)
		{
			if (hit_data[i] != nullptr)
			{
				r = hit_data[i]->r;

				//�p�x�ŏ㉺���E�𔻒�
				if ((r <= 45 && r >= 0) || r >= 315)
				{
					m_vx = -0.20f; //�E
				}
				if (r > 45 && r < 135)
				{
					m_vy = 0.20f;//��
				}
				if (r >= 135 && r < 225)
				{
					m_vx = 0.20f;//��
				}
				if (r >= 225 && r < 315)
				{
					m_vy = -0.20f; //��
				}
			}
		}
	}

	//�G��BLOCK�n���Ƃ̓����蔻��
	if (hit->CheckElementHit(ELEMENT_BLOCK) == true)
	{
		//�G���u���b�N�Ƃǂ̊p�x�œ������Ă���̂����m�F
		HIT_DATA** hit_data;							//�����������ׂ̍��ȏ������邽�߂̍\����
		hit_data = hit->SearchElementHit(ELEMENT_BLOCK);	//hit_date�Ɏ�l���Ɠ������Ă��鑼�S�Ă�HitBox�Ƃ̏�������

		float r = 0;

		for (int i = 0; i < 10; i++)
		{
			if (hit_data[i] != nullptr)
			{
				r = hit_data[i]->r;

				//�p�x�ŏ㉺���E�𔻒�
				if ((r <= 45 && r >= 0) || r >= 315)
				{
					m_movex = false;
				}
				if (r > 45 && r < 135)
				{
					m_movey = true;
				}
				if (r >= 135 && r < 225)
				{
					m_movex = true;
				}
				if (r >= 225 && r < 315)
				{
					m_movey = false;
				}
			}
		}
	}


	//�ʒu�̍X�V
	m_px += m_vx;
	m_py += m_vy;
}

//�h���[
void CObjSkillGemini::Draw()
{
	//�A�j���[�V����
	int AniData[5] =
	{
		0,1,2,3,0,
	};

	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

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
	dst.m_top    =  0.0f + m_py + block->GetScrolly();
	dst.m_left   = 80.0f + m_px + block->GetScrollx();
	dst.m_right  =  0.0f + m_px + block->GetScrollx();
	dst.m_bottom = 80.0f + m_py + block->GetScrolly();

	//�\��
	Draw::Draw(1, &src, &dst, c, 0.0f);
}