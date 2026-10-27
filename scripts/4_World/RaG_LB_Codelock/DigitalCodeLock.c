modded class DigitalCodeLock
{
	override bool CanBeLocked()
	{
		ItemBase parent = ItemBase.Cast(GetHierarchyParent());
		if (RaGLBBridge.ControlsLockParent(this, parent))
			return true;

		return super.CanBeLocked();
	}

	override void OnWasAttached(EntityAI parent, int slot_id)
	{
		super.OnWasAttached(parent, slot_id);
		RaGLB_PrepareOnParent(ItemBase.Cast(parent), slot_id);
	}

	override void AfterStoreLoad()
	{
		super.AfterStoreLoad();
		RaGLB_PrepareOnParent(ItemBase.Cast(GetHierarchyParent()), -1);
	}

	protected void RaGLB_PrepareOnParent(ItemBase storage, int slot_id)
	{
		if (!g_Game.IsServer() && g_Game.IsMultiplayer())
			return;
		if (slot_id != -1 && InventorySlots.GetSlotName(slot_id) != "Att_CodeLock_RaG")
			return;
		bool controlsStorage = RaGLBBridge.ControlsParent(this, storage);
		if (!controlsStorage && !RaGLBBridge.ControlsBuilding(this, storage))
			return;

		CodeLockComponent component = GetCodeLockComponent();
		if (component)
		{
			if (HasPIN())
				component.SetStage(CodeLockStage.NORMAL);
			else if (component.GetStage() == CodeLockStage.NONE)
				component.SetStage(CodeLockStage.SETTING);
		}

		UpdateVisuals();
		SetSynchDirty();
		if (controlsStorage)
			RaGLBBridge.ApplyInventoryLock(storage);
	}
}
