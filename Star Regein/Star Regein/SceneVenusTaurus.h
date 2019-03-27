#pragma once
//使用するヘッダーファイル
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//シーン：メイン
class CSceneVenusTaurus :public CScene
{
	public:
		CSceneVenusTaurus();
		~CSceneVenusTaurus();
		void InitScene(); //初期化メソッド
		void Scene();     //実行中メソッド
	private:

};

