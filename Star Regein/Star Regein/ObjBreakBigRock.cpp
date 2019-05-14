//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjBreakBigRock.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjBreakBigRock::CObjBreakBigRock(float x, float y, int i, int j)
{
	m_px = x;		//�ʒu
	m_py = y;
	m_i = i;	//�쐬���Ƀ}�b�v��̍��W���擾
	m_j = j;
}

//�C�j�V�����C�Y
void CObjBreakBigRock::Init()
{
	m_cnt = 0;	//���ŃJ�E���g�p
	m_f = false;	//���G���ԗp�t���O

	m_bom_x = 0;	//�����G�t�F�N�g�̕\���ʒu
	m_bom_y = 0;

	m_ani = 0;			//�A�j���[�V�����p
	m_ani_time = 0;		//�A�j���[�V�����Ԋu�^�C��
	m_eff.m_top = 0;
	m_eff.m_left = 0;
	m_eff.m_right = 200;
	m_eff.m_bottom = 200;
	m_eff_flag = false;		//�G�t�F�N�g�J�n�p�t���O
	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px + 25.0f, m_py + 20.0f , 155.0f, 155.0f, ELEMENT_BLOCK, OBJ_BREAK_BIGROCK, 1);
}

//�A�N�V����
void CObjBreakBigRock::Action()
{
	//���g��HitBox�������Ă���
	CHitBox* hit = Hits::GetHitBox(this);
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//�q�[���[�̏��������Ă���
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//��l���Ɠ������Ă���A���_�b�V���t���O���I���A�����G�t���O���I���̏ꍇ
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr && hero->GetDashF() == true && m_f == false)
	{
		m_cnt++;	//�J�E���g��1�v���X����
		m_f = true;	//���G�t���O���I���ɂ���
		m_eff_flag = true;		//�t���O���I���ɂ��āA�G�t�F�N�g�̊J�n
		if (m_cnt == 3)
		{
			Audio::Start(18);
		}
		Audio::Start(17);

	}
	//�t���O���I���̏ꍇ�A�G�t�F�N�g�Ɉڂ�
	if (m_eff_flag == true)
	{
		//�G�t�F�N�g�p
		RECT_F ani_src[10] =
		{
			{   0,    0,  192, 192 },
			{   0,  192,  384, 192 },
			{   0,  384,  576, 192 },
			{   0,  576,  768, 192 },
			{   0,  768,  960, 192 },
			{ 192,    0,  192, 384 },
			{ 192,  192,  384, 384 },
			{ 192,  384,  576, 384 },
			{ 192,  576,  768, 384 },
			{ 192,  768,  960, 384 },
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
		//�J�E���g��3�ŁA9�Ԗځi�摜�Ō�j�܂Ői�񂾏ꍇ
		if (m_ani == 9 && m_cnt == 3)
		{
			g_map[m_i][m_j] = 0;	//�}�b�v��̍��W��0�ɂ��āA�}�b�v�ɕ\������Ȃ�����
			Hits::DeleteHitBox(this);		//�q�b�g�{�b�N�X�̍폜
			this->SetStatus(false);			//�`��̍폜
		}
		//�J�E���g��3�����ŁA9�Ԗځi�摜�Ō�j�܂Ői�񂾂�
		if (m_ani == 9)
		{
			m_ani = 0;	//�A�j���[�V�������O�ɖ߂�
			m_eff_flag = false;	//�G�t�F�N�g�t���O���I�t�ɂ���
			m_f = false;	//���G�t���O���I�t
		}

	}
	//HitBox�̈ʒu�̕ύX
	hit->SetPos(m_px + block->GetScrollx() + 25.0f, m_py + block->GetScrolly() + 20.0f);
}

//�h���[
void CObjBreakBigRock::Draw()
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
	dst.m_right  = 192.0f + m_px + block->GetScrollx();
	dst.m_bottom = 192.0f + m_py + block->GetScrolly();

	//�`��
	Draw::Draw(4, &src, &dst, c, 90.0f);

	if (m_eff_flag == true)
	{
		//�J�E���g���ɂ���āA�\���ꏊ��ύX
		if (m_cnt == 1) {
			m_bom_x = 50.0f;
			m_bom_y = 50.0f;
		}
		else if (m_cnt == 2) {
			m_bom_x = -50.0f;
			m_bom_y = -50.0f;
		}
		else if (m_cnt == 3) {
			m_bom_x = 0.0f;
			m_bom_y = 0.0f;
		}
		//�G�t�F�N�g�p�\���ʒu�̐ݒ�
		dst.m_top    = -30.0f + m_py + block->GetScrolly() + m_bom_y;	//�`��ɑ΂��ăX�N���[���̉e����������
		dst.m_left   = -30.0f + m_px + block->GetScrollx() + m_bom_x;
		dst.m_right  = 230.0f + m_px + block->GetScrollx() + m_bom_x;
		dst.m_bottom = 230.0f + m_py + block->GetScrolly() + m_bom_y;
		//�`��
		Draw::Draw(17, &m_eff, &dst, c, 90.0f);
	}

}


