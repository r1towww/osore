//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"

#include "GameHead.h"
#include "ObjSkill.h"

//使用するネームスペース
using namespace GameL;

CObjSkill::CObjSkill()
{

}

//イニシャライズ
void CObjSkill::Init()
{

}

//アクション
void CObjSkill::Action()
{
	//選択スキルがNoSkillになった場合
	if (g_skill == NoSkill)
	{
		g_skill = Taurus;	//牡牛座をセット
	}
}

//ドロー
void CObjSkill::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

	//切り取り位置の設定
	src.m_top    = 0.0f;
	src.m_left   = (256.0f * g_skill) ;
	src.m_right  = 256.0f + (256.0f * g_skill);	//スキルの情報を入れ、画像を切り替える
	src.m_bottom = 256.0f;

	//表示位置の設定
	dst.m_top    = 400.0f;
	dst.m_left   = 600.0f;
	dst.m_right  = 800.0f;
	dst.m_bottom = 600.0f;

	//描画
	Draw::Draw(13, &src, &dst, c, 0.0f);
}