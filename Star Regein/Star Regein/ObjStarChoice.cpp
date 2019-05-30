//�g�p����w�b�_�[
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\SceneManager.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "ObjStarChoice.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;


//�C�j�V�����C�Y
void CObjStarChoice::Init()
{
	//�����x�̏�����
	m_Tra1 = 0.3f;
	m_Tra2 = 0.3f;
	m_Tra3 = 0.3f;
	m_Tra4 = 0.0f;
	m_Tra5 = 0.0f;
	if(g_stage == Earth || g_stage == Sun)
		m_direction = UP;	//�����I���ʒu�̏�����
	else if (g_stage == Venus || g_stage == Mercury)
		m_direction = LEFT;


	m_push_flag = false;
	//�L�[���͗p�t���O�̏�����
	m_key_flag = true;
}

//�A�N�V����
void CObjStarChoice::Action()
{
	float c[4] = { 1.0f,1.0f,0.0f,1.0f };	//�W���J���[

	//�X�e�[�W�I����ʂ̏����擾
	CObjStageChoice* stagec = (CObjStageChoice*)Objs::GetObj(OBJ_STAGECHOICE);
	ObjStageChoiceHero* stageh = (ObjStageChoiceHero*)Objs::GetObj(OBJ_STAGECHOICEHERO);

	//�f�����I������A�����I����ʂւ̈ڍs�̍�
	if (g_stage == Earth || g_stage == Venus || g_stage == Mercury || g_stage == Sun)
	{
			stagec->SetAlpha(ALPHAUNDER);	//�A���t�@�l�̕ύX
	}

	

	//�����I�����n���܂��͑��z�̏ꍇ�i������1�̏ꍇ�j
	if (g_stage == Earth || g_stage == Sun)
	{
		//��L�[����͂��đI��
		if (Input::GetVKey(VK_UP) == true)
		{
			if (m_key_flag == true)
			{
				Audio::Start(1);
				m_direction = UP;	//UP���Z�b�g
				m_key_flag = false;

			}
		}
		//���L�[����͂��đI��
		else if (Input::GetVKey(VK_DOWN) == true)
		{
			if (m_key_flag == true)
			{
				Audio::Start(1);
				m_direction = DOWN;	//DOWN���Z�b�g
				m_key_flag = false;
			}
		}
		else
			m_key_flag = true;
	}
	else if(g_stage == Venus || g_stage == Mercury)		//������2����ꍇ
	{	
		//���L�[����͂��đI��
		if (Input::GetVKey(VK_DOWN) == true)
		{
			if (m_key_flag == true)
			{
				Audio::Start(1);
				m_direction = DOWN;	//DOWN���Z�b�g
				m_key_flag = false;
			}
		}
		//�E�L�[����͂��đI��
		else if (Input::GetVKey(VK_RIGHT) == true)
		{
			if (m_key_flag == true)
			{
				Audio::Start(1);
				m_direction = RIGHT;//RIGHT���Z�b�g
				m_key_flag = false;
			}
		}
		//���L�[����͂��đI��
		else if (Input::GetVKey(VK_LEFT) == true)
		{
			if (m_key_flag == true)
			{
				Audio::Start(1);
				m_direction = LEFT;	//LEFT���Z�b�g
				m_key_flag = false;
			}
		}
		else
			m_key_flag = true;
	}

	//���̂ق��𖾂邭���ĉE�̂ق����Â�����(1���������ۂ�UP��LEFT�Ɠ��l�Ɉ���)
	//����I�����Ă����
	if (m_direction == LEFT || m_direction == UP)
	{
		//���ߗ��ύX
		m_Tra1 = 1.0f;
		m_Tra2 = 0.3f;
		m_Tra3 = 0.3f;
		m_Tra4 = 1.0f;
		//�L�[���̓^�C�������ɒB�����ꍇ�A�L�[���͂�������
		if (Input::GetVKey('Z') == true && g_key_flag == true || Input::GetVKey(VK_RETURN) == true && g_key_flag == true)
		{
			if (g_stage == Earth)
			{
				if (m_key_flag == true)
				{
					m_key_flag = false;
					//�V�[���J�ډ�
					Audio::Start(2);
					Sleep(500);
					//�X�e�[�W��n���ɐݒ�
					g_stage = EarthStar;
					m_push_flag = true;
				}
			}
			else if (g_stage == Venus)
			{
				if (m_key_flag == true)
				{
					m_key_flag = false;
					//�V�[���J�ډ�
					Audio::Start(2);
					Sleep(500);
					//�X�e�[�W���������ɐݒ�
					g_stage = VenusTaurus;
					m_push_flag = true;
				}
			}
			else if (g_stage == Mercury)
			{
				if (m_key_flag == true)
				{
					m_key_flag = false;
					//�V�[���J�ډ�
					Audio::Start(2);
					Sleep(500);
					//�X�e�[�W��o�q���ɐݒ�
					g_stage = MercuryGemini;
					m_push_flag = true;
				}
			}
			else if (g_stage == Sun)
			{
				if (m_key_flag == true)
				{
					m_key_flag = false;
					//�V�[���J�ډ�
					Audio::Start(2);
					Sleep(500);
					//�X�e�[�W��o�q���ɐݒ�
					g_stage = SunLeo;
					m_push_flag = true;
				}
			}
			else
				m_key_flag = true;
		}
	}

	//�E�̂ق��̂ق��𖾂邭���č��̂ق����Â�����
	//�E��I�����Ă����
	else if (m_direction == RIGHT)
	{
		//���ߗ��ύX
		m_Tra2 = 1.0f;
		m_Tra1 = 0.3f;
		m_Tra3 = 0.3f;
		m_Tra4 = 1.0f;
		//�L�[���̓^�C�������ɒB�����ꍇ�A�L�[���͂�������
		if ((Input::GetVKey('Z') == true && g_key_flag == true || Input::GetVKey(VK_RETURN) == true) && g_key_flag == true)
		{
			if (g_stage == Venus)
			{
				if (m_key_flag == true)
				{
					m_key_flag = false;
					//�V�[���J�ډ�
					Audio::Start(2);
					Sleep(500);
					//�X�e�[�W��V�����ɐݒ�
					g_stage = VenusLibra;
					m_push_flag = true;
				}
			}
			else if (g_stage == Mercury)
			{
				if (m_key_flag == true)
				{
					m_key_flag = false;
					//�V�[���J�ډ�
					Audio::Start(2);
					Sleep(500);
					//�X�e�[�W���������ɐݒ�
					g_stage = MercuryVirgo;
					m_push_flag = true;
				}
			}
			else
				m_key_flag = true;
		}
	}
	//���̃R�}���h�̖��邳��ύX
	//���i�߂�j��I�����Ă����
	else if (m_direction == DOWN)
	{
		//���ߗ��ύX
		m_Tra3 = 1.0f;
		m_Tra2 = 0.3f;
		m_Tra1 = 0.3f;
		m_Tra4 = 0.0f;
		//�L�[���̓t���O���I���̏ꍇ�A���͂�������
		if ((Input::GetVKey('Z') == true && g_key_flag == true 
		  || Input::GetVKey(VK_RETURN) == true) && g_key_flag == true)
		{
			if (m_key_flag == true)
			{
				g_key_flag = false;	//�L�[�t���O���I�t
				Audio::Start(1);
				g_stage = Space;	//�X�e�[�W��Space�ɐݒ�
				stagec->SetAlpha(ALPHAORIGIN);	//�A���t�@�l�����ɖ߂�
				this->SetStatus(false);
				
			}
		}
	}
	//�L�[���͂𒷉����ŏo���Ȃ��悤�ɂ���
	if (Input::GetVKey('Z') == false && Input::GetVKey(VK_RETURN) == false)
	{
		g_key_flag = true;	//��������I���ɂ���
	}
	
	//Z�L�[���������Ə��X�ɈÓ]���Ȃ���V�[���ڍs
	if (m_push_flag == true)
	{
		m_Tra5 += 0.03f;
		if (m_Tra5 > 1.0f)
		{
			if (g_stage == EarthStar)//�n��
			{
				Scene::SetScene(new CSceneEarth());
			}
			else if (g_stage == VenusTaurus)//��������
			{
				Scene::SetScene(new CSceneVenusTaurus());
			}
			else if (g_stage == VenusLibra)//�Ă�т��
			{
				Scene::SetScene(new CSceneVenusLibra());
			}
			else if (g_stage == MercuryGemini)//�ӂ�����
			{
				Scene::SetScene(new CSceneMercuryGemini());
			}
			else if (g_stage == MercuryVirgo)//���Ƃߍ�
			{
				Scene::SetScene(new CSceneMercuryVirgo());
			}
			else if (g_stage == SunLeo)//���z
			{
				Scene::SetScene(new CSceneSunLeo());
			}
		}

	}


}

