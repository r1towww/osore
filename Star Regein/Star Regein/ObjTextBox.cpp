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
			m_text += 1;
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
			Font::StrDraw(L"�e�X�g", 150, 450, 32, c);
		}
		else if (m_text == 1)
		{
			Font::StrDraw(L"�e�X�g2", 150, 450, 32, c);
		}
		else if (m_text == 2)
		{
			Font::StrDraw(L"�e�X�g2", 150, 450, 32, c);
		}
	}
	

}
