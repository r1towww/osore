//使用するヘッダーファイル
#include <stdlib.h>
#include <time.h>
#include"GameL\DrawTexture.h"
#include"GameL\WinInputs.h"
#include"GameL\SceneManager.h"
#include"GameL\HitBoxManager.h"
#include"GameL\UserData.h" 

#include"GameHead.h"
#include"ObjTwinsRed.h"
#include "UtilityModule.h"

//使用するネームスペース
using namespace GameL;

float* g_twinsred_x[20];//全ての双子（青）のX位置を把握する
float* g_twinsred_y[20];//全ての双子（青）のY位置を把握する

CObjTwinsRed::CObjTwinsRed(float x, float y,int id)
{
	m_px = x + 375.0f;	//位置
	m_py = y + 275.0f;

	m_red_id = id;
	g_enemy_cnt++;	//敵の総数のカウント
}



//イニシャライズ
void CObjTwinsRed::Init()
{
	m_hp = 5;        //体力
	m_vx = 0.0f;	//移動ベクトル
	m_vy = 0.0f;
	m_posture = 0.0f;//正面(0.0f) 左(4.0f) 右(1.0f) 背面(2.0f)

	m_ani_timeB = 0;
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
	m_kill_f = false;	//キルカウント用フラグの初期化


	m_bullet_time = 100;
	m_time = 30;

	m_df = true;

	m_invincible_flag = false;


	//消滅アニメーション用
	m_ani_delete = 0;
	m_ani_count = 0;
	m_ani_max_count = 10;
	m_ani_frame_delete = 1;

	//牛削除フラグ
	m_twinsred_delete = false;


	m_alpha = 1.0;

	srand(time(NULL));

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 40, 40, ELEMENT_NULL, OBJ_TWINS_BLUE, 1);
}

