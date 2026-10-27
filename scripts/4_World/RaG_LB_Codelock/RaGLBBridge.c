class RaGLBBridge
{
	static bool ControlsParent(EntityAI lockEntity, ItemBase storage)
	{
		DigitalCodeLock codeLock = DigitalCodeLock.Cast(lockEntity);
		if (!codeLock || !codeLock.IsRegularCodelock() || !storage)
			return false;
		if (storage.GetRaGDigitalCodeLock() != codeLock)
			return false;
		if (storage.IsInherited(RaG_ContainerBase))
			return true;

		return storage.IsKindOf("rag_baseitems_greenhouse_base");
	}

	// RaG_BB_Base 是 Fence。开关走 LB 的 OpenFence/CloseFence，不能走容器的 Open/Close，也不能锁整栋建筑的库存。
	static bool ControlsBuilding(EntityAI lockEntity, ItemBase building)
	{
		DigitalCodeLock codeLock = DigitalCodeLock.Cast(lockEntity);
		if (!codeLock || !codeLock.IsRegularCodelock() || !building)
			return false;
		if (!building.IsKindOf("RaG_BB_Base"))
			return false;

		return building.GetRaGDigitalCodeLock() == codeLock;
	}

	static bool ControlsLockParent(EntityAI lockEntity, ItemBase parent)
	{
		return ControlsParent(lockEntity, parent) || ControlsBuilding(lockEntity, parent);
	}

	static bool IsLocked(ItemBase storage)
	{
		if (!storage)
			return false;

		DigitalCodeLock codeLock = storage.GetRaGDigitalCodeLock();
		if (!codeLock || !codeLock.IsRegularCodelock())
			return false;

		return codeLock.IsLocked();
	}

	static bool HasSecuredLock(ItemBase storage)
	{
		if (!storage)
			return false;

		DigitalCodeLock codeLock = storage.GetRaGDigitalCodeLock();
		if (!codeLock || !codeLock.IsRegularCodelock())
			return false;

		return codeLock.HasPIN() || codeLock.IsLocked();
	}

	static DigitalCodeLock GetTargetLock(ActionTarget target)
	{
		if (!target)
			return null;

		ItemBase storage = ItemBase.Cast(target.GetObject());
		if (!storage || !storage.GetRaGDigitalCodeLock())
			storage = ItemBase.Cast(target.GetParent());
		if (!storage)
			return null;

		DigitalCodeLock codeLock = storage.GetRaGDigitalCodeLock();
		if (!ControlsLockParent(codeLock, storage))
			return null;

		return codeLock;
	}

	static void TryAutoLock(ItemBase storage)
	{
		if (!g_Game.IsServer() && g_Game.IsMultiplayer())
			return;
		if (!LBCodelockConfig.Get || !LBCodelockConfig.Get.autoLockOnClose)
			return;

		DigitalCodeLock codeLock = storage.GetRaGDigitalCodeLock();
		if (!codeLock || !codeLock.IsRegularCodelock() || !codeLock.HasPIN() || codeLock.IsLocked())
			return;
		if (!codeLock.CanBeLocked())
			return;

		codeLock.LBLockWithoutBuildingChange();
	}

	static void ApplyInventoryLock(ItemBase storage)
	{
		if (!storage)
			return;
		if (!g_Game.IsServer() && g_Game.IsMultiplayer())
			return;

		GameInventory inventory = storage.GetInventory();
		if (!inventory)
			return;

		if (IsLocked(storage))
			inventory.LockInventory(HIDE_INV_FROM_SCRIPT);
		else
			inventory.UnlockInventory(HIDE_INV_FROM_SCRIPT);
	}
}
