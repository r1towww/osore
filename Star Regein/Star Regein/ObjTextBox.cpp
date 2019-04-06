//�g�p����w�b�_�[
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\SceneManager.h"
#include "GameL/Audio.h"
#include "GameHead.h"
#include "ObjTextBox.h"
#include "ObjTutorial.h"

//----------------------------------
//�g�p����l�[���X�y�[�X
using namespace GameL;



//�C�j�V�����C�Y
void CObjTextBox::Init()
{
	m_key_time = 0;
	m_f = true;
	m_text = 0;
}

//�A�N�V����
void CObjTextBox::Action()
{
	//�f�����I������A�퓬��ʂւ̈ڍs�̍�
	if (g_stage == EarthStar)
	{

		//�摜���\�����ꂽ�ۂ́A�L�[���̓^�C������
		if (m_key_time >= 300)
			m_key_time = 300;	//�^�C����50�ɂȂ����ہA50�Ŏ~�߂�
		else
			m_key_time++;	//�L�[���̓^�C���𑝂₷

	}
	else
	{
		m_key_time = 0;	//����ȊO�̏ꍇ�A�L�[���̓^�C����0�ɂ���
	}
	//�L�[�^�C����300�𒴂����Z�\
	if (m_key_time >= 300)
	{
		//Z�L�[����
		if (Input::GetVKey('Z') == true)
		{
			if (m_f == false)
			{
				m_text++;//�e�L�X�g��i�߂�
				m_key_time = 0;//�L�[�^�C�������Z�b�g����
				m_f = true;
			}
			else
			{
				m_f = true;
			}
		}
		else
		{
			m_f = false;
		}
	}
}

//�h���[
void CObjTextBox::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	if (g_tutorial_flag == true)
	{
		Font::StrDraw(L"Z�L�[�Ŏ���", TEXT_ZX, TEXT_ZY, TEXTSIZE_Z, c);
	}
	//�n��
	if (g_stage == EarthStar)
	{
		if (m_text == 0)
		{
			Font::StrDraw(L"Star Regin�ւ悤�����I�I", TEXT_X, TEXT_Y1, TEXTSIZE, c);
			Font::StrDraw(L"�����A�n���X�e�[�W�ł͊�{�I�ȑ����", TEXT_X, TEXT_Y2, TEXTSIZE, c);
			Font::StrDraw(L"�Q�[���̃N���A���������`�����܂��I", TEXT_X, TEXT_Y3, TEXTSIZE, c);
		}
		else if (m_text == 1)
		{
			Font::StrDraw(L"�܂��͈ړ����Ă݂܂��傤", TEXT_X, TEXT_Y1, TEXTSIZE, c);
		}
		else if (m_text == 2)
		{
			Font::StrDraw(L"�����L�[�ňړ����邱�Ƃ��ł��܂�", TEXT_X, TEXT_Y1, TEXTSIZE, c);
		}
		else if (m_text == 3)
		{
			Font::StrDraw(L"���ɂ��̃Q�[���̃N���A������", TEXT_X, TEXT_Y1, TEXTSIZE, c);
			Font::StrDraw(L"�e�X�e�[�W�ɂ��鐯���W�߂邱�Ƃł�", TEXT_X, TEXT_Y2, TEXTSIZE, c);
		}
		else if (m_text == 4)
		{
			Font::StrDraw(L"�����W�߂���Ɛ������������A", TEXT_X, TEXT_Y1, TEXTSIZE, c);
			Font::StrDraw(L"�V�����X�L�����g�����Ƃ��ł��܂�", TEXT_X, TEXT_Y2, TEXTSIZE, c);
		}
		else if (m_text == 5)
		{
			Font::StrDraw(L"����ł͐����W�߂Ă݂܂��傤", TEXT_X, TEXT_Y1, TEXTSIZE, c);
		
		}
	}
	//else if (g_stage == VenusTaurus)
	//{
	//	if (m_text == 0)
	//	{
	//		Font::StrDraw(L"�e�X�g", 150, 450, 32, c);
	//	}
	//	else if (m_text == 1)
	//	{
	//		Font::StrDraw(L"�e�X�g2", 150, 450, 32, c);
	//	}
	//	else if (m_text == 2)
	//	{
	//		Font::StrDraw(L"�e�X�g3", 150, 450, 32, c);
	//	}
	//	else if (m_text == 3)
	//	{
	//		Font::StrDraw(L"�e�X�g4", 150, 450, 32, c);
	//	}
	//	else if (m_text == 4)
	//	{
	//		Font::StrDraw(L"�e�X�g5", 150, 450, 32, c);
	//	}

	//}
	

}
