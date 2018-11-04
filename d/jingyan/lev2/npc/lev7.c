// migong lev2

#include <ansi.h>

inherit NPC;


void create()

{
    
   set_name("巨蜥", ({ "ju xi" , "xi" }));
      
          set("race", "野兽");
       set("long",
"一头巨大的蜥蜴。\n");
              set("attitude", "aggressive");
                set("vendetta/authority",1);

set("limbs", ({ "头部", "身体", "尾巴" }) );
        set("verbs", ({ "bite" }) );
	       set("max_qi",800+random(800));
  set("max_jing",800+random(800));
  set("max_sen",800+random(800));
  set("max_mana",800+random(800));
  
      set("dex",35);
     set("str" ,30);
       
    set("age", 5);

       set("shen_type", -1);

        set("intellgent",1);

	set("pursuer",1);

        set("combat_exp", 700000);
                  
        set_temp("apply/attack", 90);
        set_temp("apply/damage", 90);
        set_temp("apply/armor", 90);
        set_temp("apply/defence",90);

   setup();

        

}

void init( )

{
	object ob;	
        remove_call_out("hunting");
	if( interactive(ob = this_player())  ) {
        call_out("hunting",1);
        }
	if(!environment()->query("no_fight") && random(10) < 5)
        call_out("hunting",1);
}

void hunting()
{
	int i;
        object *ob;
        ob = all_inventory(environment());
        for(i=sizeof(ob)-1; i>=0; i--) {
        if( !ob[i]->is_character() || ob[i]==this_object() || !living(ob[i])) continue;
        if(ob[i]->query("vendetta/authority")) continue;
                kill_ob(ob[i]);
                ob[i]->fight(this_object());
        }
}

