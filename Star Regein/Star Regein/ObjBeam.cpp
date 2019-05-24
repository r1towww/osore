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

	m_beam_time = 100;

	m_beam_flag = false;
	m_ani_flag = true;

	m_time = 0;

	m_d_beam_flag = false;

	m_eff.m_top = 0;
	m_eff.m_left = 0;
	m_eff.m_right = 192;
	m_eff.m_bottom = 192;
	m_ani = 0;
	m_ani_time = 0;
						//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px + 70, m_py - 500, 210, 2300, ELEMENT_ENEMY, OBJ_BEAM, 1);
}

//アクション
void CObjBeam::Action()
{


	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + 70 + block->GetScrollx(), m_py - 500 + block->GetScrolly());

	hit->SetInvincibility(true);

	if (m_ani_flag == true)
	{
		RECT_F ani_src[10] =
		{
			{ 0,    0,  192, 192 },
			{ 0,  192,  384, 192 },
			{ 0,  384,  576, 192 },
			{ 0,  576,  768, 192 },
			{ 0,  768,  960, 192 },
			{ 192,    0,  192, 384 },
			{ 192,  192,  384, 384 },
			{ 192,  384,  576, 384 },
			{ 192,  576,  768, 384 },
			{ 192,  768,  960, 384 },

		};


		//アニメーションのコマ間隔制御
		if (m_ani_time > 6)
		{
			m_ani++;		//アニメーションのコマを1つ進める
			m_ani_time = 0;

			m_eff = ani_src[m_ani];//アニメーションのRECT配列からm_ani番目のRECT情報取得
		}
		else
		{
			m_ani_time++;
		}


		if (m_ani == 10)
		{
			m_ani = 0;
			m_beam_flag = true;
			Audio::Start(20);
			m_ani_flag = false;
		}
	}


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

		if (m_beam_flag == true)
		{
			//アニメーションのコマ間隔制御
			if (m_beam_ani_time > 6 && m_beam_ani != 2 && m_beam_ani != 5)
			{
				m_beam_ani++;		//アニメーションのコマを1つ進める
				m_beam_ani_time = 0;

				m_beam_eff = beam_ani_src[m_beam_ani];//アニメーションのRECT配列からm_ani番目のRECT情報取得
			}
			else if (m_beam_ani_time <= 6 && m_beam_ani != 2 && m_beam_ani != 5)
			{
				m_beam_ani_time++;
			}

			//2番目のときコマの進行を少し遅くする
			if (m_beam_ani == 2)
			{
				m_time++;

				if (m_time >= 50)
				{
					m_beam_ani++;
					m_time = 0;
				}
			}
		}

		//5番目のときフラグをオフにする
		if (m_beam_ani == 5)
		{
			m_time++;
			hit->SetInvincibility(false);
			m_beam_flag = false;
		}

		//フラグがオフかつm_timeが100以上のときコマの進行を少し遅くする
		if (m_beam_flag == false && m_time >= 100)
		{
			if (m_beam_ani_time > 6)
			{
				m_beam_ani--;		//アニメーションのコマを1つ進める
				m_beam_ani_time = 0;

				m_beam_eff = beam_ani_src[m_beam_ani];//アニメーションのRECT配列からm_ani番目のRECT情報取得
			}
			else
			{
				m_beam_ani_time++;
			}

			//0番目のときビームを削除
			if (m_beam_ani == 0)
			{
				m_time = 0;
				m_beam_ani_time = 0;
				this->SetStatus(false);    //自身に削除命令を出す
				Hits::DeleteHitBox(this);  //主人公機が所有するHitBoxに削除する
			}
		}


	if (m_d_beam_flag == true)
	{

	}


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
	//表示位置の設定
	dst.m_top = -500.0f + m_py + block->GetScrolly();
	dst.m_left = 330.0f + m_px + block->GetScrollx();
	dst.m_right = 0.0f + m_px + block->GetScrollx();
	dst.m_bottom = 1800.0f + m_py + block->GetScrolly();
	//エフェクトの描画
	Draw::Draw(37, &m_beam_eff, &dst, c, 0.0f);


	//表示位置の設定
	dst.m_top = -500.0f + m_py + block->GetScrolly();	//描画に対してスクロールの影響を加える
	dst.m_left = 330.0f + m_px + block->GetScrollx();
	dst.m_right = 0.0f + m_px + block->GetScrollx();
	dst.m_bottom = -170.0f + m_py + block->GetScrolly();

	Draw::Draw(36, &m_eff, &dst, c, 0.0f);
}


