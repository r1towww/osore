//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjHeart.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

float g_mp;
float g_max_mp;

CObjMP::CObjMP()
{

}

//�C�j�V�����C�Y
void CObjMP::Init()
{

}

//�A�N�V����
void CObjMP::Action()
{


}

//�h���[
void CObjMP::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 600.0f;
	src.m_bottom = 300.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 80.0f;
	dst.m_left = 0.0f;
	dst.m_right = (g_mp / g_max_mp)*128.0f;;
	dst.m_bottom = 105.0f;

	//�`��
	Draw::Draw(11, &src, &dst, c, 0.0f);


}