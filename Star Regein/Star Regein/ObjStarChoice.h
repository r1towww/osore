#pragma once
//�g�p����w�b�_�[
#include"GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�^�C�g��
class CObjStarChoice :public CObj
{
public:
	CObjStarChoice() {};
	~CObjStarChoice() {};
	void Init();		//�C�j�V�����C�Y
	void Action();		//�A�N�V����
	void Draw();		//�h���[
private:
	bool m_oushi;
	bool m_tenbin;
	float m_Tra1;//���ߗ�
	float m_Tra2;//���ߗ�

};