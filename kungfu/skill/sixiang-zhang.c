// sixiang-zhang.c

inherit SKILL;

mapping *action = ({
([     "action" : "$N一式「拳震太阴」，侧身挥掌，带着呼呼的风声打向$n的$l",
       "force" : 180,
       "dodge" : 20,
       "parry" : 50,
       "lvl" : 0,
       "damage_type" : "内伤"
]),
([     "action" : "$N左拳虚握，右掌快如闪电般打向$n的$l，正是一招「到转太阳」",
       "force" : 205,
       "dodge" : 20,
       "lvl" : 0,
        "damage_type" : "瘀伤"
]),
([     "action" : "$N使招「意取少阴」，双掌交错，忽又分开，引内劲打向$n的$l",
       "force" : 240,
       "dodge" : 10,
       "parry" : 25,
       "lvl" : 10,
        "damage_type" : "内伤"
]),
([     "action" : "$N使出「意取少阳」如狂风骤雨般打向$n，掌影闪烁，已将$n团团围住",
       "force" : 280,
       "dodge" : 5,
       "parry" : 30,
       "lvl" : 10,
        "damage_type" : "瘀伤"
]),
([     "action" : "$N纵身越起直落在$n身后，一招「倒转乾坤」双脚落地后双掌向后挥出，打向$n的后心。",
       "force" : 290,
       "dodge" : 10,
       "parry" : 35,
       "lvl" : 30,
        "damage_type" : "瘀伤"
]),
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }

int valid_learn(object me)
{
       if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
               return notify_fail("四象掌必须空手。\n");

       if ((int)me->query("max_neili") < 100)
               return notify_fail("你的内力太弱，无法练功。\n");
       return 1;
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
       level   = (int) me->query_skill("sixiang-zhang",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
       if ((int)me->query("qi") < 30)
               return notify_fail("你的体力太低了。\n");
       if ((int)me->query("neili") < 20)
               return notify_fail("你的内力不够练四象掌。\n");
       me->receive_damage("qi", 30);
       me->add("neili", -10);
       return 1;
}
string perform_action_file(string action)
{
        return __DIR__"sixiang-zhang/" + action;
}
