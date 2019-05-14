//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjBreakBigRock.h"

//使用するネームスペース
using namespace GameL;

CObjBreakBigRock::CObjBreakBigRock(float x, float y, int i, int j)
{
	m_px = x;		//位置
	m_py = y;
	m_i = i;	//作成時にマップ上の座標を取得
	m_j = j;
}

//イニシャライズ
void CObjBreakBigRock::Init()
{
	m_cnt = 0;	//消滅カウント用
	m_f = false;	//無敵時間用フラグ

	m_bom_x = 0;	//爆発エフェクトの表示位置
	m_bom_y = 0;

	m_ani = 0;			//アニメーション用
	m_ani_time = 0;		//アニメーション間隔タイム
	m_eff.m_top = 0;
	m_eff.m_left = 0;
	m_eff.m_right = 200;
	m_eff.m_bottom = 200;
	m_eff_flag = false;		//エフェクト開始用フラグ
	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px + 25.0f, m_py + 20.0f , 155.0f, 155.0f, ELEMENT_BLOCK, OBJ_BREAK_BIGROCK, 1);
}

//アクション
void CObjBreakBigRock::Action()
{
	//自身のHitBoxを持ってくる
	CHitBox* hit = Hits::GetHitBox(this);
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//ヒーローの情報を持ってくる
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//主人公と当たっている、かつダッシュフラグがオン、かつ無敵フラグがオンの場合
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr && hero->GetDashF() == true && m_f == false)
	{
		m_cnt++;	//カウントを1プラスする
		m_f = true;	//無敵フラグをオンにする
		m_eff_flag = true;		//フラグをオンにして、エフェクトの開始
		if (m_cnt == 3)
		{
			Audio::Start(18);
		}
		Audio::Start(17);

	}
	//フラグがオンの場合、エフェクトに移る
	if (m_eff_flag == true)
	{
		//エフェクト用
		RECT_F ani_src[10] =
		{
			{   0,    0,  192, 192 },
			{   0,  192,  384, 192 },
			{   0,  384,  576, 192 },
			{   0,  576,  768, 192 },
			{   0,  768,  960, 192 },
			{ 192,    0,  192, 384 },
			{ 192,  192,  384, 384 },
			{ 192,  384,  576, 384 },
			{ 192,  576,  768, 384 },
			{ 192,  768,  960, 384 },
		};
		//アニメーションのコマ間隔制御
		if (m_ani_time > 2)
		{
			m_ani++;		//アニメーションのコマを1つ進める
			m_ani_time = 0;

			m_eff = ani_src[m_ani];//アニメーションのRECT配列からm_ani番目のRECT情報取得
		}
		else
		{
			m_ani_time++;
		}
		//カウントが3で、9番目（画像最後）まで進んだ場合
		if (m_ani == 9 && m_cnt == 3)
		{
			g_map[m_i][m_j] = 0;	//マップ上の座標を0にして、マップに表示されなくする
			Hits::DeleteHitBox(this);		//ヒットボックスの削除
			this->SetStatus(false);			//描画の削除
		}
		//カウントが3未満で、9番目（画像最後）まで進んだら
		if (m_ani == 9)
		{
			m_ani = 0;	//アニメーションを０に戻す
			m_eff_flag = false;	//エフェクトフラグをオフにする
			m_f = false;	//無敵フラグをオフ
		}

	}
	//HitBoxの位置の変更
	hit->SetPos(m_px + block->GetScrollx() + 25.0f, m_py + block->GetScrolly() + 20.0f);
}

//ドロー
void CObjBreakBigRock::Draw()
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
	dst.m_right  = 192.0f + m_px + block->GetScrollx();
	dst.m_bottom = 192.0f + m_py + block->GetScrolly();

	//描画
	Draw::Draw(4, &src, &dst, c, 90.0f);

	if (m_eff_flag == true)
	{
		//カウント数によって、表示場所を変更
		if (m_cnt == 1) {
			m_bom_x = 50.0f;
			m_bom_y = 50.0f;
		}
		else if (m_cnt == 2) {
			m_bom_x = -50.0f;
			m_bom_y = -50.0f;
		}
		else if (m_cnt == 3) {
			m_bom_x = 0.0f;
			m_bom_y = 0.0f;
		}
		//エフェクト用表示位置の設定
		dst.m_top    = -30.0f + m_py + block->GetScrolly() + m_bom_y;	//描画に対してスクロールの影響を加える
		dst.m_left   = -30.0f + m_px + block->GetScrollx() + m_bom_x;
		dst.m_right  = 230.0f + m_px + block->GetScrollx() + m_bom_x;
		dst.m_bottom = 230.0f + m_py + block->GetScrolly() + m_bom_y;
		//描画
		Draw::Draw(17, &m_eff, &dst, c, 90.0f);
	}

}


