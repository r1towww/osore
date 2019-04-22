//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjBlackhole.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

float* g_blackhole_x[10];//�S�Ẵu���b�N�z�[����X�ʒu��c������
float* g_blackhole_y[10];//�S�Ẵu���b�N�z�[����Y�ʒu��c������

CObjBlackhole::CObjBlackhole(float x, float y,int id)
{
	m_px = x;		//�ʒu
	m_py = y;

	m_blackhole_id = id;
}

//�C�j�V�����C�Y
void CObjBlackhole::Init()
{
	m_ani = 0;			//�A�j���[�V�����p
	m_ani_time = 0;		//�A�j���[�V�����Ԋu�^�C��
	m_eff.m_top = 0;
	m_eff.m_left = 0;
	m_eff.m_right = 200;
	m_eff.m_bottom = 200;

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px + 20, m_py + 20, 20.0f, 24.0f, ELEMENT_FIELD, OBJ_BLACKHOLE + g_blackhole_cnt, 1);
	//�쐬�̂��тɃJ�E���g�𑝂₵�A�ʂ̃I�u�W�F�N�g�Ƃ���
}

//�A�N�V����
void CObjBlackhole::Action()
{
	//���g��HitBox�������Ă���
	CHitBox* hit = Hits::GetHitBox(this);
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);


	//�G�t�F�N�g�p
	RECT_F ani_src[10] =
	{
		{ 0,   0,  192, 192 },
		{ 0, 192,  384, 192 },
		{ 0, 384,  576, 192 },
		{ 0, 576,  768, 192 },
		{ 0, 768,  960, 192 },
		{ 0,   0,  192, 384 },
		{ 0, 192,  384, 384 },
		{ 0, 384,  576, 384 },
		{ 0, 576,  768, 384 },
		{ 0, 768,  960, 384 },
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
	//�W�Ԗځi�摜�Ō�j�܂Ői�񂾂�A�폜
	if (m_ani == 10)
	{
		m_ani = 0;
	}

	//HitBox�̈ʒu�̕ύX
	hit->SetPos(m_px + block->GetScrollx() + 20, m_py + block->GetScrolly() + 20);
}

//�h���[
void CObjBlackhole::Draw()
{
	//�`��J���[���
	float c[4] = { 0.5f,0.5f,0.5f,1.0f };

	RECT_F dst;	//�`���\���ʒu

				//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�\���ʒu�̐ݒ�
	dst.m_top    = 0.0f + m_py + block->GetScrolly();	//�`��ɑ΂��ăX�N���[���̉e����������
	dst.m_left   = 0.0f + m_px + block->GetScrollx();
	dst.m_right  = ALLSIZE + m_px + block->GetScrollx();
	dst.m_bottom = ALLSIZE + m_py + block->GetScrolly();

	//�`��
	Draw::Draw(12, &m_eff, &dst, c, 90.0f);
}


