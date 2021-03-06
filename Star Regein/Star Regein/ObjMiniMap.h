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

		int GetID() { return count; } //牛の識別番号

	private:
		float m_blocksize,m_uisize_x, m_uisize_y;			//マップUIのサイズ
		float m_backsize;	//背景のサイズ
		float m_smallsize,m_bigsize;	//描画サイズ用の変数

		bool m_hint_f;		//ヒント表示用フラグ

		bool m_f;//キー入力制御

		int count;
		
};