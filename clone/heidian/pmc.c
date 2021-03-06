#include <room.h>
#include <ansi.h>
#include <getconfig.h>

inherit ROOM;

int do_look(string arg);

void create()
{
    set("short", HIY"金色大厅"NOR);
    set("long", @LONG
这里是一个宽敞的大房间，刚一进来，满眼灿烂的金黄耀花了
你的双眼。看到这华丽绝伦的装饰，你吓得大气都不敢出。大厅最
前方是一张精美的大桌子，一把金色棰子静静的摆放在桌子上，富
甲天下站在桌子后面，犀利的眼光似乎要把你刺透，你不由感觉浑
身热血在沸腾。靠西的墙上，挂着一块牌子(paizi)，上面写着拍
卖规则和操作手册。靠东的墙上，挂着另一块牌子(board)，上面
写着巫师操作手册。
LONG );

    set("no_fight",1);
    set("no_beg",1);
    set("no_steal",1);

    set("objects", ([
        "/adm/npc/fjtx" : 1,
    ]));

    set("exits", ([
        "south"  : "/d/city/pm_restroom",
    ]));

    set("no_clean_up", 0);
    setup();
}

void init()
{
    add_action("do_look","look");
}

int do_look(string arg)
{
    int i;
    object pms;
    string msg;
    mapping *heidian_record;

    if (arg != "paizi" && arg != "board") return 0;

    if (!wizardp(this_player()) && arg == "board")
    {
        write("你不是巫师，看不清牌子上写的字。\n");
        return 1;
    }

    if (arg == "paizi")
    {
        msg = HIC + LOCAL_MUD_NAME() + HIY "黑店拍卖" HIC " 规则：\n"NOR;
        msg += HIC "-------------------------------------------------------------\n" NOR;
        msg += HIW "第一：请在拍卖开始时关闭一切公开频道；\n" NOR;
        msg += HIW "第二：请勿使用任何公开频道说任何话；\n"NOR;
        msg += HIW "第三：请勿随便使用emote；\n"NOR;
        msg += HIW "第四：请勿随便开口交谈，如需交谈，请使用"HIY"team talk"HIW"；\n"NOR;
        msg += HIW "第五：请勿使用任何方式骚扰其他竞拍者；\n"NOR;
        msg += HIW "第六：拍卖以钱多者胜，出价最高的玩家会获得黑店经营权；\n"NOR;
        msg += HIW "第七：每个竞拍者一次只能获得一个黑店的经营权；\n"NOR;
        msg += HIW "第八：任何违反上述规定的玩家，将给取消竞拍资格；\n"NOR;
        msg += HIW "第九：竞拍指令："HIY"jupai <加价黄金数目>"HIW"，缺省为加价100两黄金；\n"NOR;
        msg += HIW "第十：巫师保留全部解释权力。\n"NOR;
        msg += HIC "-------------------------------------------------------------\n" NOR;
    } else
    {
        msg = HIC + LOCAL_MUD_NAME() + HIY "黑店拍卖" HIC " 巫师操作手册：\n"NOR;
        msg += HIC "-------------------------------------------------------------\n" NOR;
        msg += HIW "第一：请在拍卖进程启动前确保已经初始化所有黑店（"HIY"cshshop"HIW"）；\n" NOR;
        msg += HIW "第二：启动拍卖进程指令："HIY"start [任意参数]"HIW"，不使用参数表示手工操作；\n"NOR;
        msg += HIW "第三：*拍卖某个黑店使用指令："HIY"paimai <黑店ID>"HIW"；\n"NOR;
        msg += HIW "第四：*由手工操作转为自动进程指令："HIY"autopaimai"HIW"；\n"NOR;
        msg += HIW "第五：查看拍卖情况指令："HIY"paimailist"HIW"；\n"NOR;
        msg += HIW "第六：取消|开放 玩家拍卖资格指令："HIY"unwelcome <id> [1|0]"HIW"，缺省为1；\n"NOR;
        msg += HIW "第七：*拍卖宣报价格以及落棰指令："HIY"qiao"HIW"；\n"NOR;
        msg += HIW "第八：*结束拍卖指令："HIY"finish"HIW"（必须在全部黑店全部拍卖完毕才能使用）；\n"NOR;
        msg += HIW "第九：其中带"HIY"*"HIW"的指令表示只有主持拍卖的巫师才能够使用；\n"NOR;
        msg += HIW "第十：主持巫师断线、离开、退线、发呆，拍卖将转化为自动进程。\n"NOR;
        msg += HIC "-------------------------------------------------------------\n" NOR;
    }
    write(msg);
    return 1;
}
