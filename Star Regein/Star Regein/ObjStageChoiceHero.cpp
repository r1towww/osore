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
	//�ړ��x�N�g��
	m_vx = 0.0f;		
	m_vy = 0.0f;
	m_f = false;
	//�����p��
	g_posture = HERO_DOWN;

	m_ani_time = 0;
	m_ani_frame = 1;
	m_time = false;
	m_alpha = ALPHAORIGIN;

	//�X�e�[�W�J�n��F��������
	m_stage_start = true;
	m_Tra = 1.0f;

}


//�A�N�V����
void ObjStageChoiceHero::Action()
{
	//�V�[���؂�ւ��p
	if (m_alpha >= 1.0f)
	{
		m_alpha = 1.0f;
	}
	else
	{
		m_alpha += 0.03f;
	}

	g_gemini_check = false;
	//�����I�����ɓ��͐��䂷��
	if(g_stage!=Space)
	{
		return;
	}

	//�`���[�g���A���t���O�A���쐧��p�t���O�������Ă��Ȃ��Ƃ������悤�ɂ���
	if (g_tutorial_flag == true || g_move_stop_flag == true )
	{
		m_vx = 0.0f;
		m_vy = 0.0f;
		return;
	}

	//��l���@���̈�O�s���Ȃ�����
	if (g_stage_px + 80.0f > 800.0f)
	{
		g_stage_px = 800.0f - 80.0f;
	}
	if (g_stage_py + 80.0f > 600.0f)
	{
		g_stage_py = 600.0f - 80.0f;
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
	if ((Input::GetVKey('X')))
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
	//�X�e�[�W�I��(����)�I�u�W�F�N�g�쐬
	CObjStarChoice* star = new CObjStarChoice();

	CObjTextBox* text = (CObjTextBox*)Objs::GetObj(OBJ_TEXTBOX);

	//�L�[���͂𒷉����ŏo���Ȃ��悤�ɂ���
	if (Input::GetVKey('Z') == false && Input::GetVKey(VK_RETURN) == false || text != nullptr)
	{
		g_key_flag = true;	//��������I���ɂ���
	}

	//Q�L�[�����͂��ꂽ�ꍇ
	if (Input::GetVKey('Q'))
	{
		if (m_f == true)
		{
			Audio::Start(1);	//�G�t�F�N�g����炷
								//�x�N�g�����O�ɂ���
			m_vx = 0.0f;
			m_vy = 0.0f;
			//Menu�I�u�W�F�N�g���쐬
			CObjMenu *objmenu = new CObjMenu();
			Objs::InsertObj(objmenu, OBJ_MENU, 150);
			g_move_stop_flag = true;	//�X�g�b�v�t���O���I��

			m_f = false;
		}
	}
	else
	{
		m_f = true;
	}

	// Z�L�[����͂��A�L�[�t���O���I���̎��Ɏ��s
	if ((Input::GetVKey('Z') == true && g_key_flag == true || Input::GetVKey(VK_RETURN) == true) && g_key_flag == true)
	{
		//�n����
		if (g_stage_px >= EarthX && g_stage_px + 80.0f <= EarthX2 && g_stage_py >= EarthY&&g_stage_py + 80.0f <= EarthY2)
		{
			//���O�V�[������Z�L�[���������ł���������Ȃ��悤�ɁA
			//���̃V�[���ɓ����Ĉ�x�������ĂȂ���ԂɈڍs���Ȃ���
			//���s�o���Ȃ��悤�ɂ��Ă���B
			g_stage = Earth;	//�X�e�[�W�̒l��n���ɕύX
			Audio::Start(1);
			g_key_flag = false;	//�L�[�t���O���I�t
			//�X�e�[�W�I��(����)�I�u�W�F�N�g�쐬
			CObjStarChoice* star = new CObjStarChoice();

			Objs::InsertObj(star, OBJ_STARCHOICE, 20);
		}
		//������
		else if (g_stage_px >= VenusX && g_stage_px + 80.0f <= VenusX2 && g_stage_py >= VenusY&&g_stage_py + 80.0f <= VenusY2)
		{
			if (g_Earth_clear == true)
			{
				//���O�V�[������Z�L�[���������ł���������Ȃ��悤�ɁA
				//���̃V�[���ɓ����Ĉ�x�������ĂȂ���ԂɈڍs���Ȃ���
				//���s�o���Ȃ��悤�ɂ��Ă���B
				//�����ɐݒ�
				g_stage = Venus;
				Audio::Start(1);
				g_key_flag = false;	//�L�[�t���O���I�t
				//�X�e�[�W�I��(����)�I�u�W�F�N�g�쐬
				Objs::InsertObj(star, OBJ_STARCHOICE, 20);
			}
		}
		//������
		else if (g_stage_px >= MercuryX && g_stage_px + 80.0f <= MercuryX2 && g_stage_py >= MercuryY&&g_stage_py + 80.0f <= MercuryY2)
		{
			if (g_Venus_clear == true)
			{
				//	//���O�V�[������Z�L�[���������ł���������Ȃ��悤�ɁA
				//	//���̃V�[���ɓ����Ĉ�x�������ĂȂ���ԂɈڍs���Ȃ���
				//	//���s�o���Ȃ��悤�ɂ��Ă���B
				//	//�����ɐݒ�
				g_stage = Mercury;
				Audio::Start(1);
				g_key_flag = false;	//�L�[�t���O���I�t
				//�X�e�[�W�I��(����)�I�u�W�F�N�g�쐬
				Objs::InsertObj(star, OBJ_STARCHOICE, 20);
			}
		}
		//���z��
		else if (g_stage_px >= SunX && g_stage_px + 80.0f <= SunX2 && g_stage_py >= SunY&&g_stage_py + 80.0f <= SunY2)
		{
			if (g_Mercury_clear == true)
			{
				Audio::Start(1);
				//���z�ɐݒ�
				g_stage = Sun;
				g_key_flag = false;	//�L�[�t���O���I�t
				//�X�e�[�W�I��(����)�I�u�W�F�N�g�쐬
				Objs::InsertObj(star, OBJ_STARCHOICE, 20);
			}
		}
		//���ъm�F��
		else if (g_stage_px >= 550 && g_stage_px <= 700 && g_stage_py >= 400&&g_stage_py  <= 550)
		{
			g_stage = Performance;
			Audio::Start(1);
			g_key_flag = false;	//�L�[�t���O���I�t

			//���уI�u�W�F�N�g�쐬
			CObjPerformanceRoom* per = new CObjPerformanceRoom();
			Objs::InsertObj(per, OBJ_PERFORMANCE_ROOM, 20);

		}
		//�V���[�g�J�b�g
		else if (g_stage_px >= 50 && g_stage_px <= 100 && g_stage_py >= 50 && g_stage_py <= 100)
		{
			Audio::Start(1);

			g_key_flag = false;	//�L�[�t���O���I�t
			g_Earth_clear = true;	//�n��	
			g_Venus_clear = true;	//����
			g_Mercury_clear = true;	//����
			g_Sun_clear = true;	//���z

			g_Taurus_clear = true;	//������	
			g_Libra_clear = true;	//�V����
			g_Gemini_clear = true;	//�o�q��
			g_Virgo_clear = true;	//������
			g_Leo_clear = true;	//���q��
			g_Boss_Spawn = true;
			g_Taurus = true;	//������	
			g_Libra = true;	//�V����
			g_Gemini = true;	//�o�q��
			g_Virgo = true;	//������
			g_Leo = true;	//���q��

		}

	}

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
	if (g_stage_px >= EarthX && g_stage_px + 80.0f <= EarthX2 && g_stage_py >= EarthY&&g_stage_py + 80.0f <= EarthY2)
	{
		if (g_Sun_clear == true)
		{
			Font::StrDraw(L"�n���X�e�[�W", 32, 32, 32, red);
		}
		else
			Font::StrDraw(L"�n���X�e�[�W", 32, 32, 32, c);
	}
	
	//�n�����N���A���Ă��Ȃ��ꍇ���̃��b�Z�[�W��\������
	if (g_stage_px >= VenusX && g_stage_px + 80.0f <= VenusX2 && g_stage_py >= VenusY&&g_stage_py + 80.0f <= VenusY2&&g_Earth_clear == false)
	{
		Font::StrDraw(L"�O�̃X�e�[�W�����ׂăN���A���Ă��Ă�", 32, 32, 28, red);
	}
	//����
	else if (g_stage_px >= VenusX && g_stage_px + 80.0f <= VenusX2 && g_stage_py >= VenusY&&g_stage_py + 80.0f <= VenusY2&&g_Earth_clear == true)
	{
		Font::StrDraw(L"�����X�e�[�W", 32, 32, 32, c);
	}	
	//�������N���A���Ă��Ȃ��ꍇ���̃��b�Z�[�W��\������
	if (g_stage_px >= MercuryX && g_stage_px + 80.0f <= MercuryX2 && g_stage_py >= MercuryY&&g_stage_py + 80.0f <= MercuryY2&&g_Venus_clear==false)
	{
		Font::StrDraw(L"�O�̃X�e�[�W�����ׂăN���A���Ă��Ă�", 32, 32, 28, red);
	}
	//����
	else if (g_stage_px >= MercuryX && g_stage_px + 80.0f <= MercuryX2 && g_stage_py >= MercuryY&&g_stage_py + 80.0f <= MercuryY2&&g_Venus_clear == true)
	{
		Font::StrDraw(L"�����X�e�[�W", 32, 32, 32, c);
	}
	//�������N���A���Ă��Ȃ��ꍇ���̃��b�Z�[�W��\������
	if (g_stage_px >= SunX && g_stage_px + 80.0f <= SunX2 && g_stage_py >= SunY&&g_stage_py + 80.0f <= SunY2&&g_Mercury_clear == false)
	{
		Font::StrDraw(L"�O�̃X�e�[�W�����ׂăN���A���Ă��Ă�", 32, 32, 28, red);
	}
	//���z
	else if (g_stage_px >= SunX && g_stage_px + 80.0f <= SunX2 && g_stage_py >= SunY&&g_stage_py + 80.0f <= SunY2&&g_Mercury_clear == true)
	{
		Font::StrDraw(L"���z�X�e�[�W", 32, 32, 32, c);
	}
	if (g_stage_px >= 550 && g_stage_px <= 700 && g_stage_py >= 400&&g_stage_py  <= 550)
	{
		Font::StrDraw(L"����", 32, 32, 32, c);
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
	float Stage[4] = { 1.0f,1.0f,1.0f,m_Tra };

	//�V�[���ڍs�p
	if (m_stage_start == true)
	{

		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 350.0f;
		src.m_right = 400.0f;
		src.m_bottom = 50.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 600.0f;
	
		m_Tra -= 0.03f;
		if (m_Tra <= 0.0f)
		{
			m_stage_start = false;
		}

		Draw::Draw(9, &src, &dst, Stage, 0.0f);
	}

}
