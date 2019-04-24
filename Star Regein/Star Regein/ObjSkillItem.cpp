//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjSkillItem.h"

//使用するネームスペース
using namespace GameL;

bool g_Earth_Max = false;
bool g_Taurus_Max = false;
bool g_Libra_Max = false;
bool g_Gemini_Max = false;
bool g_Virgo_Max = false;
bool g_Leo_Max = false;


CObjSkillItem::CObjSkillItem(float x, float y)
{
	m_x = x;
	m_y = y;

}

//イニシャライズ
void CObjSkillItem::Init()
{
	

	m_vx = 0.0f;
	m_vy = 0.0f;

	g_skill_item_flag = false;

	//当たり判定をセット
	Hits::SetHitBox(this, m_x+80, m_y, 60.0f, 60.0f, ELEMENT_SKILL_ITEM, OBJ_SKILL_ITEM, 1);
}

//アクション
void CObjSkillItem::Action()
{
	
	
	//自身のHitBoxを持ってくる
	CHitBox* hit = Hits::GetHitBox(this);
	
	//下に移動
	m_vy += 0.01f;
	m_y += m_vy;

	//作成したHitBox更新用の入り口を取り出す
	hit->SetPos(m_x + 80, m_y);//入り口から新しい位置（主人公の位置）情報に置き換える
	

	//主人公と当たったらオブジェクト削除し、スキルアイテムフラグをオン
	if (hit->CheckElementHit(ELEMENT_PLAYER) == true)
	{
		
		this->SetStatus(false);    //自身に削除命令を出す
		Hits::DeleteHitBox(this);  //主人公機が所有するHitBoxに削除する
		g_skill_item_flag = true;
	}
	
}

//ドロー
void CObjSkillItem::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置


	if (g_Earth_Max == true)//地球
	{
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 300.0f;
		src.m_bottom = 200.0f;
	}
	else if (g_Taurus_Max==true)//牡牛座
	{
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 300.0f;
		src.m_right = 600.0f;
		src.m_bottom = 200.0f;
	}
	else if (g_Libra_Max == true)//天秤座
	{
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 600.0f;
		src.m_right = 900.0f;
		src.m_bottom = 200.0f;	
	}
	else if (g_Gemini_Max == true)//双子座
	{
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 900.0f;
		src.m_right = 1200.0f;
		src.m_bottom = 200.0f;
	}
	else if (g_Virgo_Max == true)//乙女座
	{
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 1200.0f;
		src.m_right = 1500.0f;
		src.m_bottom = 200.0f;
	}
	else if (g_Leo_Max == true)//獅子座
	{
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 1500.0f;
		src.m_right = 1800.0f;
		src.m_bottom = 200.0f;
	}
	//表示位置の設定
	dst.m_top = 0.0f + m_y;
	dst.m_left = 70.0f + m_x;
	dst.m_right = 150.0f + m_x;
	dst.m_bottom = 80.0f + m_y;

	Draw::Draw(13, &src, &dst, c, 0.0f);
}