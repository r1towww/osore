//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjBlock.h"
#include <time.h>

//使用するネームスペース
using namespace GameL;

int g_asteroid;
int g_block;
int g_blackhole_cnt = 0;
int g_whitehole_cnt = 0;

bool g_stan_cow_flag[20];//スタン牛個別認識用
bool g_stan_blue_flag[20];//スタン双子（青）個別認識用
bool g_stan_red_flag[20];//スタン双子（赤）個別認識用
bool g_stan_woman_flag[20];//スタン乙女個別認識用
bool g_stan_libra_flag[20];//スタン天秤個別認識用
bool g_stan_leo_flag[60];//スタン獅子個別認識用
bool g_stan_boss_flag;//スタンボス用
bool g_stan_snake_flag[20];//スタン蛇用
bool g_move_libra_flag[20];//ダメージで動かす判定

CObjBlock::CObjBlock(int map[MAPSIZE][MAPSIZE])
{
	//マップデータをコピー
	memcpy(m_map, map, sizeof(int)*(MAPSIZE * MAPSIZE));
}

//イニシャライズ
void CObjBlock::Init()
{
	srand(time(NULL));
	//マップのランダム処理の初期化
	m_rand = rand() % 2;

	m_block_rand = 0;	//障害物ブロックのランダム化用
	//数値を変えることでステージ上の障害物の位置を変更
	//ランダムの値が0の場合
	if (m_rand == 0)
	{
		g_block = 10;	//10をセット
		g_asteroid = 13;	//13をセット
	}
	else if (m_rand = 1)	//1の場合
	{
		g_block = 11;		//11をセット
		g_asteroid = 14;	//14をセット
	}

	//ステージクリアですべてのサイズを小さくする
	if (g_stage_clear == true)
	{
		m_allsize = 12.0f;
	}
	else
	{
		m_allsize = 64.0f;
	}
	cnt = 0;
	m_blue_c = 0;
	m_red_c = 0;
	m_woman_c = 0;
	m_c_c = 0;
	m_b_c = 0;
	m_w_c = 0;
	m_libra_c = 0;
	m_leo_c = 0;
	m_star_c = 0;

	m_scrollx = 0.0f;
	m_scrolly = 0.0f;

	//敵出現
	if (g_stage == VenusTaurus)
	{
		for (int i = 0; i < MAPSIZE; i++)
		{
			for (int j = 0; j < MAPSIZE; j++)
			{
				if (m_map[i][j] == 5)
				{
					//牛オブジェクト作成
					CObjCow* cow = new CObjCow(j*MAPSIZE, i*MAPSIZE, m_c_c);
					//敵の位置を取得
					float* cx = cow->GetPX();
					float* cy = cow->GetPY();

					g_cow_x[m_c_c] = cow->GetPX();
					g_cow_y[m_c_c] = cow->GetPY();

					g_cow_d_flag[m_c_c] = true;

					g_stan_cow_flag[m_c_c] = false;

					m_c_c++;

					Objs::InsertObj(cow, OBJ_COW, 10);
				}
			}
		}
	}
	else if (g_stage == MercuryVirgo)
	{
		for (int i = 0; i < MAPSIZE; i++)
		{
			for (int j = 0; j < MAPSIZE; j++)
			{
				if (m_map[i][j] == 5)
				{
					//乙女オブジェクト作成
					CObjWoman* woman = new CObjWoman(j*MAPSIZE, i*MAPSIZE, m_woman_c);
					//敵の位置を取得
					float* wx = woman->GetPX();
					float* wy = woman->GetPY();

					g_woman_x[m_woman_c] = woman->GetPX();
					g_woman_y[m_woman_c] = woman->GetPY();

					g_woman_d_flag[m_woman_c] = true;

					g_stan_woman_flag[m_woman_c] = false;

					m_woman_c++;

					Objs::InsertObj(woman, OBJ_WOMAN, 10);
				}
			}
		}
	}

	else if (g_stage == MercuryGemini)
	{
		for (int i = 0; i < MAPSIZE; i++)
		{
			for (int j = 0; j < MAPSIZE; j++)
			{
				if (m_map[i][j] == 5)
				{
					//双子（青）オブジェクト作成
					CObjTwinsBlue* blue = new CObjTwinsBlue(j*MAPSIZE, i*MAPSIZE, m_blue_c);
					//敵の位置を取得
					float* bx = blue->GetPX();
					float* by = blue->GetPY();

					g_twinsblue_x[m_blue_c] = blue->GetPX();
					g_twinsblue_y[m_blue_c] = blue->GetPY();

					g_blue_d_flag[m_blue_c] = true;

					g_stan_blue_flag[m_blue_c] = false;

					m_blue_c++;

					Objs::InsertObj(blue, OBJ_TWINS_BLUE, 10);
				}
				if (m_map[i][j] == 9)
				{
					//双子（赤）オブジェクト作成
					CObjTwinsRed* red = new CObjTwinsRed(j*MAPSIZE, i*MAPSIZE, m_red_c);
					//敵の位置を取得
					float* rx = red->GetPX();
					float* ry = red->GetPY();

					g_twinsred_x[m_red_c] = red->GetPX();
					g_twinsred_y[m_red_c] = red->GetPY();

					g_red_d_flag[m_red_c] = true;

					g_stan_red_flag[m_red_c] = false;

					m_red_c++;

					Objs::InsertObj(red, OBJ_TWINS_RED, 10);
				}
			}
		}
	}

	else if (g_stage == VenusLibra)
	{
		for (int i = 0; i < MAPSIZE; i++)
		{
			for (int j = 0; j < MAPSIZE; j++)
			{
				if (m_map[i][j] == 5)
				{
					//天秤オブジェクト作成
					CObjLibra* libra = new CObjLibra(j*MAPSIZE, i*MAPSIZE, m_libra_c);
					//敵の位置を取得
					float* bx = libra->GetPX();
					float* by = libra->GetPY();

					g_libra_x[m_libra_c] = libra->GetPX();
					g_libra_y[m_libra_c] = libra->GetPY();

					g_libra_d_flag[m_libra_c] = true;

					g_stan_libra_flag[m_libra_c] = false;

					g_move_libra_flag[m_libra_c] = false;

					m_libra_c++;

					Objs::InsertObj(libra, OBJ_LIBRA, 10);
				}
			}
		}
	}
	else if (g_stage == SunLeo)
	{
		for (int i = 0; i < MAPSIZE; i++)
		{
			for (int j = 0; j < MAPSIZE; j++)
			{
				if (m_map[i][j] == 5)
				{
					//獅子オブジェクト作成
					CObjLeo* leo = new CObjLeo(j*MAPSIZE, i*MAPSIZE, m_leo_c);
					//敵の位置を取得
					float* lx = leo->GetPX();
					float* ly = leo->GetPY();

					g_leo_x[m_leo_c] = leo->GetPX();
					g_leo_y[m_leo_c] = leo->GetPY();

					g_leo_d_flag[m_leo_c] = true;

					g_stan_leo_flag[m_leo_c] = false;

					m_leo_c++;

					Objs::InsertObj(leo, OBJ_LEO, 10);
				}
			}
		}
	}
	else if (g_stage == EarthStar)
	{
		for (int i = 0; i < MAPSIZE; i++)
		{
			for (int j = 0; j < MAPSIZE; j++)
			{
				if (g_Boss_Spawn == true)
				{
					if (m_map[i][j] == 80)
					{
						//ボスオブジェクト作成
						CObjBoss* boss = new CObjBoss(j*MAPSIZE, i*MAPSIZE);
						//敵の位置を取得
						float* bossx = boss->GetPX();
						float* bossy = boss->GetPY();

						g_boss_x = boss->GetPX();
						g_boss_y = boss->GetPY();

						g_boss_d_flag = true;

						g_stan_boss_flag = false;

						Objs::InsertObj(boss, OBJ_BOSS, 10);
					}
				}
			}
		}
	}



	//出現
	for (int i = 0; i < MAPSIZE; i++)
	{
		for (int j = 0; j < MAPSIZE; j++)
		{
			if (m_map[i][j] == 3)
			{
				if (g_stage_clear == true)
				{
					;
				}
				else
				{
					//主人公オブジェクト作成
					CObjHero* obj = new CObjHero(j*ALLSIZE, i*ALLSIZE);//オブジェクト作成
					Objs::InsertObj(obj, OBJ_HERO, 11);//マネージャに登録

					m_scrollx = -j * MAPSIZE;
					m_scrolly = -i * MAPSIZE;
				}

			}
			if (m_map[i][j] == 2)
			{
				//星オブジェクト作成
				CObjStar* objstar = new CObjStar(j*ALLSIZE, i*ALLSIZE,i,j,m_star_c);//オブジェクト作成
				Objs::InsertObj(objstar, OBJ_STAR, 5);//マネージャに登録

				if (g_stage == EarthStar && g_Boss_Spawn == true)
				{
					//星の位置を取得
					g_star_x[m_star_c] = objstar->GetX();
					g_star_y[m_star_c] = objstar->GetY();

					m_map[i][j] = 4;

					m_star_c++;


				}

			}
			if (m_map[i][j] == g_asteroid || m_map[i][j] == 6)
			{
				//小惑星オブジェクト作成
				CObjAsteroid* objasteroid = new CObjAsteroid(j*m_allsize, i*m_allsize);//オブジェクト作成
				Objs::InsertObj(objasteroid, OBJ_ASTEROID, 9);//マネージャに登録
			}
			if (m_map[i][j] == 7)
			{
				//ブラックホールオブジェクト作成
				CObjBlackhole* objablackhole = new CObjBlackhole(j*m_allsize, i*m_allsize, m_b_c);//オブジェクト作成
				
				//ブラックホールの位置を取得
				float* bx = objablackhole->GetBX();
				float* by = objablackhole->GetBY();

				
				g_blackhole_x[m_b_c] = objablackhole->GetBX();
				g_blackhole_y[m_b_c] = objablackhole->GetBY();

				m_b_c++;
				Objs::InsertObj(objablackhole, OBJ_BLACKHOLE + g_blackhole_cnt, 9);//マネージャに登録
				g_blackhole_cnt++;	//カウントを増やしオブジェクトを別にする
			}
			if (m_map[i][j] == 8)
			{
				//ホワイトホールオブジェクト作成
				CObjWhitehole* objawhitehole = new CObjWhitehole(j*m_allsize, i*m_allsize, m_w_c);//オブジェクト作成
				//ブラックホールの位置を取得
				float* bx = objawhitehole->GetWX();
				float* by = objawhitehole->GetWY();

				g_whitehole_x[m_w_c] = objawhitehole->GetWX();
				g_whitehole_y[m_w_c] = objawhitehole->GetWY();

				m_w_c++;

				Objs::InsertObj(objawhitehole, OBJ_WHITEHOLE , 9);//マネージャに登録
			}
			if (m_map[i][j] == 15)
			{
				//ブレイクロックオブジェクト作成
				CObjBreakRock* objbrock = new CObjBreakRock(j*m_allsize, i*m_allsize,i,j);//オブジェクト作成
				Objs::InsertObj(objbrock, OBJ_BREAK_ROCK, 9);//マネージャに登録
			}
			if (m_map[i][j] == 16)
			{
				//ブレイクビックロックオブジェクト作成
				CObjBreakBigRock* objbbrock = new CObjBreakBigRock(j*m_allsize, i*m_allsize, i, j);//オブジェクト作成
				Objs::InsertObj(objbbrock, OBJ_BREAK_BIGROCK, 9);//マネージャに登録
			}
		}
	}

	//惑星によって背景を変える（カラー変更）
	if (g_stage == EarthStar) {		//地球の場合
		m_red = 1.0f;  m_green = 1.0f;  m_blue = 1.0f;
	}
	else if (g_stage == VenusTaurus || g_stage == VenusLibra) {	//金星の場合
		m_red = 2.0f;  m_green = 2.0f;  m_blue = 1.0f;	
	}
	else if (g_stage == MercuryGemini || g_stage == MercuryVirgo) {	//水星の場合
		m_red = 1.0f;  m_green = 2.0f;  m_blue = 2.0f;
	}
	else if (g_stage == SunLeo) {		//太陽の場合
			m_red = 2.0f;  m_green = 1.0f;  m_blue = 1.0f;
		}

}

