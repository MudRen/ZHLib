// patrol.c  配合长安府巡城任务的指令
#include <ansi.h>
 
inherit F_CLEAN_UP;

int main(object me)
{
        object ob;      

        if ( me->query("changanjob/kind") != "patrol" )        
        return notify_fail("你现在没有领取巡城的任务！\n");         

        if ( me->query("changanjob/ok") )        
        return notify_fail("你现在已经完成本次巡城任务了，快回去复命吧！\n");  
    
        if ( me->is_busy() || me->query("doing") )
        return notify_fail("你现在正忙着呢！\n");  
 
        if ( me->is_fighting() )
        return notify_fail("你现在正打架呢，怎么能巡城！\n"); 

        if (me->query("qi") < 30 )
        return notify_fail("你现在体力太差，不能巡城！\n"); 

        if (me->query("jing") < 30 )
        return notify_fail("你现在精神太差，不能巡城！\n"); 
     
        message_vision(HIC"$N东瞧瞧西望望，仔细留意有没有可疑的人。\n"NOR, me);        
        me->set_short_desc("正在巡城。");
        me->delete_temp("pending/patrol");  
              
        me->start_busy((:call_other, __FILE__, "patrol" :), 
                      (:call_other, __FILE__, "halt_patrol" :)); 
        return 1;
}

int patrol(object me)
{
      object env, *ob;
      int i, flag, have; 
      
      env = environment(me);
      flag = 0;
      have = 0;

      for( i=0; i < 5; i++ )
        {
	   if ( me->query("changanjob/place/" + (i+1)) == env->short() )
          flag = i + 1;
        } 

      if (me->add_temp("pending/patrol", 1) > 8 )
      {      
         message_vision(HIY"$N巡逻了半天，发现并无可疑之人。\n"NOR, me);          
        if ( flag != 0 )        
       {   ob = all_inventory(me);
            for(i=0; i<sizeof(ob); i++) 
              {   
                  if (ob[i] == me->query("changanjob/gonghan"))
                     {                                       
                         have = 1;  
                         break;
                     }  
               }      
            if ( have == 0 )   
                message_vision(HIR"$N刚想提笔记下此地治安良好，"
                           "却发现身上没带记录本次巡城的公函。\n"NOR, me);          
            else
            {
                message_vision(HIG"$N提笔在本次巡城的公函上记下此地治安良好。\n"NOR, me);
                for( i=0; i < 5; i++ )
                {
                   if ( me->query("changanjob/place/" + (i+1)) == env->short() )
                   {
	               me->set("changanjob/placeok/" + (i+1), 1);
                      me->query("changanjob/gonghan")->set("placeok/" + (i+1), 1);
                   }
                } 
     
            }
         }
          me->set_short_desc(0);
          me->delete_temp("pending/patrol"); 
          return 0;
       } 

        if (me->query("qi") < 20 ||
            me->query("jing") < 20)
        {
                tell_object(me, HIY "你实在太疲倦了，只好先休息准备一会儿再继续巡城。\n" NOR);
                message("vision", HIC + me->name() + HIC "一脸倦容，暂时停止巡城准备休息。\n"
                                  NOR, env, ({ me }));
                me->set_short_desc(0);
                me->delete_temp("pending/patrol"); 
                return 0;
        }
        me->receive_damage("qi", 5);
        me->receive_damage("jing", 5);

       if ( me->query("changanjob/kind") == "patrol" &&
            ! me->query("changanjob/catch") &&
            flag != 0 &&  
            ! me->query("changanjob/placeok/" + flag )  &&
            me->query_temp("pending/patrol") > 5 && 
            random(12) == 1 &&
            me->query("changanjob/catch_num") < 3 )
       {
          call_other(__FILE__, "set_liumang", me);       
          me->set_short_desc(0);
          me->delete_temp("pending/patrol"); 
          return 0;
        }
       return 1;
}

int halt_patrol(object me)
{            
	 message_vision(HIG"$N松了口气，看来不再继续在此处巡城了。\n"NOR, me);        
        me->set_short_desc(0);  
        me->delete_temp("pending/patrol");     
        return 1;
}

void set_liumang(object me)
{                   
          object lm;
          int exp, lv, qi, jing;
              
          lm = new("/quest/changan_job/liumang");
          exp = me->query("combat_exp");
          lv = to_int(pow(to_float(exp*10), 1.0 / 3)) + 1;       
          qi = me->query("max_qi") * 3 / 2;
          jing = me->query("max_jing") * 3 /2;

          lm->set("max_qi", qi);
          lm->set("max_jing", jing);         
	   lm->set("eff_jing", jing);
	   lm->set("jing", jing);
          lm->set("eff_qi", qi);
	   lm->set("qi", qi);

          lm->set("combat_exp", exp * 3 / 2);
	   lm->set_skill("unarmed", lv + random(10));
	   lm->set_skill("dodge", lv + random(10));
	   lm->set_temp("apply/attack", lv * 3 / 4 + random(5));
	   lm->set_temp("apply/defense", lv * 3 / 4 + random(5));
          lm->set_temp("apply/dodge", lv * 3 / 4 + random(5));

          lm->move(environment(me));              
          message_vision(HIW"突然周围行人大喊：抓贼，抓贼！$N定睛一看，一个$n正四处奔逃。\n"NOR  
                             HIR"只见$N大喝一声：哪里逃！随即奋不顾身地扑向$n。\n" NOR, me, lm);
          me->competition_with(lm);
          lm->competition_with(me);      
}

int help(object me)
{
        write(@HELP
这个指令在巡城时使用。
HELP );
        return 1;
}

