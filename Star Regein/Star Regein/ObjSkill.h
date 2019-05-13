#pragma once
//使用するヘッダーファイル
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;


//オブジェクト：スキル
class CObjSkill : public CObj
{
	public:
		CObjSkill() {};
		~CObjSkill() {};
		void Init();		//イニシャライズ
		void Action();		//アクション
		void Draw();		//ドロー

	private:
		int m_memory;	//スキル比較用変数
		int m_next;	//次のスキル用
		int m_back;	//前のスキル用

};