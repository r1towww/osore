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
	m_Eff_Tra = 1.0f;
	m_push_flag = false;

	m_ani = 0;			//�`���[�W�A�j���[�V�����p
	m_ani_time = 0;	//�`���[�W�A�j���[�V�����Ԋu�^�C��

	m_draw_f = false;	//�O���[�h�ʕ\���t���O�̏�����
	m_draw_time = 0;	//�O���[�h�ʕ\�����Ԃ̏�����
	m_cnt_f = true;
	//�G��|�������̕]���
	if (g_enemy_cnt == g_kill_cnt)
		m_kill_grade = 3;		//�L�����̕]��
	else if(g_kill_cnt == 0)
		m_kill_grade = 0;
	else if (g_kill_cnt / g_enemy_cnt >= 0.5)
		m_kill_grade = 2;
	else
		m_kill_grade = 1;


	m_kill_star_cnt = 0;	//�L���]���̃J�E���g
	m_damage_star_cnt = 0;		//��_���[�W�̕]��

	m_time_grade = 0;		//�^�C���̕]��

	m_cnt = 0;		//�]�����J�E���g�̏�����
	m_eff.m_top = 0;
	m_eff.m_left = 0;
	m_eff.m_right = 192;
	m_eff.m_bottom = 192;
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
		m_Eff_Tra = 0.03f;
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




	if (m_alpha[5] == 1.0f) {
		m_alpha[6] += 0.05f;
		if (m_alpha[6] >= 1.0f)
			m_alpha[6] = 1.0f;
	}
	else if (m_alpha[4] == 1.0f) {
		m_alpha[5] += 0.05f;
		if (m_alpha[5] >= 1.0f)
			m_alpha[5] = 1.0f;
	}
	else if (m_alpha[3] == 1.0f&& m_ani_flag == false) {
		m_alpha[4] += 0.05f;
		if (m_alpha[4] >= 1.0f) {
			m_alpha[4] = 1.0f;
			m_ani_flag = true;
		}
	}
	else if (m_alpha[2] == 1.0f) {
		m_alpha[3] += 0.05f;
		if (m_alpha[3] >= 1.0f) {
			m_alpha[3] = 1.0f;
			m_ani_flag = true;
		}
	}
	else if (m_alpha[1] == 1.0f) {
		m_alpha[2] += 0.05f;
		if (m_alpha[2] >= 1.0f)
			m_alpha[2] = 1.0f;
	}
	else if (m_alpha[0] == 1.0f && m_ani_flag == false) {
		m_alpha[1] += 0.05f;
		if (m_alpha[1] >= 1.0f)
			m_alpha[1] = 1.0f;
	}
	else if (m_time == 60) {	//�^�C����60�ɂȂ�����A���t�@�l�𑝂₷
		m_alpha[0] += 0.05f;
		if (m_alpha[0] >= 1.0f) {
			m_alpha[0] = 1.0f;	//1.0f�ɂȂ����玟��
			m_ani_flag = true;
		}
	}

	if (m_ani_flag == true)
	{
		//�G�t�F�N�g�p
		RECT_F ani_src[15] =
		{
			{   0,   0, 192, 192 },
			{   0, 192, 384, 192 },
			{   0, 384, 576, 192 },
			{   0, 576, 768, 192 },
			{   0, 768, 960, 192 },
			{ 192,   0, 192, 384 },
			{ 192, 192, 384, 384 },
			{ 192, 384, 576, 384 },
			{ 192, 576, 768, 384 },
			{ 192, 768, 960, 384 },
			{ 384,   0, 192, 576 },
			{ 384, 192, 384, 576 },
			{ 384, 384, 576, 576 },
			{ 384, 576, 768, 576 },
			{ 384, 768, 960, 576 },
		};

		//�A�j���[�V�����̃R�}�Ԋu����
		if (m_ani_time > 2)
		{
			m_ani++;		//�A�j���[�V�����̃R�}��1�i�߂�
			m_ani_time = 0;

			m_eff = ani_src[m_ani];//�A�j���[�V������RECT�z�񂩂�m_ani�Ԗڂ�RECT���擾
		}
		else
		{
			m_ani_time++;
		}
		//�摜�Ō�܂Ői�񂾂�A0�Ԗڂɖ߂�
		if (m_ani == 14)
		{
			if (m_grade_f[0] == false)
				m_grade_f[0] = true;


			if (m_grade_f[1] == true)
				m_damage_star_cnt++;

			if (m_f[0] == true)
				m_kill_star_cnt++;

			if (m_kill_grade == m_kill_star_cnt)
				m_grade_f[1] = true;


			

			for (int i = 0; i < 10; i++) {
				if (m_cnt == i)
					m_f[i] = true;
			}
			m_cnt++;		//�J�E���g�𑝂₷
			m_ani = 0;
			m_ani_flag = false;
			
		}
	}
}

