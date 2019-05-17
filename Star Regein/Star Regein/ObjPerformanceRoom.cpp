//�g�p����w�b�_�[
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\SceneManager.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "ObjPerformanceRoom.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;
#define CLEAR_F false
//�G�����ׂē|����------------------
bool g_Taurus_Enemy_AllKill= CLEAR_F;
bool g_Libra_Enemy_AllKill= CLEAR_F;
bool g_Gemini_Enemy_AllKill= CLEAR_F;
bool g_Viego_Enemy_AllKill= CLEAR_F;
bool g_Leo_Enemy_AllKill= CLEAR_F;
//���X�{�X��|����------------------
bool g_Earth_BossKill= CLEAR_F;
//�m�[�_���[�W�N���A----------------
bool g_Taurus_NoDamage_Clear= CLEAR_F;
bool g_Libra_NoDamage_Clear= CLEAR_F;
bool g_Gemini_NoDamage_Clear= CLEAR_F;
bool g_Viego_NoDamage_Clear= CLEAR_F;
bool g_Leo_NoDamage_Clear= CLEAR_F;


//�C�j�V�����C�Y
void CObjPerformanceRoom::Init()
{
	m_page = 0;
	m_next_f = false;
	m_back_f = false;
}

//�A�N�V����
void CObjPerformanceRoom::Action()
{
	//X�őI����ʂ֖߂�
	if (Input::GetVKey('X'))
	{
		g_stage = Space;
		this->SetStatus(false);    //���g�ɍ폜���߂��o��
	}
	//Z�L�[�Ŏ��̃y�[�W��
	if (Input::GetVKey('Z'))
	{
		if (m_next_f == true)
		{
			m_page++;
			m_next_f = false;
		}
	}

	else
	{
		m_next_f = true;
	}
	//C�L�[�őO�̃y�[�W��
	if (Input::GetVKey('C'))
	{
		if (m_back_f == true)
		{
			if (m_page <= 0)
			{
				;
			}
			else
			{
				m_page--;
			}
			m_back_f = false;
		}
	}
	else
	{
		m_back_f = true;
	}

}

//�h���[
void CObjPerformanceRoom::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	float a[4] = { 1.0f,1.0f,1.0f,0.8f };
	float y[4] = { 1.0f,1.0f,0.0f,1.0f };
	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu
	//�w�i�p�摜-----------------------------------
	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 822.0f;
	src.m_bottom = 218.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 100.0f;
	dst.m_left = 50.0f;
	dst.m_right = 750.0f;
	dst.m_bottom = 500.0f;
	//�\��
	Draw::Draw(40, &src, &dst, a, 0.0f);
	//----------------------------------------------

	//�����p�̃��b�Z�[�W�̕\��
	Font::StrDraw(L"�����������", 75, 120, 27, c);
	//���ђB����ʂŕ\�������邽�߂̃t���O����
	if (m_page == 0)
	{
		Font::StrDraw(L"�m�[�_���[�W�N���A", 75, 155, 27, c);
	}
	else if (m_page == 1)
	{
		Font::StrDraw(L"ALL KILL", 75, 155, 27, c);
	}
	Font::StrDraw(L"Z�L�[�Ŏ��̍��ڂ�", 518, 460, 27, c);
	if (m_page >= 1)
	{
		Font::StrDraw(L"C�L�[�őO�̍��ڂ�", 75, 460, 28, c);
	}
	Font::StrDraw(L"X�L�[�ŕ���", 570, 120,28, c);


	//�m�[�_���[�W�N���A
	if (g_Taurus_NoDamage_Clear == true)
	{
		Font::StrDraw(L"�������F�m�[�_���[�W�N���A�I", 75, 190, 28, y);

	}
	else
	{
		Font::StrDraw(L"�������F���B��", 75, 190, 28, c);
	}
	if (g_Libra_NoDamage_Clear == true)
	{
		Font::StrDraw(L"�V�����F�m�[�_���[�W�N���A�I", 75, 225, 28, y);

	}
	else
	{
		Font::StrDraw(L"�V�����F���B��", 75, 225, 28, c);

	}
	if (g_Gemini_NoDamage_Clear == true)
	{
		Font::StrDraw(L"�o�q���F�m�[�_���[�W�N���A�I", 75, 260, 28, y);

	}
	else
	{
		Font::StrDraw(L"�o�q���F���B��", 75, 260, 28, c);

	}
	 if (g_Viego_NoDamage_Clear == true)
	{
		Font::StrDraw(L"�������F�m�[�_���[�W�N���A�I", 75, 295, 28, y);
	}
	else
	{
		Font::StrDraw(L"�������F���B��", 75, 295, 28, c);

	}
	if (g_Leo_NoDamage_Clear == true)
	{
		Font::StrDraw(L"���q���F�m�[�_���[�W�N���A�I", 75, 330, 28, y);
	}
	else
	{
		Font::StrDraw(L"���q���F���B��", 75, 330, 28, c);

	}


}
