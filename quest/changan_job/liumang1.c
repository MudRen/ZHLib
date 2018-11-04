
#include <ansi.h>
inherit NPC;

mapping *data=({
(["name":"��å", "id":"liu mang",]),
(["name":"���", "id":"hun hun",]),
(["name":"����", "id":"dao zei",]),
(["name":"ǿ��", "id":"qiang dao",]),
(["name":"С͵", "id":"xiao tou",]),
});

void create()
{
	mapping npc;
       npc=data[random(sizeof(data))];
	set_name(npc["name"],({ npc["id"] }));
	set("gender", "����");
	set("age", 19);
	set("long", "������ü���ۣ�һ�������˾��÷Ǽ鼴�������϶�ֻ�Ǹ�С��졣\n");
	
	set("combat_exp", 1000);
	set("shen_type", -1);

	set("attitude", "peaceful");
	
	set_skill("unarmed", 20);
	set_skill("dodge", 20);
	set_temp("apply/attack", 10);
	set_temp("apply/defense", 10);

	setup();
	carry_object("/clone/misc/cloth")->wear();	
}

void init()
{
        object me, ob;

        ::init();
        if (! interactive(me = this_player()))
                return;

        add_action("do_agree", "agree");
        add_action("do_disagree", "disagree");

        remove_call_out("disappear");
        call_out("disappear", 30);

        remove_call_out("runaway");
        call_out("runaway", 360);
}

void lost()
{
    object ob, me;
    ob = this_object();
    me = ob->query_temp("last_opponent");
    if ( ! ob->query("owner") && 
         me->query("changanjob/kind") == "patrol")
    {
        ob->set("owner", me );
        ob->set_leader(me);
        me->set("changanjob/catch", ob);
        me->add("changanjob/catch_num",1);
        message_vision(CYN"$N��$n˵������ʵ�㣬��������ȥ��������������Ƥ���ܿ࣡\n"
                       "$n���ε���������Ȼ������������Ҳ�޻���˵�����뽫�Ҵ��ᷢ�䡣\n"NOR
                       "$n��ʼ����$N�ж���\n", me, ob);
        
    }

} 

void win() 
{
        object ob = this_object();
        message_vision(CYN"$N��Ц�����������Ҳ��׽������ȥ������ʮ��ɣ�"
                       "��ү�ҿ�û���������濩��\n˵��$N��ವ�һ�����ˡ�\n",ob);
        destruct(ob);
}

void disappear()
{
        object ob = this_object();

        // û��ץ�Ļ��ܿ����ʧ
        if (living(ob) && ! ob->query("owner")
            && ! ob->is_busy() && ! ob->is_fighting() )
        {
                message_vision(WHT "$N������һת���͵�һ������˲���"
                               "�ӵ���Ӱ���١�\n\n", ob);
                destruct(ob);
        }
}

void runaway()
{
        object ob = this_object();

        // ʱ�䵽�˱���ʧ
        if (living(ob) && ! ob->is_busy() && ! ob->is_fighting() )
        {
                message_vision(WHT "\n$Nһ������û�ˣ�ವ�һ�������Ӱ���١�\n\n", ob);
                destruct(ob);
        }
}


void unconcious() 
{ 
        die(); 
} 