#pragma once
//使用するヘッダー
#include"GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;


//オブジェクト：タイトル
class CObjTutorial :public CObj
{
public:
	CObjTutorial(int t, int p) { m_tipe = t; m_p = p; };
	~CObjTutorial() {};
	void Init();		//イニシャライズ
	void Action();		//アクション
	void Draw();		//ドロー
	int Getline() { return m_line; }

private:
	int m_tipe;		//動作の種類
	int m_page;		//ページ数
	int m_p;		//渡されたページ数
	int m_sec;		//セコンド(秒)
	float m_keytime;	//キー入力ができるまでの時間
	bool m_next_f;
	int m_line;		//行数
	bool m_f;

};