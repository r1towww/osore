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

CObjStar::CObjStar(float x, float y ,int i,int j)
{
	m_px = x;		//位置
	m_py = y;
	m_i = i;
	m_j = j;

}

//イニシャライズ
void CObjStar::Init()
{
	m_eff.m_top = 0;
	m_eff.m_left = 0;
	m_eff.m_right =640;
	m_eff.m_bottom = 608;
	m_ani = 0;
	m_ani_time = 0;
	m_ani_stop = 0;
	m_ani_flag = false;

	m_GetStar = false;	//星を取得変数の初期化
	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py,64, 64, ELEMENT_STAR, OBJ_STAR, 1);
}

//アクション
void CObjStar::Action()
{
	RECT_F ani_src[5] =
	{
		{ 0,   0,   950, 640 },
		{ 0, 950,   1900, 640 },
		{ 0, 1900,   2851, 640 },
		{ 0, 2851,   3801, 640 },
		{ 0, 4752,   4752, 640 },
	};
	//自身のHitBoxを持ってくる
	CHitBox* hit = Hits::GetHitBox(this);

	//主人公と当たっているか確認
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)//当たっていたら取得
	{
		m_ani_flag = true;//アニメーション開始
		hit->SetInvincibility(true);	//触れられなくする
		m_GetStar = true;			//取得した際、色を変える為にフラグをオンにする
		g_StarCount++;				//現在取得している星の数をカウントする
		g_map[m_i][m_j] = 4;	//ミニマップ上で星を表示する
	}
	if (m_ani_flag == true)
	{
		//アニメーションのコマ間隔制御
		if (m_ani_time > 2)
		{

			m_ani++;	//アニメーションのコマを１つ進める
			m_ani_time = 0;

			m_eff = ani_src[m_ani];//アニメーションのRECT配列からm_ani番目のRECT情報取得
			m_ani_stop++;
			if (m_ani_stop >= 10)
			{
				m_ani_flag = false;
				m_eff.m_top = 0;
				m_eff.m_left = 0;
				m_eff.m_right = 640;
				m_eff.m_bottom = 608;

			}
		}
		else
		{
			m_ani_time++;
		}
		//3コマ目突入後、0コマ目に戻す事でアニメーションを無限ループさせる。
		if (m_ani == 3)
		{
			m_ani = 0;
		}

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

	RECT_F dst;	//描画先表示位置


	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//表示位置の設定
	dst.m_top    = 0.0f + m_py + block->GetScrolly();	//描画に対してスクロールの影響を加える
	dst.m_left   = 0.0f + m_px + block->GetScrollx();
	dst.m_right  = 64.0f + m_px + block->GetScrollx();
	dst.m_bottom = 64.0f + m_py + block->GetScrolly();

	//描画(カラー変更)
	if(m_GetStar == false)
		Draw::Draw(6, &m_eff, &dst, b, 0.0f);
	else
		Draw::Draw(6, &m_eff, &dst, c, 0.0f);
}


