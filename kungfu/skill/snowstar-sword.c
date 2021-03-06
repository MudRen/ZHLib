// snowstar-sword.c
// 华夏玩家fastidium的自创武功：雪影寒星剑法
// Modified by smallfish@huaxia Sep.1998
#include <ansi.h>

inherit SKILL;

string is_private_skill() {return "fastidium";}
int can_not_hubo() {return 1;}

mapping *action = ({
([      "skill_name":    "千里冰封",
        "action":  "$N默运内力，一阵寒气透过剑身遥指$n，$n登时由心底泛起一股寒意，仿佛置身于万载玄冰之中",
        "dodge" : 80,
        "damage": 180,
        "force" : 330,
        "attack": 130,
        "parry" : 80,
        "lvl"   : 0,
        "damage_type":  "刺伤"
]),
([      "skill_name":    "星罗棋布",
        "action":  "$N一抖手中$w，万点寒星飘飘洒洒罩向$n",
        "dodge" : 90,
        "damage": 190,
        "force" : 340,
        "attack": 135,
        "parry" : 85,
        "lvl"   : 120,
        "damage_type":  "刺伤"
]),
([      "skill_name":    "纷飞雪舞",
        "action":  "$N舞动手中$w，似雪花纷飞，又似水银泻地，层层剑光笼罩$n，$n只觉眼前剑光闪烁，一时不知如何招架",
        "dodge" : 95,
        "damage": 200,
        "force" : 350,
        "attack": 140,
        "parry" : 90,
        "lvl"   : 140,
        "damage_type":  "刺伤"
]),
([      "skill_name":    "寒星电闪",
        "action":  "$N潜运内力 ，双手紧握$w，人剑合一，电闪般向$n刺去",
        "dodge" : 105,
        "damage": 210,
        "force" : 360,
        "attack": 145,
        "parry" : 95,
        "lvl"   : 160,
        "damage_type":  "刺伤"
]),
([      "skill_name":    "冰山雪影",
        "action":  "$N执剑而立，灵台清明，周围泛起一层寒雾，似与大自然已融为一体，手中的$w缓慢推向$n的$l",
        "dodge" : 110,
        "damage": 220,
        "force" : 370,
        "attack": 150,
        "parry" : 100,
        "lvl"   : 180,
        "damage_type":  "刺伤"
]),
([      "skill_name":    "人生如奕",
        "action":  "$N双目紧闭，信手向空处连劈几剑，$n顿时进退无路，眼前一花，$w已迎面刺来",
        "dodge" : 115,
        "damage": 230,
        "force" : 380,
        "attack": 155,
        "parry" : 105,
        "lvl"   : 200,
        "damage_type":  "刺伤"
]),
});

int valid_learn(object me)
{
    object ob;
    if( (int)me->query("max_neili") < 1000 )
        return notify_fail("你的内力不够，没有办法练雪影寒星剑法。\n");

    if( (int)me->query_skill("martial-cognize",1) < 300 )
        return notify_fail("你的武学修养不够，没有办法练雪影寒星剑法。\n");

    if( !(ob = me->query_temp("weapon"))
    ||      (string)ob->query("skill_type") != "sword" )
        return notify_fail("你必须先找一把剑才能练剑法。\n");

    return 1;
}

int valid_enable(string usage)
{
    return usage=="sword" || usage=="parry";
}

string query_skill_name(int level)
{
    int i;
    for(i = sizeof(action)-1; i >= 0; i--)
        if(level >= action[i]["lvl"])
            return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
    int i, level;
    level   = (int) me->query_skill("snowstar-sword",1);
    for(i = sizeof(action); i > 0; i--)
        if(level > action[i-1]["lvl"])
            return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
    if ((int)me->query("qi") < 60)
        return notify_fail("你的体力不足以练习雪影寒星剑法。\n");

    if ((int)me->query("neili") < 60 )
        return notify_fail("你的内力不够，没有办法练习雪影寒星剑法。\n");

    me->receive_damage("qi", 50);
    me->add("neili", -50);

    return 1;
}

string perform_action_file(string action)
{
        return __DIR__"snowstar-sword/" + action;
}
