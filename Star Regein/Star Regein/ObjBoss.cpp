//使用するヘッダーファイル
#include <stdlib.h>
#include <time.h>
#include"GameL\DrawTexture.h"
#include"GameL\WinInputs.h"
#include"GameL\SceneManager.h"
#include"GameL\HitBoxManager.h"
#include"GameL\UserData.h" 
#include<time.h>
#include "GameL\Audio.h"

#include"GameHead.h"
#include"ObjBoss.h"
#include "UtilityModule.h"

//使用するネームスペース
using namespace GameL;

float* g_boss_x;
float* g_boss_y;
bool g_dead_flag = false;
bool g_Voice_flag = false;
bool g_End_flag = false;
float g_boss_hp;

CObjBoss::CObjBoss(float x, float y)
{
	m_px = x + 180.0f;	//位置
	m_py = y + 275.0f;
}

//イニシャライズ
void CObjBoss::Init()
{
	g_boss_hp = 1;        //体力（初期40）
	m_vx = 0.0f;	//移動ベクトル
	m_vy = 0.0f;
	m_posture = 0.0f;//正面(0.0f) 左(1.0f) 右(2.0f) 背面(3.0f)

	m_ani_time = 0;
	m_ani_frame = 0;	//静止フレームを初期にする

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

	g_Leo_cnt = 0.0f;

	m_time = 30;

	m_rand = 0;

	m_attack_pattern = 0;

	m_snake_c = 0;

	m_imposition_t = 0;

	m_bullet_t = 0;

	m_attack_key_f = true;

	m_invincible_flag = false;

	m_attack_f = false;
	m_beam_f = false;

	m_df = true;
	count = 0;

	
	m_alpha = 1.0;

	srand(time(NULL));

	//ワープアニメーション関連初期化
	m_warp_eff.m_top = 0;	//エフェクト初期値の初期化
	m_warp_eff.m_left = 0;
	m_warp_eff.m_right = 192;
	m_warp_eff.m_bottom = 192;

	m_warp_ani = 0;			//アニメーション用
	m_warp_ani_time = 0;		//アニメーション間隔タイム

	m_warp_flag = false;
	m_warp_time = 200;

	//死亡エフェクト
	m_dead_eff.m_top = 0;
	m_dead_eff.m_left = 0;
	m_dead_eff.m_right = 192;
	m_dead_eff.m_bottom = 192;

	m_dead_end = false;
	m_dead_time =0;//アニメーション間隔用
	m_dead_ani  =0;//アニメーション用

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 160, 160, ELEMENT_NULL, OBJ_BOSS, 1);
}

