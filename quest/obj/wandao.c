#include <ansi.h>
#include <weapon.h>
inherit BLADE;
void create()
{       
set_name(HIC "圆月弯刀" NOR, ({ "wandao" }) );  
set_weight(7000);
        if( clonep() )  
        set_default_object(__FILE__);   
        else {          set("unit", "把");              
                        set("long", "这是一把形状很奇特的刀，刀身仿佛有点弯曲。\n");            set("material", "steel");               set("wield_msg", "$N的$n突然出鞘，你根本就没有看见$N拔刀！\n");          set("unwield_msg", "$N的$n已入鞘。\n");
        }       
init_blade(25); 
setup();
}
