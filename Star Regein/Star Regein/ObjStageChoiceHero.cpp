//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjStageChoiceHero.h"
#include "ObjStageChoice.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;


ObjStageChoiceHero::ObjStageChoiceHero(float x, float y)
{//�I�u�W�F�쐬���ɓn���ꂽx,y���W�������o�ϐ��ɑ��
	m_px = x;
	m_py = y;
}

//�C�j�V�����C�Y
void ObjStageChoiceHero::Init()
{
	m_vx = 0.0f;		//�ړ��x�N�g��
	m_vy = 0.0f;
	//�����p��
	g_posture = HERO_DOWN;

	m_ani_time = 0;
	m_ani_frame = 1;

	//block�Ƃ̏Փˏ�Ԋm�F
	m_hit_up    = false;
	m_hit_down  = false;
	m_hit_left  = false;
	m_hit_right = false;

	m_block_type = 0;		//����ł���block�̎�ނ��m�F�p

}

//�A�N�V����
void ObjStageChoiceHero::Action()
{
	//�����I�����ɓ��͐��䂷��
	if (g_stage == Earth || g_stage == Venus || g_stage == Mercury || g_stage == Sun ) {
		return;
	}

	//�ړ��x�N�g���̔j��
	m_vx = 0.0f;
	m_vy = 0.0f;

	//Shift�L�[�����͂��ꂽ��_�b�V��
	if ((Input::GetVKey(VK_SHIFT)))
	{
		m_speed_power = STAGE_DASH_SPEED;
	}
	else//�ʏ푬�x
	{
		m_speed_power = STAGE_NORMAL_SPEED;
	}

	if (Input::GetVKey(VK_UP))//���L�[�i��j�����͂��ꂽ�Ƃ�
	{
		m_vy -= m_speed_power;
		g_posture = HERO_UP;
		m_ani_time += ANITIME;
	}
	else if (Input::GetVKey(VK_DOWN))//���L�[�i���j�����͂��ꂽ�Ƃ�
	{
		m_vy += m_speed_power;
		g_posture = HERO_DOWN;
		m_ani_time += ANITIME;
	}
	else if (Input::GetVKey(VK_LEFT))//���L�[�i���j�����͂��ꂽ�Ƃ�
	{
		m_vx -= m_speed_power;
		g_posture = HERO_LEFT;
		m_ani_time += ANITIME;
	}
	else if (Input::GetVKey(VK_RIGHT))//���L�[�i�E�j�����͂��ꂽ�Ƃ�
	{
		m_vx += m_speed_power;
		g_posture = HERO_RIGHT;
		m_ani_time += ANITIME;
	}
	else//�ړ��L�[�̓��͂������ꍇ
	{
		m_ani_frame = 1;	//�Î~�t���[���ɂ���
		m_ani_time = 0;		//�A�j���[�V�������ԃ��Z�b�g
	}

	//�A�j���[�V�����p
	if (m_ani_time > 4)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}

	if (m_ani_frame == 4)
	{
		m_ani_frame = 0;
	}

	//�X�e�[�W�I����ʂ̏����擾
	CObjStageChoice* stagec = (CObjStageChoice*)Objs::GetObj(OBJ_STAGECHOICE);


	//�n����
	if (m_px >= EarthX && m_px <= EarthX2 && m_py >= EarthY&&m_py <= EarthY2)
	{
		//���O�V�[������Z�L�[���������ł���������Ȃ��悤�ɁA
		//���̃V�[���ɓ����Ĉ�x�������ĂȂ���ԂɈڍs���Ȃ���
		//���s�o���Ȃ��悤�ɂ��Ă���B
		if (Input::GetVKey('Z') == true && m_key_flag == true)
		{
			g_stage = Earth;	//�X�e�[�W�̒l��n���ɕύX
		}
	}
	//������
	else if (m_px >= VenusX && m_px <= VenusX2 && m_py >= VenusY&&m_py <= VenusY2)
	{
		//���O�V�[������Z�L�[���������ł���������Ȃ��悤�ɁA
		//���̃V�[���ɓ����Ĉ�x�������ĂȂ���ԂɈڍs���Ȃ���
		//���s�o���Ȃ��悤�ɂ��Ă���B
		if (Input::GetVKey('Z') == true && m_key_flag == true)
		{
			//�����ɐݒ�
			g_stage = Venus;
		}
	}
	//������
	else if (m_px >= MercuryX && m_px <= MercuryX2 && m_py >= MercuryY&&m_py <= MercuryY2)
	{
		//���O�V�[������Z�L�[���������ł���������Ȃ��悤�ɁA
		//���̃V�[���ɓ����Ĉ�x�������ĂȂ���ԂɈڍs���Ȃ���
		//���s�o���Ȃ��悤�ɂ��Ă���B
		if (Input::GetVKey('Z') == true && m_key_flag == true)
		{
			//�����ɐݒ�
			g_stage = Mercury;
		}
	}
	//���z��
	else if (m_px >= SunX && m_px <= SunX2 && m_py >= SunY&&m_py <= SunY2)
	{
		if (Input::GetVKey('Z') == true && m_key_flag == true)
		{
			//���Ń^�C�g���ɍs���悤�ɂ��Ă邩�炠�Ƃł����Ƒ��z�ɂ��Ă����Ă�
			//���z�ɐݒ�
			//g_stage = SunLeo;���X�e�[�W������������R�����g�O���Ă�
			Scene::SetScene(new CSceneTitle());
		}
	}
	else
	{
		m_key_flag = true;
	}

	//�ʒu�̍X�V
	m_px += m_vx;
	m_py += m_vy;
}

//�h���[
void ObjStageChoiceHero::Draw()
{
	//�A�j���[�V����
	int AniData[5] =
	{
		0,1,2,3,0,
	};

	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top    = 64.0f * g_posture;
	src.m_left   =  0.0f + (AniData[m_ani_frame] * 64);
	src.m_right  = 64.0f + (AniData[m_ani_frame] * 64);
	src.m_bottom = src.m_top + 64.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top    =  0.0f + m_py;
	dst.m_left   = 80.0f + m_px;
	dst.m_right  =  0.0f + m_px;
	dst.m_bottom = 80.0f + m_py;

	//�\��
	Draw::Draw(1, &src, &dst, c, 0.0f);
}
