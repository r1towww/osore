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

CObjSkillLeo::CObjSkillLeo(int x, int y)
{
	m_x = x;
	m_y = y;
}


//�C�j�V�����C�Y
void CObjSkillLeo::Init()
{
	m_time = 0;


	//�����蔻����Z�b�g
	Hits::SetHitBox(this, m_x - 25, m_y - 25, 128, 128, ELEMENT_SKILL_LEO, OBJ_SKILL_LEO, 1);
}

//�A�N�V����
void CObjSkillLeo::Action()
{


	//HitBox�̓��e���X�V
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_x - 25, m_y - 25);

	m_time++;

	//��莞�Ԍo�ƍ폜
	if (m_time >= 10)
	{
		m_time = 0.0f;

		this->SetStatus(false);    //���g�ɍ폜���߂��o��
		Hits::DeleteHitBox(this);  //��l���@�����L����HitBox�ɍ폜����
	}

}

//�h���[
void CObjSkillLeo::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu


	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 250.0f;
	src.m_bottom = 250.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_y-40;
	dst.m_left = 0.0f + m_x-45;
	dst.m_right = 128.0f + m_x;
	dst.m_bottom = 128.0f + m_y;

	//�\��
	Draw::Draw(23, &src, &dst, c, 0.0f);


}