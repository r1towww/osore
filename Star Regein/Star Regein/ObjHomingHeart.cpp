//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"


//使用するヘッダーファイル

#include "ObjHomingHeart.h"
#include "GameHead.h"
#include "UtilityModule.h"

//使用するネームスペース
using namespace GameL;


//コンストラクタ
CObjHomingHeart::CObjHomingHeart(float x, float y)
{
	m_x = x;
	m_y = y;
}

//イニシャライズ
void CObjHomingHeart::Init()
{
	//移動量の初期化
	m_vx = 0.0f;
	m_vy = 0.0f;

	//弾削除のカウント初期化
	m_time = 0.0f;

	//着弾フラグ初期化
	m_hit_flag = false;

	m_ani_frame = 0;
	m_ani_time = 0;

	m_eff.m_top = 0;
	m_eff.m_left = 0;
	m_eff.m_right = 220;
	m_eff.m_bottom = 203;
	m_ani = 0;
	m_ani_time = 0;
	m_ani_stop = 0;

	//当たり判定をセット
	Hits::SetHitBox(this, m_x, m_y, 32, 28, ELEMENT_ENEMY, OBJ_HOMING_HEART, 1);

}

//アクション
void CObjHomingHeart::Action()
{
	//行動が制御されている場合（メニュー画面）
	if (g_move_stop_flag == true)
		return;	//行動を制御

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

	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	CObjBlock* pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

		//主人公機が存在する場合、誘導角度の計算する
		if (hero != nullptr)
		{
			float x;
			float y;

			x = 375 - (m_x + pb->GetScrollx());
			y = 275 - (m_y + pb->GetScrolly());

			float ar = GetAtan2Angle(x, y);

			//主人公機と敵角度があんまりにもかけ離れたら
			m_vx = cos(3.14 / 180 * ar) * 3;
			m_vy = sin(3.14 / 180 * ar) * 3;
		}


	//自身のHitBoxを持ってくる
	CHitBox* hit = Hits::GetHitBox(this);

	//主人公と当たっているか確認
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr || hit->CheckObjNameHit(OBJ_BEAMSABER) != nullptr)
	{
		m_hit_flag = true;//アニメーション開始
		m_vx = 0.0f;
		m_vy = 0.0f;
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

	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//作成したHitBox更新用の入り口を取り出す
	hit->SetPos(m_x + block->GetScrollx(), m_y + block->GetScrolly());//入り口から新しい位置（主人公の位置）情報に置き換える

	//位置の更新
	m_x += m_vx*1.0;
	m_y += m_vy*1.0;

	m_time++;

	if (m_time >= 200)
	{
		m_time = 0.0f;

		this->SetStatus(false);    //自身に削除命令を出す
		Hits::DeleteHitBox(this);  //主人公機が所有するHitBoxに削除する
	}
}

//ドロー
void CObjHomingHeart::Draw()
{

	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,100.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);


	if (m_hit_flag == true)
	{
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 32.0f;
		src.m_bottom = 32.0f;

		//表示位置の設定
		dst.m_top = 0.0f + m_y + block->GetScrolly();
		dst.m_left = 0.0f + m_x + block->GetScrollx();
		dst.m_right = 64.0f + m_x + block->GetScrollx();
		dst.m_bottom = 64.0f + m_y + block->GetScrolly();

		//表示
		Draw::Draw(51, &m_eff, &dst, c, 0.0f);

	}
	else {
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 32.0f;
		src.m_bottom = 28.0f;

		//表示位置の設定
		dst.m_top = 0.0f + m_y + block->GetScrolly();
		dst.m_left = 0.0f + m_x  + block->GetScrollx();
		dst.m_right = 32.0f + m_x  + block->GetScrollx();
		dst.m_bottom = 32.0f + m_y  + block->GetScrolly();

		//表示
		Draw::Draw(50, &src, &dst, c, 0.0f);
	}
}
