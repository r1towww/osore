//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"

#include "UtilityModule.h"
#include "GameHead.h"
#include "ObjSkillGemini.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjSkillGemini::Init()
{


}

//�A�N�V����
void CObjSkillGemini::Action()
{

	// ��l���@�ƃT�u�@�Ŋp�x�����B
	CObjHero*obj = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//��l���@�����݂���ꍇ�A�T�u�@�p�x�̌v�Z����
	if (obj != nullptr)
	{
		float x = obj->GetX() - m_x;
		float y = obj->GetY() - m_y;
		float ar = GetAtan2Angle(x, -y);

		//�T�u�@�̌��݂̌����Ă�p�x�����B
		float br = atan2(-m_vy, m_vx)*180.0f / 3.14f;
		if (br < 0)
		{
			br = 360 - abs(br);
		}

		//��l���@�ƃT�u�@�p�x�����܂�ɂ��������ꂽ��
		if (ar - br > 20)
		{
			//�ړ���������l���@�̕����ɂ���
			m_vx = cos(3.14 / 180 * ar);
			m_vy = -sin(3.14 / 180 * ar);
		}

		float r = 3.14 / 180.0f;   //�p�x�P��
		if (ar < br)
		{
			//�ړ������ɂ�+1��������
			m_vx = m_vx*cos(r) - m_vy*sin(r);
			m_vy = m_vy*cos(r) + m_vx*sin(r);
		}
		else
		{
			//�ړ������ɂ�-1��������
			m_vx = m_vx*cos(-r) - m_vy*sin(-r);
			m_vy = m_vy*cos(-r) + m_vx*sin(-r);

		}
	}
}

//�h���[
void CObjSkillGemini::Draw()
{
	//�A�j���[�V����
	int AniData[5] =
	{
		0,1,2,3,0,
	};

	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	//�u���b�N���������Ă���
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�؂���ʒu�̐ݒ�
	src.m_top = 64.0f * g_posture;
	src.m_left = 0.0f + (AniData[m_ani_frame] * 64);
	src.m_right = 64.0f + (AniData[m_ani_frame] * 64);
	src.m_bottom = src.m_top + 64.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top    =  0.0f;
	dst.m_left   = 80.0f;
	dst.m_right  =  0.0f;
	dst.m_bottom = 80.0f;

	//�`��
	Draw::Draw(1, &src, &dst, c, 0.0f);
}