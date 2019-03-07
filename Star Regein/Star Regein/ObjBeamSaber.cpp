//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

//使用するヘッダーファイル
#include "GameHead.h"
#include "ObjBeamSaber.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjBeamSaber::CObjBeamSaber(float x, float y)
{
	m_x = x;
	m_y = y;
}

//イニシャライズ
void CObjBeamSaber::Init()
{

}

//アクション
void CObjBeamSaber::Action()
{
	//主人公の位置を取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX();
	float hy = hero->GetY();

	//位置の更新
	m_x = hx+14;
	m_y = hy+32;
}

//ドロー
void CObjBeamSaber::Draw()
{


	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	//切り取り位置の設定
	src.m_top    = 0.0f;
	src.m_left   = 0.0f;
	src.m_right  = 32.0f;
	src.m_bottom = 64.0f;

	
	//表示位置の設定
	dst.m_top    = 0.0f+m_y;
	dst.m_left   = 0.0f+m_x;
	dst.m_right  = 32.0f+m_x;
	dst.m_bottom = 32.0f+m_y;

	//表示
	Draw::Draw(2, &src, &dst, c, 0.0f);
}
