// hong.c 洪安通

#include <ansi.h>
#include "shenlong.h"

inherit NPC;
inherit F_UNIQUE;
inherit F_MASTER;
inherit F_COAGENT;
inherit F_QUESTER;

mixed ask_me();
mixed ask_yx();

void create()
{
        set_name("洪安通", ({ "hong antong", "hong" }));
        set("title",  HIY "神龙教" NOR "教主" );
        set("nickname", HIR "永享仙福" NOR);
        set("long", "他就是武功盖世、令江湖人等谈之色变的神龙教教主洪安通。\n");
        set("gender", "男性");
        set("age", 50);
        set("attitude", "friendly");

        set("str", 32);
        set("int", 35);
        set("con", 31);
        set("dex", 32);

        set("max_qi", 6000);
        set("max_jing", 3000);
        set("neili", 6800);
        set("max_neili", 6800);
        set("jiali", 100);
        set("combat_exp", 2200000);
        set("shen_type", -1);

        set_skill("finger",280);
        set_skill("force", 250);
        set_skill("shenlong-xinfa", 250);
        set_skill("busi-shenlong",260);
        set_skill("dodge", 230);
        set_skill("yixingbu", 230);
        set_skill("hand", 240);
        set_skill("shenlong-bashi", 240);
        set_skill("strike", 240);
        set_skill("shenlong-jian",250);
        set_skill("yingxiong-sanzhao",260);
        set_skill("huagu-mianzhang", 240);
        set_skill("parry", 250);
        set_skill("staff", 250);
        set_skill("sword", 250);
        set_skill("shedao-qigong", 250);
        set_skill("literate", 220);
        set_skill("medical", 270);
        set_skill("shenlong-mixin", 270);

        map_skill("force", "shenlong-xinfa");
        map_skill("dodge", "yixingbu");
        map_skill("hand", "shenlong-bashi");
        map_skill("strike", "huagu-mianzhang");
        map_skill("parry", "shedao-qigong");
        map_skill("staff", "shedao-qigong");
        map_skill("sword", "shenlong-jian");
        map_skill("finger", "yingxiong-sanzhao");

        prepare_skill("strike", "huagu-mianzhang");
        prepare_skill("hand", "shenlong-bashi");

        create_family("神龙教", 1, "教主");

        set("inquiry", ([
                "神龙教" :  "一般人是入不了我神龙教的(join shenlongjiao)。\n",
                "入教"   :  "一般人是入不了我神龙教的(join shenlongjiao)。\n",
                "洪安通" :  "你不想活了是不是?\n",
                "教主"   :  "我就是神龙教教主。\n",
                "英雄三招"   : (: ask_yx :),
                "绝技"   : (: ask_me :),
                "飞仙术" : (: ask_me :),
        ]));
        set("chat_chance_combat", 50);  
        set("chat_msg_combat", ({
                (: command("chat 凭你这" + RANK_D->query_rude(this_player()) +
                           "，也敢在太岁爷头上动土？") :),
                (: perform_action, "staff.chang" :),
                (: perform_action, "staff.chang" :),
                (: perform_action, "staff.chang" :),
                (: perform_action, "staff.chen" :),
                (: perform_action, "staff.chen" :),
                (: perform_action, "staff.chen" :),
                (: perform_action, "staff.fei" :),
                (: perform_action, "staff.fei" :),
                (: perform_action, "staff.fei" :),
                (: exert_function, "recover" :),
                (: exert_function, "recover" :),
        }));
        setup();
        carry_object("/clone/weapon/gangzhang")->wield();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver", 35);
}

int do_flatter(string arg)
{
        if (! this_player()->query_temp("pending/flatter"))
        {
                command("say 你想嚷嚷什么，吵得我心烦意乱的。");
                return 0;
        }

        if (! arg ) return notify_fail("你说我什么？\n");

        this_player()->set_temp("pending/flatter", 0);
        message_vision(CYN "$N大声说道：" + arg + "\n" NOR,
                       this_player());

        if (strsrch(arg, "万年不老") >=0 && (strsrch(arg, "永享仙福") >=0 &&
            strsrch(arg, "寿与天齐") >=0 && strsrch(arg, "文武仁圣") >=0))
        {
                command("smile");
                command("say 这还差不多。\n");
                command("recruit " + this_player()->query("id"));
        } else
        {
                command("say 你如此不把我放在眼里，我又怎能容你？!");
                kill_ob(this_player());
        }
        return 1;
}

