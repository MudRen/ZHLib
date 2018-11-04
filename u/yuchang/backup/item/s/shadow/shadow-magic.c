// ITEM Made by player(Ó°Îè:shadow) /data/item/s/shadow-magic.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Mon Jul 23 20:49:56 2001
#include <ansi.h>
#include <armor.h>

inherit CLOTH;
inherit "/feature/mingren_itemmake.c";

void create()
{
	set_name("[1;32mÌìÏãÓñÂ¶[2;37;0m", ({ "magic" }));
	set_weight(1400);
	set("item_make", 1);
	set("unit", "ÕÅ");
	set("long", "ÕâÊÇÓÉ[1;37m±ù²ÏË¿[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»ÕÅ¼×¡£
[1;32mÕâÊÇ¸½×ÅÔÚÁéÖ¥ÉÏµÄÒ»µÎ¾§Ó¨ÌŞÍ¸µÄÓñÂ¶£¬´«Ëµ²É×Ô
ÁéÉ½£¬Ç§ÄêÀ´ÒÔÁéÖ¥ÎªÄ¸£¬²»¶ÏµÄÎüÈ¡×ÅÈÕ¾«ÔÂ»ª£¬
¾ßÓĞ×ÅÎŞ±ÈÉñÆæµÄ¹¦Ğ§¡£[2;37;0m
¼×ÔµÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ºÓ°Îè(shadow)
");
	set("value", 2100000);
	set("point", 173);
	set("materail", "silk");
	set("wear_msg", "$NÄÃ³öÒ»µÎ$n£¬ÎÕÔÚÊÖÖĞ¡£[2;37;0m\n");
	set("remove_msg", "$NÄã°Ñ$nÊÕ»Ø°üÄÒ¡£[2;37;0m\n");
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return query("long") + item_long(); }
