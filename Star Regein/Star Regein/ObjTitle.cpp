//�g�p����w�b�_�[
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\SceneManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjTitle.h"

//�ʏ�v���C�̍ۂ� false
#define CLEARF	false


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
bool g_Boss_Spawn = CLEARF;

bool g_geminiattack_check = false;	
bool g_gemini_bullet_check = false;
bool g_gemini_move = false;
bool g_gemini_check = false;

bool g_tutorial_flag = false;	//��l���̓��͐���t���O
bool g_move_stop_flag = false;	//��l���̓��͐���t���O

int g_second = 0;		//�b
int g_minute = 0;		//��


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
float g_stage_px = 55;  //�X�e�[�W�I�����̈ʒuX
float g_stage_py = 420;  //�X�e�[�W�I�����̈ʒuY


float g_enemy_cnt = 0;//�G�̑����̃J�E���g�p�ϐ��̏�����
float g_kill_cnt = 0;	//�G�r�ŗp�ϐ��̏�����
bool g_no_damage = false;	//�m�[�_���[�W�N���A�p�ϐ��̏�����

//�C�j�V�����C�Y
void CObjTitle::Init()
{
	g_stage = Space;	//�X�e�[�W�l�̏�����
	m_start=false;
	m_end=false;
	m_time = true;
	m_Tra = 1.0f;
	m_key_flag =true;	//�L�[����t���O
	m_Allclear = false;
	m_f = true;
	g_move_stop_flag = false;
	m_Riset_f=false;
	m_cnt = false;
	m_RESET = false;
	m_LEFT = false;
	m_RIGHT = false;

}

//�A�N�V����
void CObjTitle::Action()
{
	//�`���[�g���A��
	if (g_Earth_BossKill == true)
	{
		//�f���N���A��
		g_Earth_clear = true;	//�n��	
		g_Venus_clear = false;	//����
		g_Mercury_clear = false;	//����
		g_Sun_clear = false;	//���z
		g_Taurus_clear = false;	//������	
		g_Libra_clear = false;	//�V����
		g_Gemini_clear = false;	//�o�q��
		g_Virgo_clear = false;	//������
		g_Leo_clear = false;	//���q��
		g_Boss_Spawn = false;
		//�X�L��
		g_Taurus = false;	//������	
		g_Libra = false;	//�V����
		g_Gemini = false;	//�o�q��
		g_Virgo = false;	//������
		g_Leo = false;	//���q��

	}
}

