#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "小龙蜡像" NOR, ({ "laxiang teddy", "laxiang","teddy" }));
	set_weight(3000);
	set_max_encumbrance(5000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "尊");
                set("long",
                 "这是古墓派第四代传人「浪迹江湖，随心所欲」小龙(teddy)的蜡像。\n"
                 "可以从蜡像上看到他英俊潇洒，气宇轩昂，风度翩翩，面目俊朗，貌似潘安。\n");
		set("value", 1);
		set("material", "wood");
set("no_get",1);
set("amount",30);
}
setup();
}
