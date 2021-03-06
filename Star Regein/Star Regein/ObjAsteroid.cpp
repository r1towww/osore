//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjAsteroid.h"

//使用するネームスペース
using namespace GameL;

CObjAsteroid::CObjAsteroid(float x, float y)
{
	m_px = x;		//位置
	m_py = y;
}

//イニシャライズ
void CObjAsteroid::Init()
{
	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px + 25, m_py + 20, 155.0f, 155.0f, ELEMENT_BLOCK, OBJ_ASTEROID, 1);
}

//アクション
void CObjAsteroid::Action()
{
	//自身のHitBoxを持ってくる
	CHitBox* hit = Hits::GetHitBox(this);

	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//HitBoxの位置の変更
	hit->SetPos(m_px + block->GetScrollx() + 25, m_py + block->GetScrolly() + 20);

}

//ドロー
void CObjAsteroid::Draw()
{
	//描画カラー情報
	float c[4] = { 0.7f,0.7f,0.7f,1.0f };

	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 258.0f;
	src.m_bottom = 220.0f;
	
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//表示位置の設定
	dst.m_top    = 0.0f + m_py + block->GetScrolly();	//描画に対してスクロールの影響を加える
	dst.m_left   = 0.0f + m_px + block->GetScrollx();
	dst.m_right  = 192.0f + m_px + block->GetScrollx();
	dst.m_bottom = 192.0f + m_py + block->GetScrolly();

	//描画
	Draw::Draw(4, &src, &dst, c, 90.0f);
}


