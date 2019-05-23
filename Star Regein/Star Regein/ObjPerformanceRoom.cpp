//�g�p����w�b�_�[
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\SceneManager.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "ObjPerformanceRoom.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;
#define CLEAR_F false
bool g_new_Performance=false;
//�G�����ׂē|����------------------
bool g_Taurus_Enemy_AllKill= CLEAR_F;
bool g_Libra_Enemy_AllKill= CLEAR_F;
bool g_Gemini_Enemy_AllKill= CLEAR_F;
bool g_Viego_Enemy_AllKill= CLEAR_F;
bool g_Leo_Enemy_AllKill= CLEAR_F;
//�m�[�_���[�W�N���A----------------
bool g_Taurus_NoDamage_Clear= CLEAR_F;
bool g_Libra_NoDamage_Clear= CLEAR_F;
bool g_Gemini_NoDamage_Clear= CLEAR_F;
bool g_Viego_NoDamage_Clear= CLEAR_F;
bool g_Leo_NoDamage_Clear= CLEAR_F;
//���̑�
int g_All_Killcnt=0;
int g_Death_cnt=0;
int g_Taurus_Grade=0;
int g_Libra_Grade=0;
int g_Gemini_Grade=0;
int g_Viego_Grade=0;
int g_Leo_Grade=0;

//�V�[�N���b�g�n
bool g_Tutorial_Clear= CLEAR_F; //�`���[�g���A���N���A
bool g_Earth_BossKill = CLEAR_F; //���X�{�X��|����
bool g_All_Skill_Get= CLEAR_F;  //���ׂẴX�L�����l��
int g_TRank = None;
int g_LiRank = None;		//�����N�Ǘ��p
int g_GRank = None;		//�����N�Ǘ��p
int g_VRank = None;		//�����N�Ǘ��p
int g_LeRank = None;		//�����N�Ǘ��p



//�C�j�V�����C�Y
void CObjPerformanceRoom::Init()
{
	m_page = 0;
	m_next_f = false;
	m_back_f = false;
}

//�A�N�V����
void CObjPerformanceRoom::Action()
{
	g_new_Performance = false;
	//X�őI����ʂ֖߂�
	if (Input::GetVKey('X'))
	{
		g_stage = Space;
		this->SetStatus(false);    //���g�ɍ폜���߂��o��
	}
	//Z�L�[�Ŏ��̃y�[�W��
	if (Input::GetVKey('Z'))
	{
		if (m_next_f == true)
		{
			if (m_page >= 3)
			{
				;
			}
			else
			{
				Audio::Start(1);
				m_page++;
			}
			m_next_f = false;
		}
	}

	else
	{
		m_next_f = true;
	}
	//C�L�[�őO�̃y�[�W��
	if (Input::GetVKey('C'))
	{
		if (m_back_f == true)
		{
			if (m_page <= 0)
			{
				;
			}
			else
			{
				Audio::Start(1);
				m_page--;
			}
			m_back_f = false;
		}
	}
	else
	{
		m_back_f = true;
	}

}

