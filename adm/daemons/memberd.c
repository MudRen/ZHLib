/********************************中华英雄史会员管理系统**********************************

 1、YH 会员系统核心文件，包括产生/读取注册码，会员充值、会员管理系统面板，会员
    档案自动备份等。
 2、采用15位注册码，有效地防止猜解，保证系统的安全性和可靠性。
 3、采用多级容错措施和历史充值/购买记录信息，强有效的降低出错几率和保证出错
    后易于查询和修改，同时避免不必要的信息丢失，如有数据差错可根据历史记录信
    息判断和查询。
 4、采用验证码机制，有效地防止了非admin级巫师通过其他非法手段获取或修改数据。
 5、为实现网络购买/网络付费自动化提供了完善的接口。

                                                        Create by yuchang for HERO JUN 2005
*****************************************************************************************/
#pragma optimize
#pragma save_binary

#include <ansi.h>
#include <localtime.h>

inherit F_DBASE;

#define SNF              "/data/member/membersn"
#define SNFHIS           "/data/member/membersnhistory"
#define SOURCE_DIR       "/data/member/"
#define DEST_DIR         "/backup/member/member"
#define MBACKUP_DIR      "/backup/member/"
#define DELAY_TIME       900
#define SAVE_DAYS        15
#define MLOG_PAY_DIR     "/data/member/mdata/log/log_pay/"
#define MLOG_BUY_DIR     "/data/member/mdata/log/log_buy/"
#define MDATA_DIR        "/data/member/mdata/data/"
#define GOODS_D          "/adm/daemons/goodsd"
#define SNLEN            13
#define SNFIR            "YX"
#define PER_MONTH_TIME   2678400
#define SNFFIR           "######中华会员注册码######"
#define SNFHISFIR        "#####中华英雄会员注册码历史文件######"
#define PASSWD           "#####FORZHONLINEIS2006MADEBYYUCHANG#####"
#define VERSION          "V 1.00   "                         
#define PERCENT          3 / 100

public string bjtime(int seconds, int format);
public int get_end_time(string id);

void create()
{
        seteuid(getuid());
        set("channel_id", "会员系统");           
        set("no_clean_up", 1);     
        CHANNEL_D->do_channel(this_object(), "sys", "会员系统已经启动。");      
        remove_call_out("backup_data");
        call_out("backup_data", 10);
}

/************************会员档案备份***********************
  备份最近15天的档案
**********************************************************/  
public void backup_data()
{
        mixed *file;
        int iCount = 0;
        string format_time;
        string *t;

        remove_call_out("backup_data");
        call_out("backup_data", DELAY_TIME);

        file = get_dir(MDATA_DIR, -1);
        if (! sizeof(file))return;
        
        format_time = bjtime(time(), 0);
        t = explode(format_time, ":");
        
        // 一天只备份一次
        if (file_size(DEST_DIR + "-" + t[0] + "-" + t[1] + "-" + t[2]) != -1)   
                return;

        // 北京时间每天晚上22:00 -- 0:00间备份
        if (t[3] != "22" && t[3] != "23")return;
        
        message_system(HIW "系统正在对会员档案进行备份，请稍后 ...\n" NOR);
        
        // 删除大于15天的档案
        file = get_dir(MBACKUP_DIR, -1);        
        if (sizeof(file))
        {
                for (iCount = 0; iCount < sizeof(file); iCount ++)
                {       
                        if (time() - file[iCount][2] >= SAVE_DAYS * 86400 )
                                "/cmds/wiz/rm"->rm_dir(MBACKUP_DIR + file[iCount][0]);
                }
        }

        // 备份会员数据
        "/cmds/wiz/cp"->copy_dir(SOURCE_DIR, 
                                 DEST_DIR + "-" + t[0] + 
                                 "-" + t[1] + "-" + t[2],
                                 0);
                                 
        message_system(HIW "系统备份完毕！\n" NOR);
                
        return; 
}
/******************************************************
  子功能调用：用于读取注册码和注册码历史文件
******************************************************/
public mixed get_sn(int flag, string passwd)
{
      int nCount;
      string strtmpSn;
      string *sn, *snhistory;
      int lenth = SNLEN + 1;
      
      if (passwd != PASSWD)
           return "无效的验证码！\n";

      nCount = 2;
      strtmpSn = "";

      sn = ({});
      snhistory = ({});

      if (flag) // 读取注册码
      {
          while (strtmpSn = read_file(SNF, nCount, 1))
          {              
               strtmpSn = strtmpSn[0..lenth];
               sn += ({ strtmpSn });
               strtmpSn = "";
               nCount ++;
          }

          sn[sizeof(sn) - 1] = "";
          sn -= ({ "" });

          return sn;
      }

      strtmpSn = "";
      while (strtmpSn = read_file(SNFHIS, nCount, 1))
      {
            strtmpSn = strtmpSn[0..lenth];
            snhistory += ({ strtmpSn });
            strtmpSn = "";
            nCount ++;
      }

      snhistory[sizeof(snhistory) - 1] = "";
      snhistory -= ({ "" });

      return snhistory;
}

