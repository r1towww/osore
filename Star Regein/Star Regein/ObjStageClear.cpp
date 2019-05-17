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
	m_time = 0;	//�`��܂ł̃^�C�����o�̏�����
	m_Tra = 0.0f;
	m_push_flag = false;
}

//�A�N�V����
void CObjStageClear::Action()
{
	//�L�[���̓^�C�������ɒB�����ꍇ�A�L�[���͂�������
	if ((Input::GetVKey('Z') == true && m_alpha[4] == 1.0f || Input::GetVKey(VK_RETURN) == true) && m_alpha[4] == 1.0f)	
	{

		m_push_flag = true;
	
	}
	//Z�L�[�������Ə��X�ɈÓ]���A�V�[���ڍs
	if (m_push_flag == true)
	{
		m_Tra += 0.03f;
		m_alpha[0] = 0.03f;
		m_alpha[1] = 0.03f;
		m_alpha[2] = 0.03f;
		m_alpha[3] = 0.03f;
		m_alpha[4] = 0.03f;
		m_alpha[5] = 0.03f;
		m_alpha[6] = 0.03f;

		if (m_Tra >= 1.0f)
		{
			Scene::SetScene(new CSceneStageChoice());//�X�e�[�W�I��
			g_stage_clear = false;
			g_move_stop_flag = false;

		}
	}


	//�^�C����60�ɂȂ�܂Ńv���X
	m_time++;
	if (m_time >= 60)
		m_time = 60;
	if (m_time == 60) {	//�^�C����100�ɂȂ�����A���t�@�l�𑝂₷
		m_alpha[0] += 0.05f;
		if (m_alpha[0] >= 1.0f)
			m_alpha[0] = 1.0f;	//1.0f�ɂȂ����玟��
	}
	if (m_alpha[0] == 1.0f) {	//���b�Z�[�W���J��Ԃ�
		m_alpha[1] += 0.05f;
		if (m_alpha[1] >= 1.0f)
			m_alpha[1] = 1.0f;
	}
	if (m_alpha[1] == 1.0f) {
		m_alpha[2] += 0.05f;
		if (m_alpha[2] >= 1.0f)
			m_alpha[2] = 1.0f;
	}
	if (m_alpha[2] == 1.0f) {
		m_alpha[3] += 0.05f;
		if (m_alpha[3] >= 1.0f)
			m_alpha[3] = 1.0f;
	}
	if (m_alpha[3] == 1.0f) {
		m_alpha[4] += 0.05f;
		if (m_alpha[4] >= 1.0f)
			m_alpha[4] = 1.0f;
	}
	if (m_alpha[4] == 1.0f) {
		m_alpha[5] += 0.05f;
		if (m_alpha[5] >= 1.0f)
			m_alpha[5] = 1.0f;
	}
	if (m_alpha[5] == 1.0f) {
		m_alpha[6] += 0.05f;
		if (m_alpha[6] >= 1.0f)
			m_alpha[6] = 1.0f;
	}
}

