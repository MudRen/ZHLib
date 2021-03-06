// kurong-changong.c 枯荣禅功
#include <ansi.h>
inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
    return force == "duanshi-xinfa";
}

int query_neili_improve(object me)
{
    int lvl;

    lvl = (int)me->query_skill("kurong-changong", 1);
    return lvl * lvl * 18 * 15 / 100 / 200;
}

int valid_learn(object me)
{
    if ( me->query("gender") == "无性")
    	return notify_fail("你无根无性，阴阳不调，难以领会枯荣禅功。\n");

    return ::valid_learn(me);
}

int practice_skill(object me)
{
	return notify_fail("枯荣禅功只能用学(learn)的来增加熟练度。\n");
}

string exert_function_file(string func)
{
	return __DIR__"kurong-changong/" + func;
}

mapping curing_msg(object me)
{
        return ([
"apply_short"	:me->name()+"一半脸色红光满面，一半脸面状似枯骨，正在运功疗伤。",
"start_self"	:HIY"你盘腿端坐，催发枯荣禅功，开始运功疗伤。\n"NOR,
"start_other"	:WHT""+me->name()+NOR+WHT+"盘腿端坐，脸上枯荣交替，忽而红光满面，忽而状似枯骨。\n"NOR,
"on_self"	:WHT"你感觉体内两股真气交替，一股冰冷一股火热，枯荣禅功催运下伤势逐渐好转。\n"NOR,
"finish_self"	:HIY"你感觉两股真气渐渐交融，遍体舒畅，内伤尽去，长吸一口气站了起来。\n"NOR,
"finish_other"	:me->name()+"长吸一口气，站起身来，看上去红光满面，精神抖擞。\n",
"unfinish_self"	:"你正以枯荣心法运气疗伤，忽觉真气後继乏力，祗得站起身来，暂缓疗伤。\n",
"unfinish_other":me->name()+"站起身来，脸上状似枯骨，隐隐透出些许红光。\n",
"halt_self"	:"你吐气纳息，硬生生地将两股真气压了下去，站起脚步。\n",
"halt_other"	:me->name() +"摇晃着站起身来，满脸枯黄之色，吐出一口瘀血，脸色旋即恢复正常。\n",
"dazuo"		:"你盘腿坐下，丹田升起两道真气，一冷一热，行遍全身，周而复始。\n",
"tuna"		:"你盘腿坐下，屏弃所有杂念，丹田升起两道真气，缓缓流向脑部，冷热交替，经脉舒坦。\n",
        ]);
}
