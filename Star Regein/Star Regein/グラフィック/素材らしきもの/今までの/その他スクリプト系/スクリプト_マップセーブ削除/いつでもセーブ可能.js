//いつでもセーブ可能　作:1-239
//【概要】
//いつでもセーブできます
//それだけ
//
// 5/29 公開
//
﻿MapCommand.configureCommands = function(groupArray) {
		// 行動していても、セーブを表示
		groupArray.appendObject(MapCommand.Save);
		groupArray.appendObject(MapCommand.Objective);
		groupArray.appendObject(MapCommand.ConfigMenu);
		if (root.isSwitchCommandDisplayable()) {
			groupArray.appendObject(MapCommand.Switch);
		}
		if (root.isVariableCommandDisplayable()) {
			groupArray.appendObject(MapCommand.Variable);
		}
		if (EnvironmentControl.isLoadCommand()) {
			groupArray.appendObject(MapCommand.Load);
		}
		groupArray.appendObject(MapCommand.TurnEnd);
	}