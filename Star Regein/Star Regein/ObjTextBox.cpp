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
	if (Input::GetVKey('Z') == true && g_tutorial_next_flag == true || Input::GetVKey(VK_RETURN) == true && g_tutorial_next_flag == true)
	{

		if (m_f == false)
		{
			//�`���[�g���A���t���O���I���̂Ƃ�
			if (g_tutorial_flag == true || g_Voice_flag == true)
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
			if (g_Leo_clear == true)
			{
				;
			}
			else
			{
				Font::StrDraw(L"X�L�[�Ń`���[�g���A�����X�L�b�v", 300, 350, 32, c);
			}
		}

		if (g_Voice_flag == true)
		{
			;
		}
		else if (g_Boss_Spawn == true)
		{
			Font::StrDraw(L"X�L�[�œV�̐��𖳎�����", 350, 370, 32, c);
		}
	
	}

	
	//�`���[�g���A���t���O���I�t�ŏI������
	if (g_tutorial_flag == false)
	{
		m_text = 0;
	}
	//�n��
	else if (g_tutorial_flag == true)
	{
		if (g_stage == EarthStar || g_stage == Space)
		{
			//���X�{�X���j��
			if (g_Voice_flag == true)
			{
				if (m_text == 0)
				{
					Font::StrDraw(L"���ׂĂ̐����̗͂��W�߁A", TEXT_X, TEXT_Y1, TEXTSIZE, c);
					Font::StrDraw(L"�G��|�������ƂŒn���ɕ��a���K��܂����B", TEXT_X, TEXT_Y2, TEXTSIZE, c);
				}
				else if (m_text == 1)
				{
					Font::StrDraw(L"����ł�����x�ƒn���̕��a��", TEXT_X, TEXT_Y1, TEXTSIZE, c);
					Font::StrDraw(L"��������邱�Ƃ͂Ȃ��ł��傤�B", TEXT_X, TEXT_Y2, TEXTSIZE, c);
				}
				else if (m_text == 2)
				{
					Font::StrDraw(L"�����܂�", TEXT_X, TEXT_Y1, TEXTSIZE, c);
					g_End_flag = true;
					
				}
			
			}
			//���X�{�X�o�����i�n���j
			else if (g_stage == EarthStar && g_Boss_Spawn == true)
			{
				if (m_text == 0)
				{
					Font::StrDraw(L"�{�����ʒB�ł��I", TEXT_X, TEXT_Y1, TEXTSIZE, c);
					Font::StrDraw(L"�n���ɐN�U���Ă����͎̂֎g�����Ǝv���܂��I", TEXT_X, TEXT_Y2, TEXTSIZE, c);
				}
				else if (m_text == 1)
				{
					Font::StrDraw(L"���܂Ŏ�ɓ��ꂽ������������g����", TEXT_X, TEXT_Y1, TEXTSIZE, c);
					Font::StrDraw(L"�G�𓢔����ĉ������I�I", TEXT_X, TEXT_Y2, TEXTSIZE, c);

				}
				else if (m_text == 2)
				{
					Font::StrDraw(L"�����Ă��鐯�̏ꏊ�ɍs����", TEXT_X, TEXT_Y1, TEXTSIZE, c);
					Font::StrDraw(L"�x���ǂ��̗͂��񕜂��܂��I", TEXT_X, TEXT_Y2, TEXTSIZE, c);

				}
				else if (m_text == 3)
				{
					Font::StrDraw(L"�������A�����Ɠ������ɂ����", TEXT_X, TEXT_Y1, TEXTSIZE, c);
					Font::StrDraw(L"�G�����m���ă��[�v���Ă���\����", TEXT_X, TEXT_Y2, TEXTSIZE, c);
					Font::StrDraw(L"����܂��̂ł����Ӊ������I", TEXT_X, TEXT_Y3, TEXTSIZE, c);

				}
				else if (m_text == 4)
				{
					Font::StrDraw(L"�n���̖��^�͂��Ȃ��Ɋ|�����Ă��܂��I", TEXT_X, TEXT_Y1, TEXTSIZE, c);
					Font::StrDraw(L"�����^���I", TEXT_X, TEXT_Y2, TEXTSIZE, c);
					
				}
			}
			else if (g_Sun_clear == true)//���X�{�X�o�����i�X�e�[�W�I����ʁj
			{
				if (m_text == 0)
				{
					Font::StrDraw(L"�ً}�A���I�ً}�A���I", TEXT_X, TEXT_Y1, TEXTSIZE, c);
					Font::StrDraw(L"�n���ɓ�̐����̏o���I", TEXT_X, TEXT_Y2, TEXTSIZE, c);
				}
				else if (m_text == 1)
				{
					Font::StrDraw(L"�����ɒn���֋A�҂��ĉ������I", TEXT_X, TEXT_Y1, TEXTSIZE, c);
					Font::StrDraw(L"�J��Ԃ��܂��c�c", TEXT_X, TEXT_Y2, TEXTSIZE, c);
				}
			}
			else//�`���[�g���A��
			{
				if (m_text == 0)
				{
					Font::StrDraw(L"Star Regin�ւ悤�����I�I", TEXT_X, TEXT_Y1, TEXTSIZE, c);
					Font::StrDraw(L"�����A�n���X�e�[�W�ł͊�{�I�ȑ����", TEXT_X, TEXT_Y2, TEXTSIZE, c);
					Font::StrDraw(L"�Q�[���̃N���A���������`�����܂�", TEXT_X, TEXT_Y3, TEXTSIZE, c);
				}
				else if (m_text == 1)
				{
					Font::StrDraw(L"�܂��͈ړ����Ă݂܂��傤", TEXT_X, TEXT_Y1, TEXTSIZE, c);
					Font::StrDraw(L"�����L�[�ňړ����邱�Ƃ��ł��܂�", TEXT_X, TEXT_Y2, TEXTSIZE, c);

				}
				else if (m_text == 2)
				{
					Font::StrDraw(L"���̃Q�[���̃N���A������", TEXT_X, TEXT_Y1, TEXTSIZE, c);
					Font::StrDraw(L"�e�X�e�[�W�ɂ��鐯���W�߂邱�Ƃł�", TEXT_X, TEXT_Y2, TEXTSIZE, c);

				}
				else if (m_text == 3)
				{
					Font::StrDraw(L"�����W�߂���Ɛ������������A", TEXT_X, TEXT_Y1, TEXTSIZE, c);
					Font::StrDraw(L"���̐����̃X�L�����g�����Ƃ��ł��܂�", TEXT_X, TEXT_Y2, TEXTSIZE, c);

				}
				else if (m_text == 4)
				{
					Font::StrDraw(L"�X�L���̐؂�ւ���C�L�[�ōs���܂�", TEXT_X, TEXT_Y1, TEXTSIZE, c);
					Font::StrDraw(L"�e�X�L���̐����̓w���v�Ŋm�F���ĉ�����", TEXT_X, TEXT_Y2, TEXTSIZE, c);
				}
				else if (m_text == 5)
				{
					Font::StrDraw(L"����ł͐����W�߂Ă݂܂��傤", TEXT_X, TEXT_Y1, TEXTSIZE, c);
				}
			}
		
		}

	}

}


