// square.c

inherit ROOM;

void create()
{
        set("short", "�㳡");
	set("long", @LONG
�����ǻ�ɽ����ɽ�����ٵ�һ��ƽ̨��ƽʱ�ۻ��ʱ��ʹ�á���Ȼ��
��ȴ��ƽ��������ͨ�����䳡�������ǻ�ɽ������ϰ����ĵط���������
�������ַǷ��������и�С�ꡣͨ�������໪ɽ�ɵ����ڴ���Щ��Ʒ����
�ߵķ������Ϲ���һ���ң����顸Ⱥ�ɹۡ����������ƺ�����С��ͨ��ɽ
�ϡ�
LONG );
        set("exits", ([ /* sizeof() == 2 */
	    "northeast" : __DIR__"wuchang1",
            "northwest" : __DIR__"chaopath1",
            "south"     : __DIR__"yunu",
            "north"     : __DIR__"qunxianguan",
            "west"      : __DIR__"shop",
            "east"      : __DIR__"bingqifang",
        ]));

        set("outdoors", "huashan" );

        setup();
}
 