#pragma once
//使用するヘッダー
#include"GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：タイトル
class CObjWorning :public CObj
{
public:
	CObjWorning() {};
	~CObjWorning() {};
	void Init();		//イニシャライズ
	void Action();		//アクション
	void Draw();		//ドロー

private:

	float m_worning_alpha;

	int m_worning_time;
	int m_count;

	bool m_switch;
};