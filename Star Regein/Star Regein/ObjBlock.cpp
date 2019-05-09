//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjBlock.h"
#include <time.h>

//�g�p����l�[���X�y�[�X
using namespace GameL;

int g_asteroid;
int g_block;
int g_blackhole_cnt = 0;
int g_whitehole_cnt = 0;

bool g_stan_cow_flag[20];//�X�^�����ʔF���p
bool g_stan_blue_flag[20];//�X�^���o�q�i�j�ʔF���p
bool g_stan_red_flag[20];//�X�^���o�q�i�ԁj�ʔF���p
bool g_stan_woman_flag[20];//�X�^�������ʔF���p
bool g_stan_libra_flag[20];//�X�^���V���ʔF���p
bool g_stan_leo_flag[60];//�X�^�����q�ʔF���p
bool g_stan_boss_flag;//�X�^���{�X�p

CObjBlock::CObjBlock(int map[MAPSIZE][MAPSIZE])
{
	//�}�b�v�f�[�^���R�s�[
	memcpy(m_map, map, sizeof(int)*(MAPSIZE * MAPSIZE));
}

//�C�j�V�����C�Y
void CObjBlock::Init()
{
	srand(time(NULL));
	//�}�b�v�̃����_�������̏�����
	m_rand = rand() % 2;
	m_block_rand = 0;	//��Q���u���b�N�̃����_�����p
	//���l��ς��邱�ƂŃX�e�[�W��̏�Q���̈ʒu��ύX
	//�����_���̒l��0�̏ꍇ
	if (m_rand == 0)
	{
		g_block = 10;	//10���Z�b�g
		g_asteroid = 13;	//13���Z�b�g
	}
	else if (m_rand = 1)	//1�̏ꍇ
	{
		g_block = 11;		//11���Z�b�g
		g_asteroid = 14;	//14���Z�b�g
	}

	//�X�e�[�W�N���A�ł��ׂẴT�C�Y������������
	if (g_stage_clear == true)
	{
		m_allsize = 12.0f;
	}
	else
	{
		m_allsize = 64.0f;
	}
	cnt = 0;
	m_blue_c = 0;
	m_red_c = 0;
	m_woman_c = 0;
	m_c_c = 0;
	m_b_c = 0;
	m_w_c = 0;
	m_libra_c = 0;
	m_leo_c = 0;

	//�G�o��
	if (g_stage == VenusTaurus)
	{
		for (int i = 0; i < MAPSIZE; i++)
		{
			for (int j = 0; j < MAPSIZE; j++)
			{
				if (m_map[i][j] == 5)
				{
					//���I�u�W�F�N�g�쐬
					CObjCow* cow = new CObjCow(j*MAPSIZE, i*MAPSIZE, m_c_c);
					//�G�̈ʒu���擾
					float* cx = cow->GetPX();
					float* cy = cow->GetPY();

					g_cow_x[m_c_c] = cow->GetPX();
					g_cow_y[m_c_c] = cow->GetPY();

					g_cow_d_flag[m_c_c] = true;

					g_stan_cow_flag[m_c_c] = false;

					m_c_c++;

					Objs::InsertObj(cow, OBJ_COW, 10);
				}
			}
		}
	}
	else if (g_stage == MercuryVirgo)
	{
		for (int i = 0; i < MAPSIZE; i++)
		{
			for (int j = 0; j < MAPSIZE; j++)
			{
				if (m_map[i][j] == 5)
				{
					//�����I�u�W�F�N�g�쐬
					CObjWoman* woman = new CObjWoman(j*MAPSIZE, i*MAPSIZE, m_woman_c);
					//�G�̈ʒu���擾
					float* wx = woman->GetPX();
					float* wy = woman->GetPY();

					g_woman_x[m_woman_c] = woman->GetPX();
					g_woman_y[m_woman_c] = woman->GetPY();

					g_woman_d_flag[m_woman_c] = true;

					g_stan_woman_flag[m_woman_c] = false;

					m_woman_c++;

					Objs::InsertObj(woman, OBJ_WOMAN, 10);
				}
			}
		}
	}

	else if (g_stage == MercuryGemini)
	{
		for (int i = 0; i < MAPSIZE; i++)
		{
			for (int j = 0; j < MAPSIZE; j++)
			{
				if (m_map[i][j] == 5)
				{
					//�o�q�i�j�I�u�W�F�N�g�쐬
					CObjTwinsBlue* blue = new CObjTwinsBlue(j*MAPSIZE, i*MAPSIZE, m_blue_c);
					//�G�̈ʒu���擾
					float* bx = blue->GetPX();
					float* by = blue->GetPY();

					g_twinsblue_x[m_blue_c] = blue->GetPX();
					g_twinsblue_y[m_blue_c] = blue->GetPY();

					g_blue_d_flag[m_blue_c] = true;

					g_stan_blue_flag[m_blue_c] = false;

					m_blue_c++;

					Objs::InsertObj(blue, OBJ_TWINS_BLUE, 10);
				}
				if (m_map[i][j] == 9)
				{
					//�o�q�i�ԁj�I�u�W�F�N�g�쐬
					CObjTwinsRed* red = new CObjTwinsRed(j*MAPSIZE, i*MAPSIZE, m_red_c);
					//�G�̈ʒu���擾
					float* rx = red->GetPX();
					float* ry = red->GetPY();

					g_twinsred_x[m_red_c] = red->GetPX();
					g_twinsred_y[m_red_c] = red->GetPY();

					g_red_d_flag[m_red_c] = true;

					g_stan_red_flag[m_red_c] = false;

					m_red_c++;

					Objs::InsertObj(red, OBJ_TWINS_RED, 10);
				}
			}
		}
	}

	else if (g_stage == VenusLibra)
	{
		for (int i = 0; i < MAPSIZE; i++)
		{
			for (int j = 0; j < MAPSIZE; j++)
			{
				if (m_map[i][j] == 5)
				{
					//�V���I�u�W�F�N�g�쐬
					CObjLibra* libra = new CObjLibra(j*MAPSIZE, i*MAPSIZE, m_libra_c);
					//�G�̈ʒu���擾
					float* bx = libra->GetPX();
					float* by = libra->GetPY();

					g_libra_x[m_libra_c] = libra->GetPX();
					g_libra_y[m_libra_c] = libra->GetPY();

					g_libra_d_flag[m_libra_c] = true;

					g_stan_libra_flag[m_libra_c] = false;

					m_libra_c++;

					Objs::InsertObj(libra, OBJ_LIBRA, 10);
				}
			}
		}
	}
	else if (g_stage == SunLeo)
	{
		for (int i = 0; i < MAPSIZE; i++)
		{
			for (int j = 0; j < MAPSIZE; j++)
			{
				if (m_map[i][j] == 5)
				{
					//���q�I�u�W�F�N�g�쐬
					CObjLeo* leo = new CObjLeo(j*MAPSIZE, i*MAPSIZE, m_leo_c);
					//�G�̈ʒu���擾
					float* lx = leo->GetPX();
					float* ly = leo->GetPY();

					g_leo_x[m_leo_c] = leo->GetPX();
					g_leo_y[m_leo_c] = leo->GetPY();

					g_leo_d_flag[m_leo_c] = true;

					g_stan_leo_flag[m_leo_c] = false;

					m_leo_c++;

					Objs::InsertObj(leo, OBJ_LEO, 10);
				}
			}
		}
	}
	else if (g_stage == EarthStar)
	{
		for (int i = 0; i < MAPSIZE; i++)
		{
			for (int j = 0; j < MAPSIZE; j++)
			{
				if (m_map[i][j] == 5)
				{
					//�{�X�I�u�W�F�N�g�쐬
					CObjBoss* boss = new CObjBoss(j*MAPSIZE, i*MAPSIZE);
					//�G�̈ʒu���擾
					float* bossx = boss->GetPX();
					float* bossy = boss->GetPY();

					g_boss_x = boss->GetPX();
					g_boss_y = boss->GetPY();

					g_boss_d_flag = true;

					g_stan_boss_flag = false;

					Objs::InsertObj(boss, OBJ_BOSS, 10);
				}
			}
		}
	}



	//�o��
	for (int i = 0; i < MAPSIZE; i++)
	{
		for (int j = 0; j < MAPSIZE; j++)
		{
			if (m_map[i][j] == 3)
			{
				if (g_stage_clear == true)
				{
					;
				}
				else
				{
					//��l���I�u�W�F�N�g�쐬
					CObjHero* obj = new CObjHero(j*ALLSIZE, i*ALLSIZE);//�I�u�W�F�N�g�쐬
					Objs::InsertObj(obj, OBJ_HERO, 11);//�}�l�[�W���ɓo�^

					m_scrollx = -j * MAPSIZE;
					m_scrolly = -i * MAPSIZE;
				}

			}
			if (m_map[i][j] == 2)
			{
				//���I�u�W�F�N�g�쐬
				CObjStar* objstar = new CObjStar(j*ALLSIZE, i*ALLSIZE,i,j);//�I�u�W�F�N�g�쐬
				Objs::InsertObj(objstar, OBJ_STAR, 5);//�}�l�[�W���ɓo�^

			}
			if (m_map[i][j] == g_asteroid || m_map[i][j] == 6)
			{
				//���f���I�u�W�F�N�g�쐬
				CObjAsteroid* objasteroid = new CObjAsteroid(j*ALLSIZE, i*ALLSIZE);//�I�u�W�F�N�g�쐬
				Objs::InsertObj(objasteroid, OBJ_ASTEROID, 9);//�}�l�[�W���ɓo�^
			}
			if (m_map[i][j] == 7)
			{
				//�u���b�N�z�[���I�u�W�F�N�g�쐬
				CObjBlackhole* objablackhole = new CObjBlackhole(j*ALLSIZE, i*ALLSIZE, m_b_c);//�I�u�W�F�N�g�쐬
				
				//�u���b�N�z�[���̈ʒu���擾
				float* bx = objablackhole->GetBX();
				float* by = objablackhole->GetBY();

				
				g_blackhole_x[m_b_c] = objablackhole->GetBX();
				g_blackhole_y[m_b_c] = objablackhole->GetBY();

				m_b_c++;
				Objs::InsertObj(objablackhole, OBJ_BLACKHOLE + g_blackhole_cnt, 9);//�}�l�[�W���ɓo�^
				g_blackhole_cnt++;	//�J�E���g�𑝂₵�I�u�W�F�N�g��ʂɂ���
			}
			if (m_map[i][j] == 8)
			{
				//�z���C�g�z�[���I�u�W�F�N�g�쐬
				CObjWhitehole* objawhitehole = new CObjWhitehole(j*ALLSIZE, i*ALLSIZE, m_w_c);//�I�u�W�F�N�g�쐬
				//�u���b�N�z�[���̈ʒu���擾
				float* bx = objawhitehole->GetWX();
				float* by = objawhitehole->GetWY();

				g_whitehole_x[m_w_c] = objawhitehole->GetWX();
				g_whitehole_y[m_w_c] = objawhitehole->GetWY();

				m_w_c++;

				Objs::InsertObj(objawhitehole, OBJ_WHITEHOLE , 9);//�}�l�[�W���ɓo�^
			}
			if (m_map[i][j] == 15)
			{
				//�u���C�N���b�N�I�u�W�F�N�g�쐬
				CObjBreakRock* objbrock = new CObjBreakRock(j*ALLSIZE, i*ALLSIZE,i,j);//�I�u�W�F�N�g�쐬
				Objs::InsertObj(objbrock, OBJ_BREAK_ROCK, 9);//�}�l�[�W���ɓo�^
			}
			if (m_map[i][j] == 16)
			{
				//�u���C�N�r�b�N���b�N�I�u�W�F�N�g�쐬
				CObjBreakBigRock* objbbrock = new CObjBreakBigRock(j*ALLSIZE, i*ALLSIZE, i, j);//�I�u�W�F�N�g�쐬
				Objs::InsertObj(objbbrock, OBJ_BREAK_BIGROCK, 9);//�}�l�[�W���ɓo�^
			}
		}
	}

	//�f���ɂ���Ĕw�i��ς���i�J���[�ύX�j
	if (g_stage == EarthStar) {		//�n���̏ꍇ
		m_red = 1.0f;  m_green = 1.0f;  m_blue = 1.0f;
	}
	else if (g_stage == VenusTaurus || g_stage == VenusLibra) {	//�����̏ꍇ
		m_red = 2.0f;  m_green = 2.0f;  m_blue = 1.0f;	
	}
	else if (g_stage == MercuryGemini || g_stage == MercuryVirgo) {	//�����̏ꍇ
		m_red = 1.0f;  m_green = 2.0f;  m_blue = 2.0f;
	}
	else if (g_stage == SunLeo) {		//���z�̏ꍇ
			m_red = 2.0f;  m_green = 1.0f;  m_blue = 1.0f;
		}

}

