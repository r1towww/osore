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
	m_ani_flag = false;	//trueでアニメーション動作、falseでアニメーション停止
	m_eff.m_top    =   0;
	m_eff.m_left   =   0;
	m_eff.m_right  = 200;
	m_eff.m_bottom = 200;
}

//アクション
void CObjSkillLibra::Action()
{
	
	//エフェクト用
	RECT_F ani_src[8] =
	{
		{ 0,    0,   200, 200 },
		{ 0,  200,   400, 200 },
		{ 0,  400,   600, 200 },
		{ 0,  600,   800, 200 },
		{ 0,  800,  1000, 200 },
		{ 0, 1000,  1200, 200 },
		{ 0, 1200,  1400, 200 },
		{ 0, 1400,  1600, 200 },
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
	//８番目（画像最後）まで進んだら、削除
	if (m_ani == 8)
	{
		this->SetStatus(false);
	}

}

//ドロー
void CObjSkillLibra::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F dst;	//描画先表示位置

	//表示位置の設定
	dst.m_top    =  0.0f + m_y;		//位置の調整
	dst.m_left   = 80.0f + m_x;
	dst.m_right  =  0.0f + m_x;
	dst.m_bottom = 80.0f + m_y;

	//描画
	Draw::Draw(14, &m_eff, &dst, c, 0.0f);
}