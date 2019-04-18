//�g�p����w�b�_�[
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\SceneManager.h"
#include "GameL\Audio.h"
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
		//Z�L�[����
		if (Input::GetVKey('Z') == true)
		{
			
			if (m_f == false)
			{
				if (g_tutorial_flag == true)
				{
					Audio::Start(1);
					m_text++;//�e�L�X�g��i�߂�
					m_key_time = 0;//�L�[�^�C�������Z�b�g����
					m_f = true;
				}
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

//�h���[
void CObjTextBox::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	if (g_tutorial_flag == true)
	{
		Font::StrDraw(L"Z�L�[�Ŏ���", TEXT_ZX, TEXT_ZY, TEXTSIZE_Z, c);
		Font::StrDraw(L"X�L�[�Ń`���[�g���A�����X�L�b�v", 300, 350, 32, c);

	}
	//�`���[�g���A���t���O���I�t�ŏI������
	if (g_tutorial_flag == false)
	{
		;
	}
	//�n��
	else if (g_stage == EarthStar)
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
			Font::StrDraw(L"�����L�[�ňړ����邱�Ƃ��ł��܂�", TEXT_X, TEXT_Y2, TEXTSIZE, c);

		}
		else if (m_text == 2)
		{
			Font::StrDraw(L"���ɂ��̃Q�[���̃N���A������", TEXT_X, TEXT_Y1, TEXTSIZE, c);
			Font::StrDraw(L"�e�X�e�[�W�ɂ��鐯���W�߂邱�Ƃł�", TEXT_X, TEXT_Y2, TEXTSIZE, c);

		}
		else if (m_text == 3)
		{
			Font::StrDraw(L"�����W�߂���Ɛ������������A", TEXT_X, TEXT_Y1, TEXTSIZE, c);
			Font::StrDraw(L"�V�����X�L�����g�����Ƃ��ł��܂�", TEXT_X, TEXT_Y2, TEXTSIZE, c);

		}
		else if (m_text == 4)
		{
			Font::StrDraw(L"����ł͐����W�߂Ă݂܂��傤", TEXT_X, TEXT_Y1, TEXTSIZE, c);

		}
	}
	//��������
	else if (g_stage == VenusTaurus)
	{
		if (m_text == 0)
		{
			Font::StrDraw(L"���������ł͂��������ƂĂ�т����", TEXT_X, TEXT_Y1, TEXTSIZE, c);
			Font::StrDraw(L"�X�L�����擾���邱�Ƃ��ł��܂�", TEXT_X, TEXT_Y2, TEXTSIZE, c);
		}
		else if (m_text == 1)
		{
			Font::StrDraw(L"�����A���������Ŏ擾�ł���X�L����", TEXT_X, TEXT_Y1, TEXTSIZE, c);
			Font::StrDraw(L"�_�b�V���X�L�����擾���邱�Ƃ��ł��܂�", TEXT_X, TEXT_Y2, TEXTSIZE, c);

		}
		else if (m_text == 2)
		{
			Font::StrDraw(L"�����Ŋl�����ׂ����͑S���łP�W������܂�", TEXT_X, TEXT_Y1, TEXTSIZE, c);
			Font::StrDraw(L"�������A���̋�������G���o�����܂�", TEXT_X, TEXT_Y2, TEXTSIZE, c);

		}
		else if (m_text == 3)
		{
			Font::StrDraw(L"Z�L�[�ōU�����邱�Ƃ��\�ł�", TEXT_X, TEXT_Y1, TEXTSIZE, c);
			Font::StrDraw(L"������HP���O�ɂȂ��Ă��܂���", TEXT_X, TEXT_Y2, TEXTSIZE, c);
			Font::StrDraw(L"GAMEOVER�ɂȂ��Ă��܂��܂�", TEXT_X, TEXT_Y3, TEXTSIZE, c);

		}
		else if (m_text == 4)
		{
			Font::StrDraw(L"�G����������|���ɍs���̂������ł���", TEXT_X, TEXT_Y1, TEXTSIZE, c);
			Font::StrDraw(L"�������ׂĊl������ƃN���A�Ȃ̂�", TEXT_X, TEXT_Y2, TEXTSIZE, c);
			Font::StrDraw(L"���l����D��I�ɍs�����܂��傤�I", TEXT_X, TEXT_Y3, TEXTSIZE, c);

		}
		else if (m_text == 5)
		{
			Font::StrDraw(L"�����A��ɂĂ�т���̃q�[���X�L����", TEXT_X, TEXT_Y1, TEXTSIZE, c);
			Font::StrDraw(L"�l�����Ă���Ȃ�A", TEXT_X, TEXT_Y2, TEXTSIZE, c);
			Font::StrDraw(L"�V�t�g�L�[�Ŕ����ł��܂��I", TEXT_X, TEXT_Y3, TEXTSIZE, c);
		}
		else if (m_text == 6)
		{
			Font::StrDraw(L"�X�L�����g���ɂ�MP�i���Q�[�W�j���K�v�ł�", TEXT_X, TEXT_Y1, TEXTSIZE, c);
			Font::StrDraw(L"MP�͎��Ԍo�߂ŉ񕜂��Ă����̂ŁA", TEXT_X, TEXT_Y2, TEXTSIZE, c);
			Font::StrDraw(L"�ǂ�ǂ�g���Ă����܂��傤�I", TEXT_X, TEXT_Y3, TEXTSIZE, c);
		}
	}
	//�Ă�т��
	else if (g_stage == VenusLibra)
	{
		if (m_text == 0)
		{
			Font::StrDraw(L"���������ł͂��������ƂĂ�т����", TEXT_X, TEXT_Y1, TEXTSIZE, c);
			Font::StrDraw(L"�X�L�����擾���邱�Ƃ��ł��܂�", TEXT_X, TEXT_Y2, TEXTSIZE, c);

		}
		else if (m_text == 1)
		{
			Font::StrDraw(L"�����A�Ă�т���Ŏ擾�ł���X�L����", TEXT_X, TEXT_Y1, TEXTSIZE, c);
			Font::StrDraw(L"�q�[���i�񕜁j�X�L�����擾���邱�Ƃ��ł��܂�", TEXT_X, TEXT_Y2, TEXTSIZE, c);

		}
		else if (m_text == 2)
		{
			Font::StrDraw(L"�����Ŋl�����ׂ����͑S���łU�ł�", TEXT_X, TEXT_Y1, TEXTSIZE, c);
			Font::StrDraw(L"���̋�������G���o�����܂�", TEXT_X, TEXT_Y2, TEXTSIZE, c);

		}
		else if (m_text == 3)
		{
			Font::StrDraw(L"Z�L�[�ōU�����邱�Ƃ��\�ł�", TEXT_X, TEXT_Y1, TEXTSIZE, c);
			Font::StrDraw(L"������HP���O�ɂȂ��Ă��܂���", TEXT_X, TEXT_Y2, TEXTSIZE, c);
			Font::StrDraw(L"GAMEOVER�ɂȂ��Ă��܂��܂�", TEXT_X, TEXT_Y3, TEXTSIZE, c);

		}
		else if (m_text == 4)
		{
			Font::StrDraw(L"�G����������|���ɍs���̂������ł���", TEXT_X, TEXT_Y1, TEXTSIZE, c);
			Font::StrDraw(L"�������ׂĊl������ƃN���A�Ȃ̂�", TEXT_X, TEXT_Y2, TEXTSIZE, c);
			Font::StrDraw(L"���l����D��I�ɍs�����܂��傤�I", TEXT_X, TEXT_Y3, TEXTSIZE, c);

		}
		else if (m_text == 5)
		{
			Font::StrDraw(L"�����A��ɂ��������̃_�b�V���X�L����", TEXT_X, TEXT_Y1, TEXTSIZE, c);
			Font::StrDraw(L"�l�����Ă���Ȃ�A", TEXT_X, TEXT_Y2, TEXTSIZE, c);
			Font::StrDraw(L"�V�t�g�L�[�Ŕ����ł��܂��I", TEXT_X, TEXT_Y3, TEXTSIZE, c);


		}
		else if (m_text == 6)
		{
			Font::StrDraw(L"�X�L�����g���ɂ�MP�i���Q�[�W�j���K�v�ł�", TEXT_X, TEXT_Y1, TEXTSIZE, c);
			Font::StrDraw(L"MP�͎��Ԍo�߂ŉ񕜂��Ă����̂ŁA", TEXT_X, TEXT_Y2, TEXTSIZE, c);
			Font::StrDraw(L"�ǂ�ǂ�g���Ă����܂��傤�I", TEXT_X, TEXT_Y3, TEXTSIZE, c);

		}
	}


}
