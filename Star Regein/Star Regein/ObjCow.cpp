//�g�p����w�b�_�[�t�@�C��
#include <stdlib.h>
#include <time.h>
#include"GameL\DrawTexture.h"
#include"GameL\WinInputs.h"
#include"GameL\SceneManager.h"
#include"GameL\HitBoxManager.h"
#include"GameL\UserData.h" 

#include"GameHead.h"
#include"ObjCow.h"
#include "UtilityModule.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

float* g_cow_x[20];//�S�Ă̋���X�ʒu��c������
float* g_cow_y[20];//�S�Ă̋���Y�ʒu��c������

CObjCow::CObjCow(float x, float y)
{
	m_px = x;	//�ʒu
	m_py = y;
}



//�C�j�V�����C�Y
void CObjCow::Init()
{
	m_hp = 5;        //�̗�
	m_vx = 0.0f;	//�ړ��x�N�g��
	m_vy = 0.0f;
	m_posture = 0.0f;//����(0.0f) ��(1.0f) �E(2.0f) �w��(3.0f)

	m_ani_time = 0;
	m_ani_frame = 1;	//�Î~�t���[���������ɂ���

	m_speed_power = 2.0f;//�ʏ푬�x
	m_ani_max_time = 10;	//�A�j���[�V�����Ԋu��

	m_movey = true; //true=�w�ʁ@false=����
	m_movex = true;	//true=�E�@false=��

	//block�Ƃ̏Փˏ�Ԋm�F�p
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_key_f = false;		//���G���ԍs������
	m_f = false;

	m_btime = 0;

	m_time = 30;

	m_df = true;

	alpha = 1.0;

	srand(time(NULL));

	//�����蔻��p��HitBox���쐬
//	Hits::SetHitBox(this, m_px + 9, m_py + 7, 80, 80, ELEMENT_ENEMY, OBJ_COW, 1);
	Hits::SetHitBox(this, m_px + 2, m_py + 4, 64, 64, ELEMENT_ENEMY, OBJ_COW, 1);
}

