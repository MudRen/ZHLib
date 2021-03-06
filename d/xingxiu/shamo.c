// Room: /d/xingxiu/shamo4.c

#include <room.h>
inherit ROOM;

void create()
{
       set("short","大沙漠");
       set("long", @LONG
这是一片一望无际的大沙漠。你一进来就迷失了方向。
看来要走出这块沙漠并非易事。
LONG );
	set("outdoors", "xingxiuhai");
	set("exits", ([
		"east" : __FILE__,
		"west" : __FILE__,
		"south" : __FILE__,
		"north" : __FILE__,
	]));
	setup();
}

void init()
{
        object ob;
        int water, food;
        int qi, jing;

        if (interactive(ob = this_player()))
        {
                water = ob->query("water");
                food = ob->query("food");
                water -= (random(2) + 1) * water / 20 + 5;
                food -= (random(2) + 1) * food / 20 + 5;
                if (water < 0) water = 0;
                if (food < 0) food = 0;
                ob->set("water", water);
                ob->set("food", food);

                qi = ob->query("max_qi") * 5 / 100 + random(10);
                jing = ob->query("max_jing") * 5 / 100 + random(10);
                ob->receive_damage("qi", qi);
                ob->receive_damage("jing", jing);
        }
}

int valid_leave(object me, string dir)
{
        string dest;

        dest = sprintf("/d/xingxiu/shamo%d", random(10) + 1);
        me->move(dest);
        switch (random(3))
        {
        case 0:
                write("你顶着风沙走啊走，还是没有走出沙漠。\n");
                break;

        case 1:
                write("你望着漫天遍野的黄沙，叹了口气，无精打采的走着。\n");
                break;

        case 2:
                write("你一步步的往前挪着，早已分不出方向。\n");
                break;
        }
        return -1;
}
