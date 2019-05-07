//�g�p����w�b�_�[
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\SceneManager.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "ObjTutorial.h"


//----------------------------------
//�g�p����l�[���X�y�[�X
using namespace GameL;

bool g_tutorial__flag=false;

//�C�j�V�����C�Y
void CObjTutorial::Init()
{
	g_tutorial_flag = true;

	//�L�[���͗p�^�C���̏�����
	m_keytime = 0.f;

	m_page = 0;		//�n���ꂽ�y�[�W��
	m_sec = 0;		//�b���J�E���g
	m_blink = 0;
	m_line = 0;		//�s���J�E���g
	m_f = true;
	m_next_f = false;
}

//�A�N�V����
void CObjTutorial::Action()
{
	
	if (m_page == m_p) 
	{//�n���ꂽ�y�[�W���ƌ��݂̃y�[�W���������ɂȂ�����
		g_tutorial_flag = false;
	}

	//X�L�[�������ăX�L�b�v�i�ړ��L�[����͂ł��Ȃ����Ă���j
	if (Input::GetVKey('X') == true && Input::GetVKey(VK_UP) == false && Input::GetVKey(VK_DOWN) == false 
									&& Input::GetVKey(VK_LEFT) == false && Input::GetVKey(VK_RIGHT) == false )
	{
		g_tutorial_flag = false;
	}
	
}



//�h���[
void CObjTutorial::Draw()
{
		//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu
	if (g_tutorial_flag == false)
	{
		return;
	}
	//�`���[�g���A���t���O�����������`���[�g���A�����J�n����
	else if (g_tutorial_flag == true)
	{
		//�e�L�X�g�{�b�N�X�\��
		if (m_tipe == 0)
		{

			//�`���[�g���A����p�e�L�X�g�{�b�N�X------------------------------------
			//�؂���ʒu�̐ݒ�
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 822.0f;
			src.m_bottom = 218.0f;

			//�\���ʒu�̐ݒ�
			dst.m_top = 422.0f;
			dst.m_left = 10.0f;
			dst.m_right = 785.0f;
			dst.m_bottom = 600.0f;
			//�\��
			Draw::Draw(40, &src, &dst, c, 0.0f);


		}
		//----------------------------------------
		else if (m_tipe == 1)
		{//tipe1�́A�R�����g���B���摜�\��
			//�`���[�g���A����pmini�{�b�N�X------------------------------------
			//�؂���ʒu�̐ݒ�
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 287.0f;
			src.m_bottom = 97.0f;

			//�\���ʒu�̐ݒ�
			dst.m_top = 343.0f;
			dst.m_left = -30.0f;
			dst.m_right = 257.0f;
			dst.m_bottom = 440.0f;
			Draw::Draw(42, &src, &dst, c, 0.0f);

			if (m_sec <= 715)
			{//715(�R�����g�̕�)�܂Ŏ��Ԍo��
				m_sec += 20;	   //�����̕\���X�s�[�h---------------------
				m_blink += 10;
			}				   //���𒴂���ƁA�s����+1
			else
			{
				m_line += 1;
				m_sec = 0;
				m_blink = 0;
			}

			//�؂���ʒu�̐ݒ�(�摜�̍��������ɐݒ�)
			src.m_top = 20.0f;
			src.m_left = 20.0f;
			src.m_right = 119.0f;
			src.m_bottom = 55.0f;

			if (m_p != 1)
			{
				//Z���͂���ѐ���t���O�I���Ŏ��̂؁[�W��
				if (Input::GetVKey('Z') == true&& m_next_f==true)
				{
					if (m_f == false)
					{
						m_line += 1;
						m_f = true;
						//�L�[���͉\���ԂɂȂ�����Z�������Đi��
						if (m_line >= 3)
						{
							m_page += 1;
							m_line = 0;		//�s�����Z�b�g
							m_sec = 0;		//�b�����Z�b�g
							m_next_f = false;
							g_tutorial_next_flag = true;

						}

					}

				}
				else
				{
					m_f = false;
				}

				if (m_line == 0)
				{//�P�s�ځ[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
					//�\���ʒu�̐ݒ�
					dst.m_top = 450.0f;
					if (m_line == 0)//�P�s�ڂ̎��̂ݓ���
						dst.m_left = 50.0f + (m_sec*1.0f);
					else
						dst.m_left = 50.0f;
					dst.m_right = 765.0f;
					dst.m_bottom = 490.0f;
					//�`��
					Draw::Draw(41, &src, &dst, c, 0.0f);
				}//�s���ς��ƁA�\�����Ȃ�
				else { ; }
				if (m_line <= 1)
				{//�Q�s�ځ[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
					//�\���ʒu�̐ݒ�
					dst.m_top = 491.0f;
					if (m_line == 1)//�Q�s�ڂ̎��̂ݓ���
						dst.m_left = 20.0f + (m_sec*1.0f);
					else
						dst.m_left = 20.0f;
					dst.m_right = 765.0f;
					dst.m_bottom = 520.0f;
					//�`��
					Draw::Draw(41, &src, &dst, c, 0.0f);
				}//�s���ς��ƁA�\�����Ȃ�
				else { ; }
				if (m_line <= 2 && m_p != 1)
				{//�R�s�ځ[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
					//�\���ʒu�̐ݒ�
					dst.m_top = 521.0f;
					if (m_line == 2)//�R�s�ڂ̎��̂ݓ���
						dst.m_left = 20.0f + (m_sec*1.0f);
					else
						dst.m_left = 20.0f;
					dst.m_right = 765.0f;
					dst.m_bottom = 570.0f;
					//�`��
					Draw::Draw(41, &src, &dst, c, 0.0f);
				}//�s���ς��ƁA�\�����Ȃ�
				else { ; }
			}

			if (m_line <= 3 || m_p == 1)
			{//�E�E�E�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
				dst.m_top = 540.0f;
				//if (m_line > 2 || m_p == 1)//�R�s�ڈȍ~�A����
				//	if (m_blink <= 160)//�\���ʒu��i�K�I�ɕύX
				//		dst.m_left = 780.0f;
				//	else if (m_blink <= 250)
				//		dst.m_left = 600.0f;
				//	else { dst.m_left = 600.0f; m_blink = 0; m_sec = 0; }//�J�E���g���O�ɂ��āA���ɖ߂�
				//else
					dst.m_left = 780.0f;
				dst.m_right = 750.0f;
				dst.m_bottom = 575.0f;
				//�`��
				Draw::Draw(41, &src, &dst, c, 0.0f);
				m_next_f = true;

			}
			else 
			{ ; }
		}
		Font::StrDraw(L"�`���[�g���A��", 10, 380, 30, c);




	}

}
