// Room: /d/pk/turen7.c
// This is a room made by roommaker. write by Fan. :)

inherit ROOM;

void create()
{
	set("short", "[1;31mÉ¥Ãü³¡[2;37;0m");
	set("long", @LONG
ÕâÀïÒõÉ­¿Ö²À£¬µØÉÏµ½´¦ÊÇ²ĞÖ«ËéÊ¬£¬ÎŞ´¦²»ÊÇ°µºìÉ«µÄÑªµÎ¡£ÄãĞÄÖĞ
ìşìı²»°²£¬Íò·Ö¾¯Ìè£¬²»ÖªµÀ´ÓÄÄÀï¾Í»á´Ü³öÒ»¸öºÚÓ°¡£
LONG
);
	set("trds", "1");
	set("exits", ([ /* sizeof() == 3 */
  "north" : __DIR__"turen3",
  "southeast" : __DIR__"turen11",
  "east" : __DIR__"turen8",
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
