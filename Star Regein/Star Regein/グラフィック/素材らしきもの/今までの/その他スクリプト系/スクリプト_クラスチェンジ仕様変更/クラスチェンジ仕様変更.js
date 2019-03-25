//================================================
MultiClassChangeScreen._completeScreenMemberData = function(screenParam,lange) {
		var group, classGroupId;
		var classEntryArray = [];

		if (this._isMapCall) {
			if (DataConfig.isBattleSetupClassChangeAllowed()) {
			classGroupId = this._unit.getClass().custom.change;}
			else  {
			//アイテム選択の時に判別したカスタムパラメータによって
			//クラスチェンジ先を決める
			if (this._unit.custom.flag == 1 ){
			classGroupId = this._unit.getClassGroupId1()}
			else{if (this._unit.custom.flag == 2 ){
			classGroupId = this._unit.getClassGroupId2()}
			else{classGroupId = this._unit.getClass().custom.change;}}
			}}
			else {if (this._unit.custom.flag == 1 ){
			classGroupId = this._unit.getClassGroupId1()}
			else{if (this._unit.custom.flag == 2 ){
			classGroupId = this._unit.getClassGroupId2()}
			else{classGroupId = this._unit.getClass().custom.change;}}
			}

		group = ClassChangeChecker.getClassGroup(classGroupId);

		if (group !== null) {
		classEntryArray = ClassChangeChecker.createClassEntryArray(this._unit, group);}

		if (classEntryArray.length > 0) {
		this._questionWindow.setQuestionMessage(StringTable.ClassChange_UnitClassChange);
		this._classSelectWindow.setClassSelectData(this._unit, classEntryArray);
		this._classInfoWindow.setClassInfoData(this._unit, classEntryArray[0]);
		this._classParameterWindow.setClassParameterData(this._unit, classEntryArray[0]);
		this._classEntryArray = classEntryArray;
		this.changeCycleMode(MultiClassChangeMode.TOP);}

		else {this._infoWindow.setInfoMessage(StringTable.ClassChange_UnableClassChange);
		this.changeCycleMode(MultiClassChangeMode.NOCHANGE);}
}
	
ClassChangeSelectManager._checkGroup = function(unit, item) {
		var i, count, classGroupId, classUpCount, classUpMaxCount;
		var group = null;

		var info = item.getClassChangeInfo();
		if (DataConfig.isBattleSetupClassChangeAllowed()) {
		classGroupId = this._unit.getClass().custom.change;}
		else {
		//アイテムの射程でクラスチェンジ先を判別する
		//もう一つの方の処理だとアイテムによる判別が出来ないので
		//カスタムパラメータを変化させて判別できるようにする
		var lange = item.getRangeValue();
		if (lange == 2) {
		this._unit.custom.flag = 1;
		classGroupId = this._unit.getClassGroupId1();}
		else{if (lange == 3) {
		this._unit.custom.flag = 2;
		classGroupId = this._unit.getClassGroupId2();}
		else{
		this._unit.custom.flag = 0;
		classGroupId = this._unit.getClass().custom.change;}}}

		if (classGroupId === -1) {
		this._infoWindow.setInfoMessage(StringTable.ClassChange_UnableClassChange);
		this.changeCycleMode(ClassChangeSelectMode.MSG);
		return null;}

		count = info.getClassGroupCount();
		for (i = 0; i < count; i++) {
		group = info.getClassGroupData(i);
		if (group.getId() === classGroupId) {
		break;}}

		if (i === count) {
		this._infoWindow.setInfoMessage(StringTable.ClassChange_UnableClassChangeItem);
		this.changeCycleMode(ClassChangeSelectMode.MSG);
		return null;
		}
	return group;
}