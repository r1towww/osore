#pragma once
//使用するヘッダーファイル
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

/*		Skill列挙型
	Taurus,		//牡牛座		0
	Libra,		//天秤座		1
	Gemini,		//双子座		2
	Virgo,		//乙女座		3
	Leo,		//獅子座		4
	NoSkill,	//スキル無し	5
	* スキルを変更する際値を変える *
*/


//オブジェクト：ブロック＆背景
class CObjSkill : public CObj
{
	public:
		CObjSkill();
		~CObjSkill() {};
		void Init();		//イニシャライズ
		void Action();		//アクション
		void Draw();		//ドロー

	private:
};