

#include <ansi.h>
inherit ITEM;
//void tai_status();
int get_baoshi(int sta,string mess1);
void baoshi_attribute(object obj,int i);

void create()
{
        set_name(HIM"金属提炼台(tai)"NOR, ({"tai"}) );
        set("short", HIM"金属提炼台(tai)"NOR);
        set_max_encumbrance(5000);
        set_max_items(10);
        set("temperature",25);
        set_temp("max_temp",25);
        set_temp("min_temp",25);
        
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "个");
                 set("no_get", 1);
                 set("no_put", 1);
	set ("long", @LONG
这是提炼金属的地方。
在这里你可以用如下命令提炼金属:
    init    :   租用金属提炼台(十金一次）
    add     :	把材料放进金属提炼台
    jiawen  :	用内力和法力给金属提炼台加温
    jiangwen:	用内力和法力给金属提炼台降温
    tilian  :	结束提炼
    hecheng : 	结束合成
    tem     :   量金属提炼台的温度
LONG);               

                set("value", 50);
        }
}

int is_container() { return 1; }

void init()
{
	add_action("do_init", "init");
	add_action("do_add","add");
	add_action("do_jiawen", "jiawen");
	add_action("do_jiangwen", "jiangwen");
	add_action("do_tilian", "tilian");
	add_action("do_hecheng", "hecheng");
	add_action("do_get","get");
	add_action("do_put","put");
	add_action("do_tem","tem");
	
//         remove_call_out("do_temperature");
//         call_out("do_temperature", 2);
}

int do_init()
{
   	object me = this_player();
   	object obj,ob = this_object();   
   	     
//      if (me->query("balance")<200000) return notify_fail("金属提炼台是白用吗？十金一次！\n");  
     	if(ob->query_temp("user") && ob->query_temp("user") != me->query("id"))
     	{
     		if ( time()-ob->query_temp("init_time")<300 && ((obj=present(ob->query_temp("user"))) || (obj = present(ob->query_temp("user"), environment(me))))) 
   			return notify_fail(obj->name()+"正在用呢，请等五分钟再试试！\n");      
   	}
//       me->add("balance",-100000);
	reload_object(ob);
	ob->set_temp("init_time",time());
        ob->set_temp("user",me->query("id"));
         remove_call_out("do_temperature");
         call_out("do_temperature", 2);
         message_vision("$N花了十金租用了"+ob->name()+"准备提炼金属。\n",me);
        message("channel:chat",HIM"【谣言】：听说"+me->name()+"开始提炼金属。\n"NOR,users());
         return 1;		
}

int do_add(string arg)
{
	string item_name;
        object me = this_player();
        object ob = this_object();
        object item;
	if (ob->query_temp("user") != me->query("id")) return notify_fail("你租用了金属提炼台了吗？\n");
        if(!arg) return notify_fail("你要将什么东西加进金属提炼台里？\n");
        if( sscanf(arg, "%s in tai", item_name)!=1 )
                return notify_fail("用法：add <> in tai。\n");
        item=present(item_name, me);
        if (! present(item_name, me)) return notify_fail("你身上没有这东西。\n");
     	if (sizeof(all_inventory(ob))>=2) return notify_fail(ob->name()+"里面已经放满了。\n");
        message_vision( "$N将一"+item->query("unit")+item->query("name")+"放进"+ob->name()+"。\n",me);
        item->move(ob);
        
        return 1;
                
}

int do_get(string arg)
{
	string item_name;
        object me = this_player();
        object ob = this_object();
        if(!arg) return notify_fail("你要干什么？\n");
        if( sscanf(arg, "%s from tai", item_name)==1 && ob->query_temp("user") != me->query("id"))
                return 1;//notify_fail("不要拿别人的东西\n");
        return 0;
                
}

int do_put(string arg)
{
	string item_name;
        if(!arg) return notify_fail("你要干什么？\n");
        if( sscanf(arg, "%s in tai", item_name)==1 )
                return 1;
        return 0;
                
}

