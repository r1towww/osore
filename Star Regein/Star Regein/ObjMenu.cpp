//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"
#include "GameHead.h"
#include "GameL/Audio.h"

#include "ObjMenu.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjMenu::Init()
{
	//�I���L�[��0�i�E�j�ŏ�����
	m_key = 0;
	//�L�[�t���O�̏�����
	m_key_f = false;
	m_choice_key_f = false;	
	m_Tra = 0.0f;
	m_f = false;
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
		Audio::Start(1);	//�G�t�F�N�g����炷
		g_move_stop_flag = false;	//�X�g�b�v�t���O���I�t
		this->SetStatus(false);		//�I�u�W�F�N�g���폜
	}

	if (Input::GetVKey(VK_RIGHT) && m_choice_key_f == true)//�L�[�t���O���I���̏�ԂŁA���L�[�i�E�j�����͂��ꂽ�Ƃ�
	{
		Audio::Start(1);	//�G�t�F�N�g����炷
		m_key = 0;	//�O�Ԃ��Z�b�g
		m_choice_key_f = false;	//�t���O���I��
	}
	else if (Input::GetVKey(VK_LEFT) && m_choice_key_f == false)//�L�[�t���O���I�t�̏�ԂŁA���L�[�i���j�����͂��ꂽ�Ƃ�
	{
		Audio::Start(1);	//�G�t�F�N�g����炷
		m_key = 1;	//�P�Ԃ��Z�b�g
		m_choice_key_f = true;	//�t���O���I��
	}


	//Z�L�[�������ꂽ�ꍇ
	if (Input::GetVKey('Z') == true || Input::GetVKey(VK_RETURN) == true)
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
			m_push_flag = true;

			
		}
		g_key_flag = false;
	}

	if (m_push_flag == true)
	{
		if (m_f == false)
		{
			Audio::Start(2);	//�G�t�F�N�g����炷
			m_f = true;
		}
		
		
		m_Tra += 0.03;
		if (m_Tra >= 1)
		{
			if (g_stage == Space)
			{
				Scene::SetScene(new CSceneTitle());	//�^�C�g���I���֖߂�

			}
			else
			{
				this->SetStatus(false);		//�I�u�W�F�N�g���폜

				g_stage = Space;
				Scene::SetScene(new CSceneStageChoice());	//�X�e�[�W�I���֖߂�

			}
		}
	}

}

//�h���[
void CObjMenu::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };	//���b�Z�[�W�t�H���g�J���[
	float backc[4] = { 1.0f,1.0f,0.0f,1.0f };	
	float a[4] = { 1.0f,1.0f,1.0f,0.5f };
	float c2[4] = { 1.0f,1.0f,1.0f,m_Tra };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

//�w�i�p�摜-----------------------------------

	//�V�[���؂�ւ��p
	if (m_push_flag == true)
	{

		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 350.0f;
		src.m_right = 400.0f;
		src.m_bottom = 50.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 600.0f;

		Draw::Draw(9, &src, &dst, c2, 0.0f);
	}
	
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
	if (g_stage == Space)
	{
		Font::StrDraw(L"�^�C�g���֖߂�", 110, 250, 32, c);
		Font::StrDraw(L"�Q�[���֖߂�", 470, 250, 32, c);
	}
	else
	{
		Font::StrDraw(L"�X�e�[�W�I���֖߂�", 110, 250, 32, c);
		Font::StrDraw(L"�Q�[���֖߂�", 470, 250, 32, c);
	}
	//�ԍ��ɂ���đI����ύX
	if (m_key == 0)
		Font::StrDraw(L"��", 440, 250, 32, c);
	else if (m_key == 1)
		Font::StrDraw(L"��", 80, 250, 32, c);

//----------------------------------------------


}
