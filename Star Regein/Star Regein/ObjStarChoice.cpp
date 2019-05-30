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
	m_Tra4 = 0.0f;
	m_Tra5 = 0.0f;
	if(g_stage == Earth || g_stage == Sun)
		m_direction = UP;	//初期選択位置の初期化
	else if (g_stage == Venus || g_stage == Mercury)
		m_direction = LEFT;


	m_push_flag = false;
	//キー入力用フラグの初期化
	m_key_flag = true;
}

//アクション
void CObjStarChoice::Action()
{
	float c[4] = { 1.0f,1.0f,0.0f,1.0f };	//標準カラー

	//ステージ選択画面の情報を取得
	CObjStageChoice* stagec = (CObjStageChoice*)Objs::GetObj(OBJ_STAGECHOICE);
	ObjStageChoiceHero* stageh = (ObjStageChoiceHero*)Objs::GetObj(OBJ_STAGECHOICEHERO);

	//惑星が選択され、星座選択画面への移行の際
	if (g_stage == Earth || g_stage == Venus || g_stage == Mercury || g_stage == Sun)
	{
			stagec->SetAlpha(ALPHAUNDER);	//アルファ値の変更
	}

	

	//星座選択が地球または太陽の場合（星座が1つの場合）
	if (g_stage == Earth || g_stage == Sun)
	{
		//上キーを入力して選択
		if (Input::GetVKey(VK_UP) == true)
		{
			if (m_key_flag == true)
			{
				Audio::Start(1);
				m_direction = UP;	//UPをセット
				m_key_flag = false;

			}
		}
		//下キーを入力して選択
		else if (Input::GetVKey(VK_DOWN) == true)
		{
			if (m_key_flag == true)
			{
				Audio::Start(1);
				m_direction = DOWN;	//DOWNをセット
				m_key_flag = false;
			}
		}
		else
			m_key_flag = true;
	}
	else if(g_stage == Venus || g_stage == Mercury)		//星座が2つある場合
	{	
		//下キーを入力して選択
		if (Input::GetVKey(VK_DOWN) == true)
		{
			if (m_key_flag == true)
			{
				Audio::Start(1);
				m_direction = DOWN;	//DOWNをセット
				m_key_flag = false;
			}
		}
		//右キーを入力して選択
		else if (Input::GetVKey(VK_RIGHT) == true)
		{
			if (m_key_flag == true)
			{
				Audio::Start(1);
				m_direction = RIGHT;//RIGHTをセット
				m_key_flag = false;
			}
		}
		//左キーを入力して選択
		else if (Input::GetVKey(VK_LEFT) == true)
		{
			if (m_key_flag == true)
			{
				Audio::Start(1);
				m_direction = LEFT;	//LEFTをセット
				m_key_flag = false;
			}
		}
		else
			m_key_flag = true;
	}

	//左のほうを明るくして右のほうを暗くする(1つしか無い際はUPをLEFTと同様に扱う)
	//左を選択している際
	if (m_direction == LEFT || m_direction == UP)
	{
		//透過率変更
		m_Tra1 = 1.0f;
		m_Tra2 = 0.3f;
		m_Tra3 = 0.3f;
		m_Tra4 = 1.0f;
		//キー入力タイムが一定に達した場合、キー入力を許可する
		if (Input::GetVKey('Z') == true && g_key_flag == true || Input::GetVKey(VK_RETURN) == true && g_key_flag == true)
		{
			if (g_stage == Earth)
			{
				if (m_key_flag == true)
				{
					m_key_flag = false;
					//シーン遷移音
					Audio::Start(2);
					Sleep(500);
					//ステージを地球に設定
					g_stage = EarthStar;
					m_push_flag = true;
				}
			}
			else if (g_stage == Venus)
			{
				if (m_key_flag == true)
				{
					m_key_flag = false;
					//シーン遷移音
					Audio::Start(2);
					Sleep(500);
					//ステージを牡牛座に設定
					g_stage = VenusTaurus;
					m_push_flag = true;
				}
			}
			else if (g_stage == Mercury)
			{
				if (m_key_flag == true)
				{
					m_key_flag = false;
					//シーン遷移音
					Audio::Start(2);
					Sleep(500);
					//ステージを双子座に設定
					g_stage = MercuryGemini;
					m_push_flag = true;
				}
			}
			else if (g_stage == Sun)
			{
				if (m_key_flag == true)
				{
					m_key_flag = false;
					//シーン遷移音
					Audio::Start(2);
					Sleep(500);
					//ステージを双子座に設定
					g_stage = SunLeo;
					m_push_flag = true;
				}
			}
			else
				m_key_flag = true;
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
		m_Tra4 = 1.0f;
		//キー入力タイムが一定に達した場合、キー入力を許可する
		if ((Input::GetVKey('Z') == true && g_key_flag == true || Input::GetVKey(VK_RETURN) == true) && g_key_flag == true)
		{
			if (g_stage == Venus)
			{
				if (m_key_flag == true)
				{
					m_key_flag = false;
					//シーン遷移音
					Audio::Start(2);
					Sleep(500);
					//ステージを天秤座に設定
					g_stage = VenusLibra;
					m_push_flag = true;
				}
			}
			else if (g_stage == Mercury)
			{
				if (m_key_flag == true)
				{
					m_key_flag = false;
					//シーン遷移音
					Audio::Start(2);
					Sleep(500);
					//ステージを乙女座に設定
					g_stage = MercuryVirgo;
					m_push_flag = true;
				}
			}
			else
				m_key_flag = true;
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
		m_Tra4 = 0.0f;
		//キー入力フラグがオンの場合、入力を許可する
		if ((Input::GetVKey('Z') == true && g_key_flag == true 
		  || Input::GetVKey(VK_RETURN) == true) && g_key_flag == true)
		{
			if (m_key_flag == true)
			{
				g_key_flag = false;	//キーフラグをオフ
				Audio::Start(1);
				g_stage = Space;	//ステージをSpaceに設定
				stagec->SetAlpha(ALPHAORIGIN);	//アルファ値を元に戻す
				this->SetStatus(false);
				
			}
		}
	}
	//キー入力を長押しで出来ないようにする
	if (Input::GetVKey('Z') == false && Input::GetVKey(VK_RETURN) == false)
	{
		g_key_flag = true;	//離したらオンにする
	}
	
	//Zキーが押されると徐々に暗転しながらシーン移行
	if (m_push_flag == true)
	{
		m_Tra5 += 0.03f;
		if (m_Tra5 > 1.0f)
		{
			if (g_stage == EarthStar)//地球
			{
				Scene::SetScene(new CSceneEarth());
			}
			else if (g_stage == VenusTaurus)//おうし座
			{
				Scene::SetScene(new CSceneVenusTaurus());
			}
			else if (g_stage == VenusLibra)//てんびん座
			{
				Scene::SetScene(new CSceneVenusLibra());
			}
			else if (g_stage == MercuryGemini)//ふたご座
			{
				Scene::SetScene(new CSceneMercuryGemini());
			}
			else if (g_stage == MercuryVirgo)//おとめ座
			{
				Scene::SetScene(new CSceneMercuryVirgo());
			}
			else if (g_stage == SunLeo)//太陽
			{
				Scene::SetScene(new CSceneSunLeo());
			}
		}

	}


}

//ドロー
void CObjStarChoice::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,0.0f,m_Tra1 };	//標準カラー
	//クリア用
	float stage[4] = { 1.0f,1.0f,0.0f,m_Tra4 };
	float last_stage[4] = { 1.0f,0.0f,0.0f,m_Tra4 };

	float left_clear[4] = { 1.0f,1.0f,0.0f,m_Tra1 };
	float right_clear[4] = { 1.0f,1.0f,0.0f,m_Tra2 };

	float E[4] = { 1.0f,0.0f,0.0f,m_Tra1 };

	float stage_change[4] = { 1.0f,1.0f,1.0f,m_Tra5 }; //ステージ移行

	//左の星座
	float left[4]  = { 1.0f,1.0f,1.0f,m_Tra1 };
	//右の星座
	float right[4] = { 1.0f,1.0f,1.0f,m_Tra2 };
	//下のコマンド
	float down[4]  = { 1.0f,1.0f,1.0f,m_Tra3 };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置
	
				//戻るコマンド表示
	Font::StrDraw(L"戻る", BACK_POSX, BACK_POSY, BACK_FONTSIZE, down);

	

	if (m_push_flag == true)
	{
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 350.0f;
		src.m_right = 400.0f;
		src.m_bottom = 50.0f;

		//表示位置の設定
		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 600.0f;

		Draw::Draw(9, &src, &dst, stage_change, 0.0f);
	}
	//地球選択時に表示される画像
	if (g_stage == Earth)
	{
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
		//地球にラスボスを設置するんので、太陽をクリアしたらわかりやすく表示させる
		if (g_Sun_clear == true)
		{
			Font::StrDraw(L"最終ステージ", 64, 64, 32, last_stage);

		}
		else
			//カーソルを合わせると左上にステージ名表示
			Font::StrDraw(L"チュートリアルステージ", 64, 64, 32, stage);

		//表示(太陽クリアで見た目変化)
		if (g_Sun_clear == true)
		{
			Draw::Draw(7, &src, &dst, E, 0.0f);
		}
		else
			Draw::Draw(7, &src, &dst, left, 0.0f);

		if (g_Sun_clear == true)
		{
			Font::StrDraw(L"CLEAR・・・?", 350, 400, 40, c);
		}
		else if (g_Earth_clear == true)
		{
			Font::StrDraw(L"CLEAR!", 350, 400, 40, c);
		}
	}
	//金星選択時に表示される画像---------------------------------------------------------
	else if (g_stage == Venus)
	{

		//牡牛座の画像-----------------------------------------------------------------
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
			Font::StrDraw(L"CLEAR!", 500, 400, 40, right_clear);
		}

		//----------------------------------------------------------------------------------
		//カーソルを合わせると左上にステージ名表示
		if (m_direction == LEFT)
		{
			Font::StrDraw(L"牡牛座ステージ", 64, 64, 32, stage);
		}
		else if (m_direction == RIGHT)
		{
			Font::StrDraw(L"天秤座ステージ", 64, 64, 32, stage);
		}
	}
	//水星選択時に表示される画像---------------------------------------------------------
	else if (g_stage == Mercury)
	{

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
		//乙女座クリアでクリア表記
		if (g_Virgo_clear == true)
		{
			Font::StrDraw(L"CLEAR!", 500, 400, 40, right_clear);
		}
		//カーソルを合わせると左上にステージ名表示
		if (m_direction == LEFT)
		{
			Font::StrDraw(L"双子座ステージ", 64, 64, 32, stage);
		}
		else if (m_direction == RIGHT)
		{
			Font::StrDraw(L"乙女座ステージ", 64, 64, 32, stage);
		}

		//----------------------------------------------------------------------------------
	}
	else if(g_stage == Sun)
	{
		//切り取り位置の設定
		src.m_top    = 0.0f;
		src.m_left   = 1500.0f;
		src.m_right  = 1800.0f;
		src.m_bottom = 200.0f;

		//表示位置の設定
		dst.m_top    = 190.0f;
		dst.m_left   = 250.0f;
		dst.m_right  = 550.0f;
		dst.m_bottom = 390.0f;
		//表示
		Draw::Draw(7, &src, &dst, left, 0.0f);
		//獅子座クリアでクリア表記
		if (g_Sun_clear == true)
		{
			Font::StrDraw(L"CLEAR!", 350, 400, 40, c);
		}
		Font::StrDraw(L"獅子座ステージ", 64, 64, 32, stage);
	}
}
