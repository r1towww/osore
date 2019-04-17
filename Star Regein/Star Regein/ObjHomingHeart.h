#pragma once
//使用するヘッダーファイル
#include"GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：敵
class CObjHomingHeart :public CObj
{
public:
	CObjHomingHeart(float x, float y, float speed);
	~CObjHomingHeart() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー

private:
	float m_px;		//位置
	float m_py;
	float m_vx;		//移動ベクトル
	float m_vy;
	float m_speed;
	float alpha;

	int m_time;//存在時間測定

	

};