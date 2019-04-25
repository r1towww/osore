#pragma once
//使用するヘッダーファイル
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//定数
#define EARTHMAXSTAR	5	//地球の星の数

//シーン：メイン
class CSceneEarth :public CScene
{
	public:
		CSceneEarth();
		~CSceneEarth();
		void InitScene(); //初期化メソッド
		void Scene();     //実行中メソッド
		void ClearCheck(bool a);
	private:

		int cnt;
};

