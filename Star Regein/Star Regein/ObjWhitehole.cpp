//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjWhitehole.h"

//使用するネームスペース
using namespace GameL;

float* g_whitehole_x[10];//全てのホワイトホールのX位置を把握する
float* g_whitehole_y[10];//全てのホワイトホールのY位置を把握する

CObjWhitehole::CObjWhitehole(float x, float y)
{
	m_px = x;		//位置
	m_py = y;
}

//イニシャライズ
void CObjWhitehole::Init()
{
	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px + 20, m_py + 20, 20.0f, 24.0f, ELEMENT_FIELD, OBJ_WHITEHOLE, 1);
}

//アクション
void CObjWhitehole::Action()
{

}

//ドロー
void CObjWhitehole::Draw()
{
	//描画カラー情報
	float c[4] = { 0.5f,0.5f,0.5f,1.0f };

	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

	//切り取り位置の設定
	src.m_top    = 0.0f;
	src.m_left   = 0.0f;
	src.m_right  = 256.0f;
	src.m_bottom = 256.0f;

	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//表示位置の設定
	dst.m_top    = 0.0f + m_py + block->GetScrolly();	//描画に対してスクロールの影響を加える
	dst.m_left   = 0.0f + m_px + block->GetScrollx();
	dst.m_right  = ALLSIZE + m_px + block->GetScrollx();
	dst.m_bottom = ALLSIZE + m_py + block->GetScrolly();

	//描画
	Draw::Draw(12, &src, &dst, c, 90.0f);
}


