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

		float Getx() { return m_px; }	// X�ʒu�̎擾
		float Gety() { return m_py; }	// Y�ʒu�̎擾

	private:
		float m_px;			//�ʒu
		float m_py;
		int m_time;		//���G���Ԃ̐ݒ�
};
