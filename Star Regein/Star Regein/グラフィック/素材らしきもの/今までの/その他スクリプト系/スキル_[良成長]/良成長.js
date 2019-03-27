BaseUnitParameter.getUnitTotalGrowthBonus = function(unit, index) {
		var i, count, item, n, id;
		
		//指定されたスキルを所持している場合ユニットの成長率に+10する
		if (SkillControl.getPossessionCustomSkill(unit,'Growth+')) {
		var d = this.getGrowthBonus(unit.getClass()) + 10;}
		else{var d = this.getGrowthBonus(unit.getClass()) ;}

		var weapon = ItemControl.getEquippedWeapon(unit);
		var arr = [];
		
		if (weapon !== null) {
			d += this.getGrowthBonus(weapon);
		}
		
		count = UnitItemControl.getPossessionItemCount(unit);
		for (i = 0; i < count; i++) {
			item = UnitItemControl.getItem(unit, i);
			if (item !== null && !item.isWeapon()) {
				id = item.getId();
				if (arr.indexOf(id) !== -1) {
					continue;
				}
				arr.push(id);
				
				n = this.getGrowthBonus(item);
				if (n !== 0 && ItemControl.isItemUsable(unit, item)) {
					d += n;
				}
			}
		}
		
		return d;
	}