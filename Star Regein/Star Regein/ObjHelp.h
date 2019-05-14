#pragma once
//使用するヘッダーファイル
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：
class CObjHelp :public CObj
{
	public:
		CObjHelp() {};
		~CObjHelp() {};
		void Init();	//イニシャライズ
		void Action();	//アクション
		void Draw();	//ドロー

	private:
		bool  m_f;//キー入力制御用フラグ
};

