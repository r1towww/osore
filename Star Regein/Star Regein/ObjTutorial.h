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


private:
	int m_tipe;		//動作の種類
	int m_page;		//ページ数
	int m_p;		//渡されたページ数
	int m_sec;		//セコンド(秒)
	int m_keytime;	//キー入力ができるまでの時間
	int m_line;		//行数

};