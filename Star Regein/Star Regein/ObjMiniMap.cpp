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

CObjMiniMap::CObjMiniMap(int map[MAPSIZE][MAPSIZE])
{
	//マップデータをコピー
	memcpy(m_map, map, sizeof(int)*(MAPSIZE * MAPSIZE));
}

//イニシャライズ
void CObjMiniMap::Init()
{

	
}

//アクション
void CObjMiniMap::Action()
{



}

//ドロー
void CObjMiniMap::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,0.7f };

	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

	/* 背景用 */
	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	//表示位置の設定
	dst.m_top = 10.0f;
	dst.m_left = 590.0f;
	dst.m_right = 790.0f;
	dst.m_bottom = 210.0f;

	//描画
	Draw::Draw(7, &src, &dst, c, 0.0f);

	/* ブロック（障害物用） */
	for (int i = 0; i < MAPSIZE; i++)
	{
		for (int j = 0; j < MAPSIZE; j++)
		{
			if (m_map[i][j] >= 0)
			{
				//表示位置の設定
				dst.m_top    = i*7.0f + 10.0f;
				dst.m_left   = j*7.0f + 590.0f;
				dst.m_right  = dst.m_left + 7.0f;
				dst.m_bottom = dst.m_top + 7.0f;
				if (m_map[i][j] == 1)
				{
					//切り取り位置の設定
					src.m_top = 0.0f;
					src.m_left = 0.0f;
					src.m_right = 258.0f;
					src.m_bottom = 220.0f;
					//描画
					Draw::Draw(4, &src, &dst, c, 0.0f);
				}
				if (m_map[i][j] == 99)
				{
					//切り取り位置の設定
					src.m_top = 0.0f;
					src.m_left = 0.0f;
					src.m_right = 258.0f;
					src.m_bottom = 220.0f;
					//描画
					Draw::Draw(4, &src, &dst, c, 0.0f);
				}

				else
				{

				}
			}
		}
	}
}
