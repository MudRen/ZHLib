// fugu.c 如蛆附骨

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	string msg;
        int ap, dp;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("「如蛆附骨」只能对战斗中的对手使用。\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "staff")
		return notify_fail("你使用的武器不对。\n");

	if (target->is_busy())
		return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧！\n");

        if (!living(target))
                return notify_fail("对方已经不能战斗了！\n");

	if ((int)me->query_skill("tianshan-zhang", 1) < 80)
		return notify_fail("你的天山杖法不够娴熟，不会使用「如蛆附骨」。\n");

	msg = HIG "$N" HIG "桀桀奸笑，手中的" + weapon->name() +
              HIG "就像影子一般袭向$n。\n" NOR;

        ap = me->query_skill("staff");
        dp = target->query_skill("dodge");
	if (ap / 2 + random(ap) > dp)
        {
		msg += HIR "结果$p" HIR "被$P" HIR "惊慌失措，"
                       "弄得手忙脚乱，难以应对！\n" NOR;
		target->start_busy((int)me->query_skill("staff") / 25 + 2);
	} else
        {
		msg += "可是$p" HIR "看破了$P" HIR "的企图，"
                       "轻轻一退，闪去了$P" HIR "的追击。\n" NOR;
		me->start_busy(1);
	}
	message_combatd(msg, me, target);

	return 1;
}
