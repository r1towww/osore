#pragma once
//使用するヘッダーファイル
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//定数
#define LIBRAMAXSTAR	6	//天秤座の星の数

//シーン：メイン
class CSceneVenusLibra :public CScene
{
	public:
		CSceneVenusLibra();
		~CSceneVenusLibra();
		void InitScene(); //初期化メソッド
		void Scene();     //実行中メソッド
	private:

};

