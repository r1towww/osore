//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjHeart.h"

//使用するネームスペース
using namespace GameL;

float g_mp;
float g_max_mp;

CObjMP::CObjMP()
{

}

//イニシャライズ
void CObjMP::Init()
{

}

//アクション
void CObjMP::Action()
{


}

//ドロー
void CObjMP::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 600.0f;
	src.m_bottom = 300.0f;

	//表示位置の設定
	dst.m_top = 80.0f;
	dst.m_left = 0.0f;
	dst.m_right = (g_mp / g_max_mp)*128.0f;;
	dst.m_bottom = 105.0f;

	//描画
	Draw::Draw(11, &src, &dst, c, 0.0f);


}