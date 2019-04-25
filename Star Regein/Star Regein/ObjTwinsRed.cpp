//�g�p����w�b�_�[�t�@�C��
#include <stdlib.h>
#include <time.h>
#include"GameL\DrawTexture.h"
#include"GameL\WinInputs.h"
#include"GameL\SceneManager.h"
#include"GameL\HitBoxManager.h"
#include"GameL\UserData.h" 

#include"GameHead.h"
#include"ObjTwinsRed.h"
#include "UtilityModule.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

float* g_twinsred_x[20];//�S�Ă̑o�q�i�j��X�ʒu��c������
float* g_twinsred_y[20];//�S�Ă̑o�q�i�j��Y�ʒu��c������

CObjTwinsRed::CObjTwinsRed(float x, float y,int id)
{
	m_px = x;	//�ʒu
	m_py = y;

	m_red_id = id;
}



//�C�j�V�����C�Y
void CObjTwinsRed::Init()
{
	m_hp = 5;        //�̗�
	m_vx = 0.0f;	//�ړ��x�N�g��
	m_vy = 0.0f;
	m_posture = 0.0f;//����(0.0f) ��(4.0f) �E(1.0f) �w��(2.0f)

	m_ani_time = 0;
	m_ani_frame = 1;	//�Î~�t���[���������ɂ���

	m_speed_power = 2.0f;//�ʏ푬�x
	m_ani_max_time = 15;	//�A�j���[�V�����Ԋu��

	m_movey = true; //true=���ʁ@false=�w��
	m_movex = true;	//true=�E�@false=��

					//block�Ƃ̏Փˏ�Ԋm�F�p
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_key_f = false;		//���G���ԍs������
	m_f = false;


	m_bullet_time = 100;
	m_time = 30;

	m_df = true;

	alpha = 1.0;

	srand(time(NULL));

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 40, 40, ELEMENT_NULL, OBJ_TWINS_BLUE, 1);
}

//�A�N�V����
void CObjTwinsRed::Action()
{
	//�`���[�g���A���t���O�������Ă��Ȃ��ꍇ����
	if (g_tutorial_flag == false)
	{

		CObjBlock* pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

		//20���Ԋu�Œe�۔���
		m_bullet_time++;
		if (m_bullet_time > 300 && m_hp > 0)
		{
			m_bullet_time = 0;

			//6����������
			CObjRedBullet*obj_b;
			for (int i = 0; i < 360; i += 60)
			{
				//�p�xi�Ŋp�x�e�۔���
				obj_b = new CObjRedBullet(m_px, m_py, i, 3.0f);
				Objs::InsertObj(obj_b, OBJ_RED_BULLET, 5);
			}
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
		check = CheckWindow(m_px + 19 + pb->GetScrollx(), m_py + 15 + pb->GetScrolly(), 0.0f, 0.0f, 800.0f, 600.0f);
		if (check == true)
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
				m_vx = cos(3.14 / 180 * ar) * 1;
				m_vy = sin(3.14 / 180 * ar) * 1;
			}
		}
		else
		{

		}

		//HitBox�̓��e���X�V
		CHitBox*hit = Hits::GetHitBox(this);
		hit->SetPos(m_px + 19 + pb->GetScrollx(), m_py + 15 + pb->GetScrolly());

		//��l����BLOCK�n���Ƃ̓����蔻��
		if (hit->CheckElementHit(ELEMENT_BLOCK) == true)
		{
			//��l�����u���b�N�Ƃǂ̊p�x�œ������Ă���̂����m�F
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
						m_vx = -0.15f; //�E
					}
					if (r > 45 && r < 135)
					{
						m_vy = 0.15f;//��
					}
					if (r >= 135 && r < 225)
					{
						m_vx = 0.15f;//��
					}
					if (r >= 225 && r < 315)
					{
						m_vy = -0.15f; //��
					}
				}
			}
		}

		//�G��BLOCK�n���Ƃ̓����蔻��
		if (hit->CheckElementHit(ELEMENT_NULL) == true)
		{
			//�G���u���b�N�Ƃǂ̊p�x�œ������Ă���̂����m�F
			HIT_DATA** hit_data;							//�����������ׂ̍��ȏ������邽�߂̍\����
			hit_data = hit->SearchElementHit(ELEMENT_NULL);
			float r = 0;

			for (int i = 0; i < 10; i++)
			{
				if (hit_data[i] != nullptr)
				{
					r = hit_data[i]->r;

					//�p�x�ŏ㉺���E�𔻒�
					if ((r <= 45 && r >= 0) || r >= 315)
					{
						m_vx = -0.15f; //�E
					}
					if (r > 45 && r < 135)
					{
						m_vy = 0.15f;//��
					}
					if (r >= 135 && r < 225)
					{
						m_vx = 0.15f;//��
					}
					if (r >= 225 && r < 315)
					{
						m_vy = -0.15f; //��
					}
				}
			}
		}

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
		//ELEMENT_SKILL_VIRGO�����I�u�W�F�N�g�ƐڐG������
		if (hit->CheckElementHit(ELEMENT_SKILL_VIRGO) == true)
		{
			//�G����l���Ƃǂ̊p�x�œ������Ă��邩���m�F
			HIT_DATA**hit_data;							//�����������ׂ̍��ȏ������邽�߂̍\����
			hit_data = hit->SearchElementHit(ELEMENT_SKILL_VIRGO);//hit_data�Ɏ�l���Ɠ������Ă��鑼�S�Ă�HitBox�Ƃ̏�������

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

		//ELEMENT_BEAMSABER�����I�u�W�F�N�g�ƐڐG������
		if (hit->CheckElementHit(ELEMENT_SUB) == true)
		{
			//�G����l���Ƃǂ̊p�x�œ������Ă��邩���m�F
			HIT_DATA**hit_data;							//�����������ׂ̍��ȏ������邽�߂̍\����
			hit_data = hit->SearchElementHit(ELEMENT_SUB);//hit_data�Ɏ�l���Ɠ������Ă��鑼�S�Ă�HitBox�Ƃ̏�������

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
			g_red_d_flag[m_red_id] = false;
		}
	}
	//�`���[�g���A���t���O�������Ă����瓮���Ȃ��悤�ɂ���
	else
	{
		return;
	}
}

//�h���[
void CObjTwinsRed::Draw()
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
	src.m_top = 64.0f * m_posture;
	src.m_left = 0.0f + (AniData[m_ani_frame] * 64);
	src.m_right = 64.0f + (AniData[m_ani_frame] * 64);
	src.m_bottom = src.m_top + 64.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py + block->GetScrolly();
	dst.m_left = 80.0f + m_px + block->GetScrollx();
	dst.m_right = 0.0f + m_px + block->GetScrollx();
	dst.m_bottom = 80.0f + m_py + block->GetScrolly();


	//�`��
	Draw::Draw(21, &src, &dst, c, 0.0f);
}