//アクション
void CObjBlock::Action()
{
	//主人公の情報を取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	

	//スクロール
	hero->SetX(375);
	m_scrollx -= hero->GetVX() * HERO_VEC;

	hero->SetY(275);
	m_scrolly -= hero->GetVY() * HERO_VEC;

	//背景を回転させる
	//m_roll += 0.1f;
	//if (m_roll == 360.0f) {	//1回転した際
	//	m_roll = 0.0f;		//0.0fに値を戻す
	//}
}

//ドロー
void CObjBlock::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };		//通常カラー
	float r[4] = { 1.0f,0.7f,0.7f,1.0f };		//レッドカラー
	float b[4] = { 0.7f,0.7f,1.0f,1.0f };		//ブルーカラー

	float backc[4] = { m_red,m_green,m_blue,1.0f };	//背景カラー

	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

	/* 背景用 */
	//切り取り位置の設定
	src.m_top    = 0.0f;
	src.m_left   = 0.0f;
	src.m_right  = 800.0f;
	src.m_bottom = 600.0f;

	//表示位置の設定
	dst.m_top    = 0.0f;
	dst.m_left   = 0.0f;
	dst.m_right  = 800.0f;
	dst.m_bottom = 600.0f;

	//描画
	Draw::Draw(5, &src, &dst, backc, 0.0f);

	/* ブロック（障害物用） */
	for (int i = 0; i < MAPSIZE; i++)
	{
		for (int j = 0; j < MAPSIZE; j++)
		{
			if (m_map[i][j] >= 0)
			{
				//表示位置の設定
				dst.m_top    = i*m_allsize + m_scrolly;
				dst.m_left   = j*m_allsize + m_scrollx;
				dst.m_right  = dst.m_left + m_allsize;
				dst.m_bottom = dst.m_top  + m_allsize;
				if (m_map[i][j] == 1 || m_map[i][j] == g_block)//隕石、ランダム隕石用
				{
					//切り取り位置の設定
					src.m_top    = 0.0f;
					src.m_left   = 0.0f;
					src.m_right  = 258.0f;
					src.m_bottom = 220.0f;
					//描画
					Draw::Draw(4, &src, &dst, c, 0.0f);
				}
			}
		}
	}

	
}

