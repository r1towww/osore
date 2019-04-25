#pragma once
//使用するヘッダーファイル
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;


//オブジェクト：ブロック＆背景
class CObjSkillItem : public CObj
{
public:
	CObjSkillItem(float x,float y) ;
	~CObjSkillItem() {};
	void Init();		//イニシャライズ
	void Action();		//アクション
	void Draw();		//ドロー

private:
	float m_x; //スキルアイテム座標
	float m_y;

	float m_vx;//移動量
	float m_vy;
};
