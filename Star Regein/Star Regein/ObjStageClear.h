#pragma once
//使用するヘッダー
#include"GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：タイトル
class CObjStageClear :public CObj
{
	public:
		CObjStageClear() {};
		~CObjStageClear() {};
		void Init();		//イニシャライズ
		void Action();		//アクション
		void Draw();		//ドロー
		void alpha();
	private:
		int m_time;	//表示までの時間間隔

		//各メッセージの透明度用変数
		
		float m_Tra;

		int	 m_ani;			//アニメーション用
		int	 m_ani_time;	//アニメーション間隔タイム
		RECT_F m_eff;		//エフェクト描画用
		bool m_ani_flag;	//trueでアニメーション動作、falseでアニメーション停止

		bool m_push_flag;
		float m_alpha[7] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };

};