#pragma once
//�g�p����w�b�_�[
#include"GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�萔

//�I�u�W�F�N�g�F�^�C�g��
class CObjPerformanceRoom :public CObj
{
public:
	CObjPerformanceRoom() {};
	~CObjPerformanceRoom() {};
	void Init();		//�C�j�V�����C�Y
	void Action();		//�A�N�V����
	void Draw();		//�h���[
private:
	 int m_page;
	 bool m_f;
};
