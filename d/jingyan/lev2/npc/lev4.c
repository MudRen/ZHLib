// migong lev2

#include <ansi.h>

inherit NPC;


void create()

{
    
   set_name("�岽��", ({ "she"}));
      
          set("race", "Ұ��");
       set("long",
"�ഫ������ҧ����·�岽���е��С�
��\n");
              set("attitude", "aggressive");
                set("vendetta/authority",1);

set("limbs", ({ "ͷ��", "����", "β��" }) );
        set("verbs", ({ "bite" }) );
	       set("max_qi",800+random(500));
  set("max_jing",800+random(500));
  set("max_sen",800+random(500));
  set("max_mana",800+random(500));
  
      set("dex",30);
     set("str" ,30);
       
    set("age", 5);

       set("shen_type", -1);

        set("intellgent",1);

	set("pursuer",1);

        set("combat_exp", 700000);
                  
        set_temp("apply/attack", 70);
        set_temp("apply/damage", 70);
        set_temp("apply/armor", 70);
        set_temp("apply/defence",70);

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




int hit_ob(object me, object ob, int damage)
{
   if( random(damage) > (int)ob->query_temp("apply/armor")
	&&	(int)ob->query_condition("snake_poison") < 10 ) {
		ob->apply_condition("snake_poison", 30);
        tell_object(ob, HIG "����ñ�ҧ�еĵط�һ��������\n" NOR );
	}
}