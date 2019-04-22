#pragma once
//使用するヘッダーファイル
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//定数
#define EARTHMAXSTAR	5	//地球の星の数
#define TAURUSMAXSTAR	18	//牡牛座の星の数
#define LIBRAMAXSTAR	6	//天秤座の星の数
#define GEMINIMAXSTAR	14	//双子座の星の数
#define VIRGOMAXSTAR	15	//乙女座の星の数
#define LEOMAXSTAR	14		//獅子座の星の数

//オブジェクト：
class CObjMessage :public CObj
{
	public:
		CObjMessage() {};
		~CObjMessage() {};
		void Init();	//イニシャライズ
		void Action();	//アクション
		void Draw();	//ドロー

	private:
		int m_memory;	//星の数の加算を計る変数
		int m_time;	//メッセージ表示時間

		int m_MaxStar;	//星の最大の数
};

