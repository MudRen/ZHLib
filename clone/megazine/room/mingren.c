#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
        set("short",HIW "【名人堂】" NOR);
	set("long", @LONG
这是终极地狱的【名人堂】，中国古代建筑艺术的精华都在这里
尽显。你只觉得这里是有生以来你所见到过的最高贵华丽的地方。中
央的石碑(bei)上刻着以被收入【名人堂】地名人名字， 向前走可以
通向各个名人的陈列室。
LONG
	);

	set("exits", ([ 
                "out" : "/clone/megazine/room/secondroom",
        ]));

        set("item_desc",([ "bei" : HIR "目前【名人堂】内还没有名人。\n" NOR, ]));
	set("no_fight", 1);
        create_door("out", "大门", "enter", DOOR_CLOSED);
     	setup();
        replace_program(ROOM);
}
