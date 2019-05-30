#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//-------定数------------------------

//ダッシュ速度
#define STAGE_DASH_SPEED 5.0
//通常速度
#define STAGE_NORMAL_SPEED 3.0

//-------------------------------------
//オブジェクト:主人公
class ObjStageChoiceHero :public CObj
{
	public:
		ObjStageChoiceHero(float x, float y);
		~ObjStageChoiceHero() {};
		void Init();    //イニシャライズ
		void Action();  //アクション
		void Draw();    //ドロー
	
		void SetAlpha(float a) { m_alpha = a; }	//アルファ値をセットする関数

	private:
		float m_vx;  //移動ベクトル
		float m_vy;
		//float g_posture; //姿勢

		float m_speed_power; //スピードパワー

		float m_alpha;
		bool m_time;
		int m_ani_time; //アニメーションフレーム動作間隔
		int m_ani_frame;//描画フレーム

		bool m_f;//攻撃制御用

		bool m_key_flag;	//キー入力制御フラグ
		bool m_stage_start;
		float m_Tra;
		
};


