//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameHead.h"
#include "ObjBeam.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;


CObjBeam::CObjBeam(float x, float y)
{
	m_px = x;		//�ʒu
	m_py = y;

}

//�C�j�V�����C�Y
void CObjBeam::Init()
{
	//�r�[���A�j���[�V�����֘A������
	m_beam_eff.m_top = 0;	//�G�t�F�N�g�����l�̏�����
	m_beam_eff.m_left = 0;
	m_beam_eff.m_right = 65;
	m_beam_eff.m_bottom = 497;

	m_beam_ani = 0;			//�A�j���[�V�����p
	m_beam_ani_time = 0;		//�A�j���[�V�����Ԋu�^�C��

	m_beam_flag = false;
	m_beam_time = 100;


	m_eff.m_top = 0;
	m_eff.m_left = 0;
	m_eff.m_right = 220;
	m_eff.m_bottom = 203;
	m_ani = 0;
	m_ani_time = 0;
	m_ani_stop = 0;
	m_ani_flag = false;
						//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_STAR, OBJ_STAR, 1);
}

//�A�N�V����
void CObjBeam::Action()
{

	//���ɔ��Ńr�[���U��
	//�G�t�F�N�g�p
	RECT_F beam_ani_src[7] =
	{
		{ 0,   0,  65, 536 },
		{ 0, 73,  137, 536 },
		{ 0, 145,  210, 536 },
		{ 0, 217,  282, 536 },
		{ 0, 289,  353, 536 },
		{ 0, 361,  426, 536 },
		{ 0, 433,  497, 536 },
	};

	//�A�j���[�V�����̃R�}�Ԋu����
	if (m_beam_ani_time > 3)
	{
		m_beam_ani++;		//�A�j���[�V�����̃R�}��1�i�߂�
		m_beam_ani_time = 0;

		m_beam_eff = beam_ani_src[m_beam_ani];//�A�j���[�V������RECT�z�񂩂�m_ani�Ԗڂ�RECT���擾
	}
	else
	{
		m_beam_ani_time++;
	}


	if (m_beam_ani == 7)
	{
		m_beam_ani = 0;
		this->SetStatus(false);    //���g�ɍ폜���߂��o��
		Hits::DeleteHitBox(this);  //��l���@�����L����HitBox�ɍ폜����
	}


		RECT_F ani_src[8] =
		{
			{ 0,  220,   460, 203 },
			{ 0, 460,   490, 203 },
			{ 0, 490,   930, 203 },
			{ 0, 930,   1160, 203 },
			{ 0, 1160,   1390, 203 },
			{ 0, 1390,   1625, 203 },
			{ 0, 1625,   1850, 203 },
			{ 0, 1850,   2096, 203 },

		};
		//���g��HitBox�������Ă���
		CHitBox* hit = Hits::GetHitBox(this);


		if (m_ani_flag == true)
		{
			//�A�j���[�V�����̃R�}�Ԋu����
			if (m_ani_time > 2)
			{

				m_ani++;	//�A�j���[�V�����̃R�}���P�i�߂�
				m_ani_time = 0;

				m_eff = ani_src[m_ani];//�A�j���[�V������RECT�z�񂩂�m_ani�Ԗڂ�RECT���擾
				m_ani_stop++;
				if (m_ani_stop >= 8)
				{
					m_ani_flag = false;
					m_eff.m_top = 0;
					m_eff.m_left = 0;
					m_eff.m_right = 220;
					m_eff.m_bottom = 203;

				}
			}
			else
			{
				m_ani_time++;
			}

		}
		//�u���b�N���������Ă���
		CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
		//HitBox�̈ʒu�̕ύX
		hit->SetPos(m_px + block->GetScrollx(), m_py + block->GetScrolly());

		//Hits::DeleteHitBox(this);
}

//�h���[
void CObjBeam::Draw()
{

	//�`��J���[���
	float b[4] = { 0.4f,0.4f,0.4f,1.0f };	//�擾�ł��Ă��Ȃ��F
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };	//�擾�ł��Ă���F

	RECT_F dst;	//�`���\���ʒu

				//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//���[�v
	if (m_beam_flag == true)
	{
		//�\���ʒu�̐ݒ�
		dst.m_top = 0.0f + m_py + block->GetScrolly();
		dst.m_left = 200.0f + m_px + block->GetScrollx();
		dst.m_right = 0.0f + m_px + block->GetScrollx();
		dst.m_bottom = 1000.0f + m_py + block->GetScrolly();
		//�G�t�F�N�g�̕`��
		Draw::Draw(35, &m_beam_eff, &dst, c, 0.0f);

	}
	else
	{
		m_beam_ani = 0;
	}

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py + block->GetScrolly();	//�`��ɑ΂��ăX�N���[���̉e����������
	dst.m_left = 0.0f + m_px + block->GetScrollx();
	dst.m_right = 64.0f + m_px + block->GetScrollx();
	dst.m_bottom = 64.0f + m_py + block->GetScrolly();

	Draw::Draw(36, &m_beam_eff, &dst, c, 0.0f);
}


