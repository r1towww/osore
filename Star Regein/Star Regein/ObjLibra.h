#pragma once
//使用するヘッダーファイル
#include"GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：敵
class CObjLibra :public CObj
{
public:
	CObjLibra(float x, float y, int id);
	~CObjLibra() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー

	float* GetPX() { return &m_px; }
	float* GetPY() { return &m_py; }

	float GetX() { return m_px; }
	float GetY() { return m_py; }
	float GetVY() { return m_vy; }
	float GetVX() { return m_vx; }

	//int GetID() { return count; } //牛の識別番号

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

	int m_ani_time;	//アニメーションフレーム動作間隔
	int m_ani_frame;//描画フレーム
	int m_hp;//体力

	int m_libra_id;

	int m_ani_timeB;
	int m_time;//無敵時間測定
	int m_key_f;//無敵時間行動制御
	int count;
	int m_e_time;//敵行動時間

	float m_speed_power;	//通常速度
	float m_ani_max_time;	//アニメーション動作間隔最大値

	bool m_invincible_flag;//無敵フラグ

	bool m_f;//無敵時間

	bool m_move_f;

	//blockとの衝突状態確認用
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;
	//移動用の向き制御用

	int	   m_ani;		//チャージアニメーション用
	RECT_F m_eff;		//チャージエフェクト描画用
	int m_ani_stop;

	bool m_movex;//左右
	bool m_movey;//上下

	bool m_move;//移動フラグ

	bool m_do_f;//敵攻撃フラグ

	bool m_df;//ミニマップからの削除フラグ

	bool m_libra_delete; //天秤削除フラグ
    //死亡エフェクト
	RECT_F m_dead_eff;
	bool dead_flag;
	int m_dead_time;
	int m_dead_ani;

	bool m_kill_f;	//キルカウント用フラグ


};