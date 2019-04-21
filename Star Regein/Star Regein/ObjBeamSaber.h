#pragma once
//使用するヘッダー
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：ビームサーベル
class CObjBeamSaber : public CObj
{
	public:
		CObjBeamSaber(float x,float y);
		~CObjBeamSaber() {};
		void Init();  //イニシャライズ
		void Action();//アクション
		void Draw();  //ドロー
	private:
		float m_x;
		float m_y;
		bool m_f;		//サウンド用フラグ
		int m_pos_x;	//ヒットボックスの向き用変数
		int m_pos_y;
		int m_angle;	//ビームサーベルの角度用変数

		int m_ani_time; //アニメーションフレーム動作間隔
		int m_ani_frame;//描画フレーム

};