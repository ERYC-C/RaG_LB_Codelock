// 临时文件。RaG_Core 修好后删除整个 TEMP_RaGCore_ActionDismantlePart_NullConstruction.c，不要把它留在模组里。
//
// RaG_Core 的两处改动会让原版 ActionDismantlePart.DismantleCondition 第 168 行空指针，客户端对准容器时每帧报错：
// 1. Modded/ItemBase.c 的 SetActions() 给所有物品加上 ActionDismantlePart。
// 2. RaG_ContainerBase.CanUseConstruction() 固定返回 true，但 GetConstructionBasic() 仍是 null。
// 原版看到 CanUseConstruction() 为真就调用 construction.GetConstructionPartToDismantle()。
//
// 这里在调用 super 之前拦住没有建造组件的目标。栅栏和 RaG_BaseBuilding 部件有建造组件，仍走原来的拆卸。
modded class ActionDismantlePart
{
	override protected bool DismantleCondition(PlayerBase player, ActionTarget target, ItemBase item, bool camera_check)
	{
		if (target)
		{
			EntityAI targetEntity = EntityAI.Cast(target.GetObject());
			if (targetEntity && targetEntity.CanUseConstruction() && !targetEntity.GetConstructionBasic())
				return false;
		}

		return super.DismantleCondition(player, target, item, camera_check);
	}
}
