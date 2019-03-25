//射程表示修正　作:1-239
//
//【概要】装備してる武器より射程が長い武器持ってても 
//装備してる武器の射程しか行動範囲で表示されない"仕様"を修正
//わざわざif文で分岐させてるのを見るにバグじゃないんだよなぁ…
//
//【使い方】
//突っ込むだけ
//
// 5/22 とり公開
//=============================================
UnitRangePanel._setRangeData = function() {
var i, item, count;
var startRange = 99;
var endRange = 0;
var isWeapon = false;
// 自軍でない場合は、最も射程がある武器を参照する
// 自軍であっても、最も射程がある武器を参照する
count = UnitItemControl.getPossessionItemCount(this._unit);
for (i = 0; i < count; i++) {
item = UnitItemControl.getItem(this._unit, i);
if (ItemControl.isWeaponAvailable(this._unit, item)) {
if (item.getStartRange() < startRange) {
startRange = item.getStartRange();}
if (item.getEndRange() > endRange) {
endRange = item.getEndRange();}
isWeapon = true;}}
		
if (isWeapon) {
this._simulator.startSimulationWeapon(this._unit, ParamBonus.getMov(this._unit), startRange, endRange);
}else {
this._simulator.startSimulation(this._unit, ParamBonus.getMov(this._unit));}
		
this._mapChipLight.setLightType(MapLightType.MOVE);
this._mapChipLight.setIndexArray(this._simulator.getSimulationIndexArray());
if (isWeapon) {
this._mapChipLightWeapon.setLightType(MapLightType.RANGE);
this._mapChipLightWeapon.setIndexArray(this._simulator.getSimulationWeaponIndexArray());
}else{this._mapChipLightWeapon.endLight();}}