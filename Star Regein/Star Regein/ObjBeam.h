#pragma once
//使用するヘッダーファイル
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;


//オブジェクト：ブロック＆背景
class CObjBeam : public CObj
{
public:
	CObjBeam(float x, float y);
	~CObjBeam() {};
	void Init();		//イニシャライズ
	void Action();		//アクション
	void Draw();		//ドロー
	float* GetPX() { return &m_px; }
	float* GetPY() { return &m_py; }
	float GetX() { return m_px; }
	float GetY() { return m_py; }
private:

	float m_px;			//位置
	float m_py;

	//ビームアニメーション
	RECT_F m_beam_eff;		//エフェクト描画用
	int	 m_beam_ani;			//ワープアニメーション用
	int	 m_beam_ani_time;		//ワープアニメーション間隔タイム
	int m_beam_time;			//ワープ時間測定
	int m_time;					//アニメーション溜め用カウント
	bool m_beam_flag;

	bool m_d_beam_flag;

	RECT_F m_eff;		//チャージエフェクト描画用
	int	   m_ani;		//チャージアニメーション用
	int	   m_ani_time;	//チャージアニメーション間隔タイム
	bool m_ani_flag;	//trueでアニメーション動作、falseでアニメーション停止

};
