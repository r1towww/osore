//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameHead.h"
#include "ObjStarEffect.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjStarEffect::CObjStarEffect(float x, float y, int i, int j)
{
	m_px = x;		//�ʒu
	m_py = y;
	m_i = i;
	m_j = j;


}



//�C�j�V�����C�Y
void CObjStarEffect::Init()
{
	m_eff.m_top = 0;
	m_eff.m_left = 0;
	m_eff.m_right = 0;
	m_eff.m_bottom = 0;
	m_ani = 0;
	m_ani_time = 0;
	m_ani_flag = true;
}
//�A�j���[�V�����t���O�ύX�p
void CObjStarEffect::Set(bool f)
{
	m_ani_flag = f;
}

//�A�N�V����
void CObjStarEffect::Action()
{

	RECT_F ani_src[5] =
	{
		{ 0,   0,  640,  608 },
		{ 0,  700, 640,  608 },
		{ 0,  1500, 640,  608 },
		//{ 0,  2500, 400,  100 },
		//{ 0,  400, 500,  100 },
	};

	if (m_ani_flag == false)
	{
		m_eff = ani_src[5];//�A�j���[�V������RECT�z�񂩂�4�Ԗڂ�RECT���擾
	}
	else
	{
		//�A�j���[�V�����̃R�}�Ԋu����
		if (m_ani_time > 2)
		{
			m_ani++;	//�A�j���[�V�����̃R�}���P�i�߂�
			m_ani_time = 0;

			m_eff = ani_src[m_ani];//�A�j���[�V������RECT�z�񂩂�m_ani�Ԗڂ�RECT���擾
		}
		else
		{
			m_ani_time++;
		}
	}
	//if (m_ani == 65)
	//{
	//	;
	//}
}
//�h���[
void CObjStarEffect::Draw()
{
	//�`��J���[���  R=RED  G=Green  B=Blue A=alpha(���ߏ��)
	float  c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F dst; //�`���\���ʒu
	CObjStar* objs = (CObjStar*)Objs::GetObj(OBJ_STAR_EFFECT);
	m_x = objs->GetX() + 45;
	m_y = objs->GetY() - 30;
	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_y;
	dst.m_left = 0.0f + m_x;
	dst.m_right = 64.0f + m_x;
	dst.m_bottom = 64.0f + m_y;

	//2�Ԗڂɓo�^�����O���t�B�b�N��dst�Ec�̏������ɕ`��
	Draw::Draw(6, &m_eff, &dst, c, 0.0f);
}