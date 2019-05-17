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
		float m_Eff_Tra;

		int	 m_ani;			//アニメーション用
		int	 m_ani_time;	//アニメーション間隔タイム
		RECT_F m_eff;		//エフェクト描画用
		bool m_ani_flag;	//trueでアニメーション動作、falseでアニメーション停止
		int m_cnt;	//どの評価星を表示し終えたかのカウント用
		bool m_cnt_f;		//カウントするかどうかのフラグ
		bool m_f[10] = { false,false,false,false,false,false,false,false,false,false };	//各評価星のエフェクト処理を終えたかどうかのフラグ
		bool m_grade_f[4]{ false,false, false, false, };	//各評価を終えたかどうか


		int m_kill_grade;		//キル数の評価
		int m_kill_star_cnt;		//キルグレード数用のカウント

		

		int m_time_grade;		//タイムの評価
		
		int m_damage_star_cnt;		//ダメージの評価
		int m_draw_time;		//グレード別表示時間
		bool m_draw_f;			//グレード別表示フラグ

		bool m_push_flag;
		float m_alpha[7] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };	//メッセージalpha値変更用

};