/******************************************************
  子功能调用：用于检查是否为会员
******************************************************/
public int is_member(string id)
{    
      if (file_size(MDATA_DIR + id) == -1)
              return 0;

      return 1;
}

/******************************************************
  子功能和外部调用：用于检查是否为有效会员
******************************************************/
public int is_valib_member(string id)
{
      int end_time;

      if (! is_member(id))return 0;

      end_time = get_end_time(id);
      if (end_time - time() > 0)return 1;

      return 0;
      
}

/******************************************************
  子功能和外部调用：
  1、如果format = 0，返回北京时间 (年:月:日:时:分:秒)
  2、如果format = 1，返回如： 2003-6-23 18:34:23 格式
******************************************************/
public string bjtime(int seconds, int format)
{
     string result;
     mixed t;

     t = localtime(seconds);
 
     if (format)
     {
         result = sprintf("%d-%02d-%02d %02d:%02d:%02d",
                          t[LT_YEAR], 
                          t[LT_MON] + 1,
                          t[LT_MDAY],
                          t[LT_HOUR],
                          t[LT_MIN],
                          t[LT_SEC]);
                          
         return result;
     }

     result = sprintf("%d:%02d:%02d:%02d:%02d:%02d",
                      t[LT_YEAR], 
                      t[LT_MON] + 1,
                      t[LT_MDAY],
                      t[LT_HOUR],
                      t[LT_MIN],
                      t[LT_SEC]);

     return result;
}

/******************************************************
  子功能调用，返回会员有效时间
******************************************************/
public int get_end_time(string id)
{
     int end_time;
     string strtmp;

     if (file_size(MDATA_DIR + id) == -1)
     {
          write("无此会员，或档案已损坏！\n");
          return 0;
     }
     if(! strtmp = read_file(MDATA_DIR + id, 2, 1))
     {
          write("会员档案出错！\n");
          return 0;
     }
     sscanf(strtmp, "%d", end_time);

     return end_time;
}

/******************************************************
  子功能和外部调用，返回会员的中华英雄货币数量
******************************************************/
public int get_yxb(string id)
{
     int yxb;
     string strtmp;

     if (file_size(MDATA_DIR + "YXB" + id) == -1)
     {
          write("无此会员，或档案已损坏！\n");
          return 0;
     }
     if(! strtmp = read_file(MDATA_DIR + "YXB" + id, 2, 1))
     {    
          write("会员档案出错！\n");
          return 0;
     }
     sscanf(strtmp, "%d", yxb);

     return yxb;
}

/******************************************************
  子功能调用，检查会员短信息数量
******************************************************/
public int new_msg(object me)
{
     int iNew, msg_all, i;
      
     msg_all = sizeof(me->query("message"));
        
     if (msg_all == 0)return 0;

     iNew = 0;
     for (i = 1; i <= msg_all; i ++)
          if (me->query("message/msg" + i + "/is_new"))iNew ++;
     
     return iNew;
}

