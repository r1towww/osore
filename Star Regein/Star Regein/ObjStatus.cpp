//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"

#include "GameHead.h"
#include "ObjStatus.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

float g_hp;
float g_max_hp;
float g_mp;
float g_max_mp;

CObjStatus::CObjStatus()
{

}

//�C�j�V�����C�Y
void CObjStatus::Init()
{
	m_red = 0.0f;		//HP�p�J���[ ��	�̏�����
	m_gleen = 1.0f;		//HP�p�J���[ ��	�̏�����
	m_blue = 0.0f;		//HP�p�J���[ ��	�̏�����

}

//�A�N�V����
void CObjStatus::Action()
{
	//HP��20.0f�ȉ��̏ꍇ
	if (g_hp <= 20.0f)
	{
		//�J���[��ԂɕύX
		m_red = 1.0f;
		m_gleen = 0.0f;	
		m_blue = 0.0f;
	}
	//HP��50.0f�ȉ��̏ꍇ
	else if (g_hp <= 50.0f)
	{
		//�J���[�����ɕύX
		m_red = 1.0f;
		m_gleen = 1.0f;
		m_blue = 0.0f;
	}
	else	//����ȊO�̏ꍇ
	{
		//�J���[��΂ɕύX
		m_red = 0.0f;
		m_gleen = 1.0f;
		m_blue = 0.0f;
	}
}

//�h���[
void CObjStatus::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	float hpc[4] = { m_red,m_gleen,m_blue,1.0f };
	float mpc[4] = { 0.0f,0.0f,1.0f,1.0f };

	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	if (g_stage_clear == false)
	{
		//HP,MP�̔w�i�p--------------------------------

			//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 360.0f;
		src.m_right = 390.0f;
		src.m_bottom = 50.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top = 10.0f + STATUS_BACK_PY;
		dst.m_left = 0.0f;
		dst.m_right = 324.0f + STATUS_BACK_PX;
		dst.m_bottom = 53.0f + STATUS_BACK_PY;

		//�`��
		Draw::Draw(9, &src, &dst, c, 0.0f);

		//----------------------------------------------

		//HP�AMP�̕����̕`��----------------------------

		Font::StrDraw(L"HP", 2, 12, 21, c);	//HP
		Font::StrDraw(L"MP", 2, 33, 21, c);	//MP

	//----------------------------------------------

	//HP�`��p--------------------------------------
		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = (g_hp / g_max_hp)*1600.0f;
		src.m_bottom = 112.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top = 13.0f + STATUS_PY;
		dst.m_left = 4.0f + STATUS_PX;
		dst.m_right = (g_hp / g_max_hp)*320.0f + STATUS_PX;
		dst.m_bottom = 28.0f + STATUS_PY;

		//�`��
		Draw::Draw(10, &src, &dst, hpc, 0.0f);
		//----------------------------------------------

		//MP�`��p--------------------------------------
			//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = (g_mp / g_max_mp)*1600.0f;
		src.m_bottom = 112.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top = 35.0f + STATUS_PY;
		dst.m_left = 4.0f + STATUS_PX;
		dst.m_right = (g_mp / g_max_mp)*320.0f + STATUS_PX;
		dst.m_bottom = 50.0f + STATUS_PY;

		//�`��
		Draw::Draw(10, &src, &dst, mpc, 0.0f);
		//----------------------------------------------
	}

}