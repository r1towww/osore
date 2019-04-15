#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;


//�I�u�W�F�N�g�F�u���b�N���w�i
class CObjMiniMap : public CObj
{
	public:
		CObjMiniMap(int map[MAPSIZE][MAPSIZE]);
		~CObjMiniMap() {};
		void Init();		//�C�j�V�����C�Y
		void Action();		//�A�N�V����
		void Draw();		//�h���[

		void Setdcow(int t);

		int GetID() { return count; } //���̎��ʔԍ�

	private:
		float m_blocksize,m_uisize_x, m_uisize_y;			//�}�b�vUI�̃T�C�Y
		float m_backsize;	//�w�i�̃T�C�Y
		float m_alpha;		//�w�i�̓����x
		float m_smallsize,m_bigsize;	//�`��T�C�Y�p�̕ϐ�

		int c;

		int m_f;//�L�[���͐���

		int count;

		bool m_d_cow_f[20];//���폜�t���O
		bool m_d_twinsb_f[10];//�o�q�i�j�t���O
		bool m_d_twinsr_f[10];//�o�q�i�ԁj�t���O
		
};