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
	bool m_start;
	bool m_end;
	float m_Tra;
	bool m_time;
	int m_loadtime;
	bool m_key_flag;	//キー制御フラグ
	bool m_Allclear;	//チートオン
	bool m_f;
	bool m_Riset_f;
	int m_cnt;
	bool m_RESET;
	bool m_LEFT;
	bool m_RIGHT;
	int m_se_f;
};