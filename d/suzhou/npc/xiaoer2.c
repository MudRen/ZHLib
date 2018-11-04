// xiaoer2.c �Ƶ�С��

inherit KNOWER;
inherit F_DEALER;

void create()
{
	set_name("��С��", ({ "xiao er", "xiao", "waiter" }) );
	set("gender", "����" );
	set("age", 22);
	set("long",
		"��λ��С����Ц�����æ��������ʱ������ڲ����ϵ�Ĩ��������\n");
	set("combat_exp", 100);
	set("attitude", "friendly");
	set("no_get", "0");
	set("rank_info/respect", "С����");
	set("vendor_goods", ({
		__DIR__"obj/xiaren",
		__DIR__"obj/huotui",
		__DIR__"obj/soup",
	}));
	setup();
	carry_object("/clone/misc/cloth")->wear();
}

void init()
{	
	object ob; 
	mapping myfam; 

	ob = this_player();

	::init();
	if( interactive(ob) && !is_fighting() ) {
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}

	add_action("do_buy", "buy");
	add_action("do_list", "list");
}

void greeting(object ob)
{
	if( !ob || environment(ob) != environment() ) return;
	switch( random(2) ) {
		case 0:
			say( "��С��Ц�����˵������λ" + RANK_D->query_respect(ob)
				+ "�������ȱ��裬ЪЪ�Ȱɡ�\n");
			break;
		case 1:
			say( "��С���ò����ϵ�ë��Ĩ��Ĩ�֣�˵������λ" + RANK_D->query_respect(ob)
				+ "����������\n");
			break;
	}
}
