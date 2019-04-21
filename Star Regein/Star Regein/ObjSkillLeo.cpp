//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\HitBoxManager.h"


#include "GameHead.h"
#include "ObjSkillLeo.h"

//使用するネームスペース
using namespace GameL;

CObjSkillLeo::CObjSkillLeo(int x, int y)
{
	m_x = x;
	m_y = y;
}


//イニシャライズ
void CObjSkillLeo::Init()
{
	m_time = 0;


	//当たり判定をセット
	Hits::SetHitBox(this, m_x - 25, m_y - 25, 128, 128, ELEMENT_SKILL_LEO, OBJ_SKILL_LEO, 1);
}

//アクション
void CObjSkillLeo::Action()
{


	//HitBoxの内容を更新
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_x - 25, m_y - 25);

	m_time++;

	//一定時間経つと削除
	if (m_time >= 10)
	{
		m_time = 0.0f;

		this->SetStatus(false);    //自身に削除命令を出す
		Hits::DeleteHitBox(this);  //主人公機が所有するHitBoxに削除する
	}

}

//ドロー
void CObjSkillLeo::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置


	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 250.0f;
	src.m_bottom = 250.0f;

	//表示位置の設定
	dst.m_top = 0.0f + m_y-40;
	dst.m_left = 0.0f + m_x-45;
	dst.m_right = 128.0f + m_x;
	dst.m_bottom = 128.0f + m_y;

	//表示
	Draw::Draw(23, &src, &dst, c, 0.0f);


}