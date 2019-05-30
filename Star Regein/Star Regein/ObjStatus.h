#pragma once
//使用するヘッダーファイル
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

#define STATUS_PX 24.0f	//ステータス表示位置のX位置調整用
#define STATUS_PY 0.0f	//ステータス表示位置のY位置調整用
#define STATUS_BACK_PX 260.0f	//ステータス背景表示位置のX位置調整用
#define STATUS_BACK_PY 0.0f		//ステータス背景表示位置のY位置調整用

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
		float m_red;		//HP用カラー 赤
		float m_gleen;	//HP用カラー 緑
		float m_blue;		//HP用カラー 青


};