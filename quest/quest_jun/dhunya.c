#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIB"断魂崖"NOR);
        set("long", @LONG
这里就是天险断魂崖了，是扼守南北的交通必经之路，历来为兵家必
争之地，由山顶币制而下，只有一条狭窄的羊肠小道，两面则是万丈深渊，
看来断肠二字，名不虚传。
LONG
);

        set("no_magic", "1");
        set("exits", ([ /* sizeof() == 5 */
              "east"  :   __DIR__"shanlu3",
              "south" :   __DIR__"shanlu2",
        ]));

        set("objects", ([

        ]));

        setup();
        replace_program(ROOM);
}

