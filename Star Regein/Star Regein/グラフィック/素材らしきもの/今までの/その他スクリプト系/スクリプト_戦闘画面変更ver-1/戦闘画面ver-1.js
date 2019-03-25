//戦闘画面変更ver-1　作：1-239
//【概要】戦闘画面を変更します
//
//【使い方】
//まずフォルダ内の画像二つをpictureフォルダにインポート
//リソース使用箇所→画像から
//戦闘クリスタルと戦闘上部の画像を"非表示用"に変更
//戦闘下部の画像を"戦闘画面変更ver-1"に変更するだけ
//
// 5/22 とりあえず公開
//=========================================================
UIBattleLayout._drawNameArea = function(unit, isRight) {
var x, y;
var text = unit.getName();
var color = ColorValue.DEFAULT;
var font = TextRenderer.getDefaultFont();
var range = createRangeObject();
if (isRight) {x = 350;y = 370;}
else {x = 70;y = 370;}
range.x = x;
range.y = y;
range.width = 185;
range.height = 25;
TextRenderer.drawRangeText(range, TextFormat.CENTER, text, -1, color, font);}
	
UIBattleLayout._drawWeaponArea = function (unit, isRight) {
var x, y, width, height, item, text;
var color = ColorValue.DEFAULT;
var font = TextRenderer.getDefaultFont();
if (isRight) {item = this._itemRight;}
else {item = this._itemLeft;}
if (item === null) {return;}
text = item.getName();
width = TextRenderer.getTextWidth(text, font) + 24;
height = 25;
if (isRight) {x = 350;y = 385;}
	else {x = 70;y = 385;}
x += (185 - width) / 2;
y = Math.floor((y + (y + height)) / 2);
if (item !== null) {
ItemRenderer.drawItem(x, y, item, color, font, false);}}
	
UIBattleLayout._drawFaceArea = function(unit, isRight) {
var x, y;
var dx = 5;
var isReverse = false;
if (isRight) {
x = this._getBattleAreaWidth() - GraphicsFormat.FACE_WIDTH - dx;}
else {x = 0 + dx;isReverse = true;}
y = (0 + this._getBattleAreaHeight()) - GraphicsFormat.FACE_HEIGHT - 15;
ContentRenderer.drawUnitFace(x, y, unit, isReverse, 255);}
	
UIBattleLayout._drawInfoArea = function(unit, isRight) {
var x, y, arr;
var dx = 110;
var color = ColorValue.KEYWORD;
var font = TextRenderer.getDefaultFont();
if (isRight) {x = this._getBattleAreaWidth() - 190 - dx;
arr = this._statusRight;}
else {x = dx;
arr = this._statusLeft;}
y = 440;
StatusRenderer.drawAttackStatus(x, y, arr, color, font, 15);}
	
UIBattleLayout._drawHpArea = function(unit, isRight) {
var x, gauge, hp, xNumber, yNumber;
var y = 430;
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
