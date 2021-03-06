// yan.c 俞岱岩

#include <ansi.h>
#include "wudang.h"

inherit NPC;
inherit F_MASTER;

string ask_lianzhen();
int accept_object(object who, object ob); 

void create()
{
        set_name("俞岱岩", ({ "yu daiyan", "yu" }));  
        set("nickname","武当三侠");
        set("long", 
                "他就是张三丰的三弟子俞岱岩。\n"
                "身穿一件干干净净的灰色道袍。\n"
                "他已年过四十，身材瘦长。恬淡冲和，沉默寡言。\n");
        set("gender", "男性");
        set("age",43);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 29);
        set("int", 28);
        set("con", 31);
        set("dex", 25);
        
        set("max_qi", 4400);
        set("max_jing", 2000);
        set("neili", 5200);
        set("max_neili", 5200);
        set("jiali", 100);
        set("combat_exp", 1450000);
        set("score", 45000);

        set_skill("force", 190);
        set_skill("wudang-xinfa", 190);
        set_skill("taiji-shengong", 190);
        set_skill("dodge", 165);
        set_skill("tiyunzong", 165);
        set_skill("cuff", 170);
        set_skill("taiji-quan", 170);
        set_skill("strike", 170);
        set_skill("wudang-zhang", 170);
        set_skill("hand", 170);
        set_skill("paiyun-shou", 170);
        set_skill("parry", 175);
        set_skill("sword", 180);
        set_skill("wudang-jian", 180);
        set_skill("taiji-jian", 180);
        set_skill("taoism", 160);
        set_skill("array", 180);
        set_skill("zhenwu-array", 180);
        set_skill("literate", 100);

        set("no_teach", ([
                "taiji-shengong" : "要想学习太极神功请向张真人请教。",
                "taiji-jian"     : "太极剑必须张真人亲传。",
                "taiji-quan"     : "太极拳必须张真人亲传。",
        ]));

        set("inquiry", ([ 
                "真武剑阵" :  "真武剑阵乃我武当派降妖除魔之法宝。武当弟子务须勤加操演。", 
                "操演"     : (: ask_lianzhen :), 
        ])); 

        map_skill("force", "taiji-shengong");
        map_skill("dodge", "tiyunzong");
        map_skill("cuff", "taiji-quan");
        map_skill("array", "zhenwu-array");
        map_skill("parry", "taiji-quan");
        map_skill("sword", "taiji-jian");
        map_skill("strike", "wudang-zhang");

        prepare_skill("cuff", "taiji-quan");
        prepare_skill("strike", "wudang-zhang");

        create_family("武当派", 2, "弟子");
        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/wudang/obj/greyrobe")->wear();
}

void init()
{
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting",2 , ob);
        }
}

void greeting(object ob)
{
   int i;
        if (!environment(this_object()) || base_name(environment(this_object())) != "/d/wudang/gaotai")
                return;
   if (((int)ob->query_skill("wudang-xinfa", 1) == 0))
   {
      message_vision(CYN"十三弟子对$N齐声喝道：你这个邪魔外道，敢来真武剑阵？\n\n"NOR,ob);
      ob->set("qi",30);
      if ((int)ob->query("combat_exp") <2000) ob->set("combat_exp",1);
         else ob->add("combat_exp",-1000);
      message_vision(CYN"真武剑阵顿时启动，高台上剑气纵横，把$N围在中央。\n"NOR,ob);
      message_vision(CYN"十三口长剑齐出，在$N身上划出了十三道口子，鲜血淋漓。\n"NOR,ob);
      say(CYN"\n\n俞岱岩脸现怒容：“邪魔外道，也敢闯真武剑阵！”\n");
      message_vision("俞岱岩居高临下，起手一掌把$N劈落高台。\n\n\n"NOR,ob);
      ob->move("/d/wudang/nanyangong");
      CHANNEL_D->do_channel(this_object(),"chat",sprintf("%s 私闯真武剑阵，念其成长不易，暂免一死！",ob->name(1)));
   }
}

void attempt_apprentice(object me)
{
        if (! permit_recruit(me))
                return;

        if ((int)me->query_skill("wudang-xinfa", 1) < 30) {
                command("say 我武当派乃内家武功，最重视内功心法。");
                command("say " + RANK_D->query_respect(me) +
                        "是否还应该在太极神功上多下点功夫？");
                return;
        }

        if ((int)me->query("shen") < 10000) {
                command("say 我武当乃是堂堂名门正派，对弟子要求极严。");
                command("say 在德行方面，" + RANK_D->query_respect(me) +
                        "是否还做得不够？");
                return;
        }

        if ((int)me->query_skill("wudang-xinfa", 1) < 70)
        {
                command("say 我武当派最注重内功心法" + RANK_D->query_respect(me)+
                        "是否应该在武当心法上多下点功夫啊?");
                return;
        }

        if ((int)me->query_skill("taoism", 1) < 70)
        {
                command("say 习武是为了强身健体，一味的练武是不可取的！");
                command("say 我看你还需要在修身养性方面多锻炼锻炼，以提"
                        "高你的道德心法。");
                return;
        }

        command("say 好吧，我就收下你了。");
        command("recruit " + me->query("id"));
}

string ask_lianzhen() 
{ 
     string msg; 
     object me = this_player(); 
     if (me->query_skill("zhenwu-array", 1) < 180 ) 
     {
        command(":) " + me->query("id"));
        msg = "你还是先好好跟我学学再练吧。";
        return msg; 
     }
     if (query_temp("count", 1) >= 8 )
     {
        msg = "现在剑阵人数已够，你等会再来练吧。";
        return msg; 
     }
     if (me->query_temp("lianzhen"))
     {
        msg = "真武剑阵只要勤加练习，威力无比。";
        return msg; 
     }
     me->set_temp("lianzhen", 1);
     add_temp("count", 1);
     msg = "很好，在这里好好跟师兄弟们操演(caoyan)剑阵吧。"; 
     return msg; 
}

int accept_fight(object ob) 
{
    command("say 我可没工夫陪你玩！\n"); 
    return notify_fail("看起来" + this_object()->name() + "并不想跟你较量。\n");  
}

int accept_hit(object ob) 
{
    command("say 你是不是想试试真武剑阵的厉害？\n"); 
    command("cold "+ob->query("id")); 
    return 0;
}

int accept_kill(object ob) 
{
    command("say 你想造反吗？\n"); 
    command("cold "+ob->query("id")); 
    return notify_fail("\n"); 
}

int accept_touxi(object ob) 
{ 
    tell_object(ob,"你刚想偷袭，突然发现" + this_object()->name() + "正看着你。\n"); 
    command("sigh "+ob->query("id")); 
    return 1; 
} 

int accept_ansuan(object ob) 
{ 
    return notify_fail("你刚想暗算，可是发现" + this_object()->name() + "非常小心谨慎，让你无从下手。\n");  
}  

