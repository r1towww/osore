#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;


//�I�u�W�F�N�g�F�u���b�N���w�i
class CObjSkillLeo : public CObj
{
public:
	CObjSkillLeo(int x, int y);
	~CObjSkillLeo() {};
	void Init();		//�C�j�V�����C�Y
	void Action();		//�A�N�V����
	void Draw();		//�h���[

private:
	int m_x;		//�ʒu
	int m_y;

	float m_time; //���ԃJ�E���g


};
