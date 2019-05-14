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


CObjStar::CObjStar(float x, float y ,int i,int j,int id)
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
	m_eff.m_right =220;
	m_eff.m_bottom = 203;
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

	if (g_stage_clear != true)
	{
		RECT_F ani_src[8] =
		{
			{ 0,  220,   460, 203 },
			{ 0, 460,   490, 203 },
			{ 0, 490,   930, 203 },
			{ 0, 930,   1160, 203 },
			{ 0, 1160,   1390, 203 },
			{ 0, 1390,   1625, 203 },
			{ 0, 1625,   1850, 203 },
			{ 0, 1850,   2096, 203 },

		};
		//自身のHitBoxを持ってくる
		CHitBox* hit = Hits::GetHitBox(this);

		//主人公と当たっているか確認
		if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)//当たっていたら取得
		{
			//スター獲得音
			Audio::Start(6);
			g_hp += 5.0f;	//星を回収した際、HPを0.5ゲージ回復
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
				if (m_ani_stop >= 8)
				{
					m_ani_flag = false;
					m_eff.m_top = 0;
					m_eff.m_left = 0;
					m_eff.m_right = 220;
					m_eff.m_bottom = 203;

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
	else
	{
		Hits::DeleteHitBox(this);
	}
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


