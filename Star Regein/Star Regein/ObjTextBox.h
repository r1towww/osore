#pragma once
//使用するヘッダー
#include"GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;


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
	int m_text;		//渡されたページ数

};