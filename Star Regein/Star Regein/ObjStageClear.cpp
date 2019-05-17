//使用するヘッダー
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\SceneManager.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "ObjStageClear.h"

//使用するネームスペース
using namespace GameL;


//イニシャライズ
void CObjStageClear::Init()
{
	m_time = 0;	//描画までのタイム感覚の初期化
	m_Tra = 0.0f;
	m_push_flag = false;
}

//アクション
void CObjStageClear::Action()
{
	//キー入力タイムが一定に達した場合、キー入力を許可する
	if ((Input::GetVKey('Z') == true && m_alpha[4] == 1.0f || Input::GetVKey(VK_RETURN) == true) && m_alpha[4] == 1.0f)	
	{

		m_push_flag = true;
	
	}
	//Zキーを押すと徐々に暗転し、シーン移行
	if (m_push_flag == true)
	{
		m_Tra += 0.03f;
		m_alpha[0] = 0.03f;
		m_alpha[1] = 0.03f;
		m_alpha[2] = 0.03f;
		m_alpha[3] = 0.03f;
		m_alpha[4] = 0.03f;
		m_alpha[5] = 0.03f;
		m_alpha[6] = 0.03f;

		if (m_Tra >= 1.0f)
		{
			Scene::SetScene(new CSceneStageChoice());//ステージ選択
			g_stage_clear = false;
			g_move_stop_flag = false;

		}
	}


	//タイムを60になるまでプラス
	m_time++;
	if (m_time >= 60)
		m_time = 60;
	if (m_time == 60) {	//タイムが100になったらアルファ値を増やす
		m_alpha[0] += 0.05f;
		if (m_alpha[0] >= 1.0f)
			m_alpha[0] = 1.0f;	//1.0fになったら次へ
	}
	if (m_alpha[0] == 1.0f) {	//メッセージ分繰り返す
		m_alpha[1] += 0.05f;
		if (m_alpha[1] >= 1.0f)
			m_alpha[1] = 1.0f;
	}
	if (m_alpha[1] == 1.0f) {
		m_alpha[2] += 0.05f;
		if (m_alpha[2] >= 1.0f)
			m_alpha[2] = 1.0f;
	}
	if (m_alpha[2] == 1.0f) {
		m_alpha[3] += 0.05f;
		if (m_alpha[3] >= 1.0f)
			m_alpha[3] = 1.0f;
	}
	if (m_alpha[3] == 1.0f) {
		m_alpha[4] += 0.05f;
		if (m_alpha[4] >= 1.0f)
			m_alpha[4] = 1.0f;
	}
	if (m_alpha[4] == 1.0f) {
		m_alpha[5] += 0.05f;
		if (m_alpha[5] >= 1.0f)
			m_alpha[5] = 1.0f;
	}
	if (m_alpha[5] == 1.0f) {
		m_alpha[6] += 0.05f;
		if (m_alpha[6] >= 1.0f)
			m_alpha[6] = 1.0f;
	}
}

