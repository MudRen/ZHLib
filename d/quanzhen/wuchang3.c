// wuchang2.c �䳡
// By Lgg,1998.10

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "�䳡");
        set("long", @LONG
������ȫ��̵����䳡�����µ���ש�����̵��������룬ȴ
��֪����˭�ȳ��˼�ʮ�����СС�İ��ӡ����ĳ������������
���µ��е��������Ʒ��������쳤�վã����¾Ͳȳ��˰��ӡ���
���������ż��������õ�ľ�ˡ�
LONG
        );
        set("outdoors", "quanzhen");
        set("exits", ([
                "north" : __DIR__"wuchang2",
        ]));

        set("objects", ([
                "/clone/npc/mu-ren" : 3,
        ]));

        setup();
        replace_program(ROOM);
}