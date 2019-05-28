#pragma once
//使用するヘッダー
#include"GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：タイトル
class CObjTitle :public CObj
{
public:
	CObjTitle() {};
	~CObjTitle() {};
	void Init();		//イニシャライズ
	void Action();		//アクション
	void Draw();		//ドロー
private:
	bool m_up;
	bool m_down;
	bool m_start;
	bool m_end;
	float m_Tra;
	bool m_time;
	bool m_key_flag;	//キー制御フラグ
	bool m_Allclear;	//チートオン
	bool m_f;
};