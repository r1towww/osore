//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\DrawFont.h"
#include "GameHead.h"
#include "ObjStageChoiceHero.h"
#include "ObjStageChoice.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;


ObjStageChoiceHero::ObjStageChoiceHero(float x, float y)
{//�I�u�W�F�쐬���ɓn���ꂽx,y���W�������o�ϐ��ɑ��
	g_stage_px = x;
	g_stage_py = y;
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

	m_alpha = ALPHAORIGIN;

	m_key_flag = true;

}

//�A�N�V����
void ObjStageChoiceHero::Action()
{
	g_gemini_check = false;

	//�`��J���[���
	float c[4] = { 1.0f,0.0f,0.0f,1.0f };

	//�����I�����ɓ��͐��䂷��
	if (g_stage == Earth || g_stage == Venus || g_stage == Mercury || g_stage == Sun) {
		return;
	}
	//��l���@���̈�O�s���Ȃ�����
	if (g_stage_px + 64.0f > 800.0f)
	{
		g_stage_px = 800.0f - 64.0f;
	}
	if (g_stage_py + 64.0f > 600.0f)
	{
		g_stage_py = 600.0f - 64.0f;
	}
	if (g_stage_py < 0.0f)
	{
		g_stage_py = 0.0f;
	}
	if (g_stage_px < 0.0f)
	{
		g_stage_px = 0.0f;
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

	//�L�[���͂𒷉����ŏo���Ȃ��悤�ɂ���
	if (Input::GetVKey('Z') == false || Input::GetVKey(VK_RETURN) == false)
	{
		g_key_flag = true;	//��������I���ɂ���
	}


	// Z�L�[����͂��A�L�[�t���O���I���̎��Ɏ��s
	if ((Input::GetVKey('Z') == true || Input::GetVKey(VK_RETURN) == true) && g_key_flag == true)
	{
		if (m_key_flag == true)
		{
			//�n����
			if (g_stage_px >= EarthX && g_stage_px <= EarthX2 && g_stage_py >= EarthY&&g_stage_py <= EarthY2)
			{
				//���O�V�[������Z�L�[���������ł���������Ȃ��悤�ɁA
				//���̃V�[���ɓ����Ĉ�x�������ĂȂ���ԂɈڍs���Ȃ���
				//���s�o���Ȃ��悤�ɂ��Ă���B
				g_stage = Earth;	//�X�e�[�W�̒l��n���ɕύX
				Audio::Start(1);
				m_key_flag = false;
			}
			//������
			else if (g_stage_px >= VenusX && g_stage_px <= VenusX2 && g_stage_py >= VenusY&&g_stage_py <= VenusY2)
			{
				if (g_Earth_clear == true)
				{
					//���O�V�[������Z�L�[���������ł���������Ȃ��悤�ɁA
					//���̃V�[���ɓ����Ĉ�x�������ĂȂ���ԂɈڍs���Ȃ���
					//���s�o���Ȃ��悤�ɂ��Ă���B
					//�����ɐݒ�
					g_stage = Venus;
					Audio::Start(1);
				}
				else
				{
					;
				}
				m_key_flag = false;

				}
				//������
				else if (g_stage_px >= MercuryX && g_stage_px <= MercuryX2 && g_stage_py >= MercuryY&&g_stage_py <= MercuryY2)
				{
					if (g_Venus_clear == true)
					{
					//	//���O�V�[������Z�L�[���������ł���������Ȃ��悤�ɁA
					//	//���̃V�[���ɓ����Ĉ�x�������ĂȂ���ԂɈڍs���Ȃ���
					//	//���s�o���Ȃ��悤�ɂ��Ă���B
					//	//�����ɐݒ�
						g_stage = Mercury;
						Audio::Start(1);
					}
					else
					{
						;
					}
					m_key_flag = false;
				}
				//���z��
				else if (g_stage_px >= SunX && g_stage_px <= SunX2 && g_stage_py >= SunY&&g_stage_py <= SunY2)
				{
					if (g_Mercury_clear == true)
					{
						Audio::Start(1);
						//���Ń^�C�g���ɍs���悤�ɂ��Ă邩�炠�Ƃł����Ƒ��z�ɂ��Ă����Ă�
						//���z�ɐݒ�
						g_stage = Sun;
					}
					else
					{
					}
					m_key_flag = false;

			}
		}
		g_key_flag = false;	//�L�[�t���O���I�t
		//�X�e�[�W�I��(����)�I�u�W�F�N�g�쐬
		CObjStarChoice* star = new CObjStarChoice();
		Objs::InsertObj(star, OBJ_STARCHOICE, 20);
	}
	else
		m_key_flag = true;



	//�ʒu�̍X�V
	g_stage_px += m_vx;
	g_stage_py += m_vy;
}

//�h���[
void ObjStageChoiceHero::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,m_alpha };
	float red[4] = { 1.0f,0.0f,0.0f,m_alpha };


	//�A�j���[�V����
	int AniData[5] =
	{
		0,1,2,3,0,
	};
	//�e�f�������̘f�����킩��悤�ɕ`��
	//�n��
	if (g_stage_px >= EarthX && g_stage_px <= EarthX2 && g_stage_py >= EarthY&&g_stage_py <= EarthY2)
	{
		Font::StrDraw(L"�n���X�e�[�W", 32, 32, 32, c);
	}
	
	//�n�����N���A���Ă��Ȃ��ꍇ���̃��b�Z�[�W��\������
	if (g_stage_px >= VenusX && g_stage_px <= VenusX2 && g_stage_py >= VenusY&&g_stage_py <= VenusY2&&g_Earth_clear == false)
	{
		Font::StrDraw(L"�O�̃X�e�[�W�����ׂăN���A���Ă��Ă�", 32, 32, 32, red);
	}
	//����
	else if (g_stage_px >= VenusX && g_stage_px <= VenusX2 && g_stage_py >= VenusY&&g_stage_py <= VenusY2&&g_Earth_clear == true)
	{
		Font::StrDraw(L"�����X�e�[�W", 32, 32, 32, c);
	}	
	//�������N���A���Ă��Ȃ��ꍇ���̃��b�Z�[�W��\������
	if (g_stage_px >= MercuryX && g_stage_px <= MercuryX2 && g_stage_py >= MercuryY&&g_stage_py <= MercuryY2&&g_Venus_clear==false)
	{
		Font::StrDraw(L"�O�̃X�e�[�W�����ׂăN���A���Ă��Ă�", 32, 32, 32, red);
	}
	//����
	else if (g_stage_px >= MercuryX && g_stage_px <= MercuryX2 && g_stage_py >= MercuryY&&g_stage_py <= MercuryY2&&g_Venus_clear == true)
	{
		Font::StrDraw(L"�����X�e�[�W", 32, 32, 32, c);
	}
	//�������N���A���Ă��Ȃ��ꍇ���̃��b�Z�[�W��\������
	if (g_stage_px >= SunX && g_stage_px <= SunX2 && g_stage_py >= SunY&&g_stage_py <= SunY2&&g_Mercury_clear == false)
	{
		Font::StrDraw(L"�O�̃X�e�[�W�����ׂăN���A���Ă��Ă�", 32, 32, 32, red);
	}
	//���z
	else if (g_stage_px >= SunX && g_stage_px <= SunX2 && g_stage_py >= SunY&&g_stage_py <= SunY2&&g_Mercury_clear == true)
	{
		Font::StrDraw(L"���z�X�e�[�W", 32, 32, 32, c);
	}
	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top    = 64.0f * g_posture;
	src.m_left   =  0.0f + (AniData[m_ani_frame] * 64);
	src.m_right  = 64.0f + (AniData[m_ani_frame] * 64);
	src.m_bottom = src.m_top + 64.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top    =  0.0f + g_stage_py;
	dst.m_left   = 80.0f + g_stage_px;
	dst.m_right  =  0.0f + g_stage_px;
	dst.m_bottom = 80.0f + g_stage_py;

	//�\��
	Draw::Draw(1, &src, &dst, c, 0.0f);
}
