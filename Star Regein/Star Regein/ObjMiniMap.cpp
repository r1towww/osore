//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "ObjMiniMap.h"
#include "UtilityModule.h"

//使用するネームスペース
using namespace GameL;

bool g_cow_d_flag[20];//牛削除フラグ
bool g_blue_d_flag[20];//双子（青）削除フラグ
bool g_red_d_flag[20];//双子（赤）削除フラグ
bool g_woman_d_flag[20];//乙女削除フラグ
bool g_libra_d_flag[20];//天秤削除フラグ
bool g_leo_d_flag[60];//獅子削除フラグ
bool g_boss_d_flag;//ボス削除フラグ
bool g_snake_d_flag[20];

int g_map[MAPSIZE][MAPSIZE];

CObjMiniMap::CObjMiniMap(int map[MAPSIZE][MAPSIZE])
{
	//マップデータをコピー
	memcpy(g_map, map, sizeof(int)*(MAPSIZE * MAPSIZE));
}

//イニシャライズ
void CObjMiniMap::Init()
{
	if (g_stage == EarthStar) {	//地球の場合
		m_smallsize = 7.0f;	//スモールサイズを7.0fで初期化
		m_bigsize = 14.0f;	//ビッグサイズを14.0fで初期化
	}
	else if (g_stage == VenusTaurus || g_stage == VenusLibra) {	//牡牛座の場合
		m_smallsize = 5.0f;	//スモールサイズを7.0fで初期化
		m_bigsize = 10.0f;	//ビッグサイズを14.0fで初期化

	}
	else{	//それ以外の場合
		m_smallsize = 4.0f;	//ステージサイズを4.0fで初期化
		m_bigsize = 8.0f;	//ビッグサイズを8.0fで初期化
	}
	m_blocksize = m_smallsize;	//ブロックサイズとスモールサイズを合わせる

	m_uisize_x = 590.0f, m_uisize_y = 10.0f;	//背景位置の初期化
	m_backsize = 200.0f;	//背景のサイズの初期化
	m_f = false;	//キー入力制御の初期化

	m_hint_f = false;	//ヒント表示用フラグの初期化

	
	count = 0;
}


//アクション
void CObjMiniMap::Action()
{
	//ステージクリアの情報を持ってくる
	CObjSkillItem* objskillitem = (CObjSkillItem*)Objs::GetObj(OBJ_SKILL_ITEM);

	if (objskillitem != nullptr)
	{
		m_hint_f = true;		//フラグをオン
		m_blocksize = m_smallsize;		//ブロックのサイズ変更	
		m_uisize_x = 590.0f, m_uisize_y = 10.0f;	//マップの位置の変更
		m_backsize = 200.0f;						//背景のサイズ変更

	}


	if (Input::GetVKey('M'))//Mキーが入力されたとき
	{
		//キー入力制御
		if (m_f == true)
		{
			Audio::Start(1);	//エフェクト音を鳴らす
			//マップサイズの変更
			if (m_blocksize == m_smallsize)	//小さい場合大きくする
			{
				m_hint_f = false;		//フラグをオフ
				m_blocksize = m_bigsize;	//ブロックのサイズ変更	
				m_uisize_x = 200.0f, m_uisize_y = 100.0f;	//マップの位置の変更
				m_backsize = 400.0f;						//背景のサイズ変更
			}
			else						//大きい場合小さくする
			{
				m_hint_f = true;		//フラグをオン
				m_blocksize = m_smallsize;		//ブロックのサイズ変更	
				m_uisize_x = 590.0f, m_uisize_y = 10.0f;	//マップの位置の変更
				m_backsize = 200.0f;						//背景のサイズ変更
			}
			m_f = false;
		}
	}
	else
	{
		m_f = true;
	}

}

