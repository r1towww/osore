//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjMiniMap.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjMiniMap::CObjMiniMap(int map[MAPSIZE][MAPSIZE])
{
	//�}�b�v�f�[�^���R�s�[
	memcpy(m_map, map, sizeof(int)*(MAPSIZE * MAPSIZE));
}

//�C�j�V�����C�Y
void CObjMiniMap::Init()
{
	
}

//�A�N�V����
void CObjMiniMap::Action()
{
	//���̏��������Ă���
	CObjStar* objstar = (CObjStar*)Objs::GetObj(OBJ_STAR);
	if (objstar != nullptr) {
		m_i = objstar->GetI();
		m_j = objstar->GetJ();
		m_flag = objstar->GetF();
	}
	if (m_flag == true)
	{
		m_map[m_i][m_j] = 4;
		objstar->SetF(false);
	}
}

//�h���[
void CObjMiniMap::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,0.7f };
	
	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	/* �w�i�p */
	//�؂���ʒu�̐ݒ�
	src.m_top    = 0.0f;
	src.m_left   = 0.0f;
	src.m_right  = 500.0f;
	src.m_bottom = 500.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top    = 10.0f;
	dst.m_left   = 590.0f;
	dst.m_right  = 790.0f;
	dst.m_bottom = 210.0f;

	//�w�i�̕`��
	Draw::Draw(7, &src, &dst, c, 0.0f);

	/* �~�j�}�b�v�`�揈�� */
	for (int i = 0; i < MAPSIZE; i++)
	{
		for (int j = 0; j < MAPSIZE; j++)
		{
			if (m_map[i][j] >= 0)
			{
				//�\���ʒu�̐ݒ�
				dst.m_top    = i*7.0f + 10.0f;
				dst.m_left   = j*7.0f + 590.0f;
				dst.m_right  = dst.m_left + 7.0f;
				dst.m_bottom = dst.m_top + 7.0f;

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
				if (m_map[i][j] == 4 )//��
				{
					//�؂���ʒu�̐ݒ�
					src.m_top = 0.0f;
					src.m_left = 0.0f;
					src.m_right = 640.0f;
					src.m_bottom = 608.0f;

					Draw::Draw(6, &src, &dst, c, 0.0f);
				}
				

				else
				{

				}
			}
		}
	}
}
