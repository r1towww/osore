//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"

#include "UtilityModule.h"
#include "GameHead.h"
#include "ObjSkillGemini.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjSkillGemini::Init()
{


}

//アクション
void CObjSkillGemini::Action()
{

	// 主人公機とサブ機で角度を取る。
	CObjHero*obj = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//主人公機が存在する場合、サブ機角度の計算する
	if (obj != nullptr)
	{
		float x = obj->GetX() - m_x;
		float y = obj->GetY() - m_y;
		float ar = GetAtan2Angle(x, -y);

		//サブ機の現在の向いてる角度を取る。
		float br = atan2(-m_vy, m_vx)*180.0f / 3.14f;
		if (br < 0)
		{
			br = 360 - abs(br);
		}

		//主人公機とサブ機角度があまりにもかけ離れたら
		if (ar - br > 20)
		{
			//移動方向を主人公機の方向にする
			m_vx = cos(3.14 / 180 * ar);
			m_vy = -sin(3.14 / 180 * ar);
		}

		float r = 3.14 / 180.0f;   //角度１°
		if (ar < br)
		{
			//移動方向にに+1°加える
			m_vx = m_vx*cos(r) - m_vy*sin(r);
			m_vy = m_vy*cos(r) + m_vx*sin(r);
		}
		else
		{
			//移動方向にに-1°加える
			m_vx = m_vx*cos(-r) - m_vy*sin(-r);
			m_vy = m_vy*cos(-r) + m_vx*sin(-r);

		}
	}
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
	src.m_top = 64.0f * g_posture;
	src.m_left = 0.0f + (AniData[m_ani_frame] * 64);
	src.m_right = 64.0f + (AniData[m_ani_frame] * 64);
	src.m_bottom = src.m_top + 64.0f;

	//表示位置の設定
	dst.m_top    =  0.0f;
	dst.m_left   = 80.0f;
	dst.m_right  =  0.0f;
	dst.m_bottom = 80.0f;

	//描画
	Draw::Draw(1, &src, &dst, c, 0.0f);
}