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
	m_gx = x;	//位置
	m_gy = y;
}

//イニシャライズ
void CObjSkillGemini::Init()
{
	m_vx = 0.0f;	//移動ベクトル
	m_vy = 0.0f;
	m_posture = 0.0f;//正面(0.0f) 左(1.0f) 右(2.0f) 背面(3.0f)

	m_ani_time = 0;
	m_ani_frame = 1;	//静止フレームを初期にする

	m_ani_max_time = 15;	//アニメーション間隔幅

	alpha = 1.0;

	m_bullet_time = 0;

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_gx, m_gy, 40, 40, ELEMENT_GREEN, OBJ_SKILL_GEMINI, 1);
}

//アクション
void CObjSkillGemini::Action()
{
	//主人公とブロックの位置を取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	CObjBlock* pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	CObjCow*cow = (CObjCow*)Objs::GetObj(OBJ_COW);
	CObjWoman*woman = (CObjWoman*)Objs::GetObj(OBJ_WOMAN);
	CObjTwinsRed*red = (CObjTwinsRed*)Objs::GetObj(OBJ_TWINS_RED);
	CObjTwinsBlue*bule = (CObjTwinsBlue*)Objs::GetObj(OBJ_TWINS_BLUE);

	//UtilityModuleのチェック関数に場所と領域を渡し、領域外か判定
	bool check;
	check = CheckWindow(m_gx + pb->GetScrollx(), m_gy + pb->GetScrolly(), 0.0f, 0.0f, 800.0f, 600.0f);
	if (check == true)
	{
		//主人公機が存在する場合、誘導角度の計算する
		if (cow || woman || red || bule != nullptr)
		{
			//20°間隔で弾丸発射
			m_bullet_time++;

			if (m_bullet_time > 100)
			{
				m_bullet_time = 0;

				//ブロック情報を持ってくる
				CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

				//サブ機弾丸オブジェクト作成
				CObjSkillBullet* objB = new CObjSkillBullet(m_gx , m_gy);
				Objs::InsertObj(objB, OBJ_SKILL_BULLET, 150);

			}
		}
	}

	//主人公の移動ベクトルを代入
	 m_vx = hero->GetVX()*HERO_VEC;
	 m_vy = hero->GetVY()*HERO_VEC;

	//HitBoxの内容を更新
	 CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_gx + 19 + pb->GetScrollx(), m_gy + 15 + pb->GetScrolly());

	//位置の更新
	m_gx += m_vx;
	m_gy += m_vy;
}

//ドロー
void CObjSkillGemini::Draw()
{
	//アニメーション
	int AniData[4] =
	{ 1,0,2,0, };

	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,alpha };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	//ブロック情報を持ってくる
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//切り取り位置の設定
	src.m_top    = 64.0f * m_posture;
	src.m_left   = 0.0f  + (AniData[m_ani_frame] * 64);
	src.m_right  = 64.0f + (AniData[m_ani_frame] * 64);
	src.m_bottom = src.m_top + 64.0f;

	//表示位置の設定
	dst.m_top    =  0.0f + m_gy + block->GetScrolly();
	dst.m_left   = 32.0f + m_gx + block->GetScrollx();
	dst.m_right  =  0.0f + m_gx + block->GetScrollx();
	dst.m_bottom = 32.0f + m_gy + block->GetScrolly();

	//表示
	Draw::Draw(21, &src, &dst, c, 0.0f);
}