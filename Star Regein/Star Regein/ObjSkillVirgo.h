#pragma once
//使用するヘッダー
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：ビームサーベル
class CObjSkillVirgo : public CObj
{
public:
	CObjSkillVirgo(float x,float y);
	~CObjSkillVirgo() {};
	void Init();  //イニシャライズ
	void Action();//アクション
	void Draw();  //ドロー
private:

	float m_gx;		//位置
	float m_gy;

	float m_x;
	float m_y;
	float m_vx;
	float m_vy;

	float m_time;

	float m_pos_x;	//ヒットボックスの向き用変数
	float m_pos_y;
	float m_angle;	//ハート弾の角度用変数
	bool m_f;		//エフェクト音用フラグ
	bool m_bullet_f;//着弾用フラグ
	bool m_hit_flag;//着弾フラグ
	bool m_flag;	//1回だけ発動するように処理する
	int m_ani_time; //アニメーションフレーム動作間隔
	int m_ani_frame;//描画フレーム

	float m_posture;//主人公の向きを代入する変数

	int	   m_ani;		//チャージアニメーション用
	RECT_F m_eff;		//チャージエフェクト描画用
	int m_ani_stop;

};