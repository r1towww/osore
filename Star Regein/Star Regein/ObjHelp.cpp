//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"
#include "GameHead.h"

#include "ObjHelp.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjHelp::Init()
{
}

//�A�N�V����
void CObjHelp::Action()
{





	//H�L�[���b���ꂽ�ꍇ
	if (Input::GetVKey('H') == false)
	{
		this->SetStatus(false);
	}



}

//�h���[
void CObjHelp::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };	//���b�Z�[�W�t�H���g�J���[
	float a[4] = { 1.0f,1.0f,1.0f,0.5f };	

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

//�w�i�p�摜-----------------------------------
	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 822.0f;
	src.m_bottom = 218.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top    = 100.0f;
	dst.m_left   = 50.0f;
	dst.m_right  = 750.0f;
	dst.m_bottom = 500.0f;
	//�\��
	Draw::Draw(40, &src, &dst, a, 0.0f);
//----------------------------------------------

//��������p���b�Z�[�W--------------------------

	//�����p�̃��b�Z�[�W�̕\��
	Font::StrDraw(L"Z�L�[ �O���Ɍ��ōU��", 75, 120, 27, c);	
	Font::StrDraw(L"X�L�[ �I�𒆂̃X�L������", 75, 155, 27, c);
	Font::StrDraw(L"C�L�[ �X�L���̐؂�ւ�", 75, 190, 27, c);
	Font::StrDraw(L"M�L�[ �}�b�v�̕\��", 75, 225, 27, c);



//----------------------------------------------
	//�؂���ʒu�̐ݒ�
	src.m_top    = 0.0f;
	src.m_left   = 0.0f + (g_skill * 300.0f);
	src.m_right  = 300.0f + (g_skill * 300.0f);
	src.m_bottom = 200.0f;
	//�I�𒆂̃X�L���ɂ���Đ�������ύX
	if (g_skill == Taurus)	//������
	{
		//������
		Font::StrDraw(L"*�������X�L��*    MP���� 1�Q�[�W", 310, 320, 25, c);
		Font::StrDraw(L"Shift�L�[�������Ȃ���ړ�����ƁA", 315, 350, 25, c);
		Font::StrDraw(L"�_�b�V�����\�I�I", 315, 380, 25, c);
		Font::StrDraw(L"�u�_�b�V���I�_�b�V���I�_�b�V���I�v", 315, 410, 25, c);
	}
	else if (g_skill == Libra)	//�V����
	{
		//������
		Font::StrDraw(L"*�V�����X�L��*  HP�����ɂ���Ĕ���", 310, 320, 25, c);
		Font::StrDraw(L"HP������ƍU����UP�I�I", 315, 350, 25, c);
		Font::StrDraw(L"�����I�Ɍ��ʂ͔�������邼�I", 315, 380, 25, c);
		Font::StrDraw(L"�u�����̖��͑�؂ɁB�v", 315, 410, 25, c);

	}
	else if (g_skill == Gemini)	//�o�q��
	{
		//������
		Font::StrDraw(L"*�o�q���X�L��*    MP���� 10�Q�[�W", 310, 320, 25, c);
		Font::StrDraw(L"���ɐ키�T�u�@�������I�I", 315, 350, 25, c);
		Font::StrDraw(L"�ő�1�̂܂ł��������ł��Ȃ����I", 315, 380, 25, c);
		Font::StrDraw(L"�u���Ԃ͑厖����B�v", 315, 410, 25, c);

	}
	else if (g_skill == Virgo)	//������
	{
		//������
		Font::StrDraw(L"*�������X�L��*    MP���� 5�Q�[�W", 310, 320, 25, c);
		Font::StrDraw(L"HP���z������n�[�g�e�𔭎ˁI", 315, 350, 25, c);
		Font::StrDraw(L"�����Ă�������ɔ��ł������I", 315, 380, 25, c);
		Font::StrDraw(L"�u���������Ă��炤��...�v", 315, 410, 25, c);

	}
	else if (g_skill == Leo)	//���q��
	{
		//������
		Font::StrDraw(L"*���q���X�L��*    MP���� 1�Q�[�W", 310, 320, 25, c);
		Font::StrDraw(L"", 315, 350, 25, c);
		Font::StrDraw(L"", 315, 380, 25, c);
		Font::StrDraw(L"", 315, 410, 25, c);

	}
	//�\���ʒu�̐ݒ�
	dst.m_top    = 290.0f;
	dst.m_left   = 80.0f;
	dst.m_right  = 280.0f;
	dst.m_bottom = 490.0f;
	//�\��
	Draw::Draw(13, &src, &dst, c, 0.0f);

	if (g_Taurus == true)
	{
		//�؂���ʒu�̐ݒ�
		src.m_top    = 0.0f;
		src.m_left   = 300.0f;
		src.m_right  = 600.0f;
		src.m_bottom = 200.0f;
		//�\���ʒu�̐ݒ�
		dst.m_top    = 150.0f;
		dst.m_left   = 420.0f;
		dst.m_right  = 480.0f;
		dst.m_bottom = 210.0f;
		//�\��
		Draw::Draw(13, &src, &dst, c, 0.0f);
	}
	if (g_Libra == true)
	{
		//�؂���ʒu�̐ݒ�
		src.m_top    = 0.0f;
		src.m_left   = 600.0f;
		src.m_right  = 900.0f;
		src.m_bottom = 200.0f;
		//�\���ʒu�̐ݒ�
		dst.m_top    = 150.0f;
		dst.m_left   = 490.0f;
		dst.m_right  = 540.0f;
		dst.m_bottom = 210.0f;
		//�\��
		Draw::Draw(13, &src, &dst, c, 0.0f);
	}
	if (g_Gemini == true)
	{
		//�؂���ʒu�̐ݒ�
		src.m_top    = 0.0f;
		src.m_left   = 900.0f;
		src.m_right  = 1200.0f;
		src.m_bottom = 200.0f;
		//�\���ʒu�̐ݒ�
		dst.m_top    = 150.0f;
		dst.m_left   = 550.0f;
		dst.m_right  = 600.0f;
		dst.m_bottom = 210.0f;
		//�\��
		Draw::Draw(13, &src, &dst, c, 0.0f);
	}
	if (g_Virgo == true)
	{
		//�؂���ʒu�̐ݒ�
		src.m_top    = 0.0f;
		src.m_left   = 1200.0f;
		src.m_right  = 1500.0f;
		src.m_bottom = 200.0f;
		//�\���ʒu�̐ݒ�
		dst.m_top    = 150.0f;
		dst.m_left   = 610.0f;
		dst.m_right  = 660.0f;
		dst.m_bottom = 210.0f;
		//�\��
		Draw::Draw(13, &src, &dst, c, 0.0f);
	}
	if (g_Leo == true)
	{
		//�؂���ʒu�̐ݒ�
		src.m_top    = 0.0f;
		src.m_left   = 1500.0f;
		src.m_right  = 1800.0f;
		src.m_bottom = 200.0f;
		//�\���ʒu�̐ݒ�
		dst.m_top    = 150.0f;
		dst.m_left   = 670.0f;
		dst.m_right  = 720.0f;
		dst.m_bottom = 210.0f;
		//�\��
		Draw::Draw(13, &src, &dst, c, 0.0f);
	}
	

}
