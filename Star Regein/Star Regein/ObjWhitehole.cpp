//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjWhitehole.h"

//使用するネームスペース
using namespace GameL;

CObjWhitehole::CObjWhitehole(float x, float y)
{
	m_px = x;		//位置
	m_py = y;
}

//イニシャライズ
void CObjWhitehole::Init()
{
	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px + 20, m_py + 20, 20.0f, 24.0f, ELEMENT_FIELD, OBJ_ASTEROID, 1);
}

//アクション
void CObjWhitehole::Action()
{
	//自身のHitBoxを持ってくる
	CHitBox* hit = Hits::GetHitBox(this);
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//ホワイトホールの情報を持ってくる
	CObjBlackhole* blackhole = (CObjBlackhole*)Objs::GetObj(OBJ_BLACKHOLE);
	float bx = blackhole->Getx() - HOLEBALANCE_X;	//移動先X位置の調整
	float by = blackhole->Gety() - HOLEBALANCE_Y;	//移動先Y位置の調整

	//主人公と当たっているか確認
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		hit->SetInvincibility(true);	//無敵オン
		m_time = SETTIME;	//時間をセットする
		block->SetScrollx(-bx);	//ブラックホールの位置に移動させる
		block->SetScrolly(-by + TELEPORTBALANCE);	//位置が被らないようにずらす
	}
	
	/* 無敵時間用 */
	//時間がセットされている際
	if (m_time > 0) {
		m_time--;	//時間を減らす
		if (m_time <= 0) {	//0以下になったら
			m_time = 0;
			hit->SetInvincibility(false);	//無敵をオフ
		}
	}

	//HitBoxの位置の変更
	hit->SetPos(m_px + block->GetScrollx() + 20, m_py + block->GetScrolly() + 20);
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


