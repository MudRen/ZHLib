#include <ansi.h>
#include <getconfig.h>
inherit NPC;
string ask_me();

void create()
{
        set_name(HIR+LOCAL_MUD_NAME()+NOR, ({ "shizhe" }) );
        set("nickname", HIR"挑战极限"NOR);
        set("gender", "男性" );
        set("age", 18);
        set("long", YEL"这位是〖"+LOCAL_MUD_NAME()+"〗的使者，向他打听“礼物”，他会带给您想不到的惊喜。\n"NOR);
        set("shen_type", 1);
        set("combat_exp", 1000000);
        set("str", 30);
        set("dex", 30);
        set("con", 30);
        set("int", 30);
        set("per", 30);
        set("attitude", "friendly");
        set("max_qi", 100000);
        set("neili", 100000);
        set("max_neili", 100000);
        set("score", 100000);

        set("inquiry", ([
                         "礼物" : (: ask_me :)
        ]));
        setup();
}

void init()
{
        object ob;
        ob = this_player();     
        ::init();
        if( interactive(ob) && !is_fighting() )
               {
                        remove_call_out("greeting");
                        call_out("greeting", 1, ob);
                }
}

void greeting(object ob)
{
   if( !ob || environment(ob) != environment() ) return;
   command("whisper " + ob->query("id") + " "HIW"欢迎光临"+HIR+"(ask shizhe about 礼物)"+NOR+HIW+"， 小的助您行走江湖．"NOR);
   command("es " + HIR"『"+HIY+LOCAL_MUD_NAME()+HIR+"』"NOR+WHT"欢迎您的光临,"+HIR"ip:"NOR+WHT+RELEASE_SERVER()+NOR+HIR"port:"NOR+WHT+LOCAL_PORT()+NOR);
}

string ask_me()
{
        object me = this_player();
        mapping fam; 
        
         if ((int) me->query("comeworld"))
                return "呵呵～这就是您的不是了！小的已经对您施过法力了！";
         else{
                me->set("comeworld", 1);
                me->add("potential", 1000);
                me->add("food", 10000);
                me->add("water", 10000);
                return "礼物清单: 潜能: 1000,食物和饮水各: 10000。" ;
             }
}

