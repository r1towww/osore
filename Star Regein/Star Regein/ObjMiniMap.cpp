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

int g_map[MAPSIZE][MAPSIZE];

CObjMiniMap::CObjMiniMap(int map[MAPSIZE][MAPSIZE])
{
	//�}�b�v�f�[�^���R�s�[
	memcpy(g_map, map, sizeof(int)*(MAPSIZE * MAPSIZE));
}

//�C�j�V�����C�Y
void CObjMiniMap::Init()
{
	if (g_stage == Earth) {	//�n���̏ꍇ
		m_smallsize = 7.0f;	//�X���[���T�C�Y��7.0f�ŏ�����
		m_bigsize = 14.0f;	//�r�b�O�T�C�Y��14.0f�ŏ�����
	}
	else if (g_stage == VenusCow) {	//�����̏ꍇ
		m_smallsize = 4.0f;	//�X�e�[�W�T�C�Y��5.8f�ŏ�����
		m_bigsize = 8.0f;	//�r�b�O�T�C�Y��14.0f�ŏ�����
	}
	m_blocksize = m_smallsize;	//�u���b�N�T�C�Y�ƃX���[���T�C�Y�����킹��

	m_uisize_x = 590.0f, m_uisize_y = 10.0f;	//�w�i�ʒu�̏�����
	m_backsize = 200.0f;	//�w�i�̃T�C�Y�̏�����
	m_f = false;	//�L�[���͐���̏�����
	m_alpha = 0.7f;	//�A���t�@�l������
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
				m_blocksize = m_bigsize;	//�u���b�N�̃T�C�Y�ύX	
				m_uisize_x = 200.0f, m_uisize_y = 100.0f;	//�}�b�v�̈ʒu�̕ύX
				m_backsize = 400.0f;						//�w�i�̃T�C�Y�ύX
				m_alpha = 1.0f;		//�A���t�@�l�ύX
			}
			else						//�傫���ꍇ����������
			{
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
	float c[4] = { 1.0f,1.0f,1.0f,m_alpha};
	
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
				dst.m_top    = i*m_blocksize + m_uisize_y;
				dst.m_left   = j*m_blocksize + m_uisize_x;
				dst.m_right  = dst.m_left + m_blocksize;
				dst.m_bottom = dst.m_top  + m_blocksize;

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
				if (g_map[i][j] == 4 )//��
				{
					//�؂���ʒu�̐ݒ�
					src.m_top    = 0.0f;
					src.m_left   = 110.0f;
					src.m_right  = 140.0f;
					src.m_bottom = 50.0f;

					Draw::Draw(9, &src, &dst, c, 0.0f);
				}
				if (g_map[i][j] == 6)//���f��
				{
					//�؂���ʒu�̐ݒ�
					src.m_top    = 0.0f;
					src.m_left   = 0.0f;
					src.m_right  = 40.0f;
					src.m_bottom = 50.0f;

					//�\���ʒu�̐ݒ�
					dst.m_top = i*m_blocksize + m_uisize_y;
					dst.m_left = j*m_blocksize + m_uisize_x;
					dst.m_right = dst.m_left + m_blocksize * 3;
					dst.m_bottom = dst.m_top + m_blocksize * 3;

					//�`��
					Draw::Draw(9, &src, &dst, c, 0.0f);
				}
				else
				{

				}
			}
		}
	}

	//��l���̏����擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
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
				dst.m_top = m_uisize_y + (hy / ((MAPSIZE * 64.0f) / (MAPSIZE * m_blocksize)))-((block->GetScrolly())/((MAPSIZE * 64.0f)/ (MAPSIZE * m_blocksize)));
				dst.m_left = m_uisize_x + (hx / ((MAPSIZE * 64.0f) / (MAPSIZE * m_blocksize)))-((block->GetScrollx())/((MAPSIZE*64.0f)/ (MAPSIZE*m_blocksize)));
				dst.m_right = dst.m_left + m_blocksize;
				dst.m_bottom = dst.m_top + m_blocksize;

				if (g_map[i][j] ==3)//��l��
				{
					//�؂���ʒu�̐ݒ�
					src.m_top = 0.0f;
					src.m_left = 160.0f;
					src.m_right = 190.0f;
					src.m_bottom = 50.0f;
					//�`��
					Draw::Draw(9, &src, &dst, c, 0.0f);
				}
			}
		}
	}

	//��l���̏����擾
	CObjCow* cow = (CObjCow*)Objs::GetObj(OBJ_COW);
	if (cow != nullptr) 
	{
		//��l���̈ʒu���擾
		float cx = cow->GetX();
		float cy = cow->GetY();

		//UtilityModule�̃`�F�b�N�֐��ɏꏊ�Ɨ̈��n���A�̈�O������
		bool check;
		check = CheckWindow(cx + block->GetScrollx(), cy + block->GetScrolly(), 10.0f, 10.0f, 790.0f, 590.0f);

		if (check == true)
		{
			//�G�����݂���ꍇ�A�~�j�}�b�v�ɓG�̈ʒu��\������
			if (cow != nullptr)
			{
				for (int i = 0; i < MAPSIZE; i++)
				{
					for (int j = 0; j < MAPSIZE; j++)
					{
						if (g_map[i][j] >= 0)
						{
							//�\���ʒu�̐ݒ�
							dst.m_top = m_uisize_y + (cy / ((MAPSIZE * 64.0f) / (MAPSIZE * m_blocksize)));
							dst.m_left = m_uisize_x + (cx / ((MAPSIZE * 64.0f) / (MAPSIZE * m_blocksize)));
							dst.m_right = dst.m_left + m_blocksize;
							dst.m_bottom = dst.m_top + m_blocksize;

							if (g_map[i][j] == 5)//�G
							{
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



	
}
