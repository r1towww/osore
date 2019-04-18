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
	m_Tra1 = 0.3f;
	m_Tra2 = 0.3f;
	m_Tra3 = 0.3f;
	m_direction = DOWN;	//初期選択位置の初期化

	//キー入力用タイムの初期化
	m_keytime = 0;
}

//アクション
void CObjStarChoice::Action()
{
	//ステージ選択画面の情報を取得
	CObjStageChoice* stagec = (CObjStageChoice*)Objs::GetObj(OBJ_STAGECHOICE);
	ObjStageChoiceHero* stageh = (ObjStageChoiceHero*)Objs::GetObj(OBJ_STAGECHOICEHERO);

	//惑星が選択され、星座選択画面への移行の際
	if (g_stage == Earth || g_stage == Venus || g_stage == Mercury || g_stage == Sun)
	{
		stagec->SetAlpha(ALPHAUNDER);	//アルファ値の変更
		stageh->SetAlpha(ALPHAUNDER);
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
		else if (Input::GetVKey(VK_DOWN) == true)
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
		else if (Input::GetVKey(VK_RIGHT) == true)
		{
			m_direction = RIGHT;//RIGHTをセット
		}
		//左キーを入力して選択
		else if (Input::GetVKey(VK_LEFT) == true)
		{
			m_direction = LEFT;	//LEFTをセット
		}
	}

	//左のほうを明るくして右のほうを暗くする(1つしか無い際はUPをLEFTと同様に扱う)
	//左を選択している際
	if (m_direction == LEFT || m_direction == UP)
	{
		//透過率変更
		m_Tra1 = 1.0f;
		m_Tra2 = 0.3f;
		m_Tra3 = 0.3f;
		//キー入力タイムが一定に達した場合、キー入力を許可する
		if (Input::GetVKey('Z') == true && g_key_flag == true)		
		{
			if (g_stage == Earth)
			{
				//ステージを地球に設定
				g_stage = EarthStar;
				Scene::SetScene(new CSceneEarth());
			}
			else if (g_stage == Venus)
			{
				//ステージを牡牛座に設定
				g_stage = VenusTaurus;
				Scene::SetScene(new CSceneVenusTaurus());
			}
			else if (g_stage == Mercury)
			{
				//ステージを双子座に設定
				g_stage = MercuryGemini;
				Scene::SetScene(new CSceneMercuryGemini());
			}
		}
	}

	//右のほうのほうを明るくして左のほうを暗くする
	//右を選択している際
	else if (m_direction == RIGHT)
	{
		//透過率変更
		m_Tra2 = 1.0f;
		m_Tra1 = 0.3f;
		m_Tra3 = 0.3f;
		//キー入力タイムが一定に達した場合、キー入力を許可する
		if (Input::GetVKey('Z') == true && g_key_flag == true)
		{
			if (g_stage == Venus)
			{
				//ステージを天秤座に設定
				g_stage = VenusLibra;
				Scene::SetScene(new CSceneVenusLibra());
			}
			else if (g_stage == Mercury)
			{
				//ステージを乙女座に設定
				g_stage = MercuryVirgo;
				Scene::SetScene(new CSceneMercuryVirgo());
			}
		}
	}
	//下のコマンドの明るさを変更
	//下（戻る）を選択している際
	else if (m_direction == DOWN)		
	{
		//透過率変更
		m_Tra3 = 1.0f;
		m_Tra2 = 0.3f;
		m_Tra1 = 0.3f;
		//キー入力タイムが一定に達した場合、キー入力を許可する
		if (Input::GetVKey('Z') == true && g_key_flag == true)
		{
			g_stage = Space;	//ステージをSpaceに設定
			stagec->SetAlpha(ALPHAORIGIN);	//アルファ値を元に戻す
			stageh->SetAlpha(ALPHAORIGIN);
			g_key_flag = false;	//キーフラグをオフ
			this->SetStatus(false);    //自身に削除命令を出す
		}
	}
	//キー入力を長押しで出来ないようにする
	if (Input::GetVKey('Z') == false)
	{
		g_key_flag = true;	//離したらオンにする
	}
}

