// he.c 玉女剑-双剑交错

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int skill;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("双剑交错只能对战斗中的对手使用。\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对。\n");
	
	if (!mapp(me->query("family")) ||
	    me->query("family/family_name") != "古墓派")
		return notify_fail("你并没有领悟古墓派玉女剑法的精义！\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的内功不够娴熟，不能使用双剑交错。\n");

        if ((int)me->query_skill("yunv-jian", 1) < 80)
                return notify_fail("你的玉女剑法不够娴熟，不能使用双剑交错。\n");

        if ((int)me->query_skill("quanzhen-jian", 1) < 50)
                return notify_fail("你的全真剑法不够娴熟，不能使用双剑交错。\n");

        if ((int)me->query("neili", 1) < 400)
                return notify_fail("你现在内力太弱，不能使用双剑交错。\n");

        if (me->query_skill_mapped("sword") != "yunv-jian")
                return notify_fail("你没有激发玉女剑法，不能使用双剑交错。\n");

        if( (int)me->query_temp("hebi") ) 
                return notify_fail("你正与别人进行合壁，不能再进行玉女、全真剑法双剑交错。\n");

        if( (int)me->query_temp("yunv_hebi") ) 
                return notify_fail("你已经在运用玉女、全真剑法双剑交错了。\n");

        message_vision( HIY "$N" HIY "招式陡然一变，玉女剑法中夹杂着全真剑法，刁钻古怪却又浑然天成！\n" NOR, me);

        skill = ( me->query_skill("sword",1) + me->query_skill("yunv-jian",1)
                + me->query_skill("quanzhen-jian",1) +me->query_skill("force") ) / 12; 

        me->add_temp("apply/attack", skill/2);
        me->add_temp("apply/damage", skill/2);
        me->add_temp("apply/dodge",  skill/2);
        me->add_temp("apply/parry",  skill/2);
        me->set_temp("yunv_hebi", 1);

    me->add_temp("apply/damage", skill/2);

    me->map_skill("sword", "yunv-jian");
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
    me->map_skill("sword", "quanzhen-jian");
        me->setup();
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
    me->map_skill("sword", "yunv-jian");
        me->setup();
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
    me->map_skill("sword", "quanzhen-jian");
        me->setup();
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
    me->map_skill("sword", "yunv-jian");
        me->setup();
    me->add_temp("apply/damage", -skill/2);

        me->add("neili", -300);
        me->start_busy(1+random(2));

	call_out("remove_effect", (skill/4 > 40) ? 40 : skill/4, me, skill/2);
        return 1;
}

private int remove_effect(object me, int amount)
{
        if (!me) return 1;
	me->add_temp("apply/attack", -amount);
	me->add_temp("apply/damage", -amount);
	me->add_temp("apply/parry", -amount);
	me->add_temp("apply/dodge", -amount);
	me->setup();
	me->delete_temp("yunv_hebi");
	return 0;
}
