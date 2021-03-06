// ward.c 王朝战争主控制程序
// Created by yuchang

#include <ansi.h>
inherit F_DBASE;

static object *total = ({ });
static object king = 0;
static int start_time = 0;

object *query_total()  { return total; }
object query_king() { return king; }

int ask_war(object me);
int start_war(object me);
int join_war(object ob);
int fail_war();
int check_out(object me);
int check_quit(object me);

void init_king(object me);
void init_player(object me);
void message_competition(string msg);
void auto_check();
void remove_enemy();
void give_bouns();
void restore_status(object me);

string *place = ({
        "/d/xiangyang/eastgate2",
        "/d/xiangyang/eastgate1",
        "/d/xiangyang/eastjie3",
        "/d/xiangyang/eastjie2",
        "/d/xiangyang/eastjie1",
        "/d/xiangyang/guangchang",
        "/d/xiangyang/westjie1", 
        "/d/xiangyang/westjie2",
        "/d/xiangyang/westjie3",
        "/d/xiangyang/westgate1",
        "/d/xiangyang/westgate2",
        "/d/bianliang/yidao1",
        "/d/bianliang/yidao2",
        "/d/bianliang/yidao3",
        "/d/bianliang/chengmen",
});

void create() 
{
        seteuid(ROOT_UID);
        set("channel_id", "王朝战争"); 
        CHANNEL_D->do_channel(this_object(), "sys", "王朝战争已经启动。"); 
}

int clean_up()
{
        return 1;
}

int ask_war(object me)
{
        if (me->query_condition("junquest_fail"))
                return notify_fail("大人尚是待罪之身，轻言出兵，恐性命难保啊，还是请回吧！\n");

        if (me->query_condition("junquest_song"))
                return notify_fail("大人已经经军令在身了，还在这里磨蹭什么啊？！\n");
                                
        if (me->query("degree_jungong") < 8)
                return notify_fail("大人官低位卑，如何能任一军之帅，难服人心哪？！\n"); 

        if (objectp(king))
                return notify_fail("现在已经有" + king->name(1) + "率军出征了，大人可以前去助阵。\n");
                
        king = me;
        init_king(me);
        return 1;
}

void init_king(object me)
{ 
        int liangcao;
        string temp;
        object bingfu, kaijia;

        me->set("party/party_name", HIW "大宋" NOR);
        me->set("party/rank", HIW "兵马元帅" NOR);  
        me->set_temp("jun_quest/party", "song");        
        me->set("eff_qi", me->query("max_qi") + 1000 * me->query("degree_jungong"));
        me->set("qi", me->query("eff_qi"));
        me->set_temp("jun_quest/train", "infantry");
        me->apply_condition("junquest_song", 360);         
        // me->set_override("quit", (: call_other, __FILE__, "fail_war" :));
        
        liangcao = 1000;
        temp = sprintf("%d", liangcao);
        write_file("/quest/quest_jun/song/liangcao", temp, 1);
        
        if (! objectp(kaijia = present("kai jia", me)))
        {
                kaijia = new("/quest/quest_jun/song/obj/tiejia");
                kaijia->move(me);
        }
        if (! objectp(bingfu = present("bing fu", me)))
        {
                bingfu = new("/adm/npc/obj/bingfu");
                bingfu->set("owner", me->query("id"));
                bingfu->set("master", me->query("name"));
                bingfu->move(me);
                bingfu->check_me(me);
        }
        
        tell_object(me, HIC "\n大人，朝中可用之兵已经所剩无几，仅此数营步兵，尚可一战，此次\n" +
                        "出征，任重道远，无奈事关我大宋国运，还望大人尽力而为，望大人\n" +
                        "早日得胜，凯旋回朝！御马监有为将军备的千里马，可助大人脚力。\n\n" NOR);      
        start_war(me);
}

