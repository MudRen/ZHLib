// longnv.c 小龙女
// 1998.9 by Lgg

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

#include <ansi.h>
#include "gumu.h"

string ask_yunv();
string ask_me();
string ask_zhen();

void create()
{
        set_name("小龙女", ({"long nv", "long"}));
        set("gender", "女性");
        set("age", 27);
        set("long",
                "她一生爱穿白衣，当真如风拂玉树，雪裹琼苞，兼之生性清冷，\n"
                "实当得起“冷浸溶溶月”的形容。\n");
        set("attitude", "friendly");

        set("str", 21);
        set("int", 30);
        set("con", 25);
        set("dex", 26);
        set("per",29);

        set("chat_chance_combat", 15);
        set("chat_msg_combat", ({
                (: exert_function, "recover" :),
                (: perform_action, "sword.he" :),
                (: perform_action, "sword.he" :),
                (: perform_action, "sword.ding" :),
                (: perform_action, "sword.ding" :),
        }) );

        set("chat_chance", 1);
        set("chat_msg", ({
                "小龙女喃喃道：“玉女剑与全真剑合壁，是可天下无敌。可是...哪里去找这一个人呢？”\n",
                "小龙女深深地叹了口气，转过头去。\n",
        }));

        set("qi", 3800);
        set("max_qi", 3800);
        set("jing", 1900);
        set("max_jing", 1900);
        set("neili", 4400);
        set("max_neili", 4400);
        set("jiali", 50);

        set("combat_exp", 1600000);
        set("score", 0);

        set_skill("force", 180);
        set_skill("yunv-xinfa", 180);
        set_skill("sword", 180);
        set_skill("yunv-jian", 180);
        set_skill("quanzhen-jian",170);
        set_skill("dodge", 180);
        set_skill("yunv-shenfa", 180);
        set_skill("parry", 180);
        set_skill("cuff", 160);
        set_skill("meinv-quan", 160);
        set_skill("strike", 160);
        set_skill("fireice-strike", 160);
            set_skill("hand", 180);
            set_skill("tianluo-diwang", 180);
        set_skill("literate", 130);
        set_skill("qufeng", 210);
	set_skill("medical", 200);
	set_skill("yunv-xinjing", 500);
        set_skill("throwing", 200);
        set_skill("yufeng-zhen", 200);

        map_skill("force", "yunv-xinfa");
        map_skill("sword", "yunv-jian");
        map_skill("dodge", "yunv-shenfa");
        map_skill("parry", "meinv-quan");
        map_skill("hand", "tianluo-diwang");
        map_skill("cuff", "meinv-quan");
        map_skill("strike", "fireice-strike");
        map_skill("throwing", "yufeng-zhen");

        prepare_skill("cuff", "meinv-quan");
        prepare_skill("strike", "fireice-strike");

        create_family("古墓派", 3, "弟子");

        set("book_count", 1);
        set("count", 1);
        set("yfzhen_count", 3);

        set("inquiry", ([
                "过儿" : "他就在正厅啊。",
		"剑"   : (: ask_me :),
                "玉女剑法" : "玉女剑法和全真剑法合壁，天下无敌！\n",
                "古墓派" : "我的林祖师爷爷本来和重阳先师是一对璧人，可是...\n",
                "玉女心经" : (: ask_yunv :),
                "玉蜂针" : (: ask_zhen :),
        ]) );

        set("env/wimpy", 40);
        setup();

        carry_object("/d/gumu/npc/obj/shunvjian")->wield();
        carry_object("/clone/cloth/baipao")->wear();

}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob) )
                return;

	if (ob->query("per") < 25)
	{
        	command("say 尊容实在不敢恭维，我看你还是算了吧。\n");
                return;
	}

        command("say 好吧，我就收下你这个徒弟了。\n");
	command("recruit " + ob->query("id"));
}

string ask_yunv()
{
        object me;
        object ob;
        mapping fam;

        me = this_player();
        if (! (fam = me->query("family")) ||
            fam["family_name"] != "古墓派")
                return RANK_D->query_respect(me) +
                "与本派毫无瓜葛，何以问起本派的心经？";

        if (this_player()->query_skill("yunv-xinfa", 1) < 15)
                return RANK_D->query_respect(me) +
                        "的玉女心法火候太浅，我不能将玉女心经交给你。";

        if (query("book_count") < 1)
                return "你来晚了，本派的玉女心经已经被人取走了。";

        add("book_count", -1);
        ob = new("/clone/book/yunvjing1");
        ob->move(me, 1);
        return "好吧，这本「玉女心经」给你了，你要好好看看。";
}

string ask_me()
{
        object ob;

        if (query("count") < 1)
                return "现在我手头也没有了。";

        add("count", -1);
        ob=new("/d/gumu/npc/obj/junzijian");
        ob->move(this_player(), 1);
        return "这柄君子剑就送给你吧。";
}

string ask_zhen()
{
        object me;
        object ob;
        mapping fam;

        me = this_player();
        if (! (fam = me->query("family")) ||
            fam["family_name"] != "古墓派")
                return RANK_D->query_respect(me) +
                "与本派毫无瓜葛，何以问起本派暗器？";

        if (me->query_skill("yufeng-zhen", 1) < 50)
                return RANK_D->query_respect(me) +
                        "的玉蜂针手法火候还不到家，拿了玉蜂针也没有什么用。";

        if (query("yfzhen_count") < 1)
                return "你来晚了，我手头的玉蜂针已经发完了。";

        add("yfzhen_count", -1);
        ob = new("/d/gumu/obj/yfzhen");
        message_vision("$N拿出一些玉蜂针递给$n。\n", this_object(), me);
        ob->move(me, 1);
        return "好吧，这些玉蜂针你先拿去用吧。";
}

void reset()
{
	set("book_count", 1);
        set("yfzhen_count", 2 + random(2));
}
