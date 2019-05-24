//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"

#include "GameHead.h"
#include "ObjSkill.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;
/*
		 �X�L�����Ƃ̒l 
	NoSkill,	//�X�L������	0
	Taurus,		//������		1
	Libra,		//�V����		2
	Gemini,		//�o�q��		3
	Virgo,		//������		4
	Leo,		//���q��		5

		�e�����̎擾���
	g_Taurus;	//������	
	g_Libra;	//�V����
	g_Gemini;	//�o�q��
	g_Virgo;	//������
	g_Leo;		//���q��

*/

//�C�j�V�����C�Y
void CObjSkill::Init()
{
	m_memory = g_skill;	//�X�L����r�ϐ��̏�����
	m_next = 0;	//�X�L���摜�p�ϐ��̏�����
	m_back = 0;	//�X�L���摜�p�ϐ��̏�����

	m_right_f = false;
	m_left_f = false;

}

//�A�N�V����
void CObjSkill::Action()
{
	//�X�L�����擾���Ă��邩�ǂ����̊m�F�i�擾���Ă��Ȃ��A�l������A�����ꍇ�j
	
	//�X�L���̒l���������ꍇ
	if (g_skill < m_memory) {
		//�����̑O��NoSkill��������Ă���ꍇ������̂ŁA��ɏ���
		if (g_skill < NoSkill)	//�X�L���̒l��NoSkill����������ꍇ
			g_skill = Leo;		//���q���ɕύX	
		if (g_Taurus == false && g_skill == Taurus)//���������擾���Ă��Ȃ��ꍇ
			g_skill--;	//���̉摜�ֈڂ�
		if (g_Libra == false && g_skill == Libra)	//�V�������擾���Ă��Ȃ��ꍇ
			g_skill--;	//���̉摜�ֈڂ�
		if (g_Gemini == false && g_skill == Gemini)//�o�q�����擾���Ă��Ȃ��ꍇ
			g_skill--;	//���̉摜�ֈڂ�
		if (g_Virgo == false && g_skill == Virgo)	//���������擾���Ă��Ȃ��ꍇ
			g_skill--;	//���̉摜�ֈڂ�
		if (g_Leo == false && g_skill == Leo)		//���q�����擾���Ă��Ȃ��ꍇ
			g_skill--;	//���̉摜�ֈڂ�
	}
	
	//�X�L���̒l���������ꍇ
	if (g_skill > m_memory) {
		if (g_Taurus == false && g_skill == Taurus)//���������擾���Ă��Ȃ��ꍇ
			g_skill++;	//���̉摜�ֈڂ�
		if (g_Libra == false && g_skill == Libra)	//�V�������擾���Ă��Ȃ��ꍇ
			g_skill++;	//���̉摜�ֈڂ�
		if (g_Gemini == false && g_skill == Gemini)//�o�q�����擾���Ă��Ȃ��ꍇ
			g_skill++;	//���̉摜�ֈڂ�
		if (g_Virgo == false && g_skill == Virgo)	//���������擾���Ă��Ȃ��ꍇ
			g_skill++;	//���̉摜�ֈڂ�
		if (g_Leo == false && g_skill == Leo)		//���q�����擾���Ă��Ȃ��ꍇ
			g_skill++;	//���̉摜�ֈڂ�
		//�����̌��Leo�������Ă���ꍇ������̂ŁA��ɏ���
		if (g_skill > Leo)	//�X�L���̒l��Leo���������ꍇ
			g_skill = NoSkill;	//NoSkill�ɖ߂�
	}
	
	//�ς�����X�L���̒l���A��r�p�������ɕۑ����Ă���
	m_memory = g_skill;

	//�摜�̑O��`��p
	if (g_skill == NoSkill) {
		if (g_Leo == true)
			m_left_f = true;
		else
			m_left_f = false;
		if (g_Taurus == true)
			m_right_f = true;
		else
			m_right_f = false;
	}
	if (g_skill == Taurus) {
		m_left_f = true;
		if (g_Libra == true)
			m_right_f = true;
		else
			m_right_f = false;
	}
	if (g_skill == Libra) {
		if (g_Taurus == true)
			m_left_f = true;
		else
			m_left_f = false;
		if (g_Gemini == true)
			m_right_f = true;
		else
			m_right_f = false;
	}
	if (g_skill == Gemini) {
		if (g_Libra == true)
			m_left_f = true;
		else
			m_left_f = false;
		if (g_Virgo == true)
			m_right_f = true;
		else
			m_right_f = false;
	}
	if (g_skill == Virgo) {
		if (g_Gemini == true)
			m_left_f = true;
		else
			m_left_f = false;
		if (g_Leo == true)
			m_right_f = true;
		else
			m_right_f = false;
	}
	if (g_skill == Leo) {
		if (g_Virgo == true)
			m_left_f = true;
		else
			m_left_f = false;
		m_next = true;
	}

	
}

//�h���[
void CObjSkill::Draw()
{
	//�N���A�I�u�W�F�N�g���쐬����Ă���ہA�`��̒�~
	if (g_stage_clear == false)
	{
		//�`��J���[���
		float c[4] = { 1.0f,1.0f,1.0f,1.0f };
		float b[4] = { 0.0f,0.0f,0.0f,1.0f };

		float s[4] = { 1.0f,1.0f,1.0f,0.5f };
		RECT_F src;	//�`�挳�؂���ʒu
		RECT_F dst;	//�`���\���ʒu
		
		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f + (300.0f * g_skill);		//�X�L���̒l���ς��Ύ��̉摜�ֈڍs
		src.m_right = 300.0f + (300.0f * g_skill);
		src.m_bottom = 200.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top = 450.0f;
		dst.m_left = 550.0f;
		dst.m_right = 750.0f;
		dst.m_bottom = 600.0f;
		Draw::Draw(13, &src, &dst, c, 0.0f);

		//���ɂ���X�L����\��
		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 1500.0f + (300.0f * (g_skill));		//�X�L���̒l���ς��Ύ��̉摜�ֈڍs
		src.m_right = 1800.0f + (300.0f * (g_skill));
		src.m_bottom = 200.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top = 550.0f;
		dst.m_left = 500.0f;
		dst.m_right = 580.0f;
		dst.m_bottom = 600.0f; 
		if(m_left_f == true)
			Draw::Draw(13, &src, &dst, s, 0.0f);
		else
			Draw::Draw(13, &src, &dst, b, 0.0f);
	
		//�O�ɂ���X�L����\��
		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 300.0f + (300.0f * (g_skill));		//�X�L���̒l���ς��Ύ��̉摜�ֈڍs
		src.m_right = 600.0f + (300.0f * (g_skill));
		src.m_bottom = 200.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top = 550.0f;
		dst.m_left = 720.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 600.0f;
		if (m_right_f == true)
			Draw::Draw(13, &src, &dst, s, 0.0f);
		else
			Draw::Draw(13, &src, &dst, b, 0.0f);

	}
}