//�g�p����w�b�_�[
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\SceneManager.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "ObjStarChoice.h"



//�g�p����l�[���X�y�[�X
using namespace GameL;


//�C�j�V�����C�Y
void CObjStarChoice::Init()
{
	m_oushi = false;
	m_tenbin = false;
	m_Tra1 = 0.5f;
	m_Tra2 = 0.5f;
}

//�A�N�V����
void CObjStarChoice::Action()
{

}

//�h���[
void CObjStarChoice::Draw()
{
	//�`��J���[���
	float o[4] = { 1.0f,1.0f,1.0f,m_Tra1 };
	float t[4] = { 1.0f,1.0f,1.0f,m_Tra2 };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu
	//���������̉摜-----------------------------------------------------------------
	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 870.0f;
	src.m_bottom = 600.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 150.0f;
	dst.m_left = 100.0f;
	dst.m_right = 350.0f;
	dst.m_bottom = 400.0f;
	//�\��
	Draw::Draw(1, &src, &dst, o, 0.0f);
	//-------------------------------------------------------------------------------
	//�Ă�т��---------------------------------------------------------------------
	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 900.0f;
	src.m_bottom = 600.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 150.0f;
	dst.m_left = 430.0f;
	dst.m_right = 680.0f;
	dst.m_bottom = 400.0f;
	//�\��
	Draw::Draw(2, &src, &dst, t, 0.0f);
	//----------------------------------------------------------------------------------

	//�E�L�[�����đI��
	if (Input::GetVKey(VK_RIGHT) == true)
	{
		m_oushi = true;
		m_tenbin = false;
	}
	//���L�[�����đI��
	else if (Input::GetVKey(VK_LEFT) == true)
	{
		m_tenbin = true;
		m_oushi = false;
	}

	//���������̂ق��𖾂邭���ĂĂ�т�����Â�����
	if (m_oushi == true)
	{
		m_Tra2 = 1.0f;
		m_Tra1 = 0.5f;
		if (Input::GetVKey('Z') == true)
		{
			//�X�e�[�W�����������ɐݒ�
			g_stage = VenusTaurus;
			Scene::SetScene(new CSceneVenus());
			
		}

	}
	//�Ă�т���̂ق��𖾂邭���Ă����������Â�����
	else if (m_tenbin == true)
	{
		m_Tra1 = 1.0f;
		m_Tra2 = 0.5f;
		if (Input::GetVKey('Z') == true)
		{
			//�X�e�[�W���Ă�т���ɐݒ�
			g_stage = VenusLibra;
			Scene::SetScene(new CSceneEarth());
		}

	}

}
