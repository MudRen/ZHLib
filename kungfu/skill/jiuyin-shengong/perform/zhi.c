// zhi.c 九阴神指

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        object weapon;
        int n;
        int skill, ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        skill = me->query_skill("jiuyin-shengong", 1);

        if (! me->is_fighting(target))
                return notify_fail("九阴神指只能对战斗中的对手使用。\n");

        if (skill < 100)
                return notify_fail("你的九阴神功等级不够，无法施展九阴神指！\n");

        if (me->query("neili") < 100)
                return notify_fail("你现在真气不够！\n");

        ap = skill * 7 / 4 + me->query_skill("martial-cognize", 1);
        dp = target->query_skill("parry") + target->query_skill("martial-cognize", 1);

        msg = HIY "$N" HIY "出手成指，随意点戳，似乎看尽了$n"
              HIY + "招式中的破绽。\n" NOR;
        if (ap / 2 + random(ap * 2) > dp)
        {
                n = 4 + random(4);
                if (ap / 2 + random(ap) > dp)
                {
                        msg += HIY "$n" HIY "见来指玄幻无比，全然无法抵挡，慌乱之下破绽迭出，$N"
                               HIY "随手连出" + chinese_number(n) + "指！\n" NOR;
                        message_combatd(msg, me, target);
                        while (n-- && me->is_fighting(target))
                        {
				if (! target->is_busy())
                                	target->start_busy(1);
                                COMBAT_D->do_attack(me, target, 0, 0);
                        }

                        weapon = target->query_temp("weapon");
                        if (weapon && random(ap) / 2 > dp && weapon->query("type") != "pin")
                        {
                                msg = HIW "\n$n" HIW "觉得眼前眼花缭乱，手中的" + weapon->name() +
                                      HIW "一时竟然拿捏不住，脱手而出！\n" NOR;
                                weapon->move(environment(me));
                        } else
                        {
                                msg = HIY "\n$n勉力抵挡，一时间再也无力反击。\n" NOR;
                                me->start_busy(1);
                                return 1;
                        }
                } else
                {
                        msg += HIY "$n" HIY "不及多想，连忙抵挡，全然无法反击。\n" NOR;
			if (! target->is_busy())
                        	target->start_busy(4 + random(skill / 20));
                }
                me->start_busy(1);
        } else
        {
                msg += HIC "不过$n" HIC "紧守门户，不露半点破绽。\n" NOR;
                me->start_busy(3 + random(2));
		if (! target->is_busy())
                	target->start_busy(1);
        }

        message_combatd(msg, me, target);
        return 1;
}