// start war
int start_war(object me)
{
        object jiang, jiangjun, kehan, smen, mmen;
        int i;

        message("channel:rumor", MAG "【大宋史记】" +
                CHINESE_D->chinese_date((time() - 14 * 365 * 24 * 60 * 60)) +
                "蒙古可汗大举南侵，大宋派出\n " +
                "           " + "兵马大元帅" + me->query("name") + MAG + "(" + me->query("id") + MAG + ")" +
                MAG + "，兴师北上抗敌......\n" NOR,
                users());

        smen = get_object("/quest/quest_jun/syuanmen1");
        if (objectp(smen))
                smen->set("defence", 120);
                
        mmen = get_object("/quest/quest_jun/myuanmen1");
        if (objectp(mmen))
                mmen->set("defence", 120);

        // 布置蒙古军队 
        kehan = new("/quest/quest_jun/meng/kehan");
        kehan->move("/quest/quest_jun/mying1");
        kehan->change_ob();
        jiang = new("/quest/quest_jun/meng/mengj");
        jiang->move("/quest/quest_jun/mying1");
        jiang->change_ob();

        for (i = 0; i < 4; i++)
        {              
                jiang = new("/quest/quest_jun/meng/mengj");
                jiang->move("/quest/quest_jun/mying");
                jiang->change_ob();
                jiang = new("/quest/quest_jun/meng/mengj");
                jiang->move("/quest/quest_jun/dhunya");
                jiang->change_ob();
        }
        

        if (me->query("degree_jungong") > 12)
        for (i = 0; i < 2; i++)
        {
                jiangjun = new("/quest/quest_jun/meng/mengj");
                jiangjun->move("/quest/quest_jun/myuanmen1");
                jiangjun->change_ob();
        }

        if (me->query("degree_jungong") > 10)
        for (i = 0; i < 2; i++)
        {
                jiang=new("/quest/quest_jun/meng/mengj");
                jiang->move("/quest/quest_jun/caoyuan");
                jiang->change_ob();
        }
        // 布置宋军
        for(i = 0; i < 4; i++)
        {
                jiang = new("/quest/quest_jun/song/songb");
                jiang->move("/quest/quest_jun/sying1");
                jiang->change_ob();
        } 
        start_time = time();
        set_heart_beat(1);
        return 1;
} 

// join in war
int join_war(object ob)
{
        if (ob->query("age") < 18)
                return notify_fail(RANK_D->query_respect(ob) + "，你还小，以后再来为国效力吧！\n");

        if (ob->query("combat_exp") < 1000000)
                return notify_fail(RANK_D->query_respect(ob) + "其志可嘉，无奈手无缚鸡之力，还是请回吧！\n");

        if (ob->query("degree_jungong") < 4)
                return notify_fail("您的军衔太低微了，到前方估计没什么用啊！\n");
            
        if (! objectp(king))
                return notify_fail("现在前方没有战事，将军以后再来吧！\n");
                                 
        if (! arrayp(total))
                total = ({ ob });
        else
        if (member_array(ob, total) == -1)
                total += ({ ob });

        message("channel:rumor", MAG "【王朝战争】有志之士" +
                                 ob->name(1) + MAG "奔赴前线加入了支援宋军抗击蒙古军队之列！\n" NOR,
                                 users());
        init_player(ob);
        set_heart_beat(1);
        return 1;
}


// set player's override functions
void init_player(object me)
{
        me->set_temp("jun_quest/party", "song");
        me->set_override("quit", (: call_other, __FILE__, "check_quit" :));

        me->move("/quest/quest_jun/sying1");
        tell_object(me, HIY "你定神一看，这才发现自己已经到了" +
                            environment(me)->short() + HIY "。\n");
}

void heart_beat()
{
        if (sizeof(total) || (start_time && (time() - start_time) > 300))
                auto_check();
}
        
