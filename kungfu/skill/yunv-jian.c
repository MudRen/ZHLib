// yunv-jian.c 玉女素心剑

#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action" : "$N一招"+HIG+"「雁行斜击」，身形斜飞，手中$w轻轻点向$n的$l",
        "force"  : 40,
        "dodge"  : 20,
        "parry"  : 20,
        "damage" : 25,
        "lvl"    : 0,
        "damage_type" : "刺伤"
]),
([      "action" : "$N长跃而起，"+HIW+"「白虹经天」"+NOR+"，$w猛然下刺",
         "force"  : 64, 
         "dodge"  : 64, 
         "parry"  : 74, 
         "damage" : 40, 
         "lvl"    : 4,
         "damage_type" : "刺伤"
]),
([      "action" : "$N使出"+HIY+"「浪迹天涯」"+NOR+"，挥剑直劈，威不可当",
        "force"  : 80,
        "attack" : 70,
        "dodge"  : 75,
        "parry"  : 60,
        "damage" : 50,
        "lvl"    : 9,
        "damage_type" : "内伤"
]),
([      "action" : "$N使"+HIM+"「花前月下」"+NOR+"一招自上而下搏击，模拟冰轮横空、清光铺地的光景",
        "force"  : 84,
        "attack" : 40,
        "dodge"  : 65,
        "parry"  : 80,
        "damage" : 60,
        "lvl"    : 14,
        "damage_type" : "刺伤"
]),
([      "action" : "$N手中$w由内自外一刺，左手如斟茶壶，使出"+HIG+"「扫雪烹茶」"+NOR+"来",
        "force"  : 70,
        "attack" : 80,
        "dodge"  : 70,
        "parry"  : 65,
        "damage" : 90,
        "lvl"    : 29,
        "damage_type" : "刺伤"
]),
([      "action" : "$N左掌横摆胸前，右手中$w轻轻挥拂，却是一招"+HIC+"「抚琴按萧」"+NOR+"",
        "force"  : 80,
        "attack" : 50,
        "dodge"  : 75,
        "parry"  : 85,
        "damage" : 40,
        "lvl"    : 34,
        "damage_type" : "刺伤"
]),
([      "action" : "$N一招"+HIG+"「松下对弈」"+NOR+"，$w自右向左挥一个大弧，刺向$n的$l",
        "force"  : 100,
        "attack" : 79,
        "dodge"  : 75,
        "parry"  : 95,
        "damage" : 92,
        "lvl"    : 39,
        "damage_type" : "刺伤"
]),
([      "action" : "$N左手如拂五弦，竟以掌为剑攻向$n，却是一招"+HIB+"「池边调鹤」"+NOR+"",
        "force"  : 110,
        "attack" : 60,
        "dodge"  : 50,
        "parry"  : 70,
        "damage" : 63,
        "lvl" : 44,
        "damage_type" : "刺伤"
]),
([      "action" : "$N一招"+HIY+"「柳絮风飘」NOW，$w轻灵地划出几个圆弧，向$n的$l挥去",
        "force"  : 90,
        "attack" : 65,
        "dodge"  : 85,
        "parry"  : 90,
        "damage" : 65,
        "lvl"    : 49,
        "damage_type" : "刺伤"
]),
([      "action" : "$N一招"+HIW+"「小园艺菊」"+NOR+"，手中$w迅疾向$n的下盘连点三点",
        "attack" : 121,
        "force"  : 90,
        "dodge"  : 95,
        "parry"  : 90,
        "damage" : 79,
        "lvl"    : 54,
        "damage_type" : "刺伤"
]),
([      "action" : "$N使出"+HIB+"「西窗夜话」"+NOR+"，手中$w中宫直入，攻向$n的$l",
        "force"  : 130,
        "attack" : 92,
        "dodge"  : 95,
        "parry"  : 90,
        "damage" : 39,
        "lvl"    : 59,
        "damage_type" : "刺伤"
]),
([      "action" : "$N脚下左高右低，一招"+HIG+"「柳荫联句」"+NOR+"，$w在空中化成一道光环，急攻$n",
        "force"  : 140,
        "attack" : 66,
        "dodge"  : 90,
        "parry"  : 40,
        "damage" : 51,
        "lvl"    : 64,
        "damage_type" : "内伤"
]),
([      "action" : "$N手中$w由下而上卷起，犹如打起竹帘一般，却是"+HIW+"「竹帘临池」"+NOR+"",
        "force"  : 130,
        "attack" : 70,
        "dodge"  : 65,
        "parry"  : 70,
        "damage" : 95,
        "lvl"    : 70,
        "damage_type" : "刺伤"
]),
([      "action" : "$N做搭弓射箭状，一招"+HIM+"「木兰射雁」"+NOR+"，右手$w直刺$n的$l",
        "force"  : 170,
        "attack" : 81,
        "dodge"  : 90,
        "parry"  : 80,
        "damage" : 81,
        "lvl"    : 76,
        "damage_type" : "刺伤"
]),
([      "action" : "$N左手剑诀一领，右手$w平平刺向$n的$l，是一招"+HIR+"「双蝶迷回」"+NOR+"",
        "force"  : 180,
        "attack" : 73,
        "dodge"  : 80,
        "parry"  : 60,
        "damage" : 45,
        "lvl"    : 82,
        "damage_type" : "刺伤"
]),
([      "action" : "$N手中$w合身疾刺，一招"+HIW+"「孤云出釉」"+NOR+"，直指$n的$l",
        "force"  : 190,
        "attack" : 76,
        "dodge"  : 90,
        "parry"  : 100,
        "damage" : 92,
        "lvl"    : 88,
        "damage_type" : "刺伤"
]),
([      "action" : "$N一招"+HIB+"「幽兰空谷」"+NOR+"，$w看似随意地一挥，从$n不可思议的角度攻入",
        "force"  : 240,
        "attack" : 107,
        "dodge"  : 100,
        "parry"  : 95,
        "damage" : 95,
        "lvl"    : 94,
        "damage_type" : "刺伤"
]),
([      "action" : "$N使出"+HIC+"「茶花满路」"+NOR+"，一时间空中尽是$w的影子，令$n不知如何抵挡",
        "force"  : 220,
        "attack" : 80,
        "dodge"  : 120, 
        "parry"  : 75,
        "damage" : 93,
        "lvl"    : 100,
        "damage_type" : "刺伤"
]),
([      "action" : "$N一招"+HIY+"「陌路采桑」"+NOR+"，$w连点数点，疾刺$n的$l",
        "force"  : 260,
        "attack" : 93,
        "dodge"  : 110, 
        "parry"  : 95,
        "damage" : 107,
        "lvl"    : 99,
        "damage_type" : "刺伤"
]),
([      "action" : "$N突然盘蹲下来，一招"+HIY+"「秋雨萧萧」"+NOR+"，$w自下而上刺向$n",
        "force"  : 220, 
        "attack"  : 130, 
        "dodge"  : 110, 
        "parry"  : 90, 
        "damage"  : 150, 
        "lvl"    : 106,
        "damage_type" : "刺伤"
]),
([      "action" : "$N错开脚步，手中$w突然从自己的肋下刺出，却是一招"+HIR+"「琴心剑胆」"+NOR+"",
        "force"  : 240, 
        "attack"  : 130, 
        "dodge"  : 90, 
        "parry"  : 130, 
        "damage"  : 130, 
        "lvl"    : 112,
        "damage_type" : "刺伤"
]),
([      "action" : "$N犹如在水面滑行一般，一招"+HIB+"「池塘秋夜」"+NOR+"，平平地向$n的$l挥去",
        "force"  : 260, 
        "attack"  : 150, 
        "dodge"  : 110, 
        "parry"  : 100, 
        "damage" : 125,
        "lvl"    : 118,
        "damage_type" : "刺伤"
]),
([      "action" : "$N一招"+HIM+"「皓腕玉镯」"+NOR+"，手中$w刺点$n的手腕",
        "force"  : 280, 
        "attack" : 150, 
        "dodge"  : 90, 
        "parry"  : 100, 
        "damage" : 160, 
        "lvl"    : 124,
        "damage_type" : "刺伤"
]),
([      "action" : "$N一招"+HIW+"「牡丹含泪」"+NOR+"，$w绕出数个银圈，平平地向$n的$l卷去",
        "force"  : 270,
        "attack" : 137,
        "dodge"  : 105,
        "parry"  : 95,
        "damage" : 138,
        "lvl"    : 131,
        "damage_type" : "刺伤"
]),
([      "action" : "$N左脚轻点地面，身形往前一扑，一招"+HIR+"「芍药蕴珠」"+NOR+"，$w向$n的$l刺去",
        "force"  : 290,
        "attack" : 138,
        "dodge"  : 110, 
        "parry"  : 110, 
        "damage"  : 130, 
        "lvl"    : 138,
        "damage_type" : "刺伤"
]),
([      "action" : "$N一招"+HIC+"「檐前飞燕」"+NOR+"，身形跃起，手中$w扫向$n的$l",
        "force"  : 350,
        "attack" : 120, 
        "dodge"  : 114, 
        "parry"  : 90, 
        "damage"  : 164, 
        "lvl"    : 145,
        "damage_type" : "刺伤"
]),

