#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;


//�I�u�W�F�N�g�F�u���b�N���w�i
class CObjStar : public CObj
{
	public:
		CObjStar(float x, float y, int i, int j,int id);
		~CObjStar() {};
		void Init();		//�C�j�V�����C�Y
		void Action();		//�A�N�V����
		void Draw();		//�h���[
		float* GetPX() { return &m_px; }
		float* GetPY() { return &m_py; }
		float GetX() { return m_px; }
		float GetY() { return m_py; }
	private:
		int m_i;	//���̈ʒui�Ԃ̕ϐ�
		int m_j;	//���̈ʒuj�Ԃ̕ϐ�

		float m_px;			//�ʒu
		float m_py;
		int m_del;
		int	   m_ani;		//�`���[�W�A�j���[�V�����p
		int m_ani_time;	//�A�j���[�V�����t���[������Ԋu
		int m_ani_frame;//�`��t���[��

		RECT_F m_eff;		//�`���[�W�G�t�F�N�g�`��p
		int m_ani_stop;
		bool m_ani_flag;	//true�ŃA�j���[�V��������Afalse�ŃA�j���[�V������~

		bool m_GetStar;		//�����擾�������ǂ����̕ϐ�
};
