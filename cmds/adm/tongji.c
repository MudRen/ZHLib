// tongji.c 用于在线统计
 
inherit F_CLEAN_UP;
#include <ansi.h>

#define MORE_THAN 0
#define LESS_THAN 1
#define BETWEEN 0
#define OUTOF 1

void more_or_less(string para, string tar, int n_data, int flag);
void between_or_outof(string para, string tar, int less, int more, int flag);
void same_as(string para, string tar, string str_data, int n_data);

int main(object me, string arg)
{
        string para, cond, str_data, tar;
        int n_data, less, more;
        string* temp;

        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;

        if (! arg || sscanf(arg, "%s %s %s %s", para, tar, cond, str_data) != 4)
		return notify_fail("tongji < 参数 -sk|-para|-tpara > <对象变量> < 条件 <|==|>|between|outof > <统计值> \n");

        temp = explode(str_data, " ");

        if (sizeof(temp) == 1)
                sscanf(str_data, "%d", n_data);

        else sscanf(str_data, "%d %d", less, more);
        
        if (para != "-sk" && para != "-para" && para != "-tpara")
                return notify_fail("tongji < 参数 -sk|-para|-tpara > <对象变量> < 条件 <|==|>|between|outof > <统计值> \n");

        switch(cond)
        {
              case ">":
                  more_or_less(para, tar, n_data, MORE_THAN);
                  break;

              case "<":
                  more_or_less(para, tar, n_data, LESS_THAN);
                  break;
              
              case "==":
                  same_as(para, tar, str_data, n_data);
                  break;

              case "between":
                  between_or_outof(para, tar, less, more, BETWEEN);
                  break;

              case "outof":
                  between_or_outof(para, tar, less, more, OUTOF);
                  break;

              default:
                  return notify_fail("tongji < 参数 -sk|-para|-tpara > <对象变量> < 条件 <|==|"
                                     ">|between|outof > <统计值> \n");

        }

        return 1;
}

void more_or_less(string para, string tar, int n_data, int flag)
{
        object *obs;
        int i = 0, j = 0;

        obs = all_interactive();
        write(sprintf(HIC "\n统计结果列表：\n" NOR));
        write(HIW "≡———————————————————————————————————————————≡\n" NOR);

        switch(para)
        {
              case "-sk":
                 if (file_size("/kungfu/skill/" + tar + ".c") == -1)
                 {
                       write("没有 " + to_chinese(tar) + " 这种技能。\n");
                       return ;
                 }
                 for (i = 0; i < sizeof(obs); i ++)
                 {
                       if (flag == MORE_THAN && obs[i]->query_skill(tar, 1) <= n_data)
                                continue;

                       if (flag == LESS_THAN && obs[i]->query_skill(tar, 1) >= n_data)
                                continue;
                       
                       write(sprintf(HIC "玩家：%s(%-5s) " HIW "    |    " HIC "  统计项目：%s  " HIW 
                             "    |    " HIC  "  结果：%d\n" NOR, 
                             obs[i]->name(), 
                             obs[i]->query("id"), 
                             to_chinese(tar), 
                             obs[i]->query_skill(tar, 1)));
                       j ++;
                       
                 }
                 break;
                 
              case "-para":
                 for (i = 0; i < sizeof(obs); i ++)
                 {
                       if (! intp(obs[i]->query(tar)) &&
                           ! floatp(obs[i]->query(tar)))
                               continue;

                       if (flag == MORE_THAN && obs[i]->query(tar) <= n_data)
                                continue;
                       
                       if (flag == LESS_THAN && obs[i]->query(tar) >= n_data)
                                continue;

                       write(sprintf(HIC "玩家：%s(%-5s) " HIW "    |    " HIC "  统计项目：%s  " HIW 
                             "    |    " HIC "  结果：%d\n" NOR, 
                             obs[i]->name(), 
                             obs[i]->query("id"), 
                             tar, 
                             obs[i]->query(tar)));
                       
                       j ++;
                 }
                 break;
                 
              case "-tpara":
                 for (i = 0; i < sizeof(obs); i ++)
                 {
                       if (! intp(obs[i]->query_temp(tar)) &&
                           ! floatp(obs[i]->query_temp(tar)))
                               continue;

                       if (flag == MORE_THAN && obs[i]->query_temp(tar) <= n_data)
                                continue;

                       if (flag == LESS_THAN && obs[i]->query_temp(tar) >= n_data)
                                continue;
                       
                       write(sprintf(HIC "玩家：%s(%-5s) " HIW "    |    " HIC "  统计项目：%s  " HIW 
                             "    |    " HIC "  结果：%d\n" NOR, 
                             obs[i]->name(), 
                             obs[i]->query("id"), 
                             tar, 
                             obs[i]->query_temp(tar)));
               
                       j ++;
                       
                 }
                 break;     
        }
        write(HIG "总共 " + j + " 个项目。\n" NOR);
        write(HIW "≡———————————————————————————————————————————≡\n\n" NOR);
        return;
}

