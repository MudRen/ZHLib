// you.c 幽冥一击
 
#include <ansi.h>
#include <combat.h>
 
inherit F_SSERVER;
 
int perform(object me, object target)
{
	string msg;
        int ap, dp, bs;
        int damage;

        if (! target)
        {
        	me->clean_up_enemy();
        	target = me->select_opponent();
        }

	if (! target || ! me->is_fighting(target))
		return notify_fail("幽冥一击只能对战斗中的对手使用。\n");
 
	if (me->query_skill("kuihua-mogong", 1) < 120)
		return notify_fail("你的葵花魔功还不够娴熟，不能使用幽冥一击！\n");

        if (me->query("neili") < 200)
                return notify_fail("你的内力不够，不能使用幽冥一击！\n");
 
	msg = HIR "$N" HIR "忽的扑上前去，霎时便逼近$n" HIR
              "，忽的伸手猛然刺向$p的要害！\n" NOR;
 
        ap = me->query_skill("kuihua-mogong", 1) * 3 / 2 + me->query("dex") * 20 +
             me->query_skill("martial-cognize", 1);
	dp = target->query_skill("parry") + target->query("dex") * 20 +
             target->query_skill("martial-cognize", 1);

        me->start_busy(2);
        me->add("neili", -40);

        if (ap / 2 + random(ap) < dp)
        {
		msg += HIG "然而$n" HIG "抵挡得法，将$N" HIG
                       "的攻势一一化解。\n" NOR;
        } else
	{
                target->start_busy(1);
		me->add("neili",-60);
                damage = ap / 3 + random(ap / 3) - 80 - random(80);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70,
                                           HIR "$n" HIR "急忙后退，阵脚已乱，结果连中$N"
                                           HIR "数招，鲜血溅了一地！\n" NOR);
	}

	message_combatd(msg, me, target);
	return 1;
}
