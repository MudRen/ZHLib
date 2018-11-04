#include <ansi.h>
inherit BULLETIN_BOARD;

void create()
{
        set_name( HIG" Ëã»î²Ý  "+HIR"¹àË®°æ"NOR, ({ "board" }) );
        set("location", "/u/kan/workroom");
        set("board_id", "shc_b");
        set("long", HIR"·î Ö¼ ¹à Ë® £¬Î¥ Õß ´¦ Õ¶ £¡\n"NOR );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}
