//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"

#include "GameHead.h"
#include "ObjSkillLibra.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjSkillLibra::CObjSkillLibra(int x, int y)
{
	m_x = x;
	m_y = y;
}


//�C�j�V�����C�Y
void CObjSkillLibra::Init()
{

	m_ani = 0;			//�`���[�W�A�j���[�V�����p
	m_ani_time = 0;	//�`���[�W�A�j���[�V�����Ԋu�^�C��
	m_ani_flag = false;	//true�ŃA�j���[�V��������Afalse�ŃA�j���[�V������~
	m_eff.m_top    =   0;
	m_eff.m_left   =   0;
	m_eff.m_right  = 200;
	m_eff.m_bottom = 200;
}

//�A�N�V����
void CObjSkillLibra::Action()
{
	
	//�G�t�F�N�g�p
	RECT_F ani_src[8] =
	{
		{ 0,    0,   200, 200 },
		{ 0,  200,   400, 200 },
		{ 0,  400,   600, 200 },
		{ 0,  600,   800, 200 },
		{ 0,  800,  1000, 200 },
		{ 0, 1000,  1200, 200 },
		{ 0, 1200,  1400, 200 },
		{ 0, 1400,  1600, 200 },
	};


	//�A�j���[�V�����̃R�}�Ԋu����
	if (m_ani_time > 2)
	{
		m_ani++;		//�A�j���[�V�����̃R�}��1�i�߂�
		m_ani_time = 0;

		m_eff = ani_src[m_ani];//�A�j���[�V������RECT�z�񂩂�m_ani�Ԗڂ�RECT���擾
	}
	else
	{
		m_ani_time++;
	}
	//�W�Ԗځi�摜�Ō�j�܂Ői�񂾂�A�폜
	if (m_ani == 8)
	{
		this->SetStatus(false);
	}

}

//�h���[
void CObjSkillLibra::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F dst;	//�`���\���ʒu

	//�\���ʒu�̐ݒ�
	dst.m_top    =  0.0f + m_y;		//�ʒu�̒���
	dst.m_left   = 80.0f + m_x;
	dst.m_right  =  0.0f + m_x;
	dst.m_bottom = 80.0f + m_y;

	//�`��
	Draw::Draw(14, &m_eff, &dst, c, 0.0f);
}