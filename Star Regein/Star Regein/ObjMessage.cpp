//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"
#include "GameHead.h"

#include "ObjMessage.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjMessage::Init()
{
	m_memory = 0;	//���̐����v��ϐ��̏�����
	m_time = 0;		//���b�Z�[�W���ԗp�̕ϐ��̏�����
	m_time_mes = 0;	//�^�C���J�E���g�p�ϐ��̏�����
	m_f = false;	//�^�C���J�E���g�p�t���O�̏�����
	//���̍ő�̐��̏������i�������W�߂�ꏊ�ɂ���ĕω��j
	if (g_stage == EarthStar)
		m_MaxStar = EARTHMAXSTAR;	//�n��
	else if (g_stage == VenusTaurus)
		m_MaxStar = TAURUSMAXSTAR;	//�����i�������j
	else if (g_stage == VenusLibra)
		m_MaxStar = LIBRAMAXSTAR;	//�����i�V�����j
	else if (g_stage == MercuryGemini)
		m_MaxStar = GEMINIMAXSTAR;	//�����i�o�q���j
	else if (g_stage == MercuryVirgo)
		m_MaxStar = VIRGOMAXSTAR;	//�����i�������j
	else if (g_stage == SunLeo)
		m_MaxStar = LEOMAXSTAR;		//���z�i���q���j

}

//�A�N�V����
void CObjMessage::Action()
{
	//�X�L���A�C�e���I�u�W�F�N�g�̏��������Ă���
	CObjSkillItem* objskillitem = (CObjSkillItem*)Objs::GetObj(OBJ_SKILL_ITEM);
	//�X�e�[�W�N���A�̏��������Ă���
	CObjStageClear* objclear = (CObjStageClear*)Objs::GetObj(OBJ_STAGECLEAR);

	if (g_tutorial_flag == true) {
		;			//�`���[�g���A�����b�Z�[�W���\������Ă���ہA�^�C�����J�E���g���Ȃ�
	}
	else if(objskillitem != nullptr || objclear != nullptr){	//�X�L���I�u�W�F�N�g���쐬���ꂽ�ہA�܂��̓N���A�I�u�W�F�N�g���쐬����Ă����
		m_f = true;		//�t���O���I���ɂ���
	}
	else if(m_f == false){	//�t���O���I�t�̍ہA�^�C�����J�E���g
		m_time_mes++;
	}
}

//�h���[
void CObjMessage::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };	//���b�Z�[�W�t�H���g�J���[
	float ca[4] = { 1.0f,1.0f,1.0f,0.7f };	//���b�Z�[�W�t�H���g�J���[

	float sc[4] = { 1.0f,1.0f,0.4f,1.0f };
	float b[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	wchar_t STARMES[128];	//���̐��𐔂��郁�b�Z�[�W�p
	wchar_t STAR[128];	//���̐�����ɕ\������
	wchar_t TIME[128];	//�^�C���̕`��

	//m_time_mes����`�������߂�
	m_second = (m_time_mes / 60) % 60;	//�b
	m_minute = (m_time_mes / 60) / 60;	//��

	//���F�b�̒l�𕶎���
	if (m_second<10)
		swprintf_s(TIME, L"%d��0%d�b", m_minute, m_second);//�b��1���ڂ�0��p��
	else
		swprintf_s(TIME, L"%d��%d�b", m_minute, m_second);

	Font::StrDraw(TIME, 10, 250, 20, c);	//�^�C���̕\��

	swprintf_s(STAR, L"%d/%d", g_StarCount, m_MaxStar);
	Font::StrDraw(STAR, 400, 20, 25, sc);//���b�Z�[�W��\��

	Font::StrDraw(L"Q:���j���[", 465, 12, 21, c);	//���j���[
	Font::StrDraw(L"H:�w���v", 465, 33, 21, c);	//�w���v
	Font::StrDraw(L"M:�}�b�v�؂�ւ�", 635, 220, 20, ca);	//�}�b�v�g��L�[

	//�����̂ǂ��炩�̃X�L�����I���̍ە`�悷��
	if (g_Taurus == true || g_Libra == true) {
		Font::StrDraw(L"�X�L���؂�ւ�", 580, 400, 20, ca);	//�X�L���؂�ւ��L�[
		Font::StrDraw(L"C�ō��ցAV�ŉE��", 570, 420, 21, ca);	//�X�L���؂�ւ��L�[
	}
	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 232.0f;
	src.m_bottom = 203.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 16.0f;
	dst.m_left = 365.0f;
	dst.m_right = 395.0f;
	dst.m_bottom = 46.0f;

	//�`��
	Draw::Draw(6, &src, &dst, c, 0.0f);
	
	//���̃J�E���g���������ꍇ
	if (g_StarCount > m_memory)
	{
		//�Ō�̐����擾������
		if (m_MaxStar == g_StarCount) {
			Font::StrDraw(L"�Ō�̐����擾�I", 150, 240, 25, sc);	//�ʂ̃��b�Z�[�W���쐬
		}
		else
		{
			m_time++;	//time���v���X���Ă��鎞�������b�Z�[�W��\��
			swprintf_s(STARMES, L"%d�ڂ́����擾�A�c��%d�I", g_StarCount, m_MaxStar - g_StarCount);
			Font::StrDraw(STARMES, 150, 240, 25, sc);//���b�Z�[�W��\��
			if (m_time == 100) {
				m_memory = g_StarCount;	//���݂̐��̐�����
				m_time = 0;	//time�̏�����
			}
		}
	}


}
