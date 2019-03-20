//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"

#include "GameHead.h"
#include "ObjSkill.h"

//使用するネームスペース
using namespace GameL;

CObjSkill::CObjSkill()
{

}

//イニシャライズ
void CObjSkill::Init()
{

}

//アクション
void CObjSkill::Action()
{

}

//ドロー
void CObjSkill::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

	//切り取り位置の設定
	src.m_top    = 0.0f;
	src.m_left   = 0.0f   + g_image_reft ;
	src.m_right  = 900.0f + g_image_right;
	src.m_bottom = 600.0f;

	//表示位置の設定
	dst.m_top    = 400.0f;
	dst.m_left   = 600.0f;
	dst.m_right  = 800.0f;
	dst.m_bottom = 600.0f;

	//描画
	Draw::Draw(12, &src, &dst, c, 0.0f);
}