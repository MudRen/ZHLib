inherit F_DBASE;
#include <ansi.h>


void create()
{
        seteuid(getuid());
        set("name", HIG "奖劵系统发布精灵" NOR);
        set("id", "card daemon");
        call_out("remind", 20);
}

int do_place()
{
   string *alldir, dir, dir_name, *allfile,file;
   int i;
   object place, gift;
   mapping dir_list = ([
                "/d/beijing/" : "北京城", 
                "/d/changan/" : "长安城",
                "/d/city/" : "扬州城",
                "/d/city3/" : "成都城",
                "/d/dali/" : "大理城",
                "/d/guanwai/" : "关外",
                "/d/hangzhou/" : "杭州城",
                "/d/kaifeng/" : "开封城",
                "/d/jingzhou/" : "荆州城",
                "/d/luoyang/" : "洛阳城",
                "/d/lingxiao/" : "凌霄城",
                "/d/quanzhen/" : "终南山",
                "/d/wudang/" : "武当山",
                "/d/zhongzhou/" : "中州城",
                "/d/shaolin/" : "少林寺地区",
                "/d/wudu/" : "五毒教地区",
                "/d/xingxiu/" : "西域",
                "/d/huashan/" : "华山",
                "/d/emei/" : "峨眉山",
    ]);
   remove_call_out("remind");
   call_out("remind", 3500);

   alldir = keys(dir_list);

   dir = alldir[random(sizeof(alldir))];
   if ( ! dir || dir == 0 ) dir = "/d/wudang/";
   dir_name = dir_list[dir];  
   
   message( "gift", BLINK HIY"【天降礼物】" NOR HIG
            "天神在" + dir_name + "撒下了几张礼物兑换劵，大家何不群起而寻之！\n"NOR, users() );
 
   allfile = get_dir(dir);
  
   for(i = 0;i < 20;i++)
   {
      file = dir + allfile[random(sizeof(allfile))];

      if ( file[<2..<1] != ".c") continue;

      write(file + "\n");
      if ( find_object(file) )
         place = find_object(file);
      else 
          place = load_object(file);

      if (  place )
      {   
          if ( i <= 2 ) gift = new("/u/sanben/giftcard1");
          else 
          if ( i > 2 && i <= 7 ) gift = new("/u/sanben/giftcard2");
          else 
             gift = new("/u/sanben/giftcard3");            
          gift->move(place);
          tell_room(place, HIC"突然只见天神从云端里探出头来，撒下一张礼劵。\n"NOR);
      }
   }
   return 1; 


}

void remind()
{

   message( "gift", BLINK HIY"【天降礼物】" NOR HIR
            "天神将在三分钟后分发奖劵，请要寻宝的人做好准备。\n"NOR, users() );
   
   remove_call_out("do_place");
   call_out("do_place", 180);


} 





