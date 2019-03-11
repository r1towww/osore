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

	private:
		float m_blocksize,m_uisize_x, m_uisize_y;			//�}�b�vUI�̃T�C�Y
		float m_backsize;	//�w�i�̃T�C�Y
		float m_alpha;		//�w�i�̓����x

		int m_f;//�L�[���͐���
		
};