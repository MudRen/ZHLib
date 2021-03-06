// xixing-dafa.c 吸星大法

#include <ansi.h>
inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
        return 1;
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("xixing-dafa", 1);
        return lvl * lvl * 15 * 20 / 100 / 200;
}

int valid_learn(object me)
{
        int lvl = (int)me->query_skill("xixing-dafa", 1);

        if (me->query("family/family_name") != "日月神教")
                return notify_fail("这是日月神教绝学，你领悟不了。\n");

        if (me->query("character") == "光明磊落")
                return notify_fail("你心中暗道：这种害人武功，我学它作甚？\n");

        if (me->query("gender") == "无性")
                return notify_fail("你突然感觉内息紊乱，看来不能贸然修习大法。\n");

        if (me->query("con") < 26)
                return notify_fail("你试着按照法门运转了一下内息，忽然"
                                   "觉得脸热心跳，丹田却是一阵冰凉！\n");

        if ( (int)me->query_skill("riyue-xinfa", 1) < 150 )
                return notify_fail("你的日月心法等级太低，不能领会这门绝学。\n");

        if (lvl >= 10 && lvl < 180 && me->query("max_neili"))
                return notify_fail("你没有按照吸星大法的诀窍将内"
                                   "力散去，现在还不敢妄自继续修行大法。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("吸星大法只能用学的，或是从运用(exert)中增加熟练度。\n");
}

mixed hit_by(object me, object victim, int damage, int damage_bonus, int factor)
{
        object weapon1 = me->query_temp("weapon");
        object weapon2 = victim->query_temp("weapon");

        int ap, dp;
        string skilltype,result;
        mapping prepare;

        dp = (int)victim->query_skill("xixing-dafa",1);
        if (dp<100) return damage;

        if (objectp(weapon2) ){
                skilltype=weapon2->query("skill_type");
                dp += victim->query_skill(skilltype,1);
        } else {
                prepare = victim->query_skill_prepare();
                if (! prepare) prepare = ([]);
                switch (sizeof(prepare))
                {
                        case 0: skilltype = "unarmed"; break;
                        case 1: skilltype = (keys(prepare))[0]; break;
                        case 2: skilltype = (keys(prepare))[victim->query_temp("action_flag")]; break;
                }
                dp += victim->query_skill(skilltype,1);
        }

        ap = me->query_skill("force",1);
        if (objectp(weapon1))
                ap += me->query_skill("parry");
        else
                ap += me->query_skill("dodge");

        if ( dp > ap/2 + random(ap) ) {
                if ( objectp(weapon2) && objectp(weapon1)) {
                        if (damage + damage_bonus > 0)
                        {                 
                                me->add("neili", -victim->query_skill("force"));
                                victim->add("neili", victim->query_skill("force"));
                                damage_bonus=-random(4000);
                                result = HIB"$n的兵刃上隐然豪光闪烁，和$N的兵刃相交，$N突然觉得内力源源不绝从的流了出去。\n"NOR;
                        }
                        else {
                                result = HIB"只见$n手中兵刃发出淡淡光茫，$N心中一惊，不敢妄进，将兵刃收了回去。\n"NOR;
                                damage_bonus=-random(4000);
                        }
                }
                else if(objectp(weapon2) && !objectp(weapon1)){
                        if (damage + damage_bonus > 0)
                        {
                                damage_bonus=-random(4000);
                                result = HIB"$n突然发动吸星大法，$N突然觉得内力源源不绝的流了出去。\n"NOR;                      
                                me->add("neili", -victim->query_skill("force"));
                                victim->add("neili", victim->query_skill("force"));
                        }
                        else {
                                result = HIB"只见$n不闪不躲，径自迎上前来，$N心中一惊，不敢妄进，将进招改为守招。\n"NOR;
                                damage_bonus=-random(4000);
                        }

                }
                else if( !objectp(weapon2) && objectp(weapon1) ) {
                        if (damage + damage_bonus > 0)
                        {                 
                                damage_bonus=-random(4000);
                                me->add("neili", -victim->query_skill("force"));
                                victim->add("neili", victim->query_skill("force"));
                                result = HIB"$n身子一闪，顺手在$N的兵刃侧面轻轻一触，$N突然觉得胸中若有所失。\n"NOR;
                        }
                        else {
                                result = HIB"只见$n嘿嘿一笑，竟然不招不架，$N心中一惊，不敢妄进，将兵刃收了回去。\n"NOR;
                                damage_bonus=-random(4000);
                        }

                }
                else{
                        if (damage + damage_bonus > 0)
                        {                 
                                damage_bonus=-random(4000);
                                me->add("neili", -victim->query_skill("force"));
                                victim->add("neili", victim->query_skill("force"));
                                result = HIB"$N的手掌和$n的身体一触，忽觉丹田一空，内力飞泻而出。\n"NOR;
                        }
                        else {
                                result = HIB"只见$n嘿嘿一笑，竟然不招不架，$N心中一惊，不敢妄进，将兵刃收了回去。\n"NOR;
                                damage_bonus=-random(4000);
                        }
                                
                }
                return ([ "msg" : result, "damage" : damage_bonus ]);
        }
        return damage;
}

string exert_function_file(string func)
{
        return __DIR__"xixing-dafa/" + func;
}

void check_count(object me)
{
        if (me->query("max_neili") >= 3000 &&
            me->query("exception/xixing-count") > 1000)
        {
                me->apply_condition("xixing-fanshi",
                        me->query_condition("xixing-fanshi") +
                        me->query("exception/xixing-count") / 10);
                me->delete("exception/xixing-count");
        }
}

void skill_improved()
{
        this_player()->add("exception/xixing-count",
                           (int)this_player()->query_skill("xixing-dafa", 1) + 1);
        check_count(this_player());
}

