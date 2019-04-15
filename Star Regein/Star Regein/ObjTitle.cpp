//�g�p����w�b�_�[
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\SceneManager.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "ObjTitle.h"
//�e�f���E�����̃N���A��
bool g_Earth_clear=false;	//�n��	
bool g_Venus_clear=false;	//����
bool g_Mercury_clear=false;	//����
bool g_Sun_clear=false;	//���z

bool g_Taurus_clear=false;	//������	
bool g_Libra_clear=false;	//�V����
bool g_Gemini_clear=false;	//�o�q��
bool g_Virgo_clear=false;	//������
bool g_Leo_clear=false;	//���q��

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
bool g_Taurus = true;	//������	
bool g_Libra  = true;	//�V����
bool g_Gemini = true;	//�o�q��
bool g_Virgo  = true;	//������
bool g_Leo    = true;	//���q��
bool g_key_flag = false;	//�L�[���͐���t���O

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