([      "action" : "$N脸现黯然之色，随意一招"+HIG+"「蒹葭苍苍」"+NOR+"，$w刺向$n的$l",
        "force"  : 320, 
        "attack"  : 180, 
        "dodge"  : 120, 
        "parry"  : 160, 
        "damage"  : 170, 
        "lvl"    : 159,
        "damage_type" : "刺伤"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("force") < 60)
                return notify_fail("你的内功火候不到，无法学习玉女素心剑法。\n");

        if ((int)me->query("neili") < 300)
                return notify_fail("你的内力太差，无法学习玉女素心剑法。\n");

        if (me->query_skill("sword", 1) < me->query_skill("yunv-jian", 1))
                return notify_fail("你的基本剑法水平有限，无法领会更高深的玉女剑法。\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
	object target;

	if (me->query_temp("yunv_hebi"))
	{
		target = me->select_opponent();
 		me->map_skill("sword", "quanzhen-jian");
        	me->setup();
        	COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
		me->map_skill("sword", "yunv-jian");
                me->setup();
	}
        level = (int) me->query_skill("yunv-jian", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        if (damage_bonus < 300) return 0;
	if (!stringp(victim->query_skill_mapped("sword"))) return 0;
	if (victim->query_skill_mapped("sword") != "quanzhen-jian") return 0;
	if (!victim->query_temp("weapon")) return 0;
	if (victim->query_temp("weapon")->query("skill_type") != "sword") return 0;

        if (random(10) > 5)
        {
                victim->receive_wound("qi", (damage_bonus - 300) / 5);
                message_vision(HIW "$N身形飘逸，面对$n的「全真剑法」，「玉女剑法」施展的越发轻灵刁钻，占尽先机！\n",me,victim);
                return HIR "$n只看到眼前无数剑尖颤动，目瞪口呆之际，已经给$N的" + me->query_temp("weapon")->query("name") + NOR + HIR + "刺中数下！\n" NOR;
        }
}

int practice_skill(object me)
{
        object weapon;

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对。\n");

        if ((int)me->query("qi") < 65)
                return notify_fail("你的体力不够练玉女剑法。\n");

        if ((int)me->query("neili") < 65)
                return notify_fail("你的内力不足以练玉女剑法。\n");

        me->receive_damage("qi", 52);
        me->add("neili", -58);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"yunv-jian/" + action;
}