//�h���[
void CObjStageClear::Draw()
{
	

	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,m_Tra };
	float Stage[4] = { 1.0f,1.0f,1.0f,1.0f };
	float effc[4] = { 1.0f,1.0f,1.0f,m_Eff_Tra };
	float c1[4] = { 1.0f,1.0f,1.0f,m_alpha[0] };	//�����N���A���b�Z�[�W�J���[
	float c2[4] = { 1.0f,1.0f,1.0f,m_alpha[1] };	//�擾�X�L�����b�Z�[�W�J���[
	float c3[4] = { 1.0f,1.0f,1.0f,m_alpha[2] };	//�N���A�^�C�����b�Z�[�W�J���[
	float c4[4] = { 1.0f,1.0f,1.0f,m_alpha[3] };	//�G�r�Ő����b�Z�[�W�J���[
	float c4y[4] = { 1.0f,1.0f,0.0f,m_alpha[3] };	//�G�r�Ő����b�Z�[�W�J���[�i���j
	float c4r[4] = { 1.0f,0.0f,0.0f,m_alpha[3] };	//�G�r�Ő����b�Z�[�W�J���[�i�ԁj
	float c5[4] = { 1.0f,1.0f,1.0f,m_alpha[4] };	//��_���[�W���b�Z�[�W�J���[
	float c5y[4] = { 1.0f,1.0f,0.0f,m_alpha[4] };	//��_���[�W���b�Z�[�W�J���[�i���j
	float c5r[4] = { 1.0f,0.0f,0.0f,m_alpha[4] };	//��_���[�W���b�Z�[�W�J���[�i�ԁj

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




	//���b�Z�[�W�̏��������Ă���
	CObjMessage* objmes = (CObjMessage*)Objs::GetObj(OBJ_MESSAGE);
	//�N���A���
	wchar_t KILLCNT[128];	//�L���J�E���g�\���p
	wchar_t DAMAGECNT[128];	//��_���[�W�̕`��

	wchar_t TIME[128];	//�^�C���̕`��

	//m_time_mes����b�������߂�
	//���F�b�̒l�𕶎���
	if (objmes->GetSECOND()<10)
		swprintf_s(TIME, L"�N���A�^�C���F%d��0%d�b", objmes->GetMINUTE(), objmes->GetSECOND());//�b��1���ڂ�0��p��
	else
		swprintf_s(TIME, L"�N���A�^�C���F%d��%d�b", objmes->GetMINUTE(), objmes->GetSECOND());

	swprintf_s(KILLCNT, L"�G��%d�̓|�����I", g_kill_cnt);
	//�؂���ʒu�̐ݒ�
	src.m_top    = 0.0f;
	src.m_left   = 0.0f;
	src.m_right  = 184.0f;
	src.m_bottom = 175.0f;

	//�e�������Ƃ̃��b�Z�[�W
	if (g_stage == EarthStar)
	{
		Font::StrDraw(L"�n�����N���A�����I", 15, 250, 21, c1);
		Font::StrDraw(L"�擾�����X�L���F����", 15, 280, 21, c2);
	}
	if (g_stage == VenusTaurus)
	{
		Font::StrDraw(L"���������N���A�����I", 15, 250, 21, c1);

		//�\���ʒu�̐ݒ�
		dst.m_top    = 220.0f;
		dst.m_left   = 200.0f;
		dst.m_right  = dst.m_left + 80.0f;
		dst.m_bottom = dst.m_top + 80.0f;
		if(m_ani_flag == true && m_f[0] == false)
			Draw::Draw(71, &m_eff, &dst, effc, 0.0f);

		//�\���ʒu�̐ݒ�
		dst.m_top    = 245.0f;
		dst.m_left   = 225.0f;
		dst.m_right  = 255.0f;
		dst.m_bottom = 275.0f;
		if (m_f[0] == true)
			Draw::Draw(70, &src, &dst, effc, 0.0f);

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
			Font::StrDraw(L"�G��S�ł������I", 15, 340, 21, c4y);
			//���ђB����ʂŕ\�������邽�߂̃t���O����
			if (g_stage == VenusTaurus)
			{
				g_Taurus_Enemy_AllKill = true;
				g_new_Performance = true;
			}
			else if (g_stage == VenusLibra)
			{
				g_Libra_Enemy_AllKill = true;
				g_new_Performance = true;

			}
			else if (g_stage == MercuryGemini)
			{
				g_Gemini_Enemy_AllKill = true;
				g_new_Performance = true;

			}
			else if (g_stage == MercuryVirgo)
			{
				g_Viego_Enemy_AllKill = true;
				g_new_Performance = true;

			}
			else if (g_stage == SunLeo)
			{
				g_Leo_Enemy_AllKill = true;
				g_new_Performance = true;

			}

		}
		else if (g_kill_cnt == 0)
			Font::StrDraw(L"�N���|���Ȃ������I", 15, 340, 21, c4r);
		else if (g_kill_cnt > 0)
			Font::StrDraw(KILLCNT, 15, 340, 21, c4);

			
		if (m_kill_star_cnt == 1 || m_kill_star_cnt == 2) {
			m_ani_flag = true;
		}
		if (m_ani_flag == true && m_f[0] == true && m_kill_grade != 0 &&m_kill_star_cnt == 0 
			|| m_kill_star_cnt == 1 && m_f[0] == true || m_kill_star_cnt == 2 && m_f[0] == true)
		{
			//�\���ʒu�̐ݒ�
			dst.m_top = 310.0f;
			dst.m_left = 200.0f + (40.0f * m_kill_star_cnt);
			dst.m_right = 280.0f + (40.0f * m_kill_star_cnt);
			dst.m_bottom = dst.m_top + 80.0f;
			Draw::Draw(71, &m_eff, &dst, effc, 0.0f);
		}
		for (int i = 0; i < m_kill_grade; i++)
		{
			//�\���ʒu�̐ݒ�
			dst.m_top = 335.0f;
			dst.m_left = 225.0f + (40.0f * i);
			dst.m_right = 255.0f + (40.0f * i);
			dst.m_bottom = 365.0f;
			if (m_f[i + 1] == true) {
				Draw::Draw(70, &src, &dst, effc, 0.0f);
			}
		}

		//�m�[�_���[�W�N���A���b�Z�[�W�̕\��
		if (g_no_damage == false)
		{
			m_damage_star_cnt = 0;
			Font::StrDraw(L"�m�[�_���[�W�N���A�I", 15, 370, 21, c5y);

			if (m_damage_star_cnt == 1 || m_damage_star_cnt == 2) {
				m_ani_flag = true;
			}
			if (m_ani_flag == true && m_grade_f[1] == true && m_kill_grade != 0 && m_damage_star_cnt == 0
				|| m_damage_star_cnt == 1 && m_grade_f[1] == true || m_damage_star_cnt == 2 && m_grade_f[1] == true)
			{
				//�\���ʒu�̐ݒ�
				dst.m_top    = 345.0f;
				dst.m_left   = 200.0f + (40.0f * m_damage_star_cnt);
				dst.m_right  = 280.0f + (40.0f * m_damage_star_cnt);
				dst.m_bottom = dst.m_top + 80.0f;
				Draw::Draw(71, &m_eff, &dst, effc, 0.0f);
			}

			for (int i = 0; i < m_damage_star_cnt; i++)
			{
				//�\���ʒu�̐ݒ�
				dst.m_top    = 370.0f;
				dst.m_left   = 225.0f + (40.0f * i);
				dst.m_right  = 255.0f + (40.0f * i);
				dst.m_bottom = 400.0f;
				if (m_f[i + 4] == true) {
					Draw::Draw(70, &src, &dst, effc, 0.0f);
				}
			}

			//���ђB����ʂŕ\�������邽�߂̃t���O����
			if (g_stage == VenusTaurus)
			{
				g_Taurus_NoDamage_Clear = true;
				g_new_Performance = true;

			}
			else if (g_stage == VenusLibra)
			{
				g_Libra_NoDamage_Clear = true;
				g_new_Performance = true;

			}
			else if (g_stage == MercuryGemini)
			{
				g_Gemini_NoDamage_Clear = true;
				g_new_Performance = true;

			}
			else if (g_stage == MercuryVirgo)
			{
				g_Viego_NoDamage_Clear = true;
				g_new_Performance = true;

			}
			else if (g_stage == SunLeo)
			{
				g_Leo_NoDamage_Clear = true;
				g_new_Performance = true;

			}
		}
		
	}
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

}

void CObjStageClear::alpha()
{


}