#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;


//�I�u�W�F�N�g�F�u���b�N���w�i
class CObjSkillLibra : public CObj
{
	public:
		CObjSkillLibra(int x,int y);
		~CObjSkillLibra() {};
		void Init();		//�C�j�V�����C�Y
		void Action();		//�A�N�V����
		void Draw();		//�h���[

	private:
		int m_x;		//�ʒu
		int m_y;



		int	 m_ani;			//�A�j���[�V�����p
		int	 m_ani_time;	//�A�j���[�V�����Ԋu�^�C��
		RECT_F m_eff;		//�G�t�F�N�g�`��p
		bool m_ani_flag;	//true�ŃA�j���[�V��������Afalse�ŃA�j���[�V������~

};