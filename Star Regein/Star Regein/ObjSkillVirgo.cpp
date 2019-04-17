//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

//使用するヘッダーファイル
#include "GameHead.h"
#include "ObjSkillVirgo.h"

//使用するネームスペース
using namespace GameL;


//コンストラクタ
CObjSkillVirgo::CObjSkillVirgo(float x, float y)
{
	m_x = x;
	m_y = y;
}

//イニシャライズ
void CObjSkillVirgo::Init()
{
	//移動量の初期化
	m_vx = 0.0f;
	m_vy = 0.0f;

	//弾削除のカウント初期化
	m_time = 0.0f;


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
		Hits::SetHitBox(this, m_x+m_pos_x , m_y+m_pos_y, 32, 28, ELEMENT_VIRGO_SKILL, OBJ_SKILL_VIRGO, 1);
	else if (g_posture == 2) //左
		Hits::SetHitBox(this, m_x + m_pos_x, m_y+m_pos_y , 32, 28, ELEMENT_VIRGO_SKILL, OBJ_SKILL_VIRGO, 1);
	else if (g_posture == 3) //下
		Hits::SetHitBox(this, m_x + m_pos_x, m_y+m_pos_y , 32, 28, ELEMENT_VIRGO_SKILL, OBJ_SKILL_VIRGO, 1);
	else if (g_posture == 4) //右
		Hits::SetHitBox(this, m_x + m_pos_x, m_y+m_pos_y, 32, 28, ELEMENT_VIRGO_SKILL, OBJ_SKILL_VIRGO, 1);

}

//アクション
void CObjSkillVirgo::Action()
{

	//自身のHitBoxを持ってくる
	CHitBox* hit = Hits::GetHitBox(this);


	if (g_posture == 1)//上
	{
		m_vy += MOVE;
		m_y -= m_vy;
	}
	else if (g_posture == 2)//左
	{
		m_vx += MOVE;
		m_x -= m_vx;
	}
	else if (g_posture == 3)//下
	{
		m_vy += MOVE;
		m_y += m_vy;
	}
	else if (g_posture == 4)//右
	{
		m_vx += MOVE;
		m_x += m_vx;
	}



	//作成したHitBox更新用の入り口を取り出す
	hit->SetPos(m_x+m_pos_x, m_y+m_pos_y);//入り口から新しい位置（主人公の位置）情報に置き換える

	m_time++;

	if (m_time >= 20)
	{
		m_time = 0.0f;

		this->SetStatus(false);    //自身に削除命令を出す
		Hits::DeleteHitBox(this);  //主人公機が所有するHitBoxに削除する
	}
}
//ドロー
void CObjSkillVirgo::Draw()
{

	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置


	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 32.0f;
	src.m_bottom = 28.0f;

	//表示位置の設定
	dst.m_top = 0.0f + m_y + m_pos_y;
	dst.m_left = 0.0f + m_x + m_pos_x;
	dst.m_right = 32.0f + m_x + m_pos_x;
	dst.m_bottom = 32.0f + m_y + m_pos_y;

	//表示
	Draw::Draw(20, &src, &dst, c,0.0f);
}