// 万年不老,永享仙福,寿与天齐,文武仁圣
void die()
{
        message_vision("\n$N奇道：“咦,居然有人能杀了我,....”"
                       "说完睁着两眼倒地死了。\n", this_object());
        ::die();
}

void init()
{
        object ob;

        ::init();

        if (interactive(ob = this_player()) && ! is_fighting())
        {
                remove_call_out("greeting");
                call_out("greeting", 4, ob);
        }
        add_action("do_flatter", "flatter");
        add_action("do_join", "join");
}

void greeting(object ob)
{
        object obj;
        if (! objectp(ob)) return;
        if (interactive(ob) && objectp(obj = present("used gao", ob)))
        {
                set("combat_exp", 1000000);
                set("qi", 500);
                set("jing", 500);
        }
}

mixed ask_me()
{
        object me;

        me = this_player();
        if (me->query("can_perform/shedao-qigong/fei"))
                return "自己多练练，少在我面前罗嗦！";

        if (me->query("family/family_name") != query("family/family_name"))
                return "你是哪儿来的？找死啊？";

        if (me->query("shen") > -40000)
                return "你的手段还不够毒，我可不能传给你绝招！";

        if (me->query_skill("shedao-qigong", 1) < 100)
                return "你的蛇岛奇功学好了么？还好意思来问我？";

        message_vision(HIM "$n" HIM "点头道：“看清楚了！”说罢以"
                       "掌为剑“唰唰唰”接连劈出数剑，宛若数把剑在"
                       "手，真是神乎其神！\n" NOR,
                       me, this_object());
        command("say 运用很简单，不过你懂了没有？");
        tell_object(me, HIG "你学会了飞仙术。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 90000);
        me->set("can_perform/shedao-qigong/fei", 1);
        return 1;
}

mixed ask_yx()
{
        object me;

        me = this_player();
        if (me->query("can_perform/yingxiong-sanzhao/cansanzhao"))
                return "自己多练练，少在我面前罗嗦！";

        if (me->query("family/family_name") != query("family/family_name"))
                return "你是哪儿来的？找死啊？";

        if (me->query("shen") > -40000)
                return "你的手段还不够毒，我可不能传给你绝招！";

        if (me->query_skill("yingxiong-sanzhao", 1) < 100)
                return "你的英雄三招学好了么？还好意思来问我？";

        message_vision(HIM "$n" HIM "点头道：“看清楚了！我现在教你三招克敌之术。”\n"
                          "------狄龙降龙\n"
                          "------子胥举鼎\n"
                          "------鲁达拔柳\n"
                       "说罢便一边比画，一边和你拆解！\n" NOR,
                       me, this_object());
        command("say 运用很简单，不过你懂了没有？");
        tell_object(me, HIG "你学会英雄三招。\n" NOR);
        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 90000);
        me->set("can_perform/yingxiong-sanzhao/cansanzhao", 1);
        return 1;
}


void attempt_apprentice(object ob)
{
        if (ob->query("party/party_name") != "神龙教")
        {
                command("say 你不是本教教众, 想来找死啊!");
                return;
        }

        if ((int)ob->query("shen") > -1000)
        {
                command("say 林冲拜梁山还要投名状，你不杀两"
                        "个白道人物怎么表示真心？！");
                return;
        }

        if (ob->query_temp("pending/flatter"))
        {
                command("say 你如此不把我放在眼里，我又怎能容你？");
                kill_ob(ob);
                return 0;
        } else
        {
                command("say 我洪安通比起古往今来的圣人怎么样啊？");
                message_vision("洪安通微闭双眼，手捻长须，一副"
                               "等人拍马(flatter)的样子。\n",
                               this_player());
                ob->set_temp("pending/flatter", 1);
                return 0;
        }
}


