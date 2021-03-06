// /kungfu/class/xueshan/baoxiang.c  宝象
// by secret

inherit NPC;
inherit F_MASTER;
inherit F_GUARDER;

#include <ansi.h>
#include "xuedao.h"

void create()
{
        set_name("宝象", ({ "bao xiang", "bao", "xiang" }));
        set("long",@LONG
一个极高极瘦的僧人，俩眼凶芒四射。此人在血刀老祖门下，最是心狠手辣。
LONG
        );
        set("title",HIR "血刀门第五代弟子" NOR);
        set("gender", "男性");
        set("age", 35);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 22);
        set("int", 21);
        set("con", 24);
        set("dex", 22);
        set("max_qi", 5000);
        set("max_jing", 2500);
        set("neili", 2800);
        set("max_neili", 2800);
        set("jiali", 30);
        set("combat_exp", 250000);

        set_skill("lamaism", 50);
        set_skill("literate", 90);
        set_skill("force", 130);
        set_skill("parry", 110);
        set_skill("blade", 125);
        set_skill("dodge", 100);
        set_skill("mizong-neigong", 130);
        set_skill("shenkong-xing", 100);
        set_skill("hand", 110);
        set_skill("dashou-yin", 110);
        set_skill("cuff", 100);
        set_skill("yujiamu-quan", 100);
        set_skill("xue-dao", 125);

        map_skill("force", "mizong-neigong");
        map_skill("dodge", "shenkong-xing");
        map_skill("hand", "dashou-yin");
        map_skill("cuff", "yujiamu-quan");
        map_skill("parry", "xue-dao");
        map_skill("blade", "xue-dao");

        prepare_skill("cuff", "yujiamu-quan");
        prepare_skill("hand", "dashou-yin");

        create_family("血刀门", 5, "弟子");
        set("class", "bonze");

	set("coagents", ({
		([ "startroom" : "/d/xuedao/shandong3",
		   "id" : "xuedao laozu" ]),
	}));

        setup();
        carry_object("/d/xueshan/obj/y-jiasha")->wear();
        carry_object("/clone/weapon/gangdao")->wield();

}

void attempt_apprentice(object ob)
{
        command("say 对不起，本门暂不开放。");
        return;
        if (! permit_recruit(ob))
                return;

        if (ob->query("class") != "bonze")
        {
                ob->set_temp("pending/join_bonze", 1);
                command("say 你不是出家人，我们血刀门是不会收留的。"
                        "如果你要出家，请找善勇师侄。");
                return;
        }

        if ((string)ob->query("gender") != "男性")
        {
                command("say 我不收女徒弟。\n");
                return;
        }

        if (ob->query("shen") > 0)
        {
                command("say 我正想找你们侠义道的晦气。\n");
                this_object()->kill_ob(ob);
                return;
        }

        if ((int)ob->query_skill("lamaism", 1) < 30)
        {
                command("say 入我血刀门，修习密宗佛法是首要的。\n");
                return;
        }

        if ((int)ob->query_skill("force") < 60)
        {
                command("say 你这个笨蛋！怎么不先把内功练好！\n");
                return;
        }

        command("recruit " + ob->query("id"));
}
