//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjWhitehole.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

float* g_whitehole_x[10];//�S�Ẵz���C�g�z�[����X�ʒu��c������
float* g_whitehole_y[10];//�S�Ẵz���C�g�z�[����Y�ʒu��c������

CObjWhitehole::CObjWhitehole(float x, float y)
{
	m_px = x;		//�ʒu
	m_py = y;
}

//�C�j�V�����C�Y
void CObjWhitehole::Init()
{
	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px + 20, m_py + 20, 20.0f, 24.0f, ELEMENT_FIELD, OBJ_WHITEHOLE, 1);
}

//�A�N�V����
void CObjWhitehole::Action()
{

}

//�h���[
void CObjWhitehole::Draw()
{
	//�`��J���[���
	float c[4] = { 0.5f,0.5f,0.5f,1.0f };

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


