#pragma once
//使用するヘッダーファイル
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//描画関係の定数

#define GAME_CLEAR_X (225)
#define GAME_CLEAR_Y (150)
#define GAME_CLEAR_FONT_SIZE (30)

//オブジェクト：ブロック＆背景
class CObjED : public CObj
{
public:
	CObjED() {};
	~CObjED() {};
	void Init();		//イニシャライズ
	void Action();		//アクション
	void Draw();		//ドロー

private:
	int	m_ani_time;
	int m_ani_frame;
	int m_ani_max_time;	//アニメーション動作間隔最大値
	int m_key; //フォント描画
	bool m_key_f;//複数回押さないため
	bool flag;//アニメーションのフラグ
};