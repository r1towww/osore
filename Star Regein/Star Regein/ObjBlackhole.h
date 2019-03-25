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
		CObjBlackhole(float x, float y);
		~CObjBlackhole() {};
		void Init();		//イニシャライズ
		void Action();		//アクション
		void Draw();		//ドロー

		float Getx() { return m_px; }	// X位置の取得
		float Gety() { return m_py; }	// Y位置の取得

	private:
		float m_px;			//位置
		float m_py;
		int m_time;		//無敵時間の設定
};
