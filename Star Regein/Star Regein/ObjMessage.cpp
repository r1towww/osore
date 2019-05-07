//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"
#include "GameHead.h"

#include "ObjMessage.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjMessage::Init()
{
	m_memory = 0;	//���̐����v��ϐ��̏�����
	m_time = 0;		//���b�Z�[�W���ԗp�̕ϐ��̏�����
	//���̍ő�̐��̏������i�������W�߂�ꏊ�ɂ���ĕω��j
	if (g_stage == EarthStar)
		m_MaxStar = EARTHMAXSTAR;	//�n��
	else if (g_stage == VenusTaurus)
		m_MaxStar = TAURUSMAXSTAR;	//�����i�������j
	else if (g_stage == VenusLibra)
		m_MaxStar = LIBRAMAXSTAR;	//�����i�V�����j
	else if (g_stage == MercuryGemini)
		m_MaxStar = GEMINIMAXSTAR;	//�����i�o�q���j
	else if (g_stage == MercuryVirgo)
		m_MaxStar = VIRGOMAXSTAR;	//�����i�������j
	else if (g_stage == SunLeo)
		m_MaxStar = LEOMAXSTAR;		//���z�i���q���j

}

//�A�N�V����
void CObjMessage::Action()
{
	
}

//�h���[
void CObjMessage::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };	//���b�Z�[�W�t�H���g�J���[

	float sc[4] = { 1.0f,1.0f,0.4f,1.0f };
	float b[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	wchar_t STARMES[128];	//���̐��𐔂��郁�b�Z�[�W�p
	wchar_t STAR[128];	//���̐�����ɕ\������

	swprintf_s(STAR, L"%d/%d", g_StarCount, m_MaxStar);
	Font::StrDraw(STAR, 400, 20, 25, sc);//���b�Z�[�W��\��

	Font::StrDraw(L"Q:���j���[", 465, 12, 21, c);	//HP
	Font::StrDraw(L"H:�w���v", 465, 33, 21, c);	//MP


	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 232.0f;
	src.m_bottom = 203.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 16.0f;
	dst.m_left = 365.0f;
	dst.m_right = 395.0f;
	dst.m_bottom = 46.0f;

		//�`��
		Draw::Draw(6, &src, &dst, c, 0.0f);
	
	//���̃J�E���g���������ꍇ
	if (g_StarCount > m_memory)
	{
		m_time++;	//time���v���X���Ă��鎞�������b�Z�[�W��\��
		swprintf_s(STARMES, L"%d�ڂ́����擾�A�c��%d�I", g_StarCount, m_MaxStar - g_StarCount);
		Font::StrDraw(STARMES, 150, 240, 25, sc);//���b�Z�[�W��\��
		if (m_time == 100) {
			m_memory = g_StarCount;	//���݂̐��̐�����
			m_time = 0;	//time�̏�����
		}
	}


}