// check all the players who join the war
void auto_check()
{
        object ob;
        string room, site;
        object *lost;
        int i;

        lost = ({ });
        
        if (! objectp(king))
        {
                set_heart_beat(0);
                fail_war();
                return;
        }
        
        room = base_name(environment(king));
        site = file_name(environment(king));
        if (! sscanf(room, "/quest/quest_jun/%*s") &&
            member_array(site, place) == -1 && time() - start_time > 300)
        {
                message_competition("听说" + king->name(1) +
                                    "在战场上临阵脱逃，导致宋军无首领，" +
                                    "军心涣散，被蒙古军队全线击败！\n");
                set_heart_beat(0);
                fail_war();
                return;
        }
        
        if (arrayp(total) && sizeof(total))
        {
                for (i = 0; i < sizeof(total); i++)
                {
                        if (! objectp(total[i]))
                                continue;
                        // 检查是否脱离战场
                        room = base_name(environment(total[i]));
                        site = file_name(environment(total[i]));
                        if (! sscanf(room, "/quest/quest_jun/%*s") &&
                            member_array(site, place) == -1)
                        {
                                message_competition("听说" + total[i]->name(1) +
                                                    "的军队在战场上临阵脱逃，宋军" +
                                                    "军心开始涣散，战斗力下降！\n");
                                // not in war room
                                restore_status(total[i]);
                                total[i] = 0;
                                continue;
                        }
                        // 检查率领的军队（压粮没有带兵的除外）
                        if (! total[i]->query_temp("jun_quest/escort") &&
                            total[i]->query_temp("jun_quest/train") && 
                            total[i]->query("combat_exp") < 20000000 && 
                            site != "/quest/quest_jun/sying2" &&
                            site != "/quest/quest_jun/sying3" &&
                            site != "/quest/quest_jun/sying1" &&
                            site != "/quest/quest_jun/sying" && 
                            site != "/quest/quest_jun/syuanmen1" && 
                            site != "/quest/quest_jun/sying4")
                        {
                            if (total[i]->query("qi") < total[i]->query("max_qi"))
                                // total[i]->query_temp("jun_quest/group") < 1)
                                	lost += ({ total[i] });
                        }
                }
        }
        
        total -= ({ 0 });

        // kickout the players who lost 
        foreach (ob in lost)
                check_out(ob);

        lost = ({ });
        return;
}

int check_out(object me)
{
        object ob;
        mapping my;
        string msg;
        string room;

        tell_object(me, HIR "\n你乘着混乱，逃回元帅大营，又饥有渴，已到半昏迷状态！\n" NOR);
        if (ob = me->query_last_damage_from())
        {
                msg = "听说" + me->name(1) + "的军队被" + ob->name(1) + "的军队杀的全军覆没，一人逃回大营。";
        } else
                msg = "听说" + me->name(1) + "的军队全军覆没，一人逃回宋军大营。";
        message_competition(msg);

        me->move("/quest/quest_jun/sying1"); 
        message("vision", "一个黑影倏的窜了过来，随即就是“啪”的"
                "一声，就见" + me->name() +"摔倒了地上，一副半死不"
                "活的样子。\n", environment(me), ({ me }));
        tell_object(me, "半昏半迷中，你觉得被人拎了起来，又"
                    "重重的摔倒了地上。\n");
        if (! living(me))
                me->revive();
        return 1;
}

// overide function of quit
int check_quit(object me)
{       
        message_competition("听说" + me->name(1) +
                            "在战场上临阵脱逃，溜走了。");
        restore_status(me);

        if (arrayp(total))
                total -= ({ me });
                
        tell_object(me, "你一口气逃出了战场，来到扬州中央广场。\n");

        // continue run quit function
        me->move("/d/city/guangchang");
        message("vision", "只见" + me->name() + "慌里慌张的跑了过来。\n",
                environment(me), ({ me }));
        return 1;
}

int fail_war()
{       
        int i;

        remove_enemy();
        message_competition("听说宋军被金人军队击败了，大宋派出使者割地求和！\n");
        
        if (objectp(king))
        {
                restore_status(king);
                king->apply_condition("junquest_fail", 50);
        }
                
        if (arrayp(total) && sizeof(total))
        {
                for (i = 0; i < sizeof(total); i++)
                {
                        if (! objectp(total[i]))
                                continue;
                        restore_status(total[i]);
                }               
        }
        set_heart_beat(0);
        king = 0;
        total = ({ });
        start_time = 0;
}

