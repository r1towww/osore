//�g�p����w�b�_�[
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\SceneManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjTitle.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;

							//�C�j�V�����C�Y
void CObjED::Init()
{
	m_y = 0.0;
}

//�A�N�V����
void CObjED::Action()
{
	float p[4] = { 1.0f,1.0f,1.0f,1.0f };

	m_y--;

	//�G���^�[�L�[�ő�����@�\
	if (Input::GetVKey(VK_RETURN) == true)
	{
		m_y -= 10;
	}

	else
	{
		m_y -= 0.8f;
	}
	Font::StrDraw(L"END GAME"                  , GAME_CLEAR_X+25, GAME_CLEAR_Y + m_y   , GAME_CLEAR_FONT_SIZE+30, p);
	Font::StrDraw(L"�Q�[���� STAR REGEIN"      , GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 100, GAME_CLEAR_FONT_SIZE, p);
	Font::StrDraw(L"�Q�[���쐬��"              , GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 150, GAME_CLEAR_FONT_SIZE, p);
	Font::StrDraw(L"���[�_�[     ���� �\��"    , GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 200, GAME_CLEAR_FONT_SIZE, p);
	Font::StrDraw(L"�v�����i�[   ����  �@"     , GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 250, GAME_CLEAR_FONT_SIZE, p);
	Font::StrDraw(L"�v���O���}�[ �c�� ���l"    , GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 300, GAME_CLEAR_FONT_SIZE, p);
	Font::StrDraw(L"�v���O���}�[ �ؑ� �B�l"    , GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 350, GAME_CLEAR_FONT_SIZE, p);
	Font::StrDraw(L"�v���O���}�[ �ےn�J �L��"  , GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 400, GAME_CLEAR_FONT_SIZE, p);
	if (m_y <= -500)
	{

	}

}

//�h���[
void CObjED::Draw()
{

}
