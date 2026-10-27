modded class ItemBase
{
	override void AutoLockRaGDigital()
	{
		super.AutoLockRaGDigital();
		DigitalCodeLock codeLock = GetRaGDigitalCodeLock();
		if (!RaGLBBridge.ControlsParent(codeLock, this) && !RaGLBBridge.ControlsBuilding(codeLock, this))
			return;

		RaGLBBridge.TryAutoLock(this);
	}

	override void AfterStoreLoad()
	{
		super.AfterStoreLoad();
		if (RaGLBBridge.ControlsParent(GetRaGDigitalCodeLock(), this))
			RaGLBBridge.ApplyInventoryLock(this);
	}
}
