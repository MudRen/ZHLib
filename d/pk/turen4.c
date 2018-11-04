// Room: /d/pk/turen4.c
// This is a room made by roommaker. write by Fan. :)

inherit ROOM;

void create()
{
	set("short", "[1;31mËéÊ¬³¡[2;37;0m");
	set("long", @LONG
ÕâÀïÒõÉ­¿Ö²À£¬µØÉÏµ½´¦ÊÇ²ĞÖ«ËéÊ¬£¬ÎŞ´¦²»ÊÇ°µºìÉ«µÄÑªµÎ¡£ÄãĞÄÖĞ
ìşìı²»°²£¬Íò·Ö¾¯Ìè£¬²»ÖªµÀ´ÓÄÄÀï¾Í»á´Ü³öÒ»¸öºÚÓ°¡£
LONG
);
	set("trds", "1");
	set("exits", ([ /* sizeof() == 4 */
  "north" : __DIR__"turen1",
  "west" : __DIR__"turen3",
  "east" : __DIR__"turen5",
  "south" : __DIR__"turen8",
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
