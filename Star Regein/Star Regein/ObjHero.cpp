//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"


#include "GameHead.h"
#include "ObjHero.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

float g_posture;
int g_skill = Taurus;

//int g_ani_time;
//int g_ani_frame;

CObjHero::CObjHero(float x, float y)
{//�I�u�W�F�쐬���ɓn���ꂽx,y���W�������o�ϐ��ɑ��
	m_px = x;
	m_py = y;
}

//�C�j�V�����C�Y
void CObjHero::Init()
{
	m_vx = 0.0f;		//�ړ��x�N�g��
	m_vy = 0.0f;
	//�����p��
	g_posture = HERO_DOWN;

	//�ő�HP�̏�����
	g_max_hp = 50.0f;
	//HP�̏�����
	g_hp = 50.0f;

	//�ő�l�o�̏�����
	g_max_mp = 50.0f;
	//�l�o�̏�����
	g_mp = 50.0f;

	//�A�j���[�V�����p�ϐ�������
	m_ani_time = 0;
	m_ani_frame = 1;

	//block�Ƃ̏Փˏ�Ԋm�F
	m_hit_up    = false;
	m_hit_down  = false;
	m_hit_left  = false;
	m_hit_right = false;

	//���G���ԏ�����
	m_time = 100;

	//�����x������
	alpha = 1.0f;

	//�l�o�̃^�C���J�E���g�p������
	m_MP_time = 0;

	//�l�o���W�F�l�J�E���g�p������
	m_regene_time = 0;

	//�L�[�t���O�̏�����
	m_key_f = true;

	//�_�b�V���t���O������
	m_dash_flag = false;
	//�ړ��t���O������
	m_dash_flag = false;
	//�U���A�j���[�V�����t���O������
	g_attack_flag = false;

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px+15, m_py +15, 50, 50, ELEMENT_PLAYER, OBJ_HERO, 1);
}

