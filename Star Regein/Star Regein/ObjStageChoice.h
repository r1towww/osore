#pragma once
//使用するヘッダー
#include"GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//星座位置関連定数----------
#define EarthX	  5
#define EarthX2	  185
#define EarthY	  370
#define EarthY2	  560
#define VenusX	  210
#define VenusX2	  410
#define VenusY	  240
#define VenusY2	  460
#define MercuryX  400
#define MercuryX2 570
#define MercuryY  140
#define MercuryY2 310
#define SunX	  550
#define SunX2	  900
#define SunY	  -100
#define SunY2	  200

#define ALPHAORIGIN	1.0f
#define ALPHAUNDER 0.3f

//オブジェクト：タイトル
class CObjStageChoice :public CObj
{
	public:
		CObjStageChoice() {};
		~CObjStageChoice() {};
		void Init();		//イニシャライズ
		void Action();		//アクション
		void Draw();		//ドロー

		void SetAlpha(float a) { m_alpha = a; }	//アルファ値をセットする関数

	private:
		float m_alpha;	//背景透明度
};