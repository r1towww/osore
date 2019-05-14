//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

//使用するヘッダーファイル
#include "GameHead.h"
#include "ObjSkillBullet.h"
#include "UtilityModule.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjSkillBullet::CObjSkillBullet(float x, float y, float r)
{
	m_gx = x;
	m_gy = y;
	m_r = r;
}

//イニシャライズ
void CObjSkillBullet::Init()
{
	//移動量の初期化
	m_vx = 0.0f;
	m_vy = 0.0f;

	//弾削除のカウント初期化
	m_time = 0.0f;

	//着弾フラグ初期化
	m_hit_flag = false;

	m_vx = cos(3.14f / 180.0f*m_r);
	m_vy = sin(3.14f / 180.0f*m_r);

	m_ani_frame = 0;
	m_ani_time = 0;

	m_ani = 0;
	m_ani_time = 0;
	m_ani_stop = 0;

	CObjBlock* pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_gx + pb->GetScrollx(), m_gy + pb->GetScrolly(), 25, 25, ELEMENT_SUB, OBJ_SKILL_BULLET, 1);
}

//アクション
void CObjSkillBullet::Action()
{
	//大から小
	RECT_F ani_src[12] =
	{
		{ 0,   0,    32, 32 },
		{ 0,  32,    64, 32 },
		{ 0,  64,    96, 32 },
		{ 0,  96,   128, 32 },
		{ 0, 128,   160, 32 },
		{ 0, 160,   192, 32 },
		{ 0, 192,   224, 32 },
		{ 0, 224,   256, 32 },
		{ 0, 256,   288, 32 },
		{ 0, 288,   320, 32 },
		{ 0, 320,   352, 32 },
	};

	//------------双子座弾丸----------------
	CObjBlock* pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBoxの内容を更新
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_gx + pb->GetScrollx(), m_gy + pb->GetScrolly());

	//移動
	m_gx += m_vx * HERO_VEC;
	m_gy -= m_vy * HERO_VEC;

	m_time++;

	//各敵と当たっているか確認
	if (hit->CheckObjNameHit(OBJ_COW) != nullptr ||
		hit->CheckObjNameHit(OBJ_TWINS_BLUE) != nullptr ||
		hit->CheckObjNameHit(OBJ_TWINS_RED) != nullptr ||
		hit->CheckObjNameHit(OBJ_WOMAN) != nullptr ||
		hit->CheckObjNameHit(OBJ_LEO) != nullptr ||
		hit->CheckObjNameHit(OBJ_LIBRA) != nullptr)//当たっていたら取得  
	{
		m_hit_flag = true;
		m_vx = 0;
		m_vy = 0;
	}

	if (m_hit_flag == true)
	{
		//アニメーションのコマ間隔制御
		if (m_ani_time > 0)
		{

			m_ani++;	//アニメーションのコマを１つ進める
			m_ani_time = 0;

			m_eff = ani_src[m_ani];//アニメーションのRECT配列からm_ani番目のRECT情報取得
			m_ani_stop++;
			if (m_ani_stop >= 11)
			{
				m_eff.m_top = 0;
				m_eff.m_left = 0;
				m_eff.m_right = 220;
				m_eff.m_bottom = 203;

				this->SetStatus(false);
				Hits::DeleteHitBox(this);

			}

		}
		else
		{
			m_ani_time++;
		}
	}

	if (m_time >= 100)

	{
		m_time = 0.0f;

		this->SetStatus(false);    //自身に削除命令を出す
		Hits::DeleteHitBox(this);  //主人公機が所有するHitBoxに削除する
		m_hit_flag = false;
	}

	//位置の更新
	m_gx += m_vx;
	m_gy += m_vy;
}
//ドロー
void CObjSkillBullet::Draw()
{

	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//弾丸が当たったときの画像描画
	if (m_hit_flag == true)
	{
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 32.0f;
		src.m_bottom = 32.0f;

		//表示位置の設定
		dst.m_top = 0.0f + m_gy + block->GetScrolly();
		dst.m_left = 0.0f + m_gx + block->GetScrollx();
		dst.m_right = 64.0f + m_gx + block->GetScrollx();
		dst.m_bottom = 64.0f + m_gy + block->GetScrolly();

		//表示
		Draw::Draw(51, &m_eff, &dst, c, 0.0f);
	}
	//
	else if (g_gemini_bullet_check == false)
	{
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 16.0f;
		src.m_bottom = 16.0f;

		//表示位置の設定
		dst.m_top = 0.0f + m_gy + block->GetScrolly();
		dst.m_left = 0.0f + m_gx + block->GetScrollx();
		dst.m_right = 25.0f + m_gx + block->GetScrollx();
		dst.m_bottom = 25.0f + m_gy + block->GetScrolly();

		//０番目に登録したグラフィックをsrc・dst・cの情報を元に描画
		Draw::Draw(16, &src, &dst, c, 0);
	}
	else if (g_gemini_bullet_check == true)
	{
		//切り取り位置の設定
		src.m_top = 16.0f;
		src.m_left = 0.0f;
		src.m_right = 16.0f;
		src.m_bottom = 32.0f;

		//表示位置の設定
		dst.m_top = 0.0f + m_gy + block->GetScrolly();
		dst.m_left = 0.0f + m_gx + block->GetScrollx();
		dst.m_right = 25.0f + m_gx + block->GetScrollx();
		dst.m_bottom = 25.0f + m_gy + block->GetScrolly();

		//０番目に登録したグラフィックをsrc・dst・cの情報を元に描画
		Draw::Draw(16, &src, &dst, c, 0);
	}
}
