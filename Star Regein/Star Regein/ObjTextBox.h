#pragma once
//使用するヘッダー
#include"GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//定数
#define TEXT_X 20
#define TEXT_Y1 450
#define TEXT_Y2 490
#define TEXT_Y3 530

#define TEXT_ZX 600
#define TEXT_ZY 545

#define TEXTSIZE 32
#define TEXTSIZE_Z 25


//オブジェクト：タイトル
class CObjTextBox :public CObj
{
public:
	CObjTextBox() {};
	~CObjTextBox() {};
	void Init();		//イニシャライズ
	void Action();		//アクション
	void Draw();		//ドロー

private:
	bool m_f;
	int m_tipe;		//動作の種類
	int m_page;		//ページ数
	int m_key_time;
	int m_text;		//渡されたページ数

};