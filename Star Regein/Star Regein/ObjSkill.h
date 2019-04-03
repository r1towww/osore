#pragma once
//使用するヘッダーファイル
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;


//オブジェクト：ブロック＆背景
class CObjSkill : public CObj
{
	public:
		CObjSkill() {};
		~CObjSkill() {};
		void Init();		//イニシャライズ
		void Action();		//アクション
		void Draw();		//ドロー

	private:
};