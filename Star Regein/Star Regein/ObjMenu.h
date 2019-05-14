#pragma once
//使用するヘッダーファイル
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：
class CObjMenu :public CObj
{
	public:
		CObjMenu() {};
		~CObjMenu() {};
		void Init();	//イニシャライズ
		void Action();	//アクション
		void Draw();	//ドロー

	private:
		int m_key;	//キー入力用
		bool m_key_f;	//キー入力制御フラグ
		bool m_choice_key_f;	//選択用のキーフラグ
		bool m_push_flag;
		float m_Tra;

};

