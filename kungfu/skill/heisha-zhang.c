// /kungfu/skill/heisha-zhang.c 黑沙掌
// By Alf, Last Update 2002.03
// 一佛出世　二鬼拍门　三长两短　四分五裂　五内俱焚　六神无主

#include <ansi.h>
inherit SKILL;

mapping *action =
({
([
    "action":   "$N沉腰坠马，大喝一声，使招「一佛出世」，出掌迳击$n的$l",
    "dodge": -10,
    "parry": -10,
    "force": 180,
    "damage_type": "内伤"
]),
([
    "action":   "$N身形一顿，双掌一错，一式「二鬼拍门」，左右分拍$n的$l",
    "dodge": -20,
    "parry": -20,
    "force": 200,
    "damage_type": "内伤"
]),
([
    "action":   "$N身形绕$n一转，一招「三长两短」展开，向$n的$l接连出掌",
    "dodge": -10,
    "parry": -10,
    "force": 220,
    "damage_type": "内伤"
]),
([
    "action":   "$N身法一变，使招「四分五裂」，掌影千变万幻，猛击$n的$l",
    "dodge": -30,
    "parry": -30,
    "force": 250,
    "damage_type": "内伤"
]),
([
    "action":   "$N身形一转，使出一式「五内俱焚」，漫天掌影罩住了$n的$l",
    "dodge": -20,
    "parry": -20,
    "force": 280,
    "damage_type": "内伤"
]),
([
    "action":   "$N厉啸一声，一式「六神无主」，双掌挥舞，掌掌不离$n的$l",
    "dodge": -10,
    "parry": -10,
    "force": 300,
    "damage_type": "内伤"
]),
});

int valid_enable(string usage)
{
    return usage=="unarmed" || usage=="parry";
}

int valid_learn(object me)
{
    if(me->query_temp("weapon")||me->query_temp("secondary_weapon"))
        return notify_fail("练黑沙掌必须空手。\n");
    if((int)me->query("max_neili") < 100)
        return notify_fail("你的内力太弱，无法练黑沙掌。\n");
    return 1;
}

mapping query_action(object me, object weapon)
{
    return action[random(sizeof(action))];
}

int practice_skill(object me)
{
    if((int)me->query("qi")<40)
        return notify_fail("你的体力太低了。\n");
    if((int)me->query("neili")<10)
        return notify_fail("你的内力不够了，休息一下再练吧。\n");
    me->receive_damage("qi",30);
    me->add("neili",-5);
    return 1;
}

mixed hit_ob(object me,object victim,int damage_bonus)
{
    if(random(me->query_skill("heisha-zhang"))>50)
        victim->apply_condition("heisha_poison",
        random(me->query_skill("heisha-zhang")/10)+1+victim->query_condition("heisha_poison"));
    if(damage_bonus<100)
        return 0;
    if(random(damage_bonus/2)>victim->query_str())
    {
        victim->receive_wound("qi",(damage_bonus-100)/2);
        return 
HIB"只听得「砰」的一声大响，"+victim->name()+"竟被"+me->name()+"的掌力震得倒飞了出去！\n" NOR;
    }
}

string perform_action_file(string action)
{
    return "/kungfu/skill/heisha-zhang/" + action;}

