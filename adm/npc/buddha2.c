//佛祖2(转世npc/开启前世记忆)

#include <ansi.h>
inherit  NPC;
int ask_recover();

void create()
{
        seteuid(getuid());       
        set_name(HIY "释迦牟尼" NOR, ({ "buddha", "fo zu", 
                "fo", "shijia muni" }));
        set("long", @LONG
佛祖庄严宝像，让人不敢正视。
LONG);
        set("nickname", HIW "三界法王" NOR);
        set("title", HIC "佛祖" NOR);
        set("gender", "男性" );
        set("age", 500);
        set("attitude", "friendly");
        set("max_jing", 99999);
        set("max_qi", 99999);
        set("max_jingli", 99999);
        set("jingli", 99999);
        set("max_neili", 99999);
        set("neili", 99999);
        set("jiali", 9999);
        set("str", 99);
        set("int", 99);
        set("con", 99);
        set("dex", 99);
        set("combat_exp", 99999999);

        set("inquiry", ([ 
            "前世" : (: ask_recover :), 
        ])); 

        set_skill("dodge", 999);
        set_skill("unarmed", 999);
        set_skill("force", 999);
        set_skill("parry", 999);
        set_skill("sword", 999);      
        set_skill("medical", 999);       
        set_skill("literate", 999);
        set_skill("lamaism", 999);
        set_skill("buddhism", 999);  
        set_skill("shaolin-yishu", 999); 
        set_skill("idle-force", 999);
        set_skill("huntian-baojian", 999);
        set_skill("lunhui-jian", 999);
      
        map_skill("force", "huntian-baojian");       
        map_skill("parry", "lunhui-jian");    
        map_skill("sword", "lunhui-jian");     
        map_skill("medical", "shaolin-yishu");   

        set("chat_chance_combat", 200);
        set("chat_msg_combat", ({
                (: perform_action, "sword.hui" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
                (: exert_function, "heal" :),
                (: exert_function, "dispel" :),
                (: exert_function, "regenerate" :),
        }));

        setup();
        carry_object("d/city/obj/jiasha")->wear();
        carry_object("/d/city/obj/changjian")->wield(); 
}





void init()
{
     add_action("do_recall", "recall");

}


int ask_recover()
{    
    object me = this_player();

    command("look " + me->query("id"));
    command("say 你与我前世有缘吗?");    
    command("say 你可记得前世你姓甚名谁，我给你的揭语又是什么？");
    command("say 若你能答得上来我便给你开启前生全部记忆。");

    tell_object(me, HIW"佛祖在你耳边说道，"
                    "若你想起来了就输入recall <id> <揭语> \n"NOR);   
    return 1;
}

int do_recall(string arg)
{
    int i, have;
    string id, pass;
    mapping special;
    object fo, me = this_player();
    have = 0;	

    if ( me->query("reborn") )
    {
       command("say 你的阿赖耶识不是已经打开了吗？");
       return 1;
    }


    fo  = find_object(__DIR__"buddha");  
    if ( ! fo ) fo = load_object(__DIR__"buddha");  

    if ( ! arg || sscanf(arg, "%s %s", id, pass) != 2 )
	 return notify_fail("你究竟记不记得自己前世是谁？\n");   

    for(i = 0; i < sizeof(fo->query("data")); i++)    
       if (keys(fo->query("data"))[i] == id ) have = 1;

    if ( have == 0 ) 
    {
       command("say 我怎么不记得前世跟你有缘呢？");
       return 1;
    }

    if ( fo->query("data/" + id + "/reborn_time") 
           > me->query("birthday") ) 
    {
       command("say 此人转世之时你已在世上，"
               "你又怎么可能会是他今生投胎之躯？");
       return 1;
    } 

    if ( fo->query("data/" + id + "/pass") != pass ) 
    {        
       command("say 这句哪里是我给你的揭语！");
       return 1;
    }


    command("say 看来你果然是前世与我有缘之人，待我将你前世记忆打开！");

    message_vision(HIY"\n佛祖说着便朝着$N轻轻一挥手。\n\n"NOR
                   HIR"$N突然感到头痛欲裂......\n\n"NOR, me);

    me->set("str", fo->query("data/" + id + "/str"));
    me->set("int", fo->query("data/" + id + "/int"));
    me->set("con", fo->query("data/" + id + "/con"));
    me->set("dex", fo->query("data/" + id + "/dex"));
   
    if (fo->query("data/" + id + "/sun"))
        me->set("gift/sun",1);
    if (fo->query("data/" + id + "/water"))
        me->set("gift/water",1);
    if (fo->query("data/" + id + "/feng"))
        me->set("gift/feng",1);
    if (fo->query("data/" + id + "/light"))
        me->set("gift/light",1);

    special = fo->query("data/" + id + "/special_skill");
 
    me->delete("special_skill");

    for( i = 0; i < sizeof(special); i++)
       me->set("special_skill/" + values(special)[i], 1); 
     
    me->set("reborn", 1);
    me->set("gift/kaizhan",1);
    me->set("gift/bobo/rmb", 0);
    me->set("gift/jindan",2);

    log_file("static/reborn", sprintf("%s(%s) reborn at %s.\n",
             me->name(1), me->query("id"), ctime(time())));  

    message("vision", HIG"【天界传闻】据说有人已得佛祖恩典，"
                      "开启了阿赖耶识。\n"NOR, users());
    me->unconcious();

    fo->delete("data/" + id);
    fo->save();   
    return 1;
}



