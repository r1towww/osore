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
float g_Leo_cnt;


CObjCow::CObjCow(float x, float y, int id)
{
	m_px = x + 375.0f;	//�ʒu
	m_py = y + 275.0f;

	m_cow_id = id;
	g_enemy_cnt++;	//�G�̑����̃J�E���g
}

//�C�j�V�����C�Y
void CObjCow::Init()
{
	m_hp = 1;        //�̗�
	m_vx = 0.0f;	//�ړ��x�N�g��
	m_vy = 0.0f;
	m_posture = 0.0f;//����(0.0f) ��(1.0f) �E(2.0f) �w��(3.0f)

	m_ani_time = 0;
	m_ani_timeB = 0;
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
	m_kill_f = false;	//�L���J�E���g�p�t���O�̏�����

	g_Leo_cnt = 0.0f;

	m_invincible_flag = false;

	m_time = 30;

	m_df = true;
	count = 0;

	m_alpha = 1.0;


	
	//���ŃA�j���[�V�����p
	m_ani_delete = 0;
	m_ani_count = 0;
	m_ani_max_count = 10;
	m_ani_frame_delete = 1;

	//���폜�t���O
	m_cow_delete = false;

	srand(time(NULL));


	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px + 2, m_py + 4, 64, 64, ELEMENT_NULL, OBJ_COW, 1);
}

//�A�N�V����
void CObjCow::Action()
{
	//�s�������䂳��Ă���ꍇ�i���j���[��ʁj
	if (g_move_stop_flag == true || g_tutorial_flag == true)
		return;	//�s���𐧌�


	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}

	if (m_ani_frame == 3)
	{
		m_ani_frame = 1;
	}

	//�s�������䂳��Ă���ꍇ�i���j���[��ʁj
	if (g_move_stop_flag == true || g_tutorial_flag == true)
		return;	//�s���𐧌�


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

	if (g_stan_cow_flag[m_cow_id] == false)
	{
		//UtilityModule�̃`�F�b�N�֐��ɏꏊ�Ɨ̈��n���A�̈�O������
		bool check;
		check = CheckWindow(m_px + pb->GetScrollx(), m_py + pb->GetScrolly(), 0.0f, 0.0f, 800.0f, 600.0f);
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
					//�E
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

		}
	}
	else
	{
		m_vx = 0.0f;
		m_vy = 0.0f;
	}

	//HitBox�̓��e���X�V
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + 2 + pb->GetScrollx(), m_py + 4 + pb->GetScrolly());


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

	//ELEMENT_BEAMSABER�����I�u�W�F�N�g�ƐڐG������
	if (m_invincible_flag == false)
	{
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

			m_hp -= g_attack_power;	//hp����l���̍U���͕����炷
			m_f = true;
			m_invincible_flag = true;
			m_key_f = true;

		}

		//ELEMENT_VIRGO_SKILL�����I�u�W�F�N�g�ƐڐG������
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

			m_hp -= g_attack_power;	//hp����l���̍U���͕����炷
			m_f = true;
			m_invincible_flag = true;
			m_key_f = true;

		}

		//ELEMENT_SUB�����I�u�W�F�N�g�ƐڐG������
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
			m_invincible_flag = true;
			m_key_f = true;

		}

	}
	//ELEMENT_SKILL_LEO�����I�u�W�F�N�g�ƐڐG������
	if (hit->CheckElementHit(ELEMENT_SKILL_LEO) == true)
	{
		//�G����l���Ƃǂ̊p�x�œ������Ă��邩���m�F
		HIT_DATA**hit_data;							//�����������ׂ̍��ȏ������邽�߂̍\����
		hit_data = hit->SearchElementHit(ELEMENT_SKILL_LEO);//hit_data�Ɏ�l���Ɠ������Ă��鑼�S�Ă�HitBox�Ƃ̏�������
		//�q�b�g����on
		g_stan_cow_flag[m_cow_id] = true;
	}

	//�������̃q�b�g���肪on�̎��X�^��
	if (g_stan_cow_flag[m_cow_id] == true)
	{

		g_Leo_cnt += 1.0f;


		//�A�j���[�V�����̃R�}�Ԋu����
		if (m_ani_timeB < 0)
		{

			m_ani_frame++;	//�A�j���[�V�����̃R�}���P�i�߂�
			m_ani_timeB = 10;

			if (g_Leo_cnt >= 200.0f)
			{
				g_Leo_cnt = 0.0f;
				g_stan_cow_flag[m_cow_id] = false;
			}
		}

		else
		{
			m_ani_timeB--;
		}
	}

	if (m_f == true)
	{
		m_time--;
		m_alpha = ALPHAUNDER;

	}
	if (m_time <= 0)
	{
		m_f = false;
		m_invincible_flag = false;
		m_alpha = ALPHAORIGIN;

		m_time = 30;
	}


	//�ʒu�̍X�V
	m_px += m_vx*1.0;
	m_py += m_vy*1.0;


	//HP��0�ɂȂ�����j��
	if (m_hp <= 0)
	{
		//���폜�t���O
		m_cow_delete = true;
		hit->SetInvincibility(true);

	};
	//���ŃA�j���[�V�����̃R�}��i�߂�
	if (m_cow_delete == true)
	{
		m_ani_count += 1;
	}
	//�ړ��A�j���[�V����
	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}

	if (m_ani_frame == 3)
	{
		m_ani_frame = 1;
	}
	//���ŃA�j���[�V����
	if (m_ani_count > m_ani_max_count)
	{
		m_ani_frame_delete += 1;
		m_ani_count = 0;
	}
	if (m_ani_frame_delete == 3)
	{
		m_ani_frame_delete = 0;
		//�t���O���I�t�̏ꍇ
		if (m_kill_f == false)
		{
			g_kill_cnt++;	//�L���J�E���g�𑝂₷
			m_kill_f = true;//�t���O���I���ɂ��ē���Ȃ��悤�ɂ���
		}
		//�G�폜
		m_alpha = 0.0f;	
		g_cow_d_flag[m_cow_id] = false;
		this->SetStatus(false);    //���g�ɍ폜���߂��o��
	}
	CObjMiniMap*map = (CObjMiniMap*)Objs::GetObj(OBJ_MINIMAP);
}

