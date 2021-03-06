// NPC /d/npc/caihuashe.c

inherit SNAKE;

void create()
{
        set_name("菜花蛇", ({ "caihua she", "she" }) );
        set("race", "蛇类");
        set("age", 1);
        set("long", "一只青幽幽的菜花蛇，头部呈椭圆形。\n");
        set("attitude", "peaceful");
 
        set("str", 15);
        set("con", 16);

        set("limbs", ({ "头部", "身体", "七寸", "尾巴" }) );
        set("verbs", ({ "bite" }) );
 
        set("combat_exp", 100 + random(50));

        set_temp("apply/attack", 7);
        set_temp("apply/damage", 4);
	set_temp("apply/defence",6);
	set_temp("apply/armor",5);

	setup();
}

void die()
{
	object ob;
	message_vision("$N抽搐两下，死了。\n", this_object());
	ob = new("/d/baituo/npc/obj/sherou");
	ob->move(environment());
	destruct(this_object());
}

int convert(string arg)
{
	object me = this_player();
	object ob;

	if (arg!="snake" && arg!="she" && arg!="caihua she") return 0;
	if (me->query("family/family_name") != "欧阳世家") 
		return notify_fail("你不能化蛇为杖。\n");
	return notify_fail("菜花蛇野性太小，攻击天性很差，不能化为杖。\n");
}