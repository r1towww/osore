#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�r�[���T�[�x��
class CObjSkillVirgo : public CObj
{
public:
	CObjSkillVirgo(float x,float y);
	~CObjSkillVirgo() {};
	void Init();  //�C�j�V�����C�Y
	void Action();//�A�N�V����
	void Draw();  //�h���[
private:
	float m_x;
	float m_y;
	float m_vx;
	float m_vy;

	float m_time;

	int m_pos_x;	//�q�b�g�{�b�N�X�̌����p�ϐ�
	int m_pos_y;
	int m_angle;	//�n�[�g�e�̊p�x�p�ϐ�



};