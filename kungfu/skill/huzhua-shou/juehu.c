#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (userp(me) && ! me->query("can_perform/huzhua-shou/juehu"))
                return notify_fail("你现在还不会使用「绝户」这一招！\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail("「绝户」只能对战斗中的对手使用。\n");

        if (objectp(me->query_temp("weapon")))
             return notify_fail("你必须空手才能使用「绝户」！\n");

        if (me->query("shen") < 10000)
                return notify_fail("你恶念顿生，刚想对对手施展绝户，可突然想到了当初俞莲舟的一翻告戒，不得不中途放弃了攻击。\n");

        if ((int)me->query_skill("huzhua-shou", 1) < 130)
                return notify_fail("你的虎爪绝户手不够娴熟，不会使用「绝户」。\n");

        if (me->query("neili") < 300)
                return notify_fail("你现在真气不够，不能使用「绝户」。\n");

        msg = HIR "$N" HIR "大喝一声，变掌为爪，双爪化出漫天爪影，如狂风骤雨一般向$n" HIR
              "的要害抓去！\n"NOR;

        if (living(target))
                dp = target->query_skill("parry") / 2;
        else    dp = 0;

        if (random(me->query_skill("claw")) > dp)
        {
                me->start_busy(3);

                damage = me->query_skill("huzhua-shou", 1);
                damage = damage * 3 + random(damage);
                me->add("shen", -8000);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 25,
                                           HIR "结果$p" HIR "一声惨嚎，没能招架住$P" HIR
                                           "凌厉的攻势，被抓得皮肉分离，鲜血飞溅！\n" NOR);
                me->add("neili", -200);
        } else
        {
                me->start_busy(2);
                me->add("neili", -120);
                me->add("shen", -8000);
                msg += CYN "可是$p" CYN "看破了$N" CYN
                       "的企图，躲开了这招杀着。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}

