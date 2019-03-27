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

	private:
		int m_i;	//星の位置i番の変数
		int m_j;	//星の位置j番の変数

		float m_px;			//位置
		float m_py;

		bool m_GetStar;		//星を取得したかどうかの変数
};
