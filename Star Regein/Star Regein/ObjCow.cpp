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

float* g_cow_x[20];//全ての牛のX位置を把握する
float* g_cow_y[20];//全ての牛のY位置を把握する
int g_cow_id[20];
bool g_Leo_hit_flag;
float g_Leo_cnt;


CObjCow::CObjCow(float x, float y, int id)
{
	m_px = x;	//位置
	m_py = y;

	m_cow_id = id;
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
	m_ani_max_time = 15;	//アニメーション間隔幅

	m_movey = true; //true=正面　false=背面
	m_movex = true;	//true=右　false=左

	//blockとの衝突状態確認用
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_key_f = false;		//無敵時間行動制御
	m_f = false;

	g_Leo_hit_flag = false;
	g_Leo_cnt = 0.0f;

	m_btime = 0;

	m_time = 30;

	m_df = true;
	count = 0;

	alpha = 1.0;

	srand(time(NULL));

	
	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px + 2, m_py + 4, 64, 64, ELEMENT_NULL, OBJ_COW, 1);
}

//アクション
void CObjCow::Action()
{
	m_btime++;

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

	if (m_ani_frame == 3)
	{
		m_ani_frame = 1;
	}

	//ブロックとの当たり判定実行
	CObjBlock* pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockHit(&m_px, &m_py, false,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy
	);

	//主人公の位置を取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	if (hero != nullptr)
	{
		float hx = hero->GetX();
		float hy = hero->GetY();
	}

	//UtilityModuleのチェック関数に場所と領域を渡し、領域外か判定
	bool check;
	check = CheckWindow(m_px + pb->GetScrollx(), m_py + pb->GetScrolly(), 0.0f, 0.0f, 800.0f, 600.0f);
	if (check == true)
	{
		//主人公機が存在する場合、誘導角度の計算する
		if (hero != nullptr)
		{

			float x;
			float y;

			x = 375 - (m_px + pb->GetScrollx());
			y = 275 - (m_py + pb->GetScrolly());

			float ar = GetAtan2Angle(x, y);

			//敵の現在の向いている角度を取る
			float br = GetAtan2Angle(m_vx, m_vy);

			//角度で上下左右を判定
			if ((ar < 45 && ar>0) || ar > 315)
			{
				//左
				m_posture = 1.0f;
				m_ani_time += 1;
			}

			if (ar > 45 && ar < 135)
			{
				//下
				m_posture = 0.0f;
				m_ani_time += 1;
			}
			if (ar > 135 && ar < 225)
			{
				//右
				m_posture = 2.0f;
				m_ani_time += 1;
			}
			if (ar > 225 && ar < 315)
			{
				//上
				m_posture = 3.0f;
				m_ani_time += 1;

			}

			//主人公機と敵角度があんまりにもかけ離れたら
			m_vx = cos(3.14 / 180 * ar) * 2;
			m_vy = sin(3.14 / 180 * ar) * 2;
		}
	}
	else
	{
		//範囲外での行動
		if (m_btime <= 500)
		{
			m_vy = 0;
			m_movex = true;
			m_posture = 1.0f;
		}
		if (m_btime >= 501 && m_btime <= 1000)
		{
			m_vx = 0;
			m_movey = false;
			m_posture = 3.0f;
		}
		if (m_btime >= 1001 && m_btime <= 1500)
		{
			m_vy = 0;
			m_movex = false;
			m_posture = 2.0f;
		}
		if (m_btime >= 1501 && m_btime <= 2000)
		{
			m_vx = 0;
			m_movey = true;
			m_posture = 0.0f;
		}
		if (m_btime >= 2001)
			m_btime = 0;
	}

	//HitBoxの内容を更新
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + 2 + pb->GetScrollx(), m_py + 4 + pb->GetScrolly());


	//主人公とBLOCK系統との当たり判定
	if (hit->CheckElementHit(ELEMENT_BLOCK) == true)
	{
		//主人公がブロックとどの角度で当たっているのかを確認
		HIT_DATA** hit_data;							//当たった時の細かな情報を入れるための構造体
		hit_data = hit->SearchElementHit(ELEMENT_BLOCK);	//hit_dateに主人公と当たっている他全てのHitBoxとの情報を入れる
		float r = 0;

		for (int i = 0; i < 10; i++)
		{
			if (hit_data[i] != nullptr)
			{
				r = hit_data[i]->r;
				

				//角度で上下左右を判定
				if ((r <= 45 && r >= 0) || r >= 315)
				{
					m_vx = -0.15f; //右
				}
				if (r > 45 && r < 135)
				{
					m_vy = 0.15f;//上
				}
				if (r >= 135 && r < 225)
				{
					m_vx = 0.15f;//左
				}
				if (r >= 225 && r < 315)
				{
					m_vy = -0.15f; //下
				}
			}
		}
	}

	//敵とBLOCK系統との当たり判定
	if (hit->CheckElementHit(ELEMENT_BLOCK) == true || hit->CheckElementHit(ELEMENT_NULL) == true || hit->CheckElementHit(ELEMENT_FIELD))
	{
		//敵がブロックとどの角度で当たっているのかを確認
		HIT_DATA** hit_data;							//当たった時の細かな情報を入れるための構造体
		hit_data = hit->SearchElementHit(ELEMENT_BLOCK);	//hit_dateに主人公と当たっている他全てのHitBoxとの情報を入れる
		hit_data = hit->SearchElementHit(ELEMENT_NULL);
		hit_data = hit->SearchElementHit(ELEMENT_FIELD);

		float r = 0;

		for (int i = 0; i < 10; i++)
		{
			if (hit_data[i] != nullptr)
			{
				r = hit_data[i]->r;
				g_Leo_hit_flag = true;

				//角度で上下左右を判定
				if ((r <= 45 && r >= 0) || r >= 315)
				{
					m_vx = -0.15f; //右
				}
				if (r > 45 && r < 135)
				{
					m_vy = 0.15f;//上
				}
				if (r >= 135 && r < 225)
				{
					m_vx = 0.15f;//左
				}
				if (r >= 225 && r < 315)
				{
					m_vy = -0.15f; //下
				}
			
			}
		}
	}

	//ELEMENT_BEAMSABERを持つオブジェクトと接触したら
	if (hit->CheckElementHit(ELEMENT_BEAMSABER) == true)
	{
		//敵が主人公とどの角度で当たっているかを確認
		HIT_DATA**hit_data;							//当たった時の細かな情報を入れるための構造体
		hit_data = hit->SearchElementHit(ELEMENT_BEAMSABER);//hit_dataに主人公と当たっている他全てのHitBoxとの情報を入れる

		for (int i = 0; i < hit->GetCount(); i++)
		{
			//攻撃の左右に当たったら
			if (hit_data[i] == nullptr)
				continue;


			float r = hit_data[i]->r;



			if ((r < 45 && r >= 0) || r > 315)
			{
				m_vx = -20.0f;//左に移動させる
			}
			if (r >= 45 && r < 135)
			{
				m_vy = 20.0f;//上に移動させる
			}
			if (r >= 135 && r < 225)
			{
				m_vx = 20.0f;//右に移動させる
			}
			if (r >= 225 && r < 315)
			{
				m_vy = -20.0f;//したに移動させる
			}
		}

		m_hp -= 1;
		m_f = true;
		m_key_f = true;
		hit->SetInvincibility(true);

	}

	//ELEMENT_VIRGO_SKILLを持つオブジェクトと接触したら
	if (hit->CheckElementHit(ELEMENT_SKILL_VIRGO) == true)
	{
		//敵が主人公とどの角度で当たっているかを確認
		HIT_DATA**hit_data;							//当たった時の細かな情報を入れるための構造体
		hit_data = hit->SearchElementHit(ELEMENT_SKILL_VIRGO);//hit_dataに主人公と当たっている他全てのHitBoxとの情報を入れる

		for (int i = 0; i < hit->GetCount(); i++)
		{
			//攻撃の左右に当たったら
			if (hit_data[i] == nullptr)
				continue;


			float r = hit_data[i]->r;



			if ((r < 45 && r >= 0) || r > 315)
			{
				m_vx = -20.0f;//左に移動させる
			}
			if (r >= 45 && r < 135)
			{
				m_vy = 20.0f;//上に移動させる
			}
			if (r >= 135 && r < 225)
			{
				m_vx = 20.0f;//右に移動させる
			}
			if (r >= 225 && r < 315)
			{
				m_vy = -20.0f;//したに移動させる
			}
		}

		m_hp -= 1;
		m_f = true;
		m_key_f = true;
		hit->SetInvincibility(true);

	}


	//ELEMENT_SKILL_LEOを持つオブジェクトと接触したら
	if (hit->CheckElementHit(ELEMENT_SKILL_LEO) == true)
	{
		//敵が主人公とどの角度で当たっているかを確認
		HIT_DATA**hit_data;							//当たった時の細かな情報を入れるための構造体
		hit_data = hit->SearchElementHit(ELEMENT_SKILL_LEO);//hit_dataに主人公と当たっている他全てのHitBoxとの情報を入れる
		//ヒット判定on
		g_Leo_hit_flag = true;
		for (int i = 0; i < hit->GetCount(); i++)
		{
			//攻撃の左右に当たったら
			if (hit_data[i] == nullptr)
				continue;


			float r = hit_data[i]->r;
		
			//獅子座スキルヒットフラグがオンならスタンさせ
			//カウントを進め、一定数になればスタン解除
			
		}

		
	}
	//しし座のヒット判定がonの時スタン
	if (g_Leo_hit_flag == true)
	{
		m_vx = 0.0f;
		m_vy = 0.0f;
		g_Leo_cnt += 1.0f;
		if (g_Leo_cnt >= 1000.0f)
		{
			g_Leo_hit_flag = false;
			g_Leo_cnt = 0.0f;
		}
	}
	


	if (m_f == true)
	{
		m_time--;

	}

	if (m_time <= 0)
	{
		m_f = false;
		hit->SetInvincibility(false);

		m_time = 30;

	}


	//位置の更新
	m_px += m_vx*1.0;
	m_py += m_vy*1.0;

	//HPが0になったら破棄
	if (m_hp == 0)
	{

		//敵削除
		alpha = 0.0f;
		hit->SetInvincibility(true);
		g_cow_d_flag[m_cow_id] = false;
	}
	CObjMiniMap*map = (CObjMiniMap*)Objs::GetObj(OBJ_MINIMAP);



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
	src.m_top = 48.0f * m_posture;
	src.m_left = 0.0f + (AniData[m_ani_frame] * 48);
	src.m_right = 48.0f + (AniData[m_ani_frame] * 48);
	src.m_bottom = src.m_top + 48.0f;

	//表示位置の設定
	dst.m_top = 0.0f + m_py + block->GetScrolly();
	dst.m_left = 64.0f + m_px + block->GetScrollx();
	dst.m_right = 0.0f + m_px + block->GetScrollx();
	dst.m_bottom = 64.0f + m_py + block->GetScrolly();


	//描画
	Draw::Draw(3, &src, &dst, c, 0.0f);
}