/***************会员系统命令接口*******************************
 Create by Rcwiz for HERO 2003
************************************************************/

#include <ansi.h>
 
#define MEMBER_D         "/adm/daemons/memberd"
#define GOODS_D          "/adm/daemons/goodsd"
int paying;
int help(object me);
int help2(object me);

int main(object me, string arg)
{
          string str1, str2;
          object tar;
          string me_id, tar_id;
          int amount;

          if (time() - me->query_temp("last_member") < 5 
              && arg != "?" 
              && ! wizardp(me))
                return notify_fail("系统忙，请稍后再试！\n");
          
          if (arg != "?" && ! wizardp(me))me->set_temp("last_member", time());
          
          // 仅允许非会员使用member ?, member ??,member pay, member stats, member show goods指令
          if (! MEMBER_D->is_member(me->query("id")))
          {
                if (! arg)return 0;
                if (arg == "?")return help2(me);
                if (arg == "??")return help(me);
                if (arg == "stats")
                {
                	me->add_temp("last_member", 5);
                	return MEMBER_D->show_all_members(0);
                }
                if (sscanf(arg, "%s %s", str1, str2) != 2)
                       return 0;

                if (str1 != "pay" &&
                    (str1 != "show" || str2 != "goods") )return 0;
          }

          if (! arg)
          {
                MEMBER_D->show_member_info(me->query("id"), "info", me);
                return 1;
          }

          if (arg == "?")return help2(me);
          if (arg == "??")return help(me);
          if (arg == "stats")
          {
          	return MEMBER_D->show_all_members(0);
          }
          if (sscanf(arg, "%s %s", str1, str2) != 2)return help(me);

          switch(str1)
          {
                case "show":
                    if (str2 == "info")
                    {
                         MEMBER_D->show_member_info(me->query("id"), "info", me);
                         return 1;
                    }
                    else if (str2 == "payinfo")
                    {
                         MEMBER_D->show_member_info(me->query("id"), "payinfo", me);
                         return 1;
                    }
                    else if (str2 == "buyinfo")
                    {
                         MEMBER_D->show_member_info(me->query("id"), "buyinfo", me);
                         return 1;
                    }
                    else if (str2 == "goods")
                    {
                         MEMBER_D->show_member_info(me->query("id"), "goods", me);
                         return 1;
                    }
                    else if (str2 == "zhuaninfo")
                    {
                         MEMBER_D->show_member_info(me->query("id"), "zhuaninfo", me);
                         return 1;
                    }
                    else return help(me);

                case "pay":
                    if (paying)
                    {
                          write(HIG "系统忙请稍后再试！\n" NOR);
                          return 1;
                    }
                    paying = 1; // 同一时间只能一个会员充值
                    if(! MEMBER_D->pay(me, str2))
                          write("充值失败，可能由于注册码错误，或者因为其他异常原因导致！\n");
                    paying = 0;
                    return 1;

                case "buy":
                    if (! GOODS_D->buy_goods(me->query("id"), str2, me))
                    {
                          write("购买失败！\n");
                          return 1;
                    }
                    write("Successful!\n");
                    return 1;

                case "zhuan":
                    if (sscanf(str2, "%s:%d", tar_id, amount) != 2)return help(me);
                    me_id = me->query("id");
                    if (me_id == tar_id)return notify_fail("你白痴啊，给自己转帐！\n");

                    if (! MEMBER_D->virement_yhb(me_id, tar_id, amount, me))
                    {
                          write("转帐失败！\n");
                          return 1;
                    }
                    write("Successful!\n");
                    return 1;

                case "check":
                    if (wiz_level(me) < 4)
                          return help(me);
                    
                    // 检查对方是否为会员
                    if (! MEMBER_D->is_member(str2))
                          return notify_fail("目标为非会员，无法查询！\n");
                   
                    tar = UPDATE_D->global_find_player(str2);
                    if (! objectp(tar))return notify_fail("没有这个玩家！\n");
                    
                    MEMBER_D->show_member_info(str2, "info", tar);

                    UPDATE_D->global_destruct_player(tar, 1);

                    return 1;
     
                case "remove":
                    if (wiz_level(me) < 5)return help(me);
                             
                    if (! MEMBER_D->remove_member(str2))
                    {
                         write("删除会员失败！\n");
                         return 1;
                    }
                    write("OK.\n");
                    return 1;

                default:     return help(me);
          }

          return 1;
}

