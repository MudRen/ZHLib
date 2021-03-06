// heal.c

#include <ansi.h>

mapping eff_heal = ([
	"kurong-changong"	: 5,	
	"taixuan-gong"		: 5,
	"taiji-shengong"	: 4,	
	"yijinjing"		: 4,	
	"jiuyang-shengong"	: 4,	
	"xiantian-gong"		: 4,	
	"linji-zhuang"		: 4,	
	"bahuang-gong"		: 3,
	"lengyue-shengong"	: 3,
	"shonghuo-xuanming"	: 3,
	"hunyuan-yiqi"		: 3,	
	"zixia-shengong"	: 3,
	"bibao-shengong"	: 3,
	"yunv-xinfa"		: 3,
	"xiaowuxiang"		: 3,
	"huntian-qigong"	: 3,	
	"longxiang"		: 3,
	"beiming-shengong"	: 3,	
	"zihui-xinfa"		: 3,	
	"hamagong"		: 2,	
	"huagong-dafa"		: 2,	
	"shenlong-xinfa"	: 2,
	"xixing-dafa"		: 2,	
]);

int curing(object);
int halt_curing(object);
void remove_pending(object);

int exert(object me, object target)
{
        string force;
	mapping msg;

	if (me->is_fighting())
		return notify_fail("战斗中运功疗伤？找死吗？\n");

	if (me->is_busy())
		return notify_fail("等你忙完了手头的事情再说！\n");

        force = me->query_skill_mapped("force");
        if (! stringp(force))
                return notify_fail("先激发你的特殊内功。\n");

        if ((int)me->query("eff_qi") >= (int)me->query("max_qi"))
                return notify_fail("你现在气血充盈，不需要疗伤。\n");

	if ((int)me->query_skill(force, 1) < 20)
		return notify_fail("你的" + to_chinese(force) + "修为还不够。\n");

	if ((int)me->query("neili") < 50)
		return notify_fail("你的真气不够。\n");

	if ((int)me->query("eff_qi") < (int)me->query("max_qi") / 5)
		return notify_fail("你已经受伤过重，只怕一运真气便有生命危险！\n");

	msg = SKILL_D(force)->curing_msg(me);

	if( !msg || undefinedp(msg["start_self"]) )
		tell_object(me, HIW"你全身放松，坐下来开始运功疗伤。\n"NOR);
	else	tell_object(me, msg["start_self"]);

	if( !msg || undefinedp(msg["start_other"]) )
		message("vision", me->name() +"盘膝坐下，开始运功疗伤。\n"NOR,
			environment(me), me);
	else	message("vision", msg["start_other"], environment(me), me);

	if( !msg || undefinedp(msg["apply_short"]) )
		me->set_temp("apply/short", ({ me->name() +"正坐在地下运功疗伤。"}));
	else	me->set_temp("apply/short", ({ msg["apply_short"] }));

	me->set_temp("pending/curing", 1);
	me->start_busy((: curing :), (: halt_curing :));

	return 1;
}

int curing(object me)
{
        int recover_points, lvl, con, eff;
	string force_skill;
	mapping msg;
        
	if( !living(me) || me->is_ghost() || !(force_skill = me->query_skill_mapped("force")) )
	{
		remove_pending(me);
		return 0;
	}

	msg = SKILL_D(force_skill)->curing_msg(me);

	if( me->query("jing") < 1)
	{
		remove_pending(me);
		me->unconcious();
		return 0;
	}
	else if( (int)me->query("eff_qi") >= (int)me->query("max_qi") )
	{
		if( !msg || undefinedp(msg["finish_self"]) )
			tell_object(me, HIY"你运功良久，自觉经脉顺畅，内伤尽去，神元气足地站了起来。\n"NOR);
		else	tell_object(me, msg["finish_self"]);

		if( !msg || undefinedp(msg["finish_other"]) )
			message("vision", me->name() +"运功完毕，站起身来，看上去气色饱满，精神抖擞。\n"NOR,	environment(me), me);
		else	message("vision", msg["finish_other"], environment(me), me);

		remove_pending(me);
        	return 0;
	}
	else if( (int)me->query("neili") < 50 )
	{
		if( !msg || undefinedp(msg["unfinish_self"]) )
			tell_object(me, "你正在运功疗伤，忽觉内息後继乏力，祗得暂缓疗伤，站起身来。\n"NOR);
		else	tell_object(me, msg["unfinish_self"]);

		if( !msg || undefinedp(msg["unfinish_other"]) )
			message("vision", me->name() +"运功完毕，缓缓站了起来，脸色看起来好了许多。\n"NOR,environment(me), me);
		else	message("vision", msg["unfinish_other"], environment(me), me);

		remove_pending(me);
		return 0;
	}

	lvl = me->query_skill("force");	// my enable force level.
	con = me->query("con");		// my original constitution.
	eff = eff_heal[force_skill];		// my force's effect on heal.
	if( !eff ) eff = 1;

	recover_points = con + lvl/5;
	recover_points += recover_points/5*eff;

        if (me->query("breakup"))
                recover_points *= 3;

	me->receive_curing("qi", recover_points);
	me->add("neili", -50);

	if( !msg || undefinedp(msg["on_self"]) )
		message_vision(WHT "$N" WHT "脸色通红，头上白气氤氲，显然体内真气正在不停运转。\n" NOR, me);
	else
	{
		tell_object(me, msg["on_self"]);
		message("vision", msg["start_other"], environment(me), me);
	}

	return 1; 
}

int halt_curing(object me)
{
	me->receive_damage("qi",50);

	if (me->query("qi") < 5)
		me->set("qi",5);

	if (me->query("neili") > 50)
		me->add("neili", -50);
	else
		me->set("neili",0);

	tell_object(me, "你吐气纳息，硬生生地将内息压了下去，缓缓站了起来。\n");
	message("vision", me->name() +"身子一震，吐出一口瘀血，缓缓站了起来。\n", environment(me), me);

       	remove_pending(me); 
	me->start_busy(1+random(3));
	return 1;
}

void remove_pending(object me)
{
	me->delete_temp("pending/curing");
	me->delete_temp("apply/short");
}
