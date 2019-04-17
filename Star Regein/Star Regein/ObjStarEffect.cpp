//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameHead.h"
#include "ObjStarEffect.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjStarEffect::CObjStarEffect(float x, float y)
{
	m_x = x;
	m_y = y;

}



//�C�j�V�����C�Y
void CObjStarEffect::Init()
{

}
//�A�j���[�V�����t���O�ύX�p
void CObjStarEffect::Set(bool f)
{
	//m_ani_flag = f;
}

//�A�N�V����
void CObjStarEffect::Action()
{



}
//�h���[
void CObjStarEffect::Draw()
{
	//�`��J���[���  R=RED  G=Green  B=Blue A=alpha(���ߏ��)
	float  c[4] = { 1.0f,1.0f,1.0f,1.0f };
	CObjStar* obj = (CObjStar*)Objs::GetObj(OBJ_STAR);
	m_x = obj->GetX();
	m_y = obj->GetY();
	RECT_F dst; //�`���\���ʒu
	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f+m_y ;
	dst.m_left = 0.0f+m_x ;
	dst.m_right = 300.0f+m_x;
	dst.m_bottom = 300.0f+m_y;

	//�Ԗڂɓo�^�����O���t�B�b�N��dst�Ec�̏������ɕ`��
	Draw::Draw(99, &m_eff, &dst, c, 0.0f);
}