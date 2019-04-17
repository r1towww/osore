//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"

#include "GameHead.h"
#include "ObjSkill.h"

//使用するネームスペース
using namespace GameL;
/*
		 スキルごとの値 
	NoSkill,	//スキル無し	0
	Taurus,		//牡牛座		1
	Libra,		//天秤座		2
	Gemini,		//双子座		3
	Virgo,		//乙女座		4
	Leo,		//獅子座		5

		各星座の取得情報
	g_Taurus;	//牡牛座	
	g_Libra;	//天秤座
	g_Gemini;	//双子座
	g_Virgo;	//乙女座
	g_Leo;		//獅子座

*/

//イニシャライズ
void CObjSkill::Init()
{

}

//アクション
void CObjSkill::Action()
{
	//スキルを持っていない場合の処理
	if (g_skill > Leo)	//獅子座の値を超えた場合
		g_skill = Taurus;	//牡牛座に戻す
	else if (g_Libra == false && g_skill == Libra)	//天秤座を取得していない場合
		g_skill = Taurus;	//牡牛座に戻す
	else if (g_Gemini == false && g_skill == Gemini)//双子座を取得していない場合
		g_skill = Taurus;	//牡牛座に戻す
	else if (g_Virgo == false && g_skill == Virgo)	//乙女座を取得していない場合
		g_skill = Taurus;	//牡牛座に戻す
	else if (g_Leo == false && g_skill == Leo)		//獅子座を取得していない場合
		g_skill = Taurus;	//牡牛座に戻す

	



}

//ドロー
void CObjSkill::Draw()
{
	if (g_Taurus == false)
		return;

	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

	//切り取り位置の設定
	src.m_top    = 0.0f;
	src.m_left   = 0.0f   + (300.0f * g_skill);		//スキルの値が変われば次の画像へ移行
	src.m_right  = 300.0f + (300.0f * g_skill);
	src.m_bottom = 200.0f;

	//表示位置の設定
	dst.m_top    = 450.0f;
	dst.m_left   = 600.0f;
	dst.m_right  = 800.0f;
	dst.m_bottom = 600.0f;

	//描画
	Draw::Draw(13, &src, &dst, c, 0.0f);
}