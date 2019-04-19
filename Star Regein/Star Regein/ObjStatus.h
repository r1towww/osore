#pragma once
//使用するヘッダーファイル
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;


//オブジェクト：ブロック＆背景
class CObjStatus : public CObj
{
	public:
		CObjStatus();
		~CObjStatus() {};
		void Init();		//イニシャライズ
		void Action();		//アクション
		void Draw();		//ドロー

	private:
		int m_red;		//HP用カラー 赤
		int m_gleen;	//HP用カラー 緑
		int m_blue;		//HP用カラー 青

};