//ドロー
void CObjStarChoice::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,m_Tra1 };	//標準カラー
	//クリア用
	float left_clear[4] = { 1.0f,1.0f,0.0f,m_Tra1 };
	float right_clear[4] = { 1.0f,1.0f,0.0f,m_Tra2 };

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
		src.m_right  = 300.0f;
		src.m_bottom = 200.0f;

		//表示位置の設定
		dst.m_top    = 190.0f;
		dst.m_left   = 250.0f;
		dst.m_right  = 550.0f;
		dst.m_bottom = 390.0f;
		//表示
		Draw::Draw(7, &src, &dst, left, 0.0f);
		if (g_Earth_clear == true)
		{
			Font::StrDraw(L"CLEAR!", 350, 400, 40, c);
		}
	}
	//金星選択時に表示される画像---------------------------------------------------------
	else if (g_stage == Venus)
	{
		//戻るコマンド表示
		Font::StrDraw(L"戻る", BACK_POSX, BACK_POSY, BACK_FONTSIZE, down);

		//おうし座の画像-----------------------------------------------------------------
		//切り取り位置の設定
		src.m_top    = 0.0f;
		src.m_left   = 300.0f;
		src.m_right  = 600.0f;
		src.m_bottom = 200.0f;

		//表示位置の設定
		dst.m_top    = 190.0f;
		dst.m_left   = 80.0f;
		dst.m_right  = 380.0f;
		dst.m_bottom = 390.0f;
		//表示
		Draw::Draw(7, &src, &dst, left, 0.0f);
		//おうし座クリアでクリア表記
		if (g_Taurus_clear == true)
		{
			Font::StrDraw(L"CLEAR!", 200, 400, 40, left_clear);
		}
		//-------------------------------------------------------------------------------
		//天秤座---------------------------------------------------------------------
		//切り取り位置の設定
		src.m_top    = 0.0f;
		src.m_left   = 600.0f;
		src.m_right  = 900.0f;
		src.m_bottom = 200.0f;

		//表示位置の設定
		dst.m_top    = 190.0f;
		dst.m_left   = 400.0f;
		dst.m_right  = 700.0f;
		dst.m_bottom = 390.0f;
		//表示
		Draw::Draw(7, &src, &dst, right, 0.0f);
		//てんびん座クリアでクリア表記
		if (g_Libra_clear== true)
		{
			Font::StrDraw(L"CLEAR!", 450, 400, 40, right_clear);
		}

		//----------------------------------------------------------------------------------

	}
	//水星選択時に表示される画像---------------------------------------------------------
	else if (g_stage == Mercury)
	{
		//戻るコマンド表示
		Font::StrDraw(L"戻る", 380, 500, 25, down);

		//双子座の画像-----------------------------------------------------------------
		//切り取り位置の設定
		src.m_top    = 0.0f;
		src.m_left   = 900.0f;
		src.m_right  = 1200.0f;
		src.m_bottom = 200.0f;

		//表示位置の設定
		dst.m_top    = 190.0f;
		dst.m_left   = 90.0f;
		dst.m_right  = 390.0f;
		dst.m_bottom = 390.0f;
		//表示
		Draw::Draw(7, &src, &dst, left, 0.0f);
		//双子座クリアでクリア表記
		if (g_Gemini_clear == true)
		{
			Font::StrDraw(L"CLEAR!", 180, 400, 40, left_clear);
		}

		//-------------------------------------------------------------------------------
		//乙女座---------------------------------------------------------------------
		//切り取り位置の設定
		src.m_top    = 0.0f;
		src.m_left   = 1200.0f;
		src.m_right  = 1500.0f;
		src.m_bottom = 200.0f;

		//表示位置の設定
		dst.m_top    = 190.0f;
		dst.m_left   = 420.0f;
		dst.m_right  = 720.0f;
		dst.m_bottom = 390.0f;
		//表示
		Draw::Draw(7, &src, &dst, right, 0.0f);
		//おとめ座クリアでクリア表記
		if (g_Virgo_clear == true)
		{
			Font::StrDraw(L"CLEAR!", 450, 400, 40, right_clear);
		}

		//----------------------------------------------------------------------------------
	}
	else
	{

	}
	


}
