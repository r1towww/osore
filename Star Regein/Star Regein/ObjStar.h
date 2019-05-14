#pragma once
//使用するヘッダーファイル
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;


//オブジェクト：ブロック＆背景
class CObjStar : public CObj
{
	public:
		CObjStar(float x, float y, int i, int j,int id);
		~CObjStar() {};
		void Init();		//イニシャライズ
		void Action();		//アクション
		void Draw();		//ドロー
		float* GetPX() { return &m_px; }
		float* GetPY() { return &m_py; }
		float GetX() { return m_px; }
		float GetY() { return m_py; }
	private:
		int m_i;	//星の位置i番の変数
		int m_j;	//星の位置j番の変数

		float m_px;			//位置
		float m_py;
		int m_del;
		int	   m_ani;		//チャージアニメーション用
		int m_ani_time;	//アニメーションフレーム動作間隔
		int m_ani_frame;//描画フレーム

		RECT_F m_eff;		//チャージエフェクト描画用
		int m_ani_stop;
		bool m_ani_flag;	//trueでアニメーション動作、falseでアニメーション停止

		bool m_GetStar;		//星を取得したかどうかの変数
};
