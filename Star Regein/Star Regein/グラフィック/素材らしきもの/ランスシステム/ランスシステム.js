/*--------------------------------------------------
�����X�V�X�e���@�� 1-239

�y�T�v�z
�x���T�K�̃����X�n������������܂�

�y�������@�z
����̃J�X�^���p�����[�^��{distance:3}�̂悤�ɋL�q
���̏ꍇ�A�_���[�W�� ��+����З�+(�J�X�^��*�ړ�����)�ƂȂ�܂�

��)��5�̃L�����ɈЗ�5�A{distance:3}�̕�����������ĂS�}�X�ړ������ꍇ
5 + 5 + ( 3 * 4 ) = 22

�@ ��5�̃L�����ɈЗ�0�A{distance:5}�̕�����������ĂV�}�X�ړ������ꍇ
5 + 0 + ( 5 * 7 ) = 37

���̃X�N���v�g���g�p���ăQ�[���o�����X�����󂵂Ă���(1-239)�͈�ؐӔC�𕉂��܂���

6/15 �ƌ�

---------------------------------------------*/

ItemSentence.AttackAndHit.drawItemSentence = function(x, y, item) {
		var text;
		var textui = root.queryTextUI('default_window');
		var color = textui.getColor();
		var font = textui.getFont();
		
		text = root.queryCommand('attack_capacity');
		ItemInfoRenderer.drawKeyword(x, y, text);
		x += ItemInfoRenderer.getSpaceX();
		var power = item.getPow();

		//�����X����̏ꍇ�A�\�L��ύX����
		if(typeof item.custom.distance == 'number'){
		power =power + '+' + item.custom.distance + '�l';
		}
		TextRenderer.drawKeywordText(x, y,power, -1, color, font);
		x += 42;
		
		text = root.queryCommand('hit_capacity');
		ItemInfoRenderer.drawKeyword(x, y, text);
		x += ItemInfoRenderer.getSpaceX();
		NumberRenderer.drawRightNumber(x, y, item.getHit());
}

AbilityCalculator.getPower = function(unit, weapon){
		var pow;
		var movbonus = unit.getMostResentMov();
		var wpc = weapon.custom.distance;

		var attack;

		if (Miscellaneous.isPhysicsBattle(weapon)) {
			// �����U���܂��͓��ˍU��
			pow = RealBonus.getStr(unit);
		}
		else {
			// ���@�U��
			pow = RealBonus.getMag(unit);
		}
		
		// ����̈З� + (�� or ����)
		if(typeof wpc == 'number'){rance = movbonus * wpc}else{rance=0;}

		attack = pow + weapon.getPow() + rance;

		return attack;
}