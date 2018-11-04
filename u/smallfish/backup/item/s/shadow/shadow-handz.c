// ITEM Made by player(Ó°Îè:shadow) /data/item/s/shadow-handz.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Thu May 10 08:53:44 2001
#include <ansi.h>
#include <armor.h>

inherit HANDS;

void create()
{
	set_name("ÌúÊÖÕÆ[2;37;0m", ({ "handz" }));
	set_weight(20000);
	set("item_make", 1);
	set("unit", "Ë«");
	set("long", "ÕâÊÇÓÉ[1;35mÉñÌú[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»Ë«ÌúÕÆ¡£
ÕâÊÇÒ»¿éÌúÖÊµÄÊÖÕÆĞÎ»¤¾ß£¬ÓÃÒÔ±£»¤ÊÖÕÆ¡£[2;37;0m
ÌúÕÆÔµÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ºÓ°Îè(shadow)
");
	set("value", 2100000);
	set("point", 123);
	set("materail", "magic stone");
	set("wear_msg", "[33m$N´÷ÉÏÒ»¿éÌúÊÖÕÆ¡£[2;37;0m\n");
	set("remove_msg", "[33m$NĞ¶ÌúÊÖÕÆµÄ×°±¸¡£[2;37;0m\n");
	set("armor_prop/strike", 10);
	set("armor_prop/hand", 10);
	set("armor_prop/armor", 10);

	setup();
}

