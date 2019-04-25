#pragma once
//使用するヘッダーファイル
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//シーン：メイン
class CSceneMercuryVirgo :public CScene
{
	public:
		CSceneMercuryVirgo();
		~CSceneMercuryVirgo();
		void InitScene(); //初期化メソッド
		void Scene();     //実行中メソッド
		void ClearCheck(bool a);

	private:
		float Item_cnt;
		bool m_clear_f;

};

