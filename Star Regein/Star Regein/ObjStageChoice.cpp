//使用するヘッダー
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\SceneManager.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "ObjStageChoice.h"

#define Earthx 300
#define Earthy 400

//使用するネームスペース
using namespace GameL;


//イニシャライズ
void CObjStageChoice::Init()
{

}

//アクション
void CObjStageChoice::Action()
{
	////主人公位置取得
	//CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	//float hx = hero->GetX();
	//float hy = hero->GetY();

	////指定の場所で
	//if (hx >= Earthx && hy <= Earthy)
	//{
	//	if (Input::GetVKey('Z') == true)
	//	{
	//		Scene::SetScene(new CSceneEarth());
	//	}
	//}

}

//ドロー
void CObjStageChoice::Draw()
{


}