//�h���[
void CObjStageClear::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,m_Tra };
	float Stage[4] = { 1.0f,1.0f,1.0f,1.0f };

	float c1[4] = { 1.0f,1.0f,1.0f,m_alpha[0] };
	float c2[4] = { 1.0f,1.0f,1.0f,m_alpha[1] };
	float c3[4] = { 1.0f,1.0f,1.0f,m_alpha[2] };
	float c4[4] = { 1.0f,1.0f,0.0f,m_alpha[3] };
	float c5[4] = { 1.0f,1.0f,1.0f,m_alpha[4] };
	float c6[4] = { 1.0f,1.0f,1.0f,m_alpha[5] };
	float c7[4] = { 1.0f,1.0f,1.0f,m_alpha[6] };


	float y[4] = { 1.0f,1.0f,0.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	


	if (g_stage == EarthStar)
	{
		//�n��-------------------------------
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

	
	}
	if (g_stage == MercuryGemini)
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

	
	}
	if (g_stage == MercuryVirgo)
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
	}
	if (g_stage == SunLeo)
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
	}

	//�\��
	Draw::Draw(60, &src, &dst, Stage, 0.0f);

	Font::StrDraw(L"STAGE CLEAR", 120,150, 100,y);

	Font::StrDraw(L"Z�L�[�ŃX�e�[�W�I���֖߂�", 200, 510, 32, y);

	//�V�[���ڍs�p
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

		Draw::Draw(9, &src, &dst, c, 0.0f);

	}



	//���b�Z�[�W�̏��������Ă���
	CObjMessage* objmes = (CObjMessage*)Objs::GetObj(OBJ_MESSAGE);
	//�N���A���
	wchar_t KILLCNT[128];	//�L���J�E���g�\���p

	wchar_t TIME[128];	//�^�C���̕`��

	//m_time_mes����`�������߂�
	//���F�b�̒l�𕶎���
	if (objmes->GetSECOND()<10)
		swprintf_s(TIME, L"�N���A�^�C���F%d��0%d�b", objmes->GetMINUTE(), objmes->GetSECOND());//�b��1���ڂ�0��p��
	else
		swprintf_s(TIME, L"�N���A�^�C���F%d��%d�b", objmes->GetMINUTE(), objmes->GetSECOND());

	

	swprintf_s(KILLCNT, L"�G��%d�̓|�����I", g_kill_cnt);

	//�e�������Ƃ̃��b�Z�[�W
	if (g_stage == EarthStar)
	{
		Font::StrDraw(L"�n�����N���A�����I", 15, 250, 21, c1);
		Font::StrDraw(L"�擾�����X�L���F����", 15, 280, 21, c2);
	}
	if (g_stage == VenusTaurus)
	{
		Font::StrDraw(L"���������N���A�����I", 15, 250, 21, c1);
		Font::StrDraw(L"�擾�����X�L���F������", 15, 280, 21, c2);
	}
	if (g_stage == VenusLibra)
	{
		Font::StrDraw(L"�V�������N���A�����I", 15, 250, 21, c1);
		Font::StrDraw(L"�擾�����X�L���F�V����", 15, 280, 21, c2);
	}
	if (g_stage == MercuryGemini)
	{
		Font::StrDraw(L"�o�q�����N���A�����I", 15, 250, 21, c1);
		Font::StrDraw(L"�擾�����X�L���F�o�q��", 15, 280, 21, c2);
	}
	if (g_stage == MercuryVirgo)
	{
		Font::StrDraw(L"���������N���A�����I", 15, 250, 21, c1);
		Font::StrDraw(L"�擾�����X�L���F������", 15, 280, 21, c2);
	}
	if (g_stage == SunLeo)
	{
		Font::StrDraw(L"���q�����N���A�����I", 15, 250, 21, c1);
		Font::StrDraw(L"�擾�����X�L���F���q��", 15, 280, 21, c2);
	}

	Font::StrDraw(TIME, 15, 310, 21, c3);


	//�n���ȊO�̐��̏ꍇ
	if (g_stage != EarthStar)
	{
		//�G�r�ŗp���b�Z�[�W�̕\��
		if (g_kill_cnt == g_enemy_cnt)
			Font::StrDraw(L"�G��S�ł������I", 15, 340, 21, c4);
		else if (g_kill_cnt == 0)
			Font::StrDraw(L"�N���|���Ȃ������I", 15, 340, 21, c4);
		else if (g_kill_cnt > 0)
			Font::StrDraw(KILLCNT, 15, 340, 21, c4);
		//�m�[�_���[�W�N���A���b�Z�[�W�̕\��
		if (g_no_damage == false)
		{
			Font::StrDraw(L"�m�[�_���[�W�N���A�I", 15, 370, 21, c5);
			//���ђB����ʂŕ\�������邽�߂̃t���O����
			if (g_stage == VenusTaurus)
			{
				g_Taurus_NoDamage_Clear = true;
			}
			else if (g_stage == VenusLibra)
			{
				g_Libra_NoDamage_Clear = true;
			}
			else if (g_stage == MercuryGemini)
			{
				g_Gemini_NoDamage_Clear = true;
			}
			else if (g_stage == MercuryVirgo)
			{
				g_Viego_NoDamage_Clear = true;
			}
			else if (g_stage == SunLeo)
			{
				g_Leo_NoDamage_Clear = true;
			}
		}
	}
}

void CObjStageClear::alpha()
{


}