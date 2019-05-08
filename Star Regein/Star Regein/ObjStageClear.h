#pragma once
//使用するヘッダー
#include"GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：タイトル
class CObjStageClear :public CObj
{
	public:
		CObjStageClear() {};
		~CObjStageClear() {};
		void Init();		//イニシャライズ
		void Action();		//アクション
		void Draw();		//ドロー
	private:
		float m_alpha1;
		float m_alpha2;
		float m_alpha3;
		float m_alpha4;


};