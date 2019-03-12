//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjMeteo.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;


CObjMeteo::CObjMeteo(float x, float y)
{
	m_px = x;		//�ʒu
	m_py = y;
}

//�C�j�V�����C�Y
void CObjMeteo::Init()
{
	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px + 10, m_py, 30, ALLSIZE, ELEMENT_FIELD, OBJ_KEY, 1);
}

//�A�N�V����
void CObjMeteo::Action()
{
	//��l���̈ʒu���擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	key = hero->GetKEY();
	float hx = hero->GetX();
	float hy = hero->GetY();

	//���g��HitBox�������Ă���
	CHitBox* hit = Hits::GetHitBox(this);

	//��l���Ɠ������Ă��邩�m�F
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)	//�L�[���擾
	{
		this->SetStatus(false);		//���g���폜
		Hits::DeleteHitBox(this);
	}
	//���C
	m_vx += -(m_vx * 0.098);
	m_vy += -(m_vy * 0.098);

	//�ʒu�̍X�V
	m_px += m_vx;
	m_py += m_vy;

	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBox�̈ʒu�̕ύX
	hit->SetPos(m_px + block->GetScrollX() + 10, m_py + block->GetScrollY());

}

//�h���[
void CObjMeteo::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu

				//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 50.0f;
	src.m_right = 100.0f;
	src.m_bottom = 50.0f;

	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py + block->GetScrollY();	//�`��ɑ΂��ăX�N���[���̉e����������
	dst.m_left = 0.0f + m_px + block->GetScrollX();
	dst.m_right = ALL_SIZE + m_px + block->GetScrollX();
	dst.m_bottom = ALL_SIZE + m_py + block->GetScrollY();

	//�`��
	Draw::Draw(HEALKEY, &src, &dst, c, 0.0f);
}