//�A�N�V����
void CObjCow::Action()
{
	m_btime++;

	//�u���b�N�Փ˂Ō����ύX
	if (m_hit_up == true)
	{
		m_movey = true;
	}
	if (m_hit_down == true)
	{
		m_movey = false;
	}
	if (m_hit_left == true)
	{
		m_movex = false;
	}
	if (m_hit_right == true)
	{
		m_movex = true;
	}

	//����
	if (m_movey == true)
	{
		m_vy = 1;
		m_posture = 0.0f;
		m_ani_time += 1;
	}
	if (m_movey == false)
	{
		m_vy = -1;
		m_posture = 3.0f;
		m_ani_time += 1;
	}
	if (m_movex == true)
	{
		m_vx = 1;
		m_posture = 1.0f;
		m_ani_time += 1;
	}
	if (m_movex == false)
	{
		m_vx = -1;
		m_posture = 2.0f;
		m_ani_time += 1;
	}

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
	pb->BlockHit(&m_px, &m_py, true,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&m_block_type
	);

	//��l���̈ʒu���擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX();
	float hy = hero->GetY();

	//UtilityModule�̃`�F�b�N�֐��ɏꏊ�Ɨ̈��n���A�̈�O������
	bool check;
	check = CheckWindow(m_px + pb->GetScrollx(), m_py + pb->GetScrolly(), -10.0f, -10.0f, 810.0f, 610.0f);
	if (check == true)
	{
		//��l���@�����݂���ꍇ�A�U���p�x�̌v�Z����
		if (hero != nullptr)
		{

			float x;
			float y;

			x = 400 - (m_px + pb->GetScrollx());
			y = 300 - (m_py + pb->GetScrolly());

			float ar = GetAtan2Angle(x, y);

			//�G�̌��݂̌����Ă���p�x�����
			float br = GetAtan2Angle(m_vx, m_vy);

			//�p�x�ŏ㉺���E�𔻒�
			if ((ar < 45 && ar>0) || ar > 315)
			{
				//�E
				m_posture = 1.0f;
				m_ani_time += 1;
			}

			if (ar > 45 && ar < 135)
			{
				//��
				m_posture = 0.0f;
				m_ani_time += 1;
			}
			if (ar > 135 && ar < 225)
			{
				//��
				m_posture = 2.0f;
				m_ani_time += 1;
			}
			if (ar > 225 && ar < 315)
			{
				//��
				m_posture = 3.0f;
				m_ani_time += 1;

			}

			//��l���@�ƓG�p�x������܂�ɂ��������ꂽ��
			m_vx = cos(3.14 / 180 * ar) * 2;
			m_vy = sin(3.14 / 180 * ar) * 2;
		}
	}
	else
	{
		if (m_btime <= 500)
		{
			m_vy = 0;
			m_movex = true;
		}
		if (m_btime >= 501 && m_btime <= 1000)
		{
			m_vx = 0;
			m_movey = false;
		}
		if (m_btime >= 1001 && m_btime <= 1500)
		{
			m_vy = 0;
			m_movex = false;
		}
		if (m_btime >= 1501 && m_btime <= 2000)
		{
			m_vx = 0;
			m_movey = true;
		}
		if (m_btime >= 2001)
			m_btime = 0;
	}

	//HitBox�̓��e���X�V
	CHitBox*hit = Hits::GetHitBox(this);
//	hit->SetPos(m_px + 9 + pb->GetScrollx(), m_py + 7 + pb->GetScrolly());
	hit->SetPos(m_px + 2 + pb->GetScrollx(), m_py + 4 + pb->GetScrolly());

	//ELEMENT_MAGIC�����I�u�W�F�N�g�ƐڐG������
	if (hit->CheckElementHit(ELEMENT_BEAMSABER) == true)
	{
		//�G����l���Ƃǂ̊p�x�œ������Ă��邩���m�F
		HIT_DATA**hit_data;							//�����������ׂ̍��ȏ������邽�߂̍\����
		hit_data = hit->SearchElementHit(ELEMENT_BEAMSABER);//hit_data�Ɏ�l���Ɠ������Ă��鑼�S�Ă�HitBox�Ƃ̏�������

		for (int i = 0; i < hit->GetCount(); i++)
		{
			//�U���̍��E�ɓ���������
			if (hit_data[i] == nullptr)
				continue;

			float r = hit_data[i]->r;


			if ((r < 45 && r >= 0) || r > 315)
			{
				m_vx = -20.0f;//���Ɉړ�������
			}
			if (r >= 45 && r < 135)
			{
				m_vy = 20.0f;//��Ɉړ�������
			}
			if (r >= 135 && r < 225)
			{
				m_vx = 20.0f;//�E�Ɉړ�������
			}
			if (r >= 225 && r < 315)
			{
				m_vy = -20.0f;//�����Ɉړ�������
			}
		}

		m_hp -= 1;
		m_f = true;
		m_key_f = true;
		hit->SetInvincibility(true);
		
	}

	if (m_f == true)
	{
		m_time--;

	}

	if (m_time <= 0)
	{
		m_f = false;
		hit->SetInvincibility(false);
		
		m_time = 30;

	}


	//�ʒu�̍X�V
	m_px += m_vx*1.0;
	m_py += m_vy*1.0;

	//HP��0�ɂȂ�����j��
	if (m_hp == 0)
	{
		//�G�폜
		alpha = 0.0f;
		hit->SetInvincibility(true);

		CObjMiniMap*map = (CObjMiniMap*)Objs::GetObj(OBJ_MINIMAP);
		map->Setdcow(true);
	}
}

//�h���[
void CObjCow::Draw()
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
	src.m_top = 48.0f * m_posture;
	src.m_left = 0.0f + (AniData[m_ani_frame] * 48);
	src.m_right = 48.0f + (AniData[m_ani_frame] * 48);
	src.m_bottom = src.m_top + 48.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py + block->GetScrolly();
	dst.m_left = 64.0f + m_px + block->GetScrollx();
	dst.m_right = 0.0f + m_px + block->GetScrollx();
	dst.m_bottom = 64.0f + m_py + block->GetScrolly();


	//�`��
	Draw::Draw(3, &src, &dst, c, 0.0f);
}