//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"
#include "GameHead.h"
#include "GameL/Audio.h"

#include "ObjHelp.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjHelp::Init()
{
	m_f = false;	//フラグの初期化
}

//アクション
void CObjHelp::Action()
{
	//Hキーが離された場合
	if (Input::GetVKey('H') == false)
	{
		m_f = true;	//フラグをオン
	}

	//Hキーが押され、フラグがオンの場合
	if (Input::GetVKey('H') == true && m_f == true || Input::GetVKey('Q') == true)
	{
		Audio::Start(1);	//エフェクト音を鳴らす
		this->SetStatus(false);	//削除
	}

}

//ドロー
void CObjHelp::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };	//メッセージフォントカラー
	float a[4] = { 1.0f,1.0f,1.0f,0.5f };	

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

//背景用画像-----------------------------------
	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 822.0f;
	src.m_bottom = 218.0f;

	//表示位置の設定
	dst.m_top    = 100.0f;
	dst.m_left   = 50.0f;
	dst.m_right  = 750.0f;
	dst.m_bottom = 500.0f;
	//表示
	Draw::Draw(40, &src, &dst, a, 0.0f);
//----------------------------------------------

//操作説明用メッセージ--------------------------

	//説明用のメッセージの表示
	Font::StrDraw(L"Zキー 前方に剣で攻撃", 75, 120, 27, c);	
	Font::StrDraw(L"Xキー 選択中のスキル発動", 75, 155, 27, c);
	Font::StrDraw(L"Cキー スキルの切り替え", 75, 190, 27, c);
	Font::StrDraw(L"Mキー マップの表示", 75, 225, 27, c);



//----------------------------------------------
	//切り取り位置の設定
	src.m_top    = 0.0f;
	src.m_left   = 0.0f + (g_skill * 300.0f);
	src.m_right  = 300.0f + (g_skill * 300.0f);
	src.m_bottom = 200.0f;
	//選択中のスキルによって説明文を変更
	if (g_skill == NoSkill)
	{
		//説明文
		Font::StrDraw(L"*各星座スキル*    発動条件", 310, 320, 25, c);
		Font::StrDraw(L"スキルの説明を見ることができます。", 315, 350, 25, c);
		Font::StrDraw(L"星座をセットしてHキーを入力。", 315, 380, 25, c);
		Font::StrDraw(L"「スキルを使いこなそう。」", 315, 410, 25, c);
	}
	if (g_skill == Taurus)	//牡牛座
	{
		//説明文
		Font::StrDraw(L"*牡牛座スキル*    MP消費 1ゲージ", 310, 320, 25, c);
		Font::StrDraw(L"Shiftキーを押しながら移動すると、", 315, 350, 25, c);
		Font::StrDraw(L"ダッシュが可能！！", 315, 380, 25, c);
		Font::StrDraw(L"「大きな岩も壊せそう。」", 315, 410, 25, c);
	}
	else if (g_skill == Libra)	//天秤座
	{
		//説明文
		Font::StrDraw(L"*天秤座スキル*    徐々にMPを消費", 310, 320, 25, c);
		Font::StrDraw(L"セットすると攻撃力UP！！", 315, 350, 25, c);
		Font::StrDraw(L"HP減少によって攻撃力は変動し、", 315, 380, 25, c);
		Font::StrDraw(L"自動的に効果は発揮されるぞ！", 315, 410, 25, c);
		Font::StrDraw(L"「自分の命は大切に。」", 315, 440, 25, c);
	}
	else if (g_skill == Gemini)	//双子座
	{
		//説明文
		Font::StrDraw(L"*双子座スキル*    MP消費 10ゲージ", 310, 320, 25, c);
		Font::StrDraw(L"共に戦うサブ機を召喚！！", 315, 350, 25, c);
		Font::StrDraw(L"最大1体までしか召喚できないぞ！", 315, 380, 25, c);
		Font::StrDraw(L"「仲間は大事だよ。」", 315, 410, 25, c);

	}
	else if (g_skill == Virgo)	//乙女座
	{
		//説明文
		Font::StrDraw(L"*乙女座スキル*    MP消費 5ゲージ", 310, 320, 25, c);
		Font::StrDraw(L"HPを吸収するハート弾を発射！", 315, 350, 25, c);
		Font::StrDraw(L"向いている方向に飛んでいくぞ！", 315, 380, 25, c);
		Font::StrDraw(L"「少し分けてもらうね...」", 315, 410, 25, c);

	}
	else if (g_skill == Leo)	//獅子座
	{
		//説明文
		Font::StrDraw(L"*獅子座スキル*    MP消費 3ゲージ", 310, 320, 25, c);
		Font::StrDraw(L"主人公周囲の敵をスタン！", 315, 350, 25, c);
		Font::StrDraw(L"使いすぎには注意！", 315, 380, 25, c);
		Font::StrDraw(L"「獅子の力を借りよう。」", 315, 410, 25, c);

	}
	//表示位置の設定
	dst.m_top    = 280.0f;
	dst.m_left   = 40.0f;
	dst.m_right  = 280.0f;
	dst.m_bottom = 480.0f;
	//表示
	Draw::Draw(13, &src, &dst, c, 0.0f);

	if (g_Taurus == true)
	{
		//切り取り位置の設定
		src.m_top    = 0.0f;
		src.m_left   = 300.0f;
		src.m_right  = 600.0f;
		src.m_bottom = 200.0f;
		//表示位置の設定
		dst.m_top    = 150.0f;
		dst.m_left   = 420.0f;
		dst.m_right  = 480.0f;
		dst.m_bottom = 210.0f;
		//表示
		Draw::Draw(13, &src, &dst, c, 0.0f);
	}
	if (g_Libra == true)
	{
		//切り取り位置の設定
		src.m_top    = 0.0f;
		src.m_left   = 600.0f;
		src.m_right  = 900.0f;
		src.m_bottom = 200.0f;
		//表示位置の設定
		dst.m_top    = 150.0f;
		dst.m_left   = 490.0f;
		dst.m_right  = 540.0f;
		dst.m_bottom = 210.0f;
		//表示
		Draw::Draw(13, &src, &dst, c, 0.0f);
	}
	if (g_Gemini == true)
	{
		//切り取り位置の設定
		src.m_top    = 0.0f;
		src.m_left   = 900.0f;
		src.m_right  = 1200.0f;
		src.m_bottom = 200.0f;
		//表示位置の設定
		dst.m_top    = 150.0f;
		dst.m_left   = 550.0f;
		dst.m_right  = 600.0f;
		dst.m_bottom = 210.0f;
		//表示
		Draw::Draw(13, &src, &dst, c, 0.0f);
	}
	if (g_Virgo == true)
	{
		//切り取り位置の設定
		src.m_top    = 0.0f;
		src.m_left   = 1200.0f;
		src.m_right  = 1500.0f;
		src.m_bottom = 200.0f;
		//表示位置の設定
		dst.m_top    = 150.0f;
		dst.m_left   = 610.0f;
		dst.m_right  = 660.0f;
		dst.m_bottom = 210.0f;
		//表示
		Draw::Draw(13, &src, &dst, c, 0.0f);
	}
	if (g_Leo == true)
	{
		//切り取り位置の設定
		src.m_top    = 0.0f;
		src.m_left   = 1500.0f;
		src.m_right  = 1800.0f;
		src.m_bottom = 200.0f;
		//表示位置の設定
		dst.m_top    = 150.0f;
		dst.m_left   = 670.0f;
		dst.m_right  = 720.0f;
		dst.m_bottom = 210.0f;
		//表示
		Draw::Draw(13, &src, &dst, c, 0.0f);
	}
	

}
