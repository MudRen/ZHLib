// lianhuan.c 慕容剑法
#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
      {
        int count, skill, i, j, d;
        object weapon;

        i = me->query_skill("murong-sword",1)/5;
        j = me->query_skill("canhe-zhi",1)/5;
        d = me->query_skill("zihui-xinfa",1)/5;
        skill = me->query_skill("murong-sword",1);

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))

                return notify_fail("七剑连环指只能对战斗中的对手使用。\n");

        if( (int)me->query_skill("murong-sword", 1) < 120 )
                return notify_fail("你的剑法还未练成，不能使用七剑连环指！\n");

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "sword")
                return notify_fail("你手里没有剑，无法使用七剑连环指！\n");

        if((int)me->query_skill("canhe-zhi", 1) < 120 )
                return notify_fail("你的参合指法还未练成，不能使用七剑连环指！\n");

        if(me->query_skill_mapped("finger") != "canhe-zhi")
                return notify_fail("你没有用参合指，无法使用七剑连环指！\n");

        if(me->query_skill_prepared("finger") != "canhe-zhi")
                return notify_fail("你没有准备参合指，无法使用七剑连环指！\n");

        if((int)me->query("neili") < 500 )
                return notify_fail("你现在内力不足，不能使用七剑连环指！\n");

        if((int)me->query_temp("lianhuan"))
                return notify_fail("你正在使用七剑连环指！\n");

        if((int)me->query_skill("sword", 1) < 120 )
                return notify_fail("你的基本剑法不够娴熟，不能在剑招中使用七剑连环指。\n");

        if((int)me->query_skill("finger", 1) < 120 )
                return notify_fail("你的基本指法不够娴熟，不能在剑招中使用七剑连环指。\n");

        message_vision(MAG"\n$N使出七剑连环指，剑锋一转，右手食指跟着弹出，只见剑花指风相辉相映，直袭$n！\n"NOR, me,target);
        me->add("neili", -300);
        me->add("jing", -50);

        count = (i+j)/3*2;
        me->add_temp("apply/attack", count);
        me->add_temp("apply/damage", d);
        me->set_temp("lianhuan",1);
        me->start_call_out((: call_other,  __FILE__, "remove_effect", me, count, d :), skill / 2);
        return 1;
}



void remove_effect(object me, int amount, int amount1)
{
        if ((int)me->query_temp("lianhuan"))
        {
            me->add_temp("apply/attack", -amount);
            me->add_temp("apply/damage", -amount1);
            me->delete_temp("lianhuan");
                tell_object(me, HIY "你的「七剑连环指」绝技运行完毕，气回丹田,缓缓收功。\n" NOR);
        }
}
