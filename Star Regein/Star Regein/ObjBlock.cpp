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

int g_blackholecnt = 0;
int g_asteroid;
int g_block;

CObjBlock::CObjBlock(int map[MAPSIZE][MAPSIZE])
{
	//�}�b�v�f�[�^���R�s�[
	memcpy(m_map, map, sizeof(int)*(MAPSIZE * MAPSIZE));
}

//�C�j�V�����C�Y
void CObjBlock::Init()
{
	//�}�b�v�̃����_�������̏�����
	m_rand = rand() % 2;

	//�����_���̒l��0�̏ꍇ
	if (m_rand == 0)
	{
		g_block = 10;	//10���Z�b�g
		g_asteroid = 6;	//6���Z�b�g
	}
	else if (m_rand = 1)	//1�̏ꍇ
	{
		g_block = 11;		//11���Z�b�g
		g_asteroid = 13;	//13���Z�b�g
	}
	m_roll = 0.0f;

	blue_c = 0;
	red_c = 0;
	c = 0;
	b_c = 0;
	w_c = 0;

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
					CObjCow* cow = new CObjCow(j*MAPSIZE, i*MAPSIZE);
					//�G�̈ʒu���擾
					float* cx = cow->GetPX();
					float* cy = cow->GetPY();

					g_cow_x[c] = cow->GetPX();
					g_cow_y[c] = cow->GetPY();

					g_cow_id[c] = c;

					c++;

					Objs::InsertObj(cow, OBJ_COW, 10);
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
					//�o�q�i�j�I�u�W�F�N�g�쐬
					CObjTwinsBlue* blue = new CObjTwinsBlue(j*MAPSIZE, i*MAPSIZE);
					//�G�̈ʒu���擾
					float* bx = blue->GetPX();
					float* by = blue->GetPY();

					g_twinsblue_x[blue_c] = blue->GetPX();
					g_twinsblue_y[blue_c] = blue->GetPY();

					blue_c++;

					Objs::InsertObj(blue, OBJ_TWINS_BLUE, 10);
				}
				if (m_map[i][j] == 10)
				{
					//�o�q�i�ԁj�I�u�W�F�N�g�쐬
					CObjTwinsRed* red = new CObjTwinsRed(j*MAPSIZE, i*MAPSIZE);
					//�G�̈ʒu���擾
					float* rx = red->GetPX();
					float* ry = red->GetPY();

					g_twinsred_x[red_c] = red->GetPX();
					g_twinsred_y[red_c] = red->GetPY();

					red_c++;

					Objs::InsertObj(red, OBJ_TWINS_RED, 10);
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
				//��l���I�u�W�F�N�g�쐬
				CObjHero* obj = new CObjHero(j*ALLSIZE, i*ALLSIZE);//�I�u�W�F�N�g�쐬
				Objs::InsertObj(obj, OBJ_HERO, 10);//�}�l�[�W���ɓo�^

				m_scrollx = -j * MAPSIZE;
				m_scrolly = -i * MAPSIZE;
			}
			if (m_map[i][j] == 2)
			{
				//���I�u�W�F�N�g�쐬
				CObjStar* objstar = new CObjStar(j*ALLSIZE, i*ALLSIZE,i,j);//�I�u�W�F�N�g�쐬
				Objs::InsertObj(objstar, OBJ_STAR, 9);//�}�l�[�W���ɓo�^
			}
			if (m_map[i][j] == g_asteroid)
			{
				//���f���I�u�W�F�N�g�쐬
				CObjAsteroid* objasteroid = new CObjAsteroid(j*ALLSIZE, i*ALLSIZE);//�I�u�W�F�N�g�쐬
				Objs::InsertObj(objasteroid, OBJ_ASTEROID, 9);//�}�l�[�W���ɓo�^
			}
			if (m_map[i][j] == 7)
			{
				//�u���b�N�z�[���I�u�W�F�N�g�쐬
				CObjBlackhole* objablackhole = new CObjBlackhole(j*ALLSIZE, i*ALLSIZE);//�I�u�W�F�N�g�쐬
				
				//�u���b�N�z�[���̈ʒu���擾
				float* bx = objablackhole->GetBX();
				float* by = objablackhole->GetBY();

				g_blackhole_x[b_c] = objablackhole->GetBX();
				g_blackhole_y[b_c] = objablackhole->GetBY();

				b_c++;
				Objs::InsertObj(objablackhole, OBJ_BLACKHOLE, 9);//�}�l�[�W���ɓo�^
				g_blackholecnt++;	//�u���b�N�z�[���̃J�E���g�𑝂₷
			}
			if (m_map[i][j] == 8)
			{
				//�z���C�g�z�[���I�u�W�F�N�g�쐬
				CObjWhitehole* objawhitehole = new CObjWhitehole(j*ALLSIZE, i*ALLSIZE);//�I�u�W�F�N�g�쐬
																							 //�u���b�N�z�[���̈ʒu���擾
				float* bx = objawhitehole->GetWX();
				float* by = objawhitehole->GetWY();

				g_whitehole_x[w_c] = objawhitehole->GetWX();
				g_whitehole_y[w_c] = objawhitehole->GetWY();

				w_c++;

				Objs::InsertObj(objawhitehole, OBJ_WHITEHOLE, 9);//�}�l�[�W���ɓo�^
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
	
}

//�A�N�V����
void CObjBlock::Action()
{
	//��l���̏����擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	

	//�X�N���[��
	hero->SetX(375);
	m_scrollx -= hero->GetVX() * 4;

	hero->SetY(275);
	m_scrolly -= hero->GetVY() * 4;

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
				if (m_map[i][j] == 1)//覐�
				{
					//�؂���ʒu�̐ݒ�
					src.m_top = 0.0f;
					src.m_left = 0.0f;
					src.m_right = 258.0f;
					src.m_bottom = 220.0f;
					//�`��
					Draw::Draw(4, &src, &dst, c, 0.0f);
				}
				if (m_map[i][j] == g_block)//覐΁i�����_���j
				{
					//�؂���ʒu�̐ݒ�
					src.m_top = 0.0f;
					src.m_left = 0.0f;
					src.m_right = 258.0f;
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
			if (m_map[i][j] == 1  || m_map[i][j] == 99
			 || m_map[i][j] == g_block)
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
		}
	}
}