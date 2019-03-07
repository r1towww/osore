#pragma once
//使用するヘッダーファイル
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//定数
#define MAPSIZE 29

//オブジェクト：ブロック＆背景
class CObjMiniMap : public CObj
{
	public:
		CObjMiniMap(int map[MAPSIZE][MAPSIZE]);
		~CObjMiniMap() {};
		void Init();		//イニシャライズ
		void Action();		//アクション
		void Draw();		//ドロー

		int Getmap() { return m_map[MAPSIZE][MAPSIZE]; }

		//左右スクロール用
		void SetScrollx(float s) { m_scrollx = s; }
		float GetScrollx() { return m_scrollx; }
		//上下スクロール用
		void SetScrolly(float s) { m_scrolly = s; }
		float GetScrolly() { return m_scrolly; }

	private:
		int m_map[MAPSIZE][MAPSIZE];	//マップ情報

		float m_scrollx;		//左右スクロール用
		float m_scrolly;		//上下スクロール用

		int m_f;//主人公消滅時のエラー回避用

};