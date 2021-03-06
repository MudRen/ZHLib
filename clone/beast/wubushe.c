// wubushe.c

#include <ansi.h>

inherit SNAKE;

void create()
{
	set_name("五步蛇", ({ "wubushe" }) );
	set("long",	"五步蛇是福建地方毒蛇，相传中毒行路五步即行倒毙。\n");

	set("race", "蛇类");
	set("age", 3);
	set("attitude", "peaceful");

	set("max_ging", 180);
	set("max_qi", 300);

	set("str", 10);
	set("con", 50);

	set("limbs", ({ "头部", "身体", "尾巴" }) );
	set("verbs", ({ "bite" }) );

        set("snake_poison", ([
                "level"  : 50,
                "perhit" : 25,
                "remain" : 50,
                "maximum": 50,
                "supply" : 2,
        ]));

	set_temp("apply/attack",  50);
	set_temp("apply/damage",  10);
	set_temp("apply/defense", 70);
	set_temp("apply/armor",   10);

	set("combat_exp", 6000);
	setup();
}

int convert(string arg)
{
	object me = this_player();
	object ob;

	if (arg!="snake" && arg!="wubushe") return 0;
	if (me->query("family/family_name") != "欧阳世家") 
		return notify_fail("你不能化蛇为杖。\n");
	if (random(me->query_skill("training",1)) <20) {
		kill_ob(me);
		return 1;
	}
	message_vision("$N左手按住五步蛇的头，右手轻抚其七寸，口中念念有词，片刻间将蛇化为一根蛇杖。\n",
		me,);
	        ob = new("/d/baituo/obj/shezhang");
        ob->move(environment(this_object()));
        destruct(this_object());
	return 1;
}