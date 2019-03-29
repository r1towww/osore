//使用するヘッダー
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\SceneManager.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "ObjStarChoice.h"

//使用するネームスペース
using namespace GameL;


//イニシャライズ
void CObjStarChoice::Init()
{
	//透明度の初期化
	m_Tra1 = 0.5f;
	m_Tra2 = 0.5f;
	m_Tra3 = 0.5f;
	
	//キー入力用タイムの初期化
	m_keytime = 0;

}

//アクション
void CObjStarChoice::Action()
{
	//惑星が選択され、星座選択画面への移行の際
	if (g_stage == Earth || g_stage == Venus || g_stage == Mercury || g_stage == Sun)
	{
		//画像が表示された際の、キー入力タイム処理
		if (m_keytime >= 50)
			m_keytime = 50;	//タイムが50になった際、50で止める
		else
			m_keytime++;	//キー入力タイムを増やす
	}
	else
	{
		m_keytime = 0;	//それ以外の場合、キー入力タイムを0にする
	}

	//星座選択が地球または太陽の場合（星座が1つの場合）
	if (g_stage == Earth || g_stage == Sun)
	{
		//上キーを入力して選択
		if (Input::GetVKey(VK_UP) == true)
		{
			m_direction = UP;	//UPをセット
		}
		//下キーを入力して選択
		if (Input::GetVKey(VK_DOWN) == true)
		{
			m_direction = DOWN;	//DOWNをセット
		}
	}
	else		//星座が2つある場合
	{	
		//下キーを入力して選択
		if (Input::GetVKey(VK_DOWN) == true)
		{
			m_direction = DOWN;	//DOWNをセット
		}
		//右キーを入力して選択
		if (Input::GetVKey(VK_RIGHT) == true)
		{
			m_direction = RIGHT;//RIGHTをセット
		}
		//左キーを入力して選択
		else if (Input::GetVKey(VK_LEFT) == true)
		{
			m_direction = LEFT;	//LEFTをセット
		}
	}

	//ステージ選択画面の情報を取得
	CObjStageChoice* stagec = (CObjStageChoice*)Objs::GetObj(OBJ_STAGECHOICE);
	
	//左のほうを明るくして右のほうを暗くする(1つしか無い際はUPをLEFTと同様に扱う)
	if (m_direction == LEFT || m_direction == UP)
	{
		//透過率変更
		m_Tra1 = 1.0f;
		m_Tra2 = 0.5f;
		m_Tra3 = 0.5f;
		//キー入力タイムが一定に達した場合、キー入力を許可する
		if (Input::GetVKey('Z') == true && m_keytime == TIMELIMIT)		
		{
			if (g_stage == Earth)
			{
				//ステージを地球に設定
				g_stage = EarthStar;
				Scene::SetScene(new CSceneEarth());
			}
			else if (g_stage == Venus)
			{
				//ステージをおうし座に設定
				g_stage = VenusTaurus;
				Scene::SetScene(new CSceneVenusTaurus());
			}
			else if (g_stage == Mercury)
			{
				//ステージを双子座に設定
				g_stage = MercuryGemini;
				Scene::SetScene(new CSceneVenusTaurus());
			}
		}
	}

	//右のほうのほうを明るくして左のほうを暗くする
	else if (m_direction == RIGHT)
	{
		//透過率変更
		m_Tra2 = 1.0f;
		m_Tra1 = 0.5f;
		m_Tra3 = 0.5f;
		//キー入力タイムが一定に達した場合、キー入力を許可する
		if (Input::GetVKey('Z') == true && m_keytime == TIMELIMIT)		
		{
			if (g_stage == Venus)
			{
				//ステージをてんびん座に設定
				g_stage = VenusLibra;
				Scene::SetScene(new CSceneVenusLibra());
			}
			else if (g_stage == Mercury)
			{
				//ステージを乙女座に設定
				g_stage = MercuryVirgo;
				Scene::SetScene(new CSceneEarth());
			}
		}
	}
	//下のコマンドの明るさを変更
	else if (m_direction == DOWN)		
	{
		//透過率変更
		m_Tra3 = 1.0f;
		m_Tra2 = 0.5f;
		m_Tra1 = 0.5f;
		//キー入力タイムが一定に達した場合、キー入力を許可する
		if (Input::GetVKey('Z') == true && m_keytime == TIMELIMIT)
		{
			g_stage = Space;	//ステージをSpaceに設定
			stagec->SetAlpha(ALPHAORIGIN);	//アルファ値を元に戻す
		}
	}
}