void remove_enemy()
{
        object *enemys;
        int j;

        if (arrayp(enemys = children("/quest/quest_jun/meng/kehan")))
        {
                for (j = 0; j < sizeof(enemys); j++)
                {
                        if (enemys[j]->is_fighting())
                        {
                                enemys[j]->remove_all_killer();
                        }
                        tell_room(environment(enemys[j]), HIW "只见" + enemys[j]->name() +
                                  "突然哈哈大笑几声后，率领军队不见了！\n");
                        destruct(enemys[j]);
                }
        }                       
        if (arrayp(enemys = children("/quest/quest_jun/meng/mengj")))
        {
                for (j = 0; j < sizeof(enemys); j++)
                {
                        if (enemys[j]->is_fighting())
                        {
                                enemys[j]->remove_all_killer();
                                tell_room(environment(enemys[j]), HIW "只见" + enemys[j]->name() +
                                          "突然哈哈大笑几声，迅速攻出几招，跳出战圈率领军队不见了。\n");
                        }
                        else {
                                tell_room(environment(enemys[j]), HIW "只见" + enemys[j]->name() +
                                          "突然脸色大喜，急急忙忙地率领军队不见了。\n");
                        }
                        destruct(enemys[j]);
                }
        }
        if (arrayp(enemys = children("/quest/quest_jun/meng/mengb")))
        {
                for (j = 0; j < sizeof(enemys); j++)
                {
                        if (enemys[j]->is_fighting())
                        {
                                enemys[j]->remove_all_killer();
                                tell_room(environment(enemys[j]), HIW "只见" + enemys[j]->name() +
                                        "突然哈哈大笑几声，迅速攻出几招，跳出战圈率领军队不见了。\n");
                        }
                        else {
                                tell_room(environment(enemys[j]), HIW "只见" + enemys[j]->name()
                                                  + "突然脸色大喜，急急忙忙地率领军队不见了。\n");
                        }
                        destruct(enemys[j]);
                }
        }
        
        if (arrayp(enemys = children("/quest/quest_jun/song/songb")))
        {
                for (j = 0; j < sizeof(enemys); j++)
                {
                        if (enemys[j]->is_fighting())
                        {
                                enemys[j]->remove_all_killer();
                                tell_room(environment(enemys[j]), HIW "只见" + enemys[j]->name()
                                                  + "突然面色一变，迅速攻出几招，跳出战圈率领军队不见了。\n");
                        }
                        else {
                                tell_room(environment(enemys[j]), HIW "只见" + enemys[j]->name()
                                                  + "掐值一算，突然脸色大变，急急忙忙地率领军队不见了。\n");
                        }
                        destruct(enemys[j]);
                }
        }
        return;
}

// send message out
void message_competition(string msg)
{
        CHANNEL_D->do_channel(this_object(), "rumor", msg);
}

// remove overide function
void restore_status(object me)
{
        object bingfu, lingjian, zhanma, kaijia;
        
        if (objectp(bingfu = present("bing fu", me)))
                destruct(bingfu);
                        
        if (objectp(lingjian = present("ling jian", me)))
                destruct(lingjian);
        
        if (objectp(zhanma = present("zhan ma", me)))
                destruct(zhanma);
                
        if (objectp(zhanma = present("shizi ma", me)))
                destruct(zhanma);
                
        if (objectp(kaijia = present("kai jia", me)))
                destruct(kaijia);

        me->delete_override("quit");
        me->delete_temp("jun_quest");
        me->delete("party");
        me->remove_all_enemy(1);
        me->remove_all_killer();
        me->receive_damage("qi", 0);
        me->set("eff_qi", me->query("max_qi"));
        me->set("qi", me->query("eff_qi"));
        me->clear_condition();

}

