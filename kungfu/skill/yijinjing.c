// yijinjing.c 少林 易筋经神功
// Feb.21 1998 by Java

inherit FORCE;

int valid_enable(string usage)
{
        return usage == "force";
}

int valid_force(string force)
{
        return force == "hunyuan-yiqi" ||
               force == "taiji-shengong" ||
               force == "wudang-xinfa" ||
               force == "shaolin-xinfa"||
               force == "riyue-xinfa"||
               force == "xixing-dafa";
}

int query_neili_improve(object me)
{
    int lvl;

    lvl = (int)me->query_skill("yijinjing", 1);
    return lvl * lvl * 15 * 18 / 100 / 200;
}

int valid_learn(object me)
{
        if (me->query_skill("force", 1) < 100)
                return notify_fail("你的基本内功火候不够，无法学习易筋经神功！\n");

//        if (me->query("gender") != "男性")
//                return notify_fail("你不是男性，无法练习易筋经神功。\n");

        if (me->query("family/family_name") != "少林派" &&
            me->query("family/family_name") != "日月神教")
                  return notify_fail("易筋经神功乃少林绝技，妄自研习有害无利。\n");

        if (me->query("family/family_name") == "日月神教" &&
            me->query("family/master_name") != "任我行")
                  return notify_fail("易筋经神功乃少林绝技，妄自研习有害无利。\n");

        return ::valid_learn(me);
}


int practice_skill(object me)
{
        return notify_fail("易筋经神功只能用学(learn)的来增加熟练度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"yijinjing/" + func;
}