int do_jiawen()
{
   object me = this_player();
   object ob = this_object();
   mixed *inv;
   int k;
   
   inv = all_inventory(ob);
   if( !sizeof(inv) ) 
	return notify_fail("金属提炼台里什么都没有，加什么温，烧空气啊？\n");
   if (ob->query_temp("user") != me->query("id")) return notify_fail("你租用了金属提炼台了吗？\n");
   if (me->query("force")<200) return notify_fail("你的内力不够！\n");
   if (me->query("mana")<200) return notify_fail("你的法力不够！\n");
   if (me->is_busy()) return notify_fail("你正忙着呢。\n");
   
      me->add("force",-150);
       me->add("mana",-150);
   if (random(2)==0) tell_room(environment(me),HIR+me->name()+"默运神功，双手变得通红,然后按在"+ob->name()+HIR+"上，使其慢慢地变热。 \n"NOR);
   else tell_object(me,HIR+me->name()+"默运神功，双手变得通红,然后按在"+ob->name()+HIR+"上，使其慢慢地变热。 \n"NOR);
    if (!wizardp(me)) me->start_busy(1);
     ob->add("temperature",100);
   if (ob->query("temperature")>3500) {
   	for (k=0;k<sizeof(inv);k++) destruct(inv[k]);
 	tell_object(me,ob->name()+"温度过高，材料汽化消失了！\n");
   	reload_object(ob);
   	return 1;  		
   }
   if (ob->query("temperature")>ob->query_temp("max_temp")) ob->set_temp("max_temp",ob->query("temperature"));
   
   return 1;	
}

int do_jiangwen()
{
   object me = this_player();
   object ob = this_object();
   mixed *inv;
   int k;
   
   inv = all_inventory(ob);
   if( !sizeof(inv) ) 
	return notify_fail(ob->name()+"里什么都没有，降什么温啊？\n");
   if (ob->query_temp("user") != me->query("id")) return notify_fail("你租用了金属提炼台了吗？\n");
   if (me->query("force")<200) return notify_fail("你的内力不够！\n");
   if (me->query("mana")<200) return notify_fail("你的法力不够！\n");
   if (me->is_busy()) return notify_fail("你正忙着呢。\n");
   
       me->add("force",-150);
       me->add("mana",-150);
   
   if (random(2)==0) tell_room(environment(me),HIW+me->name()+"默运神功，双手蒙上一层寒霜,然后按在"+ob->name()+HIW+"上，使其慢慢地变冷。 \n"NOR);
   else tell_object(me,HIW+me->name()+"默运神功，双手蒙上一层寒霜,然后按在"+ob->name()+HIW+"上，使其慢慢地变冷。 \n"NOR);
    if (!wizardp(me)) me->start_busy(1);
   if (ob->query("temperature")>=100) ob->add("temperature",-100);
   	else ob->add("temperature",-20);
   if (ob->query("temperature")<=-273) {
   	for (k=0;k<sizeof(inv);k++) destruct(inv[k]);
 	tell_object(me,ob->name()+"温度达到了绝对零度，材料被冻坏消失了！\n");
   	reload_object(ob);
   	return 1;  		
   }
     
   if (ob->query("temperature")<ob->query_temp("min_temp")) ob->set_temp("min_temp",ob->query("temperature"));
   
   return 1;		
}

