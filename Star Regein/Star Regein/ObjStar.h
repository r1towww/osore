#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�u���b�N���w�i
class CObjStar : public CObj
{
	public:
		CObjStar(float x, float y, int i, int j);
		~CObjStar() {};
		void Init();		//�C�j�V�����C�Y
		void Action();		//�A�N�V����
		void Draw();		//�h���[

		int GetI() { return m_i; }	//���̈ʒui���擾
		int GetJ() { return m_j; }	//���̈ʒuj���擾
		bool GetF() { return m_f; }	//���ɐG�ꂽ���ǂ����̃t���O���擾

		void SetF(bool f) { m_f = f; }	//���ɐG�ꂽ���ǂ����̃t���O���Z�b�g

	private:
		int m_i;	//���̈ʒui�Ԃ̕ϐ�
		int m_j;	//���̈ʒuj�Ԃ̕ϐ�
		bool m_f;	//���ɐG�ꂽ���ǂ����̕ϐ�

		float m_px;			//�ʒu
		float m_py;

		bool m_GetStar;		//�����擾�������ǂ����̕ϐ�
};
