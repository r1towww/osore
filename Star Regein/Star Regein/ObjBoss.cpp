//�g�p����w�b�_�[�t�@�C��
#include <stdlib.h>
#include <time.h>
#include"GameL\DrawTexture.h"
#include"GameL\WinInputs.h"
#include"GameL\SceneManager.h"
#include"GameL\HitBoxManager.h"
#include"GameL\UserData.h" 
#include<time.h>
#include "GameL\Audio.h"

#include"GameHead.h"
#include"ObjBoss.h"
#include "UtilityModule.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

float* g_boss_x;
float* g_boss_y;
bool g_dead_flag = false;
bool g_Voice_flag = false;
bool g_End_flag = false;
float g_boss_hp;

CObjBoss::CObjBoss(float x, float y)
{
	m_px = x + 180.0f;	//�ʒu
	m_py = y + 275.0f;
}

//�C�j�V�����C�Y
void CObjBoss::Init()
{
	g_boss_hp = 1;        //�̗́i����40�j
	m_vx = 0.0f;	//�ړ��x�N�g��
	m_vy = 0.0f;
	m_posture = 0.0f;//����(0.0f) ��(1.0f) �E(2.0f) �w��(3.0f)

	m_ani_time = 0;
	m_ani_frame = 0;	//�Î~�t���[���������ɂ���

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

	g_Leo_cnt = 0.0f;

	m_time = 30;

	m_rand = 0;

	m_attack_pattern = 0;

	m_snake_c = 0;

	m_imposition_t = 0;

	m_bullet_t = 0;

	m_attack_key_f = true;

	m_invincible_flag = false;

	m_attack_f = false;
	m_beam_f = false;

	m_df = true;
	count = 0;

	
	m_alpha = 1.0;

	srand(time(NULL));

	//���[�v�A�j���[�V�����֘A������
	m_warp_eff.m_top = 0;	//�G�t�F�N�g�����l�̏�����
	m_warp_eff.m_left = 0;
	m_warp_eff.m_right = 192;
	m_warp_eff.m_bottom = 192;

	m_warp_ani = 0;			//�A�j���[�V�����p
	m_warp_ani_time = 0;		//�A�j���[�V�����Ԋu�^�C��

	m_warp_flag = false;
	m_warp_time = 200;

	//���S�G�t�F�N�g
	m_dead_eff.m_top = 0;
	m_dead_eff.m_left = 0;
	m_dead_eff.m_right = 192;
	m_dead_eff.m_bottom = 192;

	m_dead_end = false;
	m_dead_time =0;//�A�j���[�V�����Ԋu�p
	m_dead_ani  =0;//�A�j���[�V�����p

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 160, 160, ELEMENT_NULL, OBJ_BOSS, 1);
}

