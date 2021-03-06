#pragma once
//使用するヘッダーファイル
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//定数
#define TAURUSMAXSTAR	18	//牡牛座の星の数

//シーン：メイン
class CSceneVenusTaurus :public CScene
{
	public:
		CSceneVenusTaurus();
		~CSceneVenusTaurus();
		void InitScene(); //初期化メソッド
		void Scene();     //実行中メソッド
		void ClearCheck(bool a);

private:
		bool m_clear_f;//一回処理専用
		float Item_cnt;

};

