//�g�p����w�b�_�[
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\SceneManager.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "ObjTutorial.h"

bool g_tutorial_flag = false;

//----------------------------------
//�g�p����l�[���X�y�[�X
using namespace GameL;


//�C�j�V�����C�Y
void CObjTutorial::Init()
{
	g_tutorial_flag = true;

	//�L�[���͗p�^�C���̏�����
	m_keytime = 0;

	m_page = 0;		//�n���ꂽ�y�[�W��
	m_sec = 0;		//�b���J�E���g
	m_line = 0;		//�s���J�E���g

}

//�A�N�V����
void CObjTutorial::Action()
{
	if (m_page == m_p) 
	{//�n���ꂽ�y�[�W���ƌ��݂̃y�[�W���������ɂȂ�����
		g_tutorial_flag = false;
	}

	//�f�����I������A�퓬��ʂւ̈ڍs�̍�
	if (g_stage == EarthStar )
	{

		//�摜���\�����ꂽ�ۂ́A�L�[���̓^�C������
		if (m_keytime >= 50)
			m_keytime = 50;	//�^�C����50�ɂȂ����ہA50�Ŏ~�߂�
		else
			m_keytime++;	//�L�[���̓^�C���𑝂₷

	}
	else
	{
		m_keytime = 0;	//����ȊO�̏ꍇ�A�L�[���̓^�C����0�ɂ���
	}

}



