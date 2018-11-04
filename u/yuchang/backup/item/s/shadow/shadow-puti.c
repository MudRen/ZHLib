// ITEM Made by player(Ó°Îè:shadow) /data/item/s/shadow-puti.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Thu May 17 02:18:55 2001
#include <ansi.h>
#include <weapon.h>

inherit DAGGER;
inherit F_MINGREN_ITEMMAKE;

void create()
{
	set_name("[1;32mÆĞÌá×Ó[2;37;0m", ({ "puti" }));
	set_weight(15000);
	set("item_make", 1);
	set("unit", "Ö§");
	set("long", "ÕâÊÇÓÉ[1;35mÉñÌú[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»Ö§¶Ì±ø¡£
[1;32mÕâÊÇÒ»¿Å¾§Ó¨ÈçÓñµÄÆĞÌá×Ó£¬²É×ÔÁéÉ½·ğ×æ×ùÇ°£¬ÕäÏ¡ÎŞ±È£¬
ÄËÍòÄêÆĞÌáÊ÷Ö®Êµ£¬¹¦ÄÜ»¯°Ù½Ù£¬¶ÉÇ§ÔÖ£¬ÓëÌìµØÍ¬ÊÙ¡£[2;37;0m
¶Ì±ø±úÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ºÓ°Îè(shadow)
");
	set("value", 2100000);
	set("point", 136);
	set("materail", "magic stone");
	set("wield_msg", "$NÄÃ³öÒ»¿Å[1;32mÆĞÌá×Ó[2;37;0m£¬ÎÕÔÚÊÖÖĞ¡£[2;37;0m\n");
	set("unwield_msg", "$N°Ñ[1;32mÆĞÌá×Ó[2;37;0mÊÕ»Ø°üÄÒ¡£[2;37;0m\n");
	restore();
	init_dagger(apply_damage());

	setup();
}

string long() { return query("long") + item_long(); }
