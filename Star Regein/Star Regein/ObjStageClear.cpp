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
	m_end_start = false;
	m_end_f = false;
	m_end_s_f = false;
	m_ani = 0;			//�`���[�W�A�j���[�V�����p
	m_ani_time = 0;	//�`���[�W�A�j���[�V�����Ԋu�^�C��
	m_ani_flag = false;

	m_cnt_f = true;	//�]�������J�E���g���邩�ǂ����̃t���O
	//�n���ȊO�̏ꍇ
	if (g_stage != EarthStar)
	{
		//�G��|�������̕]���
		if (g_enemy_cnt == g_kill_cnt)
			m_kill_grade = 3;		//�L�����̕]��
		else if (g_kill_cnt == 0)
			m_kill_grade = 0;
		else if (g_kill_cnt / g_enemy_cnt >= 0.5)
			m_kill_grade = 2;
		else
			m_kill_grade = 1;
	}
	else if (g_stage == EarthStar && g_Boss_Spawn == false)//�n��
	{
		m_kill_grade = 3;
	}

	m_kill_star_cnt = 0;	//�L���]���̃J�E���g

	//���b�Z�[�W�̏��������Ă���
	CObjMessage* objmes = (CObjMessage*)Objs::GetObj(OBJ_MESSAGE);

	//�N���A�^�C���̕]���
	if (objmes->GetMINUTE() < 1)
		m_time_grade = 3;
	else if(objmes->GetMINUTE() < 2)
		m_time_grade = 2;
	else if (objmes->GetMINUTE() < 3)
		m_time_grade = 1;
	else
		m_time_grade = 0;

	m_time_star_cnt = 0;		//�^�C���O���[�h���p�̃J�E���g

	////�`���[�g���A���X�e�[�W�̓m�[�_���[�W�N���A���I�t�ɂ���
	//if (g_stage == EarthStar && g_Boss_Spawn == false)
	//	g_no_damage = true;


	//�_���[�W�̕]���
	if (g_no_damage == false)
		m_damage_grade = 3;
	else
		m_damage_grade = 0;

	m_damage_star_cnt = 0;		//��_���[�W�̕]��

	

	m_next_cnt = 0;		//���֐i�ޗp�̃J�E���g
	m_key_f = true;	//�L�[���͐���p�t���O
	m_grade_cnt_f = false;
	m_grade_draw_f = false;
	m_grade_cnt = 0;
	m_cnt = 0;		//�]�����J�E���g�̏�����
	m_eff.m_top = 0;
	m_eff.m_left = 0;
	m_eff.m_right = 192;
	m_eff.m_bottom = 192;


	Audio::Stop(8);		//�퓬BGM���~�߂�

	Audio::Start(23);	//�N���ABGM��炷
}

