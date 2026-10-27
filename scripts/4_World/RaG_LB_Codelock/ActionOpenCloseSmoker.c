modded class ActionOpenCloseSmokerDoors
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		rag_baseitems_smoker smoker = rag_baseitems_smoker.Cast(target.GetObject());
		if (smoker && RaGLBBridge.IsLocked(smoker) && !smoker.IsDoorsOpen())
			return false;

		return super.ActionCondition(player, target, item);
	}
}

modded class ActionOpenCloseSmokerDrawer
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		rag_baseitems_smoker smoker = rag_baseitems_smoker.Cast(target.GetObject());
		if (smoker && RaGLBBridge.IsLocked(smoker) && !smoker.IsDrawerOpen())
			return false;

		return super.ActionCondition(player, target, item);
	}
}

modded class ActionOpenCloseSmokerLeftDoor
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		rag_baseitems_smoker smoker = rag_baseitems_smoker.Cast(target.GetObject());
		if (smoker && RaGLBBridge.IsLocked(smoker) && !smoker.IsLeftDoorOpen())
			return false;

		return super.ActionCondition(player, target, item);
	}
}

modded class ActionOpenCloseSmokerRightDoor
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		rag_baseitems_smoker smoker = rag_baseitems_smoker.Cast(target.GetObject());
		if (smoker && RaGLBBridge.IsLocked(smoker) && !smoker.IsRightDoorOpen())
			return false;

		return super.ActionCondition(player, target, item);
	}
}
