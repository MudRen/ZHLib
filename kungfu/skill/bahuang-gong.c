// bahuang-gong.c 八荒六合唯我独尊功

#include <ansi.h>
inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force) { return force == "xiaowuxiang"; }

int query_neili_improve(object me)  
{
        int lvl; 
        lvl = (int)me->query_skill("bahuang-gong", 1); 
        return lvl * lvl * 24 * 15 / 100 / 200; 
}

int valid_learn(object me)
{
	if ((int)me->query_skill("force", 1) < 80)
		return notify_fail("你的基本内功火候还不够。\n");

	if (me->query("gender") == "无性" &&
        (int)me->query_skill("bahuang-gong", 1) > 49)
		return notify_fail("你无根无性，阴阳不调，难以领会高深的八荒六合唯我独尊功。\n");

    	return ::valid_learn(me);
}

int practice_skill(object me)
{
	return notify_fail("八荒六合唯我独尊功只能用学(learn)的来增加熟练度。\n");
}

string exert_function_file(string func)
{
	return __DIR__"bahuang-gong/" + func;
}
mapping curing_msg(object me)
{
        return ([
"apply_short"   : me->name() +"盘膝而坐，鼻孔中两道白气氤氲缭绕，面色红白变幻。",
"start_self"    : HIW"你盘膝而坐，运用八荒六合为我独尊真气，丹田真气升腾而起，开始疗伤。\n"NOR,
"on_self"       : HIM"你的八荒六合唯我独尊真气自丹田升起，左鼻孔呼出，右鼻孔吸入，复又返回丹田。\n"NOR,
"start_other"   : HIM"只见"+ me->name() +"鼻孔中两道白气循环缭绕，头顶汗气蒸腾。\n"NOR,
"finish_self"   : HIW"你只觉真力运转顺畅，周身伤势痊愈，气沉丹田，站起身来。\n"NOR,
"finish_other"  : me->name() +"收起鼻孔间的白气，精神抖擞，站起身来。\n",
"unfinish_self" : "你渐感丹田空虚，后劲不继，不得不将在体内运转的内息收回。\n",
"unfinish_other": me->name()+"缓缓将鼻间白气吸入体内，缓缓站起，胸口起伏，微微气喘。\n",
"halt_self"     : "你将八荒六合唯我独尊真气收回，睁开双目，站起身来。\n",
"halt_other"    : me->name() +"收起鼻孔间两道白气，睁眼起身，伤势似乎看上好了不少。\n",
        ]);
}
