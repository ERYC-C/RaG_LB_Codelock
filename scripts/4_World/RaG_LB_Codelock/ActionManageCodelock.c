modded class ActionManageCodelock
{
	override CodeLockComponent GetTargetComponent(ActionTarget target)
	{
		CodeLockComponent component = super.GetTargetComponent(target);
		if (component)
			return component;

		DigitalCodeLock codeLock = RaGLBBridge.GetTargetLock(target);
		if (!codeLock)
			return null;

		return codeLock.GetCodeLockComponent();
	}
}
