#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIC "养精丹" NOR, ({"yangjing dan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "粒");
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        mapping my;

        if (time() - me->query_temp("last_eat/dan(A)") < 10)
        {
                write("你刚服用过药，需药性发挥完效用以后才能继续服用。\n");
                return 1;
        }

        my = me->query_entire_dbase();
        if (my["jing"] == my["max_jing"])
        {
                write("你现在精神状态很好，无需服用" + name() + "。\n");
                return 1;
        }
        if( me->is_busy() )
                return notify_fail("急什么，小心别噎着了。\n");

        me->set_temp("last_eat/dan(A)", time());

        message_vision(HIC "$N吃下一粒养精丹，感到灵台处一片清净。\n" NOR, me);
        me->receive_curing("jing", 50);
        me->receive_heal("jing", 50);

        me->start_busy(2);
        destruct(this_object());
        return 1;
}

