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
	m_memory = g_skill;	//スキル比較変数の初期化
	m_next = 0;	//スキル画像用変数の初期化
	m_back = 0;	//スキル画像用変数の初期化

	m_right_f = false;
	m_left_f = false;

}

//アクション
void CObjSkill::Action()
{
	//スキルを取得しているかどうかの確認（取得していない、値が上回る、下回る場合）
	
	//スキルの値が減った場合
	if (g_skill < m_memory) {
		//処理の前にNoSkillを下回っている場合があるので、先に書く
		if (g_skill < NoSkill)	//スキルの値がNoSkillを下回った場合
			g_skill = Leo;		//獅子座に変更	
		if (g_Taurus == false && g_skill == Taurus)//牡牛座を取得していない場合
			g_skill--;	//次の画像へ移す
		if (g_Libra == false && g_skill == Libra)	//天秤座を取得していない場合
			g_skill--;	//次の画像へ移す
		if (g_Gemini == false && g_skill == Gemini)//双子座を取得していない場合
			g_skill--;	//次の画像へ移す
		if (g_Virgo == false && g_skill == Virgo)	//乙女座を取得していない場合
			g_skill--;	//次の画像へ移す
		if (g_Leo == false && g_skill == Leo)		//獅子座を取得していない場合
			g_skill--;	//次の画像へ移す
	}
	
	//スキルの値が増えた場合
	if (g_skill > m_memory) {
		if (g_Taurus == false && g_skill == Taurus)//牡牛座を取得していない場合
			g_skill++;	//次の画像へ移す
		if (g_Libra == false && g_skill == Libra)	//天秤座を取得していない場合
			g_skill++;	//次の画像へ移す
		if (g_Gemini == false && g_skill == Gemini)//双子座を取得していない場合
			g_skill++;	//次の画像へ移す
		if (g_Virgo == false && g_skill == Virgo)	//乙女座を取得していない場合
			g_skill++;	//次の画像へ移す
		if (g_Leo == false && g_skill == Leo)		//獅子座を取得していない場合
			g_skill++;	//次の画像へ移す
		//処理の後にLeoを上回っている場合があるので、後に書く
		if (g_skill > Leo)	//スキルの値がLeoを上回った場合
			g_skill = NoSkill;	//NoSkillに戻す
	}
	
	//変わったスキルの値を、比較用メモリに保存しておく
	m_memory = g_skill;

	//画像の前後描画用
	if (g_skill == NoSkill) {
		if (g_Leo == true)
			m_left_f = true;
		else
			m_left_f = false;
		if (g_Taurus == true)
			m_right_f = true;
		else
			m_right_f = false;
	}
	if (g_skill == Taurus) {
		m_left_f = true;
		if (g_Libra == true)
			m_right_f = true;
		else
			m_right_f = false;
	}
	if (g_skill == Libra) {
		if (g_Taurus == true)
			m_left_f = true;
		else
			m_left_f = false;
		if (g_Gemini == true)
			m_right_f = true;
		else
			m_right_f = false;
	}
	if (g_skill == Gemini) {
		if (g_Libra == true)
			m_left_f = true;
		else
			m_left_f = false;
		if (g_Virgo == true)
			m_right_f = true;
		else
			m_right_f = false;
	}
	if (g_skill == Virgo) {
		if (g_Gemini == true)
			m_left_f = true;
		else
			m_left_f = false;
		if (g_Leo == true)
			m_right_f = true;
		else
			m_right_f = false;
	}
	if (g_skill == Leo) {
		if (g_Virgo == true)
			m_left_f = true;
		else
			m_left_f = false;
		m_next = true;
	}

	
}

//ドロー
void CObjSkill::Draw()
{
	//クリアオブジェクトが作成されている際、描画の停止
	if (g_stage_clear == false)
	{
		//描画カラー情報
		float c[4] = { 1.0f,1.0f,1.0f,1.0f };
		float b[4] = { 0.0f,0.0f,0.0f,1.0f };

		float s[4] = { 1.0f,1.0f,1.0f,0.5f };
		RECT_F src;	//描画元切り取り位置
		RECT_F dst;	//描画先表示位置
		
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f + (300.0f * g_skill);		//スキルの値が変われば次の画像へ移行
		src.m_right = 300.0f + (300.0f * g_skill);
		src.m_bottom = 200.0f;

		//表示位置の設定
		dst.m_top = 450.0f;
		dst.m_left = 550.0f;
		dst.m_right = 750.0f;
		dst.m_bottom = 600.0f;
		Draw::Draw(13, &src, &dst, c, 0.0f);

		//後ろにあるスキルを表示
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 1500.0f + (300.0f * (g_skill));		//スキルの値が変われば次の画像へ移行
		src.m_right = 1800.0f + (300.0f * (g_skill));
		src.m_bottom = 200.0f;

		//表示位置の設定
		dst.m_top = 550.0f;
		dst.m_left = 500.0f;
		dst.m_right = 580.0f;
		dst.m_bottom = 600.0f; 
		if(m_left_f == true)
			Draw::Draw(13, &src, &dst, s, 0.0f);
		else
			Draw::Draw(13, &src, &dst, b, 0.0f);
	
		//前にあるスキルを表示
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 300.0f + (300.0f * (g_skill));		//スキルの値が変われば次の画像へ移行
		src.m_right = 600.0f + (300.0f * (g_skill));
		src.m_bottom = 200.0f;

		//表示位置の設定
		dst.m_top = 550.0f;
		dst.m_left = 720.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 600.0f;
		if (m_right_f == true)
			Draw::Draw(13, &src, &dst, s, 0.0f);
		else
			Draw::Draw(13, &src, &dst, b, 0.0f);

	}
}