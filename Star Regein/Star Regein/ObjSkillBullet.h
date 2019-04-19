#pragma once
//使用するヘッダー
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;
//オブジェクト：ビームサーベル
class CObjSkillBullet : public CObj
{
public:
	CObjSkillBullet(float gx, float gy);
	~CObjSkillBullet() {};
	void Init();  //イニシャライズ
	void Action();//アクション
	void Draw();  //ドロー
private:

	float m_gx;		//位置
	float m_gy;

	float m_vx;
	float m_vy;

	float m_time;

	int m_pos_x;	//ヒットボックスの向き用変数
	int m_pos_y;
	int m_angle;	//ハート弾の角度用変数

	bool m_hit_flag;//着弾フラグ

	int m_ani_time; //アニメーションフレーム動作間隔
	int m_ani_frame;//描画フレーム

	int m_posture;//主人公の向きを代入する変数

	int	   m_ani;		//チャージアニメーション用
	RECT_F m_eff;		//チャージエフェクト描画用
	int m_ani_stop;

};