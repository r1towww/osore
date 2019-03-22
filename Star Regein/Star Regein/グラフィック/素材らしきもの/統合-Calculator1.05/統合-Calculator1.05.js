/*--------------------------------------------------------------------------
  
  FE封印を参考にした計算式です
  クラスのカスタムパラメータに{bld}(体格)
　が設定されている場合それを、
　設定されていない場合力(魔力)で重さを軽減します

　[殺し・回避・達人設定スクリプト1.03.js]も必ず導入してください

--------------------------------------------------------------------------*/
AbilityCalculator.getPower = function(unit, weapon) {
	var pow;
	var movbonus = unit.getMostResentMov();

	if (Miscellaneous.isPhysicsBattle(weapon)) {
		// 物理攻撃または投射攻撃
		pow = RealBonus.getStr(unit);
	}
	else {
		// 魔法攻撃
		pow = RealBonus.getMag(unit);
	}
	
	// スキル[集中]の処理
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
	
	// スキル[一匹狼]の処理
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

	// ランスの処理
	if(typeof weapon.custom.distance == 'number'){
	rance = weapon.custom.distance * movbonus;}else{rance=0;}

	//スキル[手加減]の処理
	if (SkillControl.getPossessionCustomSkill(unit,'allowance')){
	pow /= 2;
	pow = Math.floor(pow);
	}

	// 武器の威力 + (力 or 魔力)
	return pow + weapon.getPow() + rance;
};
//============================================================================================
AbilityCalculator.getHit = function(unit, weapon) {	
	var cls = unit.getClass();
	var hitb = cls.custom.hitp;
	
	// 武器の命中率 + (技 * 2) + (幸運/2)
	hit = weapon.getHit() + (RealBonus.getSki(unit) * 2) + (RealBonus.getLuk(unit) * 2);
	
	if (typeof cls.custom.hit !== 'number') {}
	else
	{hit += hitb;};
	
	//スキル[一発屋]の処理
	if (SkillControl.getPossessionCustomSkill(unit,'one-hitter')) {
		hit -= 10;
	}	
	//スキル[質実剛健]の処理
	if (SkillControl.getPossessionCustomSkill(unit,'fortitude')){
		hit += 10;
	}
	//スキル[命中+]の処理
	var skill = SkillControl.getPossessionCustomSkill(unit,'hit+');
	if (SkillControl.getPossessionCustomSkill(unit,'hit+')){
	var bonus = skill.custom.param_bonus;
	hit += bouns;
	}

	//スキル[バイオ・偶数]の処理
	var skill = SkillControl.getPossessionCustomSkill(unit,'vaio-even');
	if (SkillControl.getPossessionCustomSkill(unit,'vaio-even')) {
	var Turn = root.getCurrentSession().getTurnCount() % 2;
	if (Turn == 0 ){var bonus = skill.custom.param_bonus;
	hit += bonus;}}

	//スキル[バイオ・奇数]の処理
	var skill = SkillControl.getPossessionCustomSkill(unit,'vaio-odd');
	if (SkillControl.getPossessionCustomSkill(unit,'vaio-odd')) {
	var Turn = root.getCurrentSession().getTurnCount() % 2;
	if (Turn == 1 ){var bonus = skill.custom.param_bonus;
	hit += bonus;}}

	//スキル[完璧主義]の処理
	var skill = SkillControl.getPossessionCustomSkill(unit,'Per-fect');
	if (SkillControl.getPossessionCustomSkill(unit,'Per-fect')) {
	var HPflag = unit.getHP() - RealBonus.getMhp(unit);
	var bonus = skill.custom.param_bonus;
	if(HPflag == 0){hit += bonus;}}

	//スキル[スロースタート]の処理
	if (SkillControl.getPossessionCustomSkill(unit,'slow-start')) {
	var Turn = root.getCurrentSession().getTurnCount();
	if (Turn <= 16){Turn = 16;}
	hit += Turn;}

	//スキル[ホットスタート]の処理
	if (SkillControl.getPossessionCustomSkill(unit,'hot-start')) {
	var Turn = root.getCurrentSession().getTurnCount() - 16;
	if (Turn <= 0){Turn = 0;}
	hit += Turn;}

	//スキル[ラッキー7]の処理
	var skill = SkillControl.getPossessionCustomSkill(unit,'lucky-7');
	if (SkillControl.getPossessionCustomSkill(unit,'lucky-7')) {
	var Turn = root.getCurrentSession().getTurnCount() - 7;
	if (Turn <= 0){hit += 33;}}

	// スキル[屋外戦闘]を持っている場合は、地形によって回避率を加算する
	if (cls.getClassType().isTerrainBonusEnabled() && SkillControl.getPossessionCustomSkill(unit,'out_combat')) {
		var skill = SkillControl.getPossessionCustomSkill(unit,'out_combat');
		var bonus = skill.custom.param_bonus;
		terrain = PosChecker.getTerrainFromPos(unit.getMapX(), unit.getMapY());
		if(terrain.custom.location!==1){
			hit += bonus;
		}
	}
	// スキル[屋内戦闘]を持っている場合は、地形によって回避率を加算する
	if (cls.getClassType().isTerrainBonusEnabled() && SkillControl.getPossessionCustomSkill(unit,'in_combat')) {
		var skill = SkillControl.getPossessionCustomSkill(unit,'in_combat');
		var bonus = skill.custom.param_bonus;
		terrain = PosChecker.getTerrainFromPos(unit.getMapX(), unit.getMapY());
		if(terrain.custom.location==1){
			hit += bonus;
		}
	}
	// スキル[疾駆]の処理
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
	//スキル[手加減]の処理
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
		
	// 回避は、(敏捷 * 2 + 幸運)
	avoid = agi * 2 + RealBonus.getLuk(unit);
	
	//スキル[回避上昇]の処理
	if (SkillControl.getPossessionCustomSkill(unit,'avo-up')){
	avoid += agi;}

	if (typeof cls.custom.avo !== 'number') {}
	else
	{avoid += avob;};
	
	//スキル[回避+10]の処理
	var skill = SkillControl.getPossessionCustomSkill(unit,'avoid+');
	if (SkillControl.getPossessionCustomSkill(unit,'avoid+')){
		var skill = SkillControl.getPossessionCustomSkill(unit,'avoid+');
		var bonus = skill.custom.param_bonus;
		avoid += bonus;
	}
	
	//スキル[完璧主義]の処理
	var skill = SkillControl.getPossessionCustomSkill(unit,'Per-fect');
	if (SkillControl.getPossessionCustomSkill(unit,'Per-fect')) {
	var HPflag = unit.getHP() - RealBonus.getMhp(unit);
	var bonus = skill.custom.param_bonus;
	if(HPflag == 0){avoid += bonus;}}

	//スキル[バイオ・偶数]の処理
	var skill = SkillControl.getPossessionCustomSkill(unit,'vaio-even');
	if (SkillControl.getPossessionCustomSkill(unit,'vaio-even')) {
	var Turn = root.getCurrentSession().getTurnCount() % 2;
	if (Turn == 0 ){var bonus = skill.custom.param_bonus;
	avoid += bonus;}}

	//スキル[バイオ・奇数]の処理
	var skill = SkillControl.getPossessionCustomSkill(unit,'vaio-odd');
	if (SkillControl.getPossessionCustomSkill(unit,'vaio-odd')) {
	var Turn = root.getCurrentSession().getTurnCount() % 2;
	if (Turn == 1 ){var bonus = skill.custom.param_bonus;
	avoid += bonus;}}

	//スキル[スロースタート]の処理
	if (SkillControl.getPossessionCustomSkill(unit,'slow-start')) {
	var Turn = root.getCurrentSession().getTurnCount();
	if (Turn <= 16){Turn = 16;}
	avoid += Turn;}

	//スキル[ホットスタート]の処理
	if (SkillControl.getPossessionCustomSkill(unit,'hot-start')) {
	var Turn = root.getCurrentSession().getTurnCount() - 16;
	if (Turn <= 0){Turn = 0;}
	avoid += Turn;}

	//スキル[ラッキー7]の処理
	var skill = SkillControl.getPossessionCustomSkill(unit,'lucky-7');
	if (SkillControl.getPossessionCustomSkill(unit,'lucky-7')) {
	var Turn = root.getCurrentSession().getTurnCount() - 7;
	if (Turn <= 0){avoid += 33;}}

	// クラス系統が地形ボーナスを考慮する場合は、地形効果の回避率を加算する
	// スキル[回避機動]を持っている場合も地形効果を受ける
	if (cls.getClassType().isTerrainBonusEnabled() || SkillControl.getPossessionCustomSkill(unit,'avoid_maneuver')) {
		terrain = PosChecker.getTerrainFromPos(unit.getMapX(), unit.getMapY());
		
		//スキル[迷彩]の処理
		if (SkillControl.getPossessionCustomSkill(unit,'Camouflage')) {
		avoid += terrain.getAvoid() * 15 / 10;}
		else{avoid += terrain.getAvoid();}
	}
	// スキル[屋外戦闘]を持っている場合は、地形によって回避率を加算する
	if (cls.getClassType().isTerrainBonusEnabled() && SkillControl.getPossessionCustomSkill(unit,'out_combat')) {
		var skill = SkillControl.getPossessionCustomSkill(unit,'out_combat');
		var bonus = skill.custom.param_bonus;
		terrain = PosChecker.getTerrainFromPos(unit.getMapX(), unit.getMapY());
		if(terrain.custom.location!==1){
			avoid += bonus;
		}
	}
	// スキル[屋内戦闘]を持っている場合は、地形によって回避率を加算する
	if (cls.getClassType().isTerrainBonusEnabled() && SkillControl.getPossessionCustomSkill(unit,'in_combat')) {
		var skill = SkillControl.getPossessionCustomSkill(unit,'in_combat');
		var bonus = skill.custom.param_bonus;
		terrain = PosChecker.getTerrainFromPos(unit.getMapX(), unit.getMapY());
		if(terrain.custom.location==1){
			avoid += bonus;
		}
	}
	// スキル[疾駆]の処理
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
	// 技 / 2 + 武器のクリティカル率
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
	
	//スキル[一発屋]の処理
	if (SkillControl.getPossessionCustomSkill(unit,'one-hitter')) {
	cri += 10;}
	
	//スキル[質実剛健]の処理
	if (SkillControl.getPossessionCustomSkill(unit,'fortitude')) {
	cri -= 10;}
	
	//スキル[覚醒式怒り]の処理
	var skill = SkillControl.getPossessionCustomSkill(unit,'HP-crtup');
	if (SkillControl.getPossessionCustomSkill(unit,'HP-crtup')){
	var limit = skill.custom.skill_limit;
	var HPflag = (RealBonus.getMhp(unit) * limit / 100) - unit.getHP();
	if (HPflag >= 0 ){
	var bonus = skill.custom.param_bonus;
	cri += bonus;}}

	//スキル[死生の技]の処理
	if (SkillControl.getPossessionCustomSkill(unit,'Life-death')) {
	cri += 100 - ((unit.getHP() * 100) / RealBonus.getMhp(unit)) ;}

	// スキル[集中覚醒]の処理
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
	// 幸運がクリティカル回避率
	var criavoid = RealBonus.getLuk(unit);
	
	
	// スキル[死神]
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

		//スキル[装備上手]の処理
		// 重さ - 体格
		var skill = SkillControl.getPossessionCustomSkill(unit,'Equipped');
		if (SkillControl.getPossessionCustomSkill(unit,'Equipped')) {
		var bonus = skill.custom.param_bonus;
		bld +=  bonus;}
	
		value = weapon.getWeight() - bld;

		if (value > 0) {
			// 力(魔力)が重さより低いため、その差分だけ敏捷を下げる
			agi = spd - value;
		}
		else {
			agi = spd;
		}
	}
	else {
		// 重さを表示しない場合は、速さが敏捷と同一になる
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
	
	// アイテムが杖の場合は、使用者の魔力を加算する
	if (item.isWand()) {
		//スキル[癒し手]の処理
		//癒し手でないと魔力が半減
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
  
  経験値の取得
  
  [fe_class]
  0 : 				上級クラスとして扱う
  1 : 				下級クラスとして扱う
  
  [fe_type]
  1 : ソルジャー	敵としての撃破経験値が、レベル分低くなる
  2 : 盗賊			基礎経験値が、最終的に除算される値が2で計算される。　※デフォは3
  					撃破経験値が20増える（倍率は低くなるが、確実に経験値はもらえる。
					敵としての撃破経験値が3増える
  3 : マムクート	撃破経験値が20増える
  
  
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
	
	
	// ボーナス経験値がマイナスの場合は、勝利時に経験値を取得しない。
	// これは最終マップのリーダー撃破を想定したものである。
	if (bonusExp < 0) {
		return 0;
	}
	
	// 撃破時の経験値を固定にしているため、
	// クラスの追加経験値をそのまま返す。
	if (root.getUserExtension().isFixedExperience()) {
		return this._getValidExperience(bonusExp);
	}
	
	// 相手を倒した場合の処理
	exp = this._getNormalValue(active, activeHp, activeDamageTotal, passive, passiveHp, passiveDamageTotal);
	
	//相手が盗賊なら+3 相手がソルジャーなら敵レベル分マイナス
	if(p_fe_type == '1'){
		etcexp = etcexp - passive.getLv();
	}else if(p_fe_type == '2'){
		etcexp = 3;
	}
	//撃破経験値ベース
	addexp = (passive.getLv() * 3 - active.getLv() * 3);
	addexp += 20;
	
	//盗賊・マムクートは経験値+20
	if(a_fe_type == '2' || a_fe_type == '3'){
		addexp += 20;
	}
	
	//クラス階級補正
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
	
		//相手がリーダー、サブリーダーの場合は経験値を加算 
		//	◆↓必要であれば　下の二つのスラッシュを消してください　	
		//exp += this._getBonusExperience(passive);
	
	// 相手のクラスの追加経験値を加算
	exp += bonusExp;
	
	exp = Math.floor(exp);
	
	return this._getValidExperience(exp);
};

//基礎経験値
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
	
	
	//クラス補正 敵マムクートは上級クラスとして計算する
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
	
	// 相手を倒した場合の処理
	exp = baseExp + lv;
	
	// カスタムパラメータの 経験値倍率 *3(シーフとマムクートは*2）
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
			// 相手は不死身の場合は、命中率が100%にならない
			return 99;
		}
		return 100;
	}
	
	//殺しスキルの処理(設定スクリプトの呼び出し)
	hit = Buster.chackweapon(active, passive, weapon, passiveTotalStatus, hit);
	avoid = this.calculateAvoid(active, passive, weapon, passiveTotalStatus);

	//[先の先]
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
	//後の先 敵から攻撃された時、命中+10
		if (SkillControl.getPossessionCustomSkill(active,'fe_gosen')){
			var skill = SkillControl.getPossessionCustomSkill(active,'fe_gosen');
			var bonus = skill.custom.param_bonus;
			hit += bonus;
		}
	}
	if(turnType == active.getUnitType()){;
	//後の先 敵から攻撃された時、回避+10
		if (SkillControl.getPossessionCustomSkill(passive,'fe_gosen')){
			var skill = SkillControl.getPossessionCustomSkill(passive,'fe_gosen');
			var bonus = skill.custom.param_bonus;
			avoid += bonus;
		}
	}
	
	//下剋上スキル
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

		//怪力スキルの処理
		//自分の力-相手の力+5でマイナスならダメ+3
		var skill = SkillControl.getPossessionCustomSkill(active,'super-power');
		if (SkillControl.getPossessionCustomSkill(active,'super-power')) {
		var bonus = skill.custom.param_bonus;
		var limit = skill.custom.skill_limit;
		var acatk =active.getParamValue(1) - passive.getParamValue(1) + limit;
		if (acatk <= 0){pow += bonus;}}
		
		//死線スキル
		//自分のダメ計算時にスキル所持なら威力+10
		//相手のダメ計算時に自分がスキル所持なら威力+10
		var skill = SkillControl.getPossessionCustomSkill(active,'death-line');
		if (SkillControl.getPossessionCustomSkill(active,'death-line'))
		{var bonus = skill.custom.param_bonus;
		pow += bonus;}
		else{
		var skill = SkillControl.getPossessionCustomSkill(passive,'death-line');
		if (SkillControl.getPossessionCustomSkill(passive,'death-line'))
		{var bonus = skill.custom.param_bonus;
		pow += bonus;}}

		//居合スキル
		var skill = SkillControl.getPossessionCustomSkill(active,'iai-do');
		if (SkillControl.getPossessionCustomSkill(active,'iai-do')){
		var Turn = root.getCurrentSession().getTurnType();
		var Unty = active.getUnitType()
		var bonus = skill.custom.param_bonus;
		if (Turn == Unty){
		pow += bonus;}}
		
		//尊大スキル
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
		
		// 特攻無効のスキルを持っていない場合
		if (SkillControl.getFlagPossessionSkill(passive, SkillType.INVALID, InvalidFlag.EFFECTIVE) === null) {
		// 相手のクラスに対して、アイテムは特効か
		classdata = passive.getClass();

		if (ItemControl.isEffectiveClass(classdata, weapon)) {
		pow = Math.floor(pow * this.getEffectiveFactor());
		}else{

		//ただ下に突っ込むだけだと6倍特攻になる可能性があるので分岐
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
		// 防御無視の武器オプションがあるため、防御は0にする
		return 0;
	}
	
	if (Miscellaneous.isPhysicsBattle(weapon)) {
		// 物理攻撃または投射攻撃
		def = RealBonus.getDef(passive);
		// スキル[一匹狼]の処理
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
		// 魔法攻撃
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
		// 攻撃をしかけた方が先制攻撃のスキルを持つ場合は、その時点で通常戦闘と判断する
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
		
		// 攻撃をしかけた方が先制攻撃のスキルを持たず、逆に相手が持つ場合は相手から攻撃が行われる
		
		// attackEntryがないから、現時点で追加処理はできない。
		// 後で追加できるように保存する。
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
//実効命中率の操作
//Probability.getProbability= function(percent) {
//	var n;
//	var n2;
//	
//	if (percent >= this.getMaxPercent()) {
//		// 100以上は無条件にtrueを返す
//		return true;
//	}
//	
//	if (percent <= 0) {
//		return false;
//	}
//	
//	// nは0から99の値になる
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
		
		//スキル[レデュースガード](月光)の処理
		//
		// 体格や熟練度を導入する際や、パラメータの並びを変えている場合
		// index位置によっては不具合が起きる可能性有り。
		//
		var skill = SkillControl.getPossessionCustomSkill(active,'reduce-guard');
		
		if ((SkillRandomizer.isSkillInvoked(active, passive, skill)) && RealBattle._attackInfo === null) {
			//スキル表示
			attackEntry.skillArrayActive.push(skill);
			
			//必中処理
			if(skill.custom.truehit==1){attackEntry.isHit = true;}
			
			if(skill.custom.increase_on==1){
				//active 力、魔力のバックアップ
				var orig_str = active.getParamValue(1);
				var orig_mag = active.getParamValue(2);
				
				//active 力、魔力の上昇
				//直接パラメータを弄るという暴挙
				var param = active.getParamValue(skill.custom.increase_index);
				var increased_str = orig_str + param;
				var increased_mag = orig_mag + param;
				
				active.setParamValue(1, increased_str);
				active.setParamValue(2, increased_mag);
			}
			//passive守備、魔防のバックアップ
			var orig_def = passive.getParamValue(6);
			var orig_mdf = passive.getParamValue(7);
			
			//passive守備、魔防の低下
			//直接パラメータを弄るという暴挙　何か利用すれば敵にかける専用で、よさげな闇魔法とか作れそう
			var reduce_def = skill.custom.reduce_def;
			var reduce_mdf = skill.custom.reduce_mdf;
			
			passive.setParamValue(6, orig_def - (Math.floor(orig_def * reduce_def / 100)));
			passive.setParamValue(7, orig_mdf - (Math.floor(orig_mdf * reduce_mdf / 100)));
			
			//root.log(passive.getName() + 'の守備が ' + reset_def + ' から ' + passive.getParamValue(6) + ' に下がった！');
			
			// 与えるダメージを再計算する
			attackEntry.damagePassive = DamageCalculator.calculateDamage(virtualActive.unitSelf, virtualPassive.unitSelf, virtualActive.weapon, attackEntry.isCritical, virtualActive.totalStatus, virtualPassive.totalStatus);
			
			// 低下した守備、魔防を元に戻す
			passive.setParamValue(6, orig_def);
			passive.setParamValue(7, orig_mdf);
			
			if(skill.custom.increase_on==1){
				active.setParamValue(1, orig_str);
				active.setParamValue(2, orig_mag);
			}
		}

		
		// 攻撃を受ける側のダメージの最終調整を行う
		attackEntry.damagePassive = this._arrangePassiveDamage(virtualActive, virtualPassive, attackEntry);
		//root.log(passive.getName() + 'に' + attackEntry.damagePassive + 'のダメージ！');
		
		// 攻撃をする側のダメージの最終調整を行う。
		// 通常、攻撃をする側にダメージが生じることはないため、damageActiveは原則0になる。
		// ダメージがマイナスである場合は、回復とみなされる。
		attackEntry.damageActive = this._arrangeActiveDamage(virtualActive, virtualPassive, attackEntry);
	},

	_arrangePassiveDamage: function(virtualActive, virtualPassive, attackEntry) {
		var damagePassive = attackEntry.damagePassive;
	
		// 相手がダメージを受けて、HPが0以下になる場合
		if (virtualPassive.hp - damagePassive < 0) {
			// 与えるダメージは相手のHPとする。
			// たとえば、相手のHP3がダメージが5の場合、ダメージは3となる。
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
			
			// ダメージをマイナスにすると、回復の意味になる
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
			// 武器オプションが吸収を持たない場合は、スキルを確認
			isWeaponAbsorption = SkillControl.checkAndPushSkill(active, passive, attackEntry, true, SkillType.DAMAGEABSORPTION) !== null;
		}
		
		return isWeaponAbsorption;
	}
}
);
//============================================================================================
// スキル[盗む]を変更

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
	//「攻撃」より上に「盗む」がいくのが気に入らない
	groupArray.appendObject(UnitCommand.Steal);
	groupArray.appendObject(UnitCommand.Wand);
	groupArray.appendObject(UnitCommand.Information);
	groupArray.appendObject(UnitCommand.Item);
	groupArray.appendObject(UnitCommand.Trade);
	groupArray.appendObject(UnitCommand.Stock);
	groupArray.appendObject(UnitCommand.Wait);
};


