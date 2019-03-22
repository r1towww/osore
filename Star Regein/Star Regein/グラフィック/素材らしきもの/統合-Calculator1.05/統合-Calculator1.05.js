/*--------------------------------------------------------------------------
  
  FE������Q�l�ɂ����v�Z���ł�
  �N���X�̃J�X�^���p�����[�^��{bld}(�̊i)
�@���ݒ肳��Ă���ꍇ������A
�@�ݒ肳��Ă��Ȃ��ꍇ��(����)�ŏd�����y�����܂�

�@[�E���E����E�B�l�ݒ�X�N���v�g1.03.js]���K���������Ă�������

--------------------------------------------------------------------------*/
AbilityCalculator.getPower = function(unit, weapon) {
	var pow;
	var movbonus = unit.getMostResentMov();

	if (Miscellaneous.isPhysicsBattle(weapon)) {
		// �����U���܂��͓��ˍU��
		pow = RealBonus.getStr(unit);
	}
	else {
		// ���@�U��
		pow = RealBonus.getMag(unit);
	}
	
	// �X�L��[�W��]�̏���
	var skill = SkillControl.getPossessionCustomSkill(unit,'concentrate');
	if (skill) {
		var i, x, y, index, targetUnit;
		var indexArray = IndexArray.getBestIndexArray(unit.getMapX(), unit.getMapY(), 1, skill.custom.area);
		var count = indexArray.length;
		var bonus = skill.custom.param_bonus;
		
		for (i = 0; i < count; i++) {
			index = indexArray[i];
			x = CurrentMap.getX(index);
			y = CurrentMap.getY(index);
			targetUnit = PosChecker.getUnitFromPos(x, y);
			if (targetUnit !== null) {
				if(targetUnit.getUnitType()==unit.getUnitType()){
					bonus = 0;
				}
			}
		}
		pow += bonus;
	}
	
	// �X�L��[��C�T]�̏���
	var skill = SkillControl.getPossessionCustomSkill(unit,'lone-wolf');
	if (skill) {
		var i, x, y, index, targetUnit;
		var indexArray = IndexArray.getBestIndexArray(unit.getMapX(), unit.getMapY(), 1, skill.custom.area);
		var count = indexArray.length;
		var bonus = skill.custom.param_bonus;
		
		for (i = 0; i < count; i++) {
			index = indexArray[i];
			x = CurrentMap.getX(index);
			y = CurrentMap.getY(index);
			targetUnit = PosChecker.getUnitFromPos(x, y);
			if (targetUnit !== null) {
				if(targetUnit.getUnitType()==unit.getUnitType()){
					bonus = 0;
				}
			}
		}
		pow += bonus;
	}

	pow += Buster.chackmuster(unit);

	// �����X�̏���
	if(typeof weapon.custom.distance == 'number'){
	rance = weapon.custom.distance * movbonus;}else{rance=0;}

	//�X�L��[�����]�̏���
	if (SkillControl.getPossessionCustomSkill(unit,'allowance')){
	pow /= 2;
	pow = Math.floor(pow);
	}

	// ����̈З� + (�� or ����)
	return pow + weapon.getPow() + rance;
};
//============================================================================================
AbilityCalculator.getHit = function(unit, weapon) {	
	var cls = unit.getClass();
	var hitb = cls.custom.hitp;
	
	// ����̖����� + (�Z * 2) + (�K�^/2)
	hit = weapon.getHit() + (RealBonus.getSki(unit) * 2) + (RealBonus.getLuk(unit) * 2);
	
	if (typeof cls.custom.hit !== 'number') {}
	else
	{hit += hitb;};
	
	//�X�L��[�ꔭ��]�̏���
	if (SkillControl.getPossessionCustomSkill(unit,'one-hitter')) {
		hit -= 10;
	}	
	//�X�L��[��������]�̏���
	if (SkillControl.getPossessionCustomSkill(unit,'fortitude')){
		hit += 10;
	}
	//�X�L��[����+]�̏���
	var skill = SkillControl.getPossessionCustomSkill(unit,'hit+');
	if (SkillControl.getPossessionCustomSkill(unit,'hit+')){
	var bonus = skill.custom.param_bonus;
	hit += bouns;
	}

	//�X�L��[�o�C�I�E����]�̏���
	var skill = SkillControl.getPossessionCustomSkill(unit,'vaio-even');
	if (SkillControl.getPossessionCustomSkill(unit,'vaio-even')) {
	var Turn = root.getCurrentSession().getTurnCount() % 2;
	if (Turn == 0 ){var bonus = skill.custom.param_bonus;
	hit += bonus;}}

	//�X�L��[�o�C�I�E�]�̏���
	var skill = SkillControl.getPossessionCustomSkill(unit,'vaio-odd');
	if (SkillControl.getPossessionCustomSkill(unit,'vaio-odd')) {
	var Turn = root.getCurrentSession().getTurnCount() % 2;
	if (Turn == 1 ){var bonus = skill.custom.param_bonus;
	hit += bonus;}}

	//�X�L��[������`]�̏���
	var skill = SkillControl.getPossessionCustomSkill(unit,'Per-fect');
	if (SkillControl.getPossessionCustomSkill(unit,'Per-fect')) {
	var HPflag = unit.getHP() - RealBonus.getMhp(unit);
	var bonus = skill.custom.param_bonus;
	if(HPflag == 0){hit += bonus;}}

	//�X�L��[�X���[�X�^�[�g]�̏���
	if (SkillControl.getPossessionCustomSkill(unit,'slow-start')) {
	var Turn = root.getCurrentSession().getTurnCount();
	if (Turn <= 16){Turn = 16;}
	hit += Turn;}

	//�X�L��[�z�b�g�X�^�[�g]�̏���
	if (SkillControl.getPossessionCustomSkill(unit,'hot-start')) {
	var Turn = root.getCurrentSession().getTurnCount() - 16;
	if (Turn <= 0){Turn = 0;}
	hit += Turn;}

	//�X�L��[���b�L�[7]�̏���
	var skill = SkillControl.getPossessionCustomSkill(unit,'lucky-7');
	if (SkillControl.getPossessionCustomSkill(unit,'lucky-7')) {
	var Turn = root.getCurrentSession().getTurnCount() - 7;
	if (Turn <= 0){hit += 33;}}

	// �X�L��[���O�퓬]�������Ă���ꍇ�́A�n�`�ɂ���ĉ�𗦂����Z����
	if (cls.getClassType().isTerrainBonusEnabled() && SkillControl.getPossessionCustomSkill(unit,'out_combat')) {
		var skill = SkillControl.getPossessionCustomSkill(unit,'out_combat');
		var bonus = skill.custom.param_bonus;
		terrain = PosChecker.getTerrainFromPos(unit.getMapX(), unit.getMapY());
		if(terrain.custom.location!==1){
			hit += bonus;
		}
	}
	// �X�L��[�����퓬]�������Ă���ꍇ�́A�n�`�ɂ���ĉ�𗦂����Z����
	if (cls.getClassType().isTerrainBonusEnabled() && SkillControl.getPossessionCustomSkill(unit,'in_combat')) {
		var skill = SkillControl.getPossessionCustomSkill(unit,'in_combat');
		var bonus = skill.custom.param_bonus;
		terrain = PosChecker.getTerrainFromPos(unit.getMapX(), unit.getMapY());
		if(terrain.custom.location==1){
			hit += bonus;
		}
	}
	// �X�L��[����]�̏���
	var skill = SkillControl.getPossessionCustomSkill(unit,'ride-fast');
	if (skill) {
		var i, x, y, index, targetUnit;
		var indexArray = IndexArray.getBestIndexArray(unit.getMapX(), unit.getMapY(), 1, skill.custom.area);
		var count = indexArray.length;
		var bonus = skill.custom.param_bonus;
		
		for (i = 0; i < count; i++) {
			index = indexArray[i];
			x = CurrentMap.getX(index);
			y = CurrentMap.getY(index);
			targetUnit = PosChecker.getUnitFromPos(x, y);
			if (targetUnit !== null) {
				if(targetUnit.getUnitType()==unit.getUnitType()){
					bonus = 0;
				}
			}
		}
		hit += bonus;
	}
	//�X�L��[�����]�̏���
	if (SkillControl.getPossessionCustomSkill(unit,'allowance')){
	hit *= 2;
	}
	return hit;
};
//============================================================================================
AbilityCalculator.getAvoid = function(unit) {
	var avoid, terrain;
	var cls = unit.getClass();
	var avob = cls.custom.avo;
	var weapon = ItemControl.getEquippedWeapon(unit);
	
	if(weapon == null){
		agi = RealBonus.getSpd(unit);
	}else{
		agi = AbilityCalculator.getAgility(unit,weapon);
	}
		
	// ����́A(�q�� * 2 + �K�^)
	avoid = agi * 2 + RealBonus.getLuk(unit);
	
	//�X�L��[����㏸]�̏���
	if (SkillControl.getPossessionCustomSkill(unit,'avo-up')){
	avoid += agi;}

	if (typeof cls.custom.avo !== 'number') {}
	else
	{avoid += avob;};
	
	//�X�L��[���+10]�̏���
	var skill = SkillControl.getPossessionCustomSkill(unit,'avoid+');
	if (SkillControl.getPossessionCustomSkill(unit,'avoid+')){
		var skill = SkillControl.getPossessionCustomSkill(unit,'avoid+');
		var bonus = skill.custom.param_bonus;
		avoid += bonus;
	}
	
	//�X�L��[������`]�̏���
	var skill = SkillControl.getPossessionCustomSkill(unit,'Per-fect');
	if (SkillControl.getPossessionCustomSkill(unit,'Per-fect')) {
	var HPflag = unit.getHP() - RealBonus.getMhp(unit);
	var bonus = skill.custom.param_bonus;
	if(HPflag == 0){avoid += bonus;}}

	//�X�L��[�o�C�I�E����]�̏���
	var skill = SkillControl.getPossessionCustomSkill(unit,'vaio-even');
	if (SkillControl.getPossessionCustomSkill(unit,'vaio-even')) {
	var Turn = root.getCurrentSession().getTurnCount() % 2;
	if (Turn == 0 ){var bonus = skill.custom.param_bonus;
	avoid += bonus;}}

	//�X�L��[�o�C�I�E�]�̏���
	var skill = SkillControl.getPossessionCustomSkill(unit,'vaio-odd');
	if (SkillControl.getPossessionCustomSkill(unit,'vaio-odd')) {
	var Turn = root.getCurrentSession().getTurnCount() % 2;
	if (Turn == 1 ){var bonus = skill.custom.param_bonus;
	avoid += bonus;}}

	//�X�L��[�X���[�X�^�[�g]�̏���
	if (SkillControl.getPossessionCustomSkill(unit,'slow-start')) {
	var Turn = root.getCurrentSession().getTurnCount();
	if (Turn <= 16){Turn = 16;}
	avoid += Turn;}

	//�X�L��[�z�b�g�X�^�[�g]�̏���
	if (SkillControl.getPossessionCustomSkill(unit,'hot-start')) {
	var Turn = root.getCurrentSession().getTurnCount() - 16;
	if (Turn <= 0){Turn = 0;}
	avoid += Turn;}

	//�X�L��[���b�L�[7]�̏���
	var skill = SkillControl.getPossessionCustomSkill(unit,'lucky-7');
	if (SkillControl.getPossessionCustomSkill(unit,'lucky-7')) {
	var Turn = root.getCurrentSession().getTurnCount() - 7;
	if (Turn <= 0){avoid += 33;}}

	// �N���X�n�����n�`�{�[�i�X���l������ꍇ�́A�n�`���ʂ̉�𗦂����Z����
	// �X�L��[����@��]�������Ă���ꍇ���n�`���ʂ��󂯂�
	if (cls.getClassType().isTerrainBonusEnabled() || SkillControl.getPossessionCustomSkill(unit,'avoid_maneuver')) {
		terrain = PosChecker.getTerrainFromPos(unit.getMapX(), unit.getMapY());
		
		//�X�L��[����]�̏���
		if (SkillControl.getPossessionCustomSkill(unit,'Camouflage')) {
		avoid += terrain.getAvoid() * 15 / 10;}
		else{avoid += terrain.getAvoid();}
	}
	// �X�L��[���O�퓬]�������Ă���ꍇ�́A�n�`�ɂ���ĉ�𗦂����Z����
	if (cls.getClassType().isTerrainBonusEnabled() && SkillControl.getPossessionCustomSkill(unit,'out_combat')) {
		var skill = SkillControl.getPossessionCustomSkill(unit,'out_combat');
		var bonus = skill.custom.param_bonus;
		terrain = PosChecker.getTerrainFromPos(unit.getMapX(), unit.getMapY());
		if(terrain.custom.location!==1){
			avoid += bonus;
		}
	}
	// �X�L��[�����퓬]�������Ă���ꍇ�́A�n�`�ɂ���ĉ�𗦂����Z����
	if (cls.getClassType().isTerrainBonusEnabled() && SkillControl.getPossessionCustomSkill(unit,'in_combat')) {
		var skill = SkillControl.getPossessionCustomSkill(unit,'in_combat');
		var bonus = skill.custom.param_bonus;
		terrain = PosChecker.getTerrainFromPos(unit.getMapX(), unit.getMapY());
		if(terrain.custom.location==1){
			avoid += bonus;
		}
	}
	// �X�L��[����]�̏���
	var skill = SkillControl.getPossessionCustomSkill(unit,'ride-fast');
	if (skill) {
		var i, x, y, index, targetUnit;
		var indexArray = IndexArray.getBestIndexArray(unit.getMapX(), unit.getMapY(), 1, skill.custom.area);
		var count = indexArray.length;
		var bonus = skill.custom.param_bonus;
		
		for (i = 0; i < count; i++) {
			index = indexArray[i];
			x = CurrentMap.getX(index);
			y = CurrentMap.getY(index);
			targetUnit = PosChecker.getUnitFromPos(x, y);
			if (targetUnit !== null) {
				if(targetUnit.getUnitType()==unit.getUnitType()){
					bonus = 0;
				}
			}
		}
		avoid += bonus;
	}
	return avoid;
};
//============================================================================================
AbilityCalculator.getCritical = function(unit, weapon) {
	// �Z / 2 + ����̃N���e�B�J����
	var cri;
	var cls = unit.getClass();
	var clb = cls.custom.crt;
	
	cri = RealBonus.getSki(unit) / 2;
	if(cri<1){
		cri = 0;
	}
	
	if (typeof cls.custom.crt !== 'number') {}
	else
	{cri += clb;};
	
	cri = cri + weapon.getCritical();
	
	//�X�L��[�ꔭ��]�̏���
	if (SkillControl.getPossessionCustomSkill(unit,'one-hitter')) {
	cri += 10;}
	
	//�X�L��[��������]�̏���
	if (SkillControl.getPossessionCustomSkill(unit,'fortitude')) {
	cri -= 10;}
	
	//�X�L��[�o�����{��]�̏���
	var skill = SkillControl.getPossessionCustomSkill(unit,'HP-crtup');
	if (SkillControl.getPossessionCustomSkill(unit,'HP-crtup')){
	var limit = skill.custom.skill_limit;
	var HPflag = (RealBonus.getMhp(unit) * limit / 100) - unit.getHP();
	if (HPflag >= 0 ){
	var bonus = skill.custom.param_bonus;
	cri += bonus;}}

	//�X�L��[�����̋Z]�̏���
	if (SkillControl.getPossessionCustomSkill(unit,'Life-death')) {
	cri += 100 - ((unit.getHP() * 100) / RealBonus.getMhp(unit)) ;}

	// �X�L��[�W���o��]�̏���
	var skill = SkillControl.getPossessionCustomSkill(unit,'Criti-cal');
	if (skill) {
		var i, x, y, index, targetUnit;
		var indexArray = IndexArray.getBestIndexArray(unit.getMapX(), unit.getMapY(), 1, skill.custom.area);
		var count = indexArray.length;
		var bonus = skill.custom.param_bonus;
		
		for (i = 0; i < count; i++) {
			index = indexArray[i];
			x = CurrentMap.getX(index);
			y = CurrentMap.getY(index);
			targetUnit = PosChecker.getUnitFromPos(x, y);
			if (targetUnit !== null) {
				if(targetUnit.getUnitType()==unit.getUnitType()){
					bonus = 0;
				}
			}
		}
		cri += bonus;
	}

	return cri;
};
//============================================================================================
AbilityCalculator.getCriticalAvoid = function(unit) {
	// �K�^���N���e�B�J�����
	var criavoid = RealBonus.getLuk(unit);
	
	
	// �X�L��[���_]
	var i, x, y, index, targetUnit;
	var indexArray = IndexArray.getBestIndexArray(unit.getMapX(), unit.getMapY(), 1, 3);
	var count = indexArray.length;
	
	for (i = 0; i < count; i++) {
		index = indexArray[i];
		x = CurrentMap.getX(index);
		y = CurrentMap.getY(index);
		targetUnit = PosChecker.getUnitFromPos(x, y);
		if (targetUnit !== null) {
			var skill = SkillControl.getPossessionCustomSkill(targetUnit,'reaper');
			//if(targetUnit.getUnitType()==unit.getUnitType() && SkillControl.getPossessionCustomSkill(targetUnit,'reaper')){
			if(skill){
				criavoid -= skill.custom.param_bonus;
				if(criavoid < 0){criavoid=0;}
			}
		}
	}
	return criavoid
};
//============================================================================================
AbilityCalculator.getAgility = function(unit, weapon) {
	var agi, pow, value;

	var bld = unit.custom.bld;
	var spd = RealBonus.getSpd(unit);

	if (DataConfig.isItemWeightDisplayable() && weapon !== null) {
		if(bld==null){
		if (Miscellaneous.isPhysicsBattle(weapon)) {
			bld = RealBonus.getStr(unit);
		}
		else {
			bld = RealBonus.getMag(unit);
		}
		}

		//�X�L��[�������]�̏���
		// �d�� - �̊i
		var skill = SkillControl.getPossessionCustomSkill(unit,'Equipped');
		if (SkillControl.getPossessionCustomSkill(unit,'Equipped')) {
		var bonus = skill.custom.param_bonus;
		bld +=  bonus;}
	
		value = weapon.getWeight() - bld;

		if (value > 0) {
			// ��(����)���d�����Ⴂ���߁A���̍��������q����������
			agi = spd - value;
		}
		else {
			agi = spd;
		}
	}
	else {
		// �d����\�����Ȃ��ꍇ�́A�������q���Ɠ���ɂȂ�
		agi = spd;
	}

	return agi;
};
//============================================================================================
HitCalculator.calculateAvoid= function(active, passive, weapon, totalStatus) {
	return AbilityCalculator.getAvoid(passive,weapon) + CompatibleCalculator.getAvoid(passive, active, ItemControl.getEquippedWeapon(passive)) + SupportCalculator.getAvoid(totalStatus);
};


