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

float  g_star_x[5];
float  g_star_y[5];

bool g_contact_star_f[5] = { false,false,false,false,false };//��l�����ڐG���Ă��鐯�̊m�F�t���O


CObjStar::CObjStar(float x, float y ,int i,int j,int id)
{
	m_px = x;		//�ʒu
	m_py = y;
	m_i = i;
	m_j = j;

	m_id = id;

}

//�C�j�V�����C�Y
void CObjStar::Init()
{
	m_ani = 0;
	m_ani_time = 0;
	m_ani_stop = 0;
	m_ani_flag = false;

	m_GetStar = false;	//�����擾�ϐ��̏�����

	m_eff.m_top    =   0;
	m_eff.m_left   =   0;
	m_eff.m_right  = 192;
	m_eff.m_bottom = 192;
	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py,64, 64, ELEMENT_STAR, OBJ_STAR, 1);
}

//�A�N�V����
void CObjStar::Action()
{


	if (g_stage_clear != true)
	{
		//�G�t�F�N�g�p
		RECT_F ani_src[15] =
		{
			{ 0,   0, 192, 192 },
			{ 0, 192, 384, 192 },
			{ 0, 384, 576, 192 },
			{ 0, 576, 768, 192 },
			{ 0, 768, 960, 192 },
			{ 192,   0, 192, 384 },
			{ 192, 192, 384, 384 },
			{ 192, 384, 576, 384 },
			{ 192, 576, 768, 384 },
			{ 192, 768, 960, 384 },
			{ 384,   0, 192, 576 },
			{ 384, 192, 384, 576 },
			{ 384, 384, 576, 576 },
			{ 384, 576, 768, 576 },
			{ 384, 768, 960, 576 },
		};
		//���g��HitBox�������Ă���
		CHitBox* hit = Hits::GetHitBox(this);

		//��l���Ɠ������Ă��邩�m�F
		if (hit->CheckObjNameHit(OBJ_HERO) != nullptr && m_GetStar == false)//�������Ă�����擾
		{
			//�X�^�[�l����
			Audio::Start(6);
			g_hp += 5.0f;	//������������ہAHP��0.5�Q�[�W��
			m_ani_flag = true;//�A�j���[�V�����J�n
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
				if (m_ani == 14)
				{
					m_ani_flag = false;
				}
			}
			else
			{
				m_ani_time++;
			}

		}
		//�u���b�N���������Ă���
		CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
		//HitBox�̈ʒu�̕ύX
		hit->SetPos(m_px + block->GetScrollx(), m_py + block->GetScrolly());
	}

	//�{�X��̏ꍇ
	if (g_stage == EarthStar && g_Boss_Spawn ==true)
	{
		m_GetStar = true;			//�F��ς���ׂɃt���O���I���ɂ���
		g_StarCount = 5;

		//���g��HitBox�������Ă���
		CHitBox* hit = Hits::GetHitBox(this);
		if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
		{
			g_contact_star_f[m_id] = true;
		}
		else
		{
			g_contact_star_f[m_id] = false;
		}
	}
}

//�h���[
void CObjStar::Draw()
{

	//�`��J���[���
	float b[4] = { 0.4f,0.4f,0.4f,1.0f };	//�擾�ł��Ă��Ȃ��F
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };	//�擾�ł��Ă���F
	RECT_F src;
	RECT_F dst;	//�`���\���ʒu

	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//�؂���ʒu
	src.m_top = 0;
	src.m_left = 0;
	src.m_right = 220;
	src.m_bottom = 203;

	//�\���ʒu�̐ݒ�
	dst.m_top    = 0.0f + m_py + block->GetScrolly();	//�`��ɑ΂��ăX�N���[���̉e����������
	dst.m_left   = 0.0f + m_px + block->GetScrollx();
	dst.m_right  = 64.0f + m_px + block->GetScrollx();
	dst.m_bottom = 64.0f + m_py + block->GetScrolly();

	//�`��(�J���[�ύX)
	if(m_GetStar == false)
		Draw::Draw(6, &src, &dst, b, 0.0f);
	else
		Draw::Draw(6, &src, &dst, c, 0.0f);

	//�\���ʒu�̐ݒ�
	dst.m_top = -64.0f + m_py + block->GetScrolly();	//�`��ɑ΂��ăX�N���[���̉e����������
	dst.m_left = -64.0f + m_px + block->GetScrollx();
	dst.m_right = 128.0f + m_px + block->GetScrollx();
	dst.m_bottom = 128.0f + m_py + block->GetScrolly();

	if (m_ani_flag == true)
	{
		Draw::Draw(99, &m_eff, &dst, c, 0.0f);
	}
}


