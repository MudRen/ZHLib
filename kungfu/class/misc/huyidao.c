// huyidao.c 胡一刀

#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
        set_name("胡一刀", ({ "hu yidao", "yidao" }));
        set("long",  "绝世刀王胡一刀，据传刀法已经臻至天刀境界，此人嫉恶如仇，豪气万千。\n");
        set("gender", "男性");
        set("age", 65);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 32);
        set("int", 33);
        set("con", 32);
        set("dex", 31);
        
        set("max_qi", 9999);
        set("max_jing", 9999);
        set("neili", 9999);
        set("max_neili", 9999);
        set("jiali", 300);
        set("combat_exp", 10000000);
        set("score", 10000000);

    set_skill("force", 710);            // 基本内功
    set_skill("lengyue-shengong", 710); // 冷月神功
    set_skill("blade", 640);            // 基本刀法
    set_skill("hujia-daofa", 640);      // 胡家刀法
    set_skill("dodge", 640);            // 基本躲闪
    set_skill("taxue-wuhen", 640);      // 踏雪无痕
    set_skill("parry", 620);            // 基本招架
    set_skill("throwing", 640);         // 基本暗器
    set_skill("mantian-xing", 640);     // 满天星
    set_skill("strike", 680);           // 基本掌法
    set_skill("tianchang-zhang", 680);  // 天长掌法
    set_skill("cuff", 680);             // 基本拳法
    set_skill("hujia-quan", 680);       // 胡家拳法

    map_skill("force", "lengyue-shengong");
    map_skill("blade", "hujia-daofa");
    map_skill("dodge", "taxue-wuhen");
    map_skill("parry", "hujia-daofa");
    map_skill("throwing", "mantian-xing");
    map_skill("strike", "tianchang-zhang");
    map_skill("cuff", "hujia-quan");

    prepare_skill("strike", "tianchang-zhang");
    prepare_skill("cuff",   "hujia-quan");

    create_family("关外胡家", 0, "刀王");

    setup();
    carry_object("/d/guanwai/obj/lengyue")->wield();
    carry_object("/clone/cloth/cloth")->wear();
}


