//�g�p����w�b�_�[
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\SceneManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjTitle.h"

#define CLEARF	true

//�e�f���E�����̃N���A��
bool g_Earth_clear= CLEARF;	//�n��	
bool g_Venus_clear= CLEARF;	//����
bool g_Mercury_clear= CLEARF;	//����
bool g_Sun_clear= CLEARF;	//���z

bool g_Taurus_clear= CLEARF;	//������	
bool g_Libra_clear= CLEARF;	//�V����
bool g_Gemini_clear= CLEARF;	//�o�q��
bool g_Virgo_clear= CLEARF;	//������
bool g_Leo_clear= CLEARF;	//���q��

bool g_geminiattack_check = false;
bool g_gemini_bullet_check = false;
bool g_gemini_move = false;
bool g_gemini_check = false;
bool g_tutorial_flag = false;
bool g_move_stop_flag = false;

//�g�p����l�[���X�y�[�X
using namespace GameL;
/*		Planet�񋓌^
	Earth,			//�n��			0
	EarthStar,		//�n��			1
	Venus,			//����			2
	VenusTaurus,	//�����i�������j3
	VenusLibra,		//�����i�V�����j4
	Mercury,		//����			5
	MercuryGemini,	//�����i�o�q���j6
	MercuryVirgo,	//�����i�������j7
	Sun,			//���z			8
	SunLeo,			//���z�i���q���j9
	Space,			//�X�e�[�W�I��	10
	* �X�e�[�W�I���̍ەύX���� *
*/
int g_stage = Space;	//�X�e�[�W�̒l�̏�����
//�e�����̎擾���
bool g_Taurus = CLEARF;	//������	
bool g_Libra  = CLEARF;	//�V����
bool g_Gemini = CLEARF;	//�o�q��
bool g_Virgo  = CLEARF;	//������
bool g_Leo    = CLEARF;	//���q��
bool g_key_flag = false;	//�L�[���͐���t���O

//�X�e�[�W�I����ʂ̎�l���̈ʒu�i�����ʒu�j
float g_stage_px = 50;  //�X�e�[�W�I�����̈ʒuX
float g_stage_py = 500;  //�X�e�[�W�I�����̈ʒuY

//�C�j�V�����C�Y
void CObjTitle::Init()
{
	m_up=false;
	m_down=false;
	m_start=false;
	m_end=false;

	m_key_flag =true;	//�L�[����t���O
}

//�A�N�V����
void CObjTitle::Action()
{
	 g_Earth_clear = true;	//�n��	
	 g_Venus_clear = true;	//����
	 g_Mercury_clear = true;	//����
	 g_Sun_clear = true;	//���z

	 g_Taurus_clear = true;	//������	
	 g_Libra_clear = true;	//�V����
	 g_Gemini_clear = true;	//�o�q��
	 g_Virgo_clear = true;	//������
	 g_Leo_clear = true;	//���q��

}

//�h���[
void CObjTitle::Draw()
{
	float c[4] = { 1,1,1,1 };
	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 800.0f;
	src.m_bottom = 600.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f;	//�`��ɑ΂��ăX�N���[���̉e����������
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;

	//�`��
	Draw::Draw(1, &src, &dst, c, 0.0f);

	//��L�[���������Ƃ�
	if (Input::GetVKey(VK_UP) == true)
	{
		if (m_key_flag == true)
		{
			Audio::Start(1);
			m_key_flag = false;
			m_up = true;
			m_down = false;
		}

	}
	//���L�[���������Ƃ�
	else if (Input::GetVKey(VK_DOWN) == true)
	{
		if (m_key_flag == true)
		{
			Audio::Start(1);
			m_key_flag = false;
			m_down = true;
			m_up = false;
		}
	}
	else
		m_key_flag = true;

	//�Q�[���J�n
	if (m_start == true)
	{
		//�V�[���J�ډ�
		Audio::Start(2);
		Sleep(500);
		Scene::SetScene(new CSceneStageChoice());
	}
	//�Q�[���I��
	if (m_end == true)
	{
		//�V�[���J�ډ�
		Audio::Start(1);
		Sleep(500);
		exit(4);
	}
	//�J�[�\��������
	if (m_up == true)
	{
		Font::StrDraw(L"���Q�[���X�^�[�g", 280, 300, 32, c);
		Font::StrDraw(L"�Q�[���I��", 280, 340, 32, c);
		//�y�L�[�Ŏn�߂�
		if (Input::GetVKey('Z') == true || Input::GetVKey(VK_RETURN) == true)
		{
			m_start = true;
		}

	}
	else if (m_down == true)
	{
		Font::StrDraw(L"�Q�[���X�^�[�g", 280, 300, 32, c);
		Font::StrDraw(L"���Q�[���I��", 280, 340, 32, c);
		//Z�L�[�ŏI���
		if (Input::GetVKey('Z') == true || Input::GetVKey(VK_RETURN) == true)
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
