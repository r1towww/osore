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

bool g_geminiattck_check;

CObjSkillGemini::CObjSkillGemini(float x, float y)
{
	m_gx = x;	//位置
	m_gy = y;
}

//イニシャライズ
void CObjSkillGemini::Init()
{
	m_vx = 0.0f;//移動xベクトル
	m_vy = 0.0f;//移動yベクトル
	m_posture = 0.0f;//正面(0.0f) 左(1.0f) 右(2.0f) 背面(3.0f)

	m_ani_time = 0;
	m_ani_frame = 1;//静止フレームを初期にする

	m_ani_max_time = 10;//アニメーション間隔幅

	m_movey = true; //true=正面　false=背面
	m_movex = true;	//true=右　false=左
	
	m_bullet_time = 0;

	m_time = 1500;

	alpha = 5.0;

	m_pos_x = 0;//主人公と同じ方向に向くため
	m_pos_y = 0;//主人公と同じ方向に向くため
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

	if (g_posture == HERO_UP)  //上
	{
		m_pos_x     = +40.0f;	//X軸調整
		m_pos_y     = -5.0f;	//Y軸調整
		m_ani_time += 1;    //maxまで数える
        m_posture   = 1.0f;   //姿勢
	}
	else if (g_posture == HERO_LEFT) //左
	{
		m_pos_x     = -15.0f;	//X軸調整
		m_pos_y     = -20.0f;	//Y軸調整
		m_ani_time += 1;    //maxまで数える
		m_posture   = 2.0f;   //姿勢
	}
	else if (g_posture == HERO_DOWN) //下
	{
		m_pos_x     = -20.0f;	//X軸調整
		m_pos_y     = +40.0f;	//Y軸調整
		m_ani_time += 1;    //maxまで数える
		m_posture   = 3.0f;   //姿勢
	}
	else if (g_posture == HERO_RIGHT) //右
	{
		m_pos_x     = +35.0f;   //X軸調整
		m_pos_y     = +45.0f;   //Y軸調整
		m_ani_time += 1;    //maxまで数える
		m_posture   = 4.0f;   //姿勢
	}
	//timeの方が大きくなると初期化フレームを進める
	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}
	//フレームが3になると初期化
	if (m_ani_frame == 3)
	{
		m_ani_frame = 0;
	}

	if (g_geminiattck_check ==true)
	{
		//20°間隔で弾丸発射
		m_bullet_time++;

		if (m_bullet_time > 200)
		{
			m_bullet_time = 0;

			//ブロック情報を持ってくる
			CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

			//10発同時発射
			for (int i = 0; i < 360; i += 36)
			{
				//サブ機弾丸オブジェクト作成
				CObjSkillBullet* objB = new CObjSkillBullet(m_gx + m_pos_x, m_gy + m_pos_y, i);
				Objs::InsertObj(objB, OBJ_SKILL_BULLET, 150);
			}
			g_geminiattck_check = false;
		}
	}

	//主人公の移動ベクトルを代入
	 m_vx = hero->GetVX()*HERO_VEC;
	 m_vy = hero->GetVY()*HERO_VEC;

	//位置の更新
	m_gx += m_vx;
	m_gy += m_vy;

	m_time--;

	if (m_time < 0)
	{
		this->SetStatus(false);
		g_gemini_check = false;
	}


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
	dst.m_top    =  0.0f + m_gy + m_pos_y + block->GetScrolly();
	dst.m_left   = 70.0f + m_gx + m_pos_x + block->GetScrollx();
	dst.m_right  =  0.0f + m_gx + m_pos_x + block->GetScrollx();
	dst.m_bottom = 70.0f + m_gy + m_pos_y + block->GetScrolly();

	//表示
	Draw::Draw(21, &src, &dst, c, 0.0f);
}