// File(/data/room/suifeng/xiaoyuan.c) of suifeng's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "桃花谷小院");
	set ("long", @LONG
这里是一个四四方方的院子，院墙都是用红砖砌成，不算高，但
是非常清爽利落。院中几棵古木成荫，隐然有一种世外桃源的感觉。
院子外面隐约是寒水潭，院子的北面有一扇木门。 
LONG );

        set("room_key", "1 of suifeng");
	setup();

	set("exits", ([
                "out"    : "/d/gumu/hanshuitan",
	]));

        set("outdoors", "quanzhen");
        set("no_sleep_room", 1);
        set("valid_startroom", 1);

        set("KEY_DOOR", ([
                "exit" : "north",
                "room" : __DIR__"dating",
        ]));
    
        set("room_owner", "柳随风");
        set("room_name", "桃花谷");
        set("room_id", "taohuagu");
        set("room_owner_id", "suifeng");
        set("room_position", "寒水潭");
}
