inherit NPC;
inherit F_MASTER;
inherit F_GUARDER;

#include <ansi.h>

void kicking(object ob);

void create()
{
        set_name("白世镜", ({"bai shijing", "bai", "shijing"}));
        set("title", "丐帮九袋长老");
        set("nickname", "执法长老");
        set("gender", "男性");
        set("age", 55);
        set("long", 
                "白世镜是丐帮的执法长老，在武林中享名已久。\n");
        set("attitude", "peaceful");
        set("class", "beggar");
        set("no_get", "1");
        set("rank",9);
        
        set("str", 28);
        set("int", 24);
        set("con", 24);
        set("dex", 25);

        set("qi", 3000);
        set("max_qi", 3000);
        set("jing", 1500);
        set("max_jing", 1500);
        set("neili", 4800);
        set("max_neili", 4800);
        set("jiali", 100);
        
        set("combat_exp", 1200000);
        
        set_skill("force", 195);
        set_skill("jiaohua-neigong", 195);
        set_skill("hand", 180);
        set_skill("chansi-shou", 180);
        set_skill("strike", 170);
        set_skill("xiaoyaoyou", 170);
        set_skill("dodge", 170);
        set_skill("feiyan-zoubi", 170);
        set_skill("parry", 190);
        set_skill("staff", 170);
        set_skill("jiaohua-bangfa", 170);
        set_skill("begging", 80);
        set_skill("checking", 150);
        set_skill("training", 120);
        
        map_skill("force", "jiaohua-neigong");
        map_skill("hand", "chansi-shou");
        map_skill("strike", "xiaoyaoyou");
        map_skill("staff", "jiaohua-bangfa");
        map_skill("dodge", "feiyan-zoubi");

        prepare_skill("hand", "chansi-shou");

        create_family("丐帮", 18, "九袋长老");
        setup();
        
        carry_object("/d/gaibang/obj/budai")->set_amount(8);
        carry_object("/d/gaibang/obj/budai")->wear();
}

void attempt_apprentice(object ob)
{
        if ((int)ob->query_str() < 26) {
                command("say 我们丐帮的武艺一向以刚猛为主，" + 
                RANK_D->query_respect(ob) + "臂力太弱，似乎不宜学丐帮的功夫？");
                return;
        }

        if( ob->query("family/family_name") != "丐帮" )
        {
                if( ob->query("rank") > 1 ) {
                        command("say 哼！本帮以忠义为先，可容不下你这种无信无义的家伙！\n");
                        return;
                }

                command("say 好吧，希望" + RANK_D->query_respect(ob) +
                "能好好学习本门武功，将来在江湖中闯出一番作为。");
                ob->set("rank", 1); 
                command("recruit " + ob->query("id"));
                ob->set("title", "丐帮一袋弟子");
        } 
        else
        {
                ob->set_temp("title", ob->query("title"));
                command("recruit " + ob->query("id"));
                ob->set("title", ob->query_temp("title"));
                ob->delete_temp("title");
        }
}
