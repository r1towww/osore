#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;


//�I�u�W�F�N�g�F�X�L��
class CObjSkill : public CObj
{
	public:
		CObjSkill() {};
		~CObjSkill() {};
		void Init();		//�C�j�V�����C�Y
		void Action();		//�A�N�V����
		void Draw();		//�h���[

	private:
		int m_memory;	//�X�L����r�p�ϐ�
		int m_next;	//���̃X�L���p
		int m_back;	//�O�̃X�L���p

};