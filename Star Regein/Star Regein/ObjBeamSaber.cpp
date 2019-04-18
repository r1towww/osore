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
	

	//主人公の向きによってビームサーベルを出す方向，向きを変える
	if (g_posture == 3)	//下
	{
		m_angle = 90.0f;	//角度調整
		m_pos_x = 20.0f;		//X軸調整
		m_pos_y = 45.0f;	//Y軸調整
	}
	if (g_posture == 4)	//右
	{
		m_angle = 180.0f;		//角度調整
		m_pos_x = 38.0f;	//X軸調整
		m_pos_y = 14.0f;		//Y軸調整
	}
	if (g_posture == 2)	//左
	{
		m_angle = 0.0f;	//角度調整
		m_pos_x = -28.0f;	//X軸調整
		m_pos_y = 24.0f;		//Y軸調整
	}
	if (g_posture == 1)	//上
	{
		m_angle = 270.0f;	//角度調整
		m_pos_x = 10.0f;		//X軸調整
		m_pos_y = -25.0f;	//Y軸調整
	}
	//当たり判定をセット
	if (g_posture == 1)  //上
		Hits::SetHitBox(this, m_x + m_pos_x +10, m_y + m_pos_y, 40, 32, ELEMENT_BEAMSABER, OBJ_BEAMSABER, 1);
	else if(g_posture==2) //左
		Hits::SetHitBox(this, m_x + m_pos_x , m_y + m_pos_y , 32, 40, ELEMENT_BEAMSABER, OBJ_BEAMSABER, 1);
	else if(g_posture==3) //下
		Hits::SetHitBox(this, m_x + m_pos_x , m_y + m_pos_y+20 , 40, 32, ELEMENT_BEAMSABER, OBJ_BEAMSABER, 1);
	else if(g_posture==4) //右
		Hits::SetHitBox(this, m_x + m_pos_x +30, m_y + m_pos_y + 10, 32, 40, ELEMENT_BEAMSABER, OBJ_BEAMSABER, 1);



}

//アクション
void CObjBeamSaber::Action()
{
	//自身のHitBoxを持ってくる
	CHitBox* hit = Hits::GetHitBox(this);

	if (hit->CheckElementHit(ELEMENT_ENEMY) == true || hit->CheckElementHit(ELEMENT_NULL) == true )
	{
		Audio::Start(4);
	}
	else
	{
		Audio::Start(3);
	}

	//攻撃アニメーション用
	if (g_slash_time > 4)
	{
		g_slash_frame += 1;
		g_slash_time = 0;
	}
	if (g_slash_frame == 4)
	{
		g_slash_frame = 0;
	}

	//作成したHitBox更新用の入り口を取り出す
	hit->SetPos(m_x, m_y);//入り口から新しい位置（主人公の位置）情報に置き換える

	this->SetStatus(false);    //自身に削除命令を出す
	Hits::DeleteHitBox(this);  //主人公機が所有するHitBoxに削除する

}

//ドロー
void CObjBeamSaber::Draw()
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
	src.m_top = 0.0f;
	src.m_left = 0.0f + (AniData[g_slash_frame] * 200);
	src.m_right = 200.0f + (AniData[g_slash_frame] * 200);
	src.m_bottom = 200.0f;

	//表示位置の設定
	dst.m_top = 0.0f + m_y + m_pos_y;
	dst.m_left = 0.0f + m_x + m_pos_x;
	dst.m_right = 64.0f + m_x + m_pos_x;
	dst.m_bottom = 64.0f + m_y + m_pos_y;


	//表示
	Draw::Draw(2, &src, &dst, c, m_angle);
}
