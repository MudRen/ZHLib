// yue-buqun.c lasted updated by cocacola on 2.19 for adding chushi
// 岳不群

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;
inherit F_QUESTER;

#include <ansi.h>
#include "qizong.h"

int  do_xunshan();
void check_weapon();
void unwield_weapon();
string ask_zixia();

// 重载个人鉴定函数，保证做quest的时候是正义的quest
int is_bad() { return 0; }
int is_good() { return 1; }

void create()
{
        set_name("岳不群", ({ "yue buqun", "yue" }) );
        set("title", "华山派掌门");
        set("nickname", HIC "君子剑" NOR);
        set("gender", "男性");
        set("class", "swordsman");
        set("age", 55);
        set("long", "岳不群自幼执掌华山派，乃当今武林中一等一的高手。\n");
        set("attitude", "peaceful");
        set("str", 26);
        set("con", 30);
        set("dex", 30);
        set("int", 28);

        set("max_qi", 5200);
        set("max_jing", 2600);
        set("neili", 6000);
        set("max_neili", 6000);
        set("jiali", 80);

        set("combat_exp", 1600000);
        set("xunshan", 1);
        set("apprentice_available", 3);

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
		(: perform_action, "sword.cimu" :),
		(: perform_action, "sword.pi" :),
                (: check_weapon :),
        }));
        set("inquiry", ([
                "巡山"     : (: do_xunshan :),
                "紫霞神功" : (: ask_zixia  :),
                "紫霞秘籍" : (: ask_zixia  :),
                "秘籍"     : (: ask_zixia  :),
        ]));

        set_skill("unarmed", 180);
        set_skill("strike", 180);
        set_skill("sword", 220);
        set_skill("force", 220); 
        set_skill("parry", 180);
        set_skill("hunyuan-zhang", 160);
        set_skill("dodge", 220);
        set_skill("literate", 200);
        set_skill("huashan-sword", 220);
        set_skill("huashan-xinfa", 170);
        set_skill("zixia-shengong", 220);
        set_skill("huashan-quanfa", 180);
        set_skill("feiyan-huixiang", 180);

        map_skill("sword", "huashan-sword");
        map_skill("parry", "huashan-sword");
        map_skill("force", "zixia-shengong");
        map_skill("unarmed", "huashan-quanfa");
        map_skill("dodge", "feiyan-huixiang");
        map_skill("strike", "hunyuan-zhang");

        set("no_teach", ([
                "zixia-shengong" : "等你基本功练好了，我"
                                   "给你紫霞秘籍你自己研读吧。",
                "pixie-jian"     : "哈哈！那是林家的家传武功，"
                                   "我怎么可能会呢？",
        ]));

        create_family("华山派", 13, "掌门");
        setup();

	set("book_count", 1);
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/clone/misc/pin");
}

void check_weapon()
{
        if (objectp(query_temp("weapon")))
                return;

        command("wield pin");
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
		(: perform_action, "sword.cimu" :),
		(: perform_action, "sword.pi" :),
        }));
        set("chat_chance", 120);
        set("chat_msg", ({
                (: unwield_weapon :),
        }));
}

void unwield_weapon()
{
        command("unwield pin");
        delete("chat_chance");
        delete("chat_msg");
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
		(: perform_action, "sword.cimu" :),
		(: perform_action, "sword.pi" :),
                (: check_weapon :),
        }));
}

void attempt_apprentice(object ob)
{
        if( query("apprentice_available") ) {
                if( find_call_out("do_recruit") != -1 )
                        command("say 慢著，一个一个来。");
                else
                        call_out("do_recruit", 2, ob);
        } else {
                command("say 老夫今天已经收了三个弟子，不想再收徒了。");
        }
}

void do_recruit(object ob)
{
        if( !permit_recruit(ob) )
                return;

        if( (int)ob->query_int() < 23 )
                command("say 我华山派以剑法为主，依我看" +
                        RANK_D->query_respect(ob)+"不适合于学剑法。");

        else {
                command("say 好，好，好，很好。");
                command("recruit " + ob->query("id") );
        }
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
        add("apprentice_availavble", -1);
}