/******************** 产生注册码 *******************************
产生一个15位长的注册码用于会员充值，产生注册码前须指定产生个数
count、系统将产生count个与SNF文件和SNFHIS内注册码不重复且曾经
未使用过的的注册码，然后将其写入文件SNF 
****************************************************************/
public int make_sn(int snc, string passwd)
{
      string *sn, *snhistory, *makecodes;
      string strtmpSn;
      int nCount, i;

      // 注册码组合序列
      string *codes = ({
               "A", "B", "C", "D", "E", "F", "G", "H", "I",
               "J", "K", "L", "M", "N", "O", "P", "Q", "R",
               "S", "T", "U", "V", "W", "X", "Y", "Z",
               "a", "b", "c", "d", "e", "f", "g", "h", "i", 
               "j", "k", "l", "m", "n", "o", "p", "q", "r", 
               "s", "t", "u", "v", "w", "x", "y", "z",               
               "0", "1", "2", "3", "4", "5", "6", "7", "8", 
               "9"
      });

      if (passwd != PASSWD)
      {
           write("无效的验证码！\n");
           return 0;
      }
      if (snc == 0)return 0;

      if (file_size(SNF) == -1)
      {
            write("文件" + SNF + "未找到！\n");
            return 0;
      }
      if (file_size(SNFHIS) == -1)
      {
            write("文件" + SNFHIS + "未找到！\n");
            return 0;
      }

      // 读取注册码和历史注册码
      sn = ({});
      snhistory = ({});
      sn = get_sn(1, PASSWD);
      snhistory = get_sn(0, PASSWD);

      // 初始化
      strtmpSn = "";
      nCount = 0;
      makecodes = ({});

      while(1)
      {
            //显示所产生的全部注册码
            if (nCount >= snc)
            {
                  write("写入 " + nCount + " 个注册码，成功！\n");

                  if (nCount > 10)return 1;

                  for (i = 0; i < nCount; i ++)
                        write(HIW + makecodes[i] + "\n" NOR);

                  return 1;
            }
            
            // 产生一个注册码
            strtmpSn = SNFIR;            
            for(i = 0; i < SNLEN; i ++)
            {
                  strtmpSn += codes[random(sizeof(codes))];
            }

            // 保证注册码不与SNF和SNFHIS重复
            // 当注册码文件和历史注册码文件都为空的情况
            if (! sizeof(sn) && ! sizeof(snhistory))
            {
                  // 产生的注册码序列也不能相同
                  if (! sizeof(makecodes))
                  {                      
                       if (! write_file(SNF, "\n" + strtmpSn, 0))
                       {
                            write("注册码写入失败。\n");
                            return 0;
                       }
                       makecodes += ({ strtmpSn });
                       nCount ++;
                       continue;
                  }
                  else
                  {
                       if (member_array(strtmpSn, makecodes) != -1)
                       {
                            strtmpSn = "";
                            write("member_array(strtmpSn, makecodes\n");
                            continue;
                       }
                       if (! write_file(SNF, "\n" + strtmpSn, 0))
                       {
                            write("注册码写入失败。\n");
                            return 0;
                       }
                       makecodes += ({ strtmpSn });
                       nCount ++;
                       continue;
                  }
            }
            else // 检查产生的注册码是否与注册码和历史注册码重复
            {
                  // 首先检测注册码文件
                  if (sizeof(sn))
                  {
                       if (! sizeof(makecodes))
                       {                    
                            if (member_array(strtmpSn, sn) != -1)
                            {
                                  strtmpSn = "";
                                  continue;
                            }
                            if (! write_file(SNF, "\n" + strtmpSn, 0))
                            {
                                  write("注册码写入失败。\n");
                                  return 0;
                            }
                            makecodes += ({ strtmpSn });
                            nCount ++;
                            continue;
                       }
                       else
                       {
                            if (member_array(strtmpSn, makecodes) != -1)
                            {
                                   strtmpSn = "";
                                   continue;
                            }
                            if (member_array(strtmpSn, sn) != -1)
                            {
                                  strtmpSn = "";
                                  continue;
                            }
                            if (! write_file(SNF, "\n" + strtmpSn, 0))
                            {
                                  write("注册码写入失败。\n");
                                  return 0;
                            }
                            makecodes += ({ strtmpSn });
                            nCount ++;
                            continue;
                       }
                       
                  }
                  if (sizeof(snhistory))
                  {
                       if (! sizeof(makecodes))
                       {                    
                            if (member_array(strtmpSn, snhistory) != -1)
                            {
                                  strtmpSn = "";
                                  continue;
                            }
                            if (! write_file(SNF, "\n" + strtmpSn, 0))
                            {
                                  write("注册码写入失败。\n");
                                  return 0;
                            }
                            makecodes += ({ strtmpSn });
                            nCount ++;
                            continue;
                       }
                       else
                       {
                            if (member_array(strtmpSn, makecodes) != -1)
                            {
                                   strtmpSn = "";
                                   continue;
                            }
                            if (member_array(strtmpSn, snhistory) != -1)
                            {
                                  strtmpSn = "";
                                  continue;
                            }
                            if (! write_file(SNF, "\n" + strtmpSn, 0))
                            {
                                  write("注册码写入失败。\n");
                                  return 0;
                            }
                            makecodes += ({ strtmpSn });
                            nCount ++;
                            continue;
                       }
                  }
            }
      }
}

