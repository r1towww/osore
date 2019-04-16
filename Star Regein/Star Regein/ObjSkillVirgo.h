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
	float m_x;
	float m_y;
	float m_vx;
	float m_vy;

	int m_pos_x;	//ヒットボックスの向き用変数
	int m_pos_y;
	int m_angle;	//ハート弾の角度用変数



};