//�A�N�V����
void CObjStageClear::Action()
{


	//�L�[���̓^�C�������ɒB�����ꍇ�A�L�[���͂�������
	if ((Input::GetVKey('Z') == true  || Input::GetVKey(VK_RETURN) == true))
	{
		if (m_key_f == true)
		{
			Audio::Start(1);	//�G�t�F�N�g����炷

			//1�x�ڂ�Z�L�[����͂�����
			if (m_next_cnt == 0)
			{
				m_ani_flag = false;	//�A�j���[�V�����t���O���I�t�ɂ���

				//���ׂĂ̕]���̎擾
				for (int i = 0; i < 4; i++)
				{
					m_grade_f[i] = true;	//�e�]����\�����I�������ǂ����̃t���O���I��
				}
				for (int i = 0; i < m_time_grade; i++)	//�^�C���O���[�h����
				{
					m_time_star_f[i] = true;	//�N���A�^�C���]���̃O���[�h���\�����I�������ǂ����̃t���O���I��
				}
				for (int i = 0; i < m_kill_grade; i++)	//�L���O���[�h����
				{
					m_kill_star_f[i] = true;	//�L�����]���̃O���[�h���\�����I�������ǂ����̃t���O���I��
				}
				for (int i = 0; i < m_damage_grade; i++)//��_���[�W�O���[�h����
				{
					m_damage_star_f[i] = true;	//��_���[�W�]���̃O���[�h���\�����I�������ǂ����̃t���O���I��
				}

				//���ׂĂ̕]�����b�Z�[�W��\��
				m_alpha[0] = 1.0f;	//�����x��߂�
				m_alpha[1] = 1.0f;
				m_alpha[2] = 1.0f;
				m_alpha[3] = 1.0f;
				m_alpha[4] = 1.0f;

				
				m_time_star_cnt = m_time_grade;	//�^�C���X�^�[�O���[�h�̐��̐������킹��
				m_kill_star_cnt = m_kill_grade;
				m_damage_star_cnt = m_damage_grade;

				

				m_cnt_f = false;
				m_grade_cnt_f = false;
				m_cnt = CLEARGRADE + m_time_grade + m_kill_grade + m_damage_grade;		//�A�j���[�V�����ɓ���Ȃ����߁A�X�R�A��]�������
				//�� CLEARGRADE�̓N���A������Ԃŕ]�������̂ŁA�K���擾
				m_grade_cnt = m_cnt;	//�ŏI�]���p�J�E���g�ɂ��ׂĂ̕]������
			}
			//���ׂĂ̕]�����`�悳�ꂽ�ꍇ
			else if (m_next_cnt == 1 && m_alpha[5] == 1.0f)
			{
				m_push_flag = true;	//�X�e�[�W�I���֖߂�悤�ɂ���
			}
			m_key_f = false;

			m_end_start = true;

			//�J�E���g�̒l��������
			if (m_cnt == m_grade_cnt) {
				//�ŏI�A�j���[�V�����t���O���I���̎�
				if (m_end_f == true)
				{
					//�ŏI�A�j���[�V�������~�߂Đ���\��������t���O
					m_end_start = false;		//�G�t�F�N�g���~�߂�
					m_end_s_f = true;			//����`�悷��
				}
				else
					m_grade_draw_f = true;		//�ŏI�]���̐��̕`��
			}
		}
	}
	else
	{
		m_key_f = true;
	}



	//Z�L�[�������Ə��X�ɈÓ]���A�V�[���ڍs
	if (m_push_flag == true)
	{
		m_Tra += 0.03f;		//�Ó]�̓��ߓx��߂�
		//�e���b�Z�[�W�̓��ߓx�����炷
		m_Eff_Tra -= 0.03f;
		m_alpha[0] -= 0.03f;
		m_alpha[1] -= 0.03f;
		m_alpha[2] -= 0.03f;
		m_alpha[3] -= 0.03f;
		m_alpha[4] -= 0.03f;
		m_alpha[5] -= 0.03f;
		m_alpha[6] -= 0.03f;

		//�Ó]�̓��ߓx��1.0f�𒴂����ꍇ
		if (m_Tra >= 1.0f)
		{
			Scene::SetScene(new CSceneStageChoice());//�X�e�[�W�I����ʂɖ߂�
			g_stage = Space;		//�X�e�[�W�̒l��Space�i�X�e�[�W�I���j�ɕύX
			g_stage_clear = false;		//�����擾�t���O��߂�
			g_move_stop_flag = false;	//���͐���t���O��߂�
		}
	}

	//�^�C����60�ɂȂ�܂Ńv���X
	m_time++;
	if (m_time >= 60)
		m_time = 60;

	//�O�̃��b�Z�[�W���\������A�A�j���[�V�����t���O���I�t�ɂȂ����ہi�G�t�F�N�g�A�]�����I������ہj�A���b�Z�[�W��\������
	if (m_alpha[3] == 1.0f&& m_grade_f[2] == true) {		//��_���[�W�]���p
		m_alpha[4] += 0.05f;
		if (m_alpha[4] >= 1.0f) {
			m_alpha[4] = 1.0f;
			if(m_damage_grade > 0)	//�]��������ꍇ
				m_ani_flag = true;
		}
	}
	//�O�̃��b�Z�[�W���\������A�A�j���[�V�����t���O���I�t�ɂȂ����ہi�G�t�F�N�g�A�]�����I������ہj�A���b�Z�[�W��\������
	else if (m_alpha[2] == 1.0f && m_grade_f[1] == true) {	//�L�����]���p
		m_alpha[3] += 0.05f;
		if (m_alpha[3] >= 1.0f) {
			m_alpha[3] = 1.0f;
			if(m_kill_grade > 0)	//�]��������ꍇ
				m_ani_flag = true;
		}
	}
	//�O�̃��b�Z�[�W���\�����ꂽ��
	else if (m_alpha[1] == 1.0f) {							//�N���A�^�C���]���p
		m_alpha[2] += 0.05f;
		if (m_alpha[2] >= 1.0f) {
			m_alpha[2] = 1.0f;
			if (m_time_grade > 0)	//�]��������ꍇ
				m_ani_flag = true;
		}
	}
	//�O�̃��b�Z�[�W���\������A�A�j���[�V�����t���O���I�t�ɂȂ����ہi�G�t�F�N�g�A�]�����I������ہj�A���b�Z�[�W��\������
	else if (m_alpha[0] == 1.0f && m_grade_f[0] == true) {	//�擾�����p
		m_alpha[1] += 0.05f;
		if (m_alpha[1] >= 1.0f)
			m_alpha[1] = 1.0f;
	}
	else if (m_time == 60) {	//�^�C����60�ɂȂ�����A���t�@�l�𑝂₷	�X�e�[�W�N���A�p
		m_alpha[0] += 0.05f;
		if (m_alpha[0] >= 1.0f) {
			m_alpha[0] = 1.0f;	//1.0f�ɂȂ����玟�̃��b�Z�[�W�̕\��
			m_ani_flag = true;
		}
	}

	//�G�t�F�N�g���쏈���p
	Star_eff_ani();
}