int do_tilian()
{
   object me = this_player();
   object ob = this_object();
   mixed *inv;
   string mess;
   int i,min_temp,max_temp,suss,suss1,*color1,tmp; //sta为炼完状态，0：失败，物品消失；1：失败，物品不消失；
   		//2：成功，得到提纯金属

   if (ob->query_temp("user") != me->query("id")) return notify_fail("你租用了金属提炼台了吗？\n");
  
   mess="";
   inv = all_inventory(ob);
   if( !sizeof(inv) ) 
	return notify_fail("金属提炼台里什么都没有，你想干什么啊？\n");  
   if( sizeof(inv)<=1) 	return get_baoshi(random(2),mess);//一颗总不能用来提炼吧？ 
   for(i=0; i<sizeof(inv); i++) //台里含有非金属类杂质、金属不同，sta=0
   	if (inv[i]->query("material") != "metal" ||inv[0]->query("name") !=inv[i]->query("name")
   	   || inv[i]->query("level")>1) 
   	{
   		mess=HIG+"炼制的材料里面有不能提炼的材料。\n"+NOR;	
         return get_baoshi(random(2),mess);
   	} 
   	   
   min_temp=-50-(int)inv[0]->query("level")*50;
   max_temp=1000+(int)inv[0]->query("level")*500;
   if (ob->query_temp("max_temp") < max_temp) 
   {
   	mess=HIG+"应该加热到足够的温度才能使材料完全融化。\n"+NOR;
      return get_baoshi(random(2),mess);
   }
   if (ob->query_temp("min_temp") > min_temp) 
   {
   	mess=HIG+"材料融化后，需要经过极寒才能重新结晶。\n"+NOR;
      return get_baoshi(random(2),mess);
   }
   

  
/*
   tmp=(int)(((int)(min_temp*1.1)-ob->query_temp("min_temp"))/10);//最低温度影响
   if (tmp<0) tmp*=-1;
   suss=tmp;
   tmp= (int)(ob->query_temp("max_temp")-(int)(max_temp*1.1)/10);//最高温度影响
   if (tmp<0) tmp*=-1;
   suss+=tmp;
*/
   suss1=inv[0]->query("level")*10+10;//等级越高，成功度越低
   suss=random(100); //成功率
   tmp=(ob->query("temperature")-(inv[0]->query("level")*100))/5; //完成温度的影响
   if (tmp<0) tmp*=-1;
   suss-=tmp;
   suss=100;//测试
 /*  
   tmp=0;
   for(i=0; i<sizeof(inv);i++)
   {
   	if (inv[0]->query("color") != inv[i]->query("color")) tmp=1;
   }  
 */ 
   //suss=100;//测试用
    if (suss>suss1 ) return get_baoshi(2,mess);
     else  return get_baoshi(random(2),mess);
  

}


int do_hecheng()
{
   object me = this_player();
   object ob = this_object();
   mixed *inv;
   string mess;
   int i,min_temp,max_temp,suss,suss1,*color1,tmp; //sta为炼完状态，0：失败，物品消失；1：失败，物品不消失；
   		//2：成功，得到合成金属

   if (ob->query_temp("user") != me->query("id")) return notify_fail("你租用了金属提炼台了吗？\n");
  
   mess="";
   inv = all_inventory(ob);
   if( !sizeof(inv) ) 
	return notify_fail("金属提炼台里什么都没有，你想干什么啊？\n");  
   if( sizeof(inv)<=1) 	return get_baoshi(random(2),mess);//一颗总不能用来合成吧？ 
   for(i=0; i<sizeof(inv); i++) //台里含有非金属类杂质、相同的材料，sta=0
   	if (inv[i]->query("material") != "metal" ||inv[0]->query("id") ==inv[1]->query("id")
   	   || (inv[i]->query("level")>4 &&inv[i]->query("level")<2) || inv[0]->query("level")!=inv[i]->query("level")) 
   	{
   		mess=HIG+"炼制的材料里面有不能提炼的材料。\n"+NOR;	
         return get_baoshi(random(2),mess);
   	} 
   	   
   min_temp=-50-(int)inv[0]->query("level")*50;
   max_temp=1000+(int)inv[0]->query("level")*500;
   if (ob->query_temp("max_temp") < max_temp) 
   {
   	mess=HIG+"应该加热到足够的温度才能使材料完全融化。\n"+NOR;
      return get_baoshi(random(2),mess);
   }
   if (ob->query_temp("min_temp") > min_temp) 
   {
   	mess=HIG+"材料融化后，需要经过极寒才能重新结晶。\n"+NOR;
      return get_baoshi(random(2),mess);
   }
   

  
/*
   tmp=(int)(((int)(min_temp*1.1)-ob->query_temp("min_temp"))/10);//最低温度影响
   if (tmp<0) tmp*=-1;
   suss=tmp;
   tmp= (int)(ob->query_temp("max_temp")-(int)(max_temp*1.1)/10);//最高温度影响
   if (tmp<0) tmp*=-1;
   suss+=tmp;
*/
   suss1=inv[0]->query("level")*10+10;//等级越高，成功度越低
   suss=random(100); //成功率
   tmp=(ob->query("temperature")-(inv[0]->query("level")*100))/5; //完成温度的影响
   if (tmp<0) tmp*=-1;
   suss-=tmp;
   suss=100;//测试
 /*  
   tmp=0;
   for(i=0; i<sizeof(inv);i++)
   {
   	if (inv[0]->query("color") != inv[i]->query("color")) tmp=1;
   }  
 */ 
   //suss=100;//测试用
    if (suss>suss1 ) return get_baoshi(2,mess);
     else  return get_baoshi(random(2),mess);
  

}

