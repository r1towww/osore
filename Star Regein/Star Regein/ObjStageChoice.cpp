//�g�p����w�b�_�[
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\SceneManager.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "ObjStageChoice.h"

//----------------------------------
//�g�p����l�[���X�y�[�X
using namespace GameL;


//�C�j�V�����C�Y
void CObjStageChoice::Init()
{
	m_alpha = ALPHAORIGIN;		//�A���t�@�l�̏�����
	m_time = true;
}

//�A�N�V����
void CObjStageChoice::Action()
{
	if (m_alpha >= 1.0f)
	{
		m_alpha = 1.0f;
	}
	else
	{
		m_alpha += 0.03f;
	}
}

//�h���[
void CObjStageChoice::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,m_alpha };
	float y[4] = { 1.0f,1.0f,0.0f,m_alpha };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	//�w�i------------------------------------
	//�؂���ʒu�̐ݒ�
	src.m_top    = 0.0f;
	src.m_left   = 0.0f;
	src.m_right  = 1920.0f;
	src.m_bottom = 1080.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top    = 0.0f ;
	dst.m_left   = 0.0f ;
	dst.m_right  = 800.0f ;
	dst.m_bottom = 600.0f ;

	//�\��
	Draw::Draw(2, &src, &dst, c, 0.0f);
	//----------------------------------------

	//�n��------------------------------------
	//�؂���ʒu�̐ݒ�
	src.m_top    = 0.0f;
	src.m_left   = 660.0f;
	src.m_right  = 880.0f;
	src.m_bottom = 220.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top    = 380.0f;
	dst.m_left   = 15.0f;
	dst.m_right  = 175.0f;
	dst.m_bottom = 550.0f;

	//�\��
	Draw::Draw(8, &src, &dst, c, 0.0f);
	if (g_Earth_clear == true)
	{
		Font::StrDraw(L"CLEAR!", 40, 550, 40, y);
	}

	//----------------------------------------

	//����------------------------------------
	//�؂���ʒu�̐ݒ�
	src.m_top    = 0.0f;
	src.m_left   = 440.0f;
	src.m_right  = 660.0f;
	src.m_bottom = 220.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top    = 250.0f;
	dst.m_left   = 200.0f;
	dst.m_right  = 400.0f;
	dst.m_bottom = 450.0f;


	//�\��
	Draw::Draw(8, &src, &dst, c, 0.0f);
	if (g_Venus_clear == true)
	{
		Font::StrDraw(L"CLEAR!", 245, 450, 40, y);
	}

	//----------------------------------------

	//����------------------------------------
	//�؂���ʒu�̐ݒ�
	src.m_top    = 0.0f;
	src.m_left   = 220.0f;
	src.m_right  = 440.0f;
	src.m_bottom = 220.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top    = 150.0f;
	dst.m_left   = 410.0f;
	dst.m_right  = 560.0f;
	dst.m_bottom = 300.0f;

	//�\��
	Draw::Draw(8, &src, &dst, c, 0.0f);
	if (g_Mercury_clear == true)
	{
		Font::StrDraw(L"CLEAR!", 435, 300, 40, y);
	}

	//----------------------------------------

	//���z------------------------------------
	//�؂���ʒu�̐ݒ�
	src.m_top    = 0.0f;
	src.m_left   = 0.0f;
	src.m_right  = 220.0f;
	src.m_bottom = 220.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top    = -150.0f;
	dst.m_left   = 550.0f;
	dst.m_right  = 900.0f;
	dst.m_bottom = 200.0f;

	//�\��
	Draw::Draw(8, &src, &dst, c, 0.0f);
	if (g_Sun_clear == true)
	{
		Font::StrDraw(L"CLEAR!", 650, 180, 40, y);
	}

	//----------------------------------------

}
