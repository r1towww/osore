#pragma once
//使用するヘッダーファイル
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：ブロック＆背景
class CObjWhitehole : public CObj
{
	public:
		CObjWhitehole(float x, float y,int id);
		~CObjWhitehole() {};
		void Init();		//イニシャライズ
		void Action();		//アクション
		void Draw();		//ドロー

		float* GetWX() { return &m_px; }
		float* GetWY() { return &m_py; }
		float Getx() { return m_px; }	// X位置の取得
		float Gety() { return m_py; }	// Y位置の取得
		int GetI() { return m_i; }	//I位置の取得
		int GetJ() { return m_j; }	//J位置の取得

	private:
		float m_px;			//位置
		float m_py;
		int m_i;		//位置	
		int m_j;

		int	 m_ani;			//アニメーション用
		int	 m_ani_time;	//アニメーション間隔タイム
		RECT_F m_eff;		//エフェクト描画用

		int m_whitehole_id;
};
