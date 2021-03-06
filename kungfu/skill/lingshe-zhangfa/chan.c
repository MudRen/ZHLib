// chan.c 灵蛇缠身

#include <ansi.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
 
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「灵蛇缠身」只能对战斗中的对手使用。\n");
 
        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "staff")
                return notify_fail("运用「灵蛇缠身」手中必须持杖！\n");

        if ((int)me->query_skill("force") < 80)
                return notify_fail("你的内功火候不够！\n");

        if ((int)me->query_skill("staff") < 80)
                return notify_fail("你的杖法还不到家，无法使用「灵蛇缠身」！\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧！\n");

        msg = HIG "$N手中的" + weapon->name() +"突然变得像一尾巨蛇，猛的甩出蛇尾迅速的缠向$n！\n" NOR;

        ap = me->query_skill("staff");
        dp = target->query_skill("dodge");
        if (ap / 2 + random(ap) > dp || !living(target))
        {
                msg += HIB "$n被缠的透不过气，无力反击！\n" NOR;
                target->start_busy(ap / 19 + 2);
             me->start_busy(1);
        } else 
        {
                msg += HIY "幸好$p看出了$N的破绽，巧妙的跳出了$P的攻击范围！\n" NOR;

                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}

