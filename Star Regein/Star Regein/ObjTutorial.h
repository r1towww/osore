#pragma once
//�g�p����w�b�_�[
#include"GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;


//�I�u�W�F�N�g�F�^�C�g��
class CObjTutorial :public CObj
{
public:
	CObjTutorial(int t, int p) { m_tipe = t; m_p = p; };
	~CObjTutorial() {};
	void Init();		//�C�j�V�����C�Y
	void Action();		//�A�N�V����
	void Draw();		//�h���[


private:
	int m_tipe;		//����̎��
	int m_page;		//�y�[�W��
	int m_p;		//�n���ꂽ�y�[�W��
	int m_sec;		//�Z�R���h(�b)
	int m_keytime;	//�L�[���͂��ł���܂ł̎���
	int m_line;		//�s��

};