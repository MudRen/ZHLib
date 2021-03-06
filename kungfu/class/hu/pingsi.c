// pingsi.c
#include <ansi.h>;

inherit NPC;
inherit F_MASTER;

void create()
{
    set_name("平四", ({"ping si", "ping"}));
    set("gender", "男性");
    set("age", 65);
    set("long", "他是胡家忠心耿耿的仆役。\n");
    set("attitude", "peaceful");
    set("str", 20);
    set("int", 20);
    set("con", 24);
    set("dex", 20);

    set("qi", 4000);
    set("max_qi", 4000);
    set("jing", 1000);
    set("max_jing", 1000);
    set("neili", 3000);
    set("max_neili", 3000);
    set("combat_exp", 150000);

    set_skill("force", 100);            // 基本内功
    set_skill("lengyue-shengong", 100); // 冷月神功
    set_skill("blade", 100);            // 基本刀法
    set_skill("zijinbagua-dao", 80);      // 胡家刀法
    set_skill("dodge", 100);            // 基本躲闪
    set_skill("taxue-wuhen", 100);      // 踏雪无痕
    set_skill("parry", 100);            // 基本招架
    set_skill("strike", 100);           // 基本掌法
    set_skill("tianchang-zhang", 100);  // 天长掌法
    set_skill("cuff", 100);             // 基本拳法
    set_skill("hujia-quan", 100);       // 胡家拳法

    map_skill("force", "lengyue-shengong");
    map_skill("blade", "zijinbagua-dao");
    map_skill("dodge", "taxue-wuhen");
    map_skill("parry", "zijinbagua-dao");
    map_skill("strike", "tianchang-zhang");
    map_skill("cuff", "hujia-quan");

    prepare_skill("strike", "tianchang-zhang");
    prepare_skill("cuff",   "hujia-quan");

    create_family("关外胡家", 8, "传人");

    set("inquiry",([
        "阎基":     "阎基... 这个狗贼。\n",
        "胡一刀":   "那，那是老主人，唉！\n",
        "苗人凤":   "苗大侠可不是坏人。\n",
        "赵半山":   "他对我家主人的交情那是没得说的。 \n",
    ]));

    setup();

    set("title", "胡家仆佣");
    carry_object("/clone/cloth/cloth")->wear();
}

void attempt_apprentice(object ob)
{
    object me;

    me = this_object();

    if (ob->query("detach/关外胡家") ||
        ob->query("betrayer/times"))
    {
        message_vision("$N摇摇头对$n说：你反复无常，我不能收你为徒！\n",
                       me, ob);
        return;
    }

    if( ob->query("born_family") != "关外胡家" && 
        ob->query("can_not_change") &&
        !ob->query("tianmo_jieti/times") )
    {

        message_vision("$N对$n道：你不是我们胡家的人，我怎能收你为徒？\n",
                       me, ob);
        return 0;

    }


    if (ob->query("family/family_name") &&
        ob->query("family/family_name") != me->query("family/family_name"))
    {
        message_vision("$N对$n道：你虽然是胡家的人，但你入了其他门派，我不能收你为徒！\n",
                       me, ob);
        return;
    }

    if (ob->query("purename") == "一刀")
    {
        message_vision("$N大怒：你取这个名字是什么意思？\n", me);
        return;
    }

    if (ob->query("purename") == "斐")
    {
        message_vision("$N大怒：他奶奶的！你取这个名字是什么意思？\n", me);
        return;
    }

    message_vision("$N感叹道：我们胡家还要靠你们来发扬光大啦！\n",
                   me, ob);
    command("recruit " + ob->query("id"));
    return;
}