//�A�N�V����
void CObjHero::Action()
{
	//�`���[�g���A���t���O�������Ă��Ȃ��Ƃ������悤�ɂ���
	if (g_tutorial_flag == false)
	{
		//�ړ��x�N�g���̔j��
		m_vx = 0.0f;
		m_vy = 0.0f;

	}
	


	//�f�o�b�N�p
	if (Input::GetVKey('O'))
	{
		Scene::SetScene(new CSceneStageChoice());
	}

//�ړ��n�����--------------------------------------------------

	if (Input::GetVKey(VK_UP))//���L�[�i��j�����͂��ꂽ�Ƃ�
	{
		m_move_flag = true;
		m_vy -= m_speed_power;
		g_posture = HERO_UP;
		m_ani_time += ANITIME;
	}
	else if (Input::GetVKey(VK_DOWN))//���L�[�i���j�����͂��ꂽ�Ƃ�
	{
		m_move_flag = true;
		m_vy += m_speed_power;
		g_posture = HERO_DOWN;
		m_ani_time += ANITIME;
	}
	else if (Input::GetVKey(VK_LEFT))//���L�[�i���j�����͂��ꂽ�Ƃ�
	{
		m_move_flag = true;
		m_vx -= m_speed_power;
		g_posture = HERO_LEFT;
		m_ani_time += ANITIME;
	}
	else if (Input::GetVKey(VK_RIGHT))//���L�[�i�E�j�����͂��ꂽ�Ƃ�
	{
		m_move_flag = true;
		m_vx += m_speed_power;
		g_posture = HERO_RIGHT;
		m_ani_time += ANITIME;
	}
	else//�ړ��L�[�̓��͂������ꍇ
	{
		m_ani_frame = 1;	//�Î~�t���[���ɂ���
		m_ani_time = 0;		//�A�j���[�V�������ԃ��Z�b�g
	}

//---------------------------------------------------------------

//�ʏ�U�����---------------------------------------------------

	//Z�L�[�����͂��ꂽ�ꍇ	
	if (Input::GetVKey('Z'))
	{
		
		//�r�[���T�[�x���I�u�W�F�N�g�쐬
		CObjBeamSaber* objb = new CObjBeamSaber(m_px, m_py);
		Objs::InsertObj(objb, OBJ_BEAMSABER, 2);

		//�U���A�j���[�V�����t���O�I��
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

//�X�L���n�����-------------------------------------------------

	//Shift�L�[�����͂��ꂽ��_�b�V��
	if (Input::GetVKey(VK_SHIFT) && g_skill == Taurus
		&& g_Taurus == true && g_mp >= 1.0f)
	{
		//�_�b�V���t���O���I��
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
	else//�ʏ푬�x
	{
		m_move_flag = false;
		m_dash_flag = false;
		m_speed_power = NORMAL_SPEED;
	}
	//X�L�[�����͂��ꂽ�ꍇ�A�X�L�����g�p
	if (Input::GetVKey('X'))
	{
		if (m_key_f == true)
		{
			//�V�����̏ꍇ
			if (g_skill == Libra)
			{
				if (g_hp < g_max_hp)
				{
					g_mp -= 25.0f;	//mp����
					g_hp += 10.0f;	//hp��
				}
				g_mp -= 25.0f;	//mp����
				g_hp += 10.0f;	//hp��
			}
			//�o�q���̏ꍇ
			else if (g_skill == Gemini)
			{
				////�T�u�@�I�u�W�F�N�g�쐬
				//CObjSkillGemini* objg = new CObjSkillGemini(m_px, m_py);
				//Objs::InsertObj(objg, OBJ_SKILL_GEMINI, 2);
			}
			m_key_f = false;
		}
	}
	//Q�L�[�����͂��ꂽ�ꍇ
	else if (Input::GetVKey('Q'))
	{
		if (m_key_f == true)
		{
			g_skill += NEXTSKILL;	//�X�L���̉摜�����֑���
			m_key_f = false;
		}
	}
	else 
	{
		m_key_f = true;
	}

	//HP���ő�𒴂��Ȃ��悤�ɂ���i�񕜃X�L���j
	if (g_hp >= g_max_hp)	//HP���ő�𒴂�����
	{
		g_hp = g_max_hp;	//�ő�HP�ɖ߂�
	}
	//MP���ő�𒴂��Ȃ��悤�ɂ���i���W�F�l�j
	if (g_mp >= g_max_mp)	//MP���ő�𒴂�����
	{
		g_mp = g_max_mp;	//�ő�MP�ɖ߂�
	}
	//MP��0�������Ȃ��悤�ɂ���i�X�L���ɂ��MP�̃I�[�o�[�j
	if(g_mp <= 0.0f)
	{
		g_mp = 0.0f;	//0�ɖ߂�
	}


	//MP��50�ȉ��ɂȂ�������Ԋu�ő�����
	if (m_dash_flag == false)//�_�b�V�����Ă��Ȃ������瑝����
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

	//HitBox�̓��e���X�V
	CHitBox*hit = Hits::GetHitBox(this);

	//��l����BLOCK�n���Ƃ̓����蔻��
	if (hit->CheckElementHit(ELEMENT_BLOCK) == true)
	{
		//��l�����u���b�N�Ƃǂ̊p�x�œ������Ă���̂����m�F
		HIT_DATA** hit_data;							//�����������ׂ̍��ȏ������邽�߂̍\����
		hit_data = hit->SearchElementHit(ELEMENT_BLOCK);	//hit_date�Ɏ�l���Ɠ������Ă��鑼�S�Ă�HitBox�Ƃ̏�������
		float r = 0;

		for (int i = 0; i < 10; i++)
		{
			if (hit_data[i] != nullptr)
			{
				r = hit_data[i]->r;

				//�p�x�ŏ㉺���E�𔻒�
				if ((r <= 45 && r >= 0) || r >= 315)
				{
					m_vx = -0.15f; //�E
				}
				if (r > 45 && r < 135)
				{
					m_vy = 0.15f;//��
				}
				if (r >= 135 && r < 225)
				{
					m_vx = 0.15f;//��
				}
				if (r >= 225 && r < 315)
				{
					m_vy = -0.15f; //��
				}
			}
		}
	}

	if (hit->CheckElementHit(ELEMENT_NULL) == true || hit->CheckElementHit(ELEMENT_ENEMY))
	{
		//�G����l���Ƃǂ̊p�x�œ������Ă��邩���m�F
		HIT_DATA**hit_data;							//�����������ׂ̍��ȏ������邽�߂̍\����
		hit_data = hit->SearchElementHit(ELEMENT_NULL);//hit_data�Ɏ�l���Ɠ������Ă��鑼�S�Ă�HitBox�Ƃ̏�������
		//hit_data = hit->SearchElementHit(ELEMENT_ENEMY);

		for (int i = 0; i < 10; i++)
		{
			if (hit_data[i] == nullptr)
				continue;

			float r = hit_data[i]->r;

			if ((r < 45 && r >= 0) || r > 315)
			{
				m_vx = -10.0f;//���Ɉړ�������
			}
			if (r >= 45 && r < 135)
			{
				m_vy = 10.0f;//��Ɉړ�������
			}
			if (r >= 135 && r < 225)
			{
				m_vx = 10.0f;//�E�Ɉړ�������
			}
			if (r >= 225 && r < 315)
			{
				m_vy = -10.0f;//�����Ɉړ�������
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

	//�ړ��A�j���[�V�����p
	if (m_ani_time > 4)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}
	if (m_ani_frame == 4)
	{
		m_ani_frame = 0;
	}

	//�u���b�N�z�[���ƐڐG�����ꍇ
	CObjBlackhole* blackhole = (CObjBlackhole*)Objs::GetObj(OBJ_BLACKHOLE);

	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�u���b�N�z�[���̐�for���[�v����
	for (int i = 0; i < 4; i++)
	{
		//�u���b�N�z�[���Ɠ��������ꍇ
		if (hit->CheckObjNameHit(OBJ_BLACKHOLE + i) != nullptr)
		{
			//�����l�̃z���C�g�z�[���ʒu�Ɉړ�������
			block->SetScrollx(-g_whitehole_x[i][0] + m_px);
			block->SetScrolly(-g_whitehole_y[i][0] + m_py);
		}
	}

	//�u���b�N�Ƃ̓����蔻����s	
	block->BlockHit(&m_px, &m_py, true,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy
	);

		//�ʒu�̍X�V
		m_px += m_vx;
		m_py += m_vy;

	

	//�쐬����HitBox�X�V�p�̓���������o��
	hit->SetPos(m_px + 15, m_py + 15);//���������V�����ʒu�i��l���̈ʒu�j���ɒu��������

	//HP���O�ɂȂ�����폜
	if (g_hp <= 0.0f)
	{
		this->SetStatus(false);    //���g�ɍ폜���߂��o��
		Hits::DeleteHitBox(this);  //��l���@�����L����HitBox�ɍ폜����
		Scene::SetScene(new CSceneGameOver());
	}
}


//�h���[
void CObjHero::Draw()
{
	//�A�j���[�V����
	int AniData[5] =
	{
		0,1,2,3,0,
	};

	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,alpha };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	//�u���b�N���������Ă���
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�؂���ʒu�̐ݒ�
	src.m_top = 64.0f * g_posture;
	src.m_left = 0.0f + (AniData[m_ani_frame] * 64);
	src.m_right = 64.0f + (AniData[m_ani_frame] * 64);
	src.m_bottom = src.m_top + 64.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py;
	dst.m_left = 80.0f + m_px;
	dst.m_right = 0.0f + m_px;
	dst.m_bottom = 80.0f + m_py;

	//�\��
	Draw::Draw(1, &src, &dst, c, 0.0f);
}
