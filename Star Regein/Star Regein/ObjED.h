#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�`��֌W�̒萔

#define GAME_CLEAR_X (225)
#define GAME_CLEAR_Y (150)
#define GAME_CLEAR_FONT_SIZE (30)

//�I�u�W�F�N�g�F�u���b�N���w�i
class CObjED : public CObj
{
public:
	CObjED() {};
	~CObjED() {};
	void Init();		//�C�j�V�����C�Y
	void Action();		//�A�N�V����
	void Draw();		//�h���[

private:
	int m_y;
};