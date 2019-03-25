(function() {
var alias1 = SkillRandomizer.isCustomSkillInvokedInternal;
SkillRandomizer.isCustomSkillInvokedInternal = function(active, passive, skill, keyword) {
	if (keyword === 'One-kill') {
		return this._isSkillInvokedInternal(active, passive, skill);
	}
	if (keyword === 'One-kill()') {
		return this._isSkillInvokedInternal(active, passive, skill);
	}
	return alias1.call(this, active, passive, skill, keyword);
};

var alias2 = AttackEvaluator.HitCritical.calculateDamage;
AttackEvaluator.HitCritical.calculateDamage = function(virtualActive, virtualPassive, entry) {
	var damage = alias2.call(this, virtualActive, virtualPassive, entry);
	
	// スキルが発動した場合は、ダメージに相手のHPを代入する
	if (SkillControl.checkAndPushCustomSkill(virtualActive.unitSelf, virtualPassive.unitSelf, entry, true, 'One-kill') !== null) {
	return virtualPassive.hp;
	}
	if (SkillControl.checkAndPushCustomSkill(virtualActive.unitSelf, virtualPassive.unitSelf, entry, true, 'One-kill()') !== null) {
	return virtualPassive.hp - 1;
	}

	return damage;

};

})();
