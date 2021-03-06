#pragma once
//使用するヘッダーファイル
#include"GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：敵
class CObjBoss :public CObj
{
public:
	CObjBoss(float x, float y);
	~CObjBoss() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー

	float* GetPX() { return &m_px; }
	float* GetPY() { return &m_py; }

	float GetX() { return m_px; }
	float GetY() { return m_py; }
	float GetVY() { return m_vy; }
	float GetVX() { return m_vx; }

	void SetX(float x) { m_px = x; }
	void SetY(float y) { m_py = y; }
	void SetVY(float vy) { m_vy = vy; }
	void SetVX(float vx) { m_vx = vx; }


private:
	float m_px;		//位置
	float m_py;
	float m_vx;		//移動ベクトル
	float m_vy;
	float m_posture;//姿勢
	float m_alpha;

	//ワープアニメーション
	RECT_F m_warp_eff;		//エフェクト描画用
	int	 m_warp_ani;			//ワープアニメーション用
	int	 m_warp_ani_time;		//ワープアニメーション間隔タイム
	int m_warp_time;			//ワープ時間測定
	bool m_warp_flag;

	//死亡エフェクト
	RECT_F m_dead_eff;
	
	int m_dead_time;
	int m_dead_ani;
	bool m_dead_end;

	int m_ani_time;	//アニメーションフレーム動作間隔
	int m_ani_frame;//描画フレーム
	int m_hp;//体力

	int m_rand;
	int m_attack_pattern;

	int m_snake_c;
	int m_bullet_t;//弾幕用タイム

	int m_time;//無敵時間測定
	int m_key_f;//無敵時間行動制御
	int m_imposition_t;//攻撃発動時間調整用
	int m_ctime;
	int count;
	int e_time;//敵行動時間
	int enemy_move;//敵移動

	float m_speed_power;	//通常速度
	float m_ani_max_time;	//アニメーション動作間隔最大値

	//blockとの衝突状態確認用
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	bool m_invincible_flag;//無敵フラグ

	//移動用の向き制御用
	bool m_movex;//左右
	bool m_movey;//上下

	bool m_f;//無敵時間
	bool m_attack_f;
	bool m_attack_key_f;

	//攻撃パターンフラグ
	bool m_snake_f;
	bool m_poison_f;
	bool m_beam_f;

	bool m_do_f;//敵攻撃フラグ

	bool m_df;//ミニマップからの削除フラグ



};
