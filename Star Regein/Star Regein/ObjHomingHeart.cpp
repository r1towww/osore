//使用するヘッダーファイル
#include <stdlib.h>
#include <time.h>
#include"GameL\DrawTexture.h"
#include"GameL\WinInputs.h"
#include"GameL\SceneManager.h"
#include"GameL\HitBoxManager.h"
#include"GameL\UserData.h" 

#include"GameHead.h"
#include"ObjHomingHeart.h"
#include "UtilityModule.h"

//使用するネームスペース
using namespace GameL;

CObjHomingHeart::CObjHomingHeart(float x, float y, float speed)
{
	m_px = x;	//位置
	m_py = y;

	m_speed = speed;
}

//イニシャライズ
void CObjHomingHeart::Init()
{
	m_vx = 0.0f;	//移動ベクトル
	m_vy = 0.0f;

	m_time = 300;

	alpha = 1.0f;

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 32, 28, ELEMENT_ENEMY, OBJ_HOMING_HEART, 1);
}

//アクション
void CObjHomingHeart::Action()
{

	m_time--;

	//弾丸実行処理　-----
	//主人公機と誘導弾丸で角度を取る
	CObjHero* obj = (CObjHero*)Objs::GetObj(OBJ_HERO);

	CObjBlock* pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//主人公機が存在する場合、誘導角度の計算する
	if (obj != nullptr)
	{

		float x;
		float y;

		x = 375 - (m_px + pb->GetScrollx());
		y = 275 - (m_py + pb->GetScrolly());

		float ar = GetAtan2Angle(x, y);

		//敵の現在の向いている角度を取る
		float br = GetAtan2Angle(m_vx, m_vy);

		//主人公機と敵角度があんまりにもかけ離れたら
		m_vx = cos(3.14 / 180 * ar) * 2;
		m_vy = sin(3.14 / 180 * ar) * 2;
	}

	//移動
	m_px += m_vx*m_speed;
	m_py += m_vy*m_speed;

	//HitBoxの内容を更新
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + block->GetScrollx(), m_py + block->GetScrolly());

	//主人公機オブジェクトと接触したら弾丸削除
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr || hit->CheckElementHit(ELEMENT_BLOCK) || m_time <= 0)
	{
		this->SetStatus(false);    //自身に削除命令を出す
		Hits::DeleteHitBox(this);  //主人公機が所有するHitBoxに削除する
	}
}

//ドロー
void CObjHomingHeart::Draw()
{
	int AniData[4] =
	{ 1,0,2,0, };

	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,alpha };

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

	 //ブロック情報を持ってくる
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 32.0f;
	src.m_bottom = 28.0f;

	//表示位置の設定
	dst.m_top = 0.0f + m_py + block->GetScrolly();
	dst.m_left = 32.0f + m_px + block->GetScrollx();
	dst.m_right = 0.0f + m_px + block->GetScrollx();
	dst.m_bottom = 28.0f + m_py + block->GetScrolly();


	//描画
	Draw::Draw(22, &src, &dst, c, 0.0f);
}