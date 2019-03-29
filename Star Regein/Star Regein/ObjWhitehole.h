#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�u���b�N���w�i
class CObjWhitehole : public CObj
{
	public:
		CObjWhitehole(float x, float y);
		~CObjWhitehole() {};
		void Init();		//�C�j�V�����C�Y
		void Action();		//�A�N�V����
		void Draw();		//�h���[

		float* GetWX() { return &m_px; }
		float* GetWY() { return &m_py; }
		float Getx() { return m_px; }	// X�ʒu�̎擾
		float Gety() { return m_py; }	// Y�ʒu�̎擾
		int GetI() { return m_i; }	//I�ʒu�̎擾
		int GetJ() { return m_j; }	//J�ʒu�̎擾

	private:
		float m_px;			//�ʒu
		float m_py;
		int m_i;		//�ʒu	
		int m_j;

		int m_time;		//���G���Ԃ̐ݒ�
};
