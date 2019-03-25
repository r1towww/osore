//�g�p����w�b�_�[
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\SceneManager.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "ObjStageClear.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;


//�C�j�V�����C�Y
void CObjStageClear::Init()
{
	m_keytime = 0;	//�L�[���̓^�C���̏�����
}

//�A�N�V����
void CObjStageClear::Action()
{
	//�V�[���Ɉڂ��Ă����ۂ̃L�[���̓^�C������
	if (m_keytime >= 50)
		m_keytime = 50;	//�^�C����50�ɂȂ����ہA50�Ŏ~�߂�
	else
		m_keytime++;	//�L�[���̓^�C���𑝂₷

	if (Input::GetVKey('Z') == true && m_keytime == TIMELIMIT)	//�L�[���̓^�C�������ɒB�����ꍇ�A�L�[���͂�������
	{
		Scene::SetScene(new CSceneStageChoice());
	}
}

//�h���[
void CObjStageClear::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	Font::StrDraw(L"�X�e�[�W�N���A", 100, 100, 50, c);

}