//�h���[
void CObjPerformanceRoom::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	float a[4] = { 1.0f,1.0f,1.0f,0.8f };
	float y[4] = { 1.0f,1.0f,0.0f,1.0f };

	float cs[4] = { 0.0f,0.5f,1.0f,1.0f };
	float ca[4] = { 1.0f,0.0f,0.0f,1.0f	};
	float cb[4] = { 0.0f,1.0f,0.0f,1.0f };
	float cc[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu
	//�w�i�p�摜-----------------------------------
	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 822.0f;
	src.m_bottom = 218.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 100.0f;
	dst.m_left = 50.0f;
	dst.m_right = 750.0f;
	dst.m_bottom = 500.0f;
	//�\��
	Draw::Draw(40, &src, &dst, a, 0.0f);
	//----------------------------------------------
		wchar_t KILLCNT[128];	//�L���J�E���g�\���p
		wchar_t DEATHCNT[128];	//�f�X�J�E���g�\���p

		swprintf_s(KILLCNT, L"�G�����v%d�̓|�����I", g_All_Killcnt);
		swprintf_s(DEATHCNT, L"%d�񎀂�ł��܂����I", g_Death_cnt);

	//�����p�̃��b�Z�[�W�̕\��
	Font::StrDraw(L"�����������", 75, 120, 27, c);
	//���ђB����ʂŕ\�������邽�߂̃t���O����
	//�m�[�_���[�W�N���A
	if (m_page == 0)
	{
		Font::StrDraw(L"�m�[�_���[�W�N���A", 75, 155, 27, c);
		//������
		if (g_Taurus_NoDamage_Clear == true)
		{
			Font::StrDraw(L"�������F�m�[�_���[�W�N���A�I", 75, 190, 28, y);

		}
		else
		{
			Font::StrDraw(L"�������F���B��", 75, 190, 28, c);
		}
		//�V����
		if (g_Libra_NoDamage_Clear == true)
		{
			Font::StrDraw(L"�V�����F�m�[�_���[�W�N���A�I", 75, 225, 28, y);

		}
		else
		{
			Font::StrDraw(L"�V�����F���B��", 75, 225, 28, c);

		}
		//�o�q��
		if (g_Gemini_NoDamage_Clear == true)
		{
			Font::StrDraw(L"�o�q���F�m�[�_���[�W�N���A�I", 75, 260, 28, y);

		}
		else
		{
			Font::StrDraw(L"�o�q���F���B��", 75, 260, 28, c);

		}
		//������
		if (g_Viego_NoDamage_Clear == true)
		{
			Font::StrDraw(L"�������F�m�[�_���[�W�N���A�I", 75, 295, 28, y);
		}
		else
		{
			Font::StrDraw(L"�������F���B��", 75, 295, 28, c);

		}
		//���q��
		if (g_Leo_NoDamage_Clear == true)
		{
			Font::StrDraw(L"���q���F�m�[�_���[�W�N���A�I", 75, 330, 28, y);
		}
		else
		{
			Font::StrDraw(L"���q���F���B��", 75, 330, 28, c);

		}

	}
	//�G�S��
	else if (m_page == 1)
	{
		Font::StrDraw(L"ALL KILL", 75, 155, 27, c);
		//������
		if (g_Taurus_Enemy_AllKill == true)
		{
			Font::StrDraw(L"�������F�G��S�ł������I�I", 75, 190, 28, y);

		}
		else
		{
			Font::StrDraw(L"�������F���B��", 75, 190, 28, c);
		}
		//�V����
		if (g_Libra_Enemy_AllKill == true)
		{
			Font::StrDraw(L"�V�����F�G��S�ł������I�I", 75, 225, 28, y);

		}
		else
		{
			Font::StrDraw(L"�V�����F���B��", 75, 225, 28, c);

		}
		//�o�q��
		if (g_Gemini_Enemy_AllKill == true)
		{
			Font::StrDraw(L"�o�q���F�G��S�ł������I�I", 75, 260, 28, y);

		}
		else
		{
			Font::StrDraw(L"�o�q���F���B��", 75, 260, 28, c);

		}
		//������
		if (g_Viego_Enemy_AllKill == true)
		{
			Font::StrDraw(L"�������F�G��S�ł������I�I", 75, 295, 28, y);
		}
		else
		{
			Font::StrDraw(L"�������F���B��", 75, 295, 28, c);

		}
		//���q��
		if (g_Leo_Enemy_AllKill == true)
		{
			Font::StrDraw(L"���q���F�G��S�ł������I�I", 75, 330, 28, y);
		}
		else
		{
			Font::StrDraw(L"���q���F���B��", 75, 330, 28, c);

		}

	}
	//���̑�
	else if (m_page == 2)
	{
		Font::StrDraw(L"���̑��E�e�����ō������N", 75, 155, 27, c);

		Font::StrDraw(KILLCNT, 75, 190, 28, y);
		Font::StrDraw(DEATHCNT, 75, 225, 28, y);
		//������
		if (g_Taurus_Grade == S)
		{			
			Font::StrDraw(L"�������FS�����N", 75, 260, 28, cs);
			g_TRank = S;
		}
		else if (g_Taurus_Grade == A)
		{
			//�����A���S�����N���Ƃ��Ă����ꍇS�����N�ɏ���������
			if (g_TRank > A)
			{
				Font::StrDraw(L"�������FS�����N", 75, 260, 28, cs);
			}
			else
			{
				Font::StrDraw(L"�������FA�����N", 75, 260, 28, ca);
				g_TRank = A;
			}
		}
		else if (g_Taurus_Grade == B)
		{
			//�����A��ɏ�ʃ����N���Ƃ��Ă����ꍇ��ʃ����N�ɏ���������
			if (g_TRank > B)
			{
				if (g_TRank == S)
				{
					Font::StrDraw(L"�������FS�����N", 75, 260, 28, cs);
				}
				else if (g_TRank == A)
				{
					Font::StrDraw(L"�������FA�����N", 75, 260, 28, ca);
				}
			}
			Font::StrDraw(L"�������FB�����N", 75, 260, 28, cb);
			g_TRank = B;
		}
		else if (g_Taurus_Grade == C)
		{	
			//�����A��ɏ�ʃ����N���Ƃ��Ă����ꍇ��ʃ����N�ɏ���������
			if (g_TRank > C)
			{
				if (g_TRank == S)
				{
					Font::StrDraw(L"�������FS�����N", 75, 260, 28, cs);
				}
				else if (g_TRank == A)
				{
					Font::StrDraw(L"�������FA�����N", 75, 260, 28, ca);
				}
				else if (g_TRank == B)
				{
					Font::StrDraw(L"�������FB�����N", 75, 260, 28, cb);
				}
				else
				{
					Font::StrDraw(L"�������FC�����N", 75, 260, 28, cc);
				}
			}
		}
		else
		{
			Font::StrDraw(L"�������F�܂��N���A���Ă��Ȃ���", 75, 260, 28, c);
		}
		//�V����
		if (g_Libra_Grade == S)
		{
			Font::StrDraw(L"�V�����FS�����N", 75, 295, 28, cs);
			g_LiRank = S;
		}
		else if (g_Libra_Grade == A)
		{
			//�����A���S�����N���Ƃ��Ă����ꍇS�����N�ɏ���������
			if (g_LiRank > A)
			{
				Font::StrDraw(L"�V�����FS�����N", 75, 295, 28, cs);
			}
			else
			{
				Font::StrDraw(L"�V�����FA�����N", 75, 295, 28, ca);
				g_LiRank = A;
			}
		}
		else if (g_Libra_Grade == B)
		{
			//�����A��ɏ�ʃ����N���Ƃ��Ă����ꍇ��ʃ����N�ɏ���������
			if (g_LiRank > B)
			{
				if (g_LiRank == S)
				{
					Font::StrDraw(L"�V�����FS�����N", 75, 295, 28, cs);
				}
				else if (g_LiRank == A)
				{
					Font::StrDraw(L"�V�����FA�����N", 75, 295, 28, ca);
				}
			}
			Font::StrDraw(L"�V�����FB�����N", 75, 295, 28, cb);
			g_LiRank = B;
		}
		else if (g_Libra_Grade == C)
		{
			//�����A��ɏ�ʃ����N���Ƃ��Ă����ꍇ��ʃ����N�ɏ���������
			if (g_LiRank > C)
			{
				if (g_LiRank == S)
				{
					Font::StrDraw(L"�V�����FS�����N", 75, 295, 28, cs);
				}
				else if (g_LiRank == A)
				{
					Font::StrDraw(L"�V�����FA�����N", 75, 295, 28, ca);
				}
				else if (g_LiRank == B)
				{
					Font::StrDraw(L"�V�����FB�����N", 75, 295, 28, cb);
				}
				else
				{
					Font::StrDraw(L"�V�����FC�����N", 75, 295, 28, cc);
				}
			}
		}
		else
		{
			Font::StrDraw(L"�V�����F�܂��N���A���Ă��Ȃ���", 75, 295, 28, c);
		}
		//�o�q��
		if (g_Gemini_Grade == S)
		{
			Font::StrDraw(L"�o�q���FS�����N", 75, 330, 28, cs);
			g_GRank = S;
		}
		else if (g_Gemini_Grade == A)
		{
			//�����A���S�����N���Ƃ��Ă����ꍇS�����N�ɏ���������
			if (g_GRank > A)
			{
				Font::StrDraw(L"�o�q���FS�����N", 75, 330, 28, cs);
			}
			else
			{
				Font::StrDraw(L"�o�q���FA�����N", 75, 330, 28, ca);
				g_GRank = A;
			}
		}
		else if (g_Gemini_Grade == B)
		{
			//�����A��ɏ�ʃ����N���Ƃ��Ă����ꍇ��ʃ����N�ɏ���������
			if (g_GRank > B)
			{
				if (g_GRank == S)
				{
					Font::StrDraw(L"�o�q���FS�����N", 75, 330, 28, cs);
				}
				else if (g_GRank == A)
				{
					Font::StrDraw(L"�o�q���FA�����N", 75, 330, 28, ca);
				}
			}
			Font::StrDraw(L"�o�q���FB�����N", 75, 330, 28, cb);
			g_GRank = B;
		}
		else if (g_Gemini_Grade == C)
		{
			//�����A��ɏ�ʃ����N���Ƃ��Ă����ꍇ��ʃ����N�ɏ���������
			if (g_GRank > C)
			{
				if (g_GRank == S)
				{
					Font::StrDraw(L"�o�q���FS�����N", 75, 330, 28, cs);
				}
				else if (g_GRank == A)
				{
					Font::StrDraw(L"�o�q���FA�����N", 75, 330, 28, ca);
				}
				else if (g_GRank == B)
				{
					Font::StrDraw(L"�o�q���FB�����N", 75, 330, 28, cb);
				}
				else
				{
					Font::StrDraw(L"�o�q���FC�����N", 75, 330, 28, cc);
				}
			}
		}
		else
		{
			Font::StrDraw(L"�o�q���F�܂��N���A���Ă��Ȃ���", 75, 330, 28, c);
		}

		//������
		if (g_Viego_Grade == S)
		{
			Font::StrDraw(L"�������FS�����N", 75, 365, 28, cs);
			g_VRank = S;
		}
		else if (g_Viego_Grade == A)
		{
			//�����A���S�����N���Ƃ��Ă����ꍇS�����N�ɏ���������
			if (g_VRank > A)
			{
				Font::StrDraw(L"�������FS�����N", 75, 365, 28, cs);
			}
			else
			{
				Font::StrDraw(L"�������FA�����N", 75, 365, 28, ca);
				g_VRank = A;
			}
		}
		else if (g_Viego_Grade == B)
		{
			//�����A��ɏ�ʃ����N���Ƃ��Ă����ꍇ��ʃ����N�ɏ���������
			if (g_VRank > B)
			{
				if (g_VRank == S)
				{
					Font::StrDraw(L"�������FS�����N", 75, 365, 28, cs);
				}
				else if (g_VRank == A)
				{
					Font::StrDraw(L"�������FA�����N", 75, 365, 28, ca);
				}
			}
			Font::StrDraw(L"�������FB�����N", 75, 365, 28, cb);
			g_VRank = B;
		}
		else if (g_Viego_Grade == C)
		{
			//�����A��ɏ�ʃ����N���Ƃ��Ă����ꍇ��ʃ����N�ɏ���������
			if (g_VRank > C)
			{
				if (g_VRank == S)
				{
					Font::StrDraw(L"�������FS�����N", 75, 365, 28, cs);
				}
				else if (g_VRank == A)
				{
					Font::StrDraw(L"�������FA�����N", 75, 365, 28, ca);
				}
				else if (g_VRank == B)
				{
					Font::StrDraw(L"�������FB�����N", 75, 365, 28, cb);
				}
				else
				{
					Font::StrDraw(L"�������FC�����N", 75, 365, 28, cc);
				}
			}
		}
		else
		{
			Font::StrDraw(L"�������F�܂��N���A���Ă��Ȃ���", 75, 365, 28, c);
		}

		//���q��
		if (g_Leo_Grade == S)
		{
			Font::StrDraw(L"���q���FS�����N", 75, 400, 28, cs);
			g_LeRank = S;
		}
		else if (g_Leo_Grade == A)
		{
			//�����A���S�����N���Ƃ��Ă����ꍇS�����N�ɏ���������
			if (g_LeRank > A)
			{
				Font::StrDraw(L"���q���FS�����N", 75, 400, 28, cs);
			}
			else
			{
				Font::StrDraw(L"���q���FA�����N", 75, 400, 28, ca);
				g_LeRank = A;
			}
		}
		else if (g_Leo_Grade == B)
		{
			//�����A��ɏ�ʃ����N���Ƃ��Ă����ꍇ��ʃ����N�ɏ���������
			if (g_LeRank > B)
			{
				if (g_LeRank == S)
				{
					Font::StrDraw(L"���q���FS�����N", 75, 400, 28, cs);
				}
				else if (g_LeRank == A)
				{
					Font::StrDraw(L"���q���FA�����N", 75, 400, 28, ca);
				}
			}
			Font::StrDraw(L"���q���FB�����N", 75, 400, 28, cb);
			g_LeRank = B;
		}
		else if (g_Leo_Grade == C)
		{
			//�����A��ɏ�ʃ����N���Ƃ��Ă����ꍇ��ʃ����N�ɏ���������
			if (g_VRank > C)
			{
				if (g_LeRank == S)
				{
					Font::StrDraw(L"���q���FS�����N", 75, 400, 28, cs);
				}
				else if (g_LeRank == A)
				{
					Font::StrDraw(L"���q���FA�����N", 75, 400, 28, ca);
				}
				else if (g_LeRank == B)
				{
					Font::StrDraw(L"���q���FB�����N", 75, 400, 28, cb);
				}
				else
				{
					Font::StrDraw(L"���q���FC�����N", 75, 400, 28, cc);
				}
			}
		}
		else
		{
			Font::StrDraw(L"���q���F�܂��N���A���Ă��Ȃ���", 75, 400, 28, c);
		}

	}
	//�V�[�N���b�g
	else if (m_page == 3)
	{
		Font::StrDraw(L"�V�[�N���b�g", 75, 155, 27, c);	
		//�`���[�g���A���N���A
		if (g_Tutorial_Clear == true)
		{			
			Font::StrDraw(L"�`���[�g���A���N���A�I�悤�����ISTAR REGEIN�ցI", 75, 190, 28, y);
		}
		else
		{
			Font::StrDraw(L"�H�H�H", 75, 190, 28, c);
		}
		//���ׂẴX�L���l��
		if (g_All_Skill_Get == true)
		{
			Font::StrDraw(L"���ׂĂ̐����̗͂���ɓ��ꂽ�I�I", 75, 225, 28, y);
		}
		else
		{
			Font::StrDraw(L"�H�H�H", 75, 225, 28, c);
		}
		//���X�{�X���j
		if (g_Earth_BossKill == true)
		{			
			Font::StrDraw(L"���X�{�X��|�����I�I�I", 75, 260, 28, y);
		}
		else
		{
			Font::StrDraw(L"�H�H�H", 75, 260, 28, c);
		}

	}
	//4�y�[�W�ȍ~�͉����Ȃ�
	if (m_page >= 3)
	{
		;
	}
	else
	{
		Font::StrDraw(L"Z�L�[�Ŏ��̍��ڂ�", 518, 460, 27, c);
	}
	if (m_page >= 1)
	{
		Font::StrDraw(L"C�L�[�őO�̍��ڂ�", 75, 460, 28, c);
	}
	Font::StrDraw(L"X�L�[�ŕ���", 570, 120,28, c);




}
