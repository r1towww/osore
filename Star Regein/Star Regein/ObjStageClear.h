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
		int m_grade_cnt;	//すべての評価星のカウント
		bool m_grade_cnt_f;	//グレード評価表示用フラグ
		bool m_grade_draw_f;//グレード評価表示用フラグ

		bool m_cnt_f;		//カウントするかどうかのフラグ
		bool m_end_start;
		bool m_end_f;		//最終アニメーション終了フラグ
		bool m_end_s_f;		//星出現開始フラグ

		bool m_grade_f[4] = { false,false, false, false, };	//各評価を終えたかどうか
			
		bool m_kill_star_f[3] = { false, false, false };	//キル数の評価を終えたか
		int m_kill_grade;		//キル数の評価
		int m_kill_star_cnt;		//キルグレード数用のカウント

		bool m_time_star_f[3] = { false, false, false };	//タイムの評価を終えたか
		int m_time_grade;		//タイムの評価
		int m_time_star_cnt;		//タイムグレード数用のカウント

		bool m_damage_star_f[3] = { false, false, false };	//ダメージの評価を終えたか
		int m_damage_grade;		//ダメージの評価
		int m_damage_star_cnt;		//ダメージの評価

		int m_next_cnt;		//次へ進む用カウント
		bool m_key_f;		//キー入力制御用フラグ
		bool m_push_flag;		//暗転用フラグ
		float m_alpha[7] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };	//メッセージalpha値変更用

};