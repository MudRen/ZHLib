// taiji-quan.c ̫��ȭ
// Modify by haiyan

#include <ansi.h>

inherit SKILL;

int can_not_hubo() {return 1;}

mapping *action = ({
([      "action" : "$Nʹһ�С���ȸβ����˫�ֻ��˸���Ȧ������$n��$l",
        "force" : 20,
        "dodge" : 50,
        "parry" : 38,
        "skill_name" : "��ȸβ",
        "lvl" : 0,
        "damage_type" : "����"
]),
([      "action" : "$Nʹһ�С����ޡ��������������£���������ӳ�������$n��$l",
        "force" : 25,
        "dodge" : 48,
        "parry" : 57,
        "skill_name" : "����",
        "lvl" : 5,
        "damage_type" : "����"
]),
([      "action" : "$N���ֻ��գ������ɹ����ƣ���������ʹһ�С�������ʽ������$n��$l��ȥ",
        "force" : 25,
        "dodge" : 46,
        "parry" : 49,
        "skill_name" : "������ʽ",
        "lvl" : 10,
        "damage_type" : "����"
]),
([      "action" : "$N˫�ֻ������������ϣ��������£�ʹһ�С��׺����᡹���ֻ�$n�����ź�$l",
        "force" : 25,
        "dodge" : 44,
        "parry" : 71,
        "skill_name" : "�׺�����",
        "lvl" : 15,
        "damage_type" : "����"
]),
([      "action" : "$N��������ǰ���£�����΢ת������һ����Ȧ��ʹһ�С�§ϥ�ֲ���������$n��$l",
        "force" : 25,
        "dodge" : 44,
        "parry" : 58,
        "skill_name" : "§ϥ�ֲ�",
        "lvl" : 20,
        "damage_type" : "����"
]),
([      "action" : "$N�������������������ںϣ�ʹһ�С��ֻ����á�����$n��$l��ȥ",
        "force" : 30,
        "dodge" : 48,
        "parry" : 62,
        "skill_name" : "�ֻ�����",
        "lvl" : 25,
        "damage_type" : "����"
]),
([      "action" : "$N���ֱ��ƺ�����ǰ����ȭ�����´�����һ�С���׿�����������$n��$l",
        "force" : 30,
        "dodge" : 54,
        "parry" : 71,
        "skill_name" : "��׿���",
        "lvl" : 30,
        "damage_type" : "����"
]),
([      "action" : "$N���ǰ̤�벽������ʹһ�С������롹��ָ������$n��$l��ȥ",
        "force" : 30,
        "dodge" : 76,
        "parry" : 65,
        "skill_name" : "������",
        "lvl" : 35,
        "damage_type" : "����"
]),
([      "action" : "$N�С���ͨ�ۡ������һ���������������Ͼ�����Ʋ������$n��$l��ȥ",
        "force" : 30,
        "dodge" : 79,
        "parry" : 76,
        "skill_name" : "��ͨ��",
        "lvl" : 40,
        "damage_type" : "����"
]),
([      "action" : "$N��������ԣ�ת�����������·ֱ�ӳ�������ʹһ�С�б��ʽ��������$n��$l",
        "force" : 35,
        "dodge" : 82,
        "parry" : 52,
        "skill_name" : "б��ʽ",
        "lvl" : 45,
        "damage_type" : "����"
]),
([      "action" : "$N�����鰴������ʹһ�С��������š�����$n��$l��ȥ",
        "force" : 35,
        "dodge" : 70,
        "parry" : 82,
        "skill_name" : "��������",
        "lvl" : 50,
        "damage_type" : "����"
]),
([      "action" : "$N˫����ȭ����ǰ��󻮻���һ�С�˫����������$n��$l",
        "force" : 35,
        "dodge" : 88,
        "parry" : 51,
        "skill_name" : "˫����",
        "lvl" : 55,
        "damage_type" : "����"
]),
([      "action" : "$N�����黮������һ�ǡ�ָ�ɴ�������$n���ɲ�",
        "force" : 40,
        "dodge" : 86,
        "parry" : 71,
        "skill_name" : "ָ�ɴ�",
        "lvl" : 60,
        "damage_type" : "����"
]),
([      "action" : "$Nʩ��������ʽ�������ֻ���$n��$l�����ֹ���$n���ɲ�",
        "force" : 40,
        "dodge" : 84,
        "parry" : 81,
        "skill_name" : "����ʽ",
        "lvl" : 65,
        "damage_type" : "����"
]),
([      "action" : "$N�ɱ۴��֣�����ǰ����������ʹһ�С����֡�������$n��$l",
        "force" : 45,
        "dodge" : 82,
        "parry" : 87,
        "skill_name" : "����",
        "lvl" : 70,
        "damage_type" : "����"
]),
([      "action" : "$N������������ʹһ�С��𼦶���������$n��$l��ȥ",
        "force" : 50,
        "dodge" : 90,
        "parry" : 51,
        "skill_name" : "�𼦶���",
        "lvl" : 75,
        "damage_type" : "����"
]),
([      "action" : "$N�����ɹ����ƣ�˫���������ϣ�������ǰ�Ƴ�һ�С���̽����",
        "force" : 55,
        "dodge" : 68,
        "parry" : 90,
        "skill_name" : "��̽��",
        "lvl" : 80,
        "damage_type" : "����"
]),
([      "action" : "$N����ʹһʽ�С���Ů���󡹣�������$n��$l��ȥ",
        "force" : 60,
        "dodge" : 76,
        "parry" : 92,
        "skill_name" : "��Ů����",
        "lvl" : 85,
        "damage_type" : "����"
]),
([      "action" : "$N���־���ǰ��������ǰƲ����ʹһ�С�����Ʋ��������$n��$l��ȥ",
        "force" : 65,
        "dodge" : 84,
        "parry" : 95,
        "skill_name" : "����Ʋ��",
        "lvl" : 90,
        "damage_type" : "����"
]),
([      "action" : "$N�����鰴������ʹһ�С�ת�����ȡ�����$n��$l��ȥ",
        "force" : 70,
        "dodge" : 42,
        "parry" : 99,
        "skill_name" : "��������",
        "lvl" : 100,
        "damage_type" : "����"
]),
([      "action" : "$N�������ϻ�������������ʹһ�С�������������$n��$l��ȥ",
        "force" : 75,
        "dodge" : 81,
        "parry" : 102,
        "skill_name" : "��������",
        "lvl" : 120,
        "damage_type" : "����"
]),
([      "action" : "$Nʹһ�С��Դ���������§��ϥ���������´���$n��$l",
        "force" : 80,
        "dodge" : 88,
        "parry" : 115,
        "skill_name" : "�Դ�",
        "lvl" : 140,
        "damage_type" : "����"
]),
([      "action" : "$N˫���ȱ�����״�����طֿ������������£�һ�С�Ұ�����ס�����$n��$l�����Ŵ�ȥ",
        "force" : 85,
        "dodge" : 86,
        "parry" : 119,
        "skill_name" : "Ұ������",
        "lvl" : 160,
        "damage_type" : "����"
]),
([      "action" : "$N��������ǰ���£��ұ�΢����ʹһ�С�������ɽ������$n��$l��ȥ",
        "force" : 90,
        "dodge" : 94,
        "parry" : 115,
        "skill_name" : "������ɽ",
        "lvl" : 180,
        "damage_type" : "����"
]),
([      "action" : "$N˫�־��¸�����������ǰ����ʮ��״��һʽ��ʮ���֡�����$n��$l��ȥ",
        "force" : 95,
        "dodge" : 102,
        "parry" : 122,
        "skill_name" : "ʮ����",
        "lvl" : 200,
        "damage_type" : "����"
]),
([      "action" : "$N���̤һ���鲽��˫�ֽ����ʮ��ȭ��һ�С��������ǡ�����$n��$l��ȥ",
        "force" : 100,
        "dodge" : 110,
        "parry" : 133,
        "skill_name" : "��������",
        "lvl" : 210,
        "damage_type" : "����"
]),
([      "action" : "$N��������ڳ���������ֱ���ұ�΢����ʹһ�С���������$n��$l�����Ŵ�ȥ",
        "force" : 115,
        "dodge" : 132,
        "parry" : 121,
        "skill_name" : "�����",
        "lvl" : 220,
        "damage_type" : "����"
]),
([      "action" : "$N˫���쿪������Ϊ�ᣬ������������һ����Բ����\nһ�С�ת������������$n�������¶�������������Ӱ֮��",
        "force" : 120,
        "dodge" : 154,
        "parry" : 145,
        "skill_name" : "ת������",
        "lvl" : 230,
        "damage_type" : "����"
]),
([      "action" : "$N˫����ȭ�����ֻ����������ʣ����ֻ�����ǰ�Ƴ���\nȭ�������һ�С��乭�仢����ֱ��$n���Ѷ�ȥ",
        "force" : 115,
        "dodge" : 166,
        "parry" : 175,
        "skill_name" : "�乭�仢",
        "lvl" : 240,
        "damage_type" : "����"
]),
([      "action" : "$N˫������ǰ���ƣ��ɸ�����ǰ�����Ƴ���һ�С�����Ʊա���һ�ɾ���ֱ��$n",
        "force" : 120,
        "dodge" : 178,
        "parry" : 185,
        "skill_name" : "����Ʊ�",
        "lvl" : 250,
        "damage_type" : "����"
]),
});


