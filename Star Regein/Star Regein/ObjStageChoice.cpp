//�g�p����w�b�_�[
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\SceneManager.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "ObjStageChoice.h"

#define Earthx 0
#define Earthy 380
#define Earthxx 100
#define Earthyy 800

//�g�p����l�[���X�y�[�X
using namespace GameL;


//�C�j�V�����C�Y
void CObjStageChoice::Init()
{
	m_key_flag = true;
}

//�A�N�V����
void CObjStageChoice::Action()
{
	//��l���ʒu�擾
	ObjStageChoiceHero* hero = (ObjStageChoiceHero*)Objs::GetObj(OBJ_STAGECHOICEHERO);
	float hx = hero->GetX();
	float hy = hero->GetY();

	//�w��̏ꏊ��Z�L�[
	if (hx >= Earthx && hx<=Earthxx && hy >= Earthy&&hy<=Earthyy)
	{
		//���O�V�[������Z�L�[���������ł���������Ȃ��悤�ɁA
		//���̃V�[���ɓ����Ĉ�x�������ĂȂ���ԂɈڍs���Ȃ���
		//���s�o���Ȃ��悤�ɂ��Ă���B
		if (Input::GetVKey('Z') == true&&m_key_flag==false)
		{
			Scene::SetScene(new CSceneEarth());
		}

	}
	else
	{
		m_key_flag = false;
	}

}

//�h���[
void CObjStageChoice::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

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


}
