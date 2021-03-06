#pragma once
//使用するヘッダー
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：ビームサーベル
class CObjHomingHeart : public CObj
{
public:
	CObjHomingHeart(float x, float y);
	~CObjHomingHeart() {};
	void Init();  //イニシャライズ
	void Action();//アクション
	void Draw();  //ドロー
private:
	float m_x;
	float m_y;
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