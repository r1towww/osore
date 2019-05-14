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
	int m_y;
};