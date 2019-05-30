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

CObjSkillLeo::CObjSkillLeo(float x, float y)
{
	m_x = x;
	m_y = y;
}


//イニシャライズ
void CObjSkillLeo::Init()
{
	m_time = 0;

	m_ani = 0;			//チャージアニメーション用
	m_ani_time = 0;	//チャージアニメーション間隔タイム

	m_eff.m_top = 0;
	m_eff.m_left = 0;
	m_eff.m_right = 192;
	m_eff.m_bottom = 192;
	//当たり判定をセット
	Hits::SetHitBox(this, m_x - 25, m_y - 25, 128, 128, ELEMENT_SKILL_LEO, OBJ_SKILL_LEO, 1);
}

//アクション
void CObjSkillLeo::Action()
{


	//HitBoxの内容を更新
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_x - 25, m_y - 25);

	//エフェクト用
	RECT_F ani_src[15] =
	{
		{ 0,   0, 192, 192 },
		{ 0, 192, 384, 192 },
		{ 0, 384, 576, 192 },
		{ 0, 576, 768, 192 },
		{ 0, 768, 960, 192 },
		{ 192,   0, 192, 384 },
		{ 192, 192, 384, 384 },
		{ 192, 384, 576, 384 },
		{ 192, 576, 768, 384 },
		{ 192, 768, 960, 384 },
		{ 384,   0, 192, 576 },
		{ 384, 192, 384, 576 },
		{ 384, 384, 576, 576 },
		{ 384, 576, 768, 576 },
		{ 384, 768, 960, 576 },
	};


	//アニメーションのコマ間隔制御
	if (m_ani_time > 2)
	{
		m_ani++;		//アニメーションのコマを1つ進める
		m_ani_time = 0;

		m_eff = ani_src[m_ani];//アニメーションのRECT配列からm_ani番目のRECT情報取得
	}
	else
	{
		m_ani_time++;
	}
	//14番目（画像最後）まで進んだら、0番目に戻す
	if (m_ani == 14)
	{
		m_ani = 0;
		this->SetStatus(false);    //自身に削除命令を出す
		Hits::DeleteHitBox(this);  //主人公機が所有するHitBoxに削除する
	}

	m_time++;

	//一定時間経つと削除
	if (m_time >= 10)
	{
		m_time = 0.0f;

	}

}

//ドロー
void CObjSkillLeo::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,0.7f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置


	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 250.0f;
	src.m_bottom = 250.0f;

	//表示位置の設定
	dst.m_top    = 0.0f + m_y-40;
	dst.m_left   = 0.0f + m_x-48;
	dst.m_right  = 128.0f + m_x;
	dst.m_bottom = 128.0f + m_y;

	//表示
	Draw::Draw(23, &m_eff, &dst, c, 0.0f);


}