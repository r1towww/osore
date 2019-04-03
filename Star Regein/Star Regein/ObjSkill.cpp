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
	Taurus,		//������	0
	Libra,		//�V����	1
	Gemini,		//�o�q��	2
	Virgo,		//������	3
	Leo,		//���q��	4
*/

CObjSkill::CObjSkill()
{

}

//�C�j�V�����C�Y
void CObjSkill::Init()
{

}

//�A�N�V����
void CObjSkill::Action()
{
	//�X�L���̒l�����q���𒴂�����
	if (g_skill > Leo)
	{
		g_skill = Taurus;	//�������ɖ߂�
	}
}

//�h���[
void CObjSkill::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top    = 0.0f;
	src.m_left   = 0.0f   + (256.0f * g_skill);		//�X�L���̒l���ς��Ύ��̉摜�ֈڍs
	src.m_right  = 256.0f + (256.0f * g_skill);
	src.m_bottom = 256.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top    = 400.0f;
	dst.m_left   = 600.0f;
	dst.m_right  = 800.0f;
	dst.m_bottom = 600.0f;

	//�`��
	Draw::Draw(13, &src, &dst, c, 0.0f);
}