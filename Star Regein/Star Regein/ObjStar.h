#pragma once
//使用するヘッダーファイル
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：ブロック＆背景
class CObjStar : public CObj
{
	public:
		CObjStar(float x, float y);
		~CObjStar() {};
		void Init();		//イニシャライズ
		void Action();		//アクション
		void Draw();		//ドロー

	private:
		float m_px;			//位置
		float m_py;

		bool m_GetStar;		//星を取得したかどうかの変数
};
