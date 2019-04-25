#pragma once
//使用するヘッダー
#include "GameL\DrawTexture.h"
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト:主人公
class CObjHero :public CObj
{
	public:
		CObjHero(float x, float y) ;
		~CObjHero() {};
		void Init();    //イニシャライズ
		void Action();  //アクション
		void Draw();    //ドロー

		float GetX() { return m_px; }
		float GetY() { return m_py; }
		float GetVY() { return m_vy; }
		float GetVX() { return m_vx; }
		float GetPos() { return g_posture; }
		void SetX(float x) { m_px = x; }
		void SetY(float y) { m_py = y; }
		void SetVY(float vy) { m_vy = vy; }
		void SetVX(float vx) { m_vx = vx; }
		float GetDashF() { return m_dash_flag; } //ダッシュフラグの取得

	
	private:
		float m_px;  //位置
		float m_py;
		float m_vx;  //移動ベクトル
		float m_vy;

		float m_alpha;//透明度
	
		int m_blackhole_num;	//惑星ごとのブラックホールの数の値を入れる

		float m_speed_power; //スピードパワー

		int m_ani_time; //アニメーションフレーム動作間隔
		int m_ani_frame;//描画フレーム

		int	 m_ani;			//アニメーション用
		int  m_ani2;
		int	 m_eff_time;	//アニメーション間隔タイム
		int  m_eff_time2;
		RECT_F m_eff;		//エフェクト描画用
		RECT_F m_eff2;		//獅子攻撃エフェクト描画用

		bool m_libra_eff_f;	//天秤座スキルエフェクト用フラグ
		int m_f;//攻撃制御用
		bool m_key_f;
		bool m_help_key_f;	//helpキー用のフラグ

		int m_time;//無敵時間カウント
		int m_MP_time;//ＭＰ減少カウント
		int m_regene_time;//ＭＰリジェネカウント

	int m_burn_time;//火傷間隔タイム
	int m_burn_max_time;//火傷合計継続時間

	bool m_dash_flag;  //ダッシュフラグ
	bool m_move_flag;  //移動フラグ

		bool m_a_flag;//攻撃制御用

	bool m_burn_f;//火傷時主人公カラー変更用フラグ

	//blockとの衝突状態確認用
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

		bool m_invincible_flag;//無敵フラグ

		bool m_eff_flag;

	
};


