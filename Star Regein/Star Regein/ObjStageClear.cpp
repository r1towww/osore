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

}

//�A�N�V����
void CObjStageClear::Action()
{
	if (Input::GetVKey('Z') == true)
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
