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

bool g_tutorial_next_flag = false;


//�C�j�V�����C�Y
void CObjTextBox::Init()
{
	m_f = true;
	m_text = 0;
}

//�A�N�V����
void CObjTextBox::Action()
{
	//�L�[�^�C���𒴂����Z�\
	//Z�L�[����
	if (Input::GetVKey('Z') == true && g_tutorial_next_flag == true ||Input::GetVKey(VK_RETURN)==true&& g_tutorial_next_flag ==true)
	{
			
		if (m_f == false)
		{
			//�`���[�g���A���t���O���I���̂Ƃ�
			if (g_tutorial_flag == true)
			{
				Audio::Start(1);
				g_tutorial_next_flag = false;

				m_text++;//�e�L�X�g��i�߂�
				m_f = true;
			}
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
		if (g_stage == EarthStar)
		{
			Font::StrDraw(L"X�L�[�Ń`���[�g���A�����X�L�b�v", 300, 350, 32, c);
		}
		else
			Font::StrDraw(L"X�L�[�œV�̐��𖳎�����", 350, 370, 32, c);

	}
	//�`���[�g���A���t���O���I�t�ŏI������
	if (g_tutorial_flag == false)
	{
		;
	}
	//�n��
	else if (g_tutorial_flag == true)
	{
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
				Font::StrDraw(L"�����A��ɂĂ�т���̃X�L����", TEXT_X, TEXT_Y1, TEXTSIZE, c);
				Font::StrDraw(L"�l�����Ă���Ȃ�A�V�����̃X�L����", TEXT_X, TEXT_Y2, TEXTSIZE, c);
				Font::StrDraw(L"�Z�b�g���邱�ƂŔ����ł��܂��I", TEXT_X, TEXT_Y3, TEXTSIZE, c);
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
				Font::StrDraw(L"HP�ɉ����čU���͂̕ς��p�b�V�u�X�L��", TEXT_X, TEXT_Y2, TEXTSIZE, c);
				Font::StrDraw(L"���擾���邱�Ƃ��ł��܂�", TEXT_X, TEXT_Y3, TEXTSIZE, c);

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
				Font::StrDraw(L"�V�����̓G�͉�����", TEXT_X, TEXT_Y1, TEXTSIZE, c);
				Font::StrDraw(L"��{�I�ɐ키�ӎv�͂Ȃ��̂ŁA", TEXT_X, TEXT_Y2, TEXTSIZE, c);
				Font::StrDraw(L"���a�ɂ����܂��傤�c�I", TEXT_X, TEXT_Y3, TEXTSIZE, c);


			}
			else if (m_text == 6)
			{
				Font::StrDraw(L"�����A�U�����Ă��܂�����E�E�E", TEXT_X, TEXT_Y1, TEXTSIZE, c);
				Font::StrDraw(L"���̎��͊撣���Đ����Ă��������E�E�E", TEXT_X, TEXT_Y2, TEXTSIZE, c);
			}
		}
		//�ӂ�����
		else if (g_stage == MercuryGemini)
		{
			if (m_text == 0)
			{
				Font::StrDraw(L"�����ւ悤�����I", TEXT_X, TEXT_Y1, TEXTSIZE, c);
				Font::StrDraw(L"���������ł͑o�q���Ƃ��Ƃߍ���", TEXT_X, TEXT_Y2, TEXTSIZE, c);
				Font::StrDraw(L"�X�L�����擾���邱�Ƃ��ł��܂�", TEXT_X, TEXT_Y3, TEXTSIZE, c);

			}
			else if (m_text == 1)
			{
				Font::StrDraw(L"�����A�o�q���Ŏ擾�ł���X�L����", TEXT_X, TEXT_Y1, TEXTSIZE, c);
				Font::StrDraw(L"�T�u�@�o���X�L�����擾���邱�Ƃ��ł��܂�", TEXT_X, TEXT_Y2, TEXTSIZE, c);
				Font::StrDraw(L"�i�擾��X�L�[�Ŕ����j", TEXT_X, TEXT_Y3, TEXTSIZE, c);

			}
			else if (m_text == 2)
			{
				Font::StrDraw(L"�����Ŋl�����ׂ����͑S����14�ł�", TEXT_X, TEXT_Y1, TEXTSIZE, c);
				Font::StrDraw(L"�����A�W�߂Ă����܂��傤�I", TEXT_X, TEXT_Y2, TEXTSIZE, c);

			}
		}
		//���Ƃߍ�
		else if (g_stage == MercuryVirgo)
		{
			if (m_text == 0)
			{
				Font::StrDraw(L"�����ւ悤�����I", TEXT_X, TEXT_Y1, TEXTSIZE, c);
				Font::StrDraw(L"���������ł͑o�q���Ƃ��Ƃߍ���", TEXT_X, TEXT_Y2, TEXTSIZE, c);
				Font::StrDraw(L"�X�L�����擾���邱�Ƃ��ł��܂�", TEXT_X, TEXT_Y3, TEXTSIZE, c);

			}
			else if (m_text == 1)
			{
				Font::StrDraw(L"�����A���Ƃߍ��Ŏ擾�ł���X�L����", TEXT_X, TEXT_Y1, TEXTSIZE, c);
				Font::StrDraw(L"HP�z���������U���X�L�����擾���邱�Ƃ��ł��܂�", TEXT_X, TEXT_Y2, TEXTSIZE, c);
				Font::StrDraw(L"�i�擾��X�L�[�Ŕ����j", TEXT_X, TEXT_Y3, TEXTSIZE, c);

			}
			else if (m_text == 2)
			{
				Font::StrDraw(L"�����Ŋl�����ׂ����͑S����15�ł�", TEXT_X, TEXT_Y1, TEXTSIZE, c);
				Font::StrDraw(L"�����A�W�߂Ă����܂��傤�I", TEXT_X, TEXT_Y2, TEXTSIZE, c);

			}

		}
		//���z
		else if (g_stage == SunLeo)
		{
			if (m_text == 0)
			{
				Font::StrDraw(L"���z�ւ悤�����I", TEXT_X, TEXT_Y1, TEXTSIZE, c);
				Font::StrDraw(L"�������z�ł͎��q����", TEXT_X, TEXT_Y2, TEXTSIZE, c);
				Font::StrDraw(L"�X�L�����擾���邱�Ƃ��ł��܂�", TEXT_X, TEXT_Y3, TEXTSIZE, c);

			}
			else if (m_text == 1)
			{
				Font::StrDraw(L"���q���Ŏ擾�ł���X�L����", TEXT_X, TEXT_Y1, TEXTSIZE, c);
				Font::StrDraw(L"���͂̓G���}�q������X�L����", TEXT_X, TEXT_Y2, TEXTSIZE, c);
				Font::StrDraw(L"�擾���邱�Ƃ��ł��܂�", TEXT_X, TEXT_Y3, TEXTSIZE, c);

			}
			else if (m_text == 2)
			{
				Font::StrDraw(L"�����Ŋl�����ׂ����͑S����15�ł�", TEXT_X, TEXT_Y1, TEXTSIZE, c);
				Font::StrDraw(L"�����ɂ���G�́A�₯�ǂ�t�^����", TEXT_X, TEXT_Y2, TEXTSIZE, c);
				Font::StrDraw(L"�U�������Ă��܂��I", TEXT_X, TEXT_Y3, TEXTSIZE, c);

			}
			else if (m_text == 3)
			{
				Font::StrDraw(L"�₯�Ǐ�Ԃł͈�莞��", TEXT_X, TEXT_Y1, TEXTSIZE, c);
				Font::StrDraw(L"�_���[�W���󂯂Ă��܂��܂��I", TEXT_X, TEXT_Y2, TEXTSIZE, c);

			}
			else if (m_text == 4)
			{
				Font::StrDraw(L"�₯�ǂ͖������ł��Ȃ��̂�", TEXT_X, TEXT_Y1, TEXTSIZE, c);
				Font::StrDraw(L"�X�L������g����", TEXT_X, TEXT_Y2, TEXTSIZE, c);
				Font::StrDraw(L"�U�����Ă����܂��傤�I", TEXT_X, TEXT_Y3, TEXTSIZE, c);

			}

		}
		
	}

}


