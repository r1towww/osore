#pragma once
//使用するヘッダー
#include "GameL\DrawTexture.h"
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：敵機角度弾丸
class CObjRedBullet : public CObj
{
public:
	CObjRedBullet(float x, float y, float r, float speed);
	~CObjRedBullet() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
private:
	float m_x;	//オブジェクトの位置X
	float m_y;	//オブジェクトの位置Y
	float m_vx;	//オブジェクトの移動用ベクトルX
	float m_vy;	//オブジェクトの移動用ベクトルY
	float m_r;	//移動する角度
	float m_speed;	//速度
	float m_ani_max_time;	//アニメーション動作間隔最大値

	int m_ani_time; //アニメーションフレーム動作間隔
	int m_ani_frame;//描画フレーム
	int m_time;//削除までの時間測定
	bool	m_del;		//削除チェック
};
