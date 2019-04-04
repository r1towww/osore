#pragma once
//使用するヘッダー
#include"GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//星座位置関連定数----------
#define EarthX	  0
#define EarthY	  380
#define EarthX2	  100
#define EarthY2	  800
#define VenusX	  180
#define VenusX2	  320
#define VenusY	  300
#define VenusY2	  445
#define MercuryX  420
#define MercuryX2 570
#define MercuryY  120
#define MercuryY2 270
#define SunX	  615
#define SunX2	  800
#define SunY	  0
#define SunY2	  90

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