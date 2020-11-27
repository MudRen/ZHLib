#include <ansi.h>  
#include <weapon.h>
inherit STAFF;
void create()
{
        set_name(HIG"寒玉杖"NOR, ({"hanyu zhang", "zhang" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("long", 
                "这是一柄用千年寒铁打造的寒玉杖，虽取自寒铁，然晶莹如玉。\n");
                set("value", 80000);   
                set("material", "crystal");
                set("wield_neili", 500);
                set("wield_maxneili", 1000);
                set("wield_str", 22);
                set("wield_msg", "$N「呼」的一声掏出一根$n握在手中。\n");
                set("unwield_msg", "$N将手中的$n插回背后。\n");   
        }
        init_staff(400);
        setup();
 }