//�h���[
void CObjStageClear::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,m_Tra };
	float Stage[4] = { 0.5f,0.5f,0.5f,1.0f };
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

	float c6s[4] = { 0.0f,0.5f,1.0f,m_alpha[5] };	//�ŏI�]�����b�Z�[�W�J���[�iS�j
	float c6a[4] = { 1.0f,0.0f,0.0f,m_alpha[5] };	//�ŏI�]�����b�Z�[�W�J���[�iA�j
	float c6b[4] = { 0.0f,1.0f,0.0f,m_alpha[5] };	//�ŏI�]�����b�Z�[�W�J���[�iB�j
	float c6c[4] = { 1.0f,1.0f,1.0f,m_alpha[5] };	//�ŏI�]�����b�Z�[�W�J���[�iC�j

	float y[4] = { 1.0f,1.0f,0.0f,1.0f };		//�X�e�[�W�N���A���̃��b�Z�[�W�J���[

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	//�N���A�w�i�摜�̐؂���ʒu�̐ݒ�
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
	Draw::Draw(60, &src, &dst, Stage, 0.0f);

	Font::StrDraw(L"STAGE CLEAR", CLEAR_X, CLEAR_Y, CLEAR_SIZE, y);

	Font::StrDraw(L"Z�L�[�ŃX�e�[�W�I���֖߂�", BACK_X, BACK_Y, BACK_SIZE, y);

	//���b�Z�[�W�̏��������Ă���
	CObjMessage* objmes = (CObjMessage*)Objs::GetObj(OBJ_MESSAGE);
	//�N���A���
	wchar_t KILLCNT[128];	//�L���J�E���g�\���p
	wchar_t TIME[128];	//�^�C���̕`��


	//m_time_mes����b�������߂�
	//���F�b�̒l�𕶎���
	if (objmes->GetSECOND() < 10)
		swprintf_s(TIME, L"�N���A�^�C���F%d��0%d�b", objmes->GetMINUTE(), objmes->GetSECOND());//�b��1���ڂ�0��p��
	else
		swprintf_s(TIME, L"�N���A�^�C���F%d��%d�b", objmes->GetMINUTE(), objmes->GetSECOND());

	swprintf_s(KILLCNT, L"�G��%.0f�̓|�����I", g_kill_cnt);

	Star_clear();//���U���g�X�^�[�G�t�F�N�g�̕\��

	Font::StrDraw(TIME, PER_ALL_X, FIRST_Y, PER_ALL_SIZE, c3);


	//���؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 184.0f;
	src.m_bottom = 175.0f;

	//�N���A�^�C���]���̕`��p----------------------------------------
	ani_flag();		//�A�j���[�V�����̃I���I�t�؂�ւ��p
	//�e�]���̃G�t�F�N�g�̕`��
	Star_grade_eff(m_ani_flag, m_time_star_cnt, m_grade_f[0], m_grade_f[1], 220.0f, 280.0f);
	//�e�]���̐����X�^�[��`��
	Star_grade_draw(m_time_star_f, m_time_star_cnt, 245.0f, 305.0f);

	//-----------------------------------------------------------------

	//�`���[�g���A�����̏ꍇ
	if (g_stage == EarthStar)
	{
		Font::StrDraw(L"�ړ����@���o�����I", PER_ALL_X, SECOND_Y, PER_ALL_SIZE, c4y);
		ani_flag();		//�A�j���[�V�����̃I���I�t�؂�ւ��p
		//�e�]���̃G�t�F�N�g�̕`��
		Star_grade_eff(m_ani_flag, m_kill_star_cnt, m_grade_f[1], m_grade_f[2], 220.0f, 310.0f);
		//�e�]���̐����X�^�[��`��
		Star_grade_draw(m_kill_star_f, m_kill_star_cnt, 245.0f, 335.0f);

		//�`���[�g���A�����̏ꍇ
		if (g_Boss_Spawn == false || g_stage == EarthStar)
			Font::StrDraw(L"�`���[�g���A���N���A�I", PER_ALL_X, THIRD_Y, PER_ALL_SIZE, c5y);

		ani_flag();		//�A�j���[�V�����̃I���I�t�؂�ւ��p
		//�e�]���̃G�t�F�N�g�̕`��
		Star_grade_eff(m_ani_flag, m_damage_star_cnt, m_grade_f[2], m_grade_f[3], 220.0f, 340.0f);
		//�e�]���̐����X�^�[��`��
		Star_grade_draw(m_damage_star_f, m_damage_star_cnt, 245.0f, 365.0f);
	}
	//�n���ȊO�̐��̏ꍇ
	else if (g_stage != EarthStar)
	{
		//1�̈ȏ�G��|���Ă���ꍇ
		if (g_kill_cnt > 0)
		{
			//�G�r�ŗp���b�Z�[�W�̕\��
			if (g_kill_cnt == g_enemy_cnt)
			{
				Font::StrDraw(L"�G��S�ł������I", PER_ALL_X, SECOND_Y, PER_ALL_SIZE, c4y);
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
			else if (g_kill_cnt > 0)
				Font::StrDraw(KILLCNT, PER_ALL_X, SECOND_Y, PER_ALL_SIZE, c4);


			//�L�����]���̕`��p----------------------------------------
			if (g_Boss_Spawn == true || g_stage != EarthStar)	//�`���[�g���A��������Ȃ��ꍇ
			{
				ani_flag();		//�A�j���[�V�����̃I���I�t�؂�ւ��p
				//�e�]���̃G�t�F�N�g�̕`��
				Star_grade_eff(m_ani_flag, m_kill_star_cnt, m_grade_f[1], m_grade_f[2], 220.0f, 310.0f);
				//�e�]���̐����X�^�[��`��
				Star_grade_draw(m_kill_star_f, m_kill_star_cnt, 245.0f, 335.0f);

			}
		}
		else if (g_kill_cnt == 0)	//�L�����Ȃ������ꍇ
		{
			Font::StrDraw(L"�N���|���Ȃ������I", PER_ALL_X, SECOND_Y, PER_ALL_SIZE, c4r);
		}

		//-----------------------------------------------------------------


		//�m�[�_���[�W�N���A���b�Z�[�W�̕\��
		if (g_no_damage == false)	//�_���[�W���󂯂Ȃ������ꍇ
		{
			Font::StrDraw(L"�m�[�_���[�W�N���A�I", PER_ALL_X, THIRD_Y, PER_ALL_SIZE, c5y);

			ani_flag();		//�A�j���[�V�����̃I���I�t�؂�ւ��p
			//�e�]���̃G�t�F�N�g�̕`��
			Star_grade_eff(m_ani_flag, m_damage_star_cnt, m_grade_f[2], m_grade_f[3], 220.0f, 340.0f);
			//�e�]���̐����X�^�[��`��
			Star_grade_draw(m_damage_star_f, m_damage_star_cnt, 245.0f ,365.0f);

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
	
	//�_���[�W�܂ł̕]����\�����I������
	if (m_grade_f[3] == true && m_end_start == true)
	{
		m_cnt_f = false;		//�G�t�F�N�g��`�悵�����̃J�E���g���I�t�ɂ���
		m_ani_flag = true;		//�A�j���[�V�����t���O���I���ɂ��āA�G�t�F�N�g���n�߂�

		//�S�]�����̃G�t�F�N�g�̕`��
		for (int i = 0; i < m_cnt; i++)	//�J�E���g����
		{
			//�\���ʒu�̐ݒ�
			dst.m_top    = 400.0f;
			dst.m_left   =  20.0f + (50.0f * i);
			dst.m_right  = 100.0f + (50.0f * i);
			dst.m_bottom = dst.m_top + 80.0f;
			Draw::Draw(71, &m_eff, &dst, effc, 0.0f);
		}
		//�ŏI�A�j���[�V�����t���O���I���ɂ���
		m_end_f = true;
		//���܂Ő��������̐�����ԉ��ɏo�����̃J�E���g�Ɠ����ɂ���
		m_grade_cnt = m_cnt;

		m_grade_cnt_f = false;
		
	}
	//�ŏI�]���̃G�t�F�N�g�`�悪�I�������
	if (m_end_s_f == true)
	{
		//�ŏI�]������
		for (int i = 0; i < m_grade_cnt; i++)
		{
			//�\���ʒu�̐ݒ�
			dst.m_top    = 425.0f;
			dst.m_left   = 45.0f + (50.0f * i);
			dst.m_right  = 80.0f + (50.0f * i);
			dst.m_bottom = 460.0f;
			if (m_grade_draw_f == true) {
				Draw::Draw(70, &src, &dst, effc, 0.0f);
			}
		}
		//�����N�̓��ߓx��߂�
		m_alpha[5] += 0.05f;
		if (m_alpha[5] >= 1.0f) {
			m_alpha[5] = 1.0f;
		}
		//���̐��ɉ����ă����N�Â�
		if (m_grade_cnt == 10)
		{
			if (m_next_cnt == 0)
				Audio::Start(20);	//�G�t�F�N�g����炷

			Font::StrDraw(L"S", 550, 390, 120, c6s);
			//�����N�f�[�^�ۑ�
			if (g_stage == VenusTaurus)
			{
				g_Taurus_Grade = S;
			}
			else if (g_stage == VenusLibra)
			{
				g_Libra_Grade = S;
			}
			else if (g_stage == MercuryGemini)
			{
				g_Gemini_Grade = S;
			}
			else if (g_stage == MercuryVirgo)
			{
				g_Viego_Grade = S;
			}
			else if (g_stage == SunLeo)
			{
				g_Leo_Grade = S;
			}
		}
		else if (m_grade_cnt >= 6)
		{
			if (m_next_cnt == 0)
				Audio::Start(21);	//�G�t�F�N�g����炷

			Font::StrDraw(L"A", 550, 390, 120, c6a);
			//�����N�f�[�^�ۑ�
			if (g_stage == VenusTaurus)
			{
				g_Taurus_Grade = A;
			}
			else if (g_stage == VenusLibra)
			{
				g_Libra_Grade = A;
			}
			else if (g_stage == MercuryGemini)
			{
				g_Gemini_Grade = A;
			}
			else if (g_stage == MercuryVirgo)
			{
				g_Viego_Grade = A;
			}
			else if (g_stage == SunLeo)
			{
				g_Leo_Grade = A;
			}
		}
		else if (m_grade_cnt >= 4)
		{
			if (m_next_cnt == 0)
				Audio::Start(22);	//�G�t�F�N�g����炷

			Font::StrDraw(L"B", 550, 390, 120, c6b);
			//�����N�f�[�^�ۑ�
			if (g_stage == VenusTaurus)
			{
				g_Taurus_Grade = B;
			}
			else if (g_stage == VenusLibra)
			{
				g_Libra_Grade = B;
			}
			else if (g_stage == MercuryGemini)
			{
				g_Gemini_Grade = B;
			}
			else if (g_stage == MercuryVirgo)
			{
				g_Viego_Grade = B;
			}
			else if (g_stage == SunLeo)
			{
				g_Leo_Grade = B;
			}
		}
		else
		{
			if(m_next_cnt == 0)
				Audio::Start(22);	//�G�t�F�N�g����炷

			Font::StrDraw(L"C", 550, 390, 120, c6c);
			//�����N�f�[�^�ۑ�
			if (g_stage == VenusTaurus)
			{
				g_Taurus_Grade = C;
			}
			else if (g_stage == VenusLibra)
			{
				g_Libra_Grade = C;
			}
			else if (g_stage == MercuryGemini)
			{
				g_Gemini_Grade = C;
			}
			else if (g_stage == MercuryVirgo)
			{
				g_Viego_Grade = C;
			}
			else if (g_stage == SunLeo)
			{
				g_Leo_Grade = C;
			}
		}

		m_next_cnt = 1;	//�L�[���͂ŃX�e�[�W�֖߂�悤�ɂ���
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
//�A�j���[�V�����t���O
bool CObjStageClear::ani_flag()
{
	//�L���O���[�h�p
	if (m_kill_star_cnt == 1 && m_grade_f[2] != true || m_kill_star_cnt == 2 && m_grade_f[2] != true)
	{
		m_ani_flag = true;
		return m_ani_flag;
	}
	else if (m_time_star_cnt == 1 && m_grade_f[1] != true || m_time_star_cnt == 2 && m_grade_f[1] != true)
	{
		m_ani_flag = true;
		return m_ani_flag;

	}
	else if (m_damage_star_cnt == 1 && m_grade_f[3] != true || m_damage_star_cnt == 2 && m_grade_f[3] != true) 
	{
		m_ani_flag = true;
		return m_ani_flag;
	}

}

//�X�^�[�A�j���[�V����
void CObjStageClear::Star_eff_ani()
{
	if (m_ani_flag == true)
	{
		//�ŏI���U���g�ȊO
		if (m_end_s_f != true)
			Audio::Start(19);	//�G�t�F�N�g��炷

		//�G�t�F�N�g�p�摜�̐؂���
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
		if (m_ani_time > 1)	//�^�C�����P���傫���ꍇ
		{
			m_ani++;		//�A�j���[�V�����̃R�}��1�i�߂�
			m_ani_time = 0;	//�^�C����0�ɖ߂�

			m_eff = ani_src[m_ani];//�A�j���[�V������RECT�z�񂩂�m_ani�Ԗڂ�RECT���擾
		}
		else	//����ȊO�̏ꍇ
		{
			m_ani_time++;		//�^�C�����v���X
		}
		//�摜�Ō�܂Ői�񂾂�A0�Ԗڂɖ߂�
		if (m_ani == 14)
		{

			//�N���A�^�C���p�O���[�h
			if (m_grade_f[0] == true && m_grade_f[1] == false) {
				m_time_star_f[m_time_star_cnt] = true;
				m_time_star_cnt++;
			}
			//�L�����p�O���[�h
			if (m_grade_f[1] == true && m_grade_f[2] == false) {
				m_kill_star_f[m_kill_star_cnt] = true;
				m_kill_star_cnt++;
			}
			//�_���[�W�p�O���[�h
			if (m_grade_f[2] == true && m_grade_f[3] == false) {
				m_damage_star_f[m_damage_star_cnt] = true;
				m_damage_star_cnt++;
			}
			//�X�e�[�W�N���A�p�O���[�h���I�t�̏ꍇ�i�G�t�F�N�g���P�x�ڂ̏ꍇ�j
			if (m_grade_f[0] == false)
				m_grade_f[0] = true;								//�X�e�[�W�N���A�p�O���[�h���I���ɂ���i�I��������ǂ����̔�r�p�j
			//�^�C���O���[�h�ƃJ�E���g�������ŁA�X�e�[�W�N���A�p�O���[�h���I���̏ꍇ
			if (m_time_grade == m_time_star_cnt && m_grade_f[0] == true)
				m_grade_f[1] = true;									//�^�C���O���[�h���I���ɂ���i�I��������ǂ����̔�r�p�j
			//�L���O���[�h�ƃJ�E���g�������ŁA�^�C���O���[�h���I���̏ꍇ
			if (m_kill_grade == m_kill_star_cnt && m_grade_f[1] == true)
				m_grade_f[2] = true;									//�L���O���[�h���I���ɂ���i�I��������ǂ����̔�r�p�j
			//�_���[�W�O���[�h�ƃJ�E���g�������ŁA�L���O���[�h���I���̏ꍇ
			if (m_damage_grade == m_damage_star_cnt && m_grade_f[2] == true)
				m_grade_f[3] = true; m_end_start = true;				//�_���[�W�O���[�h���I���ɂ���i�I��������ǂ����̔�r�p�j

			//�J�E���g�̒l��������
			if (m_cnt == m_grade_cnt) {
				//�ŏI�A�j���[�V�����t���O���I���̎�
				if (m_end_f == true)
				{
					//�ŏI�A�j���[�V�������~�߂Đ���\��������t���O
					m_end_start = false;		//�G�t�F�N�g���~�߂�
					m_end_s_f = true;			//����`�悷��
				}
				else
					m_grade_draw_f = true;		//�ŏI�]���̐��̕`��
			}
			//�t���O���I���̍ہA���i�]���j�������擾�ł�����
			if (m_cnt_f == true)
				m_cnt++;
			else if (m_cnt_f == false && m_grade_cnt_f == true)
				m_grade_cnt++;			//�ŏI�]���̃A�j���[�V�����̐����J�E���g����

			m_ani = 0;				//�A�j���[�V�������P���ڂɖ߂�
			m_ani_flag = false;		//�A�j���[�V�����t���O���I�t�ɂ���
			Audio::Stop(19);		//�G�t�F�N�g�����~�߂�i���d�ɖ�Ȃ��悤�j

		}
	}

}

//�f���N���A���b�Z�[�W�A�G�t�F�N�g�A�X�^�[�̕`��
void CObjStageClear::Star_clear()
{
	//�`��J���[���
	float c1[4] = { 1.0f,1.0f,1.0f,m_alpha[0] };	//�����N���A���b�Z�[�W�J���[
	float c2[4] = { 1.0f,1.0f,1.0f,m_alpha[1] };	//�擾�X�L�����b�Z�[�W�J���[												
	float effc[4] = { 1.0f,1.0f,1.0f,m_Eff_Tra };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	//���؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 184.0f;
	src.m_bottom = 175.0f;

	//�e�������Ƃ̃��b�Z�[�W
	if (g_stage == EarthStar)
	{
		Font::StrDraw(L"�n�����N���A�����I", PER_ALL_X, PER_CLEAR_1, PER_ALL_SIZE, c1);
		Font::StrDraw(L"�擾�����X�L���F����", PER_ALL_X, PER_CLEAR_2, PER_ALL_SIZE, c2);
	}
	if (g_stage == VenusTaurus)
	{
		Font::StrDraw(L"���������N���A�����I", PER_ALL_X, PER_CLEAR_1, PER_ALL_SIZE, c1);
		Font::StrDraw(L"�擾�����X�L���F������", PER_ALL_X, PER_CLEAR_2, PER_ALL_SIZE, c2);
	}
	if (g_stage == VenusLibra)
	{
		Font::StrDraw(L"�V�������N���A�����I", PER_ALL_X, PER_CLEAR_1, PER_ALL_SIZE, c1);

		Font::StrDraw(L"�擾�����X�L���F�V����", PER_ALL_X, PER_CLEAR_2, PER_ALL_SIZE, c2);
	}
	if (g_stage == MercuryGemini)
	{
		Font::StrDraw(L"�o�q�����N���A�����I", PER_ALL_X, PER_CLEAR_1, PER_ALL_SIZE, c1);

		Font::StrDraw(L"�擾�����X�L���F�o�q��", PER_ALL_X, PER_CLEAR_2, PER_ALL_SIZE, c2);
	}
	if (g_stage == MercuryVirgo)
	{
		Font::StrDraw(L"���������N���A�����I", PER_ALL_X, PER_CLEAR_1, PER_ALL_SIZE, c1);


		Font::StrDraw(L"�擾�����X�L���F������", PER_ALL_X, PER_CLEAR_2, PER_ALL_SIZE, c2);
	}
	if (g_stage == SunLeo)
	{
		Font::StrDraw(L"���q�����N���A�����I", PER_ALL_X, PER_CLEAR_1, PER_ALL_SIZE, c1);


		Font::StrDraw(L"�擾�����X�L���F���q��", PER_ALL_X, PER_CLEAR_2, PER_ALL_SIZE, c2);
	}

	//���U���g�X�^�[�G�t�F�N�g�̕\��
	//�\���ʒu�̐ݒ�
	dst.m_top = 220.0f;
	dst.m_left = 220.0f;
	dst.m_right = dst.m_left + 80.0f;
	dst.m_bottom = dst.m_top + 80.0f;
	if (m_ani_flag == true && m_grade_f[0] == false)
		Draw::Draw(71, &m_eff, &dst, effc, 0.0f);
	//�擾�����]���i���j�̕\��
	//�\���ʒu�̐ݒ�
	dst.m_top = 245.0f;
	dst.m_left = 245.0f;
	dst.m_right = 275.0f;
	dst.m_bottom = 275.0f;
	if (m_grade_f[0] == true)
		Draw::Draw(70, &src, &dst, effc, 0.0f);

}

//�e�]���̃G�t�F�N�g�̕`��
void CObjStageClear::Star_grade_eff(bool ani,int starcnt, bool grade1, bool grade2, float x, float y )
{
	//�`��J���[���
	float effc[4] = { 1.0f,1.0f,1.0f,m_Eff_Tra };

	RECT_F dst; //�`���\���ʒu

	if (ani == true && starcnt == 0 && grade1 == true && grade2 == false
		|| ani == true && starcnt == 1 && grade1 == true && grade2 == false
		|| ani == true && starcnt == 2 && grade1 == true && grade2 == false)
	{
		//�\���ʒu�̐ݒ�
		dst.m_top = y;
		dst.m_left = x + (40.0f * starcnt);
		dst.m_right = x + 80.0f + (40.0f * starcnt);
		dst.m_bottom = dst.m_top + 80.0f;
		Draw::Draw(71, &m_eff, &dst, effc, 0.0f);
	}

}

//�X�^�[�̕`��
void CObjStageClear::Star_grade_draw(bool grade_f[3],int starcnt,float x , float y)
{
	//�`��J���[���
	float effc[4] = { 1.0f,1.0f,1.0f,m_Eff_Tra };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	//���؂���ʒu�̐ݒ�
	src.m_top    = 0.0f;
	src.m_left   = 0.0f;
	src.m_right  = 184.0f;
	src.m_bottom = 175.0f;

	for (int i = 0; i < starcnt; i++)	//�]���i���j�̕\��
	{
		//�\���ʒu�̐ݒ�
		dst.m_top    = y;
		dst.m_left   = x + (40.0f * i);
		dst.m_right  = x + 30.0f + (40.0f * i);
		dst.m_bottom = y + 30.0f;
		if (grade_f[i] == true) {
			Draw::Draw(70, &src, &dst, effc, 0.0f);
		}
	}
}

