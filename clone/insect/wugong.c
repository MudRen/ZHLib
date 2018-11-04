// wugong.c òÚò¼

#include <ansi.h>

inherit POISON_INSECT;

void create()
{
	set_name("òÚò¼", ({ "wu gong" }) );
        set_weight(100);
	set("race", "À¥³æ");
       set("subrace", "ÅÀ³æ");
	set("age", 2);
	set("long", "Ò»Ö»òÚò¼¡£\n");
	set("attitude", "peaceful");
	set("str", 20);
	set("con", 20);
        set("unit", "Ö»");

        set("insect_poison", ([
                "level"  : 35,
                "maximum": 20,
        ]));

	set("combat_exp", 100);

	setup();
}