/************************读取一个注册码***************************
 从注册码文件中读取一个注册码
*****************************************************************/
public string read_sn(string passwd)
{
      string str;
      int lenth;
      
      if (passwd != PASSWD)return "无效的验证码！\n";
      
      lenth = SNLEN + 1;
      if (str = read_file(SNF, 2, 1))
      {
           str = str[0..lenth];

           if (str[0..0] == "#")
                  return HIR "读取注册码失败，可能是注册码已用完，请检查注册码文件！\n" NOR;

           return str;
      }
      else
      {
           return HIR "读取注册码失败，可能是注册码已用完，请检查注册码文件！\n" NOR;
      }
}

/*******************使用注册码充值*********************************
 1、校验注册码有效性
 2、保存充值记录
 3、修改会员档案
 4、从注册码文件中删除注册码并写入到注册码历史文件

 ##考虑三种情况：
   1、第一次成为会员
   2、会员过期后充值
   3、会员未过期时继续充值
*****************************************************************/
public int pay(object me, string str)
{
      string strtmpSn;
      string *sn, *snhistory;
      int end_time, tmp_end_time;
      int i;

      /*********************************************************
       校验所需的文件是否存在
      **********************************************************/
      if (file_size(SNF) == -1)
      {
           write("未找到注册码文件，请妥善保管好您的注册码，并尽快与ADMIN联系。\n");
           return 0;
           
      }
      if (file_size(SNFHIS) == -1)
      {
           write("未找到历史注册码文件，请妥善保管好您的注册码，并尽快与ADMIN联系。\n");
           return 0;
      }
      
      // 校验注册码
      sn = get_sn(1, PASSWD);
      
      if (sizeof(str) != SNLEN + 2)
      {
            return 0;
      }
      if (member_array(str, sn) == -1)
      {
            return 0;
      }

      // 保存充值记录
      if (file_size(MLOG_PAY_DIR + me->query("id")) == -1)
      {
           write_file(MLOG_PAY_DIR + me->query("id"), 
                      sprintf("%s(%s)于%s准备用充值码 %s 进行充值！\n", 
                              me->name(1), 
                              me->query("id"),
                              bjtime(time(), 1),
                              str),
                     1);
      }
      else
      {
          write_file(MLOG_PAY_DIR + me->query("id"), 
                     sprintf("%s(%s)于%s准备用充值码 %s 进行充值！\n", 
                             me->name(1), 
                             me->query("id"),
                             bjtime(time(), 1),
                             str),
                     0);
      }

      // 删除注册码并写入注册码历史文件
      // 从注册码文件中删除该注册码
      sn -= ({ str });
      if (! write_file(SNF, SNFFIR, 1))
      {
          write("重新创建注册码文件时失败，请与本站ADMIN联系！\n");
          write_file(MLOG_PAY_DIR + me->query("id"), 
                     sprintf("↑此次充值由于无法创建注册码文件而失败！\n", 
                     me->name(1),
                     me->query("id"),
                     bjtime(time(), 1),
                     str),
          0);
          return 0;
      }
      for (i = 0; i < sizeof(sn); i ++)
      {
          if (sizeof(sn[i]) != SNLEN + 2)continue;

          if (! write_file(SNF, "\n" + sn[i], 0))
          {
               write("写入注册码档案失败，请与本站ADMIN联系！\n");
               write_file(MLOG_PAY_DIR + me->query("id"), 
                          sprintf("↑此次充值由于写入注册码档案错误而失败！\n", 
                          me->name(1),
                          me->query("id"),
                          bjtime(time(), 1),
                          str),
               0);
               return 0;
          }
      }

      // 写入注册码到历史注册码文件尾
      if (! write_file(SNFHIS, "\n" + str, 0))
      {
          write("写入注册码到注册码历史文件时失败，请与本站ADMIN联系！\n");
          write_file(MLOG_PAY_DIR + me->query("id"), 
                     sprintf("↑此次充值由于写入注册码到历史注册码文件错误而失败！\n", 
                     me->name(1),
                     me->query("id"),
                     bjtime(time(), 1),
                     str),
          0);
          return 0;
      }

      // 修改会员档案
      
      // 第一次成为会
      if (! is_member(me->query("id")))
      {
            end_time = time() + PER_MONTH_TIME;
            strtmpSn = "";
            strtmpSn = sprintf("%d", end_time);
            if (! write_file(MDATA_DIR + me->query("id"), strtmpSn, 1))
            {
                    write("写入档案失败，请与本站ADMIN联系！\n");

                    write_file(MLOG_PAY_DIR + me->query("id"), 
                               sprintf("↑此次充值由于写入档案错误而失败！\n", 
                               me->name(1),
                               me->query("id"),
                               bjtime(time(), 1),
                               str),
                    0);

                    return 0;
            }
            write(HIG "充值成功！\n" NOR);
            write(HIG "恭喜您成为会员，您的会员期限还剩余 31 天！\n");
            write(HIW "您的会员到期时间为 " + bjtime(end_time, 1) + " 。\n" NOR);
            me->set("member/join_time", time());
            me->add("member/pay_times", 1);
            me->set("member/buy_times", 0);
            me->set("member/last_paytime", time());
            
            write_file(MLOG_PAY_DIR + me->query("id"), 
                       sprintf("↑此次充值成功！\n", 
                       me->name(1), 
                       me->query("id"),
                       bjtime(time(), 1),
                       str),
            0);

            // 为其建立中华英雄货币存放文件
            write_file(MDATA_DIR + "YXB" + me->query("id"), "0", 1);
            
            call_out("show_member_info", 1, me->query("id"), "info", me);
            return 1;
      }

      // 过期充值
      if (is_member(me->query("id")) && ! is_valib_member(me->query("id")))
      {
            end_time = time() + PER_MONTH_TIME;
            strtmpSn = "";
            strtmpSn = sprintf("%d", end_time);
            if (! write_file(MDATA_DIR + me->query("id"), strtmpSn, 1))
            {
                    write("写入档案失败，请与本站ADMIN联系！\n");

                    write_file(MLOG_PAY_DIR + me->query("id"), 
                               sprintf("↑此次充值由于写入档案错误而失败！\n", 
                               me->name(1), 
                               me->query("id"),
                               bjtime(time(), 1),
                               str),
                    0);

                    return 0;
            }
            write(HIG "充值成功！\n" NOR);
            write(HIG "您的会员期限还剩余 31 天！\n");
            write(HIW "您的会员到期时间为 " + bjtime(end_time, 1) + " 。\n" NOR);
            me->add("member/pay_times", 1);
            me->set("member/last_paytime", time());

            write_file(MLOG_PAY_DIR + me->query("id"), 
                       sprintf("↑此次充值成功！\n", 
                       me->name(1), 
                       me->query("id"),
                       bjtime(time(), 1),
                       str),
            0);
            
            call_out("show_member_info", 1, me->query("id"), "info", me);
            return 1;
      }

      // 未过期充值
      if (file_size(MDATA_DIR + me->query("id")) == -1)
      {
            write("未找到档案，请与本站ADMIN联系！\n");
            write_file(MLOG_PAY_DIR + me->query("id"), 
                       sprintf("↑此次充值由于未找到档案而失败！\n", 
                       me->name(1),
                       me->query("id"),
                       bjtime(time(), 1),
                       str),
            0);
            return 0;
      }
      if (! strtmpSn = read_file(MDATA_DIR + me->query("id"), 2, 1))
      {
            write("读取档案出错，请与本站ADMIN联系！\n");
            write_file(MLOG_PAY_DIR + me->query("id"), 
                       sprintf("↑此次充值由于读取档案错误而失败！\n", 
                       me->name(1), 
                       me->query("id"),
                       bjtime(time(), 1),
                       str),
            0);
            return 0;
      }

      sscanf(strtmpSn, "%d", end_time);
      end_time += PER_MONTH_TIME;
      tmp_end_time = end_time;
      strtmpSn = "";
      strtmpSn = sprintf("%d", end_time);

      if (! write_file(MDATA_DIR + me->query("id"), strtmpSn, 1))
      {
            write("写入档案出错，请与本站ADMIN联系！\n");
            write_file(MLOG_PAY_DIR + me->query("id"), 
                       sprintf("↑此次充值由于写入档案错误而失败！\n", 
                       me->name(1), 
                       me->query("id"),
                       bjtime(time(), 1),
                       str),
            0);
            return 0;
      }
      end_time -= time();
      end_time = (int)(end_time / 86400);
      me->add("member/pay_times", 1);
      write_file(MLOG_PAY_DIR + me->query("id"), 
                 sprintf("↑此次充值成功！\n", 
                 me->name(1), 
                 me->query("id"),
                 bjtime(time(), 1),
                 str),
      0);
      me->set("member/last_paytime", time());

      write(HIG "充值成功！\n" NOR);
      write(HIW "您的会员期限还剩余 " + end_time + " 天。\n" NOR);
      write(HIW "您的会员到期时间为 " + bjtime(tmp_end_time, 1) + " 。\n" NOR);
      call_out("show_member_info", 1, me->query("id"), "info", me);
      return 1;

}