CriticalCalculator.calculateCritical= function(active, passive, weapon, activeTotalStatus, passiveTotalStatus) {
	var critical, avoid, percent;
	
	if (!this.isCritical(active, passive, weapon)) {
		return 0;
	}
	
	critical = this.calculateSingleCritical(active, passive, weapon, activeTotalStatus);
	avoid = this.calculateCriticalAvoid(active, passive, weapon, passiveTotalStatus);
	
	percent = critical - avoid;
	percent = Math.floor(percent);
	
	return this.validValue(active, passive, weapon, percent);
};


Calculator.calculateRecoveryItemPlus= function(unit, targetUnit, item) {
	var plus = 0;
	var itemType = item.getItemType();
	
	if (itemType !== ItemType.RECOVERY && itemType !== ItemType.ENTIRERECOVERY) {
		return 0;
	}
	
	// �A�C�e������̏ꍇ�́A�g�p�҂̖��͂����Z����
	if (item.isWand()) {
		//�X�L��[������]�̏���
		//������łȂ��Ɩ��͂�����
		if (SkillControl.getPossessionCustomSkill(unit,'healer')) {
			plus = ParamBonus.getMag(unit) * 2;
		}else{
			plus = ParamBonus.getMag(unit);
		}

	if (SkillControl.getPossessionCustomSkill(unit,'healing')) {
	plus += 5;}

	}
	
	return plus;
};
/*--------------------------------------------------------------------------
  
  �o���l�̎擾
  
  [fe_class]
  0 : 				�㋉�N���X�Ƃ��Ĉ���
  1 : 				�����N���X�Ƃ��Ĉ���
  
  [fe_type]
  1 : �\���W���[	�G�Ƃ��Ă̌��j�o���l���A���x�����Ⴍ�Ȃ�
  2 : ����			��b�o���l���A�ŏI�I�ɏ��Z�����l��2�Ōv�Z�����B�@���f�t�H��3
  					���j�o���l��20������i�{���͒Ⴍ�Ȃ邪�A�m���Ɍo���l�͂��炦��B
					�G�Ƃ��Ă̌��j�o���l��3������
  3 : �}���N�[�g	���j�o���l��20������
  
  
--------------------------------------------------------------------------*/
ExperienceValueControl._getVictoryExperience= function(active, activeHp, activeDamageTotal, passive, passiveHp, passiveDamageTotal) {
	var exp;
	var addexp;
	var classexp = 0;
	var etcexp = 0;
	var baseExp = this._getBaseExperience();
	var bonusExp = passive.getClass().getBonusExp();
	var a_fe_type = active.getClass().custom.fe_type;
	var a_fe_class = active.getClass().custom.fe_class;
	var p_fe_type = passive.getClass().custom.fe_type;
	var p_fe_class = passive.getClass().custom.fe_class;
	
	
	// �{�[�i�X�o���l���}�C�i�X�̏ꍇ�́A�������Ɍo���l���擾���Ȃ��B
	// ����͍ŏI�}�b�v�̃��[�_�[���j��z�肵�����̂ł���B
	if (bonusExp < 0) {
		return 0;
	}
	
	// ���j���̌o���l���Œ�ɂ��Ă��邽�߁A
	// �N���X�̒ǉ��o���l�����̂܂ܕԂ��B
	if (root.getUserExtension().isFixedExperience()) {
		return this._getValidExperience(bonusExp);
	}
	
	// �����|�����ꍇ�̏���
	exp = this._getNormalValue(active, activeHp, activeDamageTotal, passive, passiveHp, passiveDamageTotal);
	
	//���肪�����Ȃ�+3 ���肪�\���W���[�Ȃ�G���x�����}�C�i�X
	if(p_fe_type == '1'){
		etcexp = etcexp - passive.getLv();
	}else if(p_fe_type == '2'){
		etcexp = 3;
	}
	//���j�o���l�x�[�X
	addexp = (passive.getLv() * 3 - active.getLv() * 3);
	addexp += 20;
	
	//�����E�}���N�[�g�͌o���l+20
	if(a_fe_type == '2' || a_fe_type == '3'){
		addexp += 20;
	}
	
	//�N���X�K���␳
	if(a_fe_class == null){
		a_fe_class = '0'
	}
	if(p_fe_class == null){
		p_fe_class = '0'
	}

	if(a_fe_class == '0' && p_fe_class == '1'){
		classexp = 60;
	}
	if(a_fe_class == '1' && p_fe_class == '0'){
		classexp = -60;
	}
	addexp += classexp;
	
	if(addexp <0){
		addexp = 0;
	}
	
	exp += etcexp + addexp;
	
		//���肪���[�_�[�A�T�u���[�_�[�̏ꍇ�͌o���l�����Z 
		//	�����K�v�ł���΁@���̓�̃X���b�V���������Ă��������@	
		//exp += this._getBonusExperience(passive);
	
	// ����̃N���X�̒ǉ��o���l�����Z
	exp += bonusExp;
	
	exp = Math.floor(exp);
	
	return this._getValidExperience(exp);
};

