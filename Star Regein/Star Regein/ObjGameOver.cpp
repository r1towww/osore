//�g�p����w�b�_�[
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\SceneManager.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "ObjGameOver.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;


//�C�j�V�����C�Y
void CObjGameOver::Init()
{
	m_keytime = 0;	//�L�[���̓^�C���̏�����
}

//�A�N�V����
void CObjGameOver::Action()
{

}

//�h���[
void CObjGameOver::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	float bl [4] = { 1.0f,0.0f,0.0f,1.0f };
	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	//�w�i------------------------------------
	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 800.0f;
	src.m_bottom = 600.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;

	//�\��
	Draw::Draw(1, &src, &dst, c, 0.0f);
	//----------------------------------------

	Font::StrDraw(L"GAME OVER", 160, 150, 100, bl);

	//�V�[���Ɉڂ��Ă����ۂ̃L�[���̓^�C������
	if (m_keytime >= 50)
		m_keytime = 50;	//�^�C����50�ɂȂ����ہA50�Ŏ~�߂�
	else
		m_keytime++;	//�L�[���̓^�C���𑝂₷

	//�E�L�[����
	if (Input::GetVKey(VK_RIGHT) == true)
	{
		m_Right = true;
		m_Left = false;
	}
	//���L�[����
	if (Input::GetVKey(VK_LEFT) == true)
	{
		m_Right = false;
		m_Left = true;
	}
	//�E�L�[���͂Ńt�H���g�؂�ւ�
	if (m_Right == true)
	{
		Font::StrDraw(L"���X�e�[�W�I���֖߂�", 400, 400, 32, c);
		//���̏�Ԃły�L�[�ŃX�e�[�W�I����
		if ((Input::GetVKey('Z') == true || Input::GetVKey(VK_RETURN) == true) && m_keytime == TIMELIMIT)	//�L�[���̓^�C�������ɒB�����ꍇ�A�L�[���͂�������
		{
			Scene::SetScene(new CSceneStageChoice());
		}

	}
	else
	{
		//�����łȂ�������ŏ��̃t�H���g��\������
		Font::StrDraw(L"�X�e�[�W�I���֖߂�", 400, 400, 32, c);
	}
	//���L�[���͂Ńt�H���g�؂�ւ�
	if (m_Left == true)
	{
		Font::StrDraw(L"���^�C�g���ɖ߂�", 100, 400, 32, c);
		//���̏�Ԃły�L�[�Ń^�C�g����
		if ((Input::GetVKey('Z') == true||Input::GetVKey(VK_RETURN)==true) && m_keytime == TIMELIMIT)	//�L�[���̓^�C�������ɒB�����ꍇ�A�L�[���͂�������
		{
			Scene::SetScene(new CSceneTitle());
		}

	}
	else
	{
		//�����łȂ�������ŏ��̃t�H���g��\������
		Font::StrDraw(L"�^�C�g���ɖ߂�", 100, 400, 32, c);
	}

}