//アクション
void CObjTwinsRed::Action()
{
	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}

	if (m_ani_frame == 3)
	{
		m_ani_frame = 1;
	}

	//行動が制御されている場合（メニュー画面）
	if (g_move_stop_flag == true || g_tutorial_flag == true)
		return;	//行動を制御
	CObjBlock* pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//20°間隔で弾丸発射
	m_bullet_time++;
	if (m_bullet_time > 300 && m_hp > 0 && g_stan_red_flag[m_red_id] == false)
	{
		m_bullet_time = 0;

		//6発同時発射
		CObjRedBullet*obj_b;
		for (int i = 0; i < 360; i += 60)
		{
			//角度iで角度弾丸発射
			obj_b = new CObjRedBullet(m_px, m_py, i, 3.0f);
			Objs::InsertObj(obj_b, OBJ_RED_BULLET, 5);
		}
	}


	//ブロックとの当たり判定実行
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

	if (g_stan_red_flag[m_red_id] == false)
	{
		//UtilityModuleのチェック関数に場所と領域を渡し、領域外か判定
		bool check;
		check = CheckWindow(m_px + 19 + pb->GetScrollx(), m_py + 15 + pb->GetScrolly(), 0.0f, 0.0f, 800.0f, 600.0f);
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
					m_posture = 4.0f;
					m_ani_time += 1;
				}

				if (ar > 45 && ar < 135)
				{
					//下
					m_posture = 3.0f;
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
					m_posture = 1.0f;
					m_ani_time += 1;

				}

				//主人公機と敵角度があんまりにもかけ離れたら
				m_vx = cos(3.14 / 180 * ar) * 1;
				m_vy = sin(3.14 / 180 * ar) * 1;
			}
		}
		else
		{

		}
	}
	else
	{
		m_vx = 0.0f;
		m_vy = 0.0f;
	}

	//HitBoxの内容を更新
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + 19 + pb->GetScrollx(), m_py + 15 + pb->GetScrolly());

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
	if (hit->CheckElementHit(ELEMENT_NULL) == true)
	{
		//敵がブロックとどの角度で当たっているのかを確認
		HIT_DATA** hit_data;							//当たった時の細かな情報を入れるための構造体
		hit_data = hit->SearchElementHit(ELEMENT_NULL);
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

	//ELEMENT_BEAMSABERを持つオブジェクトと接触したら
	if (m_invincible_flag == false)
	{
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

			m_hp -= g_attack_power;	//hpを主人公の攻撃力分減らす
			m_f = true;
			m_invincible_flag = true;
			m_key_f = true;

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

			m_hp -= g_attack_power;	//hpを主人公の攻撃力分減らす
			m_f = true;
			m_invincible_flag = true;
			m_key_f = true;

		}

		//ELEMENT_SUBを持つオブジェクトと接触したら
		if (hit->CheckElementHit(ELEMENT_SUB) == true)
		{
			//敵が主人公とどの角度で当たっているかを確認
			HIT_DATA**hit_data;							//当たった時の細かな情報を入れるための構造体
			hit_data = hit->SearchElementHit(ELEMENT_SUB);//hit_dataに主人公と当たっている他全てのHitBoxとの情報を入れる

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
			m_invincible_flag = true;
			m_key_f = true;

		}
	}

	//ELEMENT_SKILL_LEOを持つオブジェクトと接触したら
	if (hit->CheckElementHit(ELEMENT_SKILL_LEO) == true)
	{
		//敵が主人公とどの角度で当たっているかを確認
		HIT_DATA**hit_data;							//当たった時の細かな情報を入れるための構造体
		hit_data = hit->SearchElementHit(ELEMENT_SKILL_LEO);//hit_dataに主人公と当たっている他全てのHitBoxとの情報を入れる
															//ヒット判定on
		g_stan_blue_flag[m_red_id] = true;
	}

	//しし座のヒット判定がonの時スタン
	if (g_stan_blue_flag[m_red_id] == true)
	{
		g_Leo_cnt += 1.0f;
		if (g_Leo_cnt >= 200.0f)
		{
			g_Leo_cnt = 0.0f;
			g_stan_blue_flag[m_red_id] = false;
		}

	}

	//ELEMENT_SKILL_LEOを持つオブジェクトと接触したら
	if (hit->CheckElementHit(ELEMENT_SKILL_LEO) == true)
	{
		//敵が主人公とどの角度で当たっているかを確認
		HIT_DATA**hit_data;							//当たった時の細かな情報を入れるための構造体
		hit_data = hit->SearchElementHit(ELEMENT_SKILL_LEO);//hit_dataに主人公と当たっている他全てのHitBoxとの情報を入れる
															//ヒット判定on
		g_stan_red_flag[m_red_id] = true;
	}

	//しし座のヒット判定がonの時スタン
	if (g_stan_red_flag[m_red_id] == true)
	{

		g_Leo_cnt += 1.0f;


		//アニメーションのコマ間隔制御
		if (m_ani_timeB < 0)
		{

			m_ani_frame++;	//アニメーションのコマを１つ進める
			m_ani_timeB = 10;

			m_ani_stop++;

			if (m_ani_stop >= 10)
			{
				m_eff.m_top = 0;
				m_eff.m_left = 0;
				m_eff.m_right = 213;
				m_eff.m_bottom = 192;

			}
			if (g_Leo_cnt >= 200.0f)
			{
				g_Leo_cnt = 0.0f;
				g_stan_red_flag[m_red_id] = false;
			}
		}

		else
		{
			m_ani_timeB--;
		}
	}

	if (m_f == true)
	{
		m_time--;
		m_alpha = ALPHAUNDER;

	}
	if (m_time <= 0)
	{
		m_f = false;
		m_invincible_flag = false;
		m_alpha = ALPHAORIGIN;

		m_time = 30;
	}


	//位置の更新
	m_px += m_vx*1.0;
	m_py += m_vy*1.0;

	//HPが0になったら破棄
	if (m_hp <= 0)
	{
		//双子赤削除フラグ
		m_twinsred_delete = true;
	}

	//消滅アニメーションのコマを進める
	if (m_twinsred_delete == true)
	{
		m_ani_count += 1;
	}
	//移動アニメーション
	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}

	if (m_ani_frame == 3)
	{
		m_ani_frame = 1;
	}
	//消滅アニメーション
	if (m_ani_count > m_ani_max_count)
	{
		m_ani_frame_delete += 1;
		m_ani_count = 0;
	}
	if (m_ani_frame_delete == 4)
	{
		m_ani_frame_delete = 0;
		//フラグがオフの場合
		if (m_kill_f == false)
		{
			g_kill_cnt++;	//キルカウントを増やす
			m_kill_f = true;//フラグをオンにして入らないようにする
		}
		//敵削除
		m_alpha = 0.0f;xxxxx
		hit->SetInvincibility(true);
		g_cow_d_flag[m_red_id] = false;
		this->SetStatus(false);    //自身に削除命令を出す
	}
}

