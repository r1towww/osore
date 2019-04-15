#pragma once
//使用するヘッダーファイル
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;


//オブジェクト：ブロック＆背景
class CObjSkillGemini : public CObj
{
public:
	CObjSkillGemini() {};
	~CObjSkillGemini() {};
	void Init();		//イニシャライズ
	void Action();		//アクション
	void Draw();		//ドロー

private:
	int m_ani_time; //アニメーションフレーム動作間隔
	int m_ani_frame;//描画フレーム
	float m_x;
	float m_y;
	float m_vx;
	float m_vy;
	
};