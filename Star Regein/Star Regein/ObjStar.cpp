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

float  g_star_x[5];
float  g_star_y[5];

bool g_contact_star_f[5] = { false,false,false,false,false };//主人公が接触している星の確認フラグ


CObjStar::CObjStar(float x, float y ,int i,int j,int id)
{
	m_px = x;		//位置
	m_py = y;
	m_i = i;
	m_j = j;

	m_id = id;

}

//イニシャライズ
void CObjStar::Init()
{
	m_ani = 0;
	m_ani_time = 0;
	m_ani_stop = 0;
	m_ani_flag = false;

	m_GetStar = false;	//星を取得変数の初期化

	m_eff.m_top    =   0;
	m_eff.m_left   =   0;
	m_eff.m_right  = 192;
	m_eff.m_bottom = 192;
	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py,64, 64, ELEMENT_STAR, OBJ_STAR, 1);
}

//アクション
void CObjStar::Action()
{


	if (g_stage_clear != true)
	{
		//エフェクト用
		RECT_F ani_src[15] =
		{
			{ 0,   0, 192, 192 },
			{ 0, 192, 384, 192 },
			{ 0, 384, 576, 192 },
			{ 0, 576, 768, 192 },
			{ 0, 768, 960, 192 },
			{ 192,   0, 192, 384 },
			{ 192, 192, 384, 384 },
			{ 192, 384, 576, 384 },
			{ 192, 576, 768, 384 },
			{ 192, 768, 960, 384 },
			{ 384,   0, 192, 576 },
			{ 384, 192, 384, 576 },
			{ 384, 384, 576, 576 },
			{ 384, 576, 768, 576 },
			{ 384, 768, 960, 576 },
		};
		//自身のHitBoxを持ってくる
		CHitBox* hit = Hits::GetHitBox(this);

		//主人公と当たっているか確認
		if (hit->CheckObjNameHit(OBJ_HERO) != nullptr && m_GetStar == false)//当たっていたら取得
		{
			//スター獲得音
			Audio::Start(6);
			g_hp += 5.0f;	//星を回収した際、HPを0.5ゲージ回復
			m_ani_flag = true;//アニメーション開始
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
				if (m_ani == 14)
				{
					m_ani_flag = false;
				}
			}
			else
			{
				m_ani_time++;
			}

		}
		//ブロック情報を持ってくる
		CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
		//HitBoxの位置の変更
		hit->SetPos(m_px + block->GetScrollx(), m_py + block->GetScrolly());
	}

	//ボス戦の場合
	if (g_stage == EarthStar && g_Boss_Spawn ==true)
	{
		m_GetStar = true;			//色を変える為にフラグをオンにする
		g_StarCount = 5;

		//自身のHitBoxを持ってくる
		CHitBox* hit = Hits::GetHitBox(this);
		if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
		{
			g_contact_star_f[m_id] = true;
		}
		else
		{
			g_contact_star_f[m_id] = false;
		}
	}
}

//ドロー
void CObjStar::Draw()
{

	//描画カラー情報
	float b[4] = { 0.4f,0.4f,0.4f,1.0f };	//取得できていない色
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };	//取得できている色
	RECT_F src;
	RECT_F dst;	//描画先表示位置

	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//切り取り位置
	src.m_top = 0;
	src.m_left = 0;
	src.m_right = 220;
	src.m_bottom = 203;

	//表示位置の設定
	dst.m_top    = 0.0f + m_py + block->GetScrolly();	//描画に対してスクロールの影響を加える
	dst.m_left   = 0.0f + m_px + block->GetScrollx();
	dst.m_right  = 64.0f + m_px + block->GetScrollx();
	dst.m_bottom = 64.0f + m_py + block->GetScrolly();

	//描画(カラー変更)
	if(m_GetStar == false)
		Draw::Draw(6, &src, &dst, b, 0.0f);
	else
		Draw::Draw(6, &src, &dst, c, 0.0f);

	//表示位置の設定
	dst.m_top = -64.0f + m_py + block->GetScrolly();	//描画に対してスクロールの影響を加える
	dst.m_left = -64.0f + m_px + block->GetScrollx();
	dst.m_right = 128.0f + m_px + block->GetScrollx();
	dst.m_bottom = 128.0f + m_py + block->GetScrolly();

	if (m_ani_flag == true)
	{
		Draw::Draw(99, &m_eff, &dst, c, 0.0f);
	}
}


