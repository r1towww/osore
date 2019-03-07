//使用するヘッダーファイル
#include <stdlib.h>
#include <time.h>
#include"GameL\DrawTexture.h"
#include"GameL\WinInputs.h"
#include"GameL\SceneManager.h"
#include"GameL\HitBoxManager.h"
#include"GameL\UserData.h" 

#include"GameHead.h"
#include"ObjCow.h"
#include "UtilityModule.h"

//使用するネームスペース
using namespace GameL;

CObjCow::CObjCow(float x, float y)
{
	m_px = x;	//位置
	m_py = y;
}

//イニシャライズ
void CObjCow::Init()
{
	m_hp = 5;        //体力
	m_vx = 0.0f;	//移動ベクトル
	m_vy = 0.0f;
	m_posture = 0.0f;//正面(0.0f) 左(1.0f) 右(2.0f) 背面(3.0f)

	m_ani_time = 0;
	m_ani_frame = 1;	//静止フレームを初期にする

	m_speed_power = 2.0f;//通常速度
	m_ani_max_time = 5;	//アニメーション間隔幅

	m_movey = true; //true=背面　false=正面
	m_movex = true;	//true=右　false=左

					//blockとの衝突状態確認用
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_key_f = false;		//無敵時間行動制御
	m_f = false;

	m_ftime = 0;

	m_time = 30;

	alpha = 1.0;

	srand(time(NULL));

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px + 9, m_py + 7, 30, 40, ELEMENT_ENEMY, OBJ_COW, 1);
}

//アクション
void CObjCow::Action()
{
	m_ftime++;

	//ブロック衝突で向き変更
	if (m_hit_up == true)
	{
		m_movey = true;
	}
	if (m_hit_down == true)
	{
		m_movey = false;
	}
	if (m_hit_left == true)
	{
		m_movex = false;
	}
	if (m_hit_right == true)
	{
		m_movex = true;
	}

	//方向
	if (m_movey == true)
	{
		m_vy = 1;
		m_posture = 0.0f;
		m_ani_time += 1;
	}
	if (m_movey == false)
	{
		m_vy = -1;
		m_posture = 3.0f;
		m_ani_time += 1;
	}
	if (m_movex == true)
	{
		m_vx = 1;
		m_posture = 1.0f;
		m_ani_time += 1;
	}
	if (m_movex == false)
	{
		m_vx = -1;
		m_posture = 2.0f;
		m_ani_time += 1;
	}

	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}

	if (m_ani_frame == 4)
	{
		m_ani_frame = 0;
	}

	//主人公の位置を取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX();
	float hy = hero->GetY();

	//ブロック情報を持ってくる
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBoxの内容を更新
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + 9 + block->GetScrollx(), m_py + 7 + block->GetScrolly());

	//ELEMENT_MAGICを持つオブジェクトと接触したら
	if (hit->CheckElementHit(ELEMENT_MAGIC) == true)
	{
		//敵が主人公とどの角度で当たっているかを確認
		HIT_DATA**hit_data;							//当たった時の細かな情報を入れるための構造体
		hit_data = hit->SearchElementHit(ELEMENT_MAGIC);//hit_dataに主人公と当たっている他全てのHitBoxとの情報を入れる

		for (int i = 0; i < hit->GetCount(); i++)
		{
			//攻撃の左右に当たったら
			if (hit_data[i] == nullptr)
				continue;

			float r = hit_data[i]->r;
			if ((r < 45 && r >= 0) || r > 315)
			{
				m_vx = -10.0f;//左に移動させる
			}
			if (r >= 45 && r < 135)
			{
				m_vy = 10.0f;//上に移動させる
			}
			if (r >= 135 && r < 225)
			{
				m_vx = 10.0f;//右に移動させる
			}
			if (r >= 225 && r < 315)
			{
				m_vy = -10.0f;//したに移動させる
			}
		}
		m_hp -= 1;
		m_f = true;
		m_key_f = true;
	}

	//位置の更新
	m_px += m_vx*1.0;
	m_py += m_vy*1.0;

	//HPが0になったら破棄
	if (m_hp <= 0)
	{
		//敵削除
		this->SetStatus(false);
		Hits::DeleteHitBox(this);
	}
}

//ドロー
void CObjCow::Draw()
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
	src.m_top = 64.0f * m_posture;
	src.m_left = 0.0f + (AniData[m_ani_frame] * 64);
	src.m_right = 64.0f + (AniData[m_ani_frame] * 64);
	src.m_bottom = src.m_top + 64.0f;

	//表示位置の設定
	dst.m_top = 0.0f + m_py + block->GetScrolly();
	dst.m_left = 64.0f + m_px + block->GetScrollx();
	dst.m_right = 0.0f + m_px + block->GetScrollx();
	dst.m_bottom = 64.0f + m_py + block->GetScrolly();


	//描画
	Draw::Draw(3, &src, &dst, c, 0.0f);
}