/*--------------------------------------------------
ランスシステム　作 1-239

【概要】
ベルサガのランス系武器を実装します

【導入方法】
武器のカスタムパラメータに{distance:3}のように記述
この場合、ダメージが 力+武器威力+(カスタム*移動距離)となります

例)力5のキャラに威力5、{distance:3}の武器を持たせて４マス移動した場合
5 + 5 + ( 3 * 4 ) = 22

　 力5のキャラに威力0、{distance:5}の武器を持たせて７マス移動した場合
5 + 0 + ( 5 * 7 ) = 37

このスクリプトを使用してゲームバランスが崩壊しても私(1-239)は一切責任を負いません

6/15 と公

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
}

AbilityCalculator.getPower = function(unit, weapon){
		var pow;
		var movbonus = unit.getMostResentMov();
		var wpc = weapon.custom.distance;

		var attack;

		if (Miscellaneous.isPhysicsBattle(weapon)) {
			// 物理攻撃または投射攻撃
			pow = RealBonus.getStr(unit);
		}
		else {
			// 魔法攻撃
			pow = RealBonus.getMag(unit);
		}
		
		// 武器の威力 + (力 or 魔力)
		if(typeof wpc == 'number'){rance = movbonus * wpc}else{rance=0;}

		attack = pow + weapon.getPow() + rance;

		return attack;
}