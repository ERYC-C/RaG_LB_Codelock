# RaG_LB_Codelock

**RaG 系列 Mod 与 LBmaster CodeLock 密码锁兼容性扩展**

本 Mod 为 **RaG 系列建筑及物品 Mod** 提供 **LBmaster CodeLock** 密码锁兼容支持，使玩家能够在 RaG 相关建筑及物品上使用 LB 密码锁系统。

此外，本 Mod 已集成针对 `RaG_CORE` 的客户端脚本错误修复，避免特定情况下因空指针访问而持续产生错误日志。

此Mod部分内容使用AI生成，介意请勿使用。

## 兼容性

| 项目         | 说明                                                       |
| ------------ | ---------------------------------------------------------- |
| 密码锁系统   | [LBmaster CodeLock](https://lbmaster.de/product.php?id=47) |
| 已适配版本   | `2.0.3 - stable`                                           |
| 兼容 Mod     | `RaG_BaseItems`、`RaG_BaseBuilding`                        |
| 相关依赖     | `RaG_CORE`                                                 |
| 已知问题来源 | `RaG_CORE`                                                 |
| bug修复状态  | **已集成修复，无需额外操作**                               |

> **兼容性说明**
>
> - 本 Mod 已针对 **LBmaster CodeLock** `**2.0.3 - stable**` 进行适配。
> - 支持 `RaG_BaseItems` 和 `RaG_BaseBuilding`。
> - 单独使用 `RaG_BaseItems` 不会出现编译错误。
> - `RaG_CORE` 目前存在导致客户端持续产生脚本错误的问题。
> - **本 Mod 已包含针对该问题的修复代码，无需额外安装补丁。**
> - 当 RaG 官方修复该问题后，本 Mod 将移除相应的临时修复代码。

## 已修复的问题

### RaG_CORE — ActionDismantlePart 空指针异常

**问题来源：** `RaG_CORE`

**影响范围：** 客户端

**错误类型：** `NULL pointer to instance`

**修复状态：** ✅ 已修复

### 问题描述

在使用 `RaG_CORE` 时，客户端可能在执行建筑拆除动作的条件检查过程中触发空指针异常。

该问题发生在 `ActionDismantlePart.DismantleCondition()` 的执行过程中。

由于客户端会持续检查玩家当前可执行的交互动作，因此在满足特定条件时，错误可能每帧重复出现，导致客户端脚本日志持续增长。

本 Mod 已集成针对该问题的防护逻辑，在执行原有拆除条件检查之前验证建筑对象的有效性，避免因缺少必要的建筑组件而继续执行相关逻辑。

**RaG 官方问题反馈：**

[Discord — RaG_CORE 问题反馈](https://discord.com/channels/1035016643346186250/1563535280324223008)

### 错误日志

```
Reason: NULL pointer to instance

Class:    ActionDismantlePart
Function: DismantleCondition

Stack trace:

scripts/4_World/classes/useractionscomponent/actions/continuous/actiondismantlepart.c:168
Function DismantleCondition

DayZExpansion/Core/Scripts/4_World/dayzexpansion_core/classes/useractionscomponent/actions/continuous/actiondismantlepart.c:20
Function DismantleCondition

scripts/4_World/classes/useractionscomponent/actions/continuous/actiondismantlepart.c:88
Function ActionCondition

scripts/4_World/classes/useractionscomponent/actionbase.c:954
Function Can

JM/COT/Scripts/4_World/communityonlinetools/classes/useractionscomponent/actionbase.c:6
Function Can

scripts/4_World/classes/useractionscomponent/actioninput.c:343
Function _GetSelectedActions

scripts/4_World/classes/useractionscomponent/actioninput.c:379
Function UpdatePossibleActions

scripts/4_World/classes/useractionscomponent/actionmanagerclient.c:577
Function FindContextualUserActions

scripts/4_World/classes/useractionscomponent/actionmanagerclient.c:140
Function Update

scripts/4_World/entities/manbase/playerbase.c:3341
Function CommandHandler

JM/COT/Scripts/4_World/communityonlinetools/entities/player/playerbase.c:235
Function CommandHandler
```

## 修复实现

### 修复原理

通过扩展 `ActionDismantlePart` 类，在执行原有的 `DismantleCondition()` 方法之前，增加建筑对象有效性检查。

当目标实体支持建筑系统，但无法获取有效的 `ConstructionBasic` 对象时，直接返回 `false`，防止继续执行可能触发空指针异常的逻辑。

对于其他正常情况，仍然调用原有方法，尽可能保持原版及其他 Mod 的拆除行为。

### 修复代码

以下代码已包含在本 Mod 中，服务器管理员无需手动添加。

```
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
```

### 修复逻辑

1. 检查当前交互目标 `ActionTarget` 是否存在。
2. 将目标对象转换为 `EntityAI`。
3. 判断目标实体是否支持建筑系统。
4. 如果目标支持建筑系统，但 `GetConstructionBasic()` 返回空对象，则终止当前拆除条件检查。
5. 对于其他情况，继续执行原有的 `DismantleCondition()` 方法。

该修复主要用于避免异常对象进入后续拆除条件检查流程。

> **临时修复说明**
>
> 此修复属于针对 `RaG_CORE` 的临时兼容性补丁。
>
> 修复代码不会主动修改正常建筑对象的拆除条件，但对于缺少有效建筑组件的异常目标，会阻止拆除动作继续执行。
>
> **当 RaG 官方修复该问题后，本 Mod 将移除对应的补丁代码，以减少不必要的脚本覆盖并保持与官方更新的兼容性。**

## 联系与反馈

如果在使用过程中遇到密码锁兼容性问题、脚本错误或其他异常，欢迎联系反馈。

| 联系方式 | 信息         |
| -------- | ------------ |
| QQ       | `981805944`  |
| Discord  | `marsha1_00` |

提交问题时，建议提供以下信息：

- 使用的 LBmaster CodeLock 版本。
- 使用的 RaG 系列 Mod 及版本。
- 相关客户端或服务器脚本日志。
- 问题的复现步骤。

这些信息有助于更快地定位和解决兼容性问题。
