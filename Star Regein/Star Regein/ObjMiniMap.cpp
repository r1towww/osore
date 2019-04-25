//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjMiniMap.h"
#include "UtilityModule.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

bool g_cow_d_flag[20];//���폜�t���O
bool g_blue_d_flag[20];//�o�q�i�j�폜�t���O
bool g_red_d_flag[20];//�o�q�i�ԁj�폜�t���O
bool g_woman_d_flag[20];//�����폜�t���O
bool g_libra_d_flag[20];//�V���폜�t���O
bool g_leo_d_flag[50];//���q�폜�t���O


int g_map[MAPSIZE][MAPSIZE];

CObjMiniMap::CObjMiniMap(int map[MAPSIZE][MAPSIZE])
{
	//�}�b�v�f�[�^���R�s�[
	memcpy(g_map, map, sizeof(int)*(MAPSIZE * MAPSIZE));
}

//�C�j�V�����C�Y
void CObjMiniMap::Init()
{
	if (g_stage == EarthStar) {	//�n���̏ꍇ
		m_smallsize = 7.0f;	//�X���[���T�C�Y��7.0f�ŏ�����
		m_bigsize = 14.0f;	//�r�b�O�T�C�Y��14.0f�ŏ�����
	}
	else{	//����ȊO�̏ꍇ
		m_smallsize = 4.0f;	//�X�e�[�W�T�C�Y��4.0f�ŏ�����
		m_bigsize = 8.0f;	//�r�b�O�T�C�Y��8.0f�ŏ�����
	}
	m_blocksize = m_smallsize;	//�u���b�N�T�C�Y�ƃX���[���T�C�Y�����킹��

	m_uisize_x = 590.0f, m_uisize_y = 10.0f;	//�w�i�ʒu�̏�����
	m_backsize = 200.0f;	//�w�i�̃T�C�Y�̏�����
	m_f = false;	//�L�[���͐���̏�����
	m_alpha = 0.7f;	//�A���t�@�l������

	m_hint_f = false;	//�q���g�\���p�t���O�̏�����

	count = 0;
}


//�A�N�V����
void CObjMiniMap::Action()
{
	if (Input::GetVKey('M'))//M�L�[�����͂��ꂽ�Ƃ�
	{
		//�L�[���͐���
		if (m_f == true)
		{
			//�}�b�v�T�C�Y�̕ύX
			if (m_blocksize == m_smallsize)	//�������ꍇ�傫������
			{
				m_hint_f = false;		//�t���O���I�t
				m_blocksize = m_bigsize;	//�u���b�N�̃T�C�Y�ύX	
				m_uisize_x = 200.0f, m_uisize_y = 100.0f;	//�}�b�v�̈ʒu�̕ύX
				m_backsize = 400.0f;						//�w�i�̃T�C�Y�ύX
				m_alpha = 1.0f;		//�A���t�@�l�ύX
			}
			else						//�傫���ꍇ����������
			{
				m_hint_f = true;		//�t���O���I��
				m_blocksize = m_smallsize;		//�u���b�N�̃T�C�Y�ύX	
				m_uisize_x = 590.0f, m_uisize_y = 10.0f;	//�}�b�v�̈ʒu�̕ύX
				m_backsize = 200.0f;						//�w�i�̃T�C�Y�ύX
				m_alpha = 0.7f;		//�A���t�@�l�ύX
			}
			m_f = false;
		}
	}
	else
	{
		m_f = true;	
	}

}

