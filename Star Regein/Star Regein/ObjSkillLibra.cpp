//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"

#include "GameHead.h"
#include "ObjSkillLibra.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjSkillLibra::Init()
{


}

//アクション
void CObjSkillLibra::Action()
{
	//Xキーを押した際、スキルを使用
	if (Input::GetVKey('X'))
	{

	}

}

//ドロー
void CObjSkillLibra::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

	//切り取り位置の設定
	src.m_top    = 0.0f;
	src.m_left   = 0.0f;
	src.m_right  = 256.0f;
	src.m_bottom = 256.0f;

	//表示位置の設定
	dst.m_top    = 450.0f;
	dst.m_left   = 650.0f;
	dst.m_right  = 800.0f;
	dst.m_bottom = 600.0f;

	//描画
	Draw::Draw(13, &src, &dst, c, 0.0f);
}