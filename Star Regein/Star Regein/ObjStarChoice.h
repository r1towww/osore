#pragma once
//�g�p����w�b�_�[
#include"GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�萔
#define UP		0
#define DOWN	1
#define RIGHT	2
#define LEFT	3

#define BACK_POSX 380
#define BACK_POSY 500
#define BACK_FONTSIZE 25

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
		float m_Tra4;
		bool m_key_flag;	//�L�[����t���O
};