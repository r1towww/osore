#pragma once
//�g�p����w�b�_�[
#include"GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�萔
#define TEXT_X 20
#define TEXT_Y1 450
#define TEXT_Y2 490
#define TEXT_Y3 530

#define TEXT_ZX 600
#define TEXT_ZY 545

#define TEXTSIZE 32
#define TEXTSIZE_Z 25


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
	int m_key_time;
	int m_text;		//�n���ꂽ�y�[�W��

};