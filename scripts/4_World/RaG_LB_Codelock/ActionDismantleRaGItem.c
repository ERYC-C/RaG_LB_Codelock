modded class ActionDismantleRaGItem
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		ItemBase ragitem = ItemBase.Cast(target.GetObject());
		if (RaGLBBridge.HasSecuredLock(ragitem))
			return false;

		return super.ActionCondition(player, target, item);
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		if (!action_data || !action_data.m_Target)
			return;

		ItemBase ragitem = ItemBase.Cast(action_data.m_Target.GetObject());
		if (RaGLBBridge.HasSecuredLock(ragitem))
			return;

		super.OnFinishProgressServer(action_data);
	}
}
