#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;
        int lvl;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("玄冥无极只能对战斗中的对手使用。\n");

        if (objectp(me->query_temp("weapon")))
                return notify_fail("你必须空手才能使用玄冥无极。\n");         

        if ((int)me->query_skill("xuanming-shengong", 1) < 150)
                return notify_fail("你的玄冥神功火候不够，使不出玄冥无极。\n");

        if ((int)me->query_skill("xuanming-zhang", 1) < 150)
                return notify_fail("你的玄冥神掌不够熟练，不会使用玄冥无极。\n");

        if ((int)me->query("max_neili") < 2000)
                return notify_fail("你的内力修为不足，无法使用玄冥无极。\n");

        if ((int)me->query("neili") < 500)
                return notify_fail("你的真气不够，无法使用玄冥无极。\n");

        msg = MAG "$N运起玄冥神功，全身浮现出一层紫气，猛然间双掌翻腾，施展出绝招玄冥\n无极，携带着万古至毒至寒之气的掌劲已攻向$n！\n"NOR;  

        lvl = me->query_skill("xuanming-zhang", 1);
        ap = me->query_skill("strike") + me->query("str") * 10;
        dp = target->query_skill("dodge") + target->query("dex") * 10;
        me->start_busy(4);
        if (ap / 2 + random(ap) > dp || !living(target))
        { 
                damage = ap + random(ap / 2);
                me->add("neili", -400);
                target->affect_by("xuanming_poison",
                               ([ "level" : me->query("jiali") + random(me->query("jiali")),
                                  "id"    : me->query("id"),
                                  "duration" : lvl / 50 + random(lvl / 20) ]));
                                  msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70,
               MAG "$n只见眼前紫影晃动，突然间胸口一震，已知大势不妙，只感胸口处一股\n寒气升起，尽损三焦六脉。\n" NOR);
        } else
        {
                msg += HIY "$n看见$N来势汹涌，急忙提气跃开。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
