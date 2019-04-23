#pragma once
//使用するヘッダーファイル
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：ブロック＆背景
class CObjBreakRock : public CObj
{
	public:
		CObjBreakRock(float x, float y);
		~CObjBreakRock() {};
		void Init();		//イニシャライズ
		void Action();		//アクション
		void Draw();		//ドロー

	private:
		float m_px;			//位置
		float m_py;

		bool m_eff_flag;	//エフェクト用フラグ
		int	 m_ani;			//アニメーション用
		int	 m_ani_time;	//アニメーション間隔タイム
		RECT_F m_eff;		//エフェクト描画用

};
