//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameHead.h"
#include "ObjBeam.h"

//使用するネームスペース
using namespace GameL;


CObjBeam::CObjBeam(float x, float y)
{
	m_px = x;		//位置
	m_py = y;

}

//イニシャライズ
void CObjBeam::Init()
{
	//ビームアニメーション関連初期化
	m_beam_eff.m_top = 0;	//エフェクト初期値の初期化
	m_beam_eff.m_left = 0;
	m_beam_eff.m_right = 65;
	m_beam_eff.m_bottom = 497;

	m_beam_ani = 0;			//アニメーション用
	m_beam_ani_time = 0;		//アニメーション間隔タイム

	m_beam_flag = false;
	m_beam_time = 100;


	m_eff.m_top = 0;
	m_eff.m_left = 0;
	m_eff.m_right = 220;
	m_eff.m_bottom = 203;
	m_ani = 0;
	m_ani_time = 0;
	m_ani_stop = 0;
	m_ani_flag = false;
						//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_STAR, OBJ_STAR, 1);
}

//アクション
void CObjBeam::Action()
{

	//上空に飛んでビーム攻撃
	//エフェクト用
	RECT_F beam_ani_src[7] =
	{
		{ 0,   0,  65, 536 },
		{ 0, 73,  137, 536 },
		{ 0, 145,  210, 536 },
		{ 0, 217,  282, 536 },
		{ 0, 289,  353, 536 },
		{ 0, 361,  426, 536 },
		{ 0, 433,  497, 536 },
	};

	//アニメーションのコマ間隔制御
	if (m_beam_ani_time > 3)
	{
		m_beam_ani++;		//アニメーションのコマを1つ進める
		m_beam_ani_time = 0;

		m_beam_eff = beam_ani_src[m_beam_ani];//アニメーションのRECT配列からm_ani番目のRECT情報取得
	}
	else
	{
		m_beam_ani_time++;
	}


	if (m_beam_ani == 7)
	{
		m_beam_ani = 0;
		this->SetStatus(false);    //自身に削除命令を出す
		Hits::DeleteHitBox(this);  //主人公機が所有するHitBoxに削除する
	}


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

		//Hits::DeleteHitBox(this);
}

//ドロー
void CObjBeam::Draw()
{

	//描画カラー情報
	float b[4] = { 0.4f,0.4f,0.4f,1.0f };	//取得できていない色
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };	//取得できている色

	RECT_F dst;	//描画先表示位置

				//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//ワープ
	if (m_beam_flag == true)
	{
		//表示位置の設定
		dst.m_top = 0.0f + m_py + block->GetScrolly();
		dst.m_left = 200.0f + m_px + block->GetScrollx();
		dst.m_right = 0.0f + m_px + block->GetScrollx();
		dst.m_bottom = 1000.0f + m_py + block->GetScrolly();
		//エフェクトの描画
		Draw::Draw(35, &m_beam_eff, &dst, c, 0.0f);

	}
	else
	{
		m_beam_ani = 0;
	}

	//表示位置の設定
	dst.m_top = 0.0f + m_py + block->GetScrolly();	//描画に対してスクロールの影響を加える
	dst.m_left = 0.0f + m_px + block->GetScrollx();
	dst.m_right = 64.0f + m_px + block->GetScrollx();
	dst.m_bottom = 64.0f + m_py + block->GetScrolly();

	Draw::Draw(36, &m_beam_eff, &dst, c, 0.0f);
}


