// ITEM Made by player(·ç¼ä»ğÔÂ:lkyom) /data/item/l/lkyom-poke.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Tue May  8 01:49:24 2001
#include <ansi.h>
#include <weapon.h>

inherit SWORD;
inherit F_ITEMMAKE;

void create()
{
	set_name("³¤½£[2;37;0m", ({ "poke" }));
	set_weight(15000);
	set("item_make", 1);
	set("unit", "±ú");
	set("long", "ÕâÊÇÓÉ[1;35mÉñÌú[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»±ú½£¡£
½£±úÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£º·ç¼ä»ğÔÂ(lkyom)
");
	set("value", 2100000);
	set("point", 118);
	set("materail", "magic stone");
	set("wield_msg", "[1;36m$N[1;36mÒ»ÉùÇåĞ¥£¬¶¶³öÒ»±ú[1;36m$n[1;36m¡£[2;37;0m\n");
	set("unwield_msg", "$NËæÊÖÒ»Ä¨£¬ÊÕÆğÁË$n¡£\n");
	if (! check_clone()) return;
	restore();
	init_sword(apply_damage());

	setup();
}

string long() { return query("long") + item_long(); }
