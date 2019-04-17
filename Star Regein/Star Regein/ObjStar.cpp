//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameHead.h"
#include "ObjStar.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjStar::CObjStar(float x, float y ,int i,int j)
{
	m_px = x;		//�ʒu
	m_py = y;
	m_i = i;
	m_j = j;

}

//�C�j�V�����C�Y
void CObjStar::Init()
{
	m_eff.m_top = 0;
	m_eff.m_left = 0;
	m_eff.m_right =640;
	m_eff.m_bottom = 608;
	m_ani = 0;
	m_ani_time = 0;
	m_ani_stop = 0;
	m_ani_flag = false;

	m_GetStar = false;	//�����擾�ϐ��̏�����
	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py,64, 64, ELEMENT_STAR, OBJ_STAR, 1);
}

//�A�N�V����
void CObjStar::Action()
{
	RECT_F ani_src[5] =
	{
		{ 0,   0,   950, 640 },
		{ 0, 950,   1900, 640 },
		{ 0, 1900,   2851, 640 },
		{ 0, 2851,   3801, 640 },
		{ 0, 4752,   4752, 640 },
	};
	//���g��HitBox�������Ă���
	CHitBox* hit = Hits::GetHitBox(this);

	//��l���Ɠ������Ă��邩�m�F
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)//�������Ă�����擾
	{
		m_ani_flag = true;//�A�j���[�V�����J�n
		hit->SetInvincibility(true);	//�G����Ȃ�����
		m_GetStar = true;			//�擾�����ہA�F��ς���ׂɃt���O���I���ɂ���
		g_StarCount++;				//���ݎ擾���Ă��鐯�̐����J�E���g����
		g_map[m_i][m_j] = 4;	//�~�j�}�b�v��Ő���\������
	}
	if (m_ani_flag == true)
	{
		//�A�j���[�V�����̃R�}�Ԋu����
		if (m_ani_time > 2)
		{

			m_ani++;	//�A�j���[�V�����̃R�}���P�i�߂�
			m_ani_time = 0;

			m_eff = ani_src[m_ani];//�A�j���[�V������RECT�z�񂩂�m_ani�Ԗڂ�RECT���擾
			m_ani_stop++;
			if (m_ani_stop >= 10)
			{
				m_ani_flag = false;
				m_eff.m_top = 0;
				m_eff.m_left = 0;
				m_eff.m_right = 640;
				m_eff.m_bottom = 608;

			}
		}
		else
		{
			m_ani_time++;
		}
		//3�R�}�ړ˓���A0�R�}�ڂɖ߂����ŃA�j���[�V�����𖳌����[�v������B
		if (m_ani == 3)
		{
			m_ani = 0;
		}

	}
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBox�̈ʒu�̕ύX
	hit->SetPos(m_px + block->GetScrollx(), m_py + block->GetScrolly());

}

//�h���[
void CObjStar::Draw()
{

	//�`��J���[���
	float b[4] = { 0.4f,0.4f,0.4f,1.0f };	//�擾�ł��Ă��Ȃ��F
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };	//�擾�ł��Ă���F

	RECT_F dst;	//�`���\���ʒu


	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�\���ʒu�̐ݒ�
	dst.m_top    = 0.0f + m_py + block->GetScrolly();	//�`��ɑ΂��ăX�N���[���̉e����������
	dst.m_left   = 0.0f + m_px + block->GetScrollx();
	dst.m_right  = 64.0f + m_px + block->GetScrollx();
	dst.m_bottom = 64.0f + m_py + block->GetScrolly();

	//�`��(�J���[�ύX)
	if(m_GetStar == false)
		Draw::Draw(6, &m_eff, &dst, b, 0.0f);
	else
		Draw::Draw(6, &m_eff, &dst, c, 0.0f);
}