void between_or_outof(string para, string tar, int less, int more, int flag)
{
        object *obs;
        int i = 0, j = 0;

        obs = all_interactive();
        write(sprintf(HIC "\n统计结果列表：\n" NOR));
        write(HIW "≡———————————————————————————————————————————≡\n" NOR);

        switch(para)
        {
              case "-sk":
                 if (file_size("/kungfu/skill/" + tar + ".c") == -1)
                 {
                       write("没有 " + to_chinese(tar) + " 这种技能。\n");
                       return ;
                 }
                 for (i = 0; i < sizeof(obs); i ++)
                 {
                       if (flag == BETWEEN && 
                           (obs[i]->query_skill(tar, 1) <= less ||
                           obs[i]->query_skill(tar, 1) >= more))
                                continue;

                       if (flag == OUTOF && 
                           (obs[i]->query_skill(tar, 1) >= less &&
                           obs[i]->query_skill(tar, 1) <= more))
                                continue;
                       
                       write(sprintf(HIC "玩家：%s(%-5s) " HIW "    |    " HIC "  统计项目：%s  " HIW 
                             "    |    " HIC  "  结果：%d\n" NOR, 
                             obs[i]->name(), 
                             obs[i]->query("id"), 
                             to_chinese(tar), 
                             obs[i]->query_skill(tar, 1)));
                       
                       j ++;
                 }
                 break;
                 
              case "-para":
                 for (i = 0; i < sizeof(obs); i ++)
                 {
                       if (! intp(obs[i]->query(tar)) &&
                           ! floatp(obs[i]->query(tar)))
                               continue;

                       if (flag == BETWEEN && 
                           (obs[i]->query(tar) <= less ||
                           obs[i]->query(tar) >= more))
                                continue;

                       if (flag == OUTOF && 
                           (obs[i]->query(tar) >= less &&
                           obs[i]->query(tar) <= more))
                                continue;

                       write(sprintf(HIC "玩家：%s(%-5s) " HIW "    |    " HIC "  统计项目：%s  " HIW 
                             "    |    " HIC "  结果：%d\n" NOR, 
                             obs[i]->name(), 
                             obs[i]->query("id"), 
                             tar, 
                             obs[i]->query(tar)));

                       j ++;
                 }
                 break;
                 
              case "-tpara":
                 for (i = 0; i < sizeof(obs); i ++)
                 {
                       if (! intp(obs[i]->query_temp(tar)) ||
                           ! floatp(obs[i]->query_temp(tar)))
                               continue;

                       if (flag == BETWEEN && 
                           (obs[i]->query_temp(tar) <= less ||
                           obs[i]->query_temp(tar) >= more))
                                continue;

                       if (flag == OUTOF && 
                           (obs[i]->query_temp(tar) >= less &&
                           obs[i]->query_temp(tar) <= more))
                                continue;

                       write(sprintf(HIC "玩家：%s(%-5s) " HIW "    |    " HIC "  统计项目：%s  " HIW 
                             "    |    " HIC "  结果：%d\n" NOR, 
                             obs[i]->name(), 
                             obs[i]->query("id"), 
                             tar, 
                             obs[i]->query_temp(tar)));

                       j ++;
                 }
                 break;

        }
        write(HIG "总共 " + j + " 个项目。\n" NOR);
        write(HIW "≡———————————————————————————————————————————≡\n\n" NOR);
        return;
}

