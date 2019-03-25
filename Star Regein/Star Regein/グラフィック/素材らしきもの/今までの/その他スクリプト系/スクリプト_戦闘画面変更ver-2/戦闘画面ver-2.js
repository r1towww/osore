//戦闘画面変更ver-2　作：1-239
//【概要】戦闘画面を変更します
//【使い方】
//まずフォルダ内の戦闘画面変更ver-2をpictureフォルダにインポート
//リソース使用箇所→画像から
//戦闘クリスタル・戦闘上部・戦闘下部の画像を"戦闘画面変更ver-2"に変更するだけ
//…おい。手抜きっていうんじゃない
//
// 5/29 とりあえず公開
//=========================================================
UIBattleLayout._drawNameArea = function(unit, isRight) {
var x, y;
var text = unit.getName();
var color = ColorValue.DEFAULT;
var font = TextRenderer.getDefaultFont();
var range = createRangeObject();
if (isRight) {x = 350;y = 70;}
else {x = 70;y = 70;}
range.x = x;
range.y = y;
range.width = 185;
range.height = 25;
TextRenderer.drawRangeText(range, TextFormat.CENTER, text, -1, color, font);}
	
UIBattleLayout._drawWeaponArea = function (unit, isRight) {}
	
UIBattleLayout._drawFaceArea = function(unit, isRight) {}
	
UIBattleLayout._drawInfoArea = function(unit, isRight) {}
	
UIBattleLayout._drawHpArea = function(unit, isRight) {
var x, gauge, hp, xNumber, yNumber;
var y = 90;
var dx = 110;
var dyNumber = 12;
var pic = root.queryUI('battle_gauge');
if (isRight) {
x = this._getBattleAreaWidth() - this._gaugeRight.getGaugeWidth() - dx ;
gauge = this._gaugeRight;
hp = this._gaugeRight.getBalancer().getCurrentValue();
xNumber = 380;
yNumber = y - dyNumber;}
else {x = dx;
gauge = this._gaugeLeft;
hp = this._gaugeLeft.getBalancer().getCurrentValue();
xNumber = 260;
yNumber = y - dyNumber;}
gauge.drawGaugeBar(x, y, pic);
NumberRenderer.drawAttackNumberCenter(xNumber, yNumber, hp);}
