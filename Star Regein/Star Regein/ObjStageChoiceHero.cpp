//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjStageChoiceHero.h"
#include "ObjStageChoice.h"

//使用するネームスペース
using namespace GameL;


ObjStageChoiceHero::ObjStageChoiceHero(float x, float y)
{//オブジェ作成時に渡されたx,y座標をメンバ変数に代入
	m_px = x;
	m_py = y;
}

//イニシャライズ
void ObjStageChoiceHero::Init()
{
	m_vx = 0.0f;		//移動ベクトル
	m_vy = 0.0f;
	//初期姿勢
	g_posture = HERO_DOWN;

	m_ani_time = 0;
	m_ani_frame = 1;

	//blockとの衝突状態確認
	m_hit_up    = false;
	m_hit_down  = false;
	m_hit_left  = false;
	m_hit_right = false;

	m_block_type = 0;		//踏んでいるblockの種類を確認用

}

//アクション
void ObjStageChoiceHero::Action()
{
	//星座選択時に入力制御する
	if (g_stage == Earth || g_stage == Venus || g_stage == Mercury || g_stage == Sun ) {
		return;
	}

	//移動ベクトルの破棄
	m_vx = 0.0f;
	m_vy = 0.0f;

	//Shiftキーが入力されたらダッシュ
	if ((Input::GetVKey(VK_SHIFT)))
	{
		m_speed_power = STAGE_DASH_SPEED;
	}
	else//通常速度
	{
		m_speed_power = STAGE_NORMAL_SPEED;
	}

	if (Input::GetVKey(VK_UP))//矢印キー（上）が入力されたとき
	{
		m_vy -= m_speed_power;
		g_posture = HERO_UP;
		m_ani_time += ANITIME;
	}
	else if (Input::GetVKey(VK_DOWN))//矢印キー（下）が入力されたとき
	{
		m_vy += m_speed_power;
		g_posture = HERO_DOWN;
		m_ani_time += ANITIME;
	}
	else if (Input::GetVKey(VK_LEFT))//矢印キー（左）が入力されたとき
	{
		m_vx -= m_speed_power;
		g_posture = HERO_LEFT;
		m_ani_time += ANITIME;
	}
	else if (Input::GetVKey(VK_RIGHT))//矢印キー（右）が入力されたとき
	{
		m_vx += m_speed_power;
		g_posture = HERO_RIGHT;
		m_ani_time += ANITIME;
	}
	else//移動キーの入力が無い場合
	{
		m_ani_frame = 1;	//静止フレームにする
		m_ani_time = 0;		//アニメーション時間リセット
	}

	//アニメーション用
	if (m_ani_time > 4)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}

	if (m_ani_frame == 4)
	{
		m_ani_frame = 0;
	}

	//ステージ選択画面の情報を取得
	CObjStageChoice* stagec = (CObjStageChoice*)Objs::GetObj(OBJ_STAGECHOICE);


	//地球へ
	if (m_px >= EarthX && m_px <= EarthX2 && m_py >= EarthY&&m_py <= EarthY2)
	{
		//▼前シーンからZキー押し続けでこれを押さないように、
		//このシーンに入って一度も押してない状態に移行しないと
		//実行出来ないようにしている。
		if (Input::GetVKey('Z') == true && m_key_flag == true)
		{
			g_stage = Earth;	//ステージの値を地球に変更
		}
	}
	//金星へ
	else if (m_px >= VenusX && m_px <= VenusX2 && m_py >= VenusY&&m_py <= VenusY2)
	{
		//▼前シーンからZキー押し続けでこれを押さないように、
		//このシーンに入って一度も押してない状態に移行しないと
		//実行出来ないようにしている。
		if (Input::GetVKey('Z') == true && m_key_flag == true)
		{
			//金星に設定
			g_stage = Venus;
		}
	}
	//水星へ
	else if (m_px >= MercuryX && m_px <= MercuryX2 && m_py >= MercuryY&&m_py <= MercuryY2)
	{
		//▼前シーンからZキー押し続けでこれを押さないように、
		//このシーンに入って一度も押してない状態に移行しないと
		//実行出来ないようにしている。
		if (Input::GetVKey('Z') == true && m_key_flag == true)
		{
			//水星に設定
			g_stage = Mercury;
		}
	}
	//太陽へ
	else if (m_px >= SunX && m_px <= SunX2 && m_py >= SunY&&m_py <= SunY2)
	{
		if (Input::GetVKey('Z') == true && m_key_flag == true)
		{
			//仮でタイトルに行くようにしてるからあとでちゃんと太陽にしておいてね
			//太陽に設定
			//g_stage = SunLeo;←ステージが完成したらコメント外してね
			Scene::SetScene(new CSceneTitle());
		}
	}
	else
	{
		m_key_flag = true;
	}

	//位置の更新
	m_px += m_vx;
	m_py += m_vy;
}

//ドロー
void ObjStageChoiceHero::Draw()
{
	//アニメーション
	int AniData[5] =
	{
		0,1,2,3,0,
	};

	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	//切り取り位置の設定
	src.m_top    = 64.0f * g_posture;
	src.m_left   =  0.0f + (AniData[m_ani_frame] * 64);
	src.m_right  = 64.0f + (AniData[m_ani_frame] * 64);
	src.m_bottom = src.m_top + 64.0f;

	//表示位置の設定
	dst.m_top    =  0.0f + m_py;
	dst.m_left   = 80.0f + m_px;
	dst.m_right  =  0.0f + m_px;
	dst.m_bottom = 80.0f + m_py;

	//表示
	Draw::Draw(1, &src, &dst, c, 0.0f);
}
