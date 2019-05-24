//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

//使用するヘッダーファイル
#include "GameHead.h"
#include "ObjBeamSaber.h"

//使用するネームスペース
using namespace GameL;

bool g_attack_flag;
int g_slash_time;
int g_slash_frame;

//コンストラクタ
CObjBeamSaber::CObjBeamSaber(float x, float y)
{
	m_x = x;
	m_y = y;
}

//イニシャライズ
void CObjBeamSaber::Init()
{
	m_ani_frame = 0;	//アニメーションフレームの初期化
	m_ani_time = 0;		//アニメーションタイムの初期化

	m_f = false;	//サウンド用フラグの初期化
	//主人公の向きによって攻撃を出す方向，向きを変える
	//当たり判定をセット
	if (g_posture == HERO_UP)  //上
	{
		m_angle = 270.0f;	//角度調整
		m_pos_x = 10.0f;	//X軸調整
		m_pos_y = -40.0f;	//Y軸調整
	}
	else if (g_posture == HERO_LEFT) //左
	{
		m_angle = 0.0f;		//角度調整
		m_pos_x = -35.0f;	//X軸調整
		m_pos_y = 10.0f;	//Y軸調整
	}
	else if (g_posture == HERO_DOWN) //下
	{
		m_angle = 90.0f;	//角度調整
		m_pos_x = 10.0f;	//X軸調整
		m_pos_y = 50.0f;	//Y軸調整
	}
	else if (g_posture == HERO_RIGHT) //右
	{
		m_angle = 180.0f;		//角度調整
		m_pos_x = 50.0f;	//X軸調整
		m_pos_y = 10.0f;		//Y軸調整
	}

	Hits::SetHitBox(this, m_x + m_pos_x, m_y + m_pos_y, 60.0f, 60.0f, ELEMENT_BEAMSABER, OBJ_BEAMSABER, 11);

}

//アクション
void CObjBeamSaber::Action()
{
	//ブロックの情報を持ってくる
	CObjBlock* pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//自身のHitBoxを持ってくる
	CHitBox* hit = Hits::GetHitBox(this);

	//フラグがオフの場合
	if (m_f == false)
	{
		//サウンドを鳴らす
		if (hit->CheckElementHit(ELEMENT_ENEMY) == true || hit->CheckElementHit(ELEMENT_NULL) == true)
		{
			Audio::Start(4);
		}		
		else
		{
			Audio::Start(3);
		}
		m_f = true;		//オンにして2重に鳴らないようにする
	}

	//攻撃アニメーション用---------------------------------------

	m_ani_time++;		//アニメーションタイムを進ませる
	if (m_ani_time > 4)	//タイムが4より多くなったら
	{
		m_ani_frame += 1;	//フレームを進める
		m_ani_time = 0;		//タイムを0に戻す
	}
	if (m_ani_frame == 5)	//アニメーションフレームが5になったら
	{
		this->SetStatus(false);    //自身に削除命令を出す
		Hits::DeleteHitBox(this);  //所有するHitBoxに削除する
	}

	//作成したHitBox更新用の入り口を取り出す
	hit->SetPos(m_x + m_pos_x + pb->GetScrollx(), m_y + m_pos_y + pb->GetScrolly());//入り口から新しい位置（主人公の位置）情報に置き換える
}

//ドロー
void CObjBeamSaber::Draw()
{
	//アニメーション
	int AniData[5] =
	{
		0,1,2,3,4,
	};
	//ブロックの情報を持ってくる
	CObjBlock* pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	float r[4] = { 1.0f,0.3f,0.3f,1.0f };
	float y[4] = { 1.0f,0.7f,0.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	//切り取り位置の設定
	src.m_top    =   0.0f;
	src.m_left   =   0.0f + (AniData[m_ani_frame] * 192.0f);
	src.m_right  = 192.0f + (AniData[m_ani_frame] * 192.0f);
	src.m_bottom = 192.0f;

	//表示位置の設定
	dst.m_top    =  0.0f + m_y + m_pos_y + pb->GetScrolly();
	dst.m_left   =  0.0f + m_x + m_pos_x + pb->GetScrollx();
	dst.m_right  = 64.0f + m_x + m_pos_x + pb->GetScrollx();
	dst.m_bottom = 64.0f + m_y + m_pos_y + pb->GetScrolly();

	//表示
	if (g_mp <= 0.0f)
	{
		Draw::Draw(2, &src, &dst, c, m_angle);
	}
	else if(g_hp <= 20.0f && g_skill == Libra)
		Draw::Draw(2, &src, &dst, r, m_angle);
	else if(g_hp <= 50.0f && g_skill == Libra)
		Draw::Draw(2, &src, &dst, y, m_angle);
	else 
		Draw::Draw(2, &src, &dst, c, m_angle);

}
