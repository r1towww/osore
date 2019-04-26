#pragma once
//使用するヘッダー
#include"GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//定数
#define UP		0
#define DOWN	1
#define RIGHT	2
#define LEFT	3

#define BACK_POSX 380
#define BACK_POSY 500
#define BACK_FONTSIZE 25

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
		float m_Tra4;
		bool m_key_flag;	//キー制御フラグ
};