//使用するヘッダー
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\SceneManager.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "ObjPerformanceRoom.h"

//使用するネームスペース
using namespace GameL;
#define CLEAR_F false
bool g_new_Performance=false;
//敵をすべて倒した------------------
bool g_Taurus_Enemy_AllKill= CLEAR_F;
bool g_Libra_Enemy_AllKill= CLEAR_F;
bool g_Gemini_Enemy_AllKill= CLEAR_F;
bool g_Viego_Enemy_AllKill= CLEAR_F;
bool g_Leo_Enemy_AllKill= CLEAR_F;
//ノーダメージクリア----------------
bool g_Taurus_NoDamage_Clear= CLEAR_F;
bool g_Libra_NoDamage_Clear= CLEAR_F;
bool g_Gemini_NoDamage_Clear= CLEAR_F;
bool g_Viego_NoDamage_Clear= CLEAR_F;
bool g_Leo_NoDamage_Clear= CLEAR_F;
//その他
int g_All_Killcnt=0;
int g_Death_cnt=0;
int g_Taurus_Grade=0;
int g_Libra_Grade=0;
int g_Gemini_Grade=0;
int g_Viego_Grade=0;
int g_Leo_Grade=0;

//シークレット系
bool g_Tutorial_Clear= CLEAR_F; //チュートリアルクリア
bool g_Earth_BossKill = CLEAR_F; //ラスボスを倒した
bool g_All_Skill_Get= CLEAR_F;  //すべてのスキルを獲得
int g_TRank = None;
int g_LiRank = None;		//ランク管理用
int g_GRank = None;		//ランク管理用
int g_VRank = None;		//ランク管理用
int g_LeRank = None;		//ランク管理用



//イニシャライズ
void CObjPerformanceRoom::Init()
{
	m_page = 0;
	m_next_f = false;
	m_back_f = false;
}

//アクション
void CObjPerformanceRoom::Action()
{
	g_new_Performance = false;
	//Xで選択画面へ戻る
	if (Input::GetVKey('X'))
	{
		g_stage = Space;
		this->SetStatus(false);    //自身に削除命令を出す
	}
	//Zキーで次のページへ
	if (Input::GetVKey('Z'))
	{
		if (m_next_f == true)
		{
			if (m_page >= 3)
			{
				;
			}
			else
			{
				Audio::Start(1);
				m_page++;
			}
			m_next_f = false;
		}
	}

	else
	{
		m_next_f = true;
	}
	//Cキーで前のページへ
	if (Input::GetVKey('C'))
	{
		if (m_back_f == true)
		{
			if (m_page <= 0)
			{
				;
			}
			else
			{
				Audio::Start(1);
				m_page--;
			}
			m_back_f = false;
		}
	}
	else
	{
		m_back_f = true;
	}

}

