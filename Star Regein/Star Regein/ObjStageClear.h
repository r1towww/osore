#pragma once
//�g�p����w�b�_�[
#include"GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

#define CLEARGRADE 1

//�I�u�W�F�N�g�F�^�C�g��
class CObjStageClear :public CObj
{
	public:
		CObjStageClear() {};
		~CObjStageClear() {};
		void Init();		//�C�j�V�����C�Y
		void Action();		//�A�N�V����
		void Draw();		//�h���[
		bool ani_flag();	//�A�j���[�V�����̃I���I�t�̐؂�ւ�
		void Star_eff_ani();	//�X�^�[�G�t�F�N�g
		void Star_clear();	//�f���N���A���b�Z�[�W�A�G�t�F�N�g�A�X�^�[�̕`��
		//�e�]���̃G�t�F�N�g�̕`��
		void Star_grade_eff(bool ani, int starcnt, bool grade1, bool grade2, float x, float y);//�A�j���[�V�����t���O�A�e�]���̃J�E���g�A�O�̕]���A�I�𒆂̕]���A�ʒuX�A�ʒuY
		//�e�]���̃X�^�[�̕`��	
		void Star_grade_draw(bool grade_f[3], int starcnt,float x, float y);//�e�]���̐��̃t���O�A�e�]���̃J�E���g�A�ʒuX�A�ʒuY


	private:


		int m_time;	//�\���܂ł̎��ԊԊu

		//�e���b�Z�[�W�̓����x�p�ϐ�
		
		float m_Tra;
		float m_Eff_Tra;

		int	 m_ani;			//�A�j���[�V�����p
		int	 m_ani_time;	//�A�j���[�V�����Ԋu�^�C��
		RECT_F m_eff;		//�G�t�F�N�g�`��p
		bool m_ani_flag;	//true�ŃA�j���[�V��������Afalse�ŃA�j���[�V������~
		int m_cnt;	//�ǂ̕]������\�����I�������̃J�E���g�p
		int m_grade_cnt;	//���ׂĂ̕]�����̃J�E���g
		bool m_grade_cnt_f;	//�O���[�h�]���\���p�t���O
		bool m_grade_draw_f;//�O���[�h�]���\���p�t���O

		bool m_cnt_f;		//�J�E���g���邩�ǂ����̃t���O
		bool m_end_start;
		bool m_end_f;		//�ŏI�A�j���[�V�����I���t���O
		bool m_end_s_f;		//���o���J�n�t���O

		bool m_grade_f[4] = { false,false, false, false, };	//�e�]�����I�������ǂ���
			
		bool m_kill_star_f[3] = { false, false, false };	//�L�����̕]�����I������
		int m_kill_grade;		//�L�����̕]��
		int m_kill_star_cnt;		//�L���O���[�h���p�̃J�E���g

		bool m_time_star_f[3] = { false, false, false };	//�^�C���̕]�����I������
		int m_time_grade;		//�^�C���̕]��
		int m_time_star_cnt;		//�^�C���O���[�h���p�̃J�E���g

		bool m_damage_star_f[3] = { false, false, false };	//�_���[�W�̕]�����I������
		int m_damage_grade;		//�_���[�W�̕]��
		int m_damage_star_cnt;		//�_���[�W�̕]��

		int m_next_cnt;		//���֐i�ޗp�J�E���g
		bool m_key_f;		//�L�[���͐���p�t���O
		bool m_push_flag;		//�Ó]�p�t���O
		float m_alpha[7] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };	//���b�Z�[�Walpha�l�ύX�p

};