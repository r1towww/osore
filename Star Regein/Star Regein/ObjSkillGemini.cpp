//使用するヘッダーファイル
#include <stdlib.h>
#include <time.h>
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjSkillGemini.h"
#include "UtilityModule.h"

//使用するネームスペース

using namespace GameL;

CObjSkillGemini::CObjSkillGemini(float x, float y)
{
	m_px = x;	//位置
	m_py = y;
}

//イニシャライズ
void CObjSkillGemini::Init()
{
	m_vx = 0.0f;	//移動ベクトル
	m_vy = 0.0f;
	m_posture = 0.0f;//正面(0.0f) 左(1.0f) 右(2.0f) 背面(3.0f)

	m_ani_time = 0;
	m_ani_frame = 1;	//静止フレームを初期にする

	m_speed_power = 2.0f;//通常速度
	m_ani_max_time = 15;	//アニメーション間隔幅
	
	m_movey = false; //true=正面　false=背面
	m_movex = false;	//true=右　false=左

	//blockとの衝突状態確認用
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px + 2, m_py + 4, 50, 50, ELEMENT_PLAYER, OBJ_SKILL_GEMINI, 1);
}

//アクション
void CObjSkillGemini::Action()
{
	int Direction = 0; // 適当な変数、既にあるなら宣言必要なし

	srand(time(NULL)); // ランダム情報を初期化

	Direction = rand() % 4; // このように記述するとnpcには０～3までの値が入ります

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
		m_vy = 1.0f;
		m_posture = HERO_DOWN;
		m_ani_time += 1;
	}
	if (m_movey == false)
	{
		m_vy = -1.0f;
		m_posture = HERO_UP;
		m_ani_time += 1;
	}
	if (m_movex == true)
	{
		m_vx = 1.0f;
		m_posture = HERO_RIGHT;
		m_ani_time += 1;
	}
	if (m_movex == false)
	{
		m_vx = -1.0f;
		m_posture = HERO_LEFT;
		m_ani_time += 1;
	}

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
	pb->BlockHit(&m_px, &m_py, true,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy
	);

	//主人公の位置を取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//UtilityModuleのチェック関数に場所と領域を渡し、領域外か判定
	bool check;
	check = CheckWindow(m_px, m_py, -100.0f, -100.0f, 900.0f, 700.0f);
	if (check ==true)
	{
		;
	}
	else
	{
		m_px = hero->GetX();
		m_py = hero->GetY();
	}
	
	//HitBoxの内容を更新
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + 2 , m_py + 4 );

	if (hero != nullptr)
	{
		float hx = hero->GetX();
		float hy = hero->GetY();
	}

	//主人公周辺で動くため
	if (hero->GetX() <= m_px - 100)
	{
		m_movex == false;
	}

	else if (hero->GetX() >= m_px + 100)
	{
		m_movex == true;
	}

	if (hero->GetY() <= m_py - 100)
	{
		m_movey == false;
	}

	else if (hero->GetY() >= m_py + 100)
	{
		m_movey == true;
	}


	//敵とBLOCK系統との当たり判定
	if (hit->CheckElementHit(ELEMENT_BLOCK) == true)
	{
		//敵がブロックとどの角度で当たっているのかを確認
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
					m_movex = false;
				}
				if (r > 45 && r < 135)
				{
					m_movey = true;
				}
				if (r >= 135 && r < 225)
				{
					m_movex = true;
				}
				if (r >= 225 && r < 315)
				{
					m_movey = false;
				}
			}
		}
	}


	//位置の更新
	m_px += m_vx;
	m_py += m_vy;
}

//ドロー
void CObjSkillGemini::Draw()
{
	//アニメーション
	int AniData[5] =
	{
		0,1,2,3,0,
	};

	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	//ブロック情報を持ってくる
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//切り取り位置の設定
	src.m_top = 64.0f * m_posture;
	src.m_left = 0.0f + (AniData[m_ani_frame] * 64);
	src.m_right = 64.0f + (AniData[m_ani_frame] * 64);
	src.m_bottom = src.m_top + 64.0f;

	//表示位置の設定
	dst.m_top = 0.0f + m_py;
	dst.m_left = 80.0f + m_px;
	dst.m_right = 0.0f + m_px;
	dst.m_bottom = 80.0f + m_py;

	//表示

	Draw::Draw(1, &src, &dst, c, 0.0f);
}