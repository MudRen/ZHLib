// ÕâÊÇÍæ¼Ò×Ô´´Îä¹¦³ÌÐò Ô­ÓÉmaxim@nju_fengxue±àÐ´£¬ÏÖÓÉxgchen@zzfyÐÞ¸Ä
// chhu
// ÁúÕ½ÓÚÒ°
// ÎÒÊÇÒ»Ö»Ð¡Ð¡Äñ[2;37;0m
// 42941418
// Å®ÐÔ
// sword
// ÌìµØÎÞÓÃ





inherit SKILL;

////////////////////////////////

mapping *action = ({

// ZHAOSHI :0

([
"action" :"$N×ÝÉíÒ»Ô¾£¬ÊÖÖÐ$wÒ»ÕÐ$HIW$¡¸½ð¹âÐºµØ¡¹$NOR$¶Ô×¼µÄ$lÐ±Ð±´Ì³öÒ»½£",
"force" :50,
"dodge" :20,
"damage_type": "´ÌÉË",
"attack" : 50,
"parry" : 50,
"lvl" : 0,
"skill_name" : "Ìì»èµØ°µ"
]),
 });
// ZHAOSHI :1
int valid_learn(object me)
{
object weapon; if (!objectp(weapon = me->query_temp("weapon"))
     || (string)weapon->query("skill_type") != "sword") return notify_fail("ÄãÊ¹ÓÃµÄÎäÆ÷²»¶Ô¡£\n");
        if( (int)me->query("max_neili") < 2500 )
                return notify_fail("ÄãµÄÄÚÁ¦Ì«Èõ£¬ÎÞ·¨Á·"+"ÌìµØÎÞÓÃ"+"¡£\n");
        return 1;
}
int valid_enable(string usage) { return usage=="sword" || usage=="parry"; }
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
    level = (int)me->query_skill("chhu-sword",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}
int practice_skill(object me)
{
object weapon; if (!objectp(weapon = me->query_temp("weapon")) || (string)weapon->query("skill_type") != "sword") return notify_fail("ÄãÊ¹ÓÃµÄÎäÆ÷²»¶Ô¡£\n");    if( (int)me->query("qi") < 100 )
                return notify_fail("ÄãµÄÌåÁ¦²»¹»ÁË£¬ÐÝÏ¢Ò»ÏÂÔÙÁ·°É¡£\n");
        if( (int)me->query("neili") < 100 )
                return notify_fail("ÄãµÄÄÚÁ¦²»¹»ÁË£¬ÐÝÏ¢Ò»ÏÂÔÙÁ·°É¡£\n");
        me->receive_damage("qi", 90);
        me->add("neili", -70);
        return 1;
} //total 34 lines!
string perform_action_file(string action)
{
        return __DIR__"meskill/" + action;
}