//�h���[
void CObjStarChoice::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,0.0f,m_Tra1 };	//�W���J���[
	//�N���A�p
	float stage[4] = { 1.0f,1.0f,0.0f,m_Tra4 };
	float last_stage[4] = { 1.0f,0.0f,0.0f,m_Tra4 };

	float left_clear[4] = { 1.0f,1.0f,0.0f,m_Tra1 };
	float right_clear[4] = { 1.0f,1.0f,0.0f,m_Tra2 };

	float E[4] = { 1.0f,0.0f,0.0f,m_Tra1 };

	float stage_change[4] = { 1.0f,1.0f,1.0f,m_Tra5 }; //�X�e�[�W�ڍs

	//���̐���
	float left[4]  = { 1.0f,1.0f,1.0f,m_Tra1 };
	//�E�̐���
	float right[4] = { 1.0f,1.0f,1.0f,m_Tra2 };
	//���̃R�}���h
	float down[4]  = { 1.0f,1.0f,1.0f,m_Tra3 };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu
	
				//�߂�R�}���h�\��
	Font::StrDraw(L"�߂�", BACK_POSX, BACK_POSY, BACK_FONTSIZE, down);

	

	if (m_push_flag == true)
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

		Draw::Draw(9, &src, &dst, stage_change, 0.0f);
	}
	//�n���I�����ɕ\�������摜
	if (g_stage == Earth)
	{
		//�n���I��p�̉摜
		//�؂���ʒu�̐ݒ�
		src.m_top    = 0.0f;
		src.m_left   = 0.0f;
		src.m_right  = 300.0f;
		src.m_bottom = 200.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top    = 190.0f;
		dst.m_left   = 250.0f;
		dst.m_right  = 550.0f;
		dst.m_bottom = 390.0f;
		//�n���Ƀ��X�{�X��ݒu�����̂ŁA���z���N���A������킩��₷���\��������
		if (g_Sun_clear == true)
		{
			Font::StrDraw(L"�ŏI�X�e�[�W", 64, 64, 32, last_stage);

		}
		else
			//�J�[�\�������킹��ƍ���ɃX�e�[�W���\��
			Font::StrDraw(L"�`���[�g���A���X�e�[�W", 64, 64, 32, stage);

		//�\��(���z�N���A�Ō����ڕω�)
		if (g_Sun_clear == true)
		{
			Draw::Draw(7, &src, &dst, E, 0.0f);
		}
		else
			Draw::Draw(7, &src, &dst, left, 0.0f);

		if (g_Sun_clear == true)
		{
			Font::StrDraw(L"CLEAR�E�E�E?", 350, 400, 40, c);
		}
		else if (g_Earth_clear == true)
		{
			Font::StrDraw(L"CLEAR!", 350, 400, 40, c);
		}
	}
	//�����I�����ɕ\�������摜---------------------------------------------------------
	else if (g_stage == Venus)
	{

		//�������̉摜-----------------------------------------------------------------
		//�؂���ʒu�̐ݒ�
		src.m_top    = 0.0f;
		src.m_left   = 300.0f;
		src.m_right  = 600.0f;
		src.m_bottom = 200.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top    = 190.0f;
		dst.m_left   = 80.0f;
		dst.m_right  = 380.0f;
		dst.m_bottom = 390.0f;
		//�\��
		Draw::Draw(7, &src, &dst, left, 0.0f);
		//���������N���A�ŃN���A�\�L
		if (g_Taurus_clear == true)
		{
			Font::StrDraw(L"CLEAR!", 200, 400, 40, left_clear);
		}

		//-------------------------------------------------------------------------------
		//�V����---------------------------------------------------------------------
		//�؂���ʒu�̐ݒ�
		src.m_top    = 0.0f;
		src.m_left   = 600.0f;
		src.m_right  = 900.0f;
		src.m_bottom = 200.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top    = 190.0f;
		dst.m_left   = 400.0f;
		dst.m_right  = 700.0f;
		dst.m_bottom = 390.0f;

		//�\��
		Draw::Draw(7, &src, &dst, right, 0.0f);
		//�Ă�т���N���A�ŃN���A�\�L
		if (g_Libra_clear== true)
		{
			Font::StrDraw(L"CLEAR!", 500, 400, 40, right_clear);
		}

		//----------------------------------------------------------------------------------
		//�J�[�\�������킹��ƍ���ɃX�e�[�W���\��
		if (m_direction == LEFT)
		{
			Font::StrDraw(L"�������X�e�[�W", 64, 64, 32, stage);
		}
		else if (m_direction == RIGHT)
		{
			Font::StrDraw(L"�V�����X�e�[�W", 64, 64, 32, stage);
		}
	}
	//�����I�����ɕ\�������摜---------------------------------------------------------
	else if (g_stage == Mercury)
	{

		//�o�q���̉摜-----------------------------------------------------------------
		//�؂���ʒu�̐ݒ�
		src.m_top    = 0.0f;
		src.m_left   = 900.0f;
		src.m_right  = 1200.0f;
		src.m_bottom = 200.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top    = 190.0f;
		dst.m_left   = 90.0f;
		dst.m_right  = 390.0f;
		dst.m_bottom = 390.0f;
		//�\��
		Draw::Draw(7, &src, &dst, left, 0.0f);
		//�o�q���N���A�ŃN���A�\�L
		if (g_Gemini_clear == true)
		{
			Font::StrDraw(L"CLEAR!", 180, 400, 40, left_clear);
		}

		//-------------------------------------------------------------------------------
		//������---------------------------------------------------------------------
		//�؂���ʒu�̐ݒ�
		src.m_top    = 0.0f;
		src.m_left   = 1200.0f;
		src.m_right  = 1500.0f;
		src.m_bottom = 200.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top    = 190.0f;
		dst.m_left   = 420.0f;
		dst.m_right  = 720.0f;
		dst.m_bottom = 390.0f;
		//�\��
		Draw::Draw(7, &src, &dst, right, 0.0f);
		//�������N���A�ŃN���A�\�L
		if (g_Virgo_clear == true)
		{
			Font::StrDraw(L"CLEAR!", 500, 400, 40, right_clear);
		}
		//�J�[�\�������킹��ƍ���ɃX�e�[�W���\��
		if (m_direction == LEFT)
		{
			Font::StrDraw(L"�o�q���X�e�[�W", 64, 64, 32, stage);
		}
		else if (m_direction == RIGHT)
		{
			Font::StrDraw(L"�������X�e�[�W", 64, 64, 32, stage);
		}

		//----------------------------------------------------------------------------------
	}
	else if(g_stage == Sun)
	{
		//�؂���ʒu�̐ݒ�
		src.m_top    = 0.0f;
		src.m_left   = 1500.0f;
		src.m_right  = 1800.0f;
		src.m_bottom = 200.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top    = 190.0f;
		dst.m_left   = 250.0f;
		dst.m_right  = 550.0f;
		dst.m_bottom = 390.0f;
		//�\��
		Draw::Draw(7, &src, &dst, left, 0.0f);
		//���q���N���A�ŃN���A�\�L
		if (g_Sun_clear == true)
		{
			Font::StrDraw(L"CLEAR!", 350, 400, 40, c);
		}
		Font::StrDraw(L"���q���X�e�[�W", 64, 64, 32, stage);
	}
}
