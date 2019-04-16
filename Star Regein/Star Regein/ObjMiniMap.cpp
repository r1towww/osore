//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjMiniMap.h"
#include "UtilityModule.h"

//使用するネームスペース
using namespace GameL;

extern float* g_cow_x[20];//全ての牛のX位置を把握する
extern float* g_cow_y[20];//全ての牛のY位置を把握する
int g_map[MAPSIZE][MAPSIZE];

CObjMiniMap::CObjMiniMap(int map[MAPSIZE][MAPSIZE])
{
	//マップデータをコピー
	memcpy(g_map, map, sizeof(int)*(MAPSIZE * MAPSIZE));
}

void CObjMiniMap::Setdcow(bool d_flag)
{
	if (d_flag == true)
	{
		m_df = true;
	}
}

//イニシャライズ
void CObjMiniMap::Init()
{
	if (g_stage == EarthStar) {	//地球の場合
		m_smallsize = 7.0f;	//スモールサイズを7.0fで初期化
		m_bigsize = 14.0f;	//ビッグサイズを14.0fで初期化
	}
	else{	//それ以外の場合
		m_smallsize = 4.0f;	//ステージサイズを4.0fで初期化
		m_bigsize = 8.0f;	//ビッグサイズを8.0fで初期化
	}
	m_blocksize = m_smallsize;	//ブロックサイズとスモールサイズを合わせる

	m_uisize_x = 590.0f, m_uisize_y = 10.0f;	//背景位置の初期化
	m_backsize = 200.0f;	//背景のサイズの初期化
	m_f = false;	//キー入力制御の初期化
	m_alpha = 0.7f;	//アルファ値初期化

	m_df = false;
}


