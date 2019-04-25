//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjBreakRock.h"

//使用するネームスペース
using namespace GameL;

CObjBreakRock::CObjBreakRock(float x, float y,int i, int j)
{
	m_px = x;		//位置
	m_py = y;
	m_i = i;	//作成時にマップ上の座標を取得
	m_j = j;	
}

//イニシャライズ
void CObjBreakRock::Init()
{
	m_ani = 0;			//アニメーション用
	m_ani_time = 0;		//アニメーション間隔タイム
	m_eff.m_top    = 0;
	m_eff.m_left   = 0;
	m_eff.m_right  = 200;
	m_eff.m_bottom = 200;
	m_eff_flag = false;		//エフェクト開始用フラグ
	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 64.0f, 64.0f, ELEMENT_BLOCK, OBJ_BREAK_ROCK, 1);
}

//アクション
void CObjBreakRock::Action()
{
	//自身のHitBoxを持ってくる
	CHitBox* hit = Hits::GetHitBox(this);
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//ヒーローの情報を持ってくる
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	////主人公と当たっている、かつダッシュフラグがオンの場合
	//if (hit->CheckObjNameHit(OBJ_HERO) != nullptr && hero->GetDashF() == true)
	//{
	//	//this->SetStatus(false);		//自身を削除
	//	//Hits::DeleteHitBox(this);

	//	m_eff_flag = true;		//フラグをオンにして、エフェクトの開始
	//}
	//if (m_eff_flag == true)
	//{
	//	//エフェクト用
	//	RECT_F ani_src[10] =
	//	{
	//		{   0,    0,  192, 192 },
	//		{   0,  192,  384, 192 },
	//		{   0,  384,  576, 192 },
	//		{   0,  576,  768, 192 },
	//		{   0,  768,  960, 192 },
	//		{ 192,    0,  192, 400 },
	//		{ 192,  192,  384, 400 },
	//		{ 192,  384,  576, 400 },
	//		{ 192,  576,  768, 400 },
	//		{ 192,  768,  960, 400 },
	//	};
	//	//アニメーションのコマ間隔制御
	//	if (m_ani_time > 2)
	//	{
	//		m_ani++;		//アニメーションのコマを1つ進める
	//		m_ani_time = 0;

	//		m_eff = ani_src[m_ani];//アニメーションのRECT配列からm_ani番目のRECT情報取得
	//	}
	//	else
	//	{
	//		m_ani_time++;	
	//	}
	//	//9番目（画像最後）まで進んだら、削除
	//	if (m_ani == 9)
	//	{
	//		Hits::DeleteHitBox(this);
	//		this->SetStatus(false);
	//	}
	//}
	////HitBoxの位置の変更
	//hit->SetPos(m_px + block->GetScrollx(), m_py + block->GetScrolly());

}

//ドロー
void CObjBreakRock::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,0.5f,1.0f };

	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

	//切り取り位置の設定
	src.m_top    = 0.0f;
	src.m_left   = 0.0f;
	src.m_right  = 258.0f;
	src.m_bottom = 220.0f;

	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//表示位置の設定
	dst.m_top    = 0.0f + m_py + block->GetScrolly();	//描画に対してスクロールの影響を加える
	dst.m_left   = 0.0f + m_px + block->GetScrollx();
	dst.m_right  = 12.0f + m_px + block->GetScrollx();
	dst.m_bottom = 12.0f + m_py + block->GetScrolly();

	//描画
	Draw::Draw(4, &src, &dst, c, 90.0f);

	if (m_eff_flag == true)
	{
		//エフェクト用表示位置の設定
		dst.m_top = -30.0f + m_py + block->GetScrolly();	//描画に対してスクロールの影響を加える
		dst.m_left = -30.0f + m_px + block->GetScrollx();
		dst.m_right = 94.0f + m_px + block->GetScrollx();
		dst.m_bottom = 94.0f + m_py + block->GetScrolly();
		//描画
		Draw::Draw(17, &m_eff, &dst, c, 90.0f);
	}

}


