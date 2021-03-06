//
// longxiang.c 龙象般若功
//

#include <ansi.h>
inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
	return force == "mizong-neigong" ||
	       force == "xiaowuxiang";
}

int query_neili_improve(object me)
{
    int lvl;

    lvl = (int)me->query_skill("longxiang", 1);
    return lvl * lvl * 15 * 15 / 100 / 200;
}

int valid_learn(object me)
{
	if ((int)me->query_skill("force", 1) < 70)
		return notify_fail("你的基本内功火候还不够。\n");

	if ( me->query("gender") == "无性" && (int)me->query("longxiang", 1) > 49)
		return notify_fail("你无根无性，阴阳不调，难以领会高深的龙象般若功。\n");

    	if (me->query("str") < 30)
        	return notify_fail("你先天膂力不足，无法学习刚猛的龙象般若功。\n");

	return ::valid_learn(me);
}

int practice_skill(object me)
{
	return notify_fail("龙象般若功只能用学(learn)的来增加熟练度。\n");
}

string exert_function_file(string func)
{
	return __DIR__"longxiang/" + func;
}
mapping curing_msg(object me)
{
        return ([
"apply_short" :me->name()+"左手伸指，右手竖掌，衣衫鼓动，周身真气彭湃。",
"start_self" :HIW"你盘膝而坐，左手伸指，右手竖掌，口念明王回生诀，运起龙象之力疗伤。\n"NOR,
"on_self" :HIM"你口中默念不动明王回生诀，龙象之力运转周身，伤势慢慢愈合。\n"NOR,
"start_other" :HIM""+me->name()+"面目端庄，唇齿启合间，浑身散发强大真气。\n"NOR,
"finish_self" :HIW"你感到龙象之力运转周身，所有伤势一扫而空，缓缓站了起来。\n"NOR,
"finish_other" :me->name()+"睁开双目，收回真气，缓缓站了起来，精神饱满。\n",
"unfinish_self" :"你正运用龙象之力疗伤，忽觉丹田空虚，后继无力，只好暂缓疗伤。\n",
"unfinish_other":me->name()+"睁开双目，缓缓站起，脸色疲乏，略显汗痕。\n",
"halt_self" :"你深吸一口气，将龙象真气强行收回丹田，站起身来。\n",
"halt_other" :me->name() +"深吸一口气，眉头微皱，站起身来。\n",
        ]);
} 
