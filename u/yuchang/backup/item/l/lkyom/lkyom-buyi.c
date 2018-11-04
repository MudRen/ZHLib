// ITEM Made by player(·ç¼ä»ğÔÂ:lkyom) /data/item/l/lkyom-buyi.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Wed May 16 14:55:28 2001
#include <ansi.h>
#include <armor.h>

inherit CLOTH;
inherit F_ITEMMAKE;

void create()
{
	set_name("²¼ÒÂ[2;37;0m", ({ "buyi" }));
	set_weight(1400);
	set("item_make", 1);
	set("unit", "ÕÅ");
	set("long", "ÕâÊÇÓÉ[1;37m±ù²ÏË¿[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»ÕÅ¼×¡£
¼×ÔµÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£º·ç¼ä»ğÔÂ(lkyom)
");
	set("value", 2100000);
	set("point", 128);
	set("materail", "silk");
	set("wear_msg", ".[2;37;0m\n");
	set("remove_msg", ".[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return query("long") + item_long(); }
