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
		bool GetDashF() { return m_dash_flag; } //ダッシュフラグの取得

	
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
		int  m_ani3;
		int  m_heal_ani;
		int	 m_eff_time;	//アニメーション間隔タイム
		int  m_eff_time2;
		int  m_eff_time3;
		int m_heal_time;
		RECT_F m_eff;		//エフェクト描画用
		RECT_F m_eff2;		//獅子攻撃エフェクト描画用
		RECT_F m_eff3;		//主人公死亡エフェクト描画用
		RECT_F m_ani_heal;

		bool m_heal_eff_f;//回復エフェクト描画フラグ

		bool m_libra_eff_f;	//天秤座スキルエフェクト用フラグ
		bool m_menu_key_f;	//メニューキー用の制御フラグ
		bool m_f;//攻撃制御用
		bool m_key_f;
		bool m_help_key_f;	//helpキー用の制御フラグ

		int m_time;//無敵時間カウント
		int m_MP_time;//ＭＰ減少カウント
		int m_regene_time;//ＭＰリジェネカウント
		int m_hp_regene_time;//HPリジェネカウント

		int m_burn_time;//火傷間隔タイム
		int m_burn_max_time;//火傷合計継続時間

		bool m_dash_flag;  //ダッシュフラグ
		bool m_cool_flag;  //ダッシュ制限用フラグ
		int m_cool_time;

		bool m_dash_eff_f;	//ダッシュエフェクト音のフラグ

		bool m_a_flag;//攻撃制御用

		bool m_se_f;//SE制御用

		bool m_burn_f;//火傷時主人公カラー変更用フラグ
		bool m_poison_f;//火傷時主人公カラー変更用フラグ
		//blockとの衝突状態確認用
		bool m_hit_up;
		bool m_hit_down;
		bool m_hit_left;
		bool m_hit_right;

		bool m_invincible_flag;//無敵フラグ

		bool m_eff_flag;

		bool dead_flag; //死亡フラグ
		
		int m_SE_on;
};


