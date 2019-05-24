//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjHero.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

float g_posture;
int g_skill = NoSkill;
int g_attack_power = 1;

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

	m_SE_on = 0;
	//�����p��
	if (g_Boss_Spawn == true)
	{
		g_posture = HERO_UP;
	}
	else
	{
		g_posture = HERO_DOWN;
	}
	//�ő�HP�̏�����
	g_max_hp = 100.0f;
	//HP�̏�����
	g_hp = 100.0f;

	//�ő�l�o�̏�����
	g_max_mp = 100.0f;
	//�l�o�̏�����
	g_mp = 100.0f;

	//�A�j���[�V�����p�ϐ�������
	m_ani_time = 0;
	m_ani_frame = 1;

	//block�Ƃ̏Փˏ�Ԋm�F
	m_hit_up    = false;
	m_hit_down  = false;
	m_hit_left  = false;
	m_hit_right = false;

	//���G�t���O������
	m_invincible_flag = false;
	//���G���ԏ�����
	m_time = 100;

	//�����x������
	m_alpha = ALPHAORIGIN;

	//�l�o�̃^�C���J�E���g�p������
	m_MP_time = 0;

	//�l�o���W�F�l�J�E���g�p������
	m_regene_time = 0;

	//HP���W�F�l�J�E���g�p������
	m_hp_regene_time = 0;

	//�Ώ��p������
	m_burn_time = 0;
	//�Ώ����v�p������
	m_burn_max_time = 0;

	//�L�[�t���O�̏�����
	m_key_f = true;
	m_help_key_f = true;
	//�_�b�V���t���O������
	m_dash_flag = false;
	m_cool_flag = false;
	m_cool_time = 0;

	m_dash_eff_f = false;

	//�U������t���O
	m_a_flag = true;
	//�U���͂̏�����
	g_attack_power = 1;

	//���S�t���O
	dead_flag = false;

	//���q�U���q�b�g�t���O
	m_eff_flag = false;
	m_libra_eff_f = false;
	m_menu_key_f = false;

	//�Ώ�����l���J���[�ύX�p�t���O
	m_burn_f =false;
	//�Ŏ���l���J���[�ύX�p�t���O
	m_poison_f = false;

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px+15, m_py +15, 50, 50, ELEMENT_PLAYER, OBJ_HERO, 1);

	m_ani = 0;			//�A�j���[�V�����p
	m_ani2 = 0;
	m_ani3 = 0;
	m_ani_time = 0;		//�A�j���[�V�����Ԋu�^�C��
	m_eff_time = 0;
	m_eff_time2 = 0;
	m_eff_time3 = 0;
	m_eff.m_top    = 0;		//�G�t�F�N�g�̏�����
	m_eff.m_left   = 0;	
	m_eff.m_right  = 240;
	m_eff.m_bottom = 240;
	m_eff2.m_top = 0;		//�G�t�F�N�g�̏�����
	m_eff2.m_left = 0;
	m_eff2.m_right = 192;
	m_eff2.m_bottom = 192;
	m_eff3.m_top = 0;		//���S�G�t�F�N�g�̏�����
	m_eff3.m_left = 0;
	m_eff3.m_right = 192;
	m_eff3.m_bottom = 192;

}

