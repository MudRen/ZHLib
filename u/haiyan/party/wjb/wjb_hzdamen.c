//wjb_hzdamen.c

inherit ROOM;

void create()
{ 
        set("short", "无极帮杭州分舵");
        set("long",@LONG
这里是无极帮杭州分舵的大门前面，在江南一带，无极帮声势
浩大，气势不凡，成就了许多轰轰烈烈的大事。
LONG );
        set("outdoors", "xiangyang");
        set("exits", ([  
                "east"  :  __DIR__"road12",
                "west"  :  __DIR__"wjb_hzfb",
        ])); 
        set("objects", ([   
             "/d/xiangyang/npc/wjb-guard" : 2,   
        ]));
               
        setup();            
}

int valid_leave(object me, string dir) 
{ 
        if (objectp(present("shou wei", environment(me))) && dir == "west") 
        {
           if (! me->query_temp("good_wjb") && me->query("bang_good/name") != "无极帮")
               return notify_fail("守卫一把拦住你，朗声喝道：我无极帮怎由闲杂人等随便进出。\n"); 
           else
           {
              me->delete_temp("good_wjb");
              return ::valid_leave(me, dir);
           }
        }
        return ::valid_leave(me, dir); 
} 

