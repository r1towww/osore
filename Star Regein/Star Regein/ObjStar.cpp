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


CObjStar::CObjStar(float x, float y ,int i,int j,int id)
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
	m_eff.m_right =220;
	m_eff.m_bottom = 203;
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

	if (g_stage_clear != true)
	{
		RECT_F ani_src[8] =
		{
			{ 0,  220,   460, 203 },
			{ 0, 460,   490, 203 },
			{ 0, 490,   930, 203 },
			{ 0, 930,   1160, 203 },
			{ 0, 1160,   1390, 203 },
			{ 0, 1390,   1625, 203 },
			{ 0, 1625,   1850, 203 },
			{ 0, 1850,   2096, 203 },

		};
		//���g��HitBox�������Ă���
		CHitBox* hit = Hits::GetHitBox(this);

		//��l���Ɠ������Ă��邩�m�F
		if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)//�������Ă�����擾
		{
			//�X�^�[�l����
			Audio::Start(6);
			g_hp += 5.0f;	//������������ہAHP��0.5�Q�[�W��
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
				if (m_ani_stop >= 8)
				{
					m_ani_flag = false;
					m_eff.m_top = 0;
					m_eff.m_left = 0;
					m_eff.m_right = 220;
					m_eff.m_bottom = 203;

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
	else
	{
		Hits::DeleteHitBox(this);
	}
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


