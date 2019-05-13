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

}

//�A�N�V����
void CObjSkill::Action()
{
	//�X�L���̒l��0����������ꍇ
	if (g_skill < NoSkill) {
		g_skill = Leo;
		if (g_Taurus == false && g_skill == Taurus)//���������擾���Ă��Ȃ��ꍇ
			g_skill--;	//���̉摜�ֈڂ�
		else if (g_Libra == false && g_skill == Libra)	//�V�������擾���Ă��Ȃ��ꍇ
			g_skill--;	//���̉摜�ֈڂ�
		else if (g_Gemini == false && g_skill == Gemini)//�o�q�����擾���Ă��Ȃ��ꍇ
			g_skill--;	//���̉摜�ֈڂ�
		else if (g_Virgo == false && g_skill == Virgo)	//���������擾���Ă��Ȃ��ꍇ
			g_skill--;	//���̉摜�ֈڂ�
		else if (g_Leo == false && g_skill == Leo)		//���q�����擾���Ă��Ȃ��ꍇ
			g_skill--;	//���̉摜�ֈڂ�
	}
	//�X�L���̒l��5���������ꍇ
	else if (g_skill > Leo) {	
		g_skill = NoSkill;	//NoSkill�ɖ߂�
		if (g_Taurus == false && g_skill == Taurus)//���������擾���Ă��Ȃ��ꍇ
			g_skill++;	//���̉摜�ֈڂ�
		else if (g_Libra == false && g_skill == Libra)	//�V�������擾���Ă��Ȃ��ꍇ
			g_skill++;	//���̉摜�ֈڂ�
		else if (g_Gemini == false && g_skill == Gemini)//�o�q�����擾���Ă��Ȃ��ꍇ
			g_skill++;	//���̉摜�ֈڂ�
		else if (g_Virgo == false && g_skill == Virgo)	//���������擾���Ă��Ȃ��ꍇ
			g_skill++;	//���̉摜�ֈڂ�
		else if (g_Leo == false && g_skill == Leo)		//���q�����擾���Ă��Ȃ��ꍇ
			g_skill++;	//���̉摜�ֈڂ�
	}
	




}

//�h���[
void CObjSkill::Draw()
{
	if (g_stage_clear == false)
	{
		if (g_Taurus == false)
			return;

		//�`��J���[���
		float c[4] = { 1.0f,1.0f,1.0f,1.0f };
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
		src.m_left = 1500.0f + (300.0f * g_skill);		//�X�L���̒l���ς��Ύ��̉摜�ֈڍs
		src.m_right = 1800.0f + (300.0f * g_skill);
		src.m_bottom = 200.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top = 550.0f;
		dst.m_left = 500.0f;
		dst.m_right = 580.0f;
		dst.m_bottom = 600.0f; 
		Draw::Draw(13, &src, &dst, s, 0.0f);

		//�O�ɂ���X�L����\��
		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 300.0f + (300.0f * g_skill);		//�X�L���̒l���ς��Ύ��̉摜�ֈڍs
		src.m_right = 600.0f + (300.0f * g_skill);
		src.m_bottom = 200.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top = 550.0f;
		dst.m_left = 720.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 600.0f;
		Draw::Draw(13, &src, &dst, s, 0.0f);

		////�`��
		//if (g_skill == NoSkill)
		//{

		//}
		//else {
		//	Draw::Draw(13, &src, &dst, c, 0.0f);
		//}

	}
}