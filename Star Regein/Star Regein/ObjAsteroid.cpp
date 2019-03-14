//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjAsteroid.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjAsteroid::CObjAsteroid(float x, float y)
{
	m_px = x;		//�ʒu
	m_py = y;
}

//�C�j�V�����C�Y
void CObjAsteroid::Init()
{
	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px + 25, m_py + 30, 145.0f, 150.0f, ELEMENT_BLOCK, OBJ_ASTEROID, 1);
}

//�A�N�V����
void CObjAsteroid::Action()
{
	//���g��HitBox�������Ă���
	CHitBox* hit = Hits::GetHitBox(this);

	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//HitBox�̈ʒu�̕ύX
	hit->SetPos(m_px + block->GetScrollx() + 25, m_py + block->GetScrolly() + 30);

}

//�h���[
void CObjAsteroid::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 258.0f;
	src.m_bottom = 220.0f;
	
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�\���ʒu�̐ݒ�
	dst.m_top    = 0.0f + m_py + block->GetScrolly();	//�`��ɑ΂��ăX�N���[���̉e����������
	dst.m_left   = 0.0f + m_px + block->GetScrollx();
	dst.m_right  = 192.0f + m_px + block->GetScrollx();
	dst.m_bottom = 192.0f + m_py + block->GetScrolly();

	//�`��
	Draw::Draw(4, &src, &dst, c, 0.0f);
}


