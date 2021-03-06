// pi.c 群邪辟易

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        object weapon;
        int i;
        int skill;
        int count;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail("「群邪辟易」只能对战斗中的对手使用。\n");

        if (me->query("gender") != "无性" && !me->query("tianmo_jieti"))
                return notify_fail("你的性别与日月内功相斥，无法使用此绝招！\n");  

        skill = me->query_skill("pixie-jian", 1);

        if (skill < 120)
                return notify_fail("你的辟邪剑法修为有限，现在不能使用「群邪辟易」！\n");

        if (me->query("neili") < 100)
                return notify_fail("你的真气不够，无法运用「群邪辟易」！\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("你只有装备剑才能施展「群邪辟易」！\n");

        if( me->query_skill_mapped("sword") != "pixie-jian") 
                return notify_fail("你并没有使用辟邪剑法，无法使用此绝招！\n"); 

        if (weapon)
        {
                msg = HIR "$N" HIR "身形忽然变快，蓦的冲向$n"
                      HIR "，手中的" + weapon->name() + HIR "指指点点，如同"
                      HIR "寒夜晨星一般，点点光芒刺向$p" HIR "。\n" NOR;
        } else
        {
                msg = HIR "$N" HIR "忽然冲向$n" HIR "，身法快得"
                      HIR "不可思议，几近鬼魅，伸手就是数掌拍向$n" HIR "！\n" NOR;
        }

        message_combatd(msg, me, target);
        count = skill + (int)me->query_skill("riyue-guanghua", 1);
        count /= 2;

        if( me->query_skill_mapped("force") != "riyue-guanghua")
        count /= 2;

        me->add_temp("apply/attack", count);

        for (i = 0; i < 7; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(3) == 0 && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->start_busy(2 + random(3));
        me->add_temp("apply/attack", -count);

        return 1;
}

