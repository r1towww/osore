//�g�p����w�b�_�[
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\SceneManager.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "ObjStageChoice.h"

//----------------------------------
//�g�p����l�[���X�y�[�X
using namespace GameL;


//�C�j�V�����C�Y
void CObjStageChoice::Init()
{
	m_alpha = 1.0f;		//�A���t�@�l�̏�����
}

//�A�N�V����
void CObjStageChoice::Action()
{


}

//�h���[
void CObjStageChoice::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,m_alpha };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	//�w�i------------------------------------
	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1920.0f;
	src.m_bottom = 1080.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f ;
	dst.m_left = 0.0f ;
	dst.m_right = 800.0f ;
	dst.m_bottom = 600.0f ;

	//�\��
	Draw::Draw(2, &src, &dst, c, 0.0f);
	//----------------------------------------

	//�n��------------------------------------
	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 300.0f;
	src.m_bottom = 283.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top =	450.0f;
	dst.m_left = 0.0f;
	dst.m_right = 150.0f;
	dst.m_bottom = 600.0f;

	//�\��
	Draw::Draw(3, &src, &dst, c, 0.0f);
	//----------------------------------------


	//����------------------------------------
	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 303.0f;
	src.m_bottom =303.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 350.0f;
	dst.m_left = 200.0f;
	dst.m_right = 350.0f;
	dst.m_bottom = 500.0f;

	//�\��
	Draw::Draw(4, &src, &dst, c, 0.0f);
	//----------------------------------------

	//����------------------------------------
	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 325.0f;
	src.m_bottom =325.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 180.0f;
	dst.m_left = 450.0f;
	dst.m_right = 600.0f;
	dst.m_bottom =330.0f;

	//�\��
	Draw::Draw(5, &src, &dst, c, 0.0f);
	//----------------------------------------

	//���z------------------------------------
	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 335.0f;
	src.m_bottom = 350.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f;
	dst.m_left = 650.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 150.0f;

	//�\��
	Draw::Draw(6, &src, &dst, c, 0.0f);
	//----------------------------------------

}
