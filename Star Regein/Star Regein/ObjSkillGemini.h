#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;


//�I�u�W�F�N�g�F�u���b�N���w�i
class CObjSkillGemini : public CObj
{
public:
	CObjSkillGemini() {};
	~CObjSkillGemini() {};
	void Init();		//�C�j�V�����C�Y
	void Action();		//�A�N�V����
	void Draw();		//�h���[

private:
	int m_ani_time; //�A�j���[�V�����t���[������Ԋu
	int m_ani_frame;//�`��t���[��
	float m_x;
	float m_y;
	float m_vx;
	float m_vy;
	
};