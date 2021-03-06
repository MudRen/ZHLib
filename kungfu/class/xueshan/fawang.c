// /kungfu/class/xueshan/fawang.c  金轮法王
// by secret

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;

#include <ansi.h>
#include "xueshan.h"

mixed ask_me();

void create()
{
        set_name("金轮法王", ({ "jinlun fawang", "fawang", "jinlun" }));
        set("long",@LONG
他是雪山寺的护教法王。在雪山寺的地位仅次与掌门人鸠摩智。
身穿一件紫红袈裟，头戴僧帽。
LONG
        );
        set("title", HIY "法王" NOR);
        set("gender", "男性");
        set("age", 50);
        set("no_get", 0);
        set("attitude", "peaceful");
        set("shen_type", -1);

        set("str", 31);
        set("int", 32);
        set("con", 31);
        set("dex", 29);

        set("max_qi", 5200);
        set("max_jing", 5200);
        set("neili", 7500);
        set("max_neili", 7500);
        set("jiali", 100);
        set("combat_exp", 2400000);

        set_skill("force", 260);
        set_skill("longxiang", 260);
        set_skill("mizong-neigong", 260);
        set_skill("dodge", 210);
        set_skill("shenkong-xing", 210);
        set_skill("cuff", 240);
        set_skill("yujiamu-quan", 240);
        set_skill("hand", 250);
        set_skill("dashou-yin", 250);
        set_skill("parry", 250);
        set_skill("staff", 220);
        set_skill("xiangmo-chu", 220);
        set_skill("necromancy", 250);
        set_skill("lamaism", 210);
        set_skill("literate", 200);
        set_skill("hammer", 270);
        set_skill("riyue-lun", 270);

        map_skill("force", "longxiang");
        map_skill("dodge", "shenkong-xing");
        map_skill("cuff", "yujiamu-quan");
        map_skill("hand", "dashou-yin");
        map_skill("parry", "riyue-lun");
        map_skill("sword", "xiangmo-chu");
        map_skill("hammer", "riyue-lun");

        prepare_skill("hand", "dashou-yin");
        prepare_skill("cuff", "yujiamu-quan");

        create_family("雪山寺", 2, "护教法王");
        set("class", "bonze");

        set("inquiry", ([
                "绝招" : (: ask_me :),
                "绝技" : (: ask_me :),
                "破立" : (: ask_me :),
        ]));

        set_temp("apply/damage", 100);
        set_temp("apply/armor", 100);
        set_temp("apply/attack", 30);
        set_temp("apply/dodge", 25);
        set_temp("apply/parry", 25);

        setup();

        carry_object("/clone/weapon/falun")->set_amount(4);
          carry_object("/clone/weapon/falun")->wield();
              carry_object("/d/xueshan/obj/p-jiasha")->wear();
        carry_object("/d/xueshan/obj/sengmao")->wear();
        carry_object("/d/xueshan/obj/xuelian");
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if ((string)ob->query("gender") != "男性")
        {
                command("say 修习密宗内功需要纯阳之体。");
                command("say 这位" + RANK_D->query_respect(ob) +
                        "还是请回吧！");
                return;
        }

        if ((string)ob->query("class") != "bonze")
        {
                command("say 我佛门的清规戒律甚多。");
                command("say 这位" + RANK_D->query_respect(ob) +
                        "还是请回吧！");
                return;
        }

       if ((string)ob->query("family/family_name") != "雪山寺"
                && ob->query("family/family_name") != "血刀门")
        {
                command("say 这位" + RANK_D->query_respect(ob) +
                        "既非我密宗弟子，还是请回吧！");
                return;
        }
         if ((int)ob->query("jlfw") < 1){
                command("say " + RANK_D->query_respect(ob) +
                        "先去把我徒弟达尔巴打败，再来拜我吧。");
        return;
        }

       if ((int)ob->query_skill("lamaism", 1) < 100)
        {
                command("say 入我雪山寺，修习密宗心法是首要的。");
                command("say 这位" + RANK_D->query_respect(ob) +
                        "是否还应该多多钻研本门的心法？");
                return;
        }

        command("smile");
        command("nod");
        command("say 你就随我学习佛法吧！");
        command("recruit " + ob->query("id"));

        ob->set("title", HIY "活佛" NOR);
}

mixed ask_me()
{
        object me;

        me = this_player();
        if (me->query("can_perform/riyue-lun/poli"))
                return "你又来干什么？好好修行去！";

        if (me->query("family/family_name") != query("family/family_name"))
                return "你先入我们雪山寺再说";

        if (me->query_skill("riyue-lun", 1) < 120)
                return "你的日月轮法修为还不行，好好的给我练！";

        message_vision(HIY "$n" HIY "在$N" HIY "耳边嘀嘀咕咕"
                       "的说了一些口诀！\n" NOR,
                       me, this_object());
        command("say 去吧！");
        tell_object(me, HIG "你通晓了破立的奥妙。\n" NOR);
        if (me->can_improve_skill("hammer"))
                me->improve_skill("hammer", 90000);
        me->set("can_perform/riyue-lun/poli", 1);
        return 1;
}

