inherit AREA_ROOM;

void create()
{
	set("short", "成衣店");
	set("long", @LONG
这里是扬州名媛贵妇常到之处，现在也挤得凄凄惨惨，脂
粉横飞。因为这里卖的时尚，一直是她们最热衷的装扮。店主
是个很可人的小女孩，你认真一看，顿时发现满个店堂里的女
人加在一起，还不如她靓丽。
LONG );
	set("exits", ([
		"down" : __DIR__"zahuopu",
	]));
	set("objects", ([
                __DIR__"npc/zeng": 1,
                __DIR__"npc/boss7": 1,
	]));
	set("no_fight", 1);
	set("coor/x",10);
	set("coor/y",-10);
	set("coor/z",10);
        set("area/ziyuan", "布匹");
	setup();
	//replace_program(ROOM);
}