//��b�o���l
ExperienceValueControl._getNormalValue= function(active, activeHp, activeDamageTotal, passive, passiveHp, passiveDamageTotal) {
	var exp;
	var baseExp = 31;
	var feExp;
	var cls = active.getClass();
	
	var a_fe_type = cls.custom.fe_type;
	var a_fe_class = cls.custom.fe_class;
	var p_fe_type = passive.getClass().custom.fe_type;
	var p_fe_class = passive.getClass().custom.fe_class;
	var lv = passive.getLv() - active.getLv();
	
	
	//�N���X�␳ �G�}���N�[�g�͏㋉�N���X�Ƃ��Čv�Z����
	if(a_fe_class == null){
		a_fe_class = '0'
	}
	if(p_fe_class == null){
		p_fe_class = '0'
	}
	if(p_fe_type == '3'){
		p_fe_class = '1'
	}
	if(a_fe_class == '0' && p_fe_class == '1'){
		baseExp = 51;
	}
	if(a_fe_class == '1' && p_fe_class == '0'){
		baseExp = 11;
	}
	
	// �����|�����ꍇ�̏���
	exp = baseExp + lv;
	
	// �J�X�^���p�����[�^�� �o���l�{�� *3(�V�[�t�ƃ}���N�[�g��*2�j
	if(a_fe_type == '2' || a_fe_type == '3'){
		feExp = 2;
	}else{
		feExp = 3;
	}
	
	exp = Math.floor(exp / feExp);		
	return this._getValidExperience(exp);
};
//============================================================================================
HitCalculator.calculateHit= function(active, passive, weapon, activeTotalStatus, passiveTotalStatus) {
	var hit, avoid, percent;
	var turnType = root.getCurrentSession().getTurnType();
	
	if (root.isAbsoluteHit()) {
		if (passive.isImmortal()) {
			// ����͕s���g�̏ꍇ�́A��������100%�ɂȂ�Ȃ�
			return 99;
		}
		return 100;
	}
	
	//�E���X�L���̏���(�ݒ�X�N���v�g�̌Ăяo��)
	hit = Buster.chackweapon(active, passive, weapon, passiveTotalStatus, hit);
	avoid = this.calculateAvoid(active, passive, weapon, passiveTotalStatus);

	//[��̐�]
	var skill = SkillControl.getPossessionCustomSkill(active,'fe_sensen');
	if(turnType == active.getUnitType() && skill){
		var bonus = skill.custom.param_bonus;
		hit += bonus;
	}
	var skill = SkillControl.getPossessionCustomSkill(passive,'fe_sensen');
	if(turnType == passive.getUnitType() && skill){
		var bonus = skill.custom.param_bonus;
		avoid += bonus;
	}
	
	
	if(turnType == passive.getUnitType()){
	//��̐� �G����U�����ꂽ���A����+10
		if (SkillControl.getPossessionCustomSkill(active,'fe_gosen')){
			var skill = SkillControl.getPossessionCustomSkill(active,'fe_gosen');
			var bonus = skill.custom.param_bonus;
			hit += bonus;
		}
	}
	if(turnType == active.getUnitType()){;
	//��̐� �G����U�����ꂽ���A���+10
		if (SkillControl.getPossessionCustomSkill(passive,'fe_gosen')){
			var skill = SkillControl.getPossessionCustomSkill(passive,'fe_gosen');
			var bonus = skill.custom.param_bonus;
			avoid += bonus;
		}
	}
	
	//������X�L��
	var skill = SkillControl.getPossessionCustomSkill(active,'gekokuzyo');
	if (SkillControl.getPossessionCustomSkill(active,'gekokuzyo')){
	var acLV = active.getLV();
	var acCl = active.getClass();
	if (typeof acCl.custom.fe_class == 'number') {
	acLV += active.getClass().custom.fe_class * 20;}
	var paLV = passive.getLV() - 1;
	var paCl = passive.getClass();
	if (typeof paCl.custom.fe_class == 'number'){
	paLV += passive.getClass().custom.fe_class * 20;}
	var bonus = skill.custom.param_bonus;
	if (acLV <= paLV){hit += bonus;}}

	var skill = SkillControl.getPossessionCustomSkill(passive,'gekokuzyo');
	if (SkillControl.getPossessionCustomSkill(passive,'gekokuzyo')){
	var acLV = active.getLV() - 1;
	var acCl = active.getClass();
	if (typeof acCl.custom.fe_class == 'number') {
	acLV += active.getClass().custom.fe_class * 20;}
	var paLV = passive.getLV();
	var paCl = passive.getClass();
	if (typeof paCl.custom.fe_class == 'number'){
	paLV += passive.getClass().custom.fe_class * 20;}
	var bonus = skill.custom.param_bonus;
	if (acLV >= paLV){hit -= bonus;}}

	percent = Buster.chackiveid(active, passive, weapon, passiveTotalStatus, hit, avoid);
	
	return this.validValue(active, passive, weapon, percent);
};
//============================================================================================
DamageCalculator.calculateDamage = function(active, passive, weapon, isCritical, activeTotalStatus, passiveTotalStatus) {
		var pow, def, damage;
		var option = weapon.getWeaponOption();
		
		if (option === WeaponOption.HPMINIMUM) {
			return -1;
		}

		pow = this.calculateAttackPower(active, passive, weapon, isCritical, activeTotalStatus);
		def = this.calculateDefense(active, passive, weapon, isCritical, passiveTotalStatus);

		//���̓X�L���̏���
		//�����̗�-����̗�+5�Ń}�C�i�X�Ȃ�_��+3
		var skill = SkillControl.getPossessionCustomSkill(active,'super-power');
		if (SkillControl.getPossessionCustomSkill(active,'super-power')) {
		var bonus = skill.custom.param_bonus;
		var limit = skill.custom.skill_limit;
		var acatk =active.getParamValue(1) - passive.getParamValue(1) + limit;
		if (acatk <= 0){pow += bonus;}}
		
		//�����X�L��
		//�����̃_���v�Z���ɃX�L�������Ȃ�З�+10
		//����̃_���v�Z���Ɏ������X�L�������Ȃ�З�+10
		var skill = SkillControl.getPossessionCustomSkill(active,'death-line');
		if (SkillControl.getPossessionCustomSkill(active,'death-line'))
		{var bonus = skill.custom.param_bonus;
		pow += bonus;}
		else{
		var skill = SkillControl.getPossessionCustomSkill(passive,'death-line');
		if (SkillControl.getPossessionCustomSkill(passive,'death-line'))
		{var bonus = skill.custom.param_bonus;
		pow += bonus;}}

		//�����X�L��
		var skill = SkillControl.getPossessionCustomSkill(active,'iai-do');
		if (SkillControl.getPossessionCustomSkill(active,'iai-do')){
		var Turn = root.getCurrentSession().getTurnType();
		var Unty = active.getUnitType()
		var bonus = skill.custom.param_bonus;
		if (Turn == Unty){
		pow += bonus;}}
		
		//����X�L��
		var skill = SkillControl.getPossessionCustomSkill(active,'son-dai');
		if (SkillControl.getPossessionCustomSkill(active,'son-dai')){
		var acLV = active.getLV();
		var acCl = active.getClass();
		if (typeof acCl.custom.fe_class == 'number') {
		acLV += active.getClass().custom.fe_class * 20;}
		var paLV = passive.getLV() - 1;
		var paCl = passive.getClass();
		if (typeof paCl.custom.fe_class == 'number'){
		paLV += passive.getClass().custom.fe_class * 20;}
		var bonus = skill.custom.param_bonus;
		if (acLV <= paLV){pow += bonus;}}

		damage = pow - def;
		if (this.isHalveAttack(active, passive, weapon, isCritical)) {
			damage = Math.floor(damage / 2);
		}
		
		if (isCritical) {
			damage = Math.floor(damage * this.getCriticalFactor());
		}

		return this.validValue(active, passive, weapon, damage);
	}