void outof(string para, string tar, int less, int more)
{
        object *obs;
        int i = 0, j = 0;

        obs = all_interactive();
        write(sprintf(HIC "\n统计结果列表：\n" NOR));
        write(HIW "≡———————————————————————————————————————————≡\n" NOR);

        switch(para)
        {
              case "-sk":
                 if (file_size("/kungfu/skill/" + tar + ".c") == -1)
                 {
                       write("没有 " + to_chinese(tar) + " 这种技能。\n");
                       return ;
                 }
                 for (i = 0; i < sizeof(obs); i ++)
                 {
                       if (obs[i]->query_skill(tar, 1) >= less &&
                           obs[i]->query_skill(tar, 1) <= more)
                                continue;
                       
                       write(sprintf(HIC "玩家：%s(%-5s) " HIW "    |    " HIC "  统计项目：%s  " HIW 
                             "    |    " HIC  "  结果：%d\n" NOR, 
                             obs[i]->name(), 
                             obs[i]->query("id"), 
                             to_chinese(tar), 
                             obs[i]->query_skill(tar, 1)));
                       
                       j ++;
                 }
                 break;
                 
              case "-para":
                 for (i = 0; i < sizeof(obs); i ++)
                 {
                       if (! intp(obs[i]->query(tar)) &&
                           ! floatp(obs[i]->query(tar)))
                               continue;

                       if (obs[i]->query(tar) >= less &&
                           obs[i]->query(tar) <= more)
                                continue;

                       write(sprintf(HIC "玩家：%s(%-5s) " HIW "    |    " HIC "  统计项目：%s  " HIW 
                             "    |    " HIC "  结果：%d\n" NOR, 
                             obs[i]->name(), 
                             obs[i]->query("id"), 
                             tar, 
                             obs[i]->query(tar)));

                       j ++;
                 }
                 break;
                 
              case "-tpara":
                 for (i = 0; i < sizeof(obs); i ++)
                 {
                       if (! intp(obs[i]->query_temp(tar)) &&
                           ! floatp(obs[i]->query_temp(tar)))
                               continue;

                       if (obs[i]->query_temp(tar) >= less &&
                           obs[i]->query_temp(tar) <= more)
                                continue;

                       write(sprintf(HIC "玩家：%s(%-5s) " HIW "    |    " HIC "  统计项目：%s  " HIW 
                             "    |    " HIC "  结果：%d\n" NOR, 
                             obs[i]->name(), 
                             obs[i]->query("id"), 
                             tar, 
                             obs[i]->query_temp(tar)));

                       j ++;
                 }
                 break;

        }
        write(HIG "总共 " + j + " 个项目。\n" NOR);;
        write(HIW "≡———————————————————————————————————————————≡\n\n" NOR);
        return;
}
void same_as(string para, string tar, string str_data, int n_data)
{
        object *obs;
        int i = 0, j = 0;
        int types;

        obs = all_interactive();
        write(sprintf(HIC "\n统计结果列表：\n" NOR));
        write(HIW "≡———————————————————————————————————————————≡\n" NOR);

        switch(para)
        {
              case "-sk":
                 if (file_size("/kungfu/skill/" + tar + ".c") == -1)
                 {
                       write("没有 " + to_chinese(tar) + " 这种技能。\n");
                       return ;
                 }
                 for (i = 0; i < sizeof(obs); i ++)
                 {
                       if (obs[i]->query_skill(tar, 1) != n_data)
                                continue;
                       
                       write(sprintf(HIC "玩家：%s(%-5s) " HIW "    |    " HIC "  统计项目：%s  " HIW 
                             "    |    " HIC  "  结果：%d\n" NOR, 
                             obs[i]->name(), 
                             obs[i]->query("id"), 
                             to_chinese(tar), 
                             obs[i]->query_skill(tar, 1)));

                       j ++;
                       
                 }
                 break;
                 
              case "-para":
                 // 首先判断统计对象返回的类型
                 for (i = 0; i < sizeof(obs); i ++)
                 {
                      if (stringp(obs[i]->query(tar)))
                      {
                            types = 1;
                            break;
                      }
                      if (intp(obs[i]->query(tar)) ||
                          floatp(obs[i]->query(tar)))
                      {
                            // 再次判断保证类型正确
                            if (! obs[i]->query(tar) &&
                                str_data != "0")
                            {
                                 types = 1; 
                                 break;
                            }
                            types = 2;
                            break;
                      }
                      
                 }
                 if (! types)
                 {
                       write("统计对象的返回类型只能为 字符串、整型和浮点型。\n" NOR);
                       write(HIW "≡—————————————————————————————"
                             "——————————————≡\n\n" NOR);
                       return;
                 }

                 for (i = 0; i < sizeof(obs); i ++)
                 {
                       if (types == 1)
                       {

                            if (! stringp(obs[i]->query(tar)) ||
                                obs[i]->query(tar) != str_data)
                                    continue;
                       }
                       else
                       {
                            if (! obs[i]->query(tar) &&
                                obs[i]->query(tar) != n_data)
                                    continue;

                            if (obs[i]->query(tar) != n_data)
                                    continue;
                       }
                       
                       if (types == 1)
                       {
                             write(sprintf(HIC "玩家：%s(%-5s) " HIW "    |    " HIC "  统计项目：%s  " HIW 
                                   "    |    " HIC "  结果：%s\n" NOR, 
                                   obs[i]->name(), 
                                   obs[i]->query("id"),
                                   tar, 
                                   obs[i]->query(tar)));
                       }
                       else 
                       {
                             write(sprintf(HIC "玩家：%s(%-5s) " HIW "    |    " HIC "  统计项目：%s  " HIW 
                                   "    |    " HIC "  结果：%d\n" NOR, 
                                   obs[i]->name(), 
                                   obs[i]->query("id"), 
                                   tar, 
                                   obs[i]->query(tar)));

                             j ++;

                       }
                 }
                 break;

              case "-tpara":
                 // 首先判断统计对象返回的类型
                 for (i = 0; i < sizeof(obs); i ++)
                 {
                      if (stringp(obs[i]->query_temp(tar)))
                      {
                            types = 1;
                            break;
                      }
                      if (intp(obs[i]->query_temp(tar)) ||
                          floatp(obs[i]->query_temp(tar)))
                      {
                            // 再次判断保证类型正确
                            if (! obs[i]->query_temp(tar) &&
                                str_data != "0")
                            {
                                 types = 1; 
                                 break;
                            }
                            types = 2;
                            break;
                      }
                      
                 }
                 if (! types)
                 {
                       write("统计对象的返回类型只能为 字符串、整型和浮点型。\n" NOR);
                       write(HIW "≡—————————————————————————————"
                             "——————————————≡\n\n" NOR);
                       return;
                 }

                 for (i = 0; i < sizeof(obs); i ++)
                 {
                       if (types == 1)
                       {

                            if (! stringp(obs[i]->query_temp(tar)) ||
                                obs[i]->query_temp(tar) != str_data)
                                    continue;
                       }
                       else
                       {
                            if (! obs[i]->query_temp(tar) &&
                                obs[i]->query_temp(tar) != n_data)
                                    continue;

                            if (obs[i]->query_temp(tar) != n_data)
                                    continue;
                       }
                       
                       if (types == 1)
                       {
                             write(sprintf(HIC "玩家：%s(%-5s) " HIW "    |    " HIC "  统计项目：%s  " HIW 
                                   "    |    " HIC "  结果：%s\n" NOR, 
                                   obs[i]->name(), 
                                   obs[i]->query("id"),
                                   tar, 
                                   obs[i]->query_temp(tar)));
                       }
                       else 
                       {
                             write(sprintf(HIC "玩家：%s(%-5s) " HIW "    |    " HIC "  统计项目：%s  " HIW 
                                   "    |    " HIC "  结果：%d\n" NOR, 
                                   obs[i]->name(), 
                                   obs[i]->query("id"), 
                                   tar, 
                                   obs[i]->query_temp(tar)));

                             j ++;

                       }
                 }
                 break;                 

        }
        write(HIG "总共 " + j + " 个项目。\n" NOR);
        write(HIW "≡———————————————————————————————————————————≡\n\n" NOR);
        return;
}
int help(object me)
{
  write(@HELP
指令格式 : tongji < 参数 -sk|-para|-tpara > <对象变量> < 条件 <|==|>|between|outof > <统计值>

           参数 -sk 用于统计武功技能，如：tongji -sk dodge > 200 表示
           显示出技能 dodge 大于两百的玩家列表。

           参数 -para 用于统计玩家数据，如：tongji -para age > 40 表示
           显示出年龄大于四十的玩家列表。
           
           参数 -tpara 用于统计玩家临时数据，如：tongji -tpara apply/amore < 100 表示
           显示出防御大于一百的玩家列表。

           条件 between 用于统计某个数据段的数据，如：tongji -para age between 20 70 表示
           显示出年龄在二十到七十之间的玩家列表。

           条件 outof 用于统计某个数据段外的数据，如：tongji -para age outof 20 70 表示
           显示出年龄在二十到七十之外的玩家列表。

此指令可以根据需要用于在线统计，便于统一管理和维护。
HELP );
    return 1;
}
