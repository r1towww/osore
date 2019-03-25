//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjMeteo.h"

//使用するネームスペース
using namespace GameL;

CObjMeteo::CObjMeteo(float x, float y)
{
	m_px = x;		//位置
	m_py = y;
}

//イニシャライズ
void CObjMeteo::Init()
{
	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px + 10, m_py, 30, ALLSIZE, ELEMENT_FIELD, OBJ_METEO, 1);
}

//アクション
void CObjMeteo::Action()
{
	//主人公の位置を取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX();
	float hy = hero->GetY();

	//自身のHitBoxを持ってくる
	CHitBox* hit = Hits::GetHitBox(this);

	//主人公と当たっているか確認
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)	//キーを取得
	{
		this->SetStatus(false);		//自身を削除
		Hits::DeleteHitBox(this);
	}

	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBoxの位置の変更
	hit->SetPos(m_px + block->GetScrollx() + 10, m_py + block->GetScrolly());

}

//ドロー
void CObjMeteo::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 50.0f;
	src.m_right = 100.0f;
	src.m_bottom = 50.0f;
	
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//表示位置の設定
	dst.m_top = 0.0f + m_py + block->GetScrolly();	//描画に対してスクロールの影響を加える
	dst.m_left = 0.0f + m_px + block->GetScrollx();
	dst.m_right = ALLSIZE + m_px + block->GetScrollx();
	dst.m_bottom = ALLSIZE + m_py + block->GetScrolly();

	//描画
	Draw::Draw(1, &src, &dst, c, 0.0f);
}


