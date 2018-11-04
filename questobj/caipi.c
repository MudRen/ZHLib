#include <ansi.h>
inherit ITEM;
void create()
{
    set_name(HIC"×íÏÉÂ¥²ËÆ×" NOR, ({ "caipu" }) );
    set_weight(1);
    if( clonep() )
            set_default_object(__FILE__);
    else {
            set("unit", "±¾");
            set("material", "stone");
            set("long", "Ò»±¾×íÏÉÂ¥²ËÆ×\n");
          }
    setup();
}
