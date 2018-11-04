// ITEM Made by player(Ó°Îè:shadow) /data/item/s/shadow-zhou.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Thu May  3 07:46:32 2001
#include <ansi.h>
#include <weapon.h>

inherit SWORD;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;31m´óÈÕ[1;33mÈçÀ´[1;31mÖä[2;37;0m", ({ "zhou" }));
	set_weight(15000);
	set("item_make", 1);
	set("unit", "±ú");
	set("long", "ÕâÊÇÓÉ[1;35mÉñÌú[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»±ú½£¡£
[1;33mÈçÀ´·ğ×æ[1;37mÊ¹ÓÃ¹ı£¬ÒÅÂäÓÚ·²¼äµÄ[1;31mÉñÆ÷[1;37m¡£[2;37;0m
½£±úÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ºÓ°Îè(shadow)
");
	set("value", 2100000);
	set("point", 117);
	set("materail", "magic stone");
	set("wield_msg", "[1;31m´óÈÕ[1;33mÈçÀ´[1;31mÖä[1;37mÆ¾¿Õ³öÏÖÓÚ[1;36m$N[1;37mÊÖÖĞ£¬ËÄÖÜ¿ÕÆø±äµÃÒì³£ÄıÖØ¡£[2;37;0m\n");
	set("unwield_msg", "[1;37m¿ÕÆøÍ»È»±äµÃ²»ÄÇÃ´Ñ¹ÒÖ£¬Ô­À´[1;31m´óÈÕ[1;33mÈçÀ´[1;31mÖä[1;37mÔÙÒ»´ÎÏûÊ§ÔÚ[1;36m$N[1;37mÊÖÖĞ¡£[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	init_sword(apply_damage());

	setup();
}

string long() { return query("long") + item_long(); }
