#pragma once
//�g�p����w�b�_�[
#include"GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�^�C�g��
class CObjWorning :public CObj
{
public:
	CObjWorning() {};
	~CObjWorning() {};
	void Init();		//�C�j�V�����C�Y
	void Action();		//�A�N�V����
	void Draw();		//�h���[

private:

	float m_worning_alpha;

	int m_worning_time;
	int m_count;

	bool m_switch;
};