//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameHead.h"
#include "ObjBlueBullet.h"
#include "UtilityModule.h"

//使用するネームスペース
using namespace GameL;

CObjBlueBullet::CObjBlueBullet(float x, float y, float r, float speed)
{
	m_x = x;
	m_y = y;
	m_r = r;
	m_speed = speed;
}

//イニシャライズ
void CObjBlueBullet::Init()
{

	m_ani_time = 0;
	m_ani_frame = 2;
	m_ani = 0;
	m_ani_stop = 0;

	m_time = 300;
	m_del = false;

	m_vx = cos(3.14f / 180.0f*m_r);
	m_vy = sin(3.14f / 180.0f*m_r);

	m_ani_max_time = 7;	//アニメーション間隔幅

	m_vx = cos(3.14f / 180.0f*m_r);
	m_vy = sin(3.14f / 180.0f*m_r);
	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_x, m_y, 25, 25, ELEMENT_ENEMY, OBJ_BLUE_BULLET, 1);
}

//アクション
void CObjBlueBullet::Action()
{
	//行動が制御されている場合（メニュー画面）
	if (g_move_stop_flag == true || g_tutorial_flag == true)
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

	m_time--;

	m_ani_time += ANITIME;

	//弾丸実行処理　-----

	//移動
	m_x += m_vx * m_speed;
	m_y -= m_vy * m_speed;


	//アニメーション用
	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}

	if (m_ani_frame == 5)
	{
		m_ani_frame = 0;
	}

	//敵機弾丸のHitBox更新用ポインター取得
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_x + block->GetScrollx(), m_y + block->GetScrolly());			//HitBoxの位置を敵機弾丸の位置に更新

																				//主人公機オブジェクトと接触したら弾丸削除
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr || hit->CheckElementHit(ELEMENT_BLOCK) || m_time <= 150)
	{
		this->SetStatus(false);    //自身に削除命令を出す
		Hits::DeleteHitBox(this);  //主人公機が所有するHitBoxに削除する
	}
}

//ドロー
void CObjBlueBullet::Draw()
{
	//アニメーション
	int AniData[5] =
	{
		2,1,0,1,2,
	};

	//描写カラー情報　R=RED　G=Green　B=Blue　A=alpha（透過情報）
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

	//ブロック情報を持ってくる
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);


	
	//切り取り位置の設定
		src.m_top = 16.0f;
		src.m_left = 0.0f + (AniData[m_ani_frame] * 16);
		src.m_right = 16.0f + (AniData[m_ani_frame] * 16);
		src.m_bottom = 32.0f;

		//表示位置の設定
		dst.m_top = 0.0f + m_y + block->GetScrolly();
		dst.m_left = 0.0f + m_x + block->GetScrollx();
		dst.m_right = 25.0f + m_x + block->GetScrollx();
		dst.m_bottom = 25.0f + m_y + block->GetScrolly();

		//０番目に登録したグラフィックをsrc・dst・cの情報を元に描画
		Draw::Draw(16, &src, &dst, c, 0);
}