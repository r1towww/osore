#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//-------定数------------------------

//アニメーション用
#define ANITIME 1

//ダッシュ速度
#define DASH_SPEED 5.0
//通常速度
#define NORMAL_SPEED 3.0

//-------------------------------------
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
	void SetX(float x) { m_px = x; }
	void SetY(float y) { m_py = y; }
	void SetVY(float vy) { m_vy = vy; }
	void SetVX(float vx) { m_vx = vx; }

private:
	float m_px;  //位置
	float m_py;
	float m_vx;  //移動ベクトル
	float m_vy;
	float m_posture; //姿勢

	float m_speed_power; //スピードパワー

	int m_ani_time; //アニメーションフレーム動作間隔
	int m_ani_frame;//描画フレーム

	int m_f;//攻撃制御用

	int m_time;

	//blockとの衝突状態確認用
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	//踏んでいるblockの種類を確認用
	int m_block_type;

};


