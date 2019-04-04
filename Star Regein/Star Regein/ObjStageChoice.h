#pragma once
//�g�p����w�b�_�[
#include"GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�����ʒu�֘A�萔----------
#define EarthX	  0
#define EarthY	  380
#define EarthX2	  100
#define EarthY2	  800
#define VenusX	  180
#define VenusX2	  320
#define VenusY	  300
#define VenusY2	  445
#define MercuryX  420
#define MercuryX2 570
#define MercuryY  120
#define MercuryY2 270
#define SunX	  615
#define SunX2	  800
#define SunY	  0
#define SunY2	  90

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