modded class RaG_PlaceableBase
{
	override bool CanPutInCargo(EntityAI parent)
	{
		if (RaGLBBridge.IsLocked(this))
			return false;

		return super.CanPutInCargo(parent);
	}

	override bool CanPutIntoHands(EntityAI parent)
	{
		if (RaGLBBridge.IsLocked(this))
			return false;

		return super.CanPutIntoHands(parent);
	}
}