int get_baoshi(int sta,string mess1)
{
   object me = this_player();
   object obj,ob = this_object();
   string mess, me_name,ob_name;
   int i,k,sum=0,aaa=0,*kind=({0,0});
   mixed *inv;

   me_name=me->name();
   ob_name=ob->name();
   inv = all_inventory(ob);
   mess=HIG+me_name+"觉得差不多了，收起神功，屏住呼吸，小心翼翼地打开"+ob_name+"。\n";
   switch(sta)
   {
   	case 0:
   		mess+=HIG+"但是"+ob_name+"里面空空如也，什么都没有。\n"+NOR;
   		for (k=0;k<sizeof(inv);k++)
   			destruct(inv[k]);
   		message("channel:chat",HIM"【谣言】：听说"+me_name+"炼制材料失败，所有材料付之一炬。\n"NOR,users());
   		break;
   	case 1:
   		mess+=HIG+"发现原来炼制的材料还在里面，只好又尴尬地拿了出来。\n"+NOR;
   		for (k=0;k<sizeof(inv);k++)
   			inv[k]->move(me);
   		message("channel:chat",HIM"【谣言】：听说"+me_name+"炼制材料失败，还好，材料还在。\n"NOR,users());
   		break;
   	case 2://提炼成功
   		obj=inv[0];
   		if (sizeof(inv)>1) for (k=0;k<sizeof(inv);k++) 
   				   {	if (inv[k]->query("id")=="jinggang") aaa=1;
   				        if (inv[k]->query("id")=="misiyin") aaa=2;
   				        if (inv[k]->query("id")=="chaodangang") aaa=3;
   				   	sum+=inv[k]->query("list");
   				   }	   				   
   		switch(obj->query("level")) 
   		{
   		    case 0:
   			i=random(4)+1;break;//矿石随机生成纯铁、纯铜、纯锰、纯银
   		    case 1:i=obj->query("list")+4;break;
   		    case 2:
			if (aaa==1) //有精钢存在
			{
				if (sum==11) i=9;
				else if(sum==12) i=10;
				else if(sum==13) i=11;
				else i=5;
			}break;
		    case 3:
			if (aaa==2) //有米斯银存在
			{
				if (sum==20) i=12;
				else if(sum==21) i=13;
				else i=11;
			}break;	
		    case 4:
			if (aaa==3) //有超弹钢存在
			{
				if (sum==25) i=14;
				else i=12;
			}break;			    		
			        
   		 }
   		if (sizeof(inv)>1) for (k=1;k<sizeof(inv);k++) destruct(inv[k]); 
   		baoshi_attribute(obj,i);
   		obj->move(me);
   		mess+=HIG+"发现里面一块"+obj->name()+HIG+"闪闪发光。\n";
   		mess+=me_name+"迫不急待地一把抓了出来。\n"+NOR;
   		message("channel:chat",HIM"【谣言】：听说"+me_name+"炼制材料成功，炼成了"+obj->name()+"。\n"NOR,users());
		break;

   }
   mess+=mess1;
   tell_room(environment(me),mess);
   reload_object(ob);
   return 1;	
}

