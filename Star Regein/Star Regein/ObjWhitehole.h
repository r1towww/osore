#pragma once
//使用するヘッダーファイル
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：ブロック＆背景
class CObjWhitehole : public CObj
{
	public:
		CObjWhitehole(float x, float y);
		~CObjWhitehole() {};
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
