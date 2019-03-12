//使用するヘッダー
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\SceneManager.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "ObjStageChoice.h"

#define Earthx 0
#define Earthy 380
#define Earthxx 100
#define Earthyy 800

//使用するネームスペース
using namespace GameL;


//イニシャライズ
void CObjStageChoice::Init()
{
	m_key_flag = true;
}

//アクション
void CObjStageChoice::Action()
{
	//主人公位置取得
	ObjStageChoiceHero* hero = (ObjStageChoiceHero*)Objs::GetObj(OBJ_STAGECHOICEHERO);
	float hx = hero->GetX();
	float hy = hero->GetY();

	//指定の場所でZキー
	if (hx >= Earthx && hx<=Earthxx && hy >= Earthy&&hy<=Earthyy)
	{
		//▼前シーンからZキー押し続けでこれを押さないように、
		//このシーンに入って一度も押してない状態に移行しないと
		//実行出来ないようにしている。
		if (Input::GetVKey('Z') == true&&m_key_flag==false)
		{
			Scene::SetScene(new CSceneEarth());
		}

	}
	else
	{
		m_key_flag = false;
	}

}

//ドロー
void CObjStageChoice::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

				//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1920.0f;
	src.m_bottom = 1080.0f;

	//表示位置の設定
	dst.m_top = 0.0f ;
	dst.m_left = 0.0f ;
	dst.m_right = 800.0f ;
	dst.m_bottom = 600.0f ;

	//表示
	Draw::Draw(2, &src, &dst, c, 0.0f);


}
