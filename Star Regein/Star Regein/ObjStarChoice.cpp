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
	m_Tra1 = 0.5f;
	m_Tra2 = 0.5f;
	m_Tra3 = 0.5f;
	
	//�L�[���͗p�^�C���̏�����
	m_keytime = 0;

}

//�A�N�V����
void CObjStarChoice::Action()
{
	//�f�����I������A�����I����ʂւ̈ڍs�̍�
	if (g_stage == Earth || g_stage == Venus || g_stage == Mercury || g_stage == Sun)
	{
		//�摜���\�����ꂽ�ۂ́A�L�[���̓^�C������
		if (m_keytime >= 50)
			m_keytime = 50;	//�^�C����50�ɂȂ����ہA50�Ŏ~�߂�
		else
			m_keytime++;	//�L�[���̓^�C���𑝂₷
	}
	else
	{
		m_keytime = 0;	//����ȊO�̏ꍇ�A�L�[���̓^�C����0�ɂ���
	}

	//�����I�����n���܂��͑��z�̏ꍇ�i������1�̏ꍇ�j
	if (g_stage == Earth || g_stage == Sun)
	{
		//��L�[����͂��đI��
		if (Input::GetVKey(VK_UP) == true)
		{
			m_direction = UP;	//UP���Z�b�g
		}
		//���L�[����͂��đI��
		if (Input::GetVKey(VK_DOWN) == true)
		{
			m_direction = DOWN;	//DOWN���Z�b�g
		}
	}
	else		//������2����ꍇ
	{	
		//���L�[����͂��đI��
		if (Input::GetVKey(VK_DOWN) == true)
		{
			m_direction = DOWN;	//DOWN���Z�b�g
		}
		//�E�L�[����͂��đI��
		if (Input::GetVKey(VK_RIGHT) == true)
		{
			m_direction = RIGHT;//RIGHT���Z�b�g
		}
		//���L�[����͂��đI��
		else if (Input::GetVKey(VK_LEFT) == true)
		{
			m_direction = LEFT;	//LEFT���Z�b�g
		}
	}

	//�X�e�[�W�I����ʂ̏����擾
	CObjStageChoice* stagec = (CObjStageChoice*)Objs::GetObj(OBJ_STAGECHOICE);
	
	//���̂ق��𖾂邭���ĉE�̂ق����Â�����(1���������ۂ�UP��LEFT�Ɠ��l�Ɉ���)
	if (m_direction == LEFT || m_direction == UP)
	{
		//���ߗ��ύX
		m_Tra1 = 1.0f;
		m_Tra2 = 0.5f;
		m_Tra3 = 0.5f;
		//�L�[���̓^�C�������ɒB�����ꍇ�A�L�[���͂�������
		if (Input::GetVKey('Z') == true && m_keytime == TIMELIMIT)		
		{
			if (g_stage == Earth)
			{
				//�X�e�[�W��n���ɐݒ�
				g_stage = EarthStar;
				Scene::SetScene(new CSceneEarth());
			}
			else if (g_stage == Venus)
			{
				//�X�e�[�W�����������ɐݒ�
				g_stage = VenusTaurus;
				Scene::SetScene(new CSceneVenusTaurus());
			}
			else if (g_stage == Mercury)
			{
				//�X�e�[�W��o�q���ɐݒ�
				g_stage = MercuryGemini;
				Scene::SetScene(new CSceneVenusTaurus());
			}
		}
	}

	//�E�̂ق��̂ق��𖾂邭���č��̂ق����Â�����
	else if (m_direction == RIGHT)
	{
		//���ߗ��ύX
		m_Tra2 = 1.0f;
		m_Tra1 = 0.5f;
		m_Tra3 = 0.5f;
		//�L�[���̓^�C�������ɒB�����ꍇ�A�L�[���͂�������
		if (Input::GetVKey('Z') == true && m_keytime == TIMELIMIT)		
		{
			if (g_stage == Venus)
			{
				//�X�e�[�W���Ă�т���ɐݒ�
				g_stage = VenusLibra;
				Scene::SetScene(new CSceneVenusLibra());
			}
			else if (g_stage == Mercury)
			{
				//�X�e�[�W���������ɐݒ�
				g_stage = MercuryVirgo;
				Scene::SetScene(new CSceneEarth());
			}
		}
	}
	//���̃R�}���h�̖��邳��ύX
	else if (m_direction == DOWN)		
	{
		//���ߗ��ύX
		m_Tra3 = 1.0f;
		m_Tra2 = 0.5f;
		m_Tra1 = 0.5f;
		//�L�[���̓^�C�������ɒB�����ꍇ�A�L�[���͂�������
		if (Input::GetVKey('Z') == true && m_keytime == TIMELIMIT)
		{
			g_stage = Space;	//�X�e�[�W��Space�ɐݒ�
			stagec->SetAlpha(ALPHAORIGIN);	//�A���t�@�l�����ɖ߂�
		}
	}
}