//ドロー
void CObjStarChoice::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };	//標準カラー
	//左の星座
	float left[4]  = { 1.0f,1.0f,1.0f,m_Tra1 };
	//右の星座
	float right[4] = { 1.0f,1.0f,1.0f,m_Tra2 };
	//下のコマンド
	float down[4]  = { 1.0f,1.0f,1.0f,m_Tra3 };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置
	
	//地球選択時に表示される画像
	if (g_stage == Earth)
	{
		//戻るコマンド表示
		Font::StrDraw(L"戻る", BACK_POSX, BACK_POSY, BACK_FONTSIZE, down);

		//地球選択用の画像
		//切り取り位置の設定
		src.m_top    = 0.0f;
		src.m_left   = 0.0f;
		src.m_right  = 256.0f;
		src.m_bottom = 256.0f;

		//表示位置の設定
		dst.m_top    = 150.0f;
		dst.m_left   = 300.0f;
		dst.m_right  = 510.0f;
		dst.m_bottom = 400.0f;
		//表示
		Draw::Draw(9, &src, &dst, left, 0.0f);
	}
	//金星選択時に表示される画像---------------------------------------------------------
	else if (g_stage == Venus)
	{
		//戻るコマンド表示
		Font::StrDraw(L"戻る", BACK_POSX, BACK_POSY, BACK_FONTSIZE, down);

		//おうし座の画像-----------------------------------------------------------------
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 870.0f;
		src.m_bottom = 600.0f;

		//表示位置の設定
		dst.m_top = 150.0f;
		dst.m_left = 100.0f;
		dst.m_right = 350.0f;
		dst.m_bottom = 400.0f;
		//表示
		Draw::Draw(7, &src, &dst, left, 0.0f);
		//-------------------------------------------------------------------------------
		//てんびん座---------------------------------------------------------------------
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 900.0f;
		src.m_bottom = 600.0f;

		//表示位置の設定
		dst.m_top = 150.0f;
		dst.m_left = 430.0f;
		dst.m_right = 680.0f;
		dst.m_bottom = 400.0f;
		//表示
		Draw::Draw(8, &src, &dst, right, 0.0f);
		//----------------------------------------------------------------------------------
	}
	//水星選択時に表示される画像---------------------------------------------------------
	else if (g_stage == Mercury)
	{
		//戻るコマンド表示
		Font::StrDraw(L"戻る", 380, 500, 25, down);

		//双子座の画像-----------------------------------------------------------------
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 870.0f;
		src.m_right = 1700.0f;
		src.m_bottom = 600.0f;

		//表示位置の設定
		dst.m_top = 150.0f;
		dst.m_left = 100.0f;
		dst.m_right = 350.0f;
		dst.m_bottom = 400.0f;
		//表示
		Draw::Draw(7, &src, &dst, left, 0.0f);
		//-------------------------------------------------------------------------------
		//乙女座---------------------------------------------------------------------
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 1700.0f;
		src.m_right = 2620.0f;
		src.m_bottom = 600.0f;

		//表示位置の設定
		dst.m_top = 150.0f;
		dst.m_left = 430.0f;
		dst.m_right = 680.0f;
		dst.m_bottom = 400.0f;
		//表示
		Draw::Draw(8, &src, &dst, right, 0.0f);
		//----------------------------------------------------------------------------------
	}
	else
	{

	}
	


}
