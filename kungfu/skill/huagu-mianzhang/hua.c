// hua.c 化骨绵掌

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	string msg;
        int damage;
        int ap, dp;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("辣手化骨只能对战斗中的对手使用。\n");

	if ((int)me->query_skill("force") < 150)
		return notify_fail("你的内功火候不够，无法施展化骨掌。\n");

	if ((int)me->query_skill("huagu-mianzhang", 1) < 100)
		return notify_fail("你的化骨绵掌还不够娴熟，不会化骨掌。\n");

	if ((int)me->query("neili", 1) < 300)
		return notify_fail("你的真气不够，不能化骨。\n");

        if (me->query_skill_mapped("strike") != "huagu-mianzhang")
                return notify_fail("你没有激发化骨绵掌，无法施展化骨掌。\n");

        me->add("neili", -100);

	msg = MAG "$N" MAG "掌出如风轻轻拍响$n" MAG "的肩头。\n"NOR;

        ap = me->query_skill("huagu-mianzhang", 1) + me->query_skill("strike", 1) + me->query_skill("force", 1);
        if (living(target))
                 dp = target->query_skill("force",1) + target->query_skill("parry",1) + target->query_skill("dodge",1);
        else     dp = 0;
	if (ap / 2 + random(ap) > dp)
        {
	        me->start_busy(2);
                damage = ap / 3 + random(ap / 2);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 40,
                                           HIR "结果只听扑的一声，$p" HIR "被$P"
                                           HIR "一掌拍中！一时间$p" HIR
                                           "只觉得全身暖洋洋的，感到有点轻飘无力轻。\n" NOR);
                target->affect_by("sl_poison",
                               ([ "level" : me->query("jiali") + random(me->query("jiali")),
                                  "id"    : me->query("id"),
                                  "duration" : ap / 60 + random(ap / 60) ]));
	} else
        {
		msg += CYN "可是$p" CYN "急忙闪在一旁，躲了开去。\n" NOR;
		me->start_busy(3);
	}

	message_combatd(msg, me, target);
	return 1;
}
