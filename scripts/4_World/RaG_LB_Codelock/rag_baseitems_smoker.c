modded class rag_baseitems_smoker
{
	override void OpenDrawer()
	{
		if (RaGLBBridge.IsLocked(this))
			return;

		super.OpenDrawer();
	}

	override void OpenDoors()
	{
		if (RaGLBBridge.IsLocked(this))
			return;

		super.OpenDoors();
	}

	override void OpenRightDoor()
	{
		if (RaGLBBridge.IsLocked(this))
			return;

		super.OpenRightDoor();
	}

	override void OpenLeftDoor()
	{
		if (RaGLBBridge.IsLocked(this))
			return;

		super.OpenLeftDoor();
	}
}