//ドロー
void CObjTwinsRed::Draw()
{
	int AniData[4] =
	{ 1,0,2,0, };
	int DeleteData[4] =
	{ 1,2,3,4, };
	int AniDataB[6] =
	{ 0,1,2,3,4,0 };

	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,m_alpha };
	float d[4] = { 1.0f,1.0f,1.0f,1.0f };
	float cB[4] = { 1.0f,1.0f,1.0f,0.5f };

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

			   //ブロック情報を持ってくる
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	if (m_twinsred_delete == false)
	{
		//切り取り位置の設定
		src.m_top = 64.0f * m_posture;
		src.m_left = 0.0f + (AniData[m_ani_frame] * 64);
		src.m_right = 64.0f + (AniData[m_ani_frame] * 64);
		src.m_bottom = src.m_top + 64.0f;

		//表示位置の設定
		dst.m_top = 0.0f + m_py + block->GetScrolly();
		dst.m_left = 80.0f + m_px + block->GetScrollx();
		dst.m_right = 0.0f + m_px + block->GetScrollx();
		dst.m_bottom = 80.0f + m_py + block->GetScrolly();

		//描画
		Draw::Draw(21, &src, &dst, c, 0.0f);
	}
	else if (m_twinsred_delete == true)
	{
		//消滅アニメーション
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f + (DeleteData[m_ani_frame_delete] * 192);
		src.m_right = 192.0f + (DeleteData[m_ani_frame_delete] * 192);
		src.m_bottom = src.m_top + 192.0f;

		//表示位置の設定
		dst.m_top = 0.0f + m_py + block->GetScrolly();
		dst.m_left = 0.0f + m_px + block->GetScrollx();
		dst.m_right = 64.0f + m_px + block->GetScrollx();
		dst.m_bottom = 64.0f + m_py + block->GetScrolly();

		//表示
		Draw::Draw(80, &src, &dst, d, 0.0f);
	}
	if (g_stan_red_flag[m_red_id] == true)
	{
		RECT_F src;//描画元切り取り位置
		RECT_F dst;//描画先表示位置

				   //ブロック情報を持ってくる
		CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

		//切り取り位置の設定
		src.m_top = 0.0f * m_posture;
		src.m_left = 0.0f + (AniDataB[m_ani_frame] * 192);
		src.m_right = 192.0f + (AniDataB[m_ani_frame] * 192);
		src.m_bottom = src.m_top + 192.0f;

		//表示位置の設定
		dst.m_top =     0.0f + m_py + block->GetScrolly();
		dst.m_left =   10.0f + m_px + block->GetScrollx();
		dst.m_right =  70.0f + m_px + block->GetScrollx();
		dst.m_bottom = 60.0f + m_py + block->GetScrolly();

		//描画
		Draw::Draw(49, &src, &dst, cB, 0.0f);
	}
}