//BlockHit関数
//引数１　float* x			：判定を行うobjectのX位置
//引数２　float* y			：判定を行うobjectのY位置
//引数３　bool  scroll		：判定を行うobjectはスクロールの影響与えるかどうか（true=与える、false=与えない）
//引数４　bool* up			：上下左右判定の上部分に当たっているかどうかを返す
//引数５　bool* down		：上下左右判定の下部分に当たっているかどうかを返す
//引数６　bool*left			：上下左右判定の左部分に当たっているかどうかを返す
//引数７　bool*right		：上下左右判定の右部分に当たっているかどうかを返す
//引数８　float* vx			：左右判定時の反発による移動方向・力の値を変えて返す
//引数９　float* vy			：上下判定時による自由落下運動の移動方向・力の値を変えて返す
//引数10　int* bt			：下部分判定時、特殊なブロックのタイプを返す
//判定を行うobjectとブロック50*50限定で、当たり判定と上下左右判定を行う
//その結果は引数４〜10に返す
void CObjBlock::BlockHit
(
	float *x, float *y, bool scroll_on,
	bool*up, bool* down, bool*left, bool*right,
	float*vx, float*vy
)
{
	//主人公の衝突状態確認用フラグの初期化
	*up = false;
	*down = false;
	*left = false;
	*right = false;

	//m_mapの全要素にアクセス
	for (int i = 0; i < MAPSIZE; i++)
	{
		for (int j = 0; j < MAPSIZE; j++)
		{
			if (m_map[i][j] == 1 || m_map[i][j] == 99
				|| m_map[i][j] == g_block)
			{
				if (g_stage_clear == false)
				{
					//要素番号を座標に変更
					float bx = j*m_allsize;
					float by = i*m_allsize;

					//スクロールの影響
					float scrollx = scroll_on ? m_scrollx : 0;
					float scrolly = scroll_on ? m_scrolly : 0;

					//オブジェクトとブロックの当たり判定
					if ((*x + (-scrollx) + HITBOXSIZE > bx) && (*x + (-scrollx) < bx + HITBOXSIZE) && (*y + (-scrolly) + HITBOXSIZE > by) && (*y + (-scrolly) < by + HITBOXSIZE))
					{
						//上下左右判定

						//Vectorの作成
						float rvx = (*x + (-scrollx)) - bx;
						float rvy = (*y + (-scrolly)) - by;

						//長さを求める
						float len = sqrt(rvx*rvx + rvy*rvy);

						//角度を求める
						float r = atan2(rvy, rvx);
						r = r*180.0f / 3.14f;

						if (r <= 0.0f)
							r = abs(r);
						else
							r = 360.0f - abs(r);

						//lenがある一定の長さのより短い場合判定に入る
						if (len < 88.0f)
						{
							//角度で上下左右を判定
							if ((r < 45 && r >= 0) || r > 315)
							{
								*right = true;//オブジェクトの左部分が衝突している
								*x = bx + HITBOXSIZE + (scrollx);//ブロックの位置+オブジェクトの幅
								*vx = 0.15f;//-VX*反発係数
							}

							if (r > 45 && r < 135)
							{
								*down = true;//オブジェクトの下の部分が衝突している
								*y = by - HITBOXSIZE + (scrolly);//ブロックの位置-オブジェクトの幅
								*vy = -0.15f;
							}
							if (r > 135 && r < 225)
							{
								*left = true;//オブジェクトの右部分が衝突している
								*x = bx - HITBOXSIZE + (scrollx);//ブロックの位置-オブジェクトの幅
								*vx = -0.15f;//-VX*反発係数
							}
							if (r > 225 && r < 315)
							{
								*up = true;//オブジェクトの上の部分が衝突している
								*y = by + HITBOXSIZE + (scrolly);//ブロックの位置+オブジェクトの幅							
								*vy = 0.15f;
							}
						}
					}
				}
				else
				{
					return;
				}
			}
			
		}
	}
}