void baoshi_attribute(object obj,int i)
{
   object me = this_player();
   string *attr;
   int k;
   mixed *material=({
   		({GRN"矿石",		"kuangshi",	0,0,	"metal",""}),
   		({WHT"纯铁",		"chuntie",	1,1,	"metal",({"damage"})}),
   		({YEL"纯铜",		"chuntong",	1,2,	"metal",({"damage"})}),   		
   		({WHT"纯锰",		"chunmeng",	1,3,	"metal",({"damage"})}), 
   		({HIW"纯银",		"chunyin",	1,4,	"metal",({"damage"})}), 
   		({BRED"精"WHT"钢",	"jinggang",	2,5,	"metal",({"damage"})}),  
   		({BRED"精"YEL"铜",	"jingtong",	2,6,	"metal",({"damage"})}),  		  		
   		({BRED"精"WHT"锰",	"jingmeng",	2,7,	"metal",({"damage"})}), 
   		({BRED"精"HIW"银",	"jingyin",	2,8,	"metal",({"damage"})}), 
   		({BMAG"白"YEL"铜",	"baitong",	3,9,	"metal",({"damage"})}), 
   		({BMAG"锰"WHT"钢",	"menggang",	3,10,	"metal",({"damage"})}), 
   		({BMAG"米斯"HIW"银",	"misiyin",	3,11,	"metal",({"damage"})}), 
   		({MAG"超弹"WHT"钢",	"chaodangang",	4,12,	"metal",({"damage"})}), 
   		({MAG"合金"WHT"钢",	"hejingang",	4,13,	"metal",({"damage"})}), 
   		({HIM"尼"HIR"姆"HIG"合"HIY"金","nimuhejin",	5,14,	"metal",({"damage"})}), 

   	});

 //  	if (j>5) j=5;
   	obj->set_name(material[i][0]+NOR,({material[i][1]}));
   	obj->set("level",material[i][2]);
   	obj->set("changed",1);   
   	obj->set("list",material[i][3]);	
   	switch (obj->query("level"))
   	{
   	    case 1:
   		obj->set("long","一块闪闪发光的"+obj->name()+"。\n可以打造装备，也可以进一步提纯。\n是由("+me->query("name")+")炼制的。\n");
   		break;
   	    case 2:
   	    case 3:
   	    case 4:
   		obj->set("long","一块闪闪发光的"+obj->name()+"。\n可以打造装备，也可以合成更高级的材料。\n是由("+me->query("name")+")炼制的。\n");
   		break;
   	    case 5:	
   		obj->set("long","一块闪闪发光的"+obj->name()+"。\n打造装备的终极材料。\n是由("+me->query("name")+")炼制的。\n");
   		break;
  		
   	}


}

int do_tem()
{
   object me=this_player();
   object ob=this_object();
   if (!ob->query_temp("user"))  return notify_fail("你要干嘛？\n");;
   if ( wizardp(me) ||( me==present(ob->query_temp("user")) && (me == present(ob->query_temp("user"), environment(me))))) 
   	tell_object(me,"温度："+this_object()->query("temperature")+" \n");
   else  tell_object(me,"别人在炼材料呢，不要捣乱，不准偷看。\n");
   return 1;
}

void do_temperature()
{
	if (this_object()->query("temperature") > 25) 
	{
		this_object()->add("temperature",-1);
	}	   
	else if (this_object()->query("temperature") < 25)
	{
		this_object()->add("temperature",1);
	}
	call_out("do_temperature", 2);
	
}

