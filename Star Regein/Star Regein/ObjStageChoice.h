#pragma once
//�g�p����w�b�_�[
#include"GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�����ʒu�֘A�萔----------
#define EarthX	  5
#define EarthX2	  185
#define EarthY	  370
#define EarthY2	  560
#define VenusX	  210
#define VenusX2	  410
#define VenusY	  240
#define VenusY2	  460
#define MercuryX  400
#define MercuryX2 570
#define MercuryY  140
#define MercuryY2 310
#define SunX	  550
#define SunX2	  900
#define SunY	  -100
#define SunY2	  200

#define ALPHAORIGIN	1.0f
#define ALPHAUNDER 0.3f

//�I�u�W�F�N�g�F�^�C�g��
class CObjStageChoice :public CObj
{
	public:
		CObjStageChoice() {};
		~CObjStageChoice() {};
		void Init();		//�C�j�V�����C�Y
		void Action();		//�A�N�V����
		void Draw();		//�h���[

		void SetAlpha(float a) { m_alpha = a; }	//�A���t�@�l���Z�b�g����֐�

	private:
		float m_alpha;	//�w�i�����x
};