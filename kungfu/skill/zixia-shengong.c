// zixia-shengong.c 紫霞神功
// By Hop

#include <ansi.h>
inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force) { return force == "huashan-xinfa"; }

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("zixia-shengong", 1);
        return lvl * lvl * 15 * 15 / 100 / 200;
}

int valid_learn(object me)
{
	if (me->query("gender") == "无性" &&
	    (int)me->query_skill("zixia-shengong", 1) > 49)
		return notify_fail("你无根无性，阴阳不调，难以领会高深的紫霞神功。\n");

	if ((int)me->query_skill("force", 1) < 60)
		return notify_fail("你的基本内功火候还不够，还不能学习紫霞神功。\n");

	return ::valid_learn(me);
}

int practice_skill(object me)
{
	return notify_fail("紫霞神功只能用学(learn)的来增加熟练度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"zixia-shengong/" + func;
}
mapping curing_msg(object me)
{
        return ([
"apply_short"   : me->name()+"盘坐地上，面色凝重，满脸紫气氤氲。",
"start_self"    : HIM"你就地盘坐，运使紫霞神功疗伤，内息返诸柔善，鸣天鼓，饮玉浆，荡华池，叩金梁，流通周身脉络。\n"NOR,
"on_self"       : MAG"你体内真气返诸柔善，鸣天鼓，饮玉浆，荡华池，叩金梁，伤势大有好转。\n"NOR,
"start_other"   : MAG+me->name()+ "就地盘坐，脸现紫气，开始运功疗伤。\n"NOR,
"finish_self"   : HIM"你催运紫霞功疗伤多时，一道真气在体内运转无碍，内伤已经平复，当即站起身来。\n",
"finish_other"  : MAG"但见"+ me->name()+ "头顶白雾弥漫，脸上紫气大盛，忽然间一声长啸，站起身来。\n"NOR,
"unfinish_self" : "你正运气疗伤间，渐觉丹田空虚，后力不继，只能暂缓疗伤。\n",
"unfinish_other": me->name()+"脸上紫气渐渐淡去，缓缓起身，气喘不息。\n",
"halt_self"     : "你将紫霞真气压回体内，站了起来。\n",
"halt_other"    : me->name() +"脸上紫气突然散去，站了起来，看上去精神了一些。\n",
        ]);
}
