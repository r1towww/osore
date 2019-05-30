#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//-------�萔------------------------

//�_�b�V�����x
#define STAGE_DASH_SPEED 5.0
//�ʏ푬�x
#define STAGE_NORMAL_SPEED 3.0

//-------------------------------------
//�I�u�W�F�N�g:��l��
class ObjStageChoiceHero :public CObj
{
	public:
		ObjStageChoiceHero(float x, float y);
		~ObjStageChoiceHero() {};
		void Init();    //�C�j�V�����C�Y
		void Action();  //�A�N�V����
		void Draw();    //�h���[
	
		void SetAlpha(float a) { m_alpha = a; }	//�A���t�@�l���Z�b�g����֐�

	private:
		float m_vx;  //�ړ��x�N�g��
		float m_vy;
		//float g_posture; //�p��

		float m_speed_power; //�X�s�[�h�p���[

		float m_alpha;
		bool m_time;
		int m_ani_time; //�A�j���[�V�����t���[������Ԋu
		int m_ani_frame;//�`��t���[��

		bool m_f;//�U������p

		bool m_key_flag;	//�L�[���͐���t���O
		bool m_stage_start;
		float m_Tra;
		
};


