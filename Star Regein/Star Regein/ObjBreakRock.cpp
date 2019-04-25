//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjBreakRock.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjBreakRock::CObjBreakRock(float x, float y,int i, int j)
{
	m_px = x;		//�ʒu
	m_py = y;
	m_i = i;	//�쐬���Ƀ}�b�v��̍��W���擾
	m_j = j;	
}

//�C�j�V�����C�Y
void CObjBreakRock::Init()
{
	m_ani = 0;			//�A�j���[�V�����p
	m_ani_time = 0;		//�A�j���[�V�����Ԋu�^�C��
	m_eff.m_top    = 0;
	m_eff.m_left   = 0;
	m_eff.m_right  = 200;
	m_eff.m_bottom = 200;
	m_eff_flag = false;		//�G�t�F�N�g�J�n�p�t���O
	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 64.0f, 64.0f, ELEMENT_BLOCK, OBJ_BREAK_ROCK, 1);
}

//�A�N�V����
void CObjBreakRock::Action()
{
	//���g��HitBox�������Ă���
	CHitBox* hit = Hits::GetHitBox(this);
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//�q�[���[�̏��������Ă���
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	////��l���Ɠ������Ă���A���_�b�V���t���O���I���̏ꍇ
	//if (hit->CheckObjNameHit(OBJ_HERO) != nullptr && hero->GetDashF() == true)
	//{
	//	//this->SetStatus(false);		//���g���폜
	//	//Hits::DeleteHitBox(this);

	//	m_eff_flag = true;		//�t���O���I���ɂ��āA�G�t�F�N�g�̊J�n
	//}
	//if (m_eff_flag == true)
	//{
	//	//�G�t�F�N�g�p
	//	RECT_F ani_src[10] =
	//	{
	//		{   0,    0,  192, 192 },
	//		{   0,  192,  384, 192 },
	//		{   0,  384,  576, 192 },
	//		{   0,  576,  768, 192 },
	//		{   0,  768,  960, 192 },
	//		{ 192,    0,  192, 400 },
	//		{ 192,  192,  384, 400 },
	//		{ 192,  384,  576, 400 },
	//		{ 192,  576,  768, 400 },
	//		{ 192,  768,  960, 400 },
	//	};
	//	//�A�j���[�V�����̃R�}�Ԋu����
	//	if (m_ani_time > 2)
	//	{
	//		m_ani++;		//�A�j���[�V�����̃R�}��1�i�߂�
	//		m_ani_time = 0;

	//		m_eff = ani_src[m_ani];//�A�j���[�V������RECT�z�񂩂�m_ani�Ԗڂ�RECT���擾
	//	}
	//	else
	//	{
	//		m_ani_time++;	
	//	}
	//	//9�Ԗځi�摜�Ō�j�܂Ői�񂾂�A�폜
	//	if (m_ani == 9)
	//	{
	//		Hits::DeleteHitBox(this);
	//		this->SetStatus(false);
	//	}
	//}
	////HitBox�̈ʒu�̕ύX
	//hit->SetPos(m_px + block->GetScrollx(), m_py + block->GetScrolly());

}

//�h���[
void CObjBreakRock::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,0.5f,1.0f };

	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top    = 0.0f;
	src.m_left   = 0.0f;
	src.m_right  = 258.0f;
	src.m_bottom = 220.0f;

	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�\���ʒu�̐ݒ�
	dst.m_top    = 0.0f + m_py + block->GetScrolly();	//�`��ɑ΂��ăX�N���[���̉e����������
	dst.m_left   = 0.0f + m_px + block->GetScrollx();
	dst.m_right  = 12.0f + m_px + block->GetScrollx();
	dst.m_bottom = 12.0f + m_py + block->GetScrolly();

	//�`��
	Draw::Draw(4, &src, &dst, c, 90.0f);

	if (m_eff_flag == true)
	{
		//�G�t�F�N�g�p�\���ʒu�̐ݒ�
		dst.m_top = -30.0f + m_py + block->GetScrolly();	//�`��ɑ΂��ăX�N���[���̉e����������
		dst.m_left = -30.0f + m_px + block->GetScrollx();
		dst.m_right = 94.0f + m_px + block->GetScrollx();
		dst.m_bottom = 94.0f + m_py + block->GetScrolly();
		//�`��
		Draw::Draw(17, &m_eff, &dst, c, 90.0f);
	}

}


