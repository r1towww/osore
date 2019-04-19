#pragma once
//使用するヘッダーファイル
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;


//オブジェクト：ブロック＆背景
class CObjSkillLeo : public CObj
{
public:
	CObjSkillLeo(int x, int y);
	~CObjSkillLeo() {};
	void Init();		//イニシャライズ
	void Action();		//アクション
	void Draw();		//ドロー

private:
	int m_x;		//位置
	int m_y;

	float m_time; //時間カウント


};