//�A�N�V����
void CObjBlock::Action()
{
	//��l���̏����擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	

	//�X�N���[��
	hero->SetX(375);
	m_scrollx -= hero->GetVX() * HERO_VEC;

	hero->SetY(275);
	m_scrolly -= hero->GetVY() * HERO_VEC;

	//�N���A�����Ȃ�}�b�v���ĕ\��������
	if (g_stage_clear == true)
	{
		if (cnt >= 1)
		{
			;
		}
		else
		{
			Init();
			cnt++;
		}
	}

	//�w�i����]������
	//m_roll += 0.1f;
	//if (m_roll == 360.0f) {	//1��]������
	//	m_roll = 0.0f;		//0.0f�ɒl��߂�
	//}
}

//�h���[
void CObjBlock::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };		//�ʏ�J���[
	float r[4] = { 1.0f,0.7f,0.7f,1.0f };		//���b�h�J���[
	float b[4] = { 0.7f,0.7f,1.0f,1.0f };		//�u���[�J���[

	float backc[4] = { m_red,m_green,m_blue,1.0f };	//�w�i�J���[

	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	/* �w�i�p */
	//�؂���ʒu�̐ݒ�
	src.m_top    = 0.0f;
	src.m_left   = 0.0f;
	src.m_right  = 800.0f;
	src.m_bottom = 600.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top    = 0.0f;
	dst.m_left   = 0.0f;
	dst.m_right  = 800.0f;
	dst.m_bottom = 600.0f;

	//�`��
	Draw::Draw(5, &src, &dst, backc, 0.0f);

	/* �u���b�N�i��Q���p�j */
	for (int i = 0; i < MAPSIZE; i++)
	{
		for (int j = 0; j < MAPSIZE; j++)
		{
			if (m_map[i][j] >= 0)
			{
				//�\���ʒu�̐ݒ�
				dst.m_top    = i*ALLSIZE + m_scrolly;
				dst.m_left   = j*ALLSIZE + m_scrollx;
				dst.m_right  = dst.m_left + ALLSIZE;
				dst.m_bottom = dst.m_top  + ALLSIZE;
				if (m_map[i][j] == 1 || m_map[i][j] == g_block)//覐΁A�����_��覐Ηp
				{
					//�؂���ʒu�̐ݒ�
					src.m_top    = 0.0f;
					src.m_left   = 0.0f;
					src.m_right  = 258.0f;
					src.m_bottom = 220.0f;
					//�`��
					Draw::Draw(4, &src, &dst, c, 0.0f);
				}
			}
		}
	}

	
}

