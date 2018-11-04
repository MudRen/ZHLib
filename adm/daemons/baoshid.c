#include <ansi.h>

inherit F_DBASE;
int random_place(string dirss,object bs);

string *dirs = ({
"/d/baituo",
"/d/beijing",
"/d/changan",
"/d/city",
"/d/city3",
"/d/dali",
"/d/emei",
"/d/foshan",
"/d/fuzhou",
"/d/gaibang",
"/d/guanwai",
"/d/gumu",
"/d/hangzhou",
"/d/jingzhou",
"/d/kaifeng",
"/d/luoyang",
"/d/quanzhou",
"/d/shaolin",
"/d/shenlong",
"/d/suzhou",
"/d/taishan",
"/d/wudu",
"/d/xingxiu",
"/d/xiakedao",
"/d/huanghe",
"/d/zhongzhou",
"/d/tiezhang",
"/d/taohua",
"/d/qingcheng",
});

string *dirname = ({
"白驼山",
"北京城",
"长安城",
"扬州城",
"成都",
"大理",
"峨嵋山",
"佛山",
"福州",
"丐帮",
"关外",
"古墓",
"杭州",
"荆州",
"开封",
"洛阳",
"泉州",
"少林",
"神龙岛",
"苏州",
"泰山",
"五毒教",
"星宿",
"侠客岛",
"黄河",
"中洲",
"铁掌山",
"桃花岛",
"青城山",
});


void create()
{
        seteuid(ROOT_UID);
        set("channel_id", "内存精灵");
        CHANNEL_D->do_channel( this_object(), "sys", "宝石系统已经启动。\n"); 
        set("name","");
        remove_call_out("choose_baoshi");
        call_out("choose_baosi",10);
}

void choose_baosi()
{
        int i, j ,k,ppl,rd;
        object *list,newob;
        string str,m_name;
        string smp;
        
        j = random(sizeof(dirs));
        //newob = new("/d/quest/obj/"+feizei[random(sizeof(feizei))]);
        rd = random(7);
        if(rd==0) 
        {
                 newob = new("/quest/obj/baoshi");
                 str = "蓝";
        }
        if(rd==1) 
        {
                 newob = new("/quest/obj/baoshi");
                 str = "绿";
        }
        if(rd==2)
        { 
                 newob = new("/quest/obj/baoshi");
                 str = "黄";
        }
        if(rd==3)
        { 
                 newob = new("/quest/obj/baoshi");
                 str = "红";
        }
        if(rd==4)
        { 
                 newob = new("/quest/obj/baoshi");
                 str = "紫";
        }
        if(rd==5)
        { 
                 newob = new("/quest/obj/baoshi");
                 str = "青";
        }
        if(rd==6)
        { 
                 newob = new("/quest/obj/baoshi");
                 str = "水晶";
        }
                
        if(random_place(dirs[j],newob)== 1 )
        message("channel:chat",HIG"【"+HIR"异宝"+HIG"】"+HIW"突然空中打了个炸雷,一个火球横空出世,拖着一道"+str+"光向"+dirname[j]+"的方向落去!\n"+NOR,users());
        remove_call_out("choose_baosi");
  call_out("choose_baosi",1800);
}

int random_place(string dirss,object bs)
{
        int  j, k;
        object  newob,ob;
        mixed*  file, exit;
        string id_name;
        file = get_dir( dirss+"/npc/*.c", -1 );
        
        if( !sizeof(file) ) return 0;

        for(k=0;k<50;k++) { // try 50 times
           j = random(sizeof(file));
           if( file[j][1] > 0 ) {
             newob=load_object(dirss+"/npc/"+file[j][0]);
             if(!newob) continue;
             id_name = newob->query("id");
             destruct(newob);
             if(!id_name) continue;
             if(!objectp(ob=find_living(id_name))) continue; //这个npc不是活的 
                     if(bs->move(ob)) {
                    CHANNEL_D->do_channel( this_object(), "sys", "宝石落到了"+ob->query("name")+"("+ob->query("id")+")的身上。\n"); 
                     return 1;
                    }
             }
           }
         CHANNEL_D->do_channel( this_object(), "sys", "本次宝石发布失败\n");        
        return 0;
}