//アクション
void CObjBoss::Action()
{
	if (g_tutorial_flag == true)
		return;
	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}

	if (m_ani_frame == 3)
	{
		m_ani_frame = 1;
	}

	m_warp_time--;

	m_ani_time++;

	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}

	if (m_ani_frame == 3)
	{
		m_ani_frame = 0;
	}
	
	//ブロックとの当たり判定実行
	CObjBlock* pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockHit(&m_px, &m_py, false,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy
	);

	//HitBoxの内容を更新
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + pb->GetScrollx(), m_py + pb->GetScrolly());

	CObjBeam* beam = (CObjBeam*)Objs::GetObj(OBJ_BEAM);

	//時間経過でランダムにワープ
	if (m_warp_time <= 0 && m_hp > 0)
	{
		m_warp_flag = true;
	
		//エフェクト用
		RECT_F warp_ani_src[8] =
		{
			{ 0,   0,  192, 192 },
			{ 0, 192,  384, 192 },
			{ 0, 384,  576, 192 },
			{ 0, 576,  768, 192 },
			{ 0, 768,  960, 192 },
			{ 192,   0,  192, 384 },
			{ 192, 192,  384, 384 },
			{ 192, 384,  576, 384 },
		};

		//アニメーションのコマ間隔制御
		if (m_warp_ani_time > 3)
		{
			m_warp_ani++;		//アニメーションのコマを1つ進める
			m_warp_ani_time = 0;

			m_warp_eff = warp_ani_src[m_warp_ani];//アニメーションのRECT配列からm_ani番目のRECT情報取得
		}
		else
		{
			m_warp_ani_time++;
		}

		if (m_warp_ani == 4)
		{
			int count = 0;

			//どこかの星に主人公が接触していた場合、そこにワープ
			for (int i = 0; i <= 4; i++)
			{
				if (g_contact_star_f[i] == true)
				{
					Audio::Start(17); //ワープ音
					m_px = g_star_x[i] - 20;
					m_py = g_star_y[i] - 20;
					break;
				}
				count++;
			}

			//どの星にも接触していなかった場合はランダムにワープ
			if (count == 5)
			{
				srand(time(NULL));
				//マップのランダム処理の初期化
				m_rand = rand() % 5;

				if (m_rand <= 4)
				{
					Audio::Start(17); //ワープ音
					m_px = g_star_x[m_rand] - 20;
					m_py = g_star_y[m_rand] - 20;
				}
				else if (m_rand == 5)
				{
					m_beam_f = true;
				}
			}
		}

		//7番目（画像最後）まで進んだら、0に戻す
		if (m_warp_ani == 7)
		{
			m_warp_ani = 0;
			m_warp_time = 400;
			m_warp_flag = false;
			m_attack_f = true;
			m_attack_key_f = true;
		}

	}

	if (m_attack_f == true)
	{
		m_imposition_t++;

		if (m_imposition_t >= 100)
		{
			if (m_beam_f == false)
			{
				if (m_attack_key_f == true)
				{
					//攻撃パターン決定
					srand(time(NULL));
					m_attack_pattern = rand() % 2;
					//m_attack_pattern = 1;

					CObjSnake* snake = (CObjSnake*)Objs::GetObj(OBJ_SNAKE);

					//蛇召喚
					if (m_attack_pattern == 0)
					{
						CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

						float hx = hero->GetX();
						float hy = hero->GetY();

						m_snake_c = 0;
						m_imposition_t = 0;
						Audio::Start(17); //ワープ音

						//蛇オブジェクト作成
						for (int i = 0; i < MAPSIZE; i++)
						{
							for (int j = 0; j < MAPSIZE; j++)
							{
								if (g_map[i][j] == 5)
								{
									if (g_snake_d_flag[m_snake_c] == false)
									{
										//蛇オブジェクト作成
										CObjSnake* snake = new CObjSnake(j*MAPSIZE, i*MAPSIZE, m_snake_c);//オブジェクト作成
																										  //敵の位置を取得
										float* snakex = snake->GetPX();
										float* snakey = snake->GetPY();

										g_snake_x[m_snake_c] = snake->GetPX();
										g_snake_y[m_snake_c] = snake->GetPY();

										g_snake_d_flag[m_snake_c] = true;

										g_stan_snake_flag[m_snake_c] = false;

										Objs::InsertObj(snake, OBJ_SNAKE, 11);//マネージャに登録
									}
									m_snake_c++;
								}
							}
							if (m_snake_c == 20)
								break;
						}
					}
				}

				//毒弾幕
				if (m_attack_pattern == 1)
				{
					m_imposition_t = 0;
					if (count <= 3)
					{
						if (count == 0)
						{
							//毒弾丸18発同時発射
							for (int i = 36; i < 360; i += 18)
							{
								CObjPoison* poison = new CObjPoison(m_px + 55, m_py + 55, i, 4.0f);//オブジェクト作成
								Objs::InsertObj(poison, OBJ_POISON, 11);//マネージャに登録
							}
						}
						if (count == 1)
						{
							//毒弾丸18発同時発射
							for (int i = 18; i < 342; i += 18)
							{
								CObjPoison* poison = new CObjPoison(m_px + 55, m_py + 55, i, 4.0f);//オブジェクト作成
								Objs::InsertObj(poison, OBJ_POISON, 11);//マネージャに登録
							}
						}
						if (count == 2)
						{
							//毒弾丸18発同時発射
							for (int i = -0; i < 324; i += 18)
							{
								CObjPoison* poison = new CObjPoison(m_px + 55, m_py + 55, i, 4.0f);//オブジェクト作成
								Objs::InsertObj(poison, OBJ_POISON, 11);//マネージャに登録
							}
						}
						if (count == 3)
						{
							//毒弾丸18発同時発射
							for (int i = -18; i < 306; i += 18)
							{
								CObjPoison* poison = new CObjPoison(m_px + 55, m_py + 55, i, 4.0f);//オブジェクト作成
								Objs::InsertObj(poison, OBJ_POISON, 11);//マネージャに登録
							}
							m_attack_f = false;
							count = 0;
						}
						count++;
					}
				}
				m_attack_key_f = false;
			}
			else
			{
				if (beam == nullptr)
				{
					g_boss_d_flag = false;
					CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

					float hx = hero->GetX();
					float hy = hero->GetY();

					//ビームオブジェクト作成
					CObjBeam* beam = new CObjBeam(hx - 135 - pb->GetScrollx(), 275);//オブジェクト作成
					Objs::InsertObj(beam, OBJ_BEAM, 11);//マネージャに登録

					m_px = g_star_x[m_rand] - 20;
					m_py = g_star_y[m_rand] - 20;
				}
				hit->SetInvincibility(true);
				m_alpha = 0.0f;
				m_beam_f = false;
				m_imposition_t = 0;
			}
		}
		else
		{
			m_imposition_t++;
		}
	}

	if (beam == nullptr)
	{
		g_boss_d_flag = true;
		hit->SetInvincibility(false);
		m_alpha = 1.0f;
	}

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
					m_vx = -0.0f; //右
				}
				if (r > 45 && r < 135)
				{
					m_vy = 0.0f;//上
				}
				if (r >= 135 && r < 225)
				{
					m_vx = 0.0f;//左
				}
				if (r >= 225 && r < 315)
				{
					m_vy = -0.0f; //下
				}
			}
		}
	}

	//ELEMENT_BEAMSABERを持つオブジェクトと接触したら
	if (m_invincible_flag == false)
	{
		if (hit->CheckElementHit(ELEMENT_BEAMSABER) == true)
		{
			g_boss_hp -= g_attack_power;	//hpを主人公の攻撃力分減らす
			m_f = true;
			m_invincible_flag = true;
			m_key_f = true;
		}

		//ELEMENT_VIRGO_SKILLを持つオブジェクトと接触したら
		if (hit->CheckElementHit(ELEMENT_SKILL_VIRGO) == true)
		{
			g_boss_hp -= g_attack_power;	//hpを主人公の攻撃力分減らす
			m_f = true;
			m_invincible_flag = true;
			m_key_f = true;
		}

		//ELEMENT_SUBを持つオブジェクトと接触したら
		if (hit->CheckElementHit(ELEMENT_SUB) == true)
		{
			g_boss_hp -= 1;
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
		g_stan_boss_flag = true;
	}

	//しし座のヒット判定がonの時スタン 
	if (g_stan_boss_flag == true)
	{
		g_Leo_cnt += 1.0f;
		if (g_Leo_cnt >= 200.0f)
		{
			m_ani_frame++;	//アニメーションのコマを１つ進める

			if (g_Leo_cnt >= 200.0f)
			{
				g_Leo_cnt = 0.0f;
				g_stan_boss_flag = false;
			}
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
	if (m_dead_end != true)
	{
		if (g_boss_hp <= 0)
		{
			//敵削除
			m_alpha = 0.0f;
			hit->SetInvincibility(true);
			g_boss_d_flag = false;
			g_All_Killcnt++;		   //キルカウントを+する
			g_Earth_BossKill = true;
			g_dead_flag = true;
		}
	}
	//HPが０以下でエフェクト開始
	if (g_dead_flag == true)
	{
		//エフェクト用
		RECT_F dead[20] =
		{

			{ 0,     0, 192, 192 },
			{ 0,   192, 384, 192 },
			{ 0,   384, 576, 192 },
			{ 0,   576, 768, 192 },
			{ 0,   768, 960, 192 },
			{ 192,   0, 192, 384 },
			{ 192, 192, 384, 384 },
			{ 192, 384, 576, 384 },
			{ 192, 576, 768, 384 },
			{ 192, 768, 960, 384 },
			{ 384,   0, 192, 576 },
			{ 384, 192, 384, 576 },
			{ 384, 384, 576, 576 },
			{ 384, 576, 768, 576 },
			{ 384, 768, 960, 576 },
			{ 576,   0, 192, 768 },
			{ 576, 192, 384, 768 },
			{ 576, 384, 576, 768 },
			{ 576, 576, 768, 768 },
			{ 576, 768, 960, 768 },

		};

		//アニメーションのコマ間隔制御
		if (m_dead_time > 2)
		{
			m_dead_ani++;		//アニメーションのコマを1つ進める
			m_dead_time = 0;
			m_dead_eff = dead[m_dead_ani];//アニメーションのRECT配列からm_ani番目のRECT情報取得
										  // 12番目（画像最後）まで進んだら、0に戻す
			if (m_dead_ani == 20)
			{
				//撃破アニメーションが終わったら天の声（クリア用）を表示
				g_tutorial_flag = true;
				g_Voice_flag = true;
				g_dead_flag = false;
				m_dead_end = true;
				hit->SetInvincibility(true);

			}
		}
		else
		{
			m_dead_time++;
		}
	}
	if (g_Voice_flag == true)//天の声（クリア用）を表示
	{
		//チュートリアル吹き出し作成
		CObjTutorial* objtutorialhukidashi = new CObjTutorial(0, 3);
		Objs::InsertObj(objtutorialhukidashi, OBJ_TUTORIAL, 151);

		//チュートリアルオブジェクト作成
		CObjTutorial* objtutorial = new CObjTutorial(1, 3);
		Objs::InsertObj(objtutorial, OBJ_TUTORIAL, 170);
	}
	if (g_End_flag == true)//天の声（クリア用）が終わったらフェードインを作成し、EDに移行
	{

		g_tutorial_flag = false;
		CObjFadein *objfade = new CObjFadein();
		Objs::InsertObj(objfade, OBJ_FADE_IN, 150);//フェードインオブジェクト作成
	}

	CObjMiniMap*map = (CObjMiniMap*)Objs::GetObj(OBJ_MINIMAP);

}

//ドロー
void CObjBoss::Draw()
{
	int AniData[4] =
	{ 1,0,2,0, };

	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,m_alpha };
	float cB[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

	//ブロック情報を持ってくる
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//切り取り位置の設定
	src.m_top = 80.0f * m_posture;
	src.m_left = 0.0f + (AniData[m_ani_frame] * 80);
	src.m_right = 80.0f + (AniData[m_ani_frame] * 80);
	src.m_bottom = src.m_top + 80.0f;

	//表示位置の設定
	dst.m_top = 0.0f + m_py + block->GetScrolly();
	dst.m_left = 160.0f + m_px + block->GetScrollx();
	dst.m_right = 0.0f + m_px + block->GetScrollx();
	dst.m_bottom = 160.0f + m_py + block->GetScrolly();
	if (m_dead_end != true)
	{
		//描画
		Draw::Draw(33, &src, &dst, c, 0.0f);
	}

	//ワープ
	if (m_warp_flag == true)
	{
		//表示位置の設定
		dst.m_top = -80.0f + m_py + block->GetScrolly();
		dst.m_left = 240.0f + m_px + block->GetScrollx();
		dst.m_right = -80.0f + m_px + block->GetScrollx();
		dst.m_bottom = 200.0f + m_py + block->GetScrolly();
		//エフェクトの描画
		Draw::Draw(34, &m_warp_eff, &dst, c, 0.0f);
	}
	else
	{
		m_warp_ani = 0;
	}
	//表示位置の設定
	dst.m_top = -80.0f + m_py + block->GetScrolly();
	dst.m_left = 240.0f + m_px + block->GetScrollx();
	dst.m_right = -80.0f + m_px + block->GetScrollx();
	dst.m_bottom = 200.0f + m_py + block->GetScrolly();
	if (g_dead_flag == true)
	{
		//エフェクトの描画
		Draw::Draw(65, &m_dead_eff, &dst, cB, 0.0f);
	}
}