int help (object me)
{
	write(@HELP

指令格式 : member show [info | payinfo | buyinfo | zhuaninfo | goods]
           member pay 注册码             交纳会费(充值) 
           member buy 物品代号           购买物品
           member check id               检查会员信息
           member stats                  列出所有的会员
           member zhuan id:amount        YHB转帐
           member ??                     member 指令帮助
           member ?                      炎黄会员系统简明向导

member zhuan id:amount 说明：
     1、注意格式，id为对方id，对方必须是有效会员。
     2、amount是转帐金额。
     3、id和amount之间必须用“:”符号隔开。
     4、转帐的本人也必须为有效会员。
     5、每次转帐将扣除转帐金额的百分之三(%3)。
如：欲转帐“1000YHB”到“rcwiz”，指令为：
          
     member zhuan rcwiz:1000      即可。

info    : 显示会员系统面板
payinfo : 显示历史充值交费信息
buyinfo : 显示历史购买物品信息
goods   : 显示英雄商店出售的物品

member check id 为arch以上巫师使用参数。

相关参考文件：help member

HELP );
        return 1;
}

int help2(object me)
{
    
    write(BBLU + HIW "                      炎黄会员系统简明向导\t              \n" NOR);
    write(HIW "---------------------------------------------------------------\n\n" NOR);
    write(HIY "⒈会员待遇：档案定期手动备份、数据安全性、计划练功增加经验和潜能、\n"
              "  赚取炎黄货币、使用炎黄货币购买物品、使用最新的转世系统、组队任\n"
              "  务系统、总坛攻打系统、特殊故事、自创武功以及享受本站后续开发内\n"
              "  容等。\n\n" NOR);
    write(HIY "⒉如何成为会员：您只需每月（31天）交纳人民币28元即可获得一条注册\n"
              "  码，并使用 " HIR "member pay 注册码" HIY " 即可充值成为会员或续交会费。\n\n" NOR);
    write(HIY "⒊充值过程：\n" HIW
"**********************************************************************************************\n\n"HIG
" 汇款并用email和msg---->admin确认--(通过)-->admin发送注册码---->充值--(成功)--->系统记录充值信 \n"
" 通知admin， 须写明        ↓               到您的msg信箱               ↓      息并修改相应数 \n" 
" 汇款时间、实际到帐        ↓                ∧                         ↓      据             \n"
" 金额、本人欲加入会     (有差错)            /                         (失败)                    \n"
" 员的ID                    ↓              /                            ↓                      \n"
"                    (出示汇款凭证核实)--(通过)                     妥善保存注册码并              \n"
"                           ↓                                      及时告知admin                 \n"
"                    (不能出示有效凭证)                                  ↓                      \n"
"                           ↓                                           ↓                      \n"
"                       视为未汇款                                  admin及时解决                \n\n" HIW
"************************************************************************************************\n\n" NOR);

    write(HIY "⒋如何汇款：请参见帮助文件 " HIR "help member" HIY " 中的" HIR "【加入会员】" HIY "项。\n\n" NOR);
    write(HIY "欲了解更多信息请参见帮助文件 " HIR "help member" HIY " 或与之相关的链接文件。\n\n" NOR);
    write(HIM "                     皇朝再现 舍我其谁 | YΨH炎黄英雄史 巫师组 \n" NOR);
    write(HIW "---------------------------------------------------------------\n\n" NOR);
    return 1;
}