/*--------------------------------------------------------------------------
殺し・回避・達人設定スクリプト 作:1-239

【概要】
FE覚醒の〇殺しスキルとベルサガの〇回避を設定するスクリプト
本来だったらsingleton-calculatorの中に突っ込んでたけど
以下の長ったらしいスクリプトを沢山コピペすると非常に見づらいので別に作成
とり 剣槍斧弓魔 殺し
　　 剣槍斧弓魔 回避
　　 剣槍斧弓魔 の達人は実装。もっと作りたい場合はコピペで
キーワードはそれぞれ

[sword-killer]
[rance-killer]
[axe-killer]
[bow-killer]
[magic-killer]
----------------------------
[sword-iveid]
[rance-iveid]
[axe-iveid]
[bow-iveid]
[magic-iveid]
----------------------------
[sword-master]
[rance-master]
[axe-master]
[bow-master]
[magic-master]

〇殺し…相手が〇の武器を装備している場合 命中・回避+50
〇回避…〇を装備した相手と戦う時、相手の命中上限が33になる
〇の達人…〇を装備している時ダメ+5
-------------------------------------------------------------------------*/
var Buster = {
chackweapon: function(active, passive, weapon, activeTotalStatus, passiveTotalStatus) {

hit = HitCalculator.calculateSingleHit(active, passive, weapon, activeTotalStatus);

var wpt = ItemControl.getEquippedWeapon(passive); 
if( wpt == null ) 
{ //武器持ってない時の処理 
return hit; 
}
else 
{ 
	//剣殺しスキルを所持してるか
	var skill = SkillControl.getPossessionCustomSkill(active,'sword-killer');
	if (SkillControl.getPossessionCustomSkill(active,'sword-killer')){
	var wpt = passive.getItem(0).isWeapon();
	//持っているアイテムは武器かどうか
	if (wpt == true){
	wptype = passive.getItem(0).getWeaponType().getId();
	//武器タイプを代入する
	var cltype = passive.getClass().getAttackTemplateType();
	var bonus = skill.custom.param_bonus;
	//クラスタイプを代入する。
	//武器タイプ=0(剣)・クラスタイプ=0(戦士系)なら補正追加
	if(wptype == 0){if(cltype == 0){hit += bonus;}}}}

	var skill = SkillControl.getPossessionCustomSkill(passive,'sword-killer');
	if (SkillControl.getPossessionCustomSkill(passive,'sword-killer')){
	var wpt = active.getItem(0).isWeapon();
	if (wpt == true){
	wptype = active.getItem(0).getWeaponType().getId();
	var cltype = active.getClass().getAttackTemplateType();
	var bonus = skill.custom.param_bonus;
	if(wptype == 0){if(cltype == 0){hit -= bonus;}}}}
	

	//槍殺し
	var skill = SkillControl.getPossessionCustomSkill(active,'rance-killer');
	if (SkillControl.getPossessionCustomSkill(active,'rance-killer')){
	var wpt = passive.getItem(0).isWeapon();
	if (wpt == true){
	wptype = passive.getItem(0).getWeaponType().getId();
	var cltype = passive.getClass().getAttackTemplateType();
	var bonus = skill.custom.param_bonus;
	if(wptype == 1){if(cltype == 0){hit += bonus;}}}}

	var skill = SkillControl.getPossessionCustomSkill(passive,'rance-killer');
	if (SkillControl.getPossessionCustomSkill(passive,'rance-killer')){
	var wpt = active.getItem(0).isWeapon();
	if (wpt == true){
	wptype = active.getItem(0).getWeaponType().getId();
	var cltype = active.getClass().getAttackTemplateType();
	var bonus = skill.custom.param_bonus;
	if(wptype == 1){if(cltype == 0){hit -= bonus;}}}}

	//斧殺し
	var skill = SkillControl.getPossessionCustomSkill(active,'axe-killer');
	if (SkillControl.getPossessionCustomSkill(active,'axe-killer')){
	var wpt = passive.getItem(0).isWeapon();
	if (wpt == true){
	wptype = passive.getItem(0).getWeaponType().getId();
	var cltype = passive.getClass().getAttackTemplateType();
	var bonus = skill.custom.param_bonus;
	if(wptype == 2){if(cltype == 0){hit += bonus;}}}}

	var skill = SkillControl.getPossessionCustomSkill(passive,'axe-killer');
	if (SkillControl.getPossessionCustomSkill(passive,'axe-killer')){
	var wpt = active.getItem(0).isWeapon();
	if (wpt == true){
	wptype = active.getItem(0).getWeaponType().getId();
	var cltype = active.getClass().getAttackTemplateType();
	var bonus = skill.custom.param_bonus;
	if(wptype == 2){if(cltype == 0){hit -= bonus;}}}}

	//弓殺し
	var skill = SkillControl.getPossessionCustomSkill(active,'bow-killer');
	if (SkillControl.getPossessionCustomSkill(active,'bow-killer')){
	var wpt = passive.getItem(0).isWeapon();
	if (wpt == true){
	//弓攻撃全部に補正を掛けるため武器タイプの分岐は無し
	var cltype = passive.getClass().getAttackTemplateType();
	var bonus = skill.custom.param_bonus;
	if(cltype == 1){hit += bonus;}}}

	var skill = SkillControl.getPossessionCustomSkill(passive,'bow-killer');
	if (SkillControl.getPossessionCustomSkill(passive,'bow-killer')){
	var wpt = active.getItem(0).isWeapon();
	if (wpt == true){
	var cltype = active.getClass().getAttackTemplateType();
	var bonus = skill.custom.param_bonus;
	if(cltype == 1){hit -= bonus;}}}

	//魔殺し
	var skill = SkillControl.getPossessionCustomSkill(active,'magic-killer');
	if (SkillControl.getPossessionCustomSkill(active,'magic-killer')){
	var wpt = passive.getItem(0).isWeapon();
	if (wpt == true){
	var cltype = active.getClass().getAttackTemplateType();
	var bonus = skill.custom.param_bonus;
	if(cltype == 2){hit += bonus;}}}

	var skill = SkillControl.getPossessionCustomSkill(passive,'magic-killer');
	if (SkillControl.getPossessionCustomSkill(passive,'magic-killer')){
	var wpt = active.getItem(0).isWeapon();
	if (wpt == true){
	var cltype = active.getClass().getAttackTemplateType();
	var bonus = skill.custom.param_bonus;
	if(cltype == 2){hit -= bonus;}}}

return hit;

}
},

/*--------------------------------------------------------------------------
ここまで殺しスキル設定
--------------------------------------------------------------------------*/

chackiveid: function(active, passive, weapon, passiveTotalStatus, hit, avoid){
var percent = hit - avoid;

	//剣回避スキルを所持してるか
	var skill = SkillControl.getPossessionCustomSkill(passive,'sword-iveid');
	if (SkillControl.getPossessionCustomSkill(passive,'sword-iveid')){
	wptype = active.getItem(0).getWeaponType().getId();
	var cltype = active.getClass().getAttackTemplateType();
	var bonus = skill.custom.param_bonus;
	if(wptype == 0){if(cltype == 0){if(percent >= bonus){
	percent = bonus;}}}}
	
	//槍回避
	var skill = SkillControl.getPossessionCustomSkill(passive,'rance-iveid');
	if (SkillControl.getPossessionCustomSkill(passive,'rance-iveid')){
	wptype = active.getItem(0).getWeaponType().getId();
	var cltype = active.getClass().getAttackTemplateType();
	var bonus = skill.custom.param_bonus;
	if(wptype == 1){if(cltype == 0){if(percent >= bonus){
	percent = bonus;}}}}

	//斧回避
	var skill = SkillControl.getPossessionCustomSkill(passive,'axe-iveid');
	if (SkillControl.getPossessionCustomSkill(passive,'axe-iveid')){
	wptype = active.getItem(0).getWeaponType().getId();
	var cltype = active.getClass().getAttackTemplateType();
	var bonus = skill.custom.param_bonus;
	if(wptype == 2){if(cltype == 0){if(percent >= bonus){
	percent = bonus;}}}}

	//弓回避
	var skill = SkillControl.getPossessionCustomSkill(passive,'bow-iveid');
	if (SkillControl.getPossessionCustomSkill(passive,'bow-iveid')){
	var cltype = active.getClass().getAttackTemplateType();
	var bonus = skill.custom.param_bonus;
	if(cltype == 1){if(percent >= bonus){
	percent = bonus;}}}

	//魔回避
	var skill = SkillControl.getPossessionCustomSkill(passive,'magic-iveid');
	if (SkillControl.getPossessionCustomSkill(passive,'magic-iveid')){
	var cltype = active.getClass().getAttackTemplateType();
	var bonus = skill.custom.param_bonus;
	if(cltype == 2){if(percent >= bonus){
	percent = bonus;}}}

return percent;

},

/*--------------------------------------------------------------------------
ここまで回避スキル設定
--------------------------------------------------------------------------*/

chackmuster: function(unit){
var master;
var wpt = ItemControl.getEquippedWeapon(unit); 

if( wpt == null ) 
{ //武器持ってない時の処理 
return hit; 
}
else 
{ 
master = 0;
if (SkillControl.getPossessionCustomSkill(unit,'sword-master')) {
	var wpt = unit.getItem(0).getWeaponType().getId();
	var cltype = unit.getClass().getAttackTemplateType();
	if(wpt == 0){if(cltype == 0){master = 5;}}}

if (SkillControl.getPossessionCustomSkill(unit,'rance-master')) {
	var wpt = unit.getItem(0).getWeaponType().getId();
	var cltype = unit.getClass().getAttackTemplateType();
	if(wpt == 1){if(cltype == 0){master = 5;}}}

if (SkillControl.getPossessionCustomSkill(unit,'axe-master')) {
	var wpt = unit.getItem(0).getWeaponType().getId();
	var cltype = unit.getClass().getAttackTemplateType();
	if(wpt == 2){if(cltype == 0){master = 5;}}}

if (SkillControl.getPossessionCustomSkill(unit,'bow-master')) {
	var cltype = unit.getClass().getAttackTemplateType();
	if(cltype == 1){master = 5;}}

if (SkillControl.getPossessionCustomSkill(unit,'magic-master')) {
	var cltype = unit.getClass().getAttackTemplateType();
	if(cltype == 2){master = 5;}}

	return master;

}
}};