#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", CYN"ʯ��"NOR);
	set("long", CYN @LONG
����һ��������ʯ������Χ���Ǽ�Ӳ��ʯ�ڡ� 
LONG NOR);
	set("exits", ([
		"south" : __DIR__"dong1",
		"north" : __DIR__"dong20",
                	]));
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}