//�g�p����w�b�_�[
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\SceneManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjTitle.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjED::Init()
{
	m_ani_time = 0;
	m_ani_frame = 0;
	m_ani_max_time = 3;		//�A�j���[�V�����Ԋu��
	m_key = 0;
	//�L�[�t���O�̏�����
	m_key_f = false;
	flag = false;
	m_f = true;		//�I�u�W�F�N�g�쐬�p�t���O

	//�Q�T�ڌn��
	g_End_flag = false;
	g_Voice_flag = false;
	g_count = 0;
	g_last_key_f = false;	//�Q�T�ڂ̎�l�����������p

}

//�A�N�V����
void CObjED::Action()
{

	float p[4] = { 1.0f,0.0f,0.0f,1.0f };
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	//�t�H���g�`��-------------------------------------------
	if (m_key == 0)
	{
		Font::StrDraw(L"END GAME", GAME_CLEAR_X - 20, GAME_CLEAR_Y + 110, GAME_CLEAR_FONT_SIZE + 70, p);
	}
	if (m_key == 1)
	{
		Font::StrDraw(L"�Q�[����", GAME_CLEAR_X - 10, GAME_CLEAR_Y - 10, GAME_CLEAR_FONT_SIZE + 60, c);
		Font::StrDraw(L"STAR REGEIN", GAME_CLEAR_X - 75, GAME_CLEAR_Y + 200, GAME_CLEAR_FONT_SIZE + 60, c);
	}
	if (m_key == 2)
	{
		Font::StrDraw(L"���y��", GAME_CLEAR_X -10, GAME_CLEAR_Y -10, GAME_CLEAR_FONT_SIZE + 60, c);
		Font::StrDraw(L"�������l", GAME_CLEAR_X -10, GAME_CLEAR_Y + 200, GAME_CLEAR_FONT_SIZE + 60, c);
	}
	if (m_key == 3)
	{
		Font::StrDraw(L"�v���C���Ē���", GAME_CLEAR_X - 45, GAME_CLEAR_Y +70, GAME_CLEAR_FONT_SIZE + 30, c);
		Font::StrDraw(L"���肪�Ƃ��������܂���", GAME_CLEAR_X - 160, GAME_CLEAR_Y + 180, GAME_CLEAR_FONT_SIZE + 30, c);
	}
	//-----------------------------------------------------------

	//Enter�������ꂽ��t���O�I��
	if (Input::GetVKey('Z') && m_key_f == false ||Input::GetVKey(VK_RETURN) == true && m_key_f == false)
	{
		m_key_f = true;
	}
	//---------------------------

	//�A�j���[�V�����\��----
	if (m_key_f == true && flag==false)
	{
		m_ani_time += 1;

		if (m_ani_time > m_ani_max_time)
		{
			m_ani_frame += 1;
			m_ani_time = 0;
		}
		if (m_ani_frame == 10)
		{
			flag = true;
			m_key += 1;
		}
	}
	if (flag == true)
	{
		m_ani_time += 1;

		if (m_ani_time > m_ani_max_time)
		{
			m_ani_frame -= 1;
			m_ani_time = 0;
		}
		if (m_ani_frame == 0)
		{
			m_key_f = false;
			flag = false;
		}
	}
	//------------------------

	if (m_key == 4 && m_f == true)
	{
		//�I�u�W�F�N�g�쐬
		CObjStageClear* objs = new CObjStageClear();	//���т̕\��
		Objs::InsertObj(objs, OBJ_STAGECLEAR, 130);
		m_f = false;
	}

}

//�h���[
void CObjED::Draw()
{
	float bc[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;		//�`�挳�؂���ʒu
	RECT_F dst;		//�`���\���ʒu

					//�w�i�؂���
	src.m_top = 0.0f;
	src.m_left = 0.0f + (800.0f * m_ani_frame);
	src.m_right = 800.0f + (800.0f * m_ani_frame);
	src.m_bottom = 600.0f;

	//�`��
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;
	Draw::Draw(1, &src, &dst, bc, 0.0f);
}
