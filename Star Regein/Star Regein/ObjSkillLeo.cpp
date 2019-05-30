//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\HitBoxManager.h"


#include "GameHead.h"
#include "ObjSkillLeo.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjSkillLeo::CObjSkillLeo(float x, float y)
{
	m_x = x;
	m_y = y;
}


//�C�j�V�����C�Y
void CObjSkillLeo::Init()
{
	m_time = 0;

	m_ani = 0;			//�`���[�W�A�j���[�V�����p
	m_ani_time = 0;	//�`���[�W�A�j���[�V�����Ԋu�^�C��

	m_eff.m_top = 0;
	m_eff.m_left = 0;
	m_eff.m_right = 192;
	m_eff.m_bottom = 192;
	//�����蔻����Z�b�g
	Hits::SetHitBox(this, m_x - 25, m_y - 25, 128, 128, ELEMENT_SKILL_LEO, OBJ_SKILL_LEO, 1);
}

//�A�N�V����
void CObjSkillLeo::Action()
{


	//HitBox�̓��e���X�V
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_x - 25, m_y - 25);

	//�G�t�F�N�g�p
	RECT_F ani_src[15] =
	{
		{ 0,   0, 192, 192 },
		{ 0, 192, 384, 192 },
		{ 0, 384, 576, 192 },
		{ 0, 576, 768, 192 },
		{ 0, 768, 960, 192 },
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
	//14�Ԗځi�摜�Ō�j�܂Ői�񂾂�A0�Ԗڂɖ߂�
	if (m_ani == 14)
	{
		m_ani = 0;
		this->SetStatus(false);    //���g�ɍ폜���߂��o��
		Hits::DeleteHitBox(this);  //��l���@�����L����HitBox�ɍ폜����
	}

	m_time++;

	//��莞�Ԍo�ƍ폜
	if (m_time >= 10)
	{
		m_time = 0.0f;

	}

}

//�h���[
void CObjSkillLeo::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,0.7f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu


	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 250.0f;
	src.m_bottom = 250.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top    = 0.0f + m_y-40;
	dst.m_left   = 0.0f + m_x-48;
	dst.m_right  = 128.0f + m_x;
	dst.m_bottom = 128.0f + m_y;

	//�\��
	Draw::Draw(23, &m_eff, &dst, c, 0.0f);


}