//BlockHit�֐�
//�����P�@float* x			�F������s��object��X�ʒu
//�����Q�@float* y			�F������s��object��Y�ʒu
//�����R�@bool  scroll		�F������s��object�̓X�N���[���̉e���^���邩�ǂ����itrue=�^����Afalse=�^���Ȃ��j
//�����S�@bool* up			�F�㉺���E����̏㕔���ɓ������Ă��邩�ǂ�����Ԃ�
//�����T�@bool* down		�F�㉺���E����̉������ɓ������Ă��邩�ǂ�����Ԃ�
//�����U�@bool*left			�F�㉺���E����̍������ɓ������Ă��邩�ǂ�����Ԃ�
//�����V�@bool*right		�F�㉺���E����̉E�����ɓ������Ă��邩�ǂ�����Ԃ�
//�����W�@float* vx			�F���E���莞�̔����ɂ��ړ������E�͂̒l��ς��ĕԂ�
//�����X�@float* vy			�F�㉺���莞�ɂ�鎩�R�����^���̈ړ������E�͂̒l��ς��ĕԂ�
//����10�@int* bt			�F���������莞�A����ȃu���b�N�̃^�C�v��Ԃ�
//������s��object�ƃu���b�N50*50����ŁA�����蔻��Ə㉺���E������s��
//���̌��ʂ͈����S�`10�ɕԂ�
void CObjBlock::BlockHit
(
	float *x, float *y, bool scroll_on,
	bool*up, bool* down, bool*left, bool*right,
	float*vx, float*vy
)
{
	//��l���̏Փˏ�Ԋm�F�p�t���O�̏�����
	*up = false;
	*down = false;
	*left = false;
	*right = false;

	//m_map�̑S�v�f�ɃA�N�Z�X
	for (int i = 0; i < MAPSIZE; i++)
	{
		for (int j = 0; j < MAPSIZE; j++)
		{
			if (m_map[i][j] == 1 || m_map[i][j] == 99
				|| m_map[i][j] == g_block)
			{
				if (g_stage_clear == false)
				{
					//�v�f�ԍ������W�ɕύX
					float bx = j*ALLSIZE;
					float by = i*ALLSIZE;

					//�X�N���[���̉e��
					float scrollx = scroll_on ? m_scrollx : 0;
					float scrolly = scroll_on ? m_scrolly : 0;

					//�I�u�W�F�N�g�ƃu���b�N�̓����蔻��
					if ((*x + (-scrollx) + HITBOXSIZE > bx) && (*x + (-scrollx) < bx + HITBOXSIZE) && (*y + (-scrolly) + HITBOXSIZE > by) && (*y + (-scrolly) < by + HITBOXSIZE))
					{
						//�㉺���E����

						//Vector�̍쐬
						float rvx = (*x + (-scrollx)) - bx;
						float rvy = (*y + (-scrolly)) - by;

						//���������߂�
						float len = sqrt(rvx*rvx + rvy*rvy);

						//�p�x�����߂�
						float r = atan2(rvy, rvx);
						r = r*180.0f / 3.14f;

						if (r <= 0.0f)
							r = abs(r);
						else
							r = 360.0f - abs(r);

						//len��������̒����̂��Z���ꍇ����ɓ���
						if (len < 88.0f)
						{
							//�p�x�ŏ㉺���E�𔻒�
							if ((r < 45 && r >= 0) || r > 315)
							{
								*right = true;//�I�u�W�F�N�g�̍��������Փ˂��Ă���
								*x = bx + HITBOXSIZE + (scrollx);//�u���b�N�̈ʒu+�I�u�W�F�N�g�̕�
								*vx = 0.15f;//-VX*�����W��
							}

							if (r > 45 && r < 135)
							{
								*down = true;//�I�u�W�F�N�g�̉��̕������Փ˂��Ă���
								*y = by - HITBOXSIZE + (scrolly);//�u���b�N�̈ʒu-�I�u�W�F�N�g�̕�
								*vy = -0.15f;
							}
							if (r > 135 && r < 225)
							{
								*left = true;//�I�u�W�F�N�g�̉E�������Փ˂��Ă���
								*x = bx - HITBOXSIZE + (scrollx);//�u���b�N�̈ʒu-�I�u�W�F�N�g�̕�
								*vx = -0.15f;//-VX*�����W��
							}
							if (r > 225 && r < 315)
							{
								*up = true;//�I�u�W�F�N�g�̏�̕������Փ˂��Ă���
								*y = by + HITBOXSIZE + (scrolly);//�u���b�N�̈ʒu+�I�u�W�F�N�g�̕�							
								*vy = 0.15f;
							}
						}
					}
				}
				else
				{
					return;
				}
			}
			
		}
	}
}