/******************************************************
 会员管理面板
 用于显示会员信息、购买记录，充值记录和
 可购买物品等信息。
******************************************************/
public void show_member_info(string id, string arg, object me)
{
      string strtmpSn;
      int i;
      float yxb_avg, hours;

      switch(arg)
      {
           // 充值记录
           case "payinfo":
                if (file_size(MLOG_PAY_DIR + id) == -1)
                {
                     write("您目前没有充值记录！\n");
                     return;
                }
                write(BBLU + HIW "您的充值记录如下：\n" NOR);
                i = 1;
                while(strtmpSn = read_file(MLOG_PAY_DIR + id, i, 1))
                {
                     write(BBLU + HIY + strtmpSn + NOR);
                     i ++;
                }
                break;
           // 购买记录
           case "buyinfo":
                if (file_size(MLOG_BUY_DIR + id) == -1)
                {
                     write("您目前没有购买记录！\n");
                     return;
                }
                write(BBLU + HIW "您的购买记录如下：\n" NOR);
                i = 1;
                while(strtmpSn = read_file(MLOG_BUY_DIR + id, i, 1))
                {
                     write(BBLU + HIY + strtmpSn + NOR);
                     i ++;
                }
                break;
                
           // 面板
           case "info":
                write(BBLU + HIW "\t\t    中华英雄史会员系统面板\t\t  " + VERSION + "\n" NOR);
                write(HIW "≡---------------------------------------------------------------≡\n" NOR);
                write(HIY "WELCOME TO JOIN IN THE MEMBERS OF YHHERO AND HOPE YOU ALL GOES WELL.\n\n" NOR);
                write(sprintf(HIC "  会员代号：%-25s有效时间：%s\n" NOR, 
                              id, bjtime(get_end_time(id), 1)));
                write(sprintf(HIC "  入会时间：%-25s充值次数：%d\n" NOR, 
                              bjtime(me->query("member/join_time"), 1),
                              me->query("member/pay_times")));
                write(sprintf(HIC "  购买累计：%-25s购买次数：%d\n" NOR,
                              me->query("member/buy_value") + " YXB",
                              me->query("member/buy_times")));
                write(sprintf(HIC "  转帐累计：%-25s转帐次数：%d\n" NOR,
                              me->query("member/virement_value") + " YXB",
                              me->query("member/virement_times")));
                write(sprintf(HIM "\n  您最后一次充值时间是   %s\n" NOR,
                              bjtime(me->query("member/last_paytime"), 1)));
                write(sprintf(HIM "  您最后一次购买时间是   %s\n" NOR,
                              me->query("member/last_buytime") ?
                              bjtime(me->query("member/last_buytime"), 1):"————"));
                write(sprintf(HIM "  您最后一次购买物品是   %s(%s YXB)\n" NOR,
                              stringp(me->query("member/last_buyob")) ?
                              me->query("member/last_buyob"):"————",
                              stringp(me->query("member/last_buyvalue")) ?
                              me->query("member/last_buyvalue"):"0"));

                write(sprintf(HIY "\n  中华英雄货币：%d YXB\n  累计赚取：%d YXB\n" NOR,
                              get_yxb(id), 
                              get_yxb(id) + me->query("member/buy_value") +
                              me->query("member/virement_value") +
                              me->query("member/virement_value") * PERCENT));

                // 最大误差为1小时
                hours = (time() - me->query("member/join_time")) / 3600;
                if (hours < 1)hours = 1;
                yxb_avg = (get_yxb(id) + me->query("member/buy_value") +
                          me->query("member/virement_value") +
                          me->query("member/virement_value") * PERCENT) / hours;
                yxb_avg = (float)(yxb_avg * 24.0);
                
                write(sprintf(HIY "  平均增长：%.1f YXB / 日 |  预计 %.1f YXB / 月\n" NOR,
                              yxb_avg, (float)(yxb_avg * 30)));

                write(sprintf(HIW "\n  新短消息：%s\n" NOR,
                              new_msg(me) > 0 ? 
                              new_msg(me) + " 条  ○请使用 msg read new 读取" 
                              : new_msg(me) + " 条  ○请使用 help msg 查看短消息系统使用方法"));

                write(HIG "\n  *请使用" HIR " member show info " HIG "      打开中华会员系统面板。\n" NOR);
                write(HIG "  *请使用" HIR " member show payinfo " HIG "   查看历史充值记录。\n" NOR);
                write(HIG "  *请使用" HIR " member show buyinfo " HIG "   查看购买物品记录。\n" NOR);
                write(HIG "  *请使用" HIR " member show zhuaninfo " HIG " 查看历史转帐记录。\n" NOR);
                write(HIG "  *请使用" HIR " member show goods " HIG "     查看英雄商店出售的物品。\n" NOR);
                write(HIG "  *请使用" HIR " member pay 注册码 " HIG "     交纳会费。\n" NOR);
                write(HIG "  *请使用" HIR " member buy 物品代号 " HIG "   购买物品。\n" NOR);
                write(HIG "  *请使用" HIR " member ?? " HIG "             查看member指令的使用方法。\n\n" NOR);
                write(HIR "  *为避免带来不必要的损失请认真阅读中华会员制度文件 " HIY "help member\n\n" NOR);
                write(HIY "                (" HIR"YΨH" HIY ").YHHERO WIZARD GROUP http://yhhero."
                      "vicp.net\n" NOR);
                write(HIW "≡---------------------------------------------------------------≡\n" NOR);
              
                break;
           // 物品清单
           case "goods":
                GOODS_D->show_goods();
                break;
    
           // 转帐记录
           case "zhuaninfo":
                if (file_size(MLOG_PAY_DIR + "ZZYXB" + id) == -1)
                {
                     write("您目前没有转帐记录！\n");
                     return;
                }
                write(BBLU + HIW "您的转帐记录如下：\n" NOR);
                i = 1;
                while(strtmpSn = read_file(MLOG_PAY_DIR + "ZZYXB" + id, i, 1))
                {
                     write(BBLU + HIY + strtmpSn + NOR);
                     i ++;
                }
                break;                
           default:
                break;
      }

      return;
}
/**********************************************************
     增加玩家的YXB
***********************************************************/
public int add_yxb(string id, int amount, string passwd)
{
      int yxb;
      string strtmp;

      if (passwd != PASSWD)
      {   
           write("非法的验证码！\n");
           return 0;
      }
      
      if (file_size(MDATA_DIR + "YXB" + id) == -1)
      {
           write("未找到指定文件，请与本站ADMIN联系！\n");
           return 0;
      }

      yxb = get_yxb(id);

      yxb += amount;
      if (yxb <= 0)yxb = 0;

      strtmp = sprintf("%d", yxb);

      if (! write_file(MDATA_DIR + "YXB" + id, strtmp, 1))
      {
            write("写入文件出错，请与本站ADMIN联系！\n");
            return 0;
      }

      return 1;      
}
/**********************转帐YXB**********************************
   只能为有效会员间转帐，
   每次转帐扣除转帐金额的3%
**********************************************************************/
public int virement_yxb(string me_id, string tar_id, int amount, object me)
{
      string strtmp;
      int yxb_me, yxb_tar, yxb_reduce_me;
      int flag = 0;

      // 判断双方是否为有效会员
      if (! is_valib_member(me_id))
      {
           write("您的会员有效期限已过，请及时充值！\n");
           return 0;
      }

      if (! is_valib_member(tar_id))
      {
           write("目标 " + tar_id + " 为非有效会员！\n");
           return 0;
      }

      if (file_size(MDATA_DIR + "YXB" + me_id) == -1)
      {
           write("你的YXB档案出错，请与本站ADMIN联系！\n");
           return 0;
      }

      if (file_size(MDATA_DIR + "YXB" + tar_id) == -1)
      {
           write("目标 " + tar_id + " 的YXB档案出错，请与本站ADMIN联系！\n");
           return 0;
      }

      if (amount <= 100)
      {
           write("转帐金额必须大于100 YXB。\n");
           return 0;
      }

      yxb_me = get_yxb(me_id);
      yxb_reduce_me = amount * PERCENT;
      if (amount + yxb_reduce_me > yxb_me)
      {
          write("你的YXB不够或无法支付转帐费用。\n");
          return 0;
      }

      if (add_yxb(me_id, -1 * (amount + yxb_reduce_me), PASSWD))
      {
          if (add_yxb(tar_id, amount, PASSWD))
          {
                write(HIC "成功将 " + amount + " YXB 转入 " + tar_id + " 帐户！\n" NOR);
                write(HIC "您总共支付 " + yxb_reduce_me + " YXB 的转帐费用！\n" NOR);
                write(HIC "您的转帐记录已写入文件，请使用 " HIR "member show zhuan"
                      "info " HIC "查看。\n");
                // 写入转帐记录
                if (file_size(MLOG_PAY_DIR + "ZZYXB" + me_id) == -1)flag = 1;
                else flag = 0;
     
                me->add("member/virement_value", amount);
                me->add("member/virement_times", 1);
                write_file(MLOG_PAY_DIR + "ZZYXB" + me_id,
                           sprintf("%s(%s) 于 %s 将 %d YXB 转入 %s 帐户。\n", 
                           me->name(1),
                           me_id,
                           bjtime(time(), 1),
                           amount,
                           tar_id,
                           flag));
                
                return 1;
          }

          return 0;
      }

      return 0;
}
/**********************统计所有的会员**********************************
   参数1返回统计的id阵列
   参数0则仅显示
**********************************************************************/
public mixed show_all_members(int flag)
{
      mixed *file;
      string *members;
      int nCount, m = 0;
      string status;
      object ob;
      string name, join_time;

      file = get_dir(MLOG_PAY_DIR, -1);


      if (! sizeof(file))
      {
           if (flag)return ({});
           write(HIG "暂无会员！\n" NOR);
           return;
      }

      members = ({});
      for (nCount = 0; nCount < sizeof(file); nCount ++)
      {
             members += ({ file[nCount][0] });
      }

      if (flag)return members;
       
      write(HIM "以下是中华英雄史的所有会员列表：\n" NOR);
      write(HIW "≡-------------------------------------------------------------------≡\n" NOR);
           
      write(sprintf(HIR "%-18s%-18s%-26s%-20s\n\n" NOR, 
                    "姓  名", "帐  号", "入会时间", "状  况"));

      for (nCount = 0; nCount < sizeof(members); nCount ++)
      {
             if (ob = find_player(members[nCount]))
             {        
                  if (ob->query("doing"))status = HIY "计划中" NOR;          
                  else if (interactive(ob) && query_idle(ob) > 120)status = HIM "发呆" NOR;                  
                  else if (is_valib_member(members[nCount]))status = HIW "在线" NOR;
                  else status = HIR "过期" NOR;
                                name = ob->name(1);
                                join_time = bjtime(ob->query("member/join_time"), 1);
             }
             else 
             {
                  if (is_valib_member(members[nCount]))status = NOR + WHT "离线" NOR;
                  else status = HIR "过期" NOR;
                                name = "———";
                                join_time = "———";
             }

             write(sprintf(HIG "%-18s%-18s%-26s%-20s\n" NOR,
                           name,
                           members[nCount],
                           join_time,
                           status));

             m ++; // 过滤掉转帐记录文件，实际会员数
                                    
      }
      write(HIY "\n总共有 " + m + " 名注册会员。\n" NOR);
      write(HIW "≡-------------------------------------------------------------------≡\n\n" NOR);
      return 1;
}

public int remove_member(string id)
{
      object ob;
      if (! is_member(id))
      {
           write("目标为非会员。\n");
           return 0;
      }

      rm(MDATA_DIR + id);
      rm(MDATA_DIR + "YXB" + id);
      rm(MLOG_PAY_DIR + id);
      rm(MLOG_PAY_DIR + "ZZYXB" + id);
      rm(MLOG_BUY_DIR + id);
      ob = UPDATE_D->global_find_player(id);
      if (! objectp(ob))
      {
            write("没有这个玩家。\n");
            return 0;
      }
      ob->delete("member");
      UPDATE_D->global_destruct_player(ob, 1);

      write("成功删除会员 " + id + " 。\n");
      return 1;
}


