#pragma once
#pragma once
//使用するヘッダーファイル
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;


//オブジェクト：ブロック＆背景
class CObjSkillGeminiB : public CObj
{
public:
	CObjSkillGeminiB(float x, float y);
	~CObjSkillGeminiB() {};
	void Init();		//イニシャライズ
	void Action();		//アクション
	void Draw();		//ドロー

	float GetX() { return m_gx; }
	float GetY() { return m_gy; }
	float GetVY() { return m_vy; }
	float GetVX() { return m_vx; }

private:
	float m_gx;		//位置
	float m_gy;
	float m_vx;		//移動ベクトル
	float m_vy;
	float m_posture;//姿勢
	float alpha;
	float m_ani_max_time;	//アニメーション動作間隔最大値
	float m_angle;	//角度調整
	float m_pos_x;	//X軸調整
	float m_pos_y;	//Y軸調整


	int m_ani_time;	//アニメーションフレーム動作間隔
	int m_ani_frame;//描画フレーム

	int m_blackhole_num;	//惑星ごとのブラックホールの数の値を入れる
	int m_time;//双子座スキル消滅時間測定
	int m_bullet_time;//弾丸発射時間測定

					  //blockとの衝突状態確認用
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	//移動用の向き制御用
	bool m_movex;//左右
	bool m_movey;//上下
};