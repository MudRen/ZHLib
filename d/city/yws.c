// Room: /d/city/yws.c
// This is a room made by roommaker. write by Fan. :)

inherit ROOM;

void create()
{
	set("short", "医务室");
	set("long", @LONG
这里是擂台旁边的医务室，专门用来抢救因比武后重伤的江湖
人士。医务室的左边放着一个大药柜，里面有各式各样的药品，在
右边是一张休息用的床，是用来给受伤的休息之用。
LONG
);
	set("sleep_room", "1");
	set("exits", ([ /* sizeof() == 1 */
  "out" : __DIR__"leitai.c",
]));
	set("no_clean_up", 0);

	setup();
}
void init()
{
        add_action("do_get","get");
        add_action("do_drop","drop");
}
int do_get()
{
        write(this_player()->query("name")+"！！那么多手多脚做什么！！\n");
        return 1;
}
int do_drop()
{
        write(this_player()->query("name")+"！！别乱丢东西！！\n");
        return 1;
}

