// by yuchang
#include <ansi.h>

inherit NPC;
void create()
{
        set_name("傲苍天", ({ "ao cangtian", "ao", "cangtian"}));
        set("title", HIY "傲剑山庄左圣" NOR);
        set("long",
"傲苍天长得并不帅气，团团的一张圆脸，皮肤稍微有点发黑，但是骨架很大，身上的威风很足，
一对眼睛极其有神，时雍容华贵，自有一副端严之致，令人肃然起敬，不敢逼视。\n");
        set("gender", "男性");
        set("age", 45);
        set("attitude", "peaceful");
        set("shen", -200000);
        set("per", 30);
        set("str", 35);
        set("int", 25);
        set("con", 25);
        set("dex", 30);

        set("max_qi", 20000);
        set("max_jing", 20000);
        set("max_neili", 50000);
        set("neili", 50000);
        set("jiali", 500);       
        set("combat_exp", 5000000);
     
        set_skill("dodge", 500);
        set_skill("unarmed", 500);
        set_skill("force", 500);
        set_skill("parry", 500);
        set_skill("sword", 500);
        set_skill("poison", 500);
        set_skill("medical", 500);
        set_skill("hand", 500);
        set_skill("strike", 500);
        set_skill("staff", 500);
        set_skill("finger", 500);
        set_skill("claw", 500);
        set_skill("blade", 500);
        set_skill("pixie-jian", 500);
        set_skill("literate", 500);
        set_skill("taoism", 500);
        set_skill("buddhism", 500);

        set_skill("jiuyang-shengong", 500);
        set_skill("lingbo-weibu", 500);
        set_skill("qiankun-danuoyi", 500);
        set_skill("xuanming-zhang", 500);
        set_skill("jiuyin-baiguzhao", 500);
        set_skill("dugu-jiujian", 500);
        set_skill("liumai-shenjian", 500);
        set_skill("qianzhu-wandushou", 500);
        set_skill("ranmu-daofa", 500);
        set_skill("dagou-bang", 500);
        set_skill("shaolin-yishu", 500);
        set_skill("wudu-qishu", 500);
        set_skill("throwing", 500);
        set_skill("mantian-xing", 500);
        set_skill("idle-force", 500);

        map_skill("unarmed", "pixie-jian");
        map_skill("force", "jiuyang-shengong");
        map_skill("dodge", "lingbo-weibu");
        map_skill("parry", "qiankun-danuoyi");
        map_skill("hand", "qianzhu-wandushou");
        map_skill("strike", "xuanming-zhang");
        map_skill("claw", "jiuyin-baiguzhao");
        map_skill("finger", "six-finger");
        map_skill("sword", "dugu-jiujian");

        map_skill("blade", "ranmu-daofa");
        map_skill("staff", "dagou-bang");
        map_skill("throwing", "mantian-xing");
        map_skill("poison", "wudu-qishu");
        map_skill("medical", "shaolin-yishu");

        prepare_skill("finger", "liumai-shenjian");

        set("chat_chance_combat", 200);
        set("chat_msg_combat", ({
                (: perform_action, "sword.po" :),
                (: perform_action, "blade.zhenyan" :),
                (: perform_action, "blade.huo" :),
                (: perform_action, "staff.wugou" :),
                (: perform_action, "staff.chan" :),
                (: perform_action, "staff.ban" :),
                (: perform_action, "unarmed.cimu" :),
                (: perform_action, "parry.nuoyi" :),
                (: perform_action, "dodge.lingbo" :),
                (: perform_action, "throwing.shan" :),
                (: perform_action, "hand.zhugu" :),
                (: perform_action, "strike.wuji" :),
                (: perform_action, "finger.six" :),
                (: perform_action, "finger.zhongheng" :),
                (: perform_action, "claw.zhua" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
                (: exert_function, "heal" :),
                (: exert_function, "dispel" :),
                (: exert_function, "regenerate" :),
        }));        

        setup();
        carry_object(__DIR__"obj/changjian")->wield();
        carry_object(__DIR__"obj/female2-cloth")->wear();
}
void init()
{       
        object me;
        string id;
        me = this_player();      

        command("chat 大胆，谁人胆敢擅闯本庄禁地!");
        command("say 哼，又是一个不要命的!");  
        kill_ob(me);
        this_object()->set("now_killing", me);
      
}

void unconcious() 
{ 
        object ob, killer;
        ob = this_object();
        killer = ob->query("now_killing");
        
        command("chat 老夫纵横江湖数十载，想不到竟败在你手下!");
        command("chat 罢了罢了，但是要拿到绝世好剑还没这么容易！");
        tell_room(environment(ob), "\n傲苍天一晃，变为一缕轻烟消失了。\n\n"); 
        killer->set_temp("reborn_start/ao1",1);  
        destruct(ob);  
} 


