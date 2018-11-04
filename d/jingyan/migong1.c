#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", WHT"惊雁宫大门"NOR);
	set("long", @LONG
突然你眼前一亮，一座巨大的宫殿呈现在你面前，
这正是传说中的惊雁宫,惊雁宫占地极广，殿阁亭
台，气象森然，全宫依山而建，背靠惊雁峰，亦是
行宫的名之来由，惊雁宫除了由千里峰攀山而下，
唯一途径是一条直通正门的大石桥，石桥宽广，可
容四马并驰，鬼斧神工，气势磅礴，使人生起一夫
当关万夫莫敌的感叹。
LONG
        );

        set("outdoors", "qianhuigu");
              set("no_stab", 1); 
        set("exits", ([ /* sizeof() == 3 */
                "north" : __DIR__"migong2",
        ]));

        setup();
        replace_program(ROOM);
}

