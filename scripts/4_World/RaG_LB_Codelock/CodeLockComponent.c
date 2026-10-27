modded class CodeLockComponent
{
	protected ItemBase RaGLB_GetStorage()
	{
		if (!m_Parent)
			return null;

		ItemBase storage = ItemBase.Cast(m_Parent.GetHierarchyParent());
		if (!RaGLBBridge.ControlsParent(m_Parent, storage))
			return null;

		return storage;
	}

	override void CloseParentDoor()
	{
		ItemBase storage = RaGLB_GetStorage();
		if (storage)
		{
			if (storage.IsOpen())
				storage.Close();
			return;
		}

		super.CloseParentDoor();
	}

	override void OpenParentDoor()
	{
		ItemBase storage = RaGLB_GetStorage();
		if (storage)
		{
			if (!storage.IsOpen())
				storage.Open();
			return;
		}

		super.OpenParentDoor();
	}

	override void SetLockState(bool state, bool sync = true)
	{
		super.SetLockState(state, sync);
		RaGLBBridge.ApplyInventoryLock(RaGLB_GetStorage());
	}
}
