// tianzi.c
// by SmallFish  in  1/22/2002  in JDMR

#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{	
	object ob;
	mapping mine;
	string line;
	int basic_data;

//	me = this_player();

       ob = me;
       if (!arg)
	       ob = me;
       else if (me->query("born_tianzi") < 1) write(HIW"你的天资都已经分配完了！\n"NOR);
       else
       {
              switch(arg)
              {
                    case "悟性":
                            if (me->query("int") >= 30) 
                                    write(HIW"你的先天悟性已经达到了30，无法再分配啦！\n"NOR);
                            else
                            {
                                    me->add("int",1);
                                    me->add("born_tianzi",-1);
                                    write(HIW"你将一点天资分配给悟性。\n"NOR);
                            }
                            break;
                    case "膂力":
                            if (me->query("str") >= 30) 
                                    write(HIW"你的先天膂力已经达到了30，无法再分配啦！\n"NOR);
                            else
                            {
                                    me->add("str",1);
                                    me->add("born_tianzi",-1);
                                    write(HIW"你将一点天资分配给膂力。\n"NOR);
                            }
                            break;
                    case "身法":
                            if (me->query("dex") >= 30) 
                                    write(HIW"你的先天身法已经达到了30，无法再分配啦！\n"NOR);
                            else
                            {
                                    me->add("dex",1);
                                    me->add("born_tianzi",-1);
                                    write(HIW"你将一点天资分配给身法。\n"NOR);
                            }
                            break;
                    case "根骨":
                            if (me->query("con") >= 30) 
                                    write(HIW"你的先天根骨已经达到了30，无法再分配啦！\n"NOR);
                            else
                            {
                                    me->add("con",1);
                                    me->add("born_tianzi",-1);
                                    write(HIW"你将一点天资分配给根骨。\n"NOR);
                            }
                            break;
                    default:
                            write(HIW"你只能把天资分配给：膂力、悟性、根骨、身法这四种属性。\n"NOR);
                            break;
              }
	}

	mine = ob->query_entire_dbase();
	line = sprintf("\n-------先天资质-------\n");
	line += sprintf(
			" 膂力：[%s]  悟性：[%s]  根骨：[%s]  身法：[%s]\n\n", 
			sprintf("%3d",mine["str"]),
			sprintf("%3d",mine["int"]),
			sprintf("%3d",mine["con"]),
			sprintf("%3d",mine["dex"]));
	line += sprintf("-------后天资质-------\n");
	line += sprintf(
			" 膂力：[%s]  悟性：[%s]  根骨：[%s]  身法：[%s]\n\n", 
			sprintf("%3d",ob->query_str()),
			sprintf("%3d",ob->query_int()),
			sprintf("%3d",ob->query_con()),
			sprintf("%3d",ob->query_dex()));
	line += sprintf(HIC"-------魔法提升先天根骨：%s\n\n"NOR, sprintf("%3d",ob->query("con_improve_time")));

	basic_data = mine["str"] + mine["int"] + mine["con"] + mine["dex"] + me->query("born_tianzi");
	if(basic_data > (80 + (int)ob->query("con_improve_time")))
 	  line += sprintf(HIY "先天资质异常, %3d - 80 = %3d\n\n" NOR,basic_data,(basic_data-80));
	  line += sprintf(HIY "剩余可分配天资：%3d\n\n"NOR,me->query("born_tianzi"));		
	write(line); 

	return 1;
}



