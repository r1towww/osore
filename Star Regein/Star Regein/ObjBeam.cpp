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

	m_beam_time = 100;

	m_beam_flag = false;
	m_ani_flag = true;

	m_time = 0;

	m_d_beam_flag = false;

	m_eff.m_top = 0;
	m_eff.m_left = 0;
	m_eff.m_right = 192;
	m_eff.m_bottom = 192;
	m_ani = 0;
	m_ani_time = 0;
						//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px + 70, m_py - 500, 210, 2300, ELEMENT_ENEMY, OBJ_BEAM, 1);
}

//�A�N�V����
void CObjBeam::Action()
{


	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + 70 + block->GetScrollx(), m_py - 500 + block->GetScrolly());

	hit->SetInvincibility(true);

	if (m_ani_flag == true)
	{
		RECT_F ani_src[10] =
		{
			{ 0,    0,  192, 192 },
			{ 0,  192,  384, 192 },
			{ 0,  384,  576, 192 },
			{ 0,  576,  768, 192 },
			{ 0,  768,  960, 192 },
			{ 192,    0,  192, 384 },
			{ 192,  192,  384, 384 },
			{ 192,  384,  576, 384 },
			{ 192,  576,  768, 384 },
			{ 192,  768,  960, 384 },

		};


		//�A�j���[�V�����̃R�}�Ԋu����
		if (m_ani_time > 6)
		{
			m_ani++;		//�A�j���[�V�����̃R�}��1�i�߂�
			m_ani_time = 0;

			m_eff = ani_src[m_ani];//�A�j���[�V������RECT�z�񂩂�m_ani�Ԗڂ�RECT���擾
		}
		else
		{
			m_ani_time++;
		}


		if (m_ani == 10)
		{
			m_ani = 0;
			m_beam_flag = true;
			Audio::Start(20);
			m_ani_flag = false;
		}
	}


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

		if (m_beam_flag == true)
		{
			//�A�j���[�V�����̃R�}�Ԋu����
			if (m_beam_ani_time > 6 && m_beam_ani != 2 && m_beam_ani != 5)
			{
				m_beam_ani++;		//�A�j���[�V�����̃R�}��1�i�߂�
				m_beam_ani_time = 0;

				m_beam_eff = beam_ani_src[m_beam_ani];//�A�j���[�V������RECT�z�񂩂�m_ani�Ԗڂ�RECT���擾
			}
			else if (m_beam_ani_time <= 6 && m_beam_ani != 2 && m_beam_ani != 5)
			{
				m_beam_ani_time++;
			}

			//2�Ԗڂ̂Ƃ��R�}�̐i�s�������x������
			if (m_beam_ani == 2)
			{
				m_time++;

				if (m_time >= 50)
				{
					m_beam_ani++;
					m_time = 0;
				}
			}
		}

		//5�Ԗڂ̂Ƃ��t���O���I�t�ɂ���
		if (m_beam_ani == 5)
		{
			m_time++;
			hit->SetInvincibility(false);
			m_beam_flag = false;
		}

		//�t���O���I�t����m_time��100�ȏ�̂Ƃ��R�}�̐i�s�������x������
		if (m_beam_flag == false && m_time >= 100)
		{
			if (m_beam_ani_time > 6)
			{
				m_beam_ani--;		//�A�j���[�V�����̃R�}��1�i�߂�
				m_beam_ani_time = 0;

				m_beam_eff = beam_ani_src[m_beam_ani];//�A�j���[�V������RECT�z�񂩂�m_ani�Ԗڂ�RECT���擾
			}
			else
			{
				m_beam_ani_time++;
			}

			//0�Ԗڂ̂Ƃ��r�[�����폜
			if (m_beam_ani == 0)
			{
				m_time = 0;
				m_beam_ani_time = 0;
				this->SetStatus(false);    //���g�ɍ폜���߂��o��
				Hits::DeleteHitBox(this);  //��l���@�����L����HitBox�ɍ폜����
			}
		}


	if (m_d_beam_flag == true)
	{

	}


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
	//�\���ʒu�̐ݒ�
	dst.m_top = -500.0f + m_py + block->GetScrolly();
	dst.m_left = 330.0f + m_px + block->GetScrollx();
	dst.m_right = 0.0f + m_px + block->GetScrollx();
	dst.m_bottom = 1800.0f + m_py + block->GetScrolly();
	//�G�t�F�N�g�̕`��
	Draw::Draw(37, &m_beam_eff, &dst, c, 0.0f);


	//�\���ʒu�̐ݒ�
	dst.m_top = -500.0f + m_py + block->GetScrolly();	//�`��ɑ΂��ăX�N���[���̉e����������
	dst.m_left = 330.0f + m_px + block->GetScrollx();
	dst.m_right = 0.0f + m_px + block->GetScrollx();
	dst.m_bottom = -170.0f + m_py + block->GetScrolly();

	Draw::Draw(36, &m_eff, &dst, c, 0.0f);
}


