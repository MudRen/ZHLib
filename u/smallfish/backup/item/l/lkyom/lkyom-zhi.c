// ITEM Made by player(·ç¼ä»ğÔÂ:lkyom) /data/item/l/lkyom-zhi.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Fri Jun  8 19:59:02 2001
#include <ansi.h>
#include <armor.h>

inherit HANDS;
inherit F_ITEMMAKE;

void create()
{
	set_name("Ö¸Ì×[2;37;0m", ({ "zhi" }));
	set_weight(20000);
	set("item_make", 1);
	set("unit", "Ì×");
	set("long", "ÕâÊÇÓÉ[1;35mÉñÌú[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»Ì×Ö¸Ì×¡£
Ö¸Ì×ÔµÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£º·ç¼ä»ğÔÂ(lkyom)
");
	set("value", 2100000);
	set("point", 139);
	set("materail", "magic stone");
	set("wear_msg", "[33m$N[33m×°±¸Ö¸Ì×[2;37;0m[33m¡£[2;37;0m\n");
	set("remove_msg", "[33m$N[33mÍÑÏÂÁËÖ¸Ì×[2;37;0m[33m¡£[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", 10);
	set("armor_prop/unarmed_damage", apply_damage());
	set("armor_prop/claw", 10);
	set("armor_prop/finger", 10);

	setup();
}

string long() { return query("long") + item_long(); }
