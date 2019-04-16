#pragma once
//使用するヘッダー
#include"GameL\DrawTexture.h"
#include"GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：チャージエフェクト
class CObjStarEffect : public CObj
{
public:
	CObjStarEffect(float x, float y, int i, int j);
	~CObjStarEffect() {};
	void Init();		//イニシャライズ
	void Action();		//アクション
	void Draw();		//ドロー
	void Set(bool f);
private:
	float m_x;			//オブジェクトの位置Ｘ
	float m_y;			//オブジェクトの位置Ｙ
	int m_i;	//星の位置i番の変数
	int m_j;	//星の位置j番の変数

	float m_px;			//位置
	float m_py;

	int m_del;
	int	   m_ani;		//チャージアニメーション用
	int	   m_ani_time;	//チャージアニメーション間隔タイム
	RECT_F m_eff;		//チャージエフェクト描画用

	bool m_ani_flag;	//trueでアニメーション動作、falseでアニメーション停止
};