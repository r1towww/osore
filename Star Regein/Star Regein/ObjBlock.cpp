//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjBlock.h"

//使用するネームスペース
using namespace GameL;

CObjBlock::CObjBlock(int map[MAPSIZE][MAPSIZE])
{
	//マップデータをコピー
	memcpy(m_map, map, sizeof(int)*(MAPSIZE * MAPSIZE));
}

//イニシャライズ
void CObjBlock::Init()
{

	//敵出現
	//for (int i = 0; i < MAPSIZE; i++)
	//{
	//	for (int j = 0; j < MAPSIZE; j++)
	//	{
	//		if (m_map[i][j] == 5)
	//		{
	//			//牛オブジェクト作成
	//			CObjCow* cow = new CObjCow(j*MAPSIZE, i*MAPSIZE);
	//			Objs::InsertObj(cow, OBJ_COW, 10);
	//		}
	//	}
	//}

	//出現
	for (int i = 0; i < MAPSIZE; i++)
	{
		for (int j = 0; j < MAPSIZE; j++)
		{
			if (m_map[i][j] == 3)
			{
				//主人公オブジェクト作成
				CObjHero* obj = new CObjHero(j*64.0f, i*64.0f);//オブジェクト作成
				Objs::InsertObj(obj, OBJ_HERO, 10);//マネージャに登録

				m_scrollx = -j * MAPSIZE;
				m_scrolly = -i * MAPSIZE;

			}
			if (m_map[i][j] == 2)
			{
				//星オブジェクト作成
				CObjStar* objstar = new CObjStar(j*64.0f, i*64.0f);//オブジェクト作成
				Objs::InsertObj(objstar, OBJ_STAR, 9);//マネージャに登録

			}
		}
	}
}

//アクション
void CObjBlock::Action()
{

	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	//主人公の位置を取得
	float hx = hero->GetX();
	float hy = hero->GetY();

	//スクロール
	hero->SetX(375);
	m_scrollx -= hero->GetVX() * 4;

	hero->SetY(275);
	m_scrolly -= hero->GetVY() * 4;


}

//ドロー
void CObjBlock::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

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
	Draw::Draw(5, &src, &dst, c, 0.0f);

	/* ブロック（障害物用） */
	for (int i = 0; i < MAPSIZE; i++)
	{
		for (int j = 0; j < MAPSIZE; j++)
		{
			if (m_map[i][j] >= 0)
			{
				//表示位置の設定
				dst.m_top    = i*64.0f + m_scrolly;
				dst.m_left   = j*64.0f + m_scrollx;
				dst.m_right  = dst.m_left + 64.0f;
				dst.m_bottom = dst.m_top  + 64.0f;
				if (m_map[i][j] == 1)
				{
					//切り取り位置の設定
					src.m_top    = 0.0f;
					src.m_left   = 0.0f;
					src.m_right  = 258.0f;
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
//その結果は引数４～10に返す
void CObjBlock::BlockHit
(
	float *x, float *y, bool scroll_on,
	bool*up, bool* down, bool*left, bool*right,
	float*vx, float*vy, int*bt
)
{
	//主人公の衝突状態確認用フラグの初期化
	*up = false;
	*down = false;
	*left = false;
	*right = false;

	//踏んでいるblockの種類の初期化
	*bt = 0;

	//m_mapの全要素にアクセス
	for (int i = 0; i < MAPSIZE; i++)
	{
		for (int j = 0; j < MAPSIZE; j++)
		{
			if (m_map[i][j] == 1 || m_map[i][j] == 99)
			{
				//要素番号を座標に変更
				float bx = j*64.0f;
				float by = i*64.0f;

				//スクロールの影響
				float scrollx = scroll_on ? m_scrollx : 0;
				float scrolly = scroll_on ? m_scrolly : 0;

				//オブジェクトとブロックの当たり判定
				if ((*x + (-scrollx) + 64.0f > bx) && (*x + (-scrollx) < bx + 64.0f) && (*y + (-scrolly) + 64.0f > by) && (*y + (-scrolly) < by + 64.0f))
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
							*x = bx + 64.0f + (scrollx);//ブロックの位置+オブジェクトの幅
							*vx = 0.15f;//-VX*反発係数
						}

						if (r > 45 && r < 135)
						{
							*down = true;//オブジェクトの下の部分が衝突している
							*y = by - 64.0f + (scrolly);//ブロックの位置-オブジェクトの幅
							*vy = -0.15f;
						}
						if (r > 135 && r < 225)
						{
							*left = true;//オブジェクトの右部分が衝突している
							*x = bx - 64.0f + (scrollx);//ブロックの位置-オブジェクトの幅
							*vx = -0.15f;//-VX*反発係数
						}
						if (r > 225 && r < 315)
						{
							*up = true;//オブジェクトの上の部分が衝突している
							*y = by + 64.0f + (scrolly);//ブロックの位置+オブジェクトの幅							
							*vy = 0.15f;
						}
					}
				}
			}
		}
	}
}