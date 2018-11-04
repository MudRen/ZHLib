#include <ansi.h>
inherit ITEM;

void create()
{
        set_name("原石", ({"baoshi","yuanshi"}));
        set_weight(500);
       set("changed",1);
                  set("no_sell",1);
                 set("unit","颗");
                 set("material","baoshi");
                 set("color",0);
                 set("value",1);
                 set("long","一块原石，可能在某个地方可以练制成宝石的。\n");
        if( clonep() )
                set_default_object(__FILE__);
        setup();
}

void init()
{
	add_action("do_enchase", "inset");
}

int do_enchase(string arg)
{
   object in_obj;
   string item,weapon_type;
   string mats;
   mixed *list_prop;
   int rd,inset_num ,i,k,tmp;
   object me = this_player();
   object ob = this_object();
   mapping prop;
   string *attack_kind=({"cold","fire","lightning","poison","magic"});
   
   if(ob->query("level")<1) return notify_fail("这个东西好象不行吧？\n");
   if(!arg) return notify_fail("你要把宝石镶嵌到什么上？\n");
   if(sscanf(arg, "%s", item)!=1) return notify_fail("你要把宝石镶嵌到什么上？\n");
   if(!objectp(in_obj = present(item, me))) return notify_fail("你身上没有这样东西。\n");
   if( in_obj->query("equipped") )
      return notify_fail("你必须放下这样东西才能镶嵌宝石。\n");
   if( in_obj->query("sockets/max")<=in_obj->query("sockets/now"))
      return notify_fail("这样东西不能镶嵌宝石或已经镶满了。\n");
   
   if (random(100)>85) {
       message_vision(CYN"$N把$n"+CYN"朝"+in_obj->query("name")+CYN"使劲一捅。 \n"NOR,me,ob);
       tell_room(environment(me),HIM"只见"+ob->name()+HIM"撞在"+in_obj->query("name")+HIM"上，片片裂开。 \n"NOR);
       message_vision(CYN"$N镶嵌$n失败了。\n"NOR,me,ob);
       ob->move(VOID_OB);
       destruct(ob); 
       return 1;
   }
   if (random(100)>85) {
       message_vision(CYN"$N把$n"+CYN"朝"+in_obj->query("name")+CYN"使劲一捅。 \n"NOR,me,ob);
       tell_room(environment(me),HIM"结果"+ob->name()+HIM"在"+in_obj->query("name")+HIM"上面捅出一个大窟窿。 \n"NOR);
       message_vision(HIM+in_obj->query("name")+"损坏了。\n"NOR,me,ob);
       message_vision(CYN"$N镶嵌$n失败了。\n"NOR,me,ob);
       in_obj->move(VOID_OB);
       destruct(in_obj); 
       return 1;
   }
   if (random(100)>85) {
       message_vision(CYN"$N把$n"+CYN"朝"+in_obj->query("name")+CYN"使劲一捅。 \n"NOR,me,ob);
       tell_room(environment(me),HIM"只见"+ob->name()+HIM"撞在"+in_obj->query("name")+HIM"上，片片裂开。 \n"NOR);
       tell_room(environment(me),HIM+in_obj->query("name")+HIM"也被捅出一个大窟窿。 \n"NOR);
       message_vision(HIM+ob->name()+"和"+in_obj->query("name")+"都不能用了。\n"NOR,me,ob);
       message_vision(CYN"$N镶嵌$n失败了。\n"NOR,me,ob);
       ob->move(VOID_OB);
       in_obj->move(VOID_OB);
       destruct(ob); 
       destruct(in_obj); 
       return 1;
   }      
   
   prop=ob->query("prop");
   list_prop=keys(prop);
   list_prop = sort_array(list_prop, "sort_keys", ob);   
   if(in_obj->query("armor_prop"))   //防具
   {
      for (i=0;i<sizeof(list_prop);i++)
       {
       	  switch(list_prop[i]) {
       	  	case "damage":
       	  		tmp=in_obj->query("armor_prop/armor");
       	  		in_obj->add("armor_prop/armor",(int)(prop["damage"]*tmp/100));
       	  		break;
       	  	case "luck" :if (random(40) < prop["luck"]) in_obj->add("sockets/max",1);break;
       	  	case "attack":
       	  	        in_obj->add("armor_prop/"+attack_kind[random(5)]+"_defence",ob->query("level")*4);
       	  		break;	
       	  }
       }
   }
   else if(in_obj->query("weapon_prop")) 
   {  
      for (i=0;i<sizeof(list_prop);i++)
       {
       	  switch(list_prop[i]) {
       	  	case "damage":
       	  		tmp=in_obj->query("weapon_prop/damage");
       	  		in_obj->add("weapon_prop/damage",(int)(prop["damage"]*tmp/100));
       	  		break;
       	  	case "luck" :if (random(40) < prop["luck"]) in_obj->add("weapon_prop/luck",1);break;
       	  	case "attack":
       	  	        for (k=0;k<4;k++) {
       	  			if (in_obj->query("weapon_prop/"+attack_kind[k]+"_attack")) {if (random(40)<prop["attack"]) in_obj->add(attack_kind[k]+"_attack/max_level",1);}
       	  		} break;	
       	  }
       }
     }
       in_obj->add("sockets/now",1);
       message_vision(CYN"$N把$n"+CYN"镶嵌到"+in_obj->query("name")+CYN"上 \n"NOR,me,ob);
       tell_room(environment(me),HIM"只见"+ob->name()+HIM"发出一团妖艳的光芒,环绕在"+in_obj->query("name")+HIM"的周围 \n"NOR);
       message_vision(CYN""+in_obj->query("name")+CYN"似乎变得更加厉害了！\n"NOR,me);
       if(!in_obj->query("old_long")) in_obj->set("old_long",in_obj->query("long"));
       in_obj->set("long",in_obj->query("old_long")+"上面嵌上了"HIW+chinese_number(in_obj->query("sockets/now"))+"颗宝石\n"NOR);
       in_obj->save();
       destruct(ob);
       return 1;
}
