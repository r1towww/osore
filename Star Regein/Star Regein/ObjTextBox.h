#pragma once
//�g�p����w�b�_�[
#include"GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;


//�I�u�W�F�N�g�F�^�C�g��
class CObjTextBox :public CObj
{
public:
	CObjTextBox() {};
	~CObjTextBox() {};
	void Init();		//�C�j�V�����C�Y
	void Action();		//�A�N�V����
	void Draw();		//�h���[

private:
	bool m_f;
	int m_tipe;		//����̎��
	int m_page;		//�y�[�W��
	int m_text;		//�n���ꂽ�y�[�W��

};