#include <ansi.h>
inherit ITEM;
void create()
{
    set_name(HIW"尘拂" NOR, ({ "chenfu" }) );
    set_weight(1);
    if( clonep() )
            set_default_object(__FILE__);
    else {
            set("unit", "支");
            set("material", "paper");
            set("long", "一支普通的尘拂\n");
          }

    setup();
}
