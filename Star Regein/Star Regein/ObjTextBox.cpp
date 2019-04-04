//�g�p����w�b�_�[
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\SceneManager.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "ObjTextBox.h"


//----------------------------------
//�g�p����l�[���X�y�[�X
using namespace GameL;




//�C�j�V�����C�Y
void CObjTextBox::Init()
{
	m_f = true;
	m_text = 0;
}

//�A�N�V����
void CObjTextBox::Action()
{
	if (Input::GetVKey('Z') == true)
	{
		if (m_f == false)
		{
			m_text ++;
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

//�h���[
void CObjTextBox::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu
	//�n��
	if (g_stage == EarthStar)
	{
		if (m_text == 0)
		{
			Font::StrDraw(L"Star Regin�ւ悤�����I�I", 20, 450, 32, c);
			Font::StrDraw(L"�����A�n���X�e�[�W�ł͊�{�I�ȑ����", 20, 480, 32, c);
			Font::StrDraw(L"�Q�[���̃N���A���������`�����܂��I", 20, 510, 32, c);
		}
		else if (m_text == 1)
		{
			Font::StrDraw(L"�e�X�g2", 20, 450, 32, c);
		}
		else if (m_text == 2)
		{
			Font::StrDraw(L"�e�X�g3", 20, 450, 32, c);
		}
		else if (m_text == 3)
		{
			Font::StrDraw(L"�e�X�g4", 20, 450, 32, c);
		}
		else if (m_text == 4)
		{
			Font::StrDraw(L"�e�X�g5", 20, 450, 32, c);

		}
	}
	else if (g_stage == VenusTaurus)
	{
		if (m_text == 0)
		{
			Font::StrDraw(L"�e�X�g", 150, 450, 32, c);
		}
		else if (m_text == 1)
		{
			Font::StrDraw(L"�e�X�g2", 150, 450, 32, c);
		}
		else if (m_text == 2)
		{
			Font::StrDraw(L"�e�X�g3", 150, 450, 32, c);
		}
		else if (m_text == 3)
		{
			Font::StrDraw(L"�e�X�g4", 150, 450, 32, c);
		}
		else if (m_text == 4)
		{
			Font::StrDraw(L"�e�X�g5", 150, 450, 32, c);
		}

	}
	

}
