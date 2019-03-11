#pragma once
//使用するヘッダーファイル
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;


//オブジェクト：ブロック＆背景
class CObjMiniMap : public CObj
{
	public:
		CObjMiniMap(int map[MAPSIZE][MAPSIZE]);
		~CObjMiniMap() {};
		void Init();		//イニシャライズ
		void Action();		//アクション
		void Draw();		//ドロー

	private:
		float m_blocksize,m_uisize_x, m_uisize_y;			//マップUIのサイズ
		float m_backsize;	//背景のサイズ
		float m_alpha;		//背景の透明度

		int m_f;//キー入力制御
		
};