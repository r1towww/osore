#pragma once
//�g�p����w�b�_�[
#include"GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�萔
#define DOWN	0
#define RIGHT	1
#define LEFT	2

//�I�u�W�F�N�g�F�^�C�g��
class CObjStarChoice :public CObj
{
	public:
		CObjStarChoice() {};
		~CObjStarChoice() {};
		void Init();		//�C�j�V�����C�Y
		void Action();		//�A�N�V����
		void Draw();		//�h���[
	private:
		int m_direction;	//�����I��p�ϐ�
		float m_Tra1;//���ߗ�
		float m_Tra2;//���ߗ�
		float m_Tra3;//���ߗ�

		int m_keytime;	//�L�[���͂��ł���܂ł̎���
};