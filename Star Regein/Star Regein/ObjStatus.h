#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

#define STATUS_PX 24.0f	//�X�e�[�^�X�\���ʒu��X�ʒu�����p
#define STATUS_PY 0.0f	//�X�e�[�^�X�\���ʒu��Y�ʒu�����p

//�I�u�W�F�N�g�F�u���b�N���w�i
class CObjStatus : public CObj
{
	public:
		CObjStatus();
		~CObjStatus() {};
		void Init();		//�C�j�V�����C�Y
		void Action();		//�A�N�V����
		void Draw();		//�h���[

	private:
		int m_red;		//HP�p�J���[ ��
		int m_gleen;	//HP�p�J���[ ��
		int m_blue;		//HP�p�J���[ ��

};