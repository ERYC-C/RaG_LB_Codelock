modded class RaG_ContainerBase
{
	override bool CanReceiveItemIntoCargo(EntityAI item)
	{
		if (RaGLBBridge.IsLocked(this))
			return false;

		return super.CanReceiveItemIntoCargo(item);
	}

	override bool CanReleaseCargo(EntityAI cargo)
	{
		if (RaGLBBridge.IsLocked(this))
			return false;

		return super.CanReleaseCargo(cargo);
	}

	override bool CanDisplayCargo()
	{
		if (RaGLBBridge.IsLocked(this))
			return false;

		return super.CanDisplayCargo();
	}

	override bool CanReleaseAttachment(EntityAI attachment)
	{
		if (RaGLBBridge.IsLocked(this))
			return false;

		return super.CanReleaseAttachment(attachment);
	}

	override bool CanReceiveAttachment(EntityAI attachment, int slotId)
	{
		if (RaGLBBridge.IsLocked(this))
			return false;

		if (InventorySlots.GetSlotName(slotId) == "Att_CodeLock_RaG")
		{
			DigitalCodeLock codeLock = DigitalCodeLock.Cast(attachment);
			if (!codeLock || !codeLock.IsRegularCodelock())
				return false;
		}

		return super.CanReceiveAttachment(attachment, slotId);
	}
}