//アクション
void CObjMiniMap::Action()
{
	if (Input::GetVKey('M'))//Mキーが入力されたとき
	{
		//キー入力制御
		if (m_f == true)
		{
			//マップサイズの変更
			if (m_blocksize == m_smallsize)	//小さい場合大きくする
			{
				m_blocksize = m_bigsize;	//ブロックのサイズ変更	
				m_uisize_x = 200.0f, m_uisize_y = 100.0f;	//マップの位置の変更
				m_backsize = 400.0f;						//背景のサイズ変更
				m_alpha = 1.0f;		//アルファ値変更
			}
			else						//大きい場合小さくする
			{
				m_blocksize = m_smallsize;		//ブロックのサイズ変更	
				m_uisize_x = 590.0f, m_uisize_y = 10.0f;	//マップの位置の変更
				m_backsize = 200.0f;						//背景のサイズ変更
				m_alpha = 0.7f;		//アルファ値変更
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
	float c[4] = { 1.0f,1.0f,1.0f,m_alpha};	//基本カラー（半透明）
	float ac[4] = { 1.0f,1.0f,1.0f,1.0f };	//主人公カラー（非透明）

	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

	/* 背景用 */
	//切り取り位置の設定
	src.m_top    = 0.0f;
	src.m_left   = 0.0f;
	src.m_right  = 500.0f;
	src.m_bottom = 500.0f;

	//表示位置の設定
	dst.m_top    = m_uisize_y;
	dst.m_left   = m_uisize_x;
	dst.m_right  = m_uisize_x + m_backsize;
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
				dst.m_top    = i*m_blocksize + m_uisize_y;
				dst.m_left   = j*m_blocksize + m_uisize_x;
				dst.m_right  = dst.m_left + m_blocksize;
				dst.m_bottom = dst.m_top  + m_blocksize;

				if (g_map[i][j] == 1)//隕石
				{
					//切り取り位置の設定
					src.m_top    = 0.0f;
					src.m_left   = 0.0f;
					src.m_right  = 40.0f;
					src.m_bottom = 50.0f;
					//描画
					Draw::Draw(9, &src, &dst, c, 0.0f);
				}
				if (g_map[i][j] == 4 )//星
				{
					//切り取り位置の設定
					src.m_top    = 0.0f;
					src.m_left   = 110.0f;
					src.m_right  = 140.0f;
					src.m_bottom = 50.0f;
					//描画
					Draw::Draw(9, &src, &dst, c, 0.0f);
				}
				if (g_map[i][j] == 7)//ブラックホール
				{
					//切り取り位置の設定
					src.m_top    = 0.0f;
					src.m_left   = 260.0f;
					src.m_right  = 290.0f;
					src.m_bottom = 50.0f;
					//描画
					Draw::Draw(9, &src, &dst, c, 0.0f);
				}
				if (g_map[i][j] == 8)//ホワイトホール
				{
					//切り取り位置の設定
					src.m_top    = 0.0f;
					src.m_left   = 310.0f;
					src.m_right  = 340.0f;
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
				if (g_map[i][j] == g_asteroid || g_map[i][j] == 6)//小惑星
				{
					//切り取り位置の設定
					src.m_top    = 0.0f;
					src.m_left   = 0.0f;
					src.m_right  = 40.0f;
					src.m_bottom = 50.0f;

					//表示位置の設定
					dst.m_top    = i*m_blocksize + m_uisize_y + 2.0f;
					dst.m_left   = j*m_blocksize + m_uisize_x + 4.0f;
					dst.m_right  = dst.m_left + m_blocksize * 1.8;
					dst.m_bottom = dst.m_top + m_blocksize * 1.8;

					//描画
					Draw::Draw(9, &src, &dst, c, 0.0f);
				}
				
			}
		}
	}
	//主人公の情報を取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
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

	if (g_stage == EarthStar)
	{
		for (int i = 0; i < 4; i++)//敵の数分回す
		{
			float bx = *g_twinsblue_x[i];
			float by = *g_twinsblue_y[i];


			if (m_df == false)
			{
				////UtilityModuleのチェック関数に場所と領域を渡し、領域外か判定
				//bool check;
				//check = CheckWindow(cx + block->GetScrollx(), cy + block->GetScrolly(), 10.0f, 10.0f, 790.0f, 590.0f);
				//if (check == true)
				//{
				//ミニマップに敵の位置を表示する
				//表示位置の設定
				dst.m_top = m_uisize_y + (by / ((MAPSIZE * 64.0f) / (MAPSIZE * m_blocksize)));
				dst.m_left = m_uisize_x + (bx / ((MAPSIZE * 64.0f) / (MAPSIZE * m_blocksize)));
				dst.m_right = dst.m_left + m_blocksize;
				dst.m_bottom = dst.m_top + m_blocksize;

				//切り取り位置の設定
				src.m_top = 0.0f;
				src.m_left = 50.0f;
				src.m_right = 100.0f;
				src.m_bottom = 50.0f;
				//描画
				Draw::Draw(9, &src, &dst, c, 0.0f);
			}
		}
		for (int i = 0; i < 4; i++)//敵の数分回す
		{
			float rx = *g_twinsred_x[i];
			float ry = *g_twinsred_y[i];


			if (m_df == false)
			{
				////UtilityModuleのチェック関数に場所と領域を渡し、領域外か判定
				//bool check;
				//check = CheckWindow(cx + block->GetScrollx(), cy + block->GetScrolly(), 10.0f, 10.0f, 790.0f, 590.0f);
				//if (check == true)
				//{
				//ミニマップに敵の位置を表示する
				//表示位置の設定
				dst.m_top = m_uisize_y + (ry / ((MAPSIZE * 64.0f) / (MAPSIZE * m_blocksize)));
				dst.m_left = m_uisize_x + (rx / ((MAPSIZE * 64.0f) / (MAPSIZE * m_blocksize)));
				dst.m_right = dst.m_left + m_blocksize;
				dst.m_bottom = dst.m_top + m_blocksize;

				//切り取り位置の設定
				src.m_top = 0.0f;
				src.m_left = 50.0f;
				src.m_right = 100.0f;
				src.m_bottom = 50.0f;
				//描画
				Draw::Draw(9, &src, &dst, c, 0.0f);
			}
		}
	}

	if (g_stage == VenusTaurus)
	{
		for (int i = 0; i < 13; i++)//敵の数分回す
		{
			float cx = *g_cow_x[i];
			float cy = *g_cow_y[i];

			if (m_df == false)
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
					src.m_right = 100.0f;
					src.m_bottom = 50.0f;
					//描画
					Draw::Draw(9, &src, &dst, c, 0.0f);
				}
			}
		}
	}
}
