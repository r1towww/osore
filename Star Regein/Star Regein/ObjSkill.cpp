//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"

#include "GameHead.h"
#include "ObjSkill.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

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
	src.m_left   = 0.0f   + g_image_reft ;
	src.m_right  = 900.0f + g_image_right;
	src.m_bottom = 600.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top    = 400.0f;
	dst.m_left   = 600.0f;
	dst.m_right  = 800.0f;
	dst.m_bottom = 600.0f;

	//�`��
	Draw::Draw(12, &src, &dst, c, 0.0f);
}