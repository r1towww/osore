//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjSkillItem.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

bool g_Earth_Max = false;
bool g_Taurus_Max = false;
bool g_Libra_Max = false;
bool g_Gemini_Max = false;
bool g_Virgo_Max = false;
bool g_Leo_Max = false;


CObjSkillItem::CObjSkillItem(float x, float y)
{
	m_x = x;
	m_y = y;

}

//�C�j�V�����C�Y
void CObjSkillItem::Init()
{
	

	m_vx = 0.0f;
	m_vy = 0.0f;

	g_skill_item_flag = false;

	//�����蔻����Z�b�g
	Hits::SetHitBox(this, m_x+80, m_y, 60.0f, 60.0f, ELEMENT_SKILL_ITEM, OBJ_SKILL_ITEM, 1);
}

//�A�N�V����
void CObjSkillItem::Action()
{
	
	
	//���g��HitBox�������Ă���
	CHitBox* hit = Hits::GetHitBox(this);
	
	//���Ɉړ�
	m_vy += 0.01f;
	m_y += m_vy;

	//�쐬����HitBox�X�V�p�̓���������o��
	hit->SetPos(m_x + 80, m_y);//���������V�����ʒu�i��l���̈ʒu�j���ɒu��������
	

	//��l���Ɠ���������I�u�W�F�N�g�폜���A�X�L���A�C�e���t���O���I��
	if (hit->CheckElementHit(ELEMENT_PLAYER) == true)
	{
		
		this->SetStatus(false);    //���g�ɍ폜���߂��o��
		Hits::DeleteHitBox(this);  //��l���@�����L����HitBox�ɍ폜����
		g_skill_item_flag = true;
	}
	
}

//�h���[
void CObjSkillItem::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu


	if (g_Earth_Max == true)//�n��
	{
		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 300.0f;
		src.m_bottom = 200.0f;
	}
	else if (g_Taurus_Max==true)//������
	{
		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 300.0f;
		src.m_right = 600.0f;
		src.m_bottom = 200.0f;
	}
	else if (g_Libra_Max == true)//�V����
	{
		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 600.0f;
		src.m_right = 900.0f;
		src.m_bottom = 200.0f;	
	}
	else if (g_Gemini_Max == true)//�o�q��
	{
		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 900.0f;
		src.m_right = 1200.0f;
		src.m_bottom = 200.0f;
	}
	else if (g_Virgo_Max == true)//������
	{
		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 1200.0f;
		src.m_right = 1500.0f;
		src.m_bottom = 200.0f;
	}
	else if (g_Leo_Max == true)//���q��
	{
		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 1500.0f;
		src.m_right = 1800.0f;
		src.m_bottom = 200.0f;
	}
	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_y;
	dst.m_left = 70.0f + m_x;
	dst.m_right = 150.0f + m_x;
	dst.m_bottom = 80.0f + m_y;

	Draw::Draw(13, &src, &dst, c, 0.0f);
}