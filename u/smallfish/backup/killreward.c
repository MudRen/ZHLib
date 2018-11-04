//×îºóÐÞ¸ÄÊ±¼ä£¨ÇëÐÞ¸ÄÕß×¢Ã÷£©2000-11-25 llm(±£»¤ÆÚÍæ¼ÒÒÆµ½ÌØÊâµØ·½)

#include <ansi.h>

inherit F_DBASE;

void create()
{
    seteuid(getuid());
    set("name", "ËÀÍö¾«Áé");
    set("id", "killreward");
    set("chat_amount",1000000000);
}

void killer_reward(object killer, object victim)
{
    string msg,name,vmark,*atk;
    int level,exp,pot,score,i;
    mapping quest;
    float k;
    object pker;
    
    exp = victim->query("combat_exp");
//    killer->killed_enemy(victim);Õâ¸öº¯ÊýÕÒ²»µ½³ö´¦£¬ÏÈ×¢ÊÍÁË
    if(userp(victim))//Íæ¼Ò±»É±
    {
        if(!killer->is_character())//²»ÊÇÉúÎï
        {
            name = killer->query("short");
            switch(killer->query("why_die"))//Õâ¸öÊÇÔÚ¾ßÌåµÄÎÄ¼þÀï¼ÓµÄ
            {
                case "Õó": msg="ÔÚÄ³´¦À§";break;
                case "Ë¤": msg="ÔÚÄ³´¦Ë¤";break;
                case "¶¾": msg="ÖÐ¶¾";break;
                default: msg="ÒâÍâµØ";break;
            }
        }
        else//ÊÇÉúÎï
        {
            name = killer->name(1);
            switch(killer->query("race"))
            {
                case "Ò°ÊÞ": msg = "Ò§";break;
                case "¼ÒÐó": msg = "²È";break;
                case "·ÉÇÝ": msg = "×Ä";break;
                case "À¥³æ": msg = "¶£";break;
                default: msg = "É±";
            }
            msg = "±»"+name+HIM+msg;
        }
        CHANNEL_D->do_channel(this_object(), "rumor",
            sprintf("¾ÝËµ%s%sËÀÁË¡£", victim->name(1),msg));  
        victim->add("die/times", 1);              //¼ÓÒ»´Î±»É±´ÎÊý by llm
        victim->set("die/name",name);  //¼ÇÏÂ×îºóÒ»´ÎËÀÓÚË­ÊÖ by llm

        if (userp(killer))//É±ÊÖÊÇÍæ¼Ò
        {
            victim->add("die/pk", 1);                //¼ÓÒ»´Î±»PK´ÎÊý  by llm
            victim->set("die/name","Ä³Î»Íæ¼Ò");      //¸²¸ÇÇ°ÃæµÄname by llm
//-----------by llm about ÅÐ¶ÏÖ÷¶¯¹¥»÷ 2000/9/4----------------
            if(pointerp(atk = victim->query_temp("attacker"))//±»º¦ÈËÓÐ±»¹¥»÷¹ýµÄÈËÃûµ¥
                 &&member_array(killer->query("id"),atk)!=-1  //Ãûµ¥ÖÐÓÐkillerµÄid
                 &&!killer->query_temp("chaseing")  //²»ÊÇÒò¹«×·²¶PKerÕß
            )
            {
                vmark = "";
                for(i=0; i<sizeof(atk); i++)
                {
                    if(atk[i]!=killer->query("id")) vmark += atk[i]+",";//Í³¼ÆÆäËüµÄ¹¥»÷Õß
//¼ÆËãÊ¹ÓÃPKµãÊý£¬by xker 2001/4/6---------------------------------------------------------
                    if(exp>14999)
                    {       
                        if(objectp(pker=find_player(atk[i])))
                        {
                            k=(pker->query("combat_exp")-exp)*1.0/(pker->query("combat_exp")+1000);
                            if(k<0) k = 0;
                            pker->add("pk_points", 0-to_int(192*sqrt(k)));
                            pker->save();
                        }
                        else
                        {
                            pker = new(USER_OB);
                            seteuid(atk[i]);
                            export_uid(pker);
                            seteuid(getuid());
                            pker->restore();
                            k=(pker->query("combat_exp")-exp)*1.0/(pker->query("combat_exp")+1000);
                            if(k<0)         k = 0;
                            pker->add("pk_points",0-to_int(192*sqrt(k)));
                            pker->save();
                            destruct(pker);
                        }
                    }
//----------------------------------------------------------------------------------------
                }
                write_file("/log/static/KILL_PLAYER",sprintf("%s(%s)kill%s(%s)in %s on %s(°ïÐ×£º%s)\n",
                    killer->name(1),killer->query("id"),victim->name(1), victim->query("id"),environment(victim)->query("short"),ctime(time())[4..23],vmark ));
                killer->apply_condition("killer", 2000);//ÔöÒ»±¶Í¨¼­Ê±¼ä
                killer->add("PKS", 1);//ÕâÊÇÕæÕýµÄPK£¡
            }
            else//·ñÔò²»Ëã£¬¼ÇÈëÁíÒ»¸öÎÄ¼þÖÐ
            {
                write_file("/log/static/NOT_PK",sprintf("%s(%s)kill%s(%s)in %s on %s\n",
                killer->name(1),killer->query("id"),victim->name(1), victim->query("id"),environment(victim)->query("short"),ctime(time())[4..23] ));
            }
//------Ö÷¶¯¹¥»÷end-------by llm about ÅÐ¶Ï20ËêÏÂ±£»¤----------
            if(victim->query("age")<20)
            {
                if((time()-(int)victim->query("pk_time"))>86400)//±»PKÊ±¼ä¹ýÁË±£»¤ÆÚ£¬ÖØÐÂ¼ÆÊ±
                    victim->set("pk_time",time());
                else
                {
                    victim->set_temp("newdie",1);//Õâ¸ö¼ÇºÅ¿ÉÒÔÒÆµ½·Ç°×ÎÞ³£Ö®µØ
                    return;//Ö±½Ó·µ»Ø£¬Õâ¾ÍÃ»ÓÐËðÊ§ÁË
                }
            }
        }
        else //Ð×ÊÖ²»ÊÇÍæ¼Ò
	        log_file("static/PLAYER_DIE",sprintf("%s(%s)kill%s(%s)in %s on %s\n",
                name,killer->query("id"),victim->name(1), victim->query("id"),environment(victim)->query("short"),ctime(time()) ));
        if(!killer->query("quest_npc")
            ||(victim->query("quest_dg/name")!=killer->name(1)
            &&victim->query("quest_wg/quest")!=killer->name(1)
            &&victim->query("quest_df/name")!=killer->name(1)//²»ÊÇÕýÔÚÖ´ÐÐÉ±ÊÖÈÎÎñ
            ))
        {
            victim->skill_death_penalty();//½µÎä¹¦
            victim->add("combat_exp", -(int)victim->query("combat_exp") / 50);
        }
        else     //kill clone_npcÈÎÎñÊ±ËÀ£¬²»½µskill£¬¾­Ñé½µµÃÉÙ
            victim->add("combat_exp", -(int)victim->query("combat_exp") / 200);
        if(victim->query("jobname")!="Îä¹Ù")
            victim->add("shen", -(int)victim->query("shen") / 10);
        if( victim->query("thief") )
            victim->set("thief", (int)victim->query("thief") / 2);
        if( (int)victim->query("potential") > (int)victim->query("learned_points"))
            victim->add("potential",((int)victim->query("learned_points") - (int)victim->query("potential"))/2 );
    }
    else if( interactive(killer))  //npc±»Íæ¼ÒÉ±£¬npc±»npcÉ±¾Í²»¹ÜÀ²£¡llm 2001/3/30¸ÄÓÐ¹ØÉý½µÉñµÄÅÐ¶Ï
    {
		killer->add("MKS", 1);//¼ÓMKÒ»´Î
        if( stringp(vmark = victim->query("vendetta_mark")) )
			killer->add("vendetta/" + vmark, 1);//¼Ó³ðºÞ¼ÇºÅ£¬ºÃÏóºÃ´¦²»´ó£¿by llm
		shen = (int)victim->query("shen");//È¡³ö±»É±ÕßµÄshenÖµ±¸ÓÃ
		if(killer->query("combat_exp") < victim->query("combat_exp"))
		{
	   		if(victim->query("shen") > 0)      //É±ËÀÕýÉñNPC
	   		{
	   			if(killer->query("quest_dg/name")!=viticm->name(1)//²»ÊÇ¶À¹ÂÈÎÎñ
	   				&&killer->query("quest_wg/name")!=viticm->name(1))//²»ÊÇÎä¹ÙÈÎÎñ
	   		   	killer->add("shen", -(int)victim->query("shen") / 5);//½µÉñ
	   		}
    		else
    		{
    			if(killer->query("quest_df/name")!=viticm->name(1)//²»ÊÇ¶«·½É±ÈÎÎñ
                    killer->add("shen", -(int)victim->query("shen") / 10);
            }
        }
// ÒÔÏÂÊÇÈÎÎñÖÐÉ±ÈËµÄ½±Àø
		if(mapp(quest = killer->query("quest_df")))    //Ä§
		{
        	if(quest["desc"] == "Ãð")
        	{
            	if((quest["name"] == "ÄÐ×Ó" && victim->query("gender") == "ÄÐÐÔ" && victim->query("per") >= 25) ||
               		(quest["name"] == "Å®×Ó") && victim->query("gender") == "Å®ÐÔ"||
                	(quest["type"] == "µØµã" &&  getuid(victim) == quest["dir"]))
            	{
               		if((quest["time"]-time()) < 0)
               		{
                  		killer->delete("quest_df");
                  		return ;
                  	}
               		else if(victim->query("race")=="Ò°ÊÞ") return;
               		else
               		{
                  		level = (quest["level"]+1)*(60+random(40));
                  		exp = to_int(sqrt(to_float(victim->query("combat_exp"))));
                  		if(exp > level)   exp = level;
                  		pot = exp/(3+random(5));
                  		killer->add("potential",pot);
                  		killer->add("combat_exp",exp);
                  		tell_object(killer,"[1;37m\nÄã±»½±ÀøÁË£º\n" +
                                  chinese_number(exp) + "µãÊµÕ½¾­Ñé\n" +
                                  chinese_number(pot) + "µãÇ±ÄÜ\n\n[2;37;0m");
                        if(shen > 0&&flag) killer->add("shen", -shen/ 5);
                  		return ;
               		}
            	}
         	}
			if(quest["name"]==viticm->name(1)&&flag)
			{
				if(shen > 0) killer->add("shen", -shen/ 5);
				return;
			}   	
		}
		if(mapp(quest = killer->query("quest_dg")))    //ÏÀ
		{
        	if(quest["type"] == "É±" && victim->name(1) == quest["name"])
        	{
                if((i=killer->query_temp("questdg_times")) < 2)   i = 10-i;
            	else i = 1;
            	level = quest["level"]+1;
            	exp = level*quest["bonus"]*12/(i*(10+random(5)));
            	pot = level*quest["bonus"]/(3+random(3));
            	exp = exp*130/100;
            	pot = pot*130/100;   //Æ½ºâÐÞÕý
            	killer->add("potential",pot);
            	killer->add("combat_exp",exp);
            	tell_object(killer,"[1;37m\nÄã±»½±ÀøÁË£º\n" +
                            chinese_number(exp) + "µãÊµÕ½¾­Ñé\n" +
                            chinese_number(pot) + "µãÇ±ÄÜ\n\n[2;37;0m");
            	killer->add_temp("questdg_times",1);
            	killer->delete("quest_dg");
            	if(shen < 0)
            		killer->add("shen", shen/10);//Ö»¼ÓÉñ
            	return ;
         	}
      	}
      	if(mapp(quest = killer->query("quest_wg")))    //¾ü
      	{
			if(quest["type"]=="É±"&&quest["quest"]==victim->name(1))
			{
            	tell_object(killer,"¹§Ï²Äã£¡ÄãÓÖÎª³¯Í¢Á¢ÁËÒ»¹¦£¡\n");
				i = killer->query_temp("questwg_repeat");
            	if ( i < 2 )
				{
					exp=30+random((killer->query("jobrank")+1))*2;
					score=random((killer->query("jobrank")+1))*4+5;
				}
            	else
            	{
		           	if ( i < 6 ) level = 1;
		           	else if(i < 18 ) level = 2;
		           	else level = 4;
	            	exp=(killer->query("jobrank")+1)*quest["bonus"]*8*level/(10+random(10));
	            	score=((killer->query("jobrank")+1)*6+random(6*(killer->query("jobrank")+1)))*level;
	            }
            	pot = exp/(3+random(3+killer->query("jobrank")));
	         	
    	     	killer->add("combat_exp", exp);
        	 	killer->add("potential",pot);
        		killer->add("score",score);
         		tell_object(killer,HIW"Äã±»½±ÀøÁË£º\n" +
            		chinese_number(exp) + "µãÊµÕ½¾­Ñé\n"+
         			chinese_number(pot) + "µãÇ±ÄÜ\n" +
         			chinese_number(score)+"µãÎä¹ÙÆÀ¼Û¡£\n"NOR);
       	        killer->add_temp("questwg_repeat",1);
            	killer->set_temp("questwg_giveup_repeat",0);        
	         	killer->delete("quest_wg");
			}
			return;
    	}
    }
}
