#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�u���b�N���w�i
class CObjMeteo : public CObj
{
	public:
		CObjMeteo(float x, float y);
		~CObjMeteo() {};
		void Init();		//�C�j�V�����C�Y
		void Action();		//�A�N�V����
		void Draw();		//�h���[

	private:
		float m_px;			//�ʒu
		float m_py;
};
