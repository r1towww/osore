//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"
#include "GameHead.h"

#include "ObjMenu.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjMenu::Init()
{
	m_key = 0;
	m_key_f = false;
}

//�A�N�V����
void CObjMenu::Action()
{
	//�L�[����x�����Ȃ��Ɠ��͂��󂯕t���Ȃ�
	if (Input::GetVKey('Q') == false)
	{
		m_key_f = true;
	}
	//Q�L�[���ēx�����ꂽ�ꍇ
	if (Input::GetVKey('Q') == true && m_key_f == true)
	{
		g_move_stop_flag = false;	//�X�g�b�v�t���O���I�t
		this->SetStatus(false);		//�I�u�W�F�N�g���폜
	}

	if (Input::GetVKey(VK_RIGHT))//���L�[�i�E�j�����͂��ꂽ�Ƃ�
	{
		m_key = 0;	//�O�Ԃ��Z�b�g
	}
	else if (Input::GetVKey(VK_LEFT))//���L�[�i���j�����͂��ꂽ�Ƃ�
	{
		m_key = 1;	//�P�Ԃ��Z�b�g
	}


	//Z�L�[�������ꂽ�ꍇ
	if (Input::GetVKey('Z') == true)
	{
		//�O�Ԃ̏ꍇ
		if (m_key == 0)
		{
			g_move_stop_flag = false;	//�X�g�b�v�t���O���I�t
			this->SetStatus(false);		//�I�u�W�F�N�g���폜
		}
		//�P�Ԃ̏ꍇ
		else if (m_key == 1)
		{
			g_move_stop_flag = false;	//�X�g�b�v�t���O���I�t
			Scene::SetScene(new CSceneStageChoice());	//�X�e�[�W�I���֖߂�
		}
	}



}

//�h���[
void CObjMenu::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };	//���b�Z�[�W�t�H���g�J���[
	float backc[4] = { 1.0f,1.0f,0.0f,1.0f };	
	float a[4] = { 1.0f,1.0f,1.0f,0.5f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

//�w�i�p�摜-----------------------------------
	//�؂���ʒu�̐ݒ�
	src.m_top    = 0.0f;
	src.m_left   = 0.0f;
	src.m_right  = 822.0f;
	src.m_bottom = 218.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top    = 100.0f;
	dst.m_left   = 50.0f;
	dst.m_right  = 750.0f;
	dst.m_bottom = 500.0f;
	//�\��
	Draw::Draw(40, &src, &dst, backc, 0.0f);
//----------------------------------------------

//�����`��p------------------------------------
	
	Font::StrDraw(L"�X�e�[�W�I���֖߂�", 110, 250, 32, c);
	Font::StrDraw(L"�Q�[���֖߂�", 470, 250, 32, c);

	//�ԍ��ɂ���đI����ύX
	if (m_key == 0)
		Font::StrDraw(L"��", 440, 250, 32, c);
	else if (m_key == 1)
		Font::StrDraw(L"��", 80, 250, 32, c);

//----------------------------------------------


}