//ドロー
void CObjMiniMap::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,0.7f };	//基本カラー（半透明）
	float ac[4] = { 1.0f,1.0f,1.0f,1.0f };	//主人公カラー（非透明）

	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置
	//ステージクリア画像が出てるときは出さない
	if (g_stage_clear == false)
	{
		/* 背景用 */
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 500.0f;
		src.m_bottom = 500.0f;

		//表示位置の設定
		dst.m_top = m_uisize_y;
		dst.m_left = m_uisize_x;
		dst.m_right = m_uisize_x + m_backsize;
		dst.m_bottom = m_uisize_y + m_backsize;

		//背景の描画
		Draw::Draw(7, &src, &dst, c, 0.0f);


		/* ミニマップ描画処理 */
		for (int i = 0; i < MAPSIZE; i++)
		{
			for (int j = 0; j < MAPSIZE; j++)
			{
				if (g_map[i][j] >= 0)
				{
					if (g_map[i][j] == 98)//マップ描画外なのでブレイク
					{
						break;
					}
					//表示位置の設定
					dst.m_top = i*m_blocksize + m_uisize_y;
					dst.m_left = j*m_blocksize + m_uisize_x;
					dst.m_right = dst.m_left + m_blocksize;
					dst.m_bottom = dst.m_top + m_blocksize;

					if (g_map[i][j] == 1)//隕石
					{
						//切り取り位置の設定
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = 40.0f;
						src.m_bottom = 50.0f;
						//描画
						Draw::Draw(9, &src, &dst, c, 0.0f);
					}
					if (g_map[i][j] == 2)//星（取得前）
					{
						if (g_Boss_Spawn == true && g_stage == EarthStar)
						{
							g_map[i][j] = 4;
						}

						//切り取り位置の設定
						src.m_top = 0.0f;
						src.m_left = 410.0f;
						src.m_right = 440.0f;
						src.m_bottom = 50.0f;
						//描画
						Draw::Draw(9, &src, &dst, c, 0.0f);
					}
					if (g_map[i][j] == 4)//星（取得後）
					{
						//切り取り位置の設定
						src.m_top = 0.0f;
						src.m_left = 110.0f;
						src.m_right = 140.0f;
						src.m_bottom = 50.0f;
						//描画
						Draw::Draw(9, &src, &dst, c, 0.0f);
					}
					if (g_map[i][j] == 7)//ブラックホール
					{
						//切り取り位置の設定
						src.m_top = 0.0f;
						src.m_left = 260.0f;
						src.m_right = 290.0f;
						src.m_bottom = 50.0f;
						//描画
						Draw::Draw(9, &src, &dst, c, 0.0f);
					}
					if (g_map[i][j] == 8)//ホワイトホール
					{
						//切り取り位置の設定
						src.m_top = 0.0f;
						src.m_left = 310.0f;
						src.m_right = 340.0f;
						src.m_bottom = 50.0f;
						//描画
						Draw::Draw(9, &src, &dst, c, 0.0f);
					}
					if (g_map[i][j] == g_block)//隕石
					{
						//切り取り位置の設定
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = 40.0f;
						src.m_bottom = 50.0f;
						//描画
						Draw::Draw(9, &src, &dst, c, 0.0f);
					}
					if (g_map[i][j] == 15)//壊れる隕石
					{
						//切り取り位置の設定
						src.m_top = 0.0f;
						src.m_left = 460.0f;
						src.m_right = 490.0f;
						src.m_bottom = 50.0f;
						//描画
						Draw::Draw(9, &src, &dst, c, 0.0f);
					}
					if (g_map[i][j] == 16)//壊れる隕石（大）
					{
						//切り取り位置の設定
						src.m_top = 0.0f;
						src.m_left = 460.0f;
						src.m_right = 490.0f;
						src.m_bottom = 50.0f;

						//表示位置の設定
						dst.m_top = i*m_blocksize + m_uisize_y + 2.0f;
						dst.m_left = j*m_blocksize + m_uisize_x;
						dst.m_right = dst.m_left + m_blocksize * 2.8f;
						dst.m_bottom = dst.m_top + m_blocksize * 2.0f;

						//描画
						Draw::Draw(9, &src, &dst, c, 0.0f);
					}
					if (g_map[i][j] == g_asteroid || g_map[i][j] == 6)//小惑星
					{
						//切り取り位置の設定
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = 40.0f;
						src.m_bottom = 50.0f;

						//表示位置の設定
						dst.m_top = i*m_blocksize + m_uisize_y + 2.0f;
						dst.m_left = j*m_blocksize + m_uisize_x + 4.0f;
						dst.m_right = dst.m_left + m_blocksize * 1.8f;
						dst.m_bottom = dst.m_top + m_blocksize * 1.8f;

						//描画
						Draw::Draw(9, &src, &dst, c, 0.0f);
					}
				}
			}
		}
		//主人公の情報を取得
		CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
		if (hero != nullptr)
		{
			//主人公の位置を取得
			float hx = hero->GetX();
			float hy = hero->GetY();

			//ブロック情報を持ってくる
			CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
			float sx = block->GetScrollx();
			float sy = block->GetScrolly();


			for (int i = 0; i < MAPSIZE; i++)
			{
				for (int j = 0; j < MAPSIZE; j++)
				{
					if (g_map[i][j] >= 0)
					{
						//表示位置の設定
						dst.m_top = m_uisize_y + (hy / ((MAPSIZE * 64.0f) / (MAPSIZE * m_blocksize))) - ((block->GetScrolly()) / ((MAPSIZE * 64.0f) / (MAPSIZE * m_blocksize)));
						dst.m_left = m_uisize_x + (hx / ((MAPSIZE * 64.0f) / (MAPSIZE * m_blocksize))) - ((block->GetScrollx()) / ((MAPSIZE*64.0f) / (MAPSIZE*m_blocksize)));
						dst.m_right = dst.m_left + m_blocksize;
						dst.m_bottom = dst.m_top + m_blocksize;

						if (g_map[i][j] == 3)//主人公
						{
							//切り取り位置の設定
							src.m_top = 0.0f;
							src.m_left = 160.0f;
							src.m_right = 190.0f;
							src.m_bottom = 50.0f;
							//描画
							Draw::Draw(9, &src, &dst, ac, 0.0f);
						}
					}
				}
			}

			if (g_stage == VenusTaurus)
			{
				for (int i = 0; i < 10; i++)//敵の数分回す
				{
					float cx = *g_cow_x[i];
					float cy = *g_cow_y[i];

					if (g_cow_d_flag[i] == true)
					{
						//UtilityModuleのチェック関数に場所と領域を渡し、領域外か判定
						bool check;
						check = CheckWindow(cx + block->GetScrollx(), cy + block->GetScrolly(), 10.0f, 10.0f, 790.0f, 590.0f);
						if (check == true)
						{
							//ミニマップに敵の位置を表示する
							//表示位置の設定
							dst.m_top = m_uisize_y + (cy / ((MAPSIZE * 64.0f) / (MAPSIZE * m_blocksize)));
							dst.m_left = m_uisize_x + (cx / ((MAPSIZE * 64.0f) / (MAPSIZE * m_blocksize)));
							dst.m_right = dst.m_left + m_blocksize;
							dst.m_bottom = dst.m_top + m_blocksize;

							//切り取り位置の設定
							src.m_top = 0.0f;
							src.m_left = 50.0f;
							src.m_right = 95.0f;
							src.m_bottom = 50.0f;
							//描画
							Draw::Draw(9, &src, &dst, c, 0.0f);

							g_geminiattck_check = true;
						}
					}
				}
			}
			if (g_stage == VenusLibra)
			{
				for (int i = 0; i < 20; i++)//敵の数分回す
				{
					float lx = *g_libra_x[i];
					float ly = *g_libra_y[i];

					if (g_libra_d_flag[i] == true)
					{
						//UtilityModuleのチェック関数に場所と領域を渡し、領域外か判定
						bool check;
						check = CheckWindow(lx + block->GetScrollx(), ly + block->GetScrolly(), 10.0f, 10.0f, 790.0f, 590.0f);
						if (check == true)
						{
							//ミニマップに敵の位置を表示する
							//表示位置の設定
							dst.m_top = m_uisize_y + (ly / ((MAPSIZE * 64.0f) / (MAPSIZE * m_blocksize)));
							dst.m_left = m_uisize_x + (lx / ((MAPSIZE * 64.0f) / (MAPSIZE * m_blocksize)));
							dst.m_right = dst.m_left + m_blocksize;
							dst.m_bottom = dst.m_top + m_blocksize;

							//切り取り位置の設定
							src.m_top = 0.0f;
							src.m_left = 50.0f;
							src.m_right = 95.0f;
							src.m_bottom = 50.0f;
							//描画
							Draw::Draw(9, &src, &dst, c, 0.0f);

							g_geminiattck_check = true;
						}
					}
				}
			}

			if (g_stage == MercuryVirgo)
			{
				for (int i = 0; i < 16; i++)//敵の数分回す
				{
					float wx = *g_woman_x[i];
					float wy = *g_woman_y[i];


					if (g_woman_d_flag[i] == true)
					{
						//UtilityModuleのチェック関数に場所と領域を渡し、領域外か判定
						bool check;
						check = CheckWindow(wx + block->GetScrollx(), wy + block->GetScrolly(), 10.0f, 10.0f, 790.0f, 590.0f);
						if (check == true)
						{
							//ミニマップに敵の位置を表示する
							//表示位置の設定
							dst.m_top = m_uisize_y + (wy / ((MAPSIZE * 64.0f) / (MAPSIZE * m_blocksize)));
							dst.m_left = m_uisize_x + (wx / ((MAPSIZE * 64.0f) / (MAPSIZE * m_blocksize)));
							dst.m_right = dst.m_left + m_blocksize;
							dst.m_bottom = dst.m_top + m_blocksize;

							//切り取り位置の設定
							src.m_top = 0.0f;
							src.m_left = 50.0f;
							src.m_right = 95.0f;
							src.m_bottom = 50.0f;
							//描画
							Draw::Draw(9, &src, &dst, c, 0.0f);

							g_geminiattck_check = true;
						}
					}
				}
			}

			if (g_stage == MercuryGemini)
			{
				for (int i = 0; i < 7; i++)//敵の数分回す
				{
					float bx = *g_twinsblue_x[i];
					float by = *g_twinsblue_y[i];


					if (g_blue_d_flag[i] == true)
					{
						//UtilityModuleのチェック関数に場所と領域を渡し、領域外か判定
						bool check;
						check = CheckWindow(bx + block->GetScrollx(), by + block->GetScrolly(), 10.0f, 10.0f, 790.0f, 590.0f);
						if (check == true)
						{
							//ミニマップに敵の位置を表示する
							//表示位置の設定
							dst.m_top = m_uisize_y + (by / ((MAPSIZE * 64.0f) / (MAPSIZE * m_blocksize)));
							dst.m_left = m_uisize_x + (bx / ((MAPSIZE * 64.0f) / (MAPSIZE * m_blocksize)));
							dst.m_right = dst.m_left + m_blocksize;
							dst.m_bottom = dst.m_top + m_blocksize;

							//切り取り位置の設定
							src.m_top = 0.0f;
							src.m_left = 50.0f;
							src.m_right = 95.0f;
							src.m_bottom = 50.0f;
							//描画
							Draw::Draw(9, &src, &dst, c, 0.0f);

							g_geminiattck_check = true;
						}
					}
				}
				for (int i = 0; i < 7; i++)//敵の数分回す
				{
					float rx = *g_twinsred_x[i];
					float ry = *g_twinsred_y[i];


					if (g_red_d_flag[i] == true)
					{
						//UtilityModuleのチェック関数に場所と領域を渡し、領域外か判定
						bool check;
						check = CheckWindow(rx + block->GetScrollx(), ry + block->GetScrolly(), 10.0f, 10.0f, 790.0f, 590.0f);
						if (check == true)
						{
							//ミニマップに敵の位置を表示する
							//表示位置の設定
							dst.m_top = m_uisize_y + (ry / ((MAPSIZE * 64.0f) / (MAPSIZE * m_blocksize)));
							dst.m_left = m_uisize_x + (rx / ((MAPSIZE * 64.0f) / (MAPSIZE * m_blocksize)));
							dst.m_right = dst.m_left + m_blocksize;
							dst.m_bottom = dst.m_top + m_blocksize;

							//切り取り位置の設定
							src.m_top = 0.0f;
							src.m_left = 50.0f;
							src.m_right = 95.0f;
							src.m_bottom = 50.0f;
							//描画
							Draw::Draw(9, &src, &dst, c, 0.0f);

							g_geminiattck_check = true;
						}
					}
				}
			}

			

			if (g_stage == SunLeo)
			{
				for (int i = 0; i < 41; i++)//敵の数分回す
				{
					float lx = *g_leo_x[i];
					float ly = *g_leo_y[i];

					if (g_leo_d_flag[i] == true)
					{
						//UtilityModuleのチェック関数に場所と領域を渡し、領域外か判定
						bool check;
						check = CheckWindow(lx + block->GetScrollx(), ly + block->GetScrolly(), 10.0f, 10.0f, 790.0f, 590.0f);
						if (check == true)
						{
							//ミニマップに敵の位置を表示する
							//表示位置の設定
							dst.m_top = m_uisize_y + (ly / ((MAPSIZE * 64.0f) / (MAPSIZE * m_blocksize)));
							dst.m_left = m_uisize_x + (lx / ((MAPSIZE * 64.0f) / (MAPSIZE * m_blocksize)));
							dst.m_right = dst.m_left + m_blocksize;
							dst.m_bottom = dst.m_top + m_blocksize;

							//切り取り位置の設定
							src.m_top = 0.0f;
							src.m_left = 50.0f;
							src.m_right = 95.0f;
							src.m_bottom = 50.0f;
							//描画
							Draw::Draw(9, &src, &dst, c, 0.0f);
							g_geminiattck_check = true;
						}
					}
				}
			}

			if (g_stage == EarthStar && g_Boss_Spawn == true)
			{
				float bossx = *g_boss_x;
				float bossy = *g_boss_y;

				if (g_boss_d_flag == true)
				{
					////UtilityModuleのチェック関数に場所と領域を渡し、領域外か判定
					//bool check;
					//check = CheckWindow(bossx + block->GetScrollx(), bossy + block->GetScrolly(), 10.0f, 10.0f, 790.0f, 590.0f);
					//if (check == true)
					//{
						//ミニマップに敵の位置を表示する
						//表示位置の設定
						dst.m_top = m_uisize_y + (bossy / ((MAPSIZE * 64.0f) / (MAPSIZE * m_blocksize)));
						dst.m_left = m_uisize_x + (bossx / ((MAPSIZE * 64.0f) / (MAPSIZE * m_blocksize)));
						dst.m_right = dst.m_left + m_blocksize;
						dst.m_bottom = dst.m_top + m_blocksize;

						//切り取り位置の設定
						src.m_top = 0.0f;
						src.m_left = 50.0f;
						src.m_right = 95.0f;
						src.m_bottom = 50.0f;
						//描画
						Draw::Draw(9, &src, &dst, c, 0.0f);
						g_geminiattck_check = true;
					//}
				}


				CObjSnake* snake = (CObjSnake*)Objs::GetObj(OBJ_SNAKE);

				if (snake != nullptr)
				{
					for (int i = 0; i < 19; i++)//敵の数分回す
					{
						float snakex = *g_snake_x[i];
						float snakey = *g_snake_y[i];

						if (g_snake_d_flag[i] == true)
						{
							//UtilityModuleのチェック関数に場所と領域を渡し、領域外か判定
							bool check;
							check = CheckWindow(snakex + block->GetScrollx(), snakey + block->GetScrolly(), 10.0f, 10.0f, 790.0f, 590.0f);
							if (check == true)
							{
								//ミニマップに敵の位置を表示する
								//表示位置の設定
								dst.m_top = m_uisize_y + (snakey / ((MAPSIZE * 64.0f) / (MAPSIZE * m_blocksize)));
								dst.m_left = m_uisize_x + (snakex / ((MAPSIZE * 64.0f) / (MAPSIZE * m_blocksize)));
								dst.m_right = dst.m_left + m_blocksize;
								dst.m_bottom = dst.m_top + m_blocksize;

								//切り取り位置の設定
								src.m_top = 0.0f;
								src.m_left = 50.0f;
								src.m_right = 95.0f;
								src.m_bottom = 50.0f;
								//描画
								Draw::Draw(9, &src, &dst, c, 0.0f);
								g_geminiattck_check = true;
							}
						}
					}
				}
			}
		}
	}
}