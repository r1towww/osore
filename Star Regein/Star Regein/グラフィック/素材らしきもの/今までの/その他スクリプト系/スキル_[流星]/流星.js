
/*--------------------------------------------------------------------------
スキル[流星]　作:1-239
  
【概要】
敵に５回攻撃を行います

【使用方法】
スキルでカスタムを選択し、キーワードに[5attack]を設定します。
  
 5/30 とり高

あと流星と連続が同時発動した場合、連続の表示が出て来ませんが
ちゃんと攻撃回数は２倍になっています

--------------------------------------------------------------------------*/

(function() {
//
//ここは正直言ってよく分からない
//多分確率発動スキルの定義をしてるんだと思う
//
var alias1 = SkillRandomizer.isCustomSkillInvokedInternal;
SkillRandomizer.isCustomSkillInvokedInternal = function(active, passive, skill, keyword) {
	if (keyword === '5attack') {
		// 発動型でない場合は、単純にtrueを返すだけでよい
		return this._isSkillInvokedInternal(active, passive, skill);
	}
	
	return alias1.call(this, active, passive, skill, keyword);
};

var alias2 = NormalAttackOrderBuilder._getAttackCount;
NormalAttackOrderBuilder._getAttackCount = function(virtualActive, virtualPassive) {
	var attackCount = alias2.call(this, virtualActive, virtualPassive);
		//流星のスキルがあるなら判定する
		skill = SkillControl.getPossessionCustomSkill(virtualActive.unitSelf,'5attack');
		if(SkillRandomizer.isCustomSkillInvoked(virtualActive.unitSelf, virtualPassive.unitSelf, skill,'5attack')){
			attackCount *= 5;
			// attackEntryがないから、現時点で追加処理はできない。
			// 後で追加できるように保存する。
			virtualActive.skillContinuousAttack = skill;
			}

		return attackCount;
	}

})();
