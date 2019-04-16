//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"

#include "GameHead.h"
#include "ObjStatus.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

float g_hp;
float g_max_hp;
float g_mp;
float g_max_mp;

CObjStatus::CObjStatus()
{

}

//�C�j�V�����C�Y
void CObjStatus::Init()
{

}

//�A�N�V����
void CObjStatus::Action()
{


}

//�h���[
void CObjStatus::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu

//HP,MP�̔w�i�p--------------------------------

	//�؂���ʒu�̐ݒ�iHP�j
	src.m_top    = 0.0f;
	src.m_left   = 0.0f;
	src.m_right  = 40.0f;
	src.m_bottom = 50.0f;

	//�\���ʒu�̐ݒ�iHP�j
	dst.m_top    = 23.0f;
	dst.m_left   = 0.0f;
	dst.m_right  = 136.0f;
	dst.m_bottom = 53.0f;

	//�`��iHP�j
	Draw::Draw(9, &src, &dst, c, 0.0f);

	//�\���ʒu�̐ݒ�iMP�j
	dst.m_top    = 77.0f;
	dst.m_left   = 0.0f;
	dst.m_right  = 136.0f;
	dst.m_bottom = 108.0f;

	//�`��iMP�j
	Draw::Draw(9, &src, &dst, c, 0.0f);

//----------------------------------------------


//HP�`��p--------------------------------------
	//�؂���ʒu�̐ݒ�
	src.m_top    = 0.0f;
	src.m_left   = 0.0f;
	src.m_right  = 600.0f;
	src.m_bottom = 300.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top    = 26.0f;
	dst.m_left   = 4.0f;
	dst.m_right  = (g_hp / g_max_hp)*132.0f;
	dst.m_bottom = 50.0f;

	//�`��
	Draw::Draw(10, &src, &dst, c, 0.0f);
//----------------------------------------------

//MP�`��p--------------------------------------
	//�؂���ʒu�̐ݒ�
	src.m_top    = 0.0f;
	src.m_left   = 0.0f;
	src.m_right  = 600.0f;
	src.m_bottom = 300.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top    = 80.0f;
	dst.m_left   = 4.0f;
	dst.m_right  = (g_mp / g_max_mp)*132.0f;
	dst.m_bottom = 105.0f;

	//�`��
	Draw::Draw(11, &src, &dst, c, 0.0f);
//----------------------------------------------




}