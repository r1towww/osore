//�g�p����w�b�_�[
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\SceneManager.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "ObjStageChoice.h"
//�����ʒu�֘A----------------------
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
//----------------------------------
//�g�p����l�[���X�y�[�X
using namespace GameL;


//�C�j�V�����C�Y
void CObjStageChoice::Init()
{
	m_key_flag = false;
}

//�A�N�V����
void CObjStageChoice::Action()
{
	//��l���ʒu�擾
	ObjStageChoiceHero* hero = (ObjStageChoiceHero*)Objs::GetObj(OBJ_STAGECHOICEHERO);
	float hx = hero->GetX();
	float hy = hero->GetY();

	//�n����
	if (hx >= EarthX && hx<= EarthX2 && hy >= EarthY&&hy<= EarthY2)
	{
		//���O�V�[������Z�L�[���������ł���������Ȃ��悤�ɁA
		//���̃V�[���ɓ����Ĉ�x�������ĂȂ���ԂɈڍs���Ȃ���
		//���s�o���Ȃ��悤�ɂ��Ă���B
		if (Input::GetVKey('Z') == true && m_key_flag == true)
		{
			g_stage = Earth;	//�X�e�[�W�̒l��n���ɕύX
			Scene::SetScene(new CSceneEarth());
		}
	}
	//������
	else if (hx >= VenusX && hx <= VenusX2 && hy >= VenusY&&hy <= VenusY2)
	{
		//���O�V�[������Z�L�[���������ł���������Ȃ��悤�ɁA
		//���̃V�[���ɓ����Ĉ�x�������ĂȂ���ԂɈڍs���Ȃ���
		//���s�o���Ȃ��悤�ɂ��Ă���B
		if (Input::GetVKey('Z') == true && m_key_flag == true)
		{
			//�����ɐݒ�
			g_stage = Venus;
			Scene::SetScene(new CSceneStarChoice());
		}
	}
	//������
	else if (hx >= MercuryX && hx <= MercuryX2 && hy >= MercuryY&&hy <= MercuryY2)
	{
		//���O�V�[������Z�L�[���������ł���������Ȃ��悤�ɁA
		//���̃V�[���ɓ����Ĉ�x�������ĂȂ���ԂɈڍs���Ȃ���
		//���s�o���Ȃ��悤�ɂ��Ă���B
		if (Input::GetVKey('Z') == true && m_key_flag == true)
		{
			//�����ɐݒ�
			g_stage = Mercury;
			Scene::SetScene(new CSceneStarChoice());
		}

	}
	//���z��
	else if (hx >= SunX && hx <= SunX2 && hy >= SunY&&hy <= SunY2)
	{
		if (Input::GetVKey('Z') == true && m_key_flag == true)
		{
			//���Ń^�C�g���ɍs���悤�ɂ��Ă邩�炠�Ƃł����Ƒ��z�ɂ��Ă����Ă�
			//���z�ɐݒ�
			//g_stage = SunLeo;���X�e�[�W������������R�����g�O���Ă�
			Scene::SetScene(new CSceneTitle());
		}

	}
	else
	{
		m_key_flag = true;
	}

}

//�h���[
void CObjStageChoice::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	//�w�i------------------------------------
	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1920.0f;
	src.m_bottom = 1080.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f ;
	dst.m_left = 0.0f ;
	dst.m_right = 800.0f ;
	dst.m_bottom = 600.0f ;

	//�\��
	Draw::Draw(2, &src, &dst, c, 0.0f);
	//----------------------------------------

	//�n��------------------------------------
	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 300.0f;
	src.m_bottom = 283.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top =	450.0f;
	dst.m_left = 0.0f;
	dst.m_right = 150.0f;
	dst.m_bottom = 600.0f;

	//�\��
	Draw::Draw(3, &src, &dst, c, 0.0f);
	//----------------------------------------


	//����------------------------------------
	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 303.0f;
	src.m_bottom =303.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 350.0f;
	dst.m_left = 200.0f;
	dst.m_right = 350.0f;
	dst.m_bottom = 500.0f;

	//�\��
	Draw::Draw(4, &src, &dst, c, 0.0f);
	//----------------------------------------

	//����------------------------------------
	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 325.0f;
	src.m_bottom =325.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 180.0f;
	dst.m_left = 450.0f;
	dst.m_right = 600.0f;
	dst.m_bottom =330.0f;

	//�\��
	Draw::Draw(5, &src, &dst, c, 0.0f);
	//----------------------------------------

	//���z------------------------------------
	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 335.0f;
	src.m_bottom = 350.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f;
	dst.m_left = 650.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 150.0f;

	//�\��
	Draw::Draw(6, &src, &dst, c, 0.0f);
	//----------------------------------------

}
