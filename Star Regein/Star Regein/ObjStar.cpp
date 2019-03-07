//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameHead.h"
#include "ObjStar.h"

//使用するネームスペース
using namespace GameL;

CObjStar::CObjStar(float x, float y)
{
	m_px = x;		//位置
	m_py = y;
}

//イニシャライズ
void CObjStar::Init()
{
	m_GetStar = false;	//星を取得変数の初期化

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py,64, 64., ELEMENT_STAR, OBJ_STAR, 1);
}

//アクション
void CObjStar::Action()
{
	//自身のHitBoxを持ってくる
	CHitBox* hit = Hits::GetHitBox(this);

	//主人公と当たっているか確認
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)//当たっていたら取得
	{
		hit->SetInvincibility(true);	//触れられなくする
		m_GetStar = true;			//取得した際、色を変える為にフラグをオンにする
		g_StarCount++;				//現在取得している星の数をカウントする
	}

	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBoxの位置の変更
	hit->SetPos(m_px + block->GetScrollx(), m_py + block->GetScrolly());

}

//ドロー
void CObjStar::Draw()
{
	//描画カラー情報
	float b[4] = { 0.4f,0.4f,0.4f,1.0f };	//取得できていない色
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };	//取得できている色

	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

	//切り取り位置の設定
	src.m_top    = 0.0f;
	src.m_left   = 0.0f;
	src.m_right  = 640.0f;
	src.m_bottom = 608.0f;

	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//表示位置の設定
	dst.m_top    = 0.0f + m_py + block->GetScrolly();	//描画に対してスクロールの影響を加える
	dst.m_left   = 0.0f + m_px + block->GetScrollx();
	dst.m_right  = 64.0f + m_px + block->GetScrollx();
	dst.m_bottom = 64.0f + m_py + block->GetScrolly();

	//描画
	if(m_GetStar == false)
		Draw::Draw(6, &src, &dst, b, 0.0f);
	else
		Draw::Draw(6, &src, &dst, c, 0.0f);
}