void reset()
{
	set("book_count", 1);
        set("apprentice_available", 3);
}

int do_xunshan()
{
        object me = this_player();
      	string date;

    	date = NATURE_D->game_time();
	sscanf(date, "%s日%*s刻", date);

        if (me->query_temp("xunshan"))
        {
               if (!me->query_temp("xunshan/chaoyang"))
               {
                      	message_vision("$N对着$n说：你朝阳峰没去看看？"
                                       "这算巡的什么山？\n", this_object(), me);
                        return 1;
               }
               if (!me->query_temp("xunshan/lianhua"))
               {
                      	message_vision("$N对着$n说：你莲花峰没去看看？"
                                       "这算巡的什么山？\n", this_object(), me);
                      	return 1;
               }
               if (!me->query_temp("xunshan/yuntai"))
               {
                      	message_vision("$N对着$n说：你云台峰没去看看？这算"
                                       "巡的什么山？\n", this_object(), me);
                      	return 1;
               }
               if (!me->query_temp("xunshan/sheshen"))
               {
                      	message_vision("$N对着$n说：你怎么没去舍身崖？这算"
                                       "巡的什么山？\n", this_object(), me);
                      	return 1;
               }
               if (!me->query_temp("xunshan/siguo"))
               {
                      	message_vision("$N对着$n说：你到了思过崖去了？这算"
                                       "巡的什么山？\n", this_object(), me);
                      	return 1;
               }
               if (!me->query_temp("xunshan/yunu"))
               {
                      	message_vision("$N对着$n说：你到玉女峰后面华山小筑"
                                       "去看过了？这算巡的什么山？\n",
                                       this_object(), me);
                      	return 1;
               	}
               	message_vision("$N对着$n说：不错，辛苦了。你这就去"
                               "休息去吧。\n", this_object(), me);
               	me->delete_temp("xunshan");                      
               	me->add("combat_exp", 100 + random(100));
               	return 1;
        }
        else
        {
               if (query("xunshan") == date)
               {
                      	message_vision("$N对着$n说：今天已经有人巡山"
                                     "去了。你明天再来吧。\n", this_object(), me);
                      	return 1;
               }
               if( me->query("family/family_name") != "华山派")
               {
                      	message_vision("$N对着$n大喝一声：本派弟子才能"
                                     "巡山。你是哪来的奸细？\n", this_object(), me);
                      	return 1;
               }
               if( me->query("combat_exp") > 200000)
               {
                      	message_vision("$N对着$n呵呵一笑：你应该帮我做点别的"
                                     "事情了，巡山就交给新来的弟子吧！\n", this_object(), me);
                      	return 1;
               }
               else
               {
                      	set("xunshan", date);
                      	message_vision("$N对着$n说：本派弟子例当巡山。你，很好，很"
                                       "好！今天就去巡山吧。\n",
				       this_object(), me);
                      	me->set_temp("xunshan/start", 1);
                      	me->set_temp("xunshan/time", time());
                      	return 1;
               }
        }
}

string ask_zixia()
{
        mapping fam;
        object ob;
        object me;

        me = this_player();
        if( fam = me->query("family") )
        {
                if( fam["family_name"] == "华山剑宗" )
                        return "哈哈！你们剑宗居然也讲究起练气来了？";

                if( fam["family_name"] != "华山派" )
                        return RANK_D->query_respect(me) +
                               "与本派毫无瓜葛，何以问起本派的秘籍？";
        }

        if (me->query_skill("huashan-xinfa", 1) < 100)
                return "你的华山心法就学成这个样子还要什么紫霞秘籍？";

        if (me->query("max_neili", 1) < 800)
                return "你的内力也太差了，好好练练，不要先想什么紫霞神功！";

        if (query("book_count") < 1)
                return "你来晚了，本派秘籍已经被人取走了。";

        add("book_count", -1);
        ob = new("/clone/book/zixia_book");
        ob->move(me);
        return "好吧，这本「紫霞秘籍」你拿回去好好研读，苦练内功，发扬"
               "光大我们气宗一脉。";
}