// デフォは『以上』だけど『超える』じゃなきゃヤダ
Miscellaneous.isStealEnabled= function(unit, targetUnit, value) {
	if (value & StealFlag.SPEED) {
		// 速さ判定が有効な場合は、相手の速さを超えていなければ盗めない
		return ParamBonus.getSpd(unit) > ParamBonus.getSpd(targetUnit);
	}
	
	return true;
};

// 体　格　が　全　て
Miscellaneous.isStealTradeDisabled= function(unit, item, value) {
	if (!(value & StealFlag.WEAPON) && item.isWeapon()) {
		// 武器を考慮しないにも関わらず、対象が武器の場合は交換できない
		return true;
	}
	
	if (value & StealFlag.WEIGHT) {
	var flag = unit.custom.bld;
	if(flag==null)
	//体格が設定されていない場合力未満であれば無効とする
	{return ParamBonus.getStr(unit) < item.getWeight()}else
	// ユニットの体格がアイテムの重さを下回る場合は無効
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

		//ランス武器の場合、表記を変更する
		if(typeof item.custom.distance == 'number'){
		power =power + '+' + item.custom.distance + 'Ｍ';
		}
		TextRenderer.drawKeywordText(x, y,power, -1, color, font);
		x += 42;
		
		text = root.queryCommand('hit_capacity');
		ItemInfoRenderer.drawKeyword(x, y, text);
		x += ItemInfoRenderer.getSpaceX();
		NumberRenderer.drawRightNumber(x, y, item.getHit());
};