// chan.c 太极拳法「粘」字诀

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int level;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("太极拳法「粘」字诀只能对战斗中的对手使用。\n");

        if (objectp(me->query_temp("weapon")))
                return notify_fail("你必须空手才能使用「粘」字诀！\n"); 

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧！\n");
                
        if ((level = me->query_skill("taiji-quan", 1)) < 200)
                return notify_fail("你对太极拳理还不明白，不会使用「粘」字诀。\n");

        if (me->query("neili") < 60)
                return notify_fail("你现在真气不够，无法使用「粘」字诀。\n");

        msg = HIG "$N" HIG "使出太极拳法「粘」字诀，猱身而上，紧随$n"
              "进退，企图扰乱$n" HIG "的攻势。\n" NOR;

        me->add("neili", -30);
        if (random(level) > (int)target->query_skill("dodge", 1) / 2)
        {
                msg += HIR "结果$p" HIR "左冲右突，均无法摆脱$P" HIR "，不禁手忙脚乱，"
                       "惊慌失措，不知如何应对！\n" NOR;
                target->start_busy(level / 30);
        } else
        {
                msg += CYN "可是$p" CYN "看破了$P" CYN "的企图，"
                       "纵身而退，未受丝毫影响。\n" NOR;
                me->start_busy(1);
        }
        message_combatd(msg, me, target);

        return 1;
}