//�A�N�V����
void CObjHero::Action()
{
	//�V�[���؂�ւ��Ɏg�p
	if (m_alpha >= 1.0f)
	{
		m_alpha = 1.0f;
	}
	else
	{
		m_alpha += 0.03;
	}

	//�u���b�N�z�[���̐�������
	if (g_stage == VenusLibra) {	//�V����
		m_blackhole_num = 4;
	}
	else if (g_stage == MercuryVirgo) {	//������
		m_blackhole_num = 2;
	}
	else if (g_stage == SunLeo) {	//���q��
		m_blackhole_num = 2;
	}
	else
	{
		m_blackhole_num = 0;
	}

	//�X�e�[�W�N���A�̏��������Ă���
	CObjStageClear* objclear = (CObjStageClear*)Objs::GetObj(OBJ_STAGECLEAR);
	//�`���[�g���A���t���O�A���쐧��p�t���O�������Ă��Ȃ��Ƃ������悤�ɂ���
	if (g_tutorial_flag == true || g_move_stop_flag == true || objclear != nullptr)
	{
		m_vx = 0.0f;
		m_vy = 0.0f;
		return;
	}
	//�ړ��x�N�g���̔j��
	m_vx = 0.0f;
	m_vy = 0.0f;

		//�f�o�b�N�p
		if (Input::GetVKey('L'))
		{
			g_hp -= 1.0f;
		}
		//�f�o�b�N�p
		if (Input::GetVKey('K'))
		{
			g_hp += 1.0f;
		}
		//�f�o�b�N�p
		if (Input::GetVKey('J'))
		{
			g_mp += 1.0f;
		}
		if (Input::GetVKey('W'))
		{
			//�I�u�W�F�N�g�쐬
			CObjStageClear* objs = new CObjStageClear();
			Objs::InsertObj(objs, OBJ_STAGECLEAR, 130);
		}
		if (Input::GetVKey('T'))
		{
			g_mp -= 1.0f;
		}

		//�ړ��n�����--------------------------------------------------

	if (Input::GetVKey(VK_UP))//���L�[�i��j�����͂��ꂽ�Ƃ�
	{
		m_vy -= m_speed_power;
		m_dash_flag = true;
		g_posture = HERO_UP;
		m_ani_time += ANITIME;
	}
	else if (Input::GetVKey(VK_DOWN))//���L�[�i���j�����͂��ꂽ�Ƃ�
	{
		m_vy += m_speed_power;
		m_dash_flag = true;
		g_posture = HERO_DOWN;
		m_ani_time += ANITIME;
	}
	else if (Input::GetVKey(VK_LEFT))//���L�[�i���j�����͂��ꂽ�Ƃ�
	{
		m_vx -= m_speed_power;
		m_dash_flag = true;
		g_posture = HERO_LEFT;
		m_ani_time += ANITIME;
	}
	else if (Input::GetVKey(VK_RIGHT))//���L�[�i�E�j�����͂��ꂽ�Ƃ�
	{
		m_vx += m_speed_power;
		m_dash_flag = true;
		g_posture = HERO_RIGHT;
		m_ani_time += ANITIME;
	}
	else//�ړ��L�[�̓��͂������ꍇ
	{
		//�����Ă��Ȃ��Ƃ��ɏ�����
		m_dash_flag = false;
		m_ani_frame = 1;	//�Î~�t���[���ɂ���
		m_ani_time = 0;		//�A�j���[�V�������ԃ��Z�b�g
	}

	//---------------------------------------------------------------

	//�ʏ�U�����---------------------------------------------------

	//Z�L�[�����͂��ꂽ�ꍇ	
	if (Input::GetVKey('Z'))
	{
		if (m_a_flag == true)
		{

			//�u���b�N���������Ă���
			CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

			//�r�[���T�[�x���I�u�W�F�N�g�쐬
			CObjBeamSaber* objb = new CObjBeamSaber(m_px - block ->GetScrollx(), m_py - block->GetScrolly());
			Objs::InsertObj(objb, OBJ_BEAMSABER, 2);

			m_a_flag = false;
		}
	}
	else
	{
		m_a_flag = true;
	}


	//---------------------------------------------------------------

	//�X�L���n�����-------------------------------------------------

		//X�L�[�����͂��ꂽ��_�b�V��
		if (Input::GetVKey('X') && g_skill == Taurus
			&& g_Taurus == true && m_dash_flag==true && m_cool_flag == false)
		{
			//�_�b�V���G�t�F�N�g���t���O���I�t�̏ꍇ�G�t�F�N�g����炷
			if (m_dash_eff_f == false)
			{
				Audio::Start(11);
				m_dash_eff_f = true;
			}
				m_MP_time++;
				if (m_MP_time > 15)
				{
					m_MP_time = 0;
					g_mp -= 1.0f;
				}
			m_speed_power = DASH_SPEED;

		//�_�b�V���G�t�F�N�g�p����------------------------------
		RECT_F ani_src[6] =
		{
			{   0,    0,  240, 240 },
			{   0,  240,  480, 240 },
			{   0,  480,  720, 240 },
			{ 240,    0,  240, 480 },
			{ 240,  240,  480, 480 },
			{ 240,  480,  720, 480 },
		};
		
		//�_�b�V���G�t�F�N�g�̃R�}�Ԋu����
		if (m_eff_time > 4)
		{
			m_ani++;		//�_�b�V���G�t�F�N�g�̃R�}��1�i�߂�
			m_eff_time = 0;

			m_eff = ani_src[m_ani];//�_�b�V���G�t�F�N�g��RECT�z�񂩂�m_ani�Ԗڂ�RECT���擾
		}
		else
		{
			m_eff_time++;	//�G�t�F�N�g�^�C�����v���X
		}
		// 5�Ԗځi�摜�Ō�j�܂Ői�񂾂�A0�ɖ߂�
		if (m_ani == 5)
		{
			m_ani = 0;
			m_eff_time = 0;
		}
	}
	else//�ʏ푬�x
	{	
		Audio::Stop(11);	//�_�b�V�������Ă��Ȃ��ۃG�t�F�N�g�����~�߂�
		m_dash_eff_f = false;	//�_�b�V���G�t�F�N�g���t���O���I�t�ɂ���(������悤�ɂ���)
		m_dash_flag = false;
		m_speed_power = NORMAL_SPEED;
	}

	//MP��0�ɂȂ�����1�Q�[�W�񕜂���܂Ŏg�p�s��
	if (g_mp == 0.0f)
		m_cool_flag = true;

	if (m_cool_flag == true)
	{
		m_cool_time++;
		if (m_cool_time >= 200)
		{
			m_cool_time = 0;
			m_cool_flag = false;
		}
	}

	//�V�����̏ꍇ�i�p�b�V�u�j
	if (g_skill == Libra)
	{
		//�G�t�F�N�g���P�x�����o���悤�ɂ���
		if (m_libra_eff_f == false)
		{
			m_libra_eff_f = true;	//true�ɂ��ē���Ȃ��p��
			//�V���G�t�F�N�g�̍쐬
			CObjSkillLibra* libra = new CObjSkillLibra(m_px, m_py);
			Objs::InsertObj(libra, OBJ_SKILL_LIBRA, 11);
		}
		//�c��HP�ɉ����čU���͂�ύX
		if (g_mp <= 0.0f)
		{
			g_attack_power = 1;
		}
		else if (g_hp <= 20.0f)	//20.0f�ȉ�
		{
			g_attack_power = 5;	//�U���͕ύX
		}
		else if (g_hp <= 50.0f) //50.0f�ȉ�
		{
			g_attack_power = 3;	//�U���͕ύX
		}
		else if (g_hp > 50.0f)//����ȊO�i50.0f���傫���ꍇ�j
		{
			g_attack_power = 2;	//�U���͕ύX
		}
	}
	else
	{
		m_libra_eff_f = false;	//�t���O��߂�
	}

	//X�L�[�����͂��ꂽ�ꍇ�A�X�L�����g�p
	if (Input::GetVKey('X'))
	{
		if (m_key_f == true)
		{
			//�o�q���̏ꍇ
			if (g_skill == Gemini&& g_gemini_check == false && g_mp == g_max_mp)
			{
				//�u���b�N���������Ă���
				CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

				//�T�u�@�I�u�W�F�N�g�쐬
				CObjSkillGemini* objg = new CObjSkillGemini(m_px - block->GetScrollx(), m_py - block->GetScrolly());
				Objs::InsertObj(objg, OBJ_SKILL_GEMINI, 20);
				//�T�u�@�I�u�W�F�N�g�쐬
				CObjSkillGeminiB* objgb = new CObjSkillGeminiB(m_px - block->GetScrollx(), m_py - block->GetScrolly());
				Objs::InsertObj(objgb, OBJ_SKILL_GEMINIB, 20);
				g_mp -= g_max_mp;	//mp����
				g_gemini_check = true;
			}
			//�������̏ꍇ
			else if (g_skill == Virgo && g_mp >= 10.0f && g_Virgo == true && g_mp >= 30.0f)
			{
				//�u���b�N���������Ă���
				CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

				//�n�[�g�e�I�u�W�F�N�g�쐬
				CObjSkillVirgo* objv = new CObjSkillVirgo(m_px - block->GetScrollx(), m_py - block->GetScrolly());
				Objs::InsertObj(objv, OBJ_SKILL_VIRGO, 100);

				g_mp -= 50.0f;	//mp����

			}
			//���q���̏ꍇ
			else if (g_skill == Leo && g_Leo == true && g_mp >= 30.0f)
			{
				//�X�^���I�u�W�F�N�g�쐬
				CObjSkillLeo* objl = new CObjSkillLeo(m_px, m_py);
				Objs::InsertObj(objl, OBJ_SKILL_LEO, 20);
				Audio::Start(16);
				g_mp -= 30.0f;
			}
			m_key_f = false;
		}
	}
	//C�L�[�����͂��ꂽ�ꍇ
	else if (Input::GetVKey('C'))
	{
		if (m_key_f == true)
		{
			Audio::Start(1);	//�G�t�F�N�g����炷
			g_skill -= NEXTSKILL;	//�X�L���̉摜�����֑���
			m_key_f = false;
		}
	}
	else if (Input::GetVKey('V'))
	{
		if (m_key_f == true)
		{
			Audio::Start(1);	//�G�t�F�N�g����炷
			g_skill += NEXTSKILL;	//�X�L���̉摜�����֑���
			m_key_f = false;
		}
	}
	else
	{
		m_key_f = true;
	}

	//�{�X��̏ꍇ�A���̏�ɂ���Ƃ�HP������
	if (g_Boss_Spawn == true && g_stage == EarthStar)
	{
		//���g��HitBox�������Ă���
		CHitBox* hit = Hits::GetHitBox(this);
		if (hit->CheckObjNameHit(OBJ_STAR) != nullptr)
		{

			if (g_hp < 100.0f)
			{

				m_hp_regene_time++;
				if (m_hp_regene_time > 15)
				{
					m_hp_regene_time = 0;
					g_hp += 1.0f;
					Audio::Start(24);

				}
			}
		}
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
	//HP��0�������Ȃ��悤�ɂ���i�Ώ��ɂ��HP�̃I�[�o�[�j
	if (g_hp <= 0.0f)
	{
		g_hp = 0.0f;
	}
	//MP��0�������Ȃ��悤�ɂ���i�X�L���ɂ��MP�̃I�[�o�[�j
	if (g_mp <= 0.0f)
	{
		g_mp = 0.0f;	//0�ɖ߂�
	}


	//MP��100�����ɂȂ�������Ԋu�ő�����i���W�F�l�j
	if (m_dash_flag == false && g_skill != Libra)//�I���X�L����Libra����Ȃ��A�_�b�V�����Ă��Ȃ������瑝����
	{
		if (g_mp < 100.0f)
		{
			m_regene_time++;
			if (m_regene_time > 15)
			{
				m_regene_time = 0;
				g_mp += 1.0f;
			}
		}
	}

	//----------------------------------------------------------------

		//�w���v�̏��������Ă���
		CObjHelp* objhelp = (CObjHelp*)Objs::GetObj(OBJ_HELP);
		//�w���v�I�u�W�F�N�g�����݂���ꍇ�A���͂̋���
		if (objhelp == nullptr)
		{
			//H�L�[�����͂��ꂽ�ꍇ
			if (Input::GetVKey('H'))
			{
				if (m_help_key_f == true)
				{
					Audio::Start(1);	//�G�t�F�N�g����炷
					//HELP�I�u�W�F�N�g���쐬
					CObjHelp *objhelp = new CObjHelp();
					Objs::InsertObj(objhelp, OBJ_HELP, 150);
					m_help_key_f = false;
				}
			}
			else
			{
				m_help_key_f = true;
			}
		}

		//Q�L�[�����͂��ꂽ�ꍇ
		if (Input::GetVKey('Q'))
		{
			if (m_menu_key_f == true)
			{
				Audio::Start(1);	//�G�t�F�N�g����炷
				//�x�N�g�����O�ɂ���
				m_vx = 0.0f;
				m_vy = 0.0f;
				g_stage = Space;
				//Menu�I�u�W�F�N�g���쐬
				CObjMenu *objmenu = new CObjMenu();
				Objs::InsertObj(objmenu, OBJ_MENU, 150);
				g_move_stop_flag = true;	//�X�g�b�v�t���O���I��

			m_menu_key_f = false;
		}
	}
	else
	{
		m_menu_key_f = true;
	}
	//HitBox�̓��e���X�V
	CHitBox*hit = Hits::GetHitBox(this);

	//�u���b�N�z�[���̏��������Ă���
	CObjBlackhole* blackhole = (CObjBlackhole*)Objs::GetObj(OBJ_BLACKHOLE);

	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�u���b�N�z�[���̐�for���[�v����
	for (int i = 0; i < m_blackhole_num; i++)
	{
		//�u���b�N�z�[���Ɠ��������ꍇ
		if (hit->CheckObjNameHit(OBJ_BLACKHOLE + i) != nullptr)
		{
			//���[�v��
			Audio::Start(7);

			//�����l�̃z���C�g�z�[���ʒu�Ɉړ�������
			block->SetScrollx(-g_whitehole_x[i][0] + m_px);
			block->SetScrolly(-g_whitehole_y[i][0] + m_py);

			g_gemini_move = true;
		}
	}

	//��l����BLOCK�n���Ƃ̓����蔻��
	if (hit->CheckElementHit(ELEMENT_BLOCK) == true)
	{
		//��l�����u���b�N�Ƃǂ̊p�x�œ������Ă���̂����m�F
		HIT_DATA** hit_data;							//�����������ׂ̍��ȏ������邽�߂̍\����
		hit_data = hit->SearchElementHit(ELEMENT_BLOCK);	//hit_data�Ɏ�l���Ɠ������Ă��鑼�S�Ă�HitBox�Ƃ̏�������
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

	if (m_invincible_flag == false)
	{
		if (hit->CheckElementHit(ELEMENT_NULL) == true || hit->CheckElementHit(ELEMENT_ENEMY) == true)
		{
			//�G����l���Ƃǂ̊p�x�œ������Ă��邩���m�F
			HIT_DATA**hit_data;							//�����������ׂ̍��ȏ������邽�߂̍\����
			hit_data = hit->SearchElementHit(ELEMENT_NULL);//hit_data�Ɏ�l���Ɠ������Ă��鑼�S�Ă�HitBox�Ƃ̏�������

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

			//�����̒e�ۂƓ��������ꍇMP����
			if (hit->CheckObjNameHit(OBJ_HOMING_HEART) != nullptr)
				g_mp -= 25.0f;

				//�_���[�W����炷
				Audio::Start(5);
				g_no_damage = true;	//�m�[�_���[�W�t���O���I���ɂ���
				g_hp -= 10.0f;
				m_f = true;
				m_key_f = true;
				m_invincible_flag = true;
			}
		}

	//���q�Ɠ��������ꍇ�Ώ���Ԃ�t�^
	if (hit->CheckObjNameHit(OBJ_LEO) != nullptr)
	{
		Audio::Start(24);
		//�G����l���Ƃǂ̊p�x�œ������Ă��邩���m�F
		HIT_DATA**hit_data;							//�����������ׂ̍��ȏ������邽�߂̍\����
		hit_data = hit->SearchObjNameHit(OBJ_LEO);//hit_data�Ɏ�l���Ɠ������Ă��鑼�S�Ă�HitBox�Ƃ̏�������

		//�����Ώ����ɍēx�U�������������p�����ԏ�����
		m_burn_max_time = 0;
		m_burn_time = 0;

		m_burn_f = true;
		m_eff_flag = true;

	}
	//�t���O���I���̂Ƃ��Ώ���ԂɂȂ�A�����_���[�W
	if (m_burn_f == true)
	{
		m_burn_max_time++;
		if (m_burn_time >= 50)
		{
			g_hp -= 2.0f;
			m_burn_time = 0;
		}
		else
		{
			m_burn_time++;
		}

		if (m_burn_max_time > 300)
		{
			m_burn_max_time = 0;
			m_burn_f = false;
		}
	}

	//�Œe�Ɠ��������ꍇ�ŏ�Ԃ�t�^
	if (hit->CheckObjNameHit(OBJ_POISON) != nullptr)
	{
		Audio::Start(22);
		//�G����l���Ƃǂ̊p�x�œ������Ă��邩���m�F
		HIT_DATA**hit_data;							//�����������ׂ̍��ȏ������邽�߂̍\����
		hit_data = hit->SearchObjNameHit(OBJ_POISON);//hit_data�Ɏ�l���Ɠ������Ă��鑼�S�Ă�HitBox�Ƃ̏�������

		//�����Œe�ۂɍēx�U�������������p�����ԏ�����
		m_burn_max_time = 0;
		m_burn_time = 0;

		m_poison_f = true;
		m_eff_flag = true;

	}
	//�t���O���I���̂Ƃ��ŏ�ԂɂȂ�A�����_���[�W
	if (m_poison_f == true)
	{
		m_burn_max_time++;
		if (m_burn_time >= 70)
		{
			g_hp -= 2.0f;
			m_burn_time = 0;
		}
		else
		{
			m_burn_time++;
		}

		if (m_burn_max_time > 700)
		{
			m_burn_max_time = 0;
			m_poison_f = false;
		}
	}

	//�A�C�e�����쐬���ꂽ�疳�G�ɂ���
	if (g_Make_Item == true)
	{
		m_invincible_flag = true;
	}

	if (m_eff_flag == true)
	{
		//�G�t�F�N�g�p
		RECT_F ani_src2[15] =
		{
			{ 0,    0,  192, 192 },
			{ 0,  192,  384, 192 },
			{ 0,  384,  576, 192 },
			{ 0,  576,  768, 192 },
			{ 0,  768,  960, 192 },
			{ 192,    0,  192, 384 },
			{ 192,  192,  384, 384 },
			{ 192,  384,  576, 384 },
			{ 192,  576,  768, 384 },
			{ 192,  768,  960, 384 },
			{ 384,    0,  384, 576 },
			{ 384,  192,  384, 384 },
			{ 384,  384,  576, 384 },
			{ 384,  576,  768, 384 },
			{ 384,  768,  960, 384 },
		};
		//�A�j���[�V�����̃R�}�Ԋu����
		if (m_eff_time2 > 2)
		{
			m_ani2++;		//�A�j���[�V�����̃R�}��1�i�߂�
			m_eff_time2 = 0;

			m_eff2 = ani_src2[m_ani2];//�A�j���[�V������RECT�z�񂩂�m_ani�Ԗڂ�RECT���擾
		}
		else
		{
			m_eff_time2++;
		}
		// 14�Ԗځi�摜�Ō�j�܂Ői�񂾂�A0�ɖ߂�
		if (m_ani2 == 14)
		{
			m_ani2 = 0;
			m_eff_time2 = 0;

			m_eff_flag = false;
		}
	}

	if (m_f == true)
	{
		m_time--;
		m_alpha = ALPHAUNDER;

	}
	if (m_time <= 0)
	{
		m_f = false;
		m_invincible_flag = false;
		m_alpha = ALPHAORIGIN;

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

	//�ʒu�̍X�V
	m_px += m_vx;
	m_py += m_vy;
	//�u���b�N�Ƃ̓����蔻����s	
	block->BlockHit(&m_px, &m_py, true,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy
	);

	//�쐬����HitBox�X�V�p�̓���������o��
	hit->SetPos(m_px + 15, m_py + 15);//���������V�����ʒu�i��l���̈ʒu�j���ɒu��������

	//HP���O�ɂȂ�����폜
	if (g_hp <= 0.0f)
	{
		m_alpha = 0.0f;
		dead_flag = true;
		m_SE_on++ ;

	}
	if (m_SE_on ==1)
	{
		Audio::Start(25);
	}

	if (dead_flag == true)
	{
		//�G�t�F�N�g�p
		RECT_F ani_src3[12] =
		{
			{ 0,    0,  192, 192 },
			{ 0,  192,  384, 192 },
			{ 0,  384,  576, 192 },
			{ 0,  576,  768, 192 },
			{ 0,  768,  960, 192 },
			{ 192,    0,  192, 384 },
			{ 192,  192,  384, 384 },
			{ 192,  384,  576, 384 },
			{ 192,  576,  768, 384 },
			{ 192,  768,  960, 384 },
			{ 384,    0,  384, 576 },
			{ 384,  192,  384, 384 },
		};

		//�A�j���[�V�����̃R�}�Ԋu����
		if (m_eff_time3 > 2)
		{
			m_ani3++;		//�A�j���[�V�����̃R�}��1�i�߂�
			m_eff_time3 = 0;

			m_eff3 = ani_src3[m_ani3];//�A�j���[�V������RECT�z�񂩂�m_ani�Ԗڂ�RECT���擾
		}
		else
		{
			m_eff_time3++;
		}
		// 12�Ԗځi�摜�Ō�j�܂Ői�񂾂�A0�ɖ߂�
		if (m_ani3 == 12)
		{

			m_ani3 = 0;
			m_eff_time3 = 0;

			dead_flag = false;
			g_Death_cnt++;//�f�X�J�E���g��+����
			Scene::SetScene(new CSceneGameOver());
		}
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
	float c[4] = { 1.0f,1.0f,1.0f,m_alpha };
	float c2[4] = { 1.0f,0.7f,0.7f,m_alpha };
	float c3[4] = { 1.0f,1.0f,1.0f,1.0f };
	float c4[4] = { 1.0f,0.7f,1.0f,m_alpha };
	

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu


	//�u���b�N���������Ă���
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�؂���ʒu�̐ݒ�
	src.m_top    = 65.0f * g_posture;
	src.m_left   =  0.0f + (AniData[m_ani_frame] * 64);
	src.m_right  = 64.0f + (AniData[m_ani_frame] * 64);
	src.m_bottom = src.m_top + 65.0f;
	//�\���ʒu�̐ݒ�
	dst.m_top    = 0.0f	 + m_py;
	dst.m_left   = 80.0f   + m_px;
	dst.m_right  = 0.0f   + m_px;
	dst.m_bottom = 80.0f + m_py;
	//�`��
	Draw::Draw(1, &src, &dst, c, 0.0f);

	//�Ώ���Ԃ̂Ƃ���l����ԐF��
	if (m_burn_f == true)
		Draw::Draw(1, &src, &dst, c2, 0.0f);
	else if(m_poison_f == true)
		Draw::Draw(1, &src, &dst, c4, 0.0f);
	else
		Draw::Draw(1, &src, &dst, c, 0.0f);

	if (g_stage_clear == false)
	{
		//�\���ʒu�̐ݒ�
		dst.m_top = 0.0f + m_py;
		dst.m_left = 80.0f + m_px;
		dst.m_right = 0.0f + m_px;
		dst.m_bottom = 80.0f + m_py;
	}
	else
	{
		//�\���ʒu�̐ݒ�
		dst.m_top = 0.0f + m_py;
		dst.m_left = 40.0f + m_px;
		dst.m_right = 0.0f + m_px;
		dst.m_bottom = 40.0f + m_py;
	}

	//�_�b�V���t���O���I���̏ꍇ
	if (m_dash_flag == true)
	{
		/* g_posture  HERO_UP 1  HERO_LEFT 2  HERO_DOWN 3  HERO_RIGHT 4 */

		//�G�t�F�N�g�̕`��
		if (g_posture == HERO_LEFT || g_posture == HERO_RIGHT)	//���E�̍ہA�摜�����]���Ă��܂����߂̑΍�
			Draw::Draw(15, &m_eff, &dst, c, (g_posture * 270.0f + 180.0f));
		else
			Draw::Draw(15, &m_eff, &dst, c, (g_posture * 270.0f));
	}
	else
	{
		m_ani = 0;
	}
	//�X�^��
	if (m_eff_flag == true)
	{
		//�G�t�F�N�g�p�\���ʒu�̐ݒ�
		dst.m_top = 0.0f + m_py;	//�`��ɑ΂��ăX�N���[���̉e����������
		dst.m_left = 0.0f + m_px;
		dst.m_right = 94.0f + m_px;
		dst.m_bottom = 94.0f + m_py;
		//�`��
		Draw::Draw(18, &m_eff2, &dst, c, 90.0f);
	}
	if (dead_flag == true)
	{
		//�����̎�l����\��
		dst.m_top = 0.0f + m_py;
		dst.m_left = 80.0f + m_px;
		dst.m_right = 0.0f + m_px;
		dst.m_bottom = 80.0f + m_py;

		Draw::Draw(1, &src, &dst, c, 0.0f);

		//�G�t�F�N�g�p�\���ʒu�̐ݒ�
		dst.m_top = 0.0f + m_py;	//�`��ɑ΂��ăX�N���[���̉e����������
		dst.m_left = 0.0f + m_px;
		dst.m_right = 94.0f + m_px;
		dst.m_bottom = 94.0f + m_py;
		//�`��
		Draw::Draw(35, &m_eff3, &dst, c3, 90.0f);
	}

}
