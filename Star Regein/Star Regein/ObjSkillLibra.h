#pragma once
//使用するヘッダーファイル
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;


//オブジェクト：ブロック＆背景
class CObjSkillLibra : public CObj
{
	public:
		CObjSkillLibra(float x, float y);
		~CObjSkillLibra() {};
		void Init();		//イニシャライズ
		void Action();		//アクション
		void Draw();		//ドロー

	private:
		float m_x;		//位置
		float m_y;

		bool m_f;		//エフェクト音用フラグ
		int	 m_ani;			//アニメーション用
		int	 m_ani_time;	//アニメーション間隔タイム

		int  m_persist_time;//mp消費間隔タイム

		RECT_F m_eff;		//エフェクト描画用
		bool m_ani_flag;	//trueでアニメーション動作、falseでアニメーション停止

};