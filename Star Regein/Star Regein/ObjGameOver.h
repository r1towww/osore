#pragma once
//使用するヘッダー
#include"GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//定数

//オブジェクト：タイトル
class CObjGameOver :public CObj
{
public:
	CObjGameOver() {};
	~CObjGameOver() {};
	void Init();		//イニシャライズ
	void Action();		//アクション
	void Draw();		//ドロー
private:
	int m_keytime;	//キー入力タイム用変数
	bool m_Right;
	bool m_Left;
}; 
