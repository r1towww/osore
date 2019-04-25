#pragma once
//使用するヘッダーファイル
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：ブロック＆背景
class CObjBreakBigRock : public CObj
{
	public:
		CObjBreakBigRock(float x, float y, int i, int j);
		~CObjBreakBigRock() {};
		void Init();		//イニシャライズ
		void Action();		//アクション
		void Draw();		//ドロー

	private:
		float m_px;			//位置
		float m_py;
		int m_i;		//マップ上の座標取得用
		int m_j;

		int m_cnt;		//消滅までのカウント用
		bool m_f;		//無敵用フラグ

		float m_bom_x;	//爆発エフェクトの表示位置
		float m_bom_y;

		bool m_eff_flag;	//エフェクト用フラグ
		int	 m_ani;			//アニメーション用
		int	 m_ani_time;	//アニメーション間隔タイム
		RECT_F m_eff;		//エフェクト描画用

};
