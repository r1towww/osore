//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameHead.h"
#include "ObjStarEffect.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjStarEffect::CObjStarEffect(float x, float y, int i, int j)
{
	m_px = x;		//位置
	m_py = y;
	m_i = i;
	m_j = j;


}



//イニシャライズ
void CObjStarEffect::Init()
{
	m_eff.m_top = 0;
	m_eff.m_left = 0;
	m_eff.m_right = 0;
	m_eff.m_bottom = 0;
	m_ani = 0;
	m_ani_time = 0;
	m_ani_flag = true;
}
//アニメーションフラグ変更用
void CObjStarEffect::Set(bool f)
{
	m_ani_flag = f;
}

//アクション
void CObjStarEffect::Action()
{

	RECT_F ani_src[5] =
	{
		{ 0,   0,  640,  608 },
		{ 0,  700, 640,  608 },
		{ 0,  1500, 640,  608 },
		//{ 0,  2500, 400,  100 },
		//{ 0,  400, 500,  100 },
	};

	if (m_ani_flag == false)
	{
		m_eff = ani_src[5];//アニメーションのRECT配列から4番目のRECT情報取得
	}
	else
	{
		//アニメーションのコマ間隔制御
		if (m_ani_time > 2)
		{
			m_ani++;	//アニメーションのコマを１つ進める
			m_ani_time = 0;

			m_eff = ani_src[m_ani];//アニメーションのRECT配列からm_ani番目のRECT情報取得
		}
		else
		{
			m_ani_time++;
		}
	}
	//if (m_ani == 65)
	//{
	//	;
	//}
}
//ドロー
void CObjStarEffect::Draw()
{
	//描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	float  c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F dst; //描画先表示位置
	CObjStar* objs = (CObjStar*)Objs::GetObj(OBJ_STAR_EFFECT);
	m_x = objs->GetX() + 45;
	m_y = objs->GetY() - 30;
	//表示位置の設定
	dst.m_top = 0.0f + m_y;
	dst.m_left = 0.0f + m_x;
	dst.m_right = 64.0f + m_x;
	dst.m_bottom = 64.0f + m_y;

	//2番目に登録したグラフィックをdst・cの情報を元に描画
	Draw::Draw(6, &m_eff, &dst, c, 0.0f);
}