// Room: /d/pk/turen11.c
// This is a room made by roommaker. write by Fan. :)

inherit ROOM;

void create()
{
	set("short", "[1;31mÖïÈË³¡[2;37;0m");
	set("long", @LONG
ÕâÀïÒõÉ­¿Ö²À£¬µØÉÏµ½´¦ÊÇ²ĞÖ«ËéÊ¬£¬ÎŞ´¦²»ÊÇ°µºìÉ«µÄÑªµÎ¡£ÄãĞÄÖĞ
ìşìı²»°²£¬Íò·Ö¾¯Ìè£¬²»ÖªµÀ´ÓÄÄÀï¾Í»á´Ü³öÒ»¸öºÚÓ°¡£
LONG
);
	set("trds", "1");
	set("exits", ([ /* sizeof() == 3 */
  "northwest" : __DIR__"turen7",
  "north" : __DIR__"turen8",
  "east" : __DIR__"turen12",
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
