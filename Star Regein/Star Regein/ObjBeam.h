#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;


//�I�u�W�F�N�g�F�u���b�N���w�i
class CObjBeam : public CObj
{
public:
	CObjBeam(float x, float y);
	~CObjBeam() {};
	void Init();		//�C�j�V�����C�Y
	void Action();		//�A�N�V����
	void Draw();		//�h���[
	float* GetPX() { return &m_px; }
	float* GetPY() { return &m_py; }
	float GetX() { return m_px; }
	float GetY() { return m_py; }
private:

	float m_px;			//�ʒu
	float m_py;

	//�r�[���A�j���[�V����
	RECT_F m_beam_eff;		//�G�t�F�N�g�`��p
	int	 m_beam_ani;			//���[�v�A�j���[�V�����p
	int	 m_beam_ani_time;		//���[�v�A�j���[�V�����Ԋu�^�C��
	int m_beam_time;			//���[�v���ԑ���
	int m_time;					//�A�j���[�V�������ߗp�J�E���g
	bool m_beam_flag;

	bool m_d_beam_flag;

	RECT_F m_eff;		//�`���[�W�G�t�F�N�g�`��p
	int	   m_ani;		//�`���[�W�A�j���[�V�����p
	int	   m_ani_time;	//�`���[�W�A�j���[�V�����Ԋu�^�C��
	bool m_ani_flag;	//true�ŃA�j���[�V��������Afalse�ŃA�j���[�V������~

};
