//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"

#include "GameHead.h"
#include "ObjSkillLibra.h"

//使用するネームスペース
using namespace GameL;

CObjSkillLibra::CObjSkillLibra(int x, int y)
{
	m_x = x;
	m_y = y;
}


//イニシャライズ
void CObjSkillLibra::Init()
{

	m_ani = 0;			//チャージアニメーション用
	m_ani_time = 0;	//チャージアニメーション間隔タイム

	m_persist_time = 0;

	m_eff.m_top    =   0;
	m_eff.m_left   =   0;
	m_eff.m_right  = 192;
	m_eff.m_bottom = 192;
}

//アクション
void CObjSkillLibra::Action()
{

	//エフェクト用
	RECT_F ani_src[15] =
	{
		{   0,   0, 192, 192 },
		{   0, 192, 384, 192 },
		{   0, 384, 576, 192 },
		{   0, 576, 768, 192 },
		{   0, 768, 960, 192 },
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
	if (m_ani_time > 3)
	{
		m_ani++;		//アニメーションのコマを1つ進める
		m_ani_time = 0;

		m_eff = ani_src[m_ani];//アニメーションのRECT配列からm_ani番目のRECT情報取得
	}
	else
	{
		m_ani_time++;
	}
	//８番目（画像最後）まで進んだら、0番目に戻す
	if (m_ani == 14)
	{
		m_ani = 0;
	}

	m_persist_time++;
	if (m_persist_time > 40)
	{
		m_persist_time = 0;
		g_mp -= 1.0f;
	}

	//MPが0になるか別のスキルが選択されたら
	if (g_skill != Libra || g_mp <= 0.0f)
	{
		this->SetStatus(false);		//削除
	}

}

//ドロー
void CObjSkillLibra::Draw()
{
	//描画カラー情報
	float r[4] = { 1.0f,0.0f,0.0f,0.5f };
	float y[4] = { 1.0f,1.0f,0.0f,0.5f };
	float c[4] = { 1.0f,1.0f,1.0f,0.5f };

	RECT_F dst;	//描画先表示位置

	//表示位置の設定
	dst.m_top    =  0.0f + m_y;		//位置の調整
	dst.m_left   = 80.0f + m_x;
	dst.m_right  =  0.0f + m_x;
	dst.m_bottom = 80.0f + m_y;

	//描画
	if(g_hp <= 20.0f)
		Draw::Draw(14, &m_eff, &dst, r, 0.0f);
	else if (g_hp <= 50.0f)
		Draw::Draw(14, &m_eff, &dst, y, 0.0f);
	else 
		Draw::Draw(14, &m_eff, &dst, c, 0.0f);
}