#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

/*		Skill�񋓌^
	Taurus,		//������		0
	Libra,		//�V����		1
	Gemini,		//�o�q��		2
	Virgo,		//������		3
	Leo,		//���q��		4
	NoSkill,	//�X�L������	5
	* �X�L����ύX����ےl��ς��� *
*/


//�I�u�W�F�N�g�F�u���b�N���w�i
class CObjSkill : public CObj
{
	public:
		CObjSkill();
		~CObjSkill() {};
		void Init();		//�C�j�V�����C�Y
		void Action();		//�A�N�V����
		void Draw();		//�h���[

	private:
};