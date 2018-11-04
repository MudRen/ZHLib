// /guanwai/houyuan.c

inherit ROOM;

void create()
{
    set("short", "后院");
    set("long", @LONG
这是胡家的后院，虽然不大，但是收拾得颇为整齐利落，看来是有人常
用心打扫的缘故。东面隐隐的传来打斗声，西面静一些。而北面则飘来阵阵
饭香。
LONG );
    set("exits", ([
        "south" : __DIR__"xiaowu",
        "north" : __DIR__"chufang",
        "east"  : __DIR__"liangong",
        "west"  : __DIR__"jingxiu",
    ]));
    set("outdoor", "guanwai");
    setup();
}
