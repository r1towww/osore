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

		void Setdcow(int t);

		int GetID() { return count; } //牛の識別番号

	private:
		float m_blocksize,m_uisize_x, m_uisize_y;			//マップUIのサイズ
		float m_backsize;	//背景のサイズ
		float m_alpha;		//背景の透明度
		float m_smallsize,m_bigsize;	//描画サイズ用の変数

		int c;

		int m_f;//キー入力制御

		int count;

		bool m_d_cow_f[20];//牛削除フラグ
		bool m_d_twinsb_f[10];//双子（青）フラグ
		bool m_d_twinsr_f[10];//双子（赤）フラグ
		
};