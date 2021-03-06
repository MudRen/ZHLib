// jiubu.c 九部式

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	int damage;
	string msg;
        int ap, dp, ap1, dp1;

        if (! target)
        {
	        me->clean_up_enemy();
	        target = me->select_opponent();
        }
	if (! target || ! me->is_fighting(target))
		return notify_fail("「九部式」只能对战斗中的对手使用。\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon")) 
                return notify_fail("「九部式」只能空手使用。\n"); 

	if ((int)me->query_skill("zhemei-shou", 1) < 120)
		return notify_fail("你的折梅手法不够娴熟，不会使用「九部式」。\n");
	                        
	if ((int)me->query_skill("xiaowuxiang", 1)<150
		&& (int)me->query_skill("lingjiu-xinfa", 1)<150
		&& (int)me->query_skill("xiaoyao-xinfa", 1)<150
		&& (int)me->query_skill("bahuang-gong", 1)<150
		&& (int)me->query_skill("beiming-shengong", 1)<150)
        return notify_fail("你的所用内功心法不正确，或者功力不够，不能使用绝招！\n");

	if ( me->query_skill_mapped("force") != "xiaowuxiang"
		&& me->query_skill_mapped("force") != "bahuang-gong"
		&& me->query_skill_mapped("force") != "lingjiu-xinfa"
		&& me->query_skill_mapped("force") != "xiaoyao-xinfa"
		&& me->query_skill_mapped("force") != "beiming-shengong")
                return notify_fail("你没有运用逍遥派系列内功！\n");	
			
	if ((int)me->query("neili") < 100)
		return notify_fail("你现在真气不够，不能使用「九部式」。\n");

        if (me->query_skill_mapped("hand") != "zhemei-shou")
                return notify_fail("你没有激发天山折梅手，不能使用「九部式」。\n");

	msg = HIC "$N" HIC "双手虚虚实实的抓向$n"
              HIC "的要害，身法缥缈，手式奇特，令人难以捉摸。\n" NOR;

        ap = me->query_skill("hand") + me->query_str()*10;
	ap += me->query("jiali")*2/3;
        dp = target->query_skill("dodge") + target->query_dex()*10;

        if (ap / 2 + random(ap) > dp || !living(target))
	{
                damage = me->query_skill("hand") + me->query_skill("force");
                damage += random(damage/2);
		me->add("neili", -damage/10);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60,
		                           HIR "$p" HIR "一个闪避不及，结果被$P"
                                           HIR "抓了个正中，浑身内息不由得一滞，气血翻涌。\n" NOR);
		if (me->query_skill_mapped("force") == "bahuang-gong")
		{
			ap1 = me->query_skill("force");
			ap1 += me->query("jiali");
			ap1 += random(ap1/2);
			dp1 = target->query_skill("force");
			dp1 += target->query("jiali");
			dp1 += random(dp1/2);
			if (ap1 > dp1)
			{
                                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, ap1, 60,
		                           HIM "$p" HIM "尚未来得及调气养息，结果发现$P"
                                           HIM "折梅手中混合入强劲的八荒六合唯我独尊功劲气！\n未及提防之下，强大的气息冲入身体，不由张口狂碰一口鲜血！\n" NOR);
			}
		}
		if (me->query_skill_mapped("force") == "beiming-shengong")
		{
			ap1 = me->query_skill("force");
			ap1 += me->query("jiali");
			ap1 += random(ap1/2);
			dp1 = target->query_skill("force");
			dp1 += target->query("jiali");
			dp1 += random(dp1/2);
			if (ap1 > dp1)
			{
                                target->add("neili",-ap1*2);
				if (target->query("neili") < 0)
					target->set("neili",0);
		                msg += HIM + target->name() + HIM + "尚未来得及调气养息，结果发现" + me->name() +
                                       HIM + "折梅手中混合使用了北冥神功！\n未及提防之下，浑身内力飞泄而出，不由面如土色！\n" NOR;
			}
		}
		target->start_busy(1+random(2));
		me->start_busy(2);
	} else 
	{
		msg += HIC "可是$p" HIC "身手敏捷，巧妙的躲过了$P"
                       HIC "的攻击！\n"NOR;
		me->add("neili", -50);
		me->start_busy(3);
	}
	message_combatd(msg, me, target);

	return 1;
}
