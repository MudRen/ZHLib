// yuanyuantai
inherit ROOM;
#include <ansi.h>
void create()
{
	set("short", "问心泉");
	set("long", @LONG
问心泉躺卧在山麓的沟谷里，溅珠喷雪，下垂若帘。有诗云：”行到山深
处，帘泉一画图。岩空悬百尺，涧响落千珠。春雨流通急，秋云滴不枯。”然
而问心泉闻名的并不是它的美景，而是“问心”这一泉名。心错而情错，情孽
油生。上山拜月老的人，不妨在这里饮一掬清泉，扪心自问。是有情人终成眷
属，若错姻缘早离早散。
LONG );

	set("exits", ([
		"east" : __DIR__"shandao1",
 	]));

	set("objects", ([
		__DIR__"npc/qinger": 1,
	]));

	setup();
	replace_program(ROOM);
}
