//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

//使用するヘッダーファイル
#include "GameHead.h"
#include "ObjBeamSaber.h"

//使用するネームスペース
using namespace GameL;

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
		m_angle = 270.0f;	//角度調整
		m_pos_x = 20.0f;		//X軸調整
		m_pos_y = 64.0f;	//Y軸調整
	}
	if (g_posture == 4)	//右
	{
		m_angle = 0.0f;		//角度調整
		m_pos_x = 48.0f;	//X軸調整
		m_pos_y = 24.0f;		//Y軸調整
	}
	if (g_posture == 2)	//左
	{
		m_angle = 180.0f;	//角度調整
		m_pos_x = -18.0f;	//X軸調整
		m_pos_y = 24.0f;		//Y軸調整
	}
	if (g_posture == 1)	//上
	{
		m_angle = 90.0f;	//角度調整
		m_pos_x = 10.0f;		//X軸調整
		m_pos_y = -28.0f;	//Y軸調整
	}
	//当たり判定をセット
	if(g_posture == 0 || g_posture == 3)
		Hits::SetHitBox(this, m_x + m_pos_x +5, m_y + m_pos_y, 20, 32, ELEMENT_BEAMSABER, OBJ_BEAMSABER, 1);
	else
		Hits::SetHitBox(this, m_x + m_pos_x + 5, m_y + m_pos_y+5, 32, 20, ELEMENT_BEAMSABER, OBJ_BEAMSABER, 1);

}

//アクション
void CObjBeamSaber::Action()
{
	//自身のHitBoxを持ってくる
	CHitBox* hit = Hits::GetHitBox(this);

	//作成したHitBox更新用の入り口を取り出す
	hit->SetPos(m_x, m_y);//入り口から新しい位置（主人公の位置）情報に置き換える
	
	this->SetStatus(false);    //自身に削除命令を出す
	Hits::DeleteHitBox(this);  //主人公機が所有するHitBoxに削除する

}

//ドロー
void CObjBeamSaber::Draw()
{


	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	//切り取り位置の設定
	src.m_top    = 0.0f;
	src.m_left   = 0.0f;
	src.m_right  = 32.0f;
	src.m_bottom = 32.0f;

	//表示位置の設定
	dst.m_top    =  0.0f + m_y + m_pos_y;
	dst.m_left   =  0.0f + m_x + m_pos_x;
	dst.m_right  = 32.0f + m_x + m_pos_x;
	dst.m_bottom = 32.0f + m_y + m_pos_y;
	

	//表示
	Draw::Draw(2, &src, &dst, c, m_angle);
}