//============================================================================================
DamageCalculator.calculateAttackPower = function(active, passive, weapon, isCritical, totalStatus) {
		var classdata;
		var pow = AbilityCalculator.getPower(active, weapon) + CompatibleCalculator.getPower(active, passive, weapon) + SupportCalculator.getPower(totalStatus);
		
		// ���U�����̃X�L���������Ă��Ȃ��ꍇ
		if (SkillControl.getFlagPossessionSkill(passive, SkillType.INVALID, InvalidFlag.EFFECTIVE) === null) {
		// ����̃N���X�ɑ΂��āA�A�C�e���͓�����
		classdata = passive.getClass();

		if (ItemControl.isEffectiveClass(classdata, weapon)) {
		pow = Math.floor(pow * this.getEffectiveFactor());
		}else{

		//�������ɓ˂����ނ�������6�{���U�ɂȂ�\��������̂ŕ���
		if (SkillControl.getPossessionCustomSkill(active,'beast-slayer')){
		var flag;
		flag = classdata.getClassType().getID();
		if (flag == 3){pow = Math.floor(pow * this.getEffectiveFactor());}}}
		}
		
		return pow;
	};
//============================================================================================
DamageCalculator.calculateDefense= function(active, passive, weapon, isCritical, totalStatus) {
	var def;
	var option = weapon.getWeaponOption();
	
	if (option === WeaponOption.NOGUARD) {
		// �h�䖳���̕���I�v�V���������邽�߁A�h���0�ɂ���
		return 0;
	}
	
	if (Miscellaneous.isPhysicsBattle(weapon)) {
		// �����U���܂��͓��ˍU��
		def = RealBonus.getDef(passive);
		// �X�L��[��C�T]�̏���
		var skill = SkillControl.getPossessionCustomSkill(passive,'lone-wolf');
		if (skill) {
			var i, x, y, index, targetUnit;
			var indexArray = IndexArray.getBestIndexArray(passive.getMapX(), passive.getMapY(), 1, skill.custom.area);
			var count = indexArray.length;
			var bonus = skill.custom.param_bonus;
			
			for (i = 0; i < count; i++) {
				index = indexArray[i];
				x = CurrentMap.getX(index);
				y = CurrentMap.getY(index);
				targetUnit = PosChecker.getUnitFromPos(x, y);
				if (targetUnit !== null) {
					if(targetUnit.getUnitType()==passive.getUnitType()){
						bonus = 0;
					}
				}
			}
			def += bonus;
		}
	}
	else {
		// ���@�U��
		def = RealBonus.getMdf(passive);
	}
	
	def += CompatibleCalculator.getDefense(passive, active, ItemControl.getEquippedWeapon(passive)) + SupportCalculator.getDefense(totalStatus);
	
	return def;
};
//============================================================================================
NormalAttackOrderBuilder._isDefaultPriority= function(virtualActive, virtualPassive) {
	var active = virtualActive.unitSelf;
	var passive = virtualPassive.unitSelf;
	var skilltype = SkillType.FASTATTACK;
	var skill = SkillControl.getPossessionSkill(active, skilltype);

	if (SkillRandomizer.isSkillInvoked(active, passive, skill)) {
		// �U�����������������搧�U���̃X�L�������ꍇ�́A���̎��_�Œʏ�퓬�Ɣ��f����
		return true;
	}
	
	skill = SkillControl.getPossessionCustomSkill(passive,'unbush');
	//if (SkillControl.getPossessionCustomSkill(passive,'unbush')){
	if (SkillRandomizer.isSkillInvoked(passive, active, skill)) {
		if(passive.getHP() / ParamBonus.getMhp(passive) <= 0.5){
			virtualPassive.skillFastAttack = skill;
			return false;
		}
	}
	skill = SkillControl.getPossessionSkill(passive, skilltype);
	if (SkillRandomizer.isSkillInvoked(passive, active, skill)) {
		
		// �U�����������������搧�U���̃X�L�����������A�t�ɑ��肪���ꍇ�͑��肩��U�����s����
		
		// attackEntry���Ȃ�����A�����_�Œǉ������͂ł��Ȃ��B
		// ��Œǉ��ł���悤�ɕۑ�����B
		virtualPassive.skillFastAttack = skill;
		return false;
	}
	
	return true;
};

