#include <ansi.h>
#include <armor.h>

inherit CLOTH;

void create()
{
        set_name(HIY "���[����" NOR, ({ "jinlan jiasha", "jinlan", "jiasha" }));
        set_weight(1000);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "��");
                set("long", HIY "���[�����������������ഫ��ʥ����ɱ���"
                            "������˿���ɽ�\n����Ϊ�ߣ��ɶ�֯�ͣ���Ů����"
                            "�������ط��廨�죬ƬƬ���\n�ѽ��p����������"
                            "�����ƣ�����һ�β��Ʒɡ�\n" NOR);
                set("wear_msg", HIY "ֻ����������һ����$Nչ��һ���������"
                            "�������������ϡ�˲\nʱ����ǧ�������ƶ�䡣ң"
                            "��$N����ׯ�ϣ����ν����ɽǰ��\n������������"
                            "��͸���⡣����Ƕ�������������������Ƕ���\n"
                            NOR);
                set("remove_msg", HIY "$N�����[���Ĵ��������£��۵���СС"
                            "��һ�š�\n" NOR);
                set("no_sell", "�����Ǻã���ϧ��������ͺ��������û�����ա�");
                set("value", 100000);
                set("material", "silk");
                set("armor_prop/armor", 100);
                set("stable", 100);
        }
        setup();
}