//ドロー
void CObjPerformanceRoom::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	float a[4] = { 1.0f,1.0f,1.0f,0.8f };
	float y[4] = { 1.0f,1.0f,0.0f,1.0f };

	float cs[4] = { 0.0f,0.5f,1.0f,1.0f };
	float ca[4] = { 1.0f,0.0f,0.0f,1.0f	};
	float cb[4] = { 0.0f,1.0f,0.0f,1.0f };
	float cc[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置
	//背景用画像-----------------------------------
	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 822.0f;
	src.m_bottom = 218.0f;

	//表示位置の設定
	dst.m_top = 100.0f;
	dst.m_left = 50.0f;
	dst.m_right = 750.0f;
	dst.m_bottom = 500.0f;
	//表示
	Draw::Draw(40, &src, &dst, a, 0.0f);
	//----------------------------------------------
		wchar_t KILLCNT[128];	//キルカウント表示用
		wchar_t DEATHCNT[128];	//デスカウント表示用

		swprintf_s(KILLCNT, L"敵を合計%d体倒した！", g_All_Killcnt);
		swprintf_s(DEATHCNT, L"%d回死んでしまった！", g_Death_cnt);

	//説明用のメッセージの表示
	Font::StrDraw(L"解放した実績", 75, 120, 27, c);
	//実績達成画面で表示させるためのフラグ処理
	//ノーダメージクリア
	if (m_page == 0)
	{
		Font::StrDraw(L"ノーダメージクリア", 75, 155, 27, c);
		//牡牛座
		if (g_Taurus_NoDamage_Clear == true)
		{
			Font::StrDraw(L"牡牛座：ノーダメージクリア！", 75, 190, 28, y);

		}
		else
		{
			Font::StrDraw(L"牡牛座：未達成", 75, 190, 28, c);
		}
		//天秤座
		if (g_Libra_NoDamage_Clear == true)
		{
			Font::StrDraw(L"天秤座：ノーダメージクリア！", 75, 225, 28, y);

		}
		else
		{
			Font::StrDraw(L"天秤座：未達成", 75, 225, 28, c);

		}
		//双子座
		if (g_Gemini_NoDamage_Clear == true)
		{
			Font::StrDraw(L"双子座：ノーダメージクリア！", 75, 260, 28, y);

		}
		else
		{
			Font::StrDraw(L"双子座：未達成", 75, 260, 28, c);

		}
		//乙女座
		if (g_Viego_NoDamage_Clear == true)
		{
			Font::StrDraw(L"乙女座：ノーダメージクリア！", 75, 295, 28, y);
		}
		else
		{
			Font::StrDraw(L"乙女座：未達成", 75, 295, 28, c);

		}
		//獅子座
		if (g_Leo_NoDamage_Clear == true)
		{
			Font::StrDraw(L"獅子座：ノーダメージクリア！", 75, 330, 28, y);
		}
		else
		{
			Font::StrDraw(L"獅子座：未達成", 75, 330, 28, c);

		}

	}
	//敵全滅
	else if (m_page == 1)
	{
		Font::StrDraw(L"ALL KILL", 75, 155, 27, c);
		//牡牛座
		if (g_Taurus_Enemy_AllKill == true)
		{
			Font::StrDraw(L"牡牛座：敵を全滅させた！！", 75, 190, 28, y);

		}
		else
		{
			Font::StrDraw(L"牡牛座：未達成", 75, 190, 28, c);
		}
		//天秤座
		if (g_Libra_Enemy_AllKill == true)
		{
			Font::StrDraw(L"天秤座：敵を全滅させた！！", 75, 225, 28, y);

		}
		else
		{
			Font::StrDraw(L"天秤座：未達成", 75, 225, 28, c);

		}
		//双子座
		if (g_Gemini_Enemy_AllKill == true)
		{
			Font::StrDraw(L"双子座：敵を全滅させた！！", 75, 260, 28, y);

		}
		else
		{
			Font::StrDraw(L"双子座：未達成", 75, 260, 28, c);

		}
		//乙女座
		if (g_Viego_Enemy_AllKill == true)
		{
			Font::StrDraw(L"乙女座：敵を全滅させた！！", 75, 295, 28, y);
		}
		else
		{
			Font::StrDraw(L"乙女座：未達成", 75, 295, 28, c);

		}
		//獅子座
		if (g_Leo_Enemy_AllKill == true)
		{
			Font::StrDraw(L"獅子座：敵を全滅させた！！", 75, 330, 28, y);
		}
		else
		{
			Font::StrDraw(L"獅子座：未達成", 75, 330, 28, c);

		}

	}
	//その他
	else if (m_page == 2)
	{
		Font::StrDraw(L"その他・各星座最高ランク", 75, 155, 27, c);

		Font::StrDraw(KILLCNT, 75, 190, 28, y);
		Font::StrDraw(DEATHCNT, 75, 225, 28, y);
		//牡牛座
		if (g_Taurus_Grade == S)
		{			
			Font::StrDraw(L"牡牛座：Sランク", 75, 260, 28, cs);
			g_TRank = S;
		}
		else if (g_Taurus_Grade == A)
		{
			//もし、先にSランクをとっていた場合Sランクに書き換える
			if (g_TRank > A)
			{
				Font::StrDraw(L"牡牛座：Sランク", 75, 260, 28, cs);
			}
			else
			{
				Font::StrDraw(L"牡牛座：Aランク", 75, 260, 28, ca);
				g_TRank = A;
			}
		}
		else if (g_Taurus_Grade == B)
		{
			//もし、先に上位ランクをとっていた場合上位ランクに書き換える
			if (g_TRank > B)
			{
				if (g_TRank == S)
				{
					Font::StrDraw(L"牡牛座：Sランク", 75, 260, 28, cs);
				}
				else if (g_TRank == A)
				{
					Font::StrDraw(L"牡牛座：Aランク", 75, 260, 28, ca);
				}
			}
			Font::StrDraw(L"牡牛座：Bランク", 75, 260, 28, cb);
			g_TRank = B;
		}
		else if (g_Taurus_Grade == C)
		{	
			//もし、先に上位ランクをとっていた場合上位ランクに書き換える
			if (g_TRank > C)
			{
				if (g_TRank == S)
				{
					Font::StrDraw(L"牡牛座：Sランク", 75, 260, 28, cs);
				}
				else if (g_TRank == A)
				{
					Font::StrDraw(L"牡牛座：Aランク", 75, 260, 28, ca);
				}
				else if (g_TRank == B)
				{
					Font::StrDraw(L"牡牛座：Bランク", 75, 260, 28, cb);
				}
				else
				{
					Font::StrDraw(L"牡牛座：Cランク", 75, 260, 28, cc);
				}
			}
		}
		else
		{
			Font::StrDraw(L"牡牛座：まだクリアしていないよ", 75, 260, 28, c);
		}
		//天秤座
		if (g_Libra_Grade == S)
		{
			Font::StrDraw(L"天秤座：Sランク", 75, 295, 28, cs);
			g_LiRank = S;
		}
		else if (g_Libra_Grade == A)
		{
			//もし、先にSランクをとっていた場合Sランクに書き換える
			if (g_LiRank > A)
			{
				Font::StrDraw(L"天秤座：Sランク", 75, 295, 28, cs);
			}
			else
			{
				Font::StrDraw(L"天秤座：Aランク", 75, 295, 28, ca);
				g_LiRank = A;
			}
		}
		else if (g_Libra_Grade == B)
		{
			//もし、先に上位ランクをとっていた場合上位ランクに書き換える
			if (g_LiRank > B)
			{
				if (g_LiRank == S)
				{
					Font::StrDraw(L"天秤座：Sランク", 75, 295, 28, cs);
				}
				else if (g_LiRank == A)
				{
					Font::StrDraw(L"天秤座：Aランク", 75, 295, 28, ca);
				}
			}
			Font::StrDraw(L"天秤座：Bランク", 75, 295, 28, cb);
			g_LiRank = B;
		}
		else if (g_Libra_Grade == C)
		{
			//もし、先に上位ランクをとっていた場合上位ランクに書き換える
			if (g_LiRank > C)
			{
				if (g_LiRank == S)
				{
					Font::StrDraw(L"天秤座：Sランク", 75, 295, 28, cs);
				}
				else if (g_LiRank == A)
				{
					Font::StrDraw(L"天秤座：Aランク", 75, 295, 28, ca);
				}
				else if (g_LiRank == B)
				{
					Font::StrDraw(L"天秤座：Bランク", 75, 295, 28, cb);
				}
				else
				{
					Font::StrDraw(L"天秤座：Cランク", 75, 295, 28, cc);
				}
			}
		}
		else
		{
			Font::StrDraw(L"天秤座：まだクリアしていないよ", 75, 295, 28, c);
		}
		//双子座
		if (g_Gemini_Grade == S)
		{
			Font::StrDraw(L"双子座：Sランク", 75, 330, 28, cs);
			g_GRank = S;
		}
		else if (g_Gemini_Grade == A)
		{
			//もし、先にSランクをとっていた場合Sランクに書き換える
			if (g_GRank > A)
			{
				Font::StrDraw(L"双子座：Sランク", 75, 330, 28, cs);
			}
			else
			{
				Font::StrDraw(L"双子座：Aランク", 75, 330, 28, ca);
				g_GRank = A;
			}
		}
		else if (g_Gemini_Grade == B)
		{
			//もし、先に上位ランクをとっていた場合上位ランクに書き換える
			if (g_GRank > B)
			{
				if (g_GRank == S)
				{
					Font::StrDraw(L"双子座：Sランク", 75, 330, 28, cs);
				}
				else if (g_GRank == A)
				{
					Font::StrDraw(L"双子座：Aランク", 75, 330, 28, ca);
				}
			}
			Font::StrDraw(L"双子座：Bランク", 75, 330, 28, cb);
			g_GRank = B;
		}
		else if (g_Gemini_Grade == C)
		{
			//もし、先に上位ランクをとっていた場合上位ランクに書き換える
			if (g_GRank > C)
			{
				if (g_GRank == S)
				{
					Font::StrDraw(L"双子座：Sランク", 75, 330, 28, cs);
				}
				else if (g_GRank == A)
				{
					Font::StrDraw(L"双子座：Aランク", 75, 330, 28, ca);
				}
				else if (g_GRank == B)
				{
					Font::StrDraw(L"双子座：Bランク", 75, 330, 28, cb);
				}
				else
				{
					Font::StrDraw(L"双子座：Cランク", 75, 330, 28, cc);
				}
			}
		}
		else
		{
			Font::StrDraw(L"双子座：まだクリアしていないよ", 75, 330, 28, c);
		}

		//乙女座
		if (g_Viego_Grade == S)
		{
			Font::StrDraw(L"乙女座：Sランク", 75, 365, 28, cs);
			g_VRank = S;
		}
		else if (g_Viego_Grade == A)
		{
			//もし、先にSランクをとっていた場合Sランクに書き換える
			if (g_VRank > A)
			{
				Font::StrDraw(L"乙女座：Sランク", 75, 365, 28, cs);
			}
			else
			{
				Font::StrDraw(L"乙女座：Aランク", 75, 365, 28, ca);
				g_VRank = A;
			}
		}
		else if (g_Viego_Grade == B)
		{
			//もし、先に上位ランクをとっていた場合上位ランクに書き換える
			if (g_VRank > B)
			{
				if (g_VRank == S)
				{
					Font::StrDraw(L"乙女座：Sランク", 75, 365, 28, cs);
				}
				else if (g_VRank == A)
				{
					Font::StrDraw(L"乙女座：Aランク", 75, 365, 28, ca);
				}
			}
			Font::StrDraw(L"乙女座：Bランク", 75, 365, 28, cb);
			g_VRank = B;
		}
		else if (g_Viego_Grade == C)
		{
			//もし、先に上位ランクをとっていた場合上位ランクに書き換える
			if (g_VRank > C)
			{
				if (g_VRank == S)
				{
					Font::StrDraw(L"乙女座：Sランク", 75, 365, 28, cs);
				}
				else if (g_VRank == A)
				{
					Font::StrDraw(L"乙女座：Aランク", 75, 365, 28, ca);
				}
				else if (g_VRank == B)
				{
					Font::StrDraw(L"乙女座：Bランク", 75, 365, 28, cb);
				}
				else
				{
					Font::StrDraw(L"乙女座：Cランク", 75, 365, 28, cc);
				}
			}
		}
		else
		{
			Font::StrDraw(L"乙女座：まだクリアしていないよ", 75, 365, 28, c);
		}

		//獅子座
		if (g_Leo_Grade == S)
		{
			Font::StrDraw(L"獅子座：Sランク", 75, 400, 28, cs);
			g_LeRank = S;
		}
		else if (g_Leo_Grade == A)
		{
			//もし、先にSランクをとっていた場合Sランクに書き換える
			if (g_LeRank > A)
			{
				Font::StrDraw(L"獅子座：Sランク", 75, 400, 28, cs);
			}
			else
			{
				Font::StrDraw(L"獅子座：Aランク", 75, 400, 28, ca);
				g_LeRank = A;
			}
		}
		else if (g_Leo_Grade == B)
		{
			//もし、先に上位ランクをとっていた場合上位ランクに書き換える
			if (g_LeRank > B)
			{
				if (g_LeRank == S)
				{
					Font::StrDraw(L"獅子座：Sランク", 75, 400, 28, cs);
				}
				else if (g_LeRank == A)
				{
					Font::StrDraw(L"獅子座：Aランク", 75, 400, 28, ca);
				}
			}
			Font::StrDraw(L"獅子座：Bランク", 75, 400, 28, cb);
			g_LeRank = B;
		}
		else if (g_Leo_Grade == C)
		{
			//もし、先に上位ランクをとっていた場合上位ランクに書き換える
			if (g_VRank > C)
			{
				if (g_LeRank == S)
				{
					Font::StrDraw(L"獅子座：Sランク", 75, 400, 28, cs);
				}
				else if (g_LeRank == A)
				{
					Font::StrDraw(L"獅子座：Aランク", 75, 400, 28, ca);
				}
				else if (g_LeRank == B)
				{
					Font::StrDraw(L"獅子座：Bランク", 75, 400, 28, cb);
				}
				else
				{
					Font::StrDraw(L"獅子座：Cランク", 75, 400, 28, cc);
				}
			}
		}
		else
		{
			Font::StrDraw(L"獅子座：まだクリアしていないよ", 75, 400, 28, c);
		}

	}
	//シークレット
	else if (m_page == 3)
	{
		Font::StrDraw(L"シークレット", 75, 155, 27, c);	
		//チュートリアルクリア
		if (g_Tutorial_Clear == true)
		{			
			Font::StrDraw(L"チュートリアルクリア！ようこそ！STAR REGEINへ！", 75, 190, 28, y);
		}
		else
		{
			Font::StrDraw(L"？？？", 75, 190, 28, c);
		}
		//すべてのスキル獲得
		if (g_All_Skill_Get == true)
		{
			Font::StrDraw(L"すべての星座の力を手に入れた！！", 75, 225, 28, y);
		}
		else
		{
			Font::StrDraw(L"？？？", 75, 225, 28, c);
		}
		//ラスボス撃破
		if (g_Earth_BossKill == true)
		{			
			Font::StrDraw(L"ラスボスを倒した！！！", 75, 260, 28, y);
		}
		else
		{
			Font::StrDraw(L"？？？", 75, 260, 28, c);
		}

	}
	//4ページ以降は何もなし
	if (m_page >= 3)
	{
		;
	}
	else
	{
		Font::StrDraw(L"Zキーで次の項目へ", 518, 460, 27, c);
	}
	if (m_page >= 1)
	{
		Font::StrDraw(L"Cキーで前の項目へ", 75, 460, 28, c);
	}
	Font::StrDraw(L"Xキーで閉じる", 570, 120,28, c);




}