void give_bouns()
{                         
        int reward, pot, exp, jungong, i;
        object me, bingfu;
        object ob;

        remove_enemy();

        if (! objectp(king))
        {
                if (arrayp(total) && sizeof(total) > 0)
                {
                        for (i = 0; i < sizeof(total); i++)
                        {
                                if (! objectp(total[i]))
                                        continue;
                                restore_status(total[i]);
                        }
                }
                set_heart_beat(0);
                king = 0;
                total = ({ });  
                start_time = 0;
                return;
        }
        
        reward = king->query_temp("jun_quest/reward");

        message("channel:rumor", MAG "【大宋京城】" + 
                CHINESE_D->chinese_date((time() - 14 * 365 * 24 * 60 * 60)) +
                "......\n" NOR,
                users());
                
        reward += 20;                  
        if (reward > 200) reward = 200;
        exp = (reward / 2 + random(reward / 2)) * king->query("degree_jungong") * 400; 
        pot = exp / 2; 
        jungong = exp / 5000;
        king->add("guo_shoucheng/reward_exp", exp);
        king->add("guo_shoucheng/reward_potential", pot);
        king->add("guo_shoucheng/reward", jungong);
        king->add("combat_exp", exp);
        king->add("potential", pot);
        king->add("experience", 500 + random(500)); 
        king->add("balance", 1000000);
        if (random(2)) ob = new("/clone/fam/gift/int3");
        else ob = new("/clone/fam/gift/con3");
        ob->move(king, 1);
        if (random(2)) ob = new("/clone/fam/etc/lv7a");
        else ob = new("/clone/fam/gift/dex3");
        ob->move(king, 1);
        if (random(2)) ob = new("/clone/fam/gift/str3");
        else ob = new("/clone/fam/item/stone5");
        ob->move(king, 1);
        
        message("channel:rumor", HIY "【大宋京城】奉天承命，皇帝诏曰：\n" +
                "            " + king->name(1) + HIY "抗金有功，赏黄金百两，绸缎五百匹，美女十名，" +
                "记军功 " HIR + chinese_number(jungong) +
                HIY " 策，钦此！\n\n" NOR,
                users());                              

        tell_object(king, HIW "因抗金有功，你获得了 " + HIR + chinese_number(jungong) +
                          HIW " 策军功和" + HIR + chinese_number(exp) +
                          HIW " 点经验和 " + HIR + chinese_number(pot) +
                          HIW " 点潜能和一些实战体会奖励！！\n" NOR);
               
        restore_status(king);
        king->move("/d/city/guangchang");
        message("vision", "只见" + king->name() + "走了过来。\n",
                environment(king), ({ king }));


        if (arrayp(total) && sizeof(total) > 0)
        {
                for (i = 0; i < sizeof(total); i++)
                {
                        if (! objectp(total[i]))
                                continue;
                        
                        tell_object(total[i], HIR "金军撤兵了，准备班师回朝吧！\n" NOR);

                        reward = total[i]->query_temp("jun_quest/reward"); 
                        if (reward < 2)
                        {
                                restore_status(total[i]);
                                continue;
                        }
                        if (reward > 200) reward = 200;       
                        exp = (reward / 2 + random(reward / 2)) * total[i]->query("degree_jungong") * 300;
                        pot = exp / 3;
                        jungong = exp / 5000;
                
                        total[i]->add("guo_shoucheng/reward_exp", exp);
                        total[i]->add("guo_shoucheng/reward_potential", pot);
                        total[i]->add("guo_shoucheng/reward", jungong);
                        total[i]->add("combat_exp", exp);
                        total[i]->add("potential", pot);
                        total[i]->add("experience", 500 + random(250)); 
                        total[i]->add("balance", 500000);  
                        if (random(2)) ob = new("/clone/fam/gift/int3");
                        else ob = new("/clone/fam/gift/con3");
                        ob->move(total[i], 1);
                        if (random(2)) ob = new("/clone/fam/etc/lv7a");
                        else ob = new("/clone/fam/gift/dex3");
                        ob->move(total[i], 1);
                        if (random(2)) ob = new("/clone/fam/gift/str3");
                        else ob = new("/clone/fam/item/stone5");
                        ob->move(total[i], 1);
                
                        tell_object(total[i], HIW "因抗金有功，你获得了 " + HIR + chinese_number(jungong) +
                                              HIW " 策军功和 " + HIR + chinese_number(exp) +
                                              HIW " 点经验和 " + HIR + chinese_number(pot) + 
                                              HIW " 点潜能和一些实战体会奖励！！\n" NOR);  
                
                        restore_status(total[i]);
                        total[i]->move("/d/city/guangchang");
                        message("vision", "只见" + total[i]->name() + "走了过来。\n",
                                environment(total[i]), ({ total[i] }));
                }
        }   

        set_heart_beat(0);        
        king = 0;
        total = ({ }); 
        start_time = 0;
        return;
}

