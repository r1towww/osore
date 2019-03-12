//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjMiniMap.h"

//使用するネームスペース
using namespace GameL;

int g_map[MAPSIZE][MAPSIZE];

CObjMiniMap::CObjMiniMap(int map[MAPSIZE][MAPSIZE])
{
	//マップデータをコピー
	memcpy(g_map, map, sizeof(int)*(MAPSIZE * MAPSIZE));
}

//イニシャライズ
void CObjMiniMap::Init()
{
	m_blocksize = 7.0f;	//7.0fで初期化
	m_uisize_x = 590.0f, m_uisize_y = 10.0f;	//背景位置の初期化
	m_backsize = 200.0f;	//背景のサイズの初期化
	m_f = false;	//キー入力制御の初期化
	m_alpha = 0.7f;	//アルファ値初期化
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
			if (m_blocksize == 7.0f)	//小さい場合大きくする
			{
				m_blocksize = 14.0f;	//ブロックのサイズ変更	
				m_uisize_x = 200.0f, m_uisize_y = 100.0f;	//マップの位置の変更
				m_backsize = 400.0f;						//背景のサイズ変更
				m_alpha = 1.0f;		//アルファ値変更
			}
			else						//大きい場合小さくする
			{
				m_blocksize = 7.0f;		//ブロックのサイズ変更	
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
	float c[4] = { 1.0f,1.0f,1.0f,m_alpha};
	
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
					src.m_right  = 50.0f;
					src.m_bottom = 50.0f;
					//描画
					Draw::Draw(9, &src, &dst, c, 0.0f);
				}
				if (g_map[i][j] == 4 )//星
				{
					//切り取り位置の設定
					src.m_top    = 0.0f;
					src.m_left   = 0.0f;
					src.m_right  = 640.0f;
					src.m_bottom = 608.0f;

					Draw::Draw(6, &src, &dst, c, 0.0f);
				}
				else
				{

				}
			}
		}
	}

	//主人公の情報を取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	//主人公の位置を取得
	float hx = hero->GetX();
	float hy = hero->GetY();


	for (int i = 0; i < MAPSIZE; i++)
	{
		for (int j = 0; j < MAPSIZE; j++)
		{
			if (g_map[i][j] >= 0)
			{
				//表示位置の設定
				dst.m_top = i*m_blocksize + m_uisize_y;
				dst.m_left = j*m_blocksize + m_uisize_x;
				dst.m_right = dst.m_left + m_blocksize;
				dst.m_bottom = dst.m_top + m_blocksize;

				if (g_map[i][j] ==3)//主人公
				{
					//切り取り位置の設定
					src.m_top = 0.0f;
					src.m_left = 150.0f;
					src.m_right = 200.0f;
					src.m_bottom = 50.0f;
					//描画
					Draw::Draw(9, &src, &dst, c, 0.0f);
				}
			}
		}
	}
}
