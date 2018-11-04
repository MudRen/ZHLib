// indian.c ӡ�ȸ���

#include <ansi.h>

inherit CHALLENGER;

void create()
{
        set_name("������", ({ "indian" }));
	set("long", "һ�������ˣ����÷ǳ���С��\n");
	set("gender", "����");
	set("age", 20);
	set("str", 20);
	set("int", 20);
	set("con", 20);
	set("dex", 20);

        // the follow 5 setting has no use
	set("max_qi", 100);
	set("max_jing", 100);
	set("neili", 100);
	set("max_neili", 100);
	set("jiali", 100);
        set("shen", -1000);

	set("combat_exp", 3000000);
        set("scale", 100);

	set_skill("force", 1);
        set_skill("yujiashu", 1);
	set_skill("dodge", 1);
        set_skill("yujiashu", 1);
	set_skill("parry", 1);
        set_skill("finger", 1);
        set_skill("nianhua-zhi", 1);
        set_skill("strike", 1);
        set_skill("sanhua-zhang", 1);

        map_skill("finger", "nianhua-zhi");
        map_skill("strike", "sanhua-zhang");
        map_skill("force", "yujiashu");
        map_skill("dodge", "yujiashu");
        map_skill("parry", "nianhua-zhi");

        prepare_skill("strike", "sanhua-zhang");
        prepare_skill("finger", "nianhua-zhi");

        set("class", "bonze");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
                (: perform_action, "finger.fuxue" :),
                (: perform_action, "strike.sanhua" :),
        }));

        set_temp("apply/strike", 50);
        set_temp("apply/finger", 50);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/parry", 50);
        set_temp("apply/dodge", 50);
        set_temp("apply/force", 50);

        set("chat_lost", "������ѧ���������鴫��");
        set("chat_win", "��...����������书��û��ѧ���ң����Ǹ��������ɡ�");

	setup();

        carry_object("/clone/cloth/seng-cloth")->wear();
}

string challenge()
{
        set("opinion/msg", ({
                (random(2) ? "������ͷ��С�������Ħ��ʦ�����������á�"
                           : "�������ø��֣�������������ͬԴ��"),
                (random(2) ? "ȥ����·;ңԶ��ʮ�����գ��������Ĵ��ǲ��ס�"
                           : "�������������������־�ѧ�׽�����ɴ˻�����"),
                (random(2) ? "������Ħ��ʦ�������ģ�������ʮ���������ʵ���Ƿ�ͬС�ɡ�"
                           : "���־��������������ѧʵ�ڲ���С�Ӱ���"),
        }));

        command(random(2) ? "bow" : "buddhi " + query("id"));
        switch (random(2))
        {
        case 0:
                return "����" + query("nation") + "��ʿ����Զ����"
                        "�������ģ��ص�����λ���������ѧ��";

        default:
                return "����" + query("nation") + "��" + name() + "����"
                       "��������λ���ָ��ִͽ̡�";
        }
}

void unconcious()
{
        command("say ������ѧ���������鴫������������\n");
        die();
}

void competition_with(object ob)
{
        command("say �ðɣ����ǾͱȻ��Ȼ������˺�����\n");
        ::competition_with(ob);
}

void lost()
{
        string *ob_list = ({
                "/clone/gift/xisuidan",
		"/d/shaolin/obj/puti-zi",
        });
        object ob;

        ob = new(ob_list[random(sizeof(ob_list))]);
        message_vision(HIY "$N" HIY "˫�ֺ�ʮ��̾������������ѧ���ǲ������" +
                       ob->query("unit") + ob->name() + HIY "������"
                       "����ѧ������ɣ�\n\n" NOR, this_object());
        ob->move(this_object(), 1);
        command("give " + ob->query("id") + " to " + query_competitor()->query("id"));
        ::lost();
}