SkillRandomizer.isSkillInvoked= function(active, passive, skill) {
	var skilltype;
	var result = false;
	
	if (skill === null) {
		return false;
	}
	
	skilltype = skill.getSkillType();
	
	if (skilltype === SkillType.FASTATTACK) {
		result = this._isFastAttack(active, passive, skill);
	}
	else if (skilltype === SkillType.CONTINUOUSATTACK) {
		result = this._isContinuousAttack(active, passive, skill);
	}
	else if (skilltype === SkillType.COUNTERATTACKCRITICAL) {
		result = this._isCounterattackCritical(active, passive, skill);
	}
	else if (skilltype === SkillType.DAMAGEABSORPTION) {
		result = this._isDamageAbsorption(active, passive, skill);
	}
	else if (skilltype === SkillType.TRUEHIT) {
		result = this._isTrueHit(active, passive, skill);
	}
	else if (skilltype === SkillType.NODAMAGE) {
		result = this._isNoDamage(active, passive, skill);
	}
	else if (skilltype === SkillType.SURVIVAL) {
		result = this._isSurvival(active, passive, skill);
	}
	else if (skill.getCustomKeyword()=='unbush') {
		result = this._isFastAttack(active, passive, skill);
	}
	else if (skill.getCustomKeyword()=='reduce-guard') {
		result = this._isReduceGuard(active, passive, skill);
	}
	return result;
};

