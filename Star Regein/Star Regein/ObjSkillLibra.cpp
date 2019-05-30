//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjSkillLibra.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjSkillLibra::CObjSkillLibra(float x, float y)
{
	m_x = x;
	m_y = y;
}


//�C�j�V�����C�Y
void CObjSkillLibra::Init()
{

	m_ani = 0;			//�`���[�W�A�j���[�V�����p
	m_ani_time = 0;	//�`���[�W�A�j���[�V�����Ԋu�^�C��

	m_f = false;	//�G�t�F�N�g���t���O�̏�����

	m_persist_time = 0;

	m_eff.m_top    =   0;
	m_eff.m_left   =   0;
	m_eff.m_right  = 192;
	m_eff.m_bottom = 192;
}

//�A�N�V����
void CObjSkillLibra::Action()
{
	//�t���O���I�t�̏ꍇ
	if (m_f == false)
	{
		Audio::Start(12);	//SE��炷
		m_f = true;	//�P�x�������悤�Ƀt���O���I���ɂ���
	}
	//�G�t�F�N�g�p
	RECT_F ani_src[15] =
	{
		{   0,   0, 192, 192 },
		{   0, 192, 384, 192 },
		{   0, 384, 576, 192 },
		{   0, 576, 768, 192 },
		{   0, 768, 960, 192 },
		{ 192,   0, 192, 384 },
		{ 192, 192, 384, 384 },
		{ 192, 384, 576, 384 },
		{ 192, 576, 768, 384 },
		{ 192, 768, 960, 384 },
		{ 384,   0, 192, 576 },
		{ 384, 192, 384, 576 },
		{ 384, 384, 576, 576 },
		{ 384, 576, 768, 576 },
		{ 384, 768, 960, 576 },
	};

	//�A�j���[�V�����̃R�}�Ԋu����
	if (m_ani_time > 3)
	{
		m_ani++;		//�A�j���[�V�����̃R�}��1�i�߂�
		m_ani_time = 0;

		m_eff = ani_src[m_ani];//�A�j���[�V������RECT�z�񂩂�m_ani�Ԗڂ�RECT���擾
	}
	else
	{
		m_ani_time++;
	}
	//�W�Ԗځi�摜�Ō�j�܂Ői�񂾂�A0�Ԗڂɖ߂�
	if (m_ani == 14)
	{
		m_ani = 0;
	}

	m_persist_time++;
	
	if (m_persist_time > 25)
	{
		m_persist_time = 0;

		//�{�X��|���Ă������l����MP������Ȃ��悤�ɂ���
		if (g_boss_hp <= 0)
			;
		else
			g_mp -= 1.0f;
	}

	//MP��0�ɂȂ邩�ʂ̃X�L�����I�����ꂽ��
	if (g_skill != Libra || g_mp <= 0.0f)
	{
		this->SetStatus(false);		//�폜
	}

}

//�h���[
void CObjSkillLibra::Draw()
{
	//�`��J���[���
	float r[4] = { 1.0f,0.0f,0.0f,0.5f };
	float y[4] = { 1.0f,1.0f,0.0f,0.5f };
	float c[4] = { 1.0f,1.0f,1.0f,0.5f };

	RECT_F dst;	//�`���\���ʒu

	//�\���ʒu�̐ݒ�
	dst.m_top    =  0.0f + m_y;		//�ʒu�̒���
	dst.m_left   = 80.0f + m_x;
	dst.m_right  =  0.0f + m_x;
	dst.m_bottom = 80.0f + m_y;

	//�`��
	if(g_hp <= 20.0f)
		Draw::Draw(14, &m_eff, &dst, r, 0.0f);
	else if (g_hp <= 50.0f)
		Draw::Draw(14, &m_eff, &dst, y, 0.0f);
	else 
		Draw::Draw(14, &m_eff, &dst, c, 0.0f);
}