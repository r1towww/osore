#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：背景
class CObjFadein : public CObj
{
	public:
		CObjFadein() {};
		~CObjFadein() {};
		void Init();	//イニシャライズ
		void Action();	//アクション
		void Draw();	//ドロー

	private:
		int	m_ani_time;
		int m_ani_frame;

		float m_ani_max_time;	//アニメーション動作間隔最大値

		bool m_flag;			//切り替え用フラグ
		bool m_fade_flag;		//フェイドインの切り替え用フラグ
		bool m_next_flag;		//次の階層への移行用
		bool m_main_flag;		//タイトルからの移行用
		bool m_death_flag;		//ゲームオーバーシーンへの移行用
		bool m_clear_flag;		//ゲームクリアへの移行用
};