//�A�N�V����
void CObjBoss::Action()
{
	if (g_tutorial_flag == true)
		return;
	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}

	if (m_ani_frame == 3)
	{
		m_ani_frame = 1;
	}

	m_warp_time--;

	m_ani_time++;

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

	//HitBox�̓��e���X�V
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + pb->GetScrollx(), m_py + pb->GetScrolly());

	CObjBeam* beam = (CObjBeam*)Objs::GetObj(OBJ_BEAM);

	//���Ԍo�߂Ń����_���Ƀ��[�v
	if (m_warp_time <= 0 && m_hp > 0)
	{
		m_warp_flag = true;
	
		//�G�t�F�N�g�p
		RECT_F warp_ani_src[8] =
		{
			{ 0,   0,  192, 192 },
			{ 0, 192,  384, 192 },
			{ 0, 384,  576, 192 },
			{ 0, 576,  768, 192 },
			{ 0, 768,  960, 192 },
			{ 192,   0,  192, 384 },
			{ 192, 192,  384, 384 },
			{ 192, 384,  576, 384 },
		};

		//�A�j���[�V�����̃R�}�Ԋu����
		if (m_warp_ani_time > 3)
		{
			m_warp_ani++;		//�A�j���[�V�����̃R�}��1�i�߂�
			m_warp_ani_time = 0;

			m_warp_eff = warp_ani_src[m_warp_ani];//�A�j���[�V������RECT�z�񂩂�m_ani�Ԗڂ�RECT���擾
		}
		else
		{
			m_warp_ani_time++;
		}

		if (m_warp_ani == 4)
		{
			int count = 0;

			//�ǂ����̐��Ɏ�l�����ڐG���Ă����ꍇ�A�����Ƀ��[�v
			for (int i = 0; i <= 4; i++)
			{
				if (g_contact_star_f[i] == true)
				{
					Audio::Start(17); //���[�v��
					m_px = g_star_x[i] - 20;
					m_py = g_star_y[i] - 20;
					break;
				}
				count++;
			}

			//�ǂ̐��ɂ��ڐG���Ă��Ȃ������ꍇ�̓����_���Ƀ��[�v
			if (count == 5)
			{
				srand(time(NULL));
				//�}�b�v�̃����_�������̏�����
				m_rand = rand() % 5;

				if (m_rand <= 4)
				{
					Audio::Start(17); //���[�v��
					m_px = g_star_x[m_rand] - 20;
					m_py = g_star_y[m_rand] - 20;
				}
				else if (m_rand == 5)
				{
					m_beam_f = true;
				}
			}
		}

		//7�Ԗځi�摜�Ō�j�܂Ői�񂾂�A0�ɖ߂�
		if (m_warp_ani == 7)
		{
			m_warp_ani = 0;
			m_warp_time = 400;
			m_warp_flag = false;
			m_attack_f = true;
			m_attack_key_f = true;
		}

	}

	if (m_attack_f == true)
	{
		m_imposition_t++;

		if (m_imposition_t >= 100)
		{
			if (m_beam_f == false)
			{
				if (m_attack_key_f == true)
				{
					//�U���p�^�[������
					srand(time(NULL));
					m_attack_pattern = rand() % 2;
					//m_attack_pattern = 1;

					CObjSnake* snake = (CObjSnake*)Objs::GetObj(OBJ_SNAKE);

					//�֏���
					if (m_attack_pattern == 0)
					{
						CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

						float hx = hero->GetX();
						float hy = hero->GetY();

						m_snake_c = 0;
						m_imposition_t = 0;
						Audio::Start(17); //���[�v��

						//�փI�u�W�F�N�g�쐬
						for (int i = 0; i < MAPSIZE; i++)
						{
							for (int j = 0; j < MAPSIZE; j++)
							{
								if (g_map[i][j] == 5)
								{
									if (g_snake_d_flag[m_snake_c] == false)
									{
										//�փI�u�W�F�N�g�쐬
										CObjSnake* snake = new CObjSnake(j*MAPSIZE, i*MAPSIZE, m_snake_c);//�I�u�W�F�N�g�쐬
																										  //�G�̈ʒu���擾
										float* snakex = snake->GetPX();
										float* snakey = snake->GetPY();

										g_snake_x[m_snake_c] = snake->GetPX();
										g_snake_y[m_snake_c] = snake->GetPY();

										g_snake_d_flag[m_snake_c] = true;

										g_stan_snake_flag[m_snake_c] = false;

										Objs::InsertObj(snake, OBJ_SNAKE, 11);//�}�l�[�W���ɓo�^
									}
									m_snake_c++;
								}
							}
							if (m_snake_c == 20)
								break;
						}
					}
				}

				//�Œe��
				if (m_attack_pattern == 1)
				{
					m_imposition_t = 0;
					if (count <= 3)
					{
						if (count == 0)
						{
							//�Œe��18����������
							for (int i = 36; i < 360; i += 18)
							{
								CObjPoison* poison = new CObjPoison(m_px + 55, m_py + 55, i, 4.0f);//�I�u�W�F�N�g�쐬
								Objs::InsertObj(poison, OBJ_POISON, 11);//�}�l�[�W���ɓo�^
							}
						}
						if (count == 1)
						{
							//�Œe��18����������
							for (int i = 18; i < 342; i += 18)
							{
								CObjPoison* poison = new CObjPoison(m_px + 55, m_py + 55, i, 4.0f);//�I�u�W�F�N�g�쐬
								Objs::InsertObj(poison, OBJ_POISON, 11);//�}�l�[�W���ɓo�^
							}
						}
						if (count == 2)
						{
							//�Œe��18����������
							for (int i = -0; i < 324; i += 18)
							{
								CObjPoison* poison = new CObjPoison(m_px + 55, m_py + 55, i, 4.0f);//�I�u�W�F�N�g�쐬
								Objs::InsertObj(poison, OBJ_POISON, 11);//�}�l�[�W���ɓo�^
							}
						}
						if (count == 3)
						{
							//�Œe��18����������
							for (int i = -18; i < 306; i += 18)
							{
								CObjPoison* poison = new CObjPoison(m_px + 55, m_py + 55, i, 4.0f);//�I�u�W�F�N�g�쐬
								Objs::InsertObj(poison, OBJ_POISON, 11);//�}�l�[�W���ɓo�^
							}
							m_attack_f = false;
							count = 0;
						}
						count++;
					}
				}
				m_attack_key_f = false;
			}
			else
			{
				if (beam == nullptr)
				{
					g_boss_d_flag = false;
					CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

					float hx = hero->GetX();
					float hy = hero->GetY();

					//�r�[���I�u�W�F�N�g�쐬
					CObjBeam* beam = new CObjBeam(hx - 135 - pb->GetScrollx(), 275);//�I�u�W�F�N�g�쐬
					Objs::InsertObj(beam, OBJ_BEAM, 11);//�}�l�[�W���ɓo�^

					m_px = g_star_x[m_rand] - 20;
					m_py = g_star_y[m_rand] - 20;
				}
				hit->SetInvincibility(true);
				m_alpha = 0.0f;
				m_beam_f = false;
				m_imposition_t = 0;
			}
		}
		else
		{
			m_imposition_t++;
		}
	}

	if (beam == nullptr)
	{
		g_boss_d_flag = true;
		hit->SetInvincibility(false);
		m_alpha = 1.0f;
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
					m_vx = -0.0f; //�E
				}
				if (r > 45 && r < 135)
				{
					m_vy = 0.0f;//��
				}
				if (r >= 135 && r < 225)
				{
					m_vx = 0.0f;//��
				}
				if (r >= 225 && r < 315)
				{
					m_vy = -0.0f; //��
				}
			}
		}
	}

	//ELEMENT_BEAMSABER�����I�u�W�F�N�g�ƐڐG������
	if (m_invincible_flag == false)
	{
		if (hit->CheckElementHit(ELEMENT_BEAMSABER) == true)
		{
			g_boss_hp -= g_attack_power;	//hp����l���̍U���͕����炷
			m_f = true;
			m_invincible_flag = true;
			m_key_f = true;
		}

		//ELEMENT_VIRGO_SKILL�����I�u�W�F�N�g�ƐڐG������
		if (hit->CheckElementHit(ELEMENT_SKILL_VIRGO) == true)
		{
			g_boss_hp -= g_attack_power;	//hp����l���̍U���͕����炷
			m_f = true;
			m_invincible_flag = true;
			m_key_f = true;
		}

		//ELEMENT_SUB�����I�u�W�F�N�g�ƐڐG������
		if (hit->CheckElementHit(ELEMENT_SUB) == true)
		{
			g_boss_hp -= 1;
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
		g_stan_boss_flag = true;
	}

	//�������̃q�b�g���肪on�̎��X�^�� 
	if (g_stan_boss_flag == true)
	{
		g_Leo_cnt += 1.0f;
		if (g_Leo_cnt >= 200.0f)
		{
			m_ani_frame++;	//�A�j���[�V�����̃R�}���P�i�߂�

			if (g_Leo_cnt >= 200.0f)
			{
				g_Leo_cnt = 0.0f;
				g_stan_boss_flag = false;
			}
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
	if (m_dead_end != true)
	{
		if (g_boss_hp <= 0)
		{
			//�G�폜
			m_alpha = 0.0f;
			hit->SetInvincibility(true);
			g_boss_d_flag = false;
			g_All_Killcnt++;		   //�L���J�E���g��+����
			g_Earth_BossKill = true;
			g_dead_flag = true;
		}
	}
	//HP���O�ȉ��ŃG�t�F�N�g�J�n
	if (g_dead_flag == true)
	{
		//�G�t�F�N�g�p
		RECT_F dead[20] =
		{

			{ 0,     0, 192, 192 },
			{ 0,   192, 384, 192 },
			{ 0,   384, 576, 192 },
			{ 0,   576, 768, 192 },
			{ 0,   768, 960, 192 },
			{ 192,   0, 192, 384 },
			{ 192, 192, 384, 384 },
			{ 192, 384, 576, 384 },
			{ 192, 576, 768, 384 },
			{ 192, 768, 960, 384 },
			{ 384,   0, 192, 576 },
			{ 384, 192, 384, 576 },
			{ 384, 384, 576, 576 },
			{ 384, 576, 768, 576 },
			{ 384, 768, 960, 576 },
			{ 576,   0, 192, 768 },
			{ 576, 192, 384, 768 },
			{ 576, 384, 576, 768 },
			{ 576, 576, 768, 768 },
			{ 576, 768, 960, 768 },

		};

		//�A�j���[�V�����̃R�}�Ԋu����
		if (m_dead_time > 2)
		{
			m_dead_ani++;		//�A�j���[�V�����̃R�}��1�i�߂�
			m_dead_time = 0;
			m_dead_eff = dead[m_dead_ani];//�A�j���[�V������RECT�z�񂩂�m_ani�Ԗڂ�RECT���擾
										  // 12�Ԗځi�摜�Ō�j�܂Ői�񂾂�A0�ɖ߂�
			if (m_dead_ani == 20)
			{
				//���j�A�j���[�V�������I�������V�̐��i�N���A�p�j��\��
				g_tutorial_flag = true;
				g_Voice_flag = true;
				g_dead_flag = false;
				m_dead_end = true;
				hit->SetInvincibility(true);

			}
		}
		else
		{
			m_dead_time++;
		}
	}
	if (g_Voice_flag == true)//�V�̐��i�N���A�p�j��\��
	{
		//�`���[�g���A�������o���쐬
		CObjTutorial* objtutorialhukidashi = new CObjTutorial(0, 3);
		Objs::InsertObj(objtutorialhukidashi, OBJ_TUTORIAL, 151);

		//�`���[�g���A���I�u�W�F�N�g�쐬
		CObjTutorial* objtutorial = new CObjTutorial(1, 3);
		Objs::InsertObj(objtutorial, OBJ_TUTORIAL, 170);
	}
	if (g_End_flag == true)//�V�̐��i�N���A�p�j���I�������t�F�[�h�C�����쐬���AED�Ɉڍs
	{

		g_tutorial_flag = false;
		CObjFadein *objfade = new CObjFadein();
		Objs::InsertObj(objfade, OBJ_FADE_IN, 150);//�t�F�[�h�C���I�u�W�F�N�g�쐬
	}

	CObjMiniMap*map = (CObjMiniMap*)Objs::GetObj(OBJ_MINIMAP);

}

//�h���[
void CObjBoss::Draw()
{
	int AniData[4] =
	{ 1,0,2,0, };

	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,m_alpha };
	float cB[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu

	//�u���b�N���������Ă���
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�؂���ʒu�̐ݒ�
	src.m_top = 80.0f * m_posture;
	src.m_left = 0.0f + (AniData[m_ani_frame] * 80);
	src.m_right = 80.0f + (AniData[m_ani_frame] * 80);
	src.m_bottom = src.m_top + 80.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py + block->GetScrolly();
	dst.m_left = 160.0f + m_px + block->GetScrollx();
	dst.m_right = 0.0f + m_px + block->GetScrollx();
	dst.m_bottom = 160.0f + m_py + block->GetScrolly();
	if (m_dead_end != true)
	{
		//�`��
		Draw::Draw(33, &src, &dst, c, 0.0f);
	}

	//���[�v
	if (m_warp_flag == true)
	{
		//�\���ʒu�̐ݒ�
		dst.m_top = -80.0f + m_py + block->GetScrolly();
		dst.m_left = 240.0f + m_px + block->GetScrollx();
		dst.m_right = -80.0f + m_px + block->GetScrollx();
		dst.m_bottom = 200.0f + m_py + block->GetScrolly();
		//�G�t�F�N�g�̕`��
		Draw::Draw(34, &m_warp_eff, &dst, c, 0.0f);
	}
	else
	{
		m_warp_ani = 0;
	}
	//�\���ʒu�̐ݒ�
	dst.m_top = -80.0f + m_py + block->GetScrolly();
	dst.m_left = 240.0f + m_px + block->GetScrollx();
	dst.m_right = -80.0f + m_px + block->GetScrollx();
	dst.m_bottom = 200.0f + m_py + block->GetScrolly();
	if (g_dead_flag == true)
	{
		//�G�t�F�N�g�̕`��
		Draw::Draw(65, &m_dead_eff, &dst, cB, 0.0f);
	}
}