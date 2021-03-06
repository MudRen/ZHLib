// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("中华英雄", ({ "ying xiong", "ying", "xiong", "hero" }));
        set("long", @LONG
他就是传说中的中华英雄，你可以向他打听关于
建帮的消息。
LONG);
        set("nickname", HIW "天下无双" NOR);
        set("title", HIC "武林泰斗" NOR);
        set("gender", "男性" );
        set("age", 68);
        set("attitude", "friendly");
        set("max_jing", 50000);
        set("max_qi", 50000);
        set("max_jingli", 50000);
        set("jingli", 50000);
        set("max_neili", 50000);
        set("neili", 50000);
        set("jiali", 350);
        set("str", 50);
        set("int", 50);
        set("con", 50);
        set("dex", 50);
        set("combat_exp", 12000000);

        set("inquiry", ([
                "帮派"  :"要创建帮会请先组队，人数不能少于五个，然后 team bunch <帮会名> 就可以了。\n",
                "帮会"  :"要创建帮会请先组队，人数不能少于五个，然后 team bunch <帮会名> 就可以了。\n",
                "建帮"  :"要创建帮会请先组队，人数不能少于五个，然后 team bunch <帮会名> 就可以了。\n",
        ]) );

        setup();
        carry_object("d/city/obj/cloth")->wear();
/*
        if (! clonep(this_object()))
        {
                move("/d/city/wumiao");
                message_vision(CYN "\n$N" CYN "笑嘻嘻道：各位大侠要建帮吗？\n"
                               NOR, this_object());
                set("startroom", "/d/city/wumiao");
        }
*/
}
