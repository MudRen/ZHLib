// tu.c ̫��ͼ

#include <ansi.h>

inherit F_SSERVER;

int perform(object me)
{
        object *obs;
        string msg;
        int damage;
        int ap, dp;
        int flag, acter;
        int i;

        if (userp(me) && me->query("can_perform/taiji-quan/tu") < 10)
                return notify_fail("�㻹�������á�̫��ͼ����\n");

        if (environment(me)->query("no_fight"))
                return notify_fail("���ﲻ�ܴ�ܡ�\n");

        me->clean_up_enemy();
        if (! me->is_fighting())
                return notify_fail("��̫��ͼ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ((int)me->query_skill("taiji-quan", 1) < 250)
                return notify_fail("���̫��ȭ������죬����ʹ�á�̫��ͼ����\n");

        if ((int)me->query_skill("taiji-shengong", 1) < 300)
                return notify_fail("���̫������Ϊ�������ߣ��������á�̫��ͼ����\n");

        if ((int)me->query_skill("taoism", 1) < 300)
                return notify_fail("��ĵ�ѧ�ķ���Ϊ�������ߣ��������á�̫��ͼ����\n");

        if ((int)me->query("jingli") < 1000)
                return notify_fail("�����ھ����������޷�ʹ�á�̫��ͼ����\n");

        if ((int)me->query("neili", 1) < 1000)
                return notify_fail("�����������������޷�ʹ�á�̫��ͼ����\n");

        if (objectp(me->query_temp("weapon")) ||
            objectp(me->query_temp("secondary_weapon")))
                return notify_fail("Ҫʩչ������̫��ͼ��������֡�\n");

        msg = HIM "$N" HIM "��ȻһЦ��˫�����Ữ������Ȧ�ӣ���ʱ���ܵ���"
              "��������ԴԴ���ϵı�ǣ��������\n\n" NOR;
        message_combatd(msg, me);

        me->add("neili", -1000);
        me->add("jingli", -1000);
        me->start_busy(4);
        if (me->query("character") == "��������" || me->query("character") == "������") 
             acter = 2;
        else 
             acter = 3; 
        ap = me->query_skill("taoism", 1) +
             me->query_skill("taiji-quan", 1) +
             me->query_skill("martial-cognize", 1) +
             me->query_skill("taiji-shengong", 1);
        obs = me->query_enemy();
        for (flag = 0, i = 0; i < sizeof(obs); i++)
        {
                dp = obs[i]->query_skill("force") * 2 +
                     obs[i]->query_skill("martial-cognize") +
                     obs[i]->query_skill("taoism", 1);
                if (ap / acter + random(ap) > dp || !living(obs[i]))
                {
                        switch (random(3))
                        {
                        case 0:
                                tell_object(obs[i], HIY "���֮�����ƺ��ص��˹�ȥ�����磬��"
                                                    "Ȼ���޷��������ң���Ȼ��ǰ��һ��\n"
                                                    "��ȫȻ����������ͷһ�ң�����һ���"
                                                    "ʹ�������������Կ��ƣ�\n" NOR);
                                break;
                        case 1:
                                tell_object(obs[i], HIW "����ǰһ�н�����ģ�������������ǵ�"
                                                    "���ɾ���Ȼ����ȴ������ϢԽ��Խ�ң�\n"
                                                    "��֫һ����ʹ������Ҫվ����ס��\n" NOR);
                                break;
                        default:
                                tell_object(obs[i], HIR "����ߺ�Ȼ����һ���������ۼ������"
                                                    "��紸����������㲻�����һ����\n"
                                                    "�������¶�����ʹ����ֻ�и������ȡ�\n" NOR);
                                break;
                        }
                        // receive damage of qi
                        damage = obs[i]->query("max_qi");
                        damage = damage * (15 + random(10)) / 100;
                        obs[i]->receive_damage("qi", damage, me);
                        obs[i]->receive_wound("qi", damage / 2, me);

                        // receive damage of jing
                        damage = obs[i]->query("max_jing");
                        damage = damage * (15 + random(10)) / 100;
                        obs[i]->receive_damage("jing", damage, me);
                        obs[i]->receive_wound("jing", damage / 3, me);

                        switch (random(3))
                        {
                        case 0:
                                msg = HIM "ֻ��" + obs[i]->name() +
                                      HIM "�����㵸���������ԣ���"
                                      "Ȼ���һ������Ѫ��ֹ��\n\n" NOR;
                                break;
                        case 1:
                                msg = HIR "ȴ��" + obs[i]->name() +
                                      HIR "��ò���ݣ��ƺ�������ʲ"
                                      "ô����֮�£�����һ�Σ�Ż��������Ѫ��\n\n" NOR;
                                break;
                        default:
                                msg = HIW + obs[i]->name() +
                                      HIW "����������һ��������������"
                                      "а�����϶��ų���Ѫ����\n\n" NOR;
                                break;
                        }
                        obs[i]->start_busy(3);
                        message("vision", msg, environment(me), ({ obs[i] }));
                        obs[i]->add("neili", -500);
                        flag = 1;
                } else
                {
                        tell_object(obs[i], HIG "�㷢����ǰ�ľ����ƻ����棬��æ"
                                            "Ĭ���ڹ����������š�\n" NOR);
                        obs[i]->add("neili", -200);
                }
                if (obs[i]->query("neili") < 0)
                        obs[i]->set("neili", 0);
        }

        if (! flag) 
                message_vision(HIM "Ȼ��û���κ�������$N"
			       HIM "��Ӱ�졣\n\n" NOR, me, 0, obs);

        return 1;
}