#pragma once
//使用するヘッダー
#include"GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//定数

//オブジェクト：タイトル
class CObjPerformanceRoom :public CObj
{
public:
	CObjPerformanceRoom() {};
	~CObjPerformanceRoom() {};
	void Init();		//イニシャライズ
	void Action();		//アクション
	void Draw();		//ドロー
private:
	 int m_page;
	 bool m_f;
};
