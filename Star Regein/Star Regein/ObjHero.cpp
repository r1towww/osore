//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"


#include "GameHead.h"
#include "ObjHero.h"

//使用するネームスペース
using namespace GameL;

float g_posture;
int g_skill = Taurus;

//int g_ani_time;
//int g_ani_frame;

CObjHero::CObjHero(float x, float y)
{//オブジェ作成時に渡されたx,y座標をメンバ変数に代入
	m_px = x;
	m_py = y;
}

//イニシャライズ
void CObjHero::Init()
{
	m_vx = 0.0f;		//移動ベクトル
	m_vy = 0.0f;
	//初期姿勢
	g_posture = HERO_DOWN;

	//最大HPの初期化
	g_max_hp = 50.0f;
	//HPの初期化
	g_hp = 50.0f;

	//最大ＭＰの初期化
	g_max_mp = 50.0f;
	//ＭＰの初期化
	g_mp = 50.0f;

	//アニメーション用変数初期化
	m_ani_time = 0;
	m_ani_frame = 1;

	//blockとの衝突状態確認
	m_hit_up    = false;
	m_hit_down  = false;
	m_hit_left  = false;
	m_hit_right = false;

	//無敵時間初期化
	m_time = 100;

	//透明度初期化
	alpha = 1.0f;

	//ＭＰのタイムカウント用初期化
	m_MP_time = 0;

	//ＭＰリジェネカウント用初期化
	m_regene_time = 0;

	//キーフラグの初期化
	m_key_f = true;

	//ダッシュフラグ初期化
	m_dash_flag = false;
	//移動フラグ初期化
	m_dash_flag = false;
	//攻撃アニメーションフラグ初期化
	g_attack_flag = false;

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px+15, m_py +15, 50, 50, ELEMENT_PLAYER, OBJ_HERO, 1);
}

