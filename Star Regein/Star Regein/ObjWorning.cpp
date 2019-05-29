//使用するヘッダー
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\SceneManager.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "ObjWorning.h"

//----------------------------------
//使用するネームスペース
using namespace GameL;


//イニシャライズ
void CObjWorning::Init()
{
	m_count = 0;
	m_worning_alpha = 0.0f;
	m_worning_time = 0;
	m_switch = false;
}

//アクション
void CObjWorning::Action()
{
	m_worning_time++;

	if (m_worning_alpha >= 1.0f)
	{
		m_worning_alpha = 1.0f;
		m_switch = true;
	}
	if(m_switch == false )
	{
		m_worning_alpha += 0.03f;
	}

	if (m_worning_alpha <= 0.0f)
	{
		m_worning_alpha = 0.0f;
		m_switch = false;
		m_count++;
	}
	if(m_switch == true)
	{
		m_worning_alpha -= 0.03f;
	}

	if (m_count == 3)
	{
		this->SetStatus(false);		//削除
		Audio::Start(3);
		g_tutorial_flag = true;
		//チュートリアル吹き出し作成
		CObjTutorial* objtutorialhukidashi = new CObjTutorial(0, 2);
		Objs::InsertObj(objtutorialhukidashi, OBJ_TUTORIAL, 151);
		//チュートリアルオブジェクト作成
		CObjTutorial* objtutorial = new CObjTutorial(1, 2);
		Objs::InsertObj(objtutorial, OBJ_TUTORIAL, 170);
		//テキストボックスオブジェクト作成
		CObjTextBox* objtextbox = new CObjTextBox();
		Objs::InsertObj(objtextbox, OBJ_TEXTBOX, 160);
	}
}

//ドロー
void CObjWorning::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,m_worning_alpha };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	//WORNING!!帯表示
	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 10.0f + m_worning_time;
	src.m_right = 810.0f + m_worning_time;
	src.m_bottom = 500.0f;

	//表示位置の設定
	dst.m_top = 50.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 550.0f;
	//表示
	Draw::Draw(50, &src, &dst, c, 0.0f);

	//マーク表示
	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1400.0f;
	src.m_bottom = 1103.0f;

	//表示位置の設定
	dst.m_top = 200.0f;
	dst.m_left = 280.0f;
	dst.m_right = 534.0f;
	dst.m_bottom = 420.0f;

	//表示
	Draw::Draw(51, &src, &dst, c, 0.0f);

}
