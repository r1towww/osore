//�g�p����w�b�_�[
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\SceneManager.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "ObjTitle.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;
/*		Planet�񋓌^
	Earth			�n��			0
	VenusCow		�����i�������j	1
	MercuryGemini	�����i�o�q���j	2
	MercuryVirgo	�����i�������j	3
	SunLeo			���z�i���q���j	4
*/
int g_stage = VenusCow;	//�X�e�[�W�̒l�̏�����
int g_image_right = 0;
int g_image_reft  = 0;

//�C�j�V�����C�Y
void CObjTitle::Init()
{
	m_up=false;
	m_down=false;
	m_start=false;
	m_end=false;


}

//�A�N�V����
void CObjTitle::Action()
{

}

//�h���[
void CObjTitle::Draw()
{
	float c[4] = { 1,1,1,1 };
	//��L�[���������Ƃ�
	if (Input::GetVKey(VK_UP) == true)
	{
		m_up = true;
		m_down = false;

	}
	//���L�[���������Ƃ�
	if (Input::GetVKey(VK_DOWN) == true)
	{
		m_down = true;
		m_up = false;
	}
	//�Q�[���J�n
	if (m_start == true)
	{
		Scene::SetScene(new CSceneStageChoice());
	}
	//�Q�[���I��
	if (m_end == true)
	{
		exit(4);
	}
	//�J�[�\��������
	if (m_up == true)
	{
		Font::StrDraw(L"���Q�[���X�^�[�g", 280, 300, 32, c);
		Font::StrDraw(L"�Q�[���I��", 280, 340, 32, c);
		//�y�L�[�Ŏn�߂�
		if (Input::GetVKey('Z') == true)
		{
			m_start = true;
		}

	}
	else if (m_down == true)
	{
		Font::StrDraw(L"�Q�[���X�^�[�g", 280, 300, 32, c);
		Font::StrDraw(L"���Q�[���I��", 280, 340, 32, c);
		//Z�L�[�ŏI���
		if (Input::GetVKey('Z') == true)
		{
			m_end = true;
		}


	}
	//�n�߂͂��̏��
	else
	{
		Font::StrDraw(L"�Q�[���X�^�[�g", 280, 300, 32, c);
		Font::StrDraw(L"�Q�[���I��", 280, 340, 32, c);
	}


}
