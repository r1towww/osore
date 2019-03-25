//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjBlackhole.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjBlackhole::CObjBlackhole(float x, float y)
{
	m_px = x;		//�ʒu
	m_py = y;
}

//�C�j�V�����C�Y
void CObjBlackhole::Init()
{
	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px + 20, m_py + 20, 20.0f, 24.0f, ELEMENT_FIELD, OBJ_ASTEROID, 1);
}

//�A�N�V����
void CObjBlackhole::Action()
{
	//���g��HitBox�������Ă���
	CHitBox* hit = Hits::GetHitBox(this);
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//�z���C�g�z�[���̏��������Ă���
	CObjWhitehole* whitehole = (CObjWhitehole*)Objs::GetObj(OBJ_WHITEHOLE);
	float wx = whitehole->Getx() - HOLEBALANCE_X;	//�ړ���ʒu�̒���
	float wy = whitehole->Gety() - HOLEBALANCE_Y;
	
	//��l���Ɠ������Ă��邩�m�F
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		hit->SetInvincibility(true);	//���G�I��
		m_time = SETTIME;	//���Ԃ��Z�b�g����
		block->SetScrollx(-wx);	//�z���C�g�z�[���̈ʒu�Ɉړ�������
		block->SetScrolly(-wy + TELEPORTBALANCE);	//�ʒu�����Ȃ��悤�ɂ��炷
	}

	/* ���G���ԗp */
	//���Ԃ��Z�b�g����Ă����
	if (m_time > 0) {
		m_time--;	//���Ԃ����炷
		if (m_time <= 0) {	//0�ȉ��ɂȂ�����
			m_time = 0;
			hit->SetInvincibility(false);	//���G���I�t
		}
	}

	//HitBox�̈ʒu�̕ύX
	hit->SetPos(m_px + block->GetScrollx() + 20, m_py + block->GetScrolly() + 20);

}

//�h���[
void CObjBlackhole::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top    = 0.0f;
	src.m_left   = 0.0f;
	src.m_right  = 256.0f;
	src.m_bottom = 256.0f;

	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�\���ʒu�̐ݒ�
	dst.m_top    = 0.0f + m_py + block->GetScrolly();	//�`��ɑ΂��ăX�N���[���̉e����������
	dst.m_left   = 0.0f + m_px + block->GetScrollx();
	dst.m_right  = ALLSIZE + m_px + block->GetScrollx();
	dst.m_bottom = ALLSIZE + m_py + block->GetScrolly();

	//�`��
	Draw::Draw(12, &src, &dst, c, 90.0f);
}


