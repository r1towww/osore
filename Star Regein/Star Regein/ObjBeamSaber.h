#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�r�[���T�[�x��
class CObjBeamSaber : public CObj
{
	public:
		CObjBeamSaber(float x,float y);
		~CObjBeamSaber() {};
		void Init();  //�C�j�V�����C�Y
		void Action();//�A�N�V����
		void Draw();  //�h���[
	private:
		float m_x;
		float m_y;
		int m_time;
		int m_pos_x;	//�q�b�g�{�b�N�X�̌����p�ϐ�
		int m_pos_y;
		int m_angle;	//�r�[���T�[�x���̊p�x�p�ϐ�

};