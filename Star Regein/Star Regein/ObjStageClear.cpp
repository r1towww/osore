//�g�p����w�b�_�[
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\SceneManager.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "ObjStageClear.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;


//�C�j�V�����C�Y
void CObjStageClear::Init()
{
	m_keytime = 0;	//�L�[���̓^�C���̏�����
}

//�A�N�V����
void CObjStageClear::Action()
{
	//�V�[���Ɉڂ��Ă����ۂ̃L�[���̓^�C������
	if (m_keytime >= 50)
		m_keytime = 50;	//�^�C����50�ɂȂ����ہA50�Ŏ~�߂�
	else
		m_keytime++;	//�L�[���̓^�C���𑝂₷

	if (Input::GetVKey('Z') == true && m_keytime == TIMELIMIT)	//�L�[���̓^�C�������ɒB�����ꍇ�A�L�[���͂�������
	{
		g_stage_clear = false;
		Scene::SetScene(new CSceneStageChoice());
	}
}

//�h���[
void CObjStageClear::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	float y[4] = { 1.0f,1.0f,0.0f,1.0f };
	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu
	if (g_stage == EarthStar)
	{
		//�n��------------------------------------
		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 790.0f;
		src.m_bottom = 590.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 600.0f;

		//�\��
		Draw::Draw(16, &src, &dst, c, 0.0f);
		//----------------------------------------
	}
	if (g_stage == VenusTaurus)
	{
		//�����i�������j--------------------------
		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 790.0f;
		src.m_bottom = 590.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 600.0f;

		//�\��
		Draw::Draw(16, &src, &dst, c, 0.0f);
		//---------------------------------------
	}
	if (g_stage == VenusLibra)
	{
		//�����i�������j--------------------------
		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 790.0f;
		src.m_bottom = 590.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 600.0f;

		//�\��
		Draw::Draw(18, &src, &dst, c, 0.0f);
		//---------------------------------------
	}

	Font::StrDraw(L"STAGE CLEAR", 120,150, 100,y);

	Font::StrDraw(L"Z�L�[�ŃX�e�[�W�I���֖߂�", 200, 510, 32, y);

}