//�h���[
void CObjStarChoice::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };	//�W���J���[
	//���̐���
	float left[4]  = { 1.0f,1.0f,1.0f,m_Tra1 };
	//�E�̐���
	float right[4] = { 1.0f,1.0f,1.0f,m_Tra2 };
	//���̃R�}���h
	float down[4]  = { 1.0f,1.0f,1.0f,m_Tra3 };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu
	
	//�n���I�����ɕ\�������摜
	if (g_stage == Earth)
	{
		//�߂�R�}���h�\��
		Font::StrDraw(L"�߂�", BACK_POSX, BACK_POSY, BACK_FONTSIZE, down);

		//�n���I��p�̉摜
		//�؂���ʒu�̐ݒ�
		src.m_top    = 0.0f;
		src.m_left   = 0.0f;
		src.m_right  = 256.0f;
		src.m_bottom = 256.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top    = 150.0f;
		dst.m_left   = 300.0f;
		dst.m_right  = 510.0f;
		dst.m_bottom = 400.0f;
		//�\��
		Draw::Draw(9, &src, &dst, left, 0.0f);
	}
	//�����I�����ɕ\�������摜---------------------------------------------------------
	else if (g_stage == Venus)
	{
		//�߂�R�}���h�\��
		Font::StrDraw(L"�߂�", BACK_POSX, BACK_POSY, BACK_FONTSIZE, down);

		//���������̉摜-----------------------------------------------------------------
		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 870.0f;
		src.m_bottom = 600.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top = 150.0f;
		dst.m_left = 100.0f;
		dst.m_right = 350.0f;
		dst.m_bottom = 400.0f;
		//�\��
		Draw::Draw(7, &src, &dst, left, 0.0f);
		//-------------------------------------------------------------------------------
		//�Ă�т��---------------------------------------------------------------------
		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 900.0f;
		src.m_bottom = 600.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top = 150.0f;
		dst.m_left = 430.0f;
		dst.m_right = 680.0f;
		dst.m_bottom = 400.0f;
		//�\��
		Draw::Draw(8, &src, &dst, right, 0.0f);
		//----------------------------------------------------------------------------------
	}
	//�����I�����ɕ\�������摜---------------------------------------------------------
	else if (g_stage == Mercury)
	{
		//�߂�R�}���h�\��
		Font::StrDraw(L"�߂�", 380, 500, 25, down);

		//�o�q���̉摜-----------------------------------------------------------------
		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 870.0f;
		src.m_right = 1700.0f;
		src.m_bottom = 600.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top = 150.0f;
		dst.m_left = 100.0f;
		dst.m_right = 350.0f;
		dst.m_bottom = 400.0f;
		//�\��
		Draw::Draw(7, &src, &dst, left, 0.0f);
		//-------------------------------------------------------------------------------
		//������---------------------------------------------------------------------
		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 1700.0f;
		src.m_right = 2620.0f;
		src.m_bottom = 600.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top = 150.0f;
		dst.m_left = 430.0f;
		dst.m_right = 680.0f;
		dst.m_bottom = 400.0f;
		//�\��
		Draw::Draw(8, &src, &dst, right, 0.0f);
		//----------------------------------------------------------------------------------
	}
	else
	{

	}
	


}
