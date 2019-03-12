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

float g_hp;
float g_max_hp;

CObjHeart::CObjHeart()
{

}

//イニシャライズ
void CObjHeart::Init()
{

}

//アクション
void CObjHeart::Action()
{
	

}

//ドロー
void CObjHeart::Draw()
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
	dst.m_top = 26.0f;
	dst.m_left = 0.0f;
	dst.m_right = (g_hp / g_max_hp)*128.0f;
	dst.m_bottom = 50.0f;

	//描画
	Draw::Draw(10, &src, &dst, c, 0.0f);

		
}