//ドロー
void CObjStageClear::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,m_Tra };
	float Stage[4] = { 1.0f,1.0f,1.0f,1.0f };

	float c1[4] = { 1.0f,1.0f,1.0f,m_alpha[0] };
	float c2[4] = { 1.0f,1.0f,1.0f,m_alpha[1] };
	float c3[4] = { 1.0f,1.0f,1.0f,m_alpha[2] };
	float c4[4] = { 1.0f,1.0f,0.0f,m_alpha[3] };
	float c5[4] = { 1.0f,1.0f,1.0f,m_alpha[4] };
	float c6[4] = { 1.0f,1.0f,1.0f,m_alpha[5] };
	float c7[4] = { 1.0f,1.0f,1.0f,m_alpha[6] };


	float y[4] = { 1.0f,1.0f,0.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	


	if (g_stage == EarthStar)
	{
		//地球-------------------------------
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 790.0f;
		src.m_bottom = 590.0f;

		//表示位置の設定
		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 600.0f;

	}
	if (g_stage == VenusTaurus)
	{
		//金星（牡牛座）--------------------------
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 790.0f;
		src.m_bottom = 590.0f;

		//表示位置の設定
		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 600.0f;

		
	}
	if (g_stage == VenusLibra)
	{
		//金星（牡牛座）--------------------------
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 790.0f;
		src.m_bottom = 590.0f;

		//表示位置の設定
		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 600.0f;

	
	}
	if (g_stage == MercuryGemini)
	{
		//金星（牡牛座）--------------------------
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 790.0f;
		src.m_bottom = 590.0f;

		//表示位置の設定
		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 600.0f;

	
	}
	if (g_stage == MercuryVirgo)
	{
		//金星（牡牛座）--------------------------
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 790.0f;
		src.m_bottom = 590.0f;

		//表示位置の設定
		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 600.0f;
	}
	if (g_stage == SunLeo)
	{
		//金星（牡牛座）--------------------------
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 790.0f;
		src.m_bottom = 590.0f;

		//表示位置の設定
		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 600.0f;
	}

	//表示
	Draw::Draw(60, &src, &dst, Stage, 0.0f);

	Font::StrDraw(L"STAGE CLEAR", 120,150, 100,y);

	Font::StrDraw(L"Zキーでステージ選択へ戻る", 200, 510, 32, y);

	//シーン移行用
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

		Draw::Draw(9, &src, &dst, c, 0.0f);

	}



	//メッセージの情報を持ってくる
	CObjMessage* objmes = (CObjMessage*)Objs::GetObj(OBJ_MESSAGE);
	//クリア情報
	wchar_t KILLCNT[128];	//キルカウント表示用

	wchar_t TIME[128];	//タイムの描画

	//m_time_mesから描分を求める
	//分：秒の値を文字列化
	if (objmes->GetSECOND()<10)
		swprintf_s(TIME, L"クリアタイム：%d分0%d秒", objmes->GetMINUTE(), objmes->GetSECOND());//秒の1桁目に0を用意
	else
		swprintf_s(TIME, L"クリアタイム：%d分%d秒", objmes->GetMINUTE(), objmes->GetSECOND());

	

	swprintf_s(KILLCNT, L"敵を%d体倒した！", g_kill_cnt);

	//各星座ごとのメッセージ
	if (g_stage == EarthStar)
	{
		Font::StrDraw(L"地球をクリアした！", 15, 250, 21, c1);
		Font::StrDraw(L"取得したスキル：無し", 15, 280, 21, c2);
	}
	if (g_stage == VenusTaurus)
	{
		Font::StrDraw(L"牡牛座をクリアした！", 15, 250, 21, c1);
		Font::StrDraw(L"取得したスキル：牡牛座", 15, 280, 21, c2);
	}
	if (g_stage == VenusLibra)
	{
		Font::StrDraw(L"天秤座をクリアした！", 15, 250, 21, c1);
		Font::StrDraw(L"取得したスキル：天秤座", 15, 280, 21, c2);
	}
	if (g_stage == MercuryGemini)
	{
		Font::StrDraw(L"双子座をクリアした！", 15, 250, 21, c1);
		Font::StrDraw(L"取得したスキル：双子座", 15, 280, 21, c2);
	}
	if (g_stage == MercuryVirgo)
	{
		Font::StrDraw(L"乙女座をクリアした！", 15, 250, 21, c1);
		Font::StrDraw(L"取得したスキル：乙女座", 15, 280, 21, c2);
	}
	if (g_stage == SunLeo)
	{
		Font::StrDraw(L"獅子座をクリアした！", 15, 250, 21, c1);
		Font::StrDraw(L"取得したスキル：獅子座", 15, 280, 21, c2);
	}

	Font::StrDraw(TIME, 15, 310, 21, c3);


	//地球以外の星の場合
	if (g_stage != EarthStar)
	{
		//敵殲滅用メッセージの表示
		if (g_kill_cnt == g_enemy_cnt)
			Font::StrDraw(L"敵を全滅させた！", 15, 340, 21, c4);
		else if (g_kill_cnt == 0)
			Font::StrDraw(L"誰も倒さなかった！", 15, 340, 21, c4);
		else if (g_kill_cnt > 0)
			Font::StrDraw(KILLCNT, 15, 340, 21, c4);
		//ノーダメージクリアメッセージの表示
		if (g_no_damage == false)
		{
			Font::StrDraw(L"ノーダメージクリア！", 15, 370, 21, c5);
			//実績達成画面で表示させるためのフラグ処理
			if (g_stage == VenusTaurus)
			{
				g_Taurus_NoDamage_Clear = true;
			}
			else if (g_stage == VenusLibra)
			{
				g_Libra_NoDamage_Clear = true;
			}
			else if (g_stage == MercuryGemini)
			{
				g_Gemini_NoDamage_Clear = true;
			}
			else if (g_stage == MercuryVirgo)
			{
				g_Viego_NoDamage_Clear = true;
			}
			else if (g_stage == SunLeo)
			{
				g_Leo_NoDamage_Clear = true;
			}
		}
	}
}

void CObjStageClear::alpha()
{


}