//�h���[
void CObjTitle::Draw()
{
	float c[4] = { 1,1,1,m_Tra };
	float t[4] = { 0,1,0,m_Tra };

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
	if(m_Allclear!=true)
		Draw::Draw(1, &src, &dst, c, 0.0f);
	else
		Draw::Draw(1, &src, &dst, t, 0.0f);

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 800.0f;
	src.m_bottom = 353.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 50.0f;	//�`��ɑ΂��ăX�N���[���̉e����������
	dst.m_left = 50.0f;
	dst.m_right =750.0f;
	dst.m_bottom = 350.0f;

	Draw::Draw(2, &src, &dst, c, 0.0f);

	//�^�C�g���ŃX�y�[�X+Z�L�[�Ń`�[�g�I��
	if (Input::GetVKey(VK_SPACE) == true && Input::GetVKey('Z') == true)
	{
		if (m_f == false)
		{
			if (m_Allclear == true)
				m_Allclear = false;
			else
				m_Allclear = true;

			m_f = true;
		}
	}
	else
	{
		m_f = false;
	}

	//��L�[���������Ƃ�
	if (Input::GetVKey(VK_UP) == true&&m_cnt!=0)
	{
		if (m_key_flag == true)
		{
			m_cnt--;
			Audio::Start(1);
			m_key_flag = false;
		}

	}
	//���L�[���������Ƃ�
	else if (Input::GetVKey(VK_DOWN) == true&&m_cnt!=2)
	{
		if (m_key_flag == true)
		{
			m_cnt++;
			Audio::Start(1);
			m_key_flag = false;
		}
	}
	else
		m_key_flag = true;

	//�`�[�g�t���O�I��
	if (m_Allclear == true)
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
		g_Boss_Spawn = true;
		g_Taurus = true;	//������	
		g_Libra = true;	//�V����
		g_Gemini = true;	//�o�q��
		g_Virgo = true;	//������
		g_Leo = true;	//���q��
	}
	//�Q�[���J�n
	if (m_start == true)
	{
		if (m_time == true)
		{
			Audio::Start(2);
			m_time = false;
		}
		m_Tra -= 0.03f;
		if (m_Tra <= 0.0f)
		{
			Scene::SetScene(new CSceneStageChoice());
		}
	}
	//�Q�[���I��
	if (m_end == true)
	{
		if (m_time == true)
		{
			Audio::Start(2);

			m_time = false;
		}
		m_Tra -= 0.03f;
		if (m_Tra <= 0.0f)
		{
			exit(4);
		}
	}
	//���Z�b�g���邩�ۂ��̃e�L�X�g�\��
	if (m_Riset_f == true)
	{
		if (m_time == true)
		{
			Audio::Start(2);

		}

		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 822.0f;
		src.m_bottom = 218.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top = 422.0f;
		dst.m_left = 10.0f;
		dst.m_right = 785.0f;
		dst.m_bottom = 600.0f;


		//�\��
		Draw::Draw(3, &src, &dst, c, 0.0f);
		Font::StrDraw(L"����܂ł̋L�^�����ׂă��Z�b�g���܂����H", 100, 450, 32, c);

		m_time = false;
	}
	else
	{
		m_time = true;
	}
	//���Z�b�g�t���O����
	if (m_Riset_f == true)
	{
		//����I����
		if (Input::GetVKey(VK_RIGHT))
		{
			m_RIGHT = true;
			m_LEFT = false;

			if (m_time == true)
			{
				Audio::Start(1);
				m_time = false;
			}
		}
		//�E��I����
		else if (Input::GetVKey(VK_LEFT))
		{
			m_RIGHT = false;
			m_LEFT = true;

			if(m_time==true)
			{
				Audio::Start(1);
				m_time = false;
			}
		}
		if (m_RIGHT == true)
		{
			Font::StrDraw(L"�͂�", 100, 500, 32, c);
			Font::StrDraw(L"��������", 250, 500, 32, c);
			if (Input::GetVKey('Z'))
			{
				Audio::Start(2);
				m_Riset_f = false;
				m_RIGHT = false;
				m_key_flag = false;
			}
		}
		else if (m_LEFT == true)
		{
			Font::StrDraw(L"���͂�", 100, 500, 32, c);
			Font::StrDraw(L"������", 250, 500, 32, c);
			if (Input::GetVKey('Z'))
			{
				Audio::Start(2);
				m_RESET = true;
				m_LEFT = false;
				m_Riset_f = false;
				m_key_flag = false;

			}

		}
		else
		{
			Font::StrDraw(L"�͂�", 100, 500, 32, c);
			Font::StrDraw(L"������", 250, 500, 32, c);
		}

	}
	else
	{
		m_time = true;
	}

	//���ׂĂ̋L�^�����Z�b�g������
	if (m_RESET == true)
	{
		g_Earth_clear = false;	//�n��	
		g_Venus_clear = false;	//����
		g_Mercury_clear = false;	//����
		g_Sun_clear = false;	//���z
		g_Taurus_clear = false;	//������	
		g_Libra_clear = false;	//�V����
		g_Gemini_clear = false;	//�o�q��
		g_Virgo_clear = false;	//������
		g_Leo_clear = false;	//���q��
		g_Boss_Spawn = false;
		g_Taurus = false;	//������	
		g_Libra = false;	//�V����
		g_Gemini = false;	//�o�q��
		g_Virgo = false;	//������
		g_Leo = false;	//���q��

		//�G�����ׂē|����------------------
		g_Taurus_Enemy_AllKill = false;
		g_Libra_Enemy_AllKill = false;
		g_Gemini_Enemy_AllKill = false;
		g_Viego_Enemy_AllKill = false;
		g_Leo_Enemy_AllKill = false;
		//�m�[�_���[�W�N���A----------------
		g_Taurus_NoDamage_Clear = false;
		g_Libra_NoDamage_Clear = false;
		g_Gemini_NoDamage_Clear = false;
		g_Viego_NoDamage_Clear = false;
		g_Leo_NoDamage_Clear = false;
		//���̑�
		g_All_Killcnt = 0;
		g_Death_cnt = 0;
		g_Taurus_Grade = 0;
		g_Libra_Grade = 0;
		g_Gemini_Grade = 0;
		g_Viego_Grade = 0;
		g_Leo_Grade = 0;

	//�V�[�N���b�g�n
		g_Tutorial_Clear = false; //�`���[�g���A���N���A
		g_Earth_BossKill = false; //���X�{�X��|����
		g_All_Skill_Get = false;  //���ׂẴX�L�����l��
		g_TRank = None;
		g_LiRank = None;		//�����N�Ǘ��p
		g_GRank = None;		//�����N�Ǘ��p
		g_VRank = None;		//�����N�Ǘ��p
		g_LeRank = None;		//�����N�Ǘ��p

	}
	//�J�[�\��������
	if (m_Riset_f != true)
	{
		if (m_cnt == 0)
		{
			Font::StrDraw(L"���Q�[���X�^�[�g", 300, 380, 32, c);
			Font::StrDraw(L"�Q�[���I��", 300, 420, 32, c);
			Font::StrDraw(L"����܂ł̋L�^�����Z�b�g����", 300, 450, 32, c);

			//�y�L�[�Ŏn�߂�
			if (Input::GetVKey('Z') == true || Input::GetVKey(VK_RETURN) == true)
			{
				m_start = true;
			}

		}
		else if (m_cnt == 1)
		{
			Font::StrDraw(L"�Q�[���X�^�[�g", 300, 380, 32, c);
			Font::StrDraw(L"���Q�[���I��", 300, 420, 32, c);
			Font::StrDraw(L"����܂ł̋L�^�����Z�b�g����", 300, 450, 32, c);

			//Z�L�[�ŏI���
			if (Input::GetVKey('Z') == true || Input::GetVKey(VK_RETURN) == true)
			{
				m_end = true;
			}


		}
		else if (m_cnt == 2)
		{
			Font::StrDraw(L"�Q�[���X�^�[�g", 300, 380, 32, c);
			Font::StrDraw(L"�Q�[���I��", 300, 420, 32, c);
			Font::StrDraw(L"������܂ł̋L�^�����Z�b�g����", 300, 450, 32, c);
			//Z�L�[�ŏI���
			if (Input::GetVKey('Z') == true || Input::GetVKey(VK_RETURN) == true)
			{
				m_Riset_f = true;
			}

		}
		//�n�߂͂��̏��
		else
		{
			Font::StrDraw(L"�Q�[���X�^�[�g", 300, 380, 32, c);
			Font::StrDraw(L"�Q�[���I��", 300, 420, 32, c);
			Font::StrDraw(L"����܂ł̋L�^�����Z�b�g����", 300, 450, 32, c);

		}
	}

}
