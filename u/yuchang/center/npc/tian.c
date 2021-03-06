#include <ansi.h>

inherit NPC;

int give_card();

void create()
{
        set_name(HIG "纪惜惜" NOR, ({"ji xixi", "ji", "xixi"}));
        set("gender", "女性" );
        set("long", HIM "她是中华会员服务中心的管理人员，听说她和浪翻云关系非同寻常。\n" NOR);
        set("title", HIY "中华会员服务中心管理员" NOR);
        set("nickname", HIR "天下第一才女" NOR); 
        set("age", 20);
        set("str", 99);
        set("con", 99);
        set("int", 99);
        set("dex", 99);
        set("per", 29);
        set("combat_exp", 650000);
        set("attitude", "peaceful");

        set("max_qi", 8400);
        set("max_jing", 8400);
        set("neili", 8000);
        set("max_neili", 8000);
        set("jiali", 800);

        set_skill("force", 300);
        set_skill("jiuyang-shengong", 300);   
        set_skill("finger", 300);
        set_skill("liumai-shenjian", 300);  
        set_skill("dodge", 300);
        set_skill("lingbo-weibu", 300);
        set_skill("unarmed", 300);   
        set_skill("zuoyou-hubo", 300); 
        set_skill("parry", 300);
        set_skill("qiankun-danuoyi", 300);
        set_skill("martial-cognize", 300);

        map_skill("finger", "liumai-shenjian");
        map_skill("force", "jiuyang-shengong");
        map_skill("dodge", "liubo-weibu");
        map_skill("unarmed", "jiuyang-shengong");
        map_skill("parry", "qiankun-danuoyi");
      
        prepare_skill("finger", "liumai-shenjian");  
        prepare_skill("unarmed", "jiuyang-shengong");

        set("inquiry", ([
                "中华会员卡" : (: give_card :),               
        ]));

        set("chat_chance_combat", 120);
                set("chat_msg_combat", ({
                (: perform_action, "sword.fei" :),
                (: perform_action, "force.ri" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set_temp("apply/damage", 200);
        set_temp("apply/unarmed_damage", 200);
        set_temp("apply/armor", 200);
        setup();

        carry_object(__DIR__"obj/qunzi")->wear();
}

int give_card()
{
        object me, hycard, ob;
        int rmb;

        me = this_player();
        rmb = me->query("rmb");

        // 已经成为会员, 卡片丢失后领取
        if (me->query("is_member"))
        {
              if (ob = present("huiyuan card", me)) 
              {
                     write(HIG "纪惜惜说道：“你已经领取了中华会员卡！请不要在这捣乱！”\n" NOR);
                     return 1;
              }
              // 判断是否在挂失
              if (! me->query("card_lost"))
              {
                     write(HIR "纪惜惜说道：“如果你卡片丢失，请先到中华会员服务中心大厅挂失！”\n" NOR);
                     return 1;
              }

              write(HIW "纪惜惜说道：“以后小心保管，这张中华会员卡就交还给你了！\n" NOR);
              hycard = new("/clone/gift/hycard");
              hycard->move(me);
              message_vision(HIC "$N" HIC "从纪惜惜处领取一张" HIY "中华会员卡" NOR "。\n" NOR,
                             me);
              me->delete("card_lost");
              return 1;            
        }

        // 非会员
        else
        {
             if (me->query("rmb") < 50)
             {
                      write(HIR "纪惜惜说道：“对不起，你注入的资金不足，无法申请会员。”\n" NOR);         
                      return 1;
             }

             write(NOR + CYN "纪惜惜说道：“好吧，从现在开始你就成为炎黄会员了！\n" NOR);
             write(NOR + CYN "纪惜惜说道：“这张会员卡就交给你了，以后请遵守会员条例！\n" NOR);
             message_vision(HIG + me->name() + HIG "从纪惜惜处领取一张" HIY "中华会员卡" NOR " 。\n" NOR,
                            me);
             hycard = new("/clone/gift/hycard");
             hycard->move(me);
             me->set("is_member", 1);
             CHANNEL_D->do_channel(this_object(), "ic", me->name() + "正式加入中华会员！");
             return 1;       
        }
}
void unconcious()
{
        die();
}


