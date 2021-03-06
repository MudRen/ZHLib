// Code of JHSH
///kungfu/skill/chongyang-shenzhang/lianhuan.c 连环三招

/*
尹志平左剑平刺，右掌正击，同时左腿横扫而出，正是全真派中的「三连环」绝招。赵志敬高纵丈馀，
挥剑下削。尹志平长剑脱手，猛往对方掷去，跟著「嘿」的一声，双掌齐出。

杨过见这几招凌厉变幻，已非己之所知，不禁手心人全是冷汗，眼见赵志敬身在半空，一个势虚，一
个势实，看来这两掌要打得他筋折骨断。岂知赵志敬竟在这情势危急异常之际忽然空中翻身，急退寻
丈，轻轻巧巧的落了下来。
*/


#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

int perform(object me, object target)
{
	int skill;
	string weapon;
	int damage;
	string *limb, type, result, str;

	if( !target ) target = offensive_target(me);

	if( !target
	||	!target->is_character()
	||	!me->is_fighting(target) )
		return notify_fail("连环三招只能对战斗中的对手使用。\n");


	if( objectp(me->query_temp("weapon")) )
		return notify_fail("连环三招需空手才能施展！\n");

	if( me->query_skill_mapped("strike") != "chongyang-shenzhang" )
		return notify_fail("你所用的并非重阳神掌，不能施展连环三招！\n");

	if( me->query_skill_prepared("strike") != "chongyang-shenzhang" )
		return notify_fail("你所备的并非重阳神掌，不能施展连环三招！\n");

	if( me->query_skill_mapped("force") != "xiantian-gong" )
		return notify_fail("你所用的并非玄门先天功，施展不出连环三招！\n");

	if( me->query_skill("force") < 120 )
		return notify_fail("你的玄门先天功火候未到，无法施展连环三招！\n");

	if( me->query_skill("strike") < 120 )
		return notify_fail("连环三招需要精湛的重阳神掌方能有效施展！\n");

	if( me->query("neili") <= 200 )
		return notify_fail("你的内力不够使用连环三招！\n");

	message_vision(HIY "$N怒喝一声，拚尽全力，突然闪电般攻出指、掌、腿连环三招！\n\n" NOR, me, target);

	skill = me->query_skill("strike")/2 + me->query_skill("strike") / 8;
	if(skill>300)skill=300;
	me->add_temp("apply/attack",skill);
/*
        if(me->query_temp("apply/attack")> 400){
		me->set_temp("apply/attack",400);
	}
*/

	if( me->query_skill_prepared("strike") == "chongyang-shenzhang" ) {
		me->set_temp("restore", 1);
		me->prepare_skill("strike");
	}

	COMBAT_D->do_attack(me, target, me->query_temp("weapon"));

	if( me->query_temp("restore") ) me->prepare_skill("strike", "chongyang-shenzhang");

	if( me->query_skill_prepared("finger") == "zhongnan-zhi" ) {
		me->set_temp("restore", 1);
		me->prepare_skill("finger");
	}

	COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
	if( me->query_temp("restore") ) me->prepare_skill("finger", "zhongnan-zhi");
	me->add_temp("apply/attack",-skill);

	message_vision( HIY "\n紧跟着$N突然腾空飞起，使出一招鸳鸯连环腿，两腿风驰电掣连环踢向$n\n" NOR,me,target);
	if( random(me->query("combat_exp")) > (int)target->query("combat_exp")/3)
	{
		if( ( target->query_skill("dodge")+target->query_skill("parry") ) < random((me->query_skill("strike") + me->query_skill("force"))*2/3) )
		{
			message_vision(HIR"只听$N一声惨叫，这连环二腿正中心口。但见$n一个身躯突然平平飞出，腾的一响，尘土飞扬，跌在丈许之外，直挺挺的躺在地下，再也不动。\n\n"NOR, target,target );
                        damage = (int)target->query("eff_qi");
                        target->receive_wound("qi", (damage>0?damage:-damage), me);
                        damage = (int)target->query("qi");
                        target->receive_wound("qi", (damage>0?damage+1:1-damage), me);
			me->add("neili", -me->query("jiali"));
		}
		else
		{
			damage = random((int)me->query_skill("strike")+me->query("jiali")) ;
			if(damage > 1500) damage = 1500;
			if(damage < 300) damage = 300;
			me->add("neili", -me->query("jiali"));

			target->receive_damage("qi", damage,  me);
			target->receive_wound("qi", (int)me->query_skill("strike"), me);

			limb = target->query("limbs");
			type = "瘀伤";
			message_vision("只听$N一声惨叫，这连环二腿正中$P"+limb[random(sizeof(limb))]+"，结果把$P踢摔了个跟头。\n",target);

			str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
			message_vision("($N"+str+")\n", target);
		}
		me->start_busy(1+random(2));
	}
	else if( ( random( target->query_skill("dodge") ) >  me->query_skill("strike")*2/3) && random(5) == 1 )
	{
		message_vision(HIR"$N猛觉得劲风罩来，心知不妙，慌忙闪开，结果$n踢了个空，白白自己重重跌了一跤。\n\n"NOR, target,me );
		me->receive_wound("qi", 30+random(50),  me);
		me->start_busy(2+random(2));
		str = COMBAT_D->status_msg((int)me->query("qi") * 100 /(int)me->query("max_qi"));
		message_vision("($N"+str+")\n", me);
	}
	else
	{
		message_vision( "$N眼见这一腿来势凶猛，当下双足一点，跃高四尺，躲开了$n这一招，不过也出了一身冷汗。\n\n" NOR,  target,me);
		me->start_busy(2);
	}

	me->add("neili", -random(me->query_skill("strike")/4) -100 );
	me->start_busy( 2+random(2) );

	return 1;
}


