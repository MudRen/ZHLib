// weapon: /z/xingxiu/npc/obj/wandao.c
// Jay 3/17/96

#include <weapon.h>
#include <ansi.h>
inherit BLADE;

void create()
{
        set_name(HIW"阿拉伯弯刀"NOR, ({ "wan dao","dao"}));
        set_weight(6000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "这是一柄亮晃晃的阿拉伯弯刀，刀身呈新月状，是中东"
"地区最常见的兵刃。\n");
                set("value", 40000);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一声抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N将手中的$n插回刀鞘。\n");
        }
        init_blade(200);
        setup();
 }