SkillRandomizer._isReduceGuard= function(active, passive, skill) {
		return this._isSkillInvokedInternal(active, passive, skill);
};
//============================================================================================
//�����������̑���
//Probability.getProbability= function(percent) {
//	var n;
//	var n2;
//	
//	if (percent >= this.getMaxPercent()) {
//		// 100�ȏ�͖�������true��Ԃ�
//		return true;
//	}
//	
//	if (percent <= 0) {
//		return false;
//	}
//	
//	// n��0����99�̒l�ɂȂ�
//	n = this.getRandomNumber() % 100;
//	n2 = this.getRandomNumber() % 100;
//	
//	if(n > n2){
//		n = n2;
//	}
//	
//	root.log('n:' + n + '   n2:' + n2);
//	return percent >= n;
//};
//============================================================================================
AttackEvaluator.ActiveAction = defineObject(BaseAttackEvaluator,
{
	evaluateAttackEntry: function(virtualActive, virtualPassive, attackEntry) {
		var active = virtualActive.unitSelf;
		var passive = virtualPassive.unitSelf;
		
		//�X�L��[���f���[�X�K�[�h](����)�̏���
		//
		// �̊i��n���x�𓱓�����ۂ�A�p�����[�^�̕��т�ς��Ă���ꍇ
		// index�ʒu�ɂ���Ă͕s����N����\���L��B
		//
		var skill = SkillControl.getPossessionCustomSkill(active,'reduce-guard');
		
		if ((SkillRandomizer.isSkillInvoked(active, passive, skill)) && RealBattle._attackInfo === null) {
			//�X�L���\��
			attackEntry.skillArrayActive.push(skill);
			
			//�K������
			if(skill.custom.truehit==1){attackEntry.isHit = true;}
			
			if(skill.custom.increase_on==1){
				//active �́A���͂̃o�b�N�A�b�v
				var orig_str = active.getParamValue(1);
				var orig_mag = active.getParamValue(2);
				
				//active �́A���͂̏㏸
				//���ڃp�����[�^��M��Ƃ����\��
				var param = active.getParamValue(skill.custom.increase_index);
				var increased_str = orig_str + param;
				var increased_mag = orig_mag + param;
				
				active.setParamValue(1, increased_str);
				active.setParamValue(2, increased_mag);
			}
			//passive����A���h�̃o�b�N�A�b�v
			var orig_def = passive.getParamValue(6);
			var orig_mdf = passive.getParamValue(7);
			
			//passive����A���h�̒ቺ
			//���ڃp�����[�^��M��Ƃ����\���@�������p����ΓG�ɂ������p�ŁA�悳���ȈŖ��@�Ƃ���ꂻ��
			var reduce_def = skill.custom.reduce_def;
			var reduce_mdf = skill.custom.reduce_mdf;
			
			passive.setParamValue(6, orig_def - (Math.floor(orig_def * reduce_def / 100)));
			passive.setParamValue(7, orig_mdf - (Math.floor(orig_mdf * reduce_mdf / 100)));
			
			//root.log(passive.getName() + '�̎���� ' + reset_def + ' ���� ' + passive.getParamValue(6) + ' �ɉ��������I');
			
			// �^����_���[�W���Čv�Z����
			attackEntry.damagePassive = DamageCalculator.calculateDamage(virtualActive.unitSelf, virtualPassive.unitSelf, virtualActive.weapon, attackEntry.isCritical, virtualActive.totalStatus, virtualPassive.totalStatus);
			
			// �ቺ��������A���h�����ɖ߂�
			passive.setParamValue(6, orig_def);
			passive.setParamValue(7, orig_mdf);
			
			if(skill.custom.increase_on==1){
				active.setParamValue(1, orig_str);
				active.setParamValue(2, orig_mag);
			}
		}

		
		// �U�����󂯂鑤�̃_���[�W�̍ŏI�������s��
		attackEntry.damagePassive = this._arrangePassiveDamage(virtualActive, virtualPassive, attackEntry);
		//root.log(passive.getName() + '��' + attackEntry.damagePassive + '�̃_���[�W�I');
		
		// �U�������鑤�̃_���[�W�̍ŏI�������s���B
		// �ʏ�A�U�������鑤�Ƀ_���[�W�������邱�Ƃ͂Ȃ����߁AdamageActive�͌���0�ɂȂ�B
		// �_���[�W���}�C�i�X�ł���ꍇ�́A�񕜂Ƃ݂Ȃ����B
		attackEntry.damageActive = this._arrangeActiveDamage(virtualActive, virtualPassive, attackEntry);
	},

	_arrangePassiveDamage: function(virtualActive, virtualPassive, attackEntry) {
		var damagePassive = attackEntry.damagePassive;
	
		// ���肪�_���[�W���󂯂āAHP��0�ȉ��ɂȂ�ꍇ
		if (virtualPassive.hp - damagePassive < 0) {
			// �^����_���[�W�͑����HP�Ƃ���B
			// ���Ƃ��΁A�����HP3���_���[�W��5�̏ꍇ�A�_���[�W��3�ƂȂ�B
			damagePassive = virtualPassive.hp;
		}
		
		return damagePassive;
	},
	
	_arrangeActiveDamage: function(virtualActive, virtualPassive, attackEntry) {
		var max;
		var active = virtualActive.unitSelf;
		var damageActive = attackEntry.damageActive;
		var damagePassive = attackEntry.damagePassive;
		
		if (this._isAbsorption(virtualActive, virtualPassive, attackEntry)) {
			max = ParamBonus.getMhp(active);
			
			damageActive = damagePassive;
			
			if (virtualActive.hp + damageActive > max) {
				damageActive = max - virtualActive.hp;
			}
			
			// �_���[�W���}�C�i�X�ɂ���ƁA�񕜂̈Ӗ��ɂȂ�
			damageActive *= -1;
		}
		else {
			damageActive = 0;
		}
		
		return damageActive;
	},
	
	_isAbsorption: function(virtualActive, virtualPassive, attackEntry) {
		var isWeaponAbsorption;
		var active = virtualActive.unitSelf;
		var passive = virtualActive.unitSelf;
		var weapon = virtualActive.weapon;
		
		if (weapon !== null && weapon.getWeaponOption() === WeaponOption.HPABSORB) {
			isWeaponAbsorption = true;
		}
		else {
			isWeaponAbsorption = false;
		}
		
		if (!isWeaponAbsorption) {
			// ����I�v�V�������z���������Ȃ��ꍇ�́A�X�L�����m�F
			isWeaponAbsorption = SkillControl.checkAndPushSkill(active, passive, attackEntry, true, SkillType.DAMAGEABSORPTION) !== null;
		}
		
		return isWeaponAbsorption;
	}
}
);
//============================================================================================
// �X�L��[����]��ύX

