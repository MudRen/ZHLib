#include <ansi.h>
inherit ITEM;
void create()
{
    set_name(HIR"镖旗"NOR, ({ "biaoqi" }) );
    set_weight(1);
    if( clonep() )
            set_default_object(__FILE__);
    else {
            set("unit", "张");
            set("material", "stone");
            set("long", "一张林家镖局的镖旗\n");
          }

    setup();
}