//�h���[
void CObjTutorial::Draw()
{
		//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	//�`���[�g���A���t���O�����������`���[�g���A�����J�n����
	if (g_tutorial_flag == true)
	{
		//�n��
		if (g_stage == EarthStar)
		{
			//�e�L�X�g�{�b�N�X�\��
			if (m_tipe == 0)
			{
				
				//�`���[�g���A����p�e�L�X�g�{�b�N�X------------------------------------
				//�؂���ʒu�̐ݒ�
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 775.0f;
				src.m_bottom = 183.0f;

				//�\���ʒu�̐ݒ�
				dst.m_top = 400.0f;
				dst.m_left = 0.0f;
				dst.m_right = 775.0f;
				dst.m_bottom = 588.0f;
				//�\��
				Draw::Draw(12, &src, &dst, c, 0.0f);
				if (m_p != 1) {//�y�[�W����1�ł͂Ȃ��ꍇ
				//�����摜�𖼑O�p�ɏォ��\��
				//�\���ʒu�̐ݒ�
					dst.m_top = 400.0f;
					dst.m_left = 0.0f;
					dst.m_right = 775.0f;
					dst.m_bottom = 588.0f;

					//�`��
					Draw::Draw(12, &src, &dst, c, 0.0f);
				}
				else { ; }

			}
			//----------------------------------------
			else if (m_tipe == 1) {//tipe1�́A�R�����g���B���摜�\��
				if (m_sec <= 700) {//715(�R�����g�̕�)�܂Ŏ��Ԍo��
					m_sec += 5;	   //�����̕\���X�s�[�h---------------------
				}				   //���𒴂���ƁA�s����+1
				else {
					m_line += 1;
					m_sec = 0;
				}

				//�؂���ʒu�̐ݒ�(�摜�̍��������ɐݒ�)
				src.m_top = 20.0f;
				src.m_left = 20.0f;
				src.m_right = 119.0f;
				src.m_bottom = 55.0f;

				if (m_p != 1) {
					if (m_line == 0) 
					{//�P�s�ځ[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
									  //�\���ʒu�̐ݒ�
						dst.m_top = 450.0f;
						if (m_line == 0)//�P�s�ڂ̎��̂ݓ���
							dst.m_left = 50.0f + (m_sec*1.0f);
						else
							dst.m_left = 50.0f;
						dst.m_right = 765.0f;
						dst.m_bottom = 480.0f;
						//�`��
						Draw::Draw(13, &src, &dst, c, 0.0f);
					}//�s���ς��ƁA�\�����Ȃ�
					else { ; }
					if (m_line <= 1) 
					{//�Q�s�ځ[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
									  //�\���ʒu�̐ݒ�
						dst.m_top = 480.0f;
						if (m_line == 1)//�Q�s�ڂ̎��̂ݓ���
							dst.m_left = 50.0f + (m_sec*1.0f);
						else
							dst.m_left = 50.0f;
						dst.m_right = 765.0f;
						dst.m_bottom = 510.0f;
						//�`��
						Draw::Draw(13, &src, &dst, c, 0.0f);
					}//�s���ς��ƁA�\�����Ȃ�
					else { ; }
					if (m_line <= 2 && m_p != 1) 
					{//�R�s�ځ[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
												  //�\���ʒu�̐ݒ�
						dst.m_top = 520.0f;
						if (m_line == 2)//�R�s�ڂ̎��̂ݓ���
							dst.m_left = 50.0f + (m_sec*1.0f);
						else
							dst.m_left = 50.0f;
						dst.m_right = 765.0f;
						dst.m_bottom = 550.0f;
						//�`��
						Draw::Draw(13, &src, &dst, c, 0.0f);
					}//�s���ς��ƁA�\�����Ȃ�
					else { ; }
				}

				if (m_line <= 3 || m_p == 1) 
				{//�E�E�E�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
					dst.m_top = 550.0f;
					if (m_line > 2 || m_p == 1)//�R�s�ڈȍ~�A����
						if (m_sec <= 160)//�\���ʒu��i�K�I�ɕύX
							dst.m_left = 745.0f;
						else if (m_sec <= 280)
							dst.m_left = 760.0f;
						else if (m_sec <= 440)
							dst.m_left = 770.0f;
						else if (m_sec <= 600)
							dst.m_left = 730.0f;
						else { dst.m_left = 730.0f; m_sec = 0; }//�J�E���g���O�ɂ��āA���ɖ߂�
					else
						dst.m_left = 730.0f;
					dst.m_right = 770.0f;
					dst.m_bottom = 575.0f;
					//�`��
					Draw::Draw(13, &src, &dst, c, 0.0f);
				}
				else { ; }
			}
			Font::StrDraw(L"�`���[�g���A��", 0, 410, 30, c);

			//�L�[���͉\���ԂɂȂ�����Z�������Đi��
			if (m_keytime == 50)
			{
				if (Input::GetVKey('Z') == true)
				{
					m_page += 1;
					m_line = 0;		//�s�����Z�b�g
					m_sec = 0;		//�b�����Z�b�g
					m_keytime = 0;
				}
			}

		}



	//	if (g_stage == VenusTaurus)
	//	{
	//		//�`���[�g���A����p�e�L�X�g�{�b�N�X------------------------------------
	//		//�؂���ʒu�̐ݒ�
	//		src.m_top = 0.0f;
	//		src.m_left = 0.0f;
	//		src.m_right = 775.0f;
	//		src.m_bottom = 183.0f;

	//		//�\���ʒu�̐ݒ�
	//		dst.m_top = 400.0f;
	//		dst.m_left = 0.0f;
	//		dst.m_right = 775.0f;
	//		dst.m_bottom = 588.0f;

	//		//�\��
	//		Draw::Draw(12, &src, &dst, c, 0.0f);
	//		//----------------------------------------
	//		Font::StrDraw(L"�`���[�g���A��", 0, 410, 30, c);
	//		//�L�[���͉\���ԂɂȂ�����Z�������Đi��
	//		if (m_keytime == 50)
	//		{
	//			if (Input::GetVKey('Z') == true)
	//			{
	//				m_page += 1;
	//			}
	//		}

	//	}
	//	if (g_stage == VenusLibra)
	//	{
	//		//�`���[�g���A����p�e�L�X�g�{�b�N�X------------------------------------
	//		//�؂���ʒu�̐ݒ�
	//		src.m_top = 0.0f;
	//		src.m_left = 0.0f;
	//		src.m_right = 775.0f;
	//		src.m_bottom = 183.0f;

	//		//�\���ʒu�̐ݒ�
	//		dst.m_top = 400.0f;
	//		dst.m_left = 0.0f;
	//		dst.m_right = 775.0f;
	//		dst.m_bottom = 588.0f;

	//		//�\��
	//		Draw::Draw(12, &src, &dst, c, 0.0f);
	//		//----------------------------------------
	//		Font::StrDraw(L"�`���[�g���A��", 0, 410, 30, c);
	//		for (int i = 0; i < 5; i++)
	//		{

	//		}
	//		//�L�[���͉\���ԂɂȂ�����Z�������Đi��
	//		if (m_keytime == 50)
	//		{
	//			if (Input::GetVKey('Z') == true)
	//			{
	//				g_tutorial_flag = false;
	//			}
	//		}
	//	}
	//	if (g_stage == MercuryGemini)
	//	{
	//		//�`���[�g���A����p�e�L�X�g�{�b�N�X------------------------------------
	//		//�؂���ʒu�̐ݒ�
	//		src.m_top = 0.0f;
	//		src.m_left = 0.0f;
	//		src.m_right = 775.0f;
	//		src.m_bottom = 183.0f;

	//		//�\���ʒu�̐ݒ�
	//		dst.m_top = 400.0f;
	//		dst.m_left = 0.0f;
	//		dst.m_right = 775.0f;
	//		dst.m_bottom = 588.0f;

	//		//�\��
	//		Draw::Draw(12, &src, &dst, c, 0.0f);
	//		//----------------------------------------
	//		Font::StrDraw(L"�`���[�g���A��", 0, 410, 30, c);
	//		for (int i = 0; i < 5; i++)
	//		{

	//		}
	//		//�L�[���͉\���ԂɂȂ�����Z�������Đi��
	//		if (m_keytime == 50)
	//		{
	//			if (Input::GetVKey('Z') == true)
	//			{
	//				g_tutorial_flag = false;
	//			}
	//		}
	//	}

	}


}
