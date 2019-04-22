//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjBlackhole.h"

//使用するネームスペース
using namespace GameL;

float* g_blackhole_x[10];//全てのブラックホールのX位置を把握する
float* g_blackhole_y[10];//全てのブラックホールのY位置を把握する

CObjBlackhole::CObjBlackhole(float x, float y,int id)
{
	m_px = x;		//位置
	m_py = y;

	m_blackhole_id = id;
}

//イニシャライズ
void CObjBlackhole::Init()
{
	m_ani = 0;			//アニメーション用
	m_ani_time = 0;		//アニメーション間隔タイム
	m_eff.m_top = 0;
	m_eff.m_left = 0;
	m_eff.m_right = 200;
	m_eff.m_bottom = 200;

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px + 20, m_py + 20, 20.0f, 24.0f, ELEMENT_FIELD, OBJ_BLACKHOLE + g_blackhole_cnt, 1);
	//作成のたびにカウントを増やし、別のオブジェクトとする
}

//アクション
void CObjBlackhole::Action()
{
	//自身のHitBoxを持ってくる
	CHitBox* hit = Hits::GetHitBox(this);
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);


	//エフェクト用
	RECT_F ani_src[10] =
	{
		{ 0,   0,  192, 192 },
		{ 0, 192,  384, 192 },
		{ 0, 384,  576, 192 },
		{ 0, 576,  768, 192 },
		{ 0, 768,  960, 192 },
		{ 0,   0,  192, 384 },
		{ 0, 192,  384, 384 },
		{ 0, 384,  576, 384 },
		{ 0, 576,  768, 384 },
		{ 0, 768,  960, 384 },
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
	//８番目（画像最後）まで進んだら、削除
	if (m_ani == 10)
	{
		m_ani = 0;
	}

	//HitBoxの位置の変更
	hit->SetPos(m_px + block->GetScrollx() + 20, m_py + block->GetScrolly() + 20);
}

//ドロー
void CObjBlackhole::Draw()
{
	//描画カラー情報
	float c[4] = { 0.5f,0.5f,0.5f,1.0f };

	RECT_F dst;	//描画先表示位置

				//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//表示位置の設定
	dst.m_top    = 0.0f + m_py + block->GetScrolly();	//描画に対してスクロールの影響を加える
	dst.m_left   = 0.0f + m_px + block->GetScrollx();
	dst.m_right  = ALLSIZE + m_px + block->GetScrollx();
	dst.m_bottom = ALLSIZE + m_py + block->GetScrolly();

	//描画
	Draw::Draw(12, &m_eff, &dst, c, 90.0f);
}


