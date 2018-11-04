// Room: /city/dangpu.c
// YZC 1995/12/04 

inherit AREA_ROOM;

void create()
{
	set("short", "当铺");
	set("long", @LONG
这是一家以买卖公平著称的当铺，一个五尺高的柜台挡在你的面前，
柜台上摆着一个牌子(paizi)，柜台后坐着唐老板，一双精明的上上下下
打量着你。
LONG );
	set("no_fight", 1);
	set("no_steal", 1);
	set("no_beg",1);
	set("item_desc", ([
		"paizi" : "公平交易\n
list        看货
sell        卖 
buy         买
pawn        典当
redeem      赎
value       估价
check       查询

",
	]));
	set("objects", ([
                __DIR__"npc/tang" : 1,
                __DIR__"npc/boss3" : 1,
	]));
	set("exits", ([
		"west" : __DIR__"nandajie1",
	]));
        set("area/ziyuan", "资金");

	setup();
}
