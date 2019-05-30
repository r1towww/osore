//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameHead.h"
#include "GameL\WinInputs.h"
#include "GameL\Audio.h"
#include "ObjFadein.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjFadein::Init()
{
	m_ani_time = 0;
	m_ani_frame = 0;
	m_ani_max_time = 8;		//�A�j���[�V�����Ԋu��

	m_flag = true;			//�؂�ւ��p�t���O
	m_fade_flag = true;		//�t�F�C�h�C���̐؂�ւ��p�t���O
}

//�A�N�V����
void CObjFadein::Action()
{
	m_ani_time += 1;

	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}
	if (m_ani_frame == 10)
	{
		Scene::SetScene(new  CSceneED());
	}
}

//�h���[
void CObjFadein::Draw()
{
	//�`��J���[���@R=RED  G=Green  B=Blue A=alpha(���ߏ��)
	float  c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;		//�`�挳�؂���ʒu
	RECT_F dst;		//�`���\���ʒu

	//�w�i�؂���
	src.m_top = 0.0f;
	src.m_left = 0.0f + (800.0f * m_ani_frame);
	src.m_right = 800.0f + (800.0f * m_ani_frame);
	src.m_bottom = 600.0f;

	//�`��
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;
	Draw::Draw(89, &src, &dst, c, 0.0f);
}