//�h���[
void CObjMiniMap::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,m_alpha };	//��{�J���[�i�������j
	float ac[4] = { 1.0f,1.0f,1.0f,1.0f };	//��l���J���[�i�񓧖��j

	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	/* �w�i�p */
	//�؂���ʒu�̐ݒ�
	src.m_top    = 0.0f;
	src.m_left   = 0.0f;
	src.m_right  = 500.0f;
	src.m_bottom = 500.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top    = m_uisize_y;
	dst.m_left   = m_uisize_x;
	dst.m_right  = m_uisize_x + m_backsize;
	dst.m_bottom = m_uisize_y + m_backsize;

		//�w�i�̕`��
		Draw::Draw(7, &src, &dst, c, 0.0f);

	if (m_hint_f == true)
	{






	}
	else
	{

	}





	/* �~�j�}�b�v�`�揈�� */
	for (int i = 0; i < MAPSIZE; i++)
	{
		for (int j = 0; j < MAPSIZE; j++)
		{
			if (g_map[i][j] >= 0)
			{
				if (g_map[i][j] == 98)//�}�b�v�`��O�Ȃ̂Ńu���C�N
				{
					break;
				}
				//�\���ʒu�̐ݒ�
				dst.m_top = i*m_blocksize + m_uisize_y;
				dst.m_left = j*m_blocksize + m_uisize_x;
				dst.m_right = dst.m_left + m_blocksize;
				dst.m_bottom = dst.m_top + m_blocksize;

				if (g_map[i][j] == 1)//覐�
				{
					//�؂���ʒu�̐ݒ�
					src.m_top    = 0.0f;
					src.m_left   = 0.0f;
					src.m_right  = 40.0f;
					src.m_bottom = 50.0f;
					//�`��
					Draw::Draw(9, &src, &dst, c, 0.0f);
				}
				if (g_map[i][j] == 2)//���i�擾�O�j
				{
					//�؂���ʒu�̐ݒ�
					src.m_top    = 0.0f;
					src.m_left   = 410.0f;
					src.m_right  = 440.0f;
					src.m_bottom = 50.0f;
					//�`��
					Draw::Draw(9, &src, &dst, c, 0.0f);
				}
				if (g_map[i][j] == 4)//���i�擾��j
				{
					//�؂���ʒu�̐ݒ�
					src.m_top = 0.0f;
					src.m_left = 110.0f;
					src.m_right = 140.0f;
					src.m_bottom = 50.0f;
					//�`��
					Draw::Draw(9, &src, &dst, c, 0.0f);
				}
				if (g_map[i][j] == 7)//�u���b�N�z�[��
				{
					//�؂���ʒu�̐ݒ�
					src.m_top    = 0.0f;
					src.m_left   = 260.0f;
					src.m_right  = 290.0f;
					src.m_bottom = 50.0f;
					//�`��
					Draw::Draw(9, &src, &dst, c, 0.0f);
				}
				if (g_map[i][j] == 8)//�z���C�g�z�[��
				{
					//�؂���ʒu�̐ݒ�
					src.m_top    = 0.0f;
					src.m_left   = 310.0f;
					src.m_right  = 340.0f;
					src.m_bottom = 50.0f;
					//�`��
					Draw::Draw(9, &src, &dst, c, 0.0f);
				}
				if (g_map[i][j] == g_block)//覐�
				{
					//�؂���ʒu�̐ݒ�
					src.m_top    = 0.0f;
					src.m_left   = 0.0f;
					src.m_right  = 40.0f;
					src.m_bottom = 50.0f;
					//�`��
					Draw::Draw(9, &src, &dst, c, 0.0f);
				}
				if (g_map[i][j] == 15)//����覐�
				{
					//�؂���ʒu�̐ݒ�
					src.m_top    = 0.0f;
					src.m_left   = 460.0f;
					src.m_right  = 490.0f;
					src.m_bottom = 50.0f;
					//�`��
					Draw::Draw(9, &src, &dst, c, 0.0f);
				}
				if (g_map[i][j] == 16)//����覐΁i��j
				{
					//�؂���ʒu�̐ݒ�
					src.m_top    = 0.0f;
					src.m_left   = 460.0f;
					src.m_right  = 490.0f;
					src.m_bottom = 50.0f;

					//�\���ʒu�̐ݒ�
					dst.m_top    = i*m_blocksize + m_uisize_y + 2.0f;
					dst.m_left   = j*m_blocksize + m_uisize_x ;
					dst.m_right  = dst.m_left + m_blocksize * 2.8;
					dst.m_bottom = dst.m_top + m_blocksize * 2.0f;

					//�`��
					Draw::Draw(9, &src, &dst, c, 0.0f);
				}
				if (g_map[i][j] == g_asteroid || g_map[i][j] == 6)//���f��
				{
					//�؂���ʒu�̐ݒ�
					src.m_top    = 0.0f;
					src.m_left   = 0.0f;
					src.m_right  = 40.0f;
					src.m_bottom = 50.0f;

						//�\���ʒu�̐ݒ�
						dst.m_top = i*m_blocksize + m_uisize_y + 2.0f;
						dst.m_left = j*m_blocksize + m_uisize_x + 4.0f;
						dst.m_right = dst.m_left + m_blocksize * 1.8;
						dst.m_bottom = dst.m_top + m_blocksize * 1.8;

					//�`��
					Draw::Draw(9, &src, &dst, c, 0.0f);
				}
			}
		}
	}
	//��l���̏����擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	if (hero != nullptr)
	{
		//��l���̈ʒu���擾
		float hx = hero->GetX();
		float hy = hero->GetY();

			//�u���b�N���������Ă���
			CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
			float sx = block->GetScrollx();
			float sy = block->GetScrolly();


			for (int i = 0; i < MAPSIZE; i++)
			{
				for (int j = 0; j < MAPSIZE; j++)
				{
					if (g_map[i][j] >= 0)
					{
						//�\���ʒu�̐ݒ�
						dst.m_top = m_uisize_y + (hy / ((MAPSIZE * 64.0f) / (MAPSIZE * m_blocksize))) - ((block->GetScrolly()) / ((MAPSIZE * 64.0f) / (MAPSIZE * m_blocksize)));
						dst.m_left = m_uisize_x + (hx / ((MAPSIZE * 64.0f) / (MAPSIZE * m_blocksize))) - ((block->GetScrollx()) / ((MAPSIZE*64.0f) / (MAPSIZE*m_blocksize)));
						dst.m_right = dst.m_left + m_blocksize;
						dst.m_bottom = dst.m_top + m_blocksize;

						if (g_map[i][j] == 3)//��l��
						{
							//�؂���ʒu�̐ݒ�
							src.m_top = 0.0f;
							src.m_left = 160.0f;
							src.m_right = 190.0f;
							src.m_bottom = 50.0f;
							//�`��
							Draw::Draw(9, &src, &dst, ac, 0.0f);
						}
					}
				}
			}

			if (g_stage == EarthStar)
			{
				for (int i = 0; i < 4; i++)//�G�̐�����
				{
					float wx = *g_woman_x[i];
					float wy = *g_woman_y[i];


					if (g_woman_d_flag[i] == true)
					{
						//UtilityModule�̃`�F�b�N�֐��ɏꏊ�Ɨ̈��n���A�̈�O������
						bool check;
						check = CheckWindow(wx + block->GetScrollx(), wy + block->GetScrolly(), 10.0f, 10.0f, 790.0f, 590.0f);
						if (check == true)
						{
							//�~�j�}�b�v�ɓG�̈ʒu��\������
							//�\���ʒu�̐ݒ�
							dst.m_top = m_uisize_y + (wy / ((MAPSIZE * 64.0f) / (MAPSIZE * m_blocksize)));
							dst.m_left = m_uisize_x + (wx / ((MAPSIZE * 64.0f) / (MAPSIZE * m_blocksize)));
							dst.m_right = dst.m_left + m_blocksize;
							dst.m_bottom = dst.m_top + m_blocksize;

							//�؂���ʒu�̐ݒ�
							src.m_top = 0.0f;
							src.m_left = 50.0f;
							src.m_right = 100.0f;
							src.m_bottom = 50.0f;
							//�`��
							Draw::Draw(9, &src, &dst, c, 0.0f);
						}
					}
				}
			}

			if (g_stage == MercuryGemini)
			{
				for (int i = 0; i < 7; i++)//�G�̐�����
				{
					float bx = *g_twinsblue_x[i];
					float by = *g_twinsblue_y[i];


					if (g_blue_d_flag[i] == true)
					{
						//UtilityModule�̃`�F�b�N�֐��ɏꏊ�Ɨ̈��n���A�̈�O������
						bool check;
						check = CheckWindow(bx + block->GetScrollx(), by + block->GetScrolly(), 10.0f, 10.0f, 790.0f, 590.0f);
						if (check == true)
						{
							//�~�j�}�b�v�ɓG�̈ʒu��\������
							//�\���ʒu�̐ݒ�
							dst.m_top = m_uisize_y + (by / ((MAPSIZE * 64.0f) / (MAPSIZE * m_blocksize)));
							dst.m_left = m_uisize_x + (bx / ((MAPSIZE * 64.0f) / (MAPSIZE * m_blocksize)));
							dst.m_right = dst.m_left + m_blocksize;
							dst.m_bottom = dst.m_top + m_blocksize;

							//�؂���ʒu�̐ݒ�
							src.m_top = 0.0f;
							src.m_left = 50.0f;
							src.m_right = 100.0f;
							src.m_bottom = 50.0f;
							//�`��
							Draw::Draw(9, &src, &dst, c, 0.0f);
						}
					}
				}
				for (int i = 0; i < 7; i++)//�G�̐�����
				{
					float rx = *g_twinsred_x[i];
					float ry = *g_twinsred_y[i];


					if (g_red_d_flag[i] == true)
					{
						//UtilityModule�̃`�F�b�N�֐��ɏꏊ�Ɨ̈��n���A�̈�O������
						bool check;
						check = CheckWindow(rx + block->GetScrollx(), ry + block->GetScrolly(), 10.0f, 10.0f, 790.0f, 590.0f);
						if (check == true)
						{
							//�~�j�}�b�v�ɓG�̈ʒu��\������
							//�\���ʒu�̐ݒ�
							dst.m_top = m_uisize_y + (ry / ((MAPSIZE * 64.0f) / (MAPSIZE * m_blocksize)));
							dst.m_left = m_uisize_x + (rx / ((MAPSIZE * 64.0f) / (MAPSIZE * m_blocksize)));
							dst.m_right = dst.m_left + m_blocksize;
							dst.m_bottom = dst.m_top + m_blocksize;

							//�؂���ʒu�̐ݒ�
							src.m_top = 0.0f;
							src.m_left = 50.0f;
							src.m_right = 100.0f;
							src.m_bottom = 50.0f;
							//�`��
							Draw::Draw(9, &src, &dst, c, 0.0f);
						}
					}
				}
			}

			if (g_stage == VenusTaurus)
			{
				for (int i = 0; i < 13; i++)//�G�̐�����
				{
					float cx = *g_cow_x[i];
					float cy = *g_cow_y[i];

					if (g_cow_d_flag[i] == true)
					{
						//UtilityModule�̃`�F�b�N�֐��ɏꏊ�Ɨ̈��n���A�̈�O������
						bool check;
						check = CheckWindow(cx + block->GetScrollx(), cy + block->GetScrolly(), 10.0f, 10.0f, 790.0f, 590.0f);
						if (check == true)
						{
							//�~�j�}�b�v�ɓG�̈ʒu��\������
							//�\���ʒu�̐ݒ�
							dst.m_top = m_uisize_y + (cy / ((MAPSIZE * 64.0f) / (MAPSIZE * m_blocksize)));
							dst.m_left = m_uisize_x + (cx / ((MAPSIZE * 64.0f) / (MAPSIZE * m_blocksize)));
							dst.m_right = dst.m_left + m_blocksize;
							dst.m_bottom = dst.m_top + m_blocksize;

							//�؂���ʒu�̐ݒ�
							src.m_top = 0.0f;
							src.m_left = 50.0f;
							src.m_right = 100.0f;
							src.m_bottom = 50.0f;
							//�`��
							Draw::Draw(9, &src, &dst, c, 0.0f);
						}
					}
				}
			}

			if (g_stage == SunLeo)
			{
				for (int i = 0; i < 50; i++)//�G�̐�����
				{
					float lx = *g_leo_x[i];
					float ly = *g_leo_y[i];

					if (g_leo_d_flag[i] == true)
					{
						//UtilityModule�̃`�F�b�N�֐��ɏꏊ�Ɨ̈��n���A�̈�O������
						bool check;
						check = CheckWindow(lx + block->GetScrollx(), ly + block->GetScrolly(), 10.0f, 10.0f, 790.0f, 590.0f);
						if (check == true)
						{
							//�~�j�}�b�v�ɓG�̈ʒu��\������
							//�\���ʒu�̐ݒ�
							dst.m_top = m_uisize_y + (ly / ((MAPSIZE * 64.0f) / (MAPSIZE * m_blocksize)));
							dst.m_left = m_uisize_x + (lx / ((MAPSIZE * 64.0f) / (MAPSIZE * m_blocksize)));
							dst.m_right = dst.m_left + m_blocksize;
							dst.m_bottom = dst.m_top + m_blocksize;

							//�؂���ʒu�̐ݒ�
							src.m_top = 0.0f;
							src.m_left = 50.0f;
							src.m_right = 100.0f;
							src.m_bottom = 50.0f;
							//�`��
							Draw::Draw(9, &src, &dst, c, 0.0f);
						}
					}
				}
			}
		}
	}
}