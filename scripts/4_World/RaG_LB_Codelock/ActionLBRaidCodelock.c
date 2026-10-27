modded class ActionLBRaidCodelock
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (super.ActionCondition(player, target, item))
			return true;
		if (!item || !LBCodelockConfig.Get || !LBCodelockConfig.Get.enableRaiding || !LBCodelockConfig.Get.IsRaidingActive())
			return false;

		LBCodelockRaidTool tool = LBCodelockConfig.Get.GetToolConfig(item.GetType());
		if (!tool || tool.totalRaidTime <= 0)
			return false;

		return RaGLBBridge.GetTargetLock(target) != null;
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		DigitalCodeLock lookedAtLock = DigitalCodeLock.Cast(action_data.m_Target.GetObject());
		if (lookedAtLock)
		{
			super.OnFinishProgressServer(action_data);
			return;
		}

		DigitalCodeLock codeLock = RaGLBBridge.GetTargetLock(action_data.m_Target);
		if (!codeLock)
		{
			super.OnFinishProgressServer(action_data);
			return;
		}

		RaGLB_DamageLock(action_data, codeLock);
	}

	protected void RaGLB_DamageLock(ActionData action_data, DigitalCodeLock codeLock)
	{
		LBCodelockRaidTool tool = LBCodelockConfig.Get.GetToolConfig(action_data.m_MainItem.GetType());
		if (!tool)
			return;

		float rounds = Math.Max(1, tool.actionRounds);
		float codelockDmg = 1.0 / rounds * codeLock.GetMaxHealth("", "");
		codeLock.AddHealth("", "", -codelockDmg);

		float toolDmg = tool.toolDamage / rounds * action_data.m_MainItem.GetMaxHealth("", "");
		action_data.m_MainItem.AddHealth("", "", -toolDmg);

		CodeLockComponent component = codeLock.GetCodeLockComponent();
		if (!component)
			return;

		if (!codeLock.IsAlive())
		{
			LBLogger.Admin("Player " + LBLogger.FormatPlayerIdentity(action_data.m_Player) + " Raided " + component.GetLoggingString() + " from " + action_data.m_Player.GetPosition() + " with " + action_data.m_MainItem, "Codelock");
			codeLock.UnlockOnServer(action_data.m_Player);
			component.SetLockState(false, false);
			codeLock.Delete();
			return;
		}

		LBLogger.Admin("Player " + LBLogger.FormatPlayerIdentity(action_data.m_Player) + " Is Raiding " + component.GetLoggingString() + " Remaining Health: " + (codeLock.GetHealth01() * 100) + " Percent", "Codelock");
	}
}