UnitCommand.configureCommands= function(groupArray) {
	this._appendUnitEvent(groupArray);
	this._appendTalkEvent(groupArray);
	groupArray.appendObject(UnitCommand.PlaceCommand);
	groupArray.appendObject(UnitCommand.Quick);
	groupArray.appendObject(UnitCommand.Occupation);
	groupArray.appendObject(UnitCommand.Treasure);
	groupArray.appendObject(UnitCommand.Village);
	groupArray.appendObject(UnitCommand.Shop);
	groupArray.appendObject(UnitCommand.Gate);
	groupArray.appendObject(UnitCommand.Attack);
	//�u�U���v����Ɂu���ށv�������̂��C�ɓ���Ȃ�
	groupArray.appendObject(UnitCommand.Steal);
	groupArray.appendObject(UnitCommand.Wand);
	groupArray.appendObject(UnitCommand.Information);
	groupArray.appendObject(UnitCommand.Item);
	groupArray.appendObject(UnitCommand.Trade);
	groupArray.appendObject(UnitCommand.Stock);
	groupArray.appendObject(UnitCommand.Wait);
};


// �f�t�H�́w�ȏ�x�����ǁw������x����Ȃ��Ⴤ�_
Miscellaneous.isStealEnabled= function(unit, targetUnit, value) {
	if (value & StealFlag.SPEED) {
		// �������肪�L���ȏꍇ�́A����̑����𒴂��Ă��Ȃ���Γ��߂Ȃ�
		return ParamBonus.getSpd(unit) > ParamBonus.getSpd(targetUnit);
	}
	
	return true;
};

// �́@�i�@���@�S�@��
Miscellaneous.isStealTradeDisabled= function(unit, item, value) {
	if (!(value & StealFlag.WEAPON) && item.isWeapon()) {
		// ������l�����Ȃ��ɂ��ւ�炸�A�Ώۂ�����̏ꍇ�͌����ł��Ȃ�
		return true;
	}
	
	if (value & StealFlag.WEIGHT) {
	var flag = unit.custom.bld;
	if(flag==null)
	//�̊i���ݒ肳��Ă��Ȃ��ꍇ�͖����ł���Ζ����Ƃ���
	{return ParamBonus.getStr(unit) < item.getWeight()}else
	// ���j�b�g�̑̊i���A�C�e���̏d���������ꍇ�͖���
	{return unit.custom.bld < item.getWeight()}

	}
	
	return this.isTradeDisabled(unit, item);
};
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
};