//�h���[
void CObjCow::Draw()
{
	int AniData[4] =
	{ 1,0,2,0, };

	int DeleteData[4] =
	{1,2,3,4, };

	int AniDataB[6] =
	{ 0,1,2,3,4,0 };

	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,m_alpha };
	float d[4] = { 1.0f,1.0f,1.0f,1.0f };

	float cB[4] = { 1.0f,1.0f,1.0f,0.5f };

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu

	//�u���b�N���������Ă���
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	if (m_cow_delete == false)
	{
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
	else if (m_cow_delete == true)
	{
		//���ŃA�j���[�V����
		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f + (DeleteData[m_ani_frame_delete] * 192);
		src.m_right = 192.0f + (DeleteData[m_ani_frame_delete] * 192);
		src.m_bottom = src.m_top + 192.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top = 0.0f + m_py + block->GetScrolly();
		dst.m_left = 0.0f + m_px + block->GetScrollx();
		dst.m_right = 64.0f + m_px + block->GetScrollx();
		dst.m_bottom = 64.0f + m_py + block->GetScrolly();

		//�\��
		Draw::Draw(80, &src, &dst, d, 0.0f);
	}



	if (g_stan_cow_flag[m_cow_id] == true)
	{
		RECT_F src;//�`�挳�؂���ʒu
		RECT_F dst;//�`���\���ʒu

				   //�u���b�N���������Ă���
		CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f * m_posture;
		src.m_left = 0.0f + (AniDataB[m_ani_frame] * 192);
		src.m_right = 192.0f + (AniDataB[m_ani_frame] * 192);
		src.m_bottom = src.m_top + 192.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top =   -5.0f + m_py + block->GetScrolly();
		dst.m_left =   94.0f + m_px + block->GetScrollx();
		dst.m_right = -30.0f + m_px + block->GetScrollx();
		dst.m_bottom = 85.0f + m_py + block->GetScrolly();

		//�`��
		Draw::Draw(49, &src, &dst, cB, 0.0f);
	}
}