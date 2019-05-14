#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;


//�I�u�W�F�N�g�F�X�L���A�C�e��
class CObjSkillItem : public CObj
{
public:
	CObjSkillItem(float x,float y) ;
	~CObjSkillItem() {};
	void Init();		//�C�j�V�����C�Y
	void Action();		//�A�N�V����
	void Draw();		//�h���[

private:
	float m_x; //�X�L���A�C�e�����W
	float m_y;

	float m_vx;//�ړ���
	float m_vy;

	bool m_eff_flag;	//�G�t�F�N�g�p�t���O
	int	 m_ani;			//�A�j���[�V�����p
	int	 m_ani_time;	//�A�j���[�V�����Ԋu�^�C��
	RECT_F m_eff;		//�G�t�F�N�g�`��p
};
