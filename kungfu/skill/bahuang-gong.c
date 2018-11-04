// bahuang-gong.c �˻�����Ψ�Ҷ���

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
		return notify_fail("��Ļ����ڹ���򻹲�����\n");

	if (me->query("gender") == "����" &&
        (int)me->query_skill("bahuang-gong", 1) > 49)
		return notify_fail("���޸����ԣ���������������������İ˻�����Ψ�Ҷ��𹦡�\n");

    	return ::valid_learn(me);
}

int practice_skill(object me)
{
	return notify_fail("�˻�����Ψ�Ҷ���ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
	return __DIR__"bahuang-gong/" + func;
}
mapping curing_msg(object me)
{
        return ([
"apply_short"   : me->name() +"��ϥ�������ǿ����������������ƣ���ɫ��ױ�á�",
"start_self"    : HIW"����ϥ���������ð˻�����Ϊ�Ҷ��������������������ڶ��𣬿�ʼ���ˡ�\n"NOR,
"on_self"       : HIM"��İ˻�����Ψ�Ҷ��������Ե���������ǿ׺������ұǿ����룬���ַ��ص��\n"NOR,
"start_other"   : HIM"ֻ��"+ me->name() +"�ǿ�����������ѭ�����ƣ�ͷ���������ڡ�\n"NOR,
"finish_self"   : HIW"��ֻ��������ת˳������������Ȭ�����������վ��������\n"NOR,
"finish_other"  : me->name() +"����ǿ׼�İ����������ӣ�վ��������\n",
"unfinish_self" : "�㽥�е�����飬�󾢲��̣����ò�����������ת����Ϣ�ջء�\n",
"unfinish_other": me->name()+"�������Ǽ�����������ڣ�����վ���ؿ������΢΢������\n",
"halt_self"     : "�㽫�˻�����Ψ�Ҷ��������ջأ�����˫Ŀ��վ��������\n",
"halt_other"    : me->name() +"����ǿ׼��������������������������ƺ����Ϻ��˲��١�\n",
        ]);
}