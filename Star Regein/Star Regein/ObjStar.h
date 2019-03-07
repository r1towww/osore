#pragma once
//使用するヘッダーファイル
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：ブロック＆背景
class CObjStar : public CObj
{
	public:
		CObjStar(float x, float y, int i, int j);
		~CObjStar() {};
		void Init();		//イニシャライズ
		void Action();		//アクション
		void Draw();		//ドロー

		int GetI() { return m_i; }	//星の位置iを取得
		int GetJ() { return m_j; }	//星の位置jを取得
		bool GetF() { return m_f; }	//星に触れたかどうかのフラグを取得

		void SetF(bool f) { m_f = f; }	//星に触れたかどうかのフラグをセット

	private:
		int m_i;	//星の位置i番の変数
		int m_j;	//星の位置j番の変数
		bool m_f;	//星に触れたかどうかの変数

		float m_px;			//位置
		float m_py;

		bool m_GetStar;		//星を取得したかどうかの変数
};
