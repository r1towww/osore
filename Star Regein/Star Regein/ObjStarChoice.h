#pragma once
//使用するヘッダー
#include"GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：タイトル
class CObjStarChoice :public CObj
{
public:
	CObjStarChoice() {};
	~CObjStarChoice() {};
	void Init();		//イニシャライズ
	void Action();		//アクション
	void Draw();		//ドロー
private:
	bool m_oushi;
	bool m_tenbin;
	float m_Tra1;//透過率
	float m_Tra2;//透過率

};