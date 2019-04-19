#pragma once
//使用するヘッダーファイル
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//定数
#define HOLEBALANCE_X 380
#define HOLEBALANCE_Y 280
#define TELEPORTBALANCE 50
#define SETTIME 150

//オブジェクト：ブロック＆背景
class CObjBlackhole : public CObj
{
	public:
		CObjBlackhole(float x, float y,int id);
		~CObjBlackhole() {};
		void Init();		//イニシャライズ
		void Action();		//アクション
		void Draw();		//ドロー

		float* GetBX() { return &m_px; }
		float* GetBY() { return &m_py; }
		float Getx() { return m_px; }	// X位置の取得
		float Gety() { return m_py; }	// Y位置の取得
		int GetI() { return m_i; }	//I位置の取得
		int GetJ() { return m_j; }	//J位置の取得

	private:
		float m_px;			//位置
		float m_py;
		int m_i;		//位置	
		int m_j;

		int m_time;		//無敵時間の設定

		int m_blackhole_id;
};
