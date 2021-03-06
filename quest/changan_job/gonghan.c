//小布包
//配合趣味任务埋宝画图任务的道具


#include <ansi.h>
inherit ITEM;

int is_bag() { return 1; }

void create()
{
        set_name(NOR + HIY "小布包" NOR, ({ "bag" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "个");
                set("long", "这是一个小布包，里面不知道裹着什么。\n");
                set("value", 0);
                set("no_drop", "这样东西不能离开你。\n");
                  set("no_put", "这样东西不能离开你。\n");
                  set("no_sell", "这样东西不能离开你。\n");
        }
        setup();
}

void init()
{
     add_action("do_open","open");
     add_action("do_bury","bury");
}

int do_open( string arg )
{

    if ( !arg || arg != "bag")
    return notify_fail("你要打开什么？\n");

    write(HIR"别人的东西你就这么打开不太好吧？"
             "还是遵守诺言去把它埋了(bury)吧！\n"NOR);
    return 1;

}

int do_bury( string arg )
{
    object me = this_player();

    if ( !arg || arg != "bag")
    return notify_fail("你到底要埋什么东西呀？\n");

    if ( me->query("xquest/kind") != "do_drawing" )
    return notify_fail("好像没人要你埋这布包呀？\n");

    if ( me->query("xquest/buried") == 1 )
    return notify_fail("你这之前不是已经埋过一个布包了吗？\n");

    if ( me->query("xquest/place2") != environment(me)->short() )
    return notify_fail("你刚想动手埋布包，却突然发现这里不是" +
                       me->query("xquest/init_npc") + "说的地方，只好作罢。\n");

    message_vision(CYN "$N" CYN "鬼鬼祟祟地朝四周张望了几下，眼见着没啥人注意\n"
                   "随即迅速掏出一个小布包匆匆忙忙埋到了地里。\n"NOR,
                    me);
    me->start_busy(4);
    me->set("xquest/buried", 1);

    destruct(this_object());

    return 1;

}