//アクション
void CObjHero::Action()
{
	//チュートリアルフラグが立っていないとき動くようにする
	if (g_tutorial_flag == false)
	{
		//移動ベクトルの破棄
		m_vx = 0.0f;
		m_vy = 0.0f;

	}
	


	//デバック用
	if (Input::GetVKey('O'))
	{
		Scene::SetScene(new CSceneStageChoice());
	}

//移動系統情報--------------------------------------------------

	if (Input::GetVKey(VK_UP))//矢印キー（上）が入力されたとき
	{
		m_move_flag = true;
		m_vy -= m_speed_power;
		g_posture = HERO_UP;
		m_ani_time += ANITIME;
	}
	else if (Input::GetVKey(VK_DOWN))//矢印キー（下）が入力されたとき
	{
		m_move_flag = true;
		m_vy += m_speed_power;
		g_posture = HERO_DOWN;
		m_ani_time += ANITIME;
	}
	else if (Input::GetVKey(VK_LEFT))//矢印キー（左）が入力されたとき
	{
		m_move_flag = true;
		m_vx -= m_speed_power;
		g_posture = HERO_LEFT;
		m_ani_time += ANITIME;
	}
	else if (Input::GetVKey(VK_RIGHT))//矢印キー（右）が入力されたとき
	{
		m_move_flag = true;
		m_vx += m_speed_power;
		g_posture = HERO_RIGHT;
		m_ani_time += ANITIME;
	}
	else//移動キーの入力が無い場合
	{
		m_ani_frame = 1;	//静止フレームにする
		m_ani_time = 0;		//アニメーション時間リセット
	}

//---------------------------------------------------------------

//通常攻撃情報---------------------------------------------------

	//Zキーが入力された場合	
	if (Input::GetVKey('Z'))
	{
		
		//ビームサーベルオブジェクト作成
		CObjBeamSaber* objb = new CObjBeamSaber(m_px, m_py);
		Objs::InsertObj(objb, OBJ_BEAMSABER, 2);

		//攻撃アニメーションフラグオン
		g_attack_flag = true;

		g_slash_time += ANITIME;
	}
	else
	{
		g_attack_flag = false;
		g_slash_frame = 1;
		g_slash_time = 0;

	}


//---------------------------------------------------------------

//スキル系統情報-------------------------------------------------

	//Shiftキーが入力されたらダッシュ
	if (Input::GetVKey(VK_SHIFT) && g_skill == Taurus
		&& g_Taurus == true && g_mp >= 1.0f)
	{
		//ダッシュフラグをオン
		m_dash_flag = true;

		if (m_move_flag == true)
		{
			m_MP_time++;
			if (m_MP_time > 60)
			{
				m_MP_time = 0;
				g_mp -= 5.0f;
			}
		}
		m_speed_power = DASH_SPEED;
	}
	else//通常速度
	{
		m_move_flag = false;
		m_dash_flag = false;
		m_speed_power = NORMAL_SPEED;
	}
	//Xキーが入力された場合、スキルを使用
	if (Input::GetVKey('X'))
	{
		if (m_key_f == true)
		{
			//天秤座の場合
			if (g_skill == Libra)
			{
				if (g_hp < g_max_hp)
				{
					g_mp -= 25.0f;	//mp消費
					g_hp += 10.0f;	//hp回復
				}
				g_mp -= 25.0f;	//mp消費
				g_hp += 10.0f;	//hp回復
			}
			//双子座の場合
			else if (g_skill == Gemini)
			{
				////サブ機オブジェクト作成
				//CObjSkillGemini* objg = new CObjSkillGemini(m_px, m_py);
				//Objs::InsertObj(objg, OBJ_SKILL_GEMINI, 2);
			}
			m_key_f = false;
		}
	}
	//Qキーが入力された場合
	else if (Input::GetVKey('Q'))
	{
		if (m_key_f == true)
		{
			g_skill += NEXTSKILL;	//スキルの画像を次へ送る
			m_key_f = false;
		}
	}
	else 
	{
		m_key_f = true;
	}

	//HPが最大を超えないようにする（回復スキル）
	if (g_hp >= g_max_hp)	//HPが最大を超えたら
	{
		g_hp = g_max_hp;	//最大HPに戻す
	}
	//MPが最大を超えないようにする（リジェネ）
	if (g_mp >= g_max_mp)	//MPが最大を超えたら
	{
		g_mp = g_max_mp;	//最大MPに戻す
	}
	//MPが0を下回らないようにする（スキルによるMPのオーバー）
	if(g_mp <= 0.0f)
	{
		g_mp = 0.0f;	//0に戻す
	}


	//MPが50以下になったら一定間隔で増える
	if (m_dash_flag == false)//ダッシュしていなかったら増える
	{
		if (g_mp < 50.0f)
		{
			m_regene_time++;
			if (m_regene_time > 30)
			{
				m_regene_time = 0;
				g_mp += 1.0f;
			}
		}
	}
	else if (m_dash_flag == true)
	{
		;
	}

//----------------------------------------------------------------

	//HitBoxの内容を更新
	CHitBox*hit = Hits::GetHitBox(this);

	//主人公とBLOCK系統との当たり判定
	if (hit->CheckElementHit(ELEMENT_BLOCK) == true)
	{
		//主人公がブロックとどの角度で当たっているのかを確認
		HIT_DATA** hit_data;							//当たった時の細かな情報を入れるための構造体
		hit_data = hit->SearchElementHit(ELEMENT_BLOCK);	//hit_dateに主人公と当たっている他全てのHitBoxとの情報を入れる
		float r = 0;

		for (int i = 0; i < 10; i++)
		{
			if (hit_data[i] != nullptr)
			{
				r = hit_data[i]->r;

				//角度で上下左右を判定
				if ((r <= 45 && r >= 0) || r >= 315)
				{
					m_vx = -0.15f; //右
				}
				if (r > 45 && r < 135)
				{
					m_vy = 0.15f;//上
				}
				if (r >= 135 && r < 225)
				{
					m_vx = 0.15f;//左
				}
				if (r >= 225 && r < 315)
				{
					m_vy = -0.15f; //下
				}
			}
		}
	}

	if (hit->CheckElementHit(ELEMENT_NULL) == true || hit->CheckElementHit(ELEMENT_ENEMY))
	{
		//敵が主人公とどの角度で当たっているかを確認
		HIT_DATA**hit_data;							//当たった時の細かな情報を入れるための構造体
		hit_data = hit->SearchElementHit(ELEMENT_NULL);//hit_dataに主人公と当たっている他全てのHitBoxとの情報を入れる
		//hit_data = hit->SearchElementHit(ELEMENT_ENEMY);

		for (int i = 0; i < 10; i++)
		{
			if (hit_data[i] == nullptr)
				continue;

			float r = hit_data[i]->r;

			if ((r < 45 && r >= 0) || r > 315)
			{
				m_vx = -10.0f;//左に移動させる
			}
			if (r >= 45 && r < 135)
			{
				m_vy = 10.0f;//上に移動させる
			}
			if (r >= 135 && r < 225)
			{
				m_vx = 10.0f;//右に移動させる
			}
			if (r >= 225 && r < 315)
			{
				m_vy = -10.0f;//したに移動させる
			}
		}

		g_hp -= 10.0f;
		m_f = true;
		m_key_f = true;
		hit->SetInvincibility(true);
	}

	if (m_f == true)
	{
		m_time--;
		alpha = 0.5f;

	}
	if (m_time <= 0)
	{
		m_f = false;
		hit->SetInvincibility(false);
		alpha = 1.0f;

		m_time = 100;
	}

	//移動アニメーション用
	if (m_ani_time > 4)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}
	if (m_ani_frame == 4)
	{
		m_ani_frame = 0;
	}

	//ブラックホールと接触した場合
	CObjBlackhole* blackhole = (CObjBlackhole*)Objs::GetObj(OBJ_BLACKHOLE);

	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//ブラックホールの数forループを回す
	for (int i = 0; i < 4; i++)
	{
		//ブラックホールと当たった場合
		if (hit->CheckObjNameHit(OBJ_BLACKHOLE + i) != nullptr)
		{
			//同じ値のホワイトホール位置に移動させる
			block->SetScrollx(-g_whitehole_x[i][0] + m_px);
			block->SetScrolly(-g_whitehole_y[i][0] + m_py);
		}
	}

	//ブロックとの当たり判定実行	
	block->BlockHit(&m_px, &m_py, true,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy
	);

		//位置の更新
		m_px += m_vx;
		m_py += m_vy;

	

	//作成したHitBox更新用の入り口を取り出す
	hit->SetPos(m_px + 15, m_py + 15);//入り口から新しい位置（主人公の位置）情報に置き換える

	//HPが０になったら削除
	if (g_hp <= 0.0f)
	{
		this->SetStatus(false);    //自身に削除命令を出す
		Hits::DeleteHitBox(this);  //主人公機が所有するHitBoxに削除する
		Scene::SetScene(new CSceneGameOver());
	}
}


//ドロー
void CObjHero::Draw()
{
	//アニメーション
	int AniData[5] =
	{
		0,1,2,3,0,
	};

	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,alpha };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	//ブロック情報を持ってくる
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//切り取り位置の設定
	src.m_top = 64.0f * g_posture;
	src.m_left = 0.0f + (AniData[m_ani_frame] * 64);
	src.m_right = 64.0f + (AniData[m_ani_frame] * 64);
	src.m_bottom = src.m_top + 64.0f;

	//表示位置の設定
	dst.m_top = 0.0f + m_py;
	dst.m_left = 80.0f + m_px;
	dst.m_right = 0.0f + m_px;
	dst.m_bottom = 80.0f + m_py;

	//表示
	Draw::Draw(1, &src, &dst, c, 0.0f);
}
