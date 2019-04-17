//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameHead.h"
#include "ObjStarEffect.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjStarEffect::CObjStarEffect(float x, float y)
{
	m_x = x;
	m_y = y;

}



//イニシャライズ
void CObjStarEffect::Init()
{

}
//アニメーションフラグ変更用
void CObjStarEffect::Set(bool f)
{
	//m_ani_flag = f;
}

//アクション
void CObjStarEffect::Action()
{



}
//ドロー
void CObjStarEffect::Draw()
{
	//描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	float  c[4] = { 1.0f,1.0f,1.0f,1.0f };
	CObjStar* obj = (CObjStar*)Objs::GetObj(OBJ_STAR);
	m_x = obj->GetX();
	m_y = obj->GetY();
	RECT_F dst; //描画先表示位置
	//表示位置の設定
	dst.m_top = 0.0f+m_y ;
	dst.m_left = 0.0f+m_x ;
	dst.m_right = 300.0f+m_x;
	dst.m_bottom = 300.0f+m_y;

	//番目に登録したグラフィックをdst・cの情報を元に描画
	Draw::Draw(99, &m_eff, &dst, c, 0.0f);
}