//�g�p����w�b�_�[
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\SceneManager.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "ObjWorning.h"

//----------------------------------
//�g�p����l�[���X�y�[�X
using namespace GameL;


//�C�j�V�����C�Y
void CObjWorning::Init()
{
	m_count = 0;
	m_worning_alpha = 0.0f;
	m_worning_time = 0;
	m_switch = false;
}

//�A�N�V����
void CObjWorning::Action()
{
	m_worning_time++;

	if (m_worning_alpha >= 1.0f)
	{
		m_worning_alpha = 1.0f;
		m_switch = true;
	}
	if(m_switch == false )
	{
		m_worning_alpha += 0.03f;
	}

	if (m_worning_alpha <= 0.0f)
	{
		m_worning_alpha = 0.0f;
		m_switch = false;
		m_count++;
	}
	if(m_switch == true)
	{
		m_worning_alpha -= 0.03f;
	}

	if (m_count == 3)
	{
		this->SetStatus(false);		//�폜
		Audio::Start(3);
		g_tutorial_flag = true;
		//�`���[�g���A�������o���쐬
		CObjTutorial* objtutorialhukidashi = new CObjTutorial(0, 2);
		Objs::InsertObj(objtutorialhukidashi, OBJ_TUTORIAL, 151);
		//�`���[�g���A���I�u�W�F�N�g�쐬
		CObjTutorial* objtutorial = new CObjTutorial(1, 2);
		Objs::InsertObj(objtutorial, OBJ_TUTORIAL, 170);
		//�e�L�X�g�{�b�N�X�I�u�W�F�N�g�쐬
		CObjTextBox* objtextbox = new CObjTextBox();
		Objs::InsertObj(objtextbox, OBJ_TEXTBOX, 160);
	}
}

//�h���[
void CObjWorning::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,m_worning_alpha };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	//WORNING!!�ѕ\��
	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 10.0f + m_worning_time;
	src.m_right = 810.0f + m_worning_time;
	src.m_bottom = 500.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 50.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 550.0f;
	//�\��
	Draw::Draw(50, &src, &dst, c, 0.0f);

	//�}�[�N�\��
	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1400.0f;
	src.m_bottom = 1103.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 200.0f;
	dst.m_left = 280.0f;
	dst.m_right = 534.0f;
	dst.m_bottom = 420.0f;

	//�\��
	Draw::Draw(51, &src, &dst, c, 0.0f);

}
