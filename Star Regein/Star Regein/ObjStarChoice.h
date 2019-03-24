#pragma once
//使用するヘッダー
#include"GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//定数
#define DOWN	0
#define RIGHT	1
#define LEFT	2

//オブジェクト：タイトル
class CObjStarChoice :public CObj
{
	public:
		CObjStarChoice() {};
		~CObjStarChoice() {};
		void Init();		//イニシャライズ
		void Action();		//アクション
		void Draw();		//ドロー
	private:
		int m_direction;	//星座選択用変数
		float m_Tra1;//透過率
		float m_Tra2;//透過率
		float m_Tra3;//透過率

		int m_keytime;	//キー入力ができるまでの時間
};