int valid_enable(string usage) { return usage == "cuff" || usage == "parry"; }

int valid_combine(string combo)
{
        return combo == "wudang-zhang" || combo == "paiyun-shou";
}

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("��̫��ȭ������֡�\n");

        if ((int)me->query_skill("force") < 180)
                return notify_fail("����ڹ���򲻹����޷�ѧ̫��ȭ��\n");

        if ((int)me->query_skill("taiji-shengong",1) < 100) 
                return notify_fail("���̫���񹦻�򲻹����޷�����̫��ȭ��\n"); 

        if ((int)me->query_skill("taoism",1) < 200) 
                return notify_fail("��ĵ�ѧ�ķ���Ϊ������������̫��ȭ��\n"); 

        if ((int)me->query("max_neili") < 1000)
                return notify_fail("�������̫�����޷���̫��ȭ��\n");

        if ((int)me->query_skill("cuff", 1) < 100)
                return notify_fail("��Ļ���ȭ����򲻹����޷�ѧϰ̫��ȭ��\n");

        if (me->query("gender") == "����" && 
           (int)me->query_skill("taiji-quan", 1) > 99) 
                return notify_fail("���޸����ԣ����������������������̫��ȭ����\n"); 

        if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("taiji-quan", 1))
                return notify_fail("��Ļ���ȭ��ˮƽ���ޣ��޷����������̫��ȭ��\n");

        if ((int)me->query_skill("taiji-quan", 1) >= 200 &&
            (int)me->query_skill("taiji-quan", 1) < 300 &&
            !me->query("taiji_quanli",1))
                return notify_fail("�㻹δ����̫��ȭ�����޷����������̫��ȭ��\n");

        if ((int)me->query_skill("taiji-quan", 1) >= 300 &&
            (int)me->query_skill("taiji-quan", 1) < 400 &&
            me->query("taiji_quanli",1) < 2 && me->query("taiji_quanli",1) >= 1)
                return notify_fail("����Ҫ�������һ���̫��ȭ��������������̫��ȭˮƽ��\n");

        if ((int)me->query_skill("taiji-quan", 1) >= 400 &&
            (int)me->query_skill("taiji-quan", 1) < 500 &&
            me->query("taiji_quanli",1) < 3 && me->query("taiji_quanli",1) >= 2)
                return notify_fail("����Ҫ�������һ���̫��ȭ��������������̫��ȭˮƽ��\n");

        if ((int)me->query_skill("taiji-quan", 1) >= 500 &&
            me->query("taiji_quanli",1) < 4 && me->query("taiji_quanli",1) >= 3)
                return notify_fail("����Ҫ�������һ���̫��ȭ��������������̫��ȭˮƽ��\n");

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
        level = (int) me->query_skill("taiji-quan",1);
        for(i = sizeof(action); i > 0; i--)
            if(level > action[i-1]["lvl"])
                return action[NewRandom(i, 5, level/5)];
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp, acter;

        if ((int)me->query_skill("taiji-quan", 1) < 100 ||
            me->query_temp("weapon"))
                return;

        if (!living(me) || (me->is_busy() && random(3) == 0))  return;

        ap = (ob->query_skill("force", 1) +  
             ob->query_skill("dodge", 1) + 
             ob->query_skill("martial-cognize", 1)) / 3 ;

        if (me->query("character") == "��������" || me->query("character") == "������")  
             acter = 4;  
        else 
             acter = 5;  

        dp = (me->query_skill("force", 1) / 2 +
             me->query_skill("parry", 1) + 
             me->query_skill("taiji-quan", 1) + 
             me->query_skill("martial-cognize", 1) +  
             me->query_skill("taoism", 1) / 2) / acter;

        if (dp / 2 + random(dp) > ap)
        {
                result = ([ "damage": -damage ]);

                switch (random(2))
                {
                case 0:
                        result += (["msg" : HIC "$n" HIC "�溬΢Ц��˫�������������"
                                            "һ��ԲȦ����Ȼ��$N" +
                                            HIC "�Ĺ���ȫ��������\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIC "$n" HIC "������ȭ"
                                            HIC "��������Ȼ������ȴ��$N"
                                            HIC "�е�����ճ�ͣ������泩��\n" NOR]);
                        break;
                }
                return result;
        }
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        if (me->query_temp("weapon"))
                return 0;

        lvl = me->query_skill("taiji-quan", 1);
        if (lvl < 100) return 0;
        if (lvl < 200) return 50;
        if (lvl < 300) return 80;
        if (lvl < 400) return 100;
        return 120;
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 70)
                return notify_fail("�������̫���ˡ�\n");

        if ((int)me->query("neili") < 70)
                return notify_fail("�������������̫��ȭ��\n");

        me->receive_damage("qi", 35);
        me->add("neili", -59);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"taiji-quan/" + action;
}
