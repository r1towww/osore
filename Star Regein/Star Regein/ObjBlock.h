#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�萔
#define HITBOXSIZE 50.0f	//��Q���p�̃q�b�g�{�b�N�X�T�C�Y

//�I�u�W�F�N�g�F�u���b�N���w�i
class CObjBlock : public CObj
{
	public:
		CObjBlock(int map[MAPSIZE][MAPSIZE]);
		~CObjBlock() {};
		void Init();		//�C�j�V�����C�Y
		void Action();		//�A�N�V����
		void Draw();		//�h���[

		int Getmap() { return m_map[MAPSIZE][MAPSIZE]; }

		bool GetType() { return m_Atypef; }

		//���E�X�N���[���p
		void SetScrollx(float s) { m_scrollx = s; }
		float GetScrollx() { return m_scrollx; }
		//�㉺�X�N���[���p
		void SetScrolly(float s) { m_scrolly = s; }
		float GetScrolly() { return m_scrolly; }

		//�u���b�N�Ƃ̓����蔻��
		void BlockHit(
			float *x, float *y, bool scroll_on,
			bool*up, bool* down, bool*left, bool*right,
			float*vx, float*vy
		);
	private:
		int m_map[MAPSIZE][MAPSIZE];	//�}�b�v���a

		int m_c_c;//���J�E���g�p
		int m_rand_cow;
		int m_blue_c;//�o�q�i�j�J�E���g�p
		int m_red_c;//�o�q�i�ԁj�J�E���g�p
		int m_woman_c;//�����J�E���g�p
		int m_b_c;//�u���b�N�z�[���J�E���g�p
		int m_w_c;//�z���C�g�z�[���J�E���g�p
		int m_libra_c;//�V���J�E���g�p

		float m_scrollx;		//���E�X�N���[���p
		float m_scrolly;		//�㉺�X�N���[���p
		float m_roll;			//�w�i��]�p
		int m_f;//��l�����Ŏ��̃G���[���p

		bool m_Atypef;

		int m_rand;	//�}�b�v�̃����_�����p

		//�f�����Ƃ̔w�i�J���[���
		float m_red;	//��
		float m_green;	//��
		float m_blue;	//��
		
};