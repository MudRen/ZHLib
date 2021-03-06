// banker.c 银行家
// This is a inheritable object.
// Each dealer should support buy, sell, list, value 4 commands
// Updated by Lonely for banghui tax of withdraw

#include <dbase.h>
#include <ansi.h>

int do_check()
{
        // here we use 3 units to display bank infos
        int tax;
        int total = (int)this_player()->query("balance");
        
        tax = (int)environment(this_object())->query("bunch/tax");
                
        if (intp(tax) && tax > 0 && tax < 11)
                write("敝商号的取钱的手续费为百分之" + chinese_number(tax) + "。\n");       
        else
                write("敝商号的取钱的手续费为百分之十。\n");      
        
        if (!total || total < 0)
        {
                this_player()->set("balance", 0);
                write("您在敝商号没有存钱。\n");
                return 1;
        }
        write(this_object()->query("name")+"悄悄告诉你：您在弊商号共存有" + 
              MONEY_D->money_str(total) + "。\n");
              
        return 1;                                                               
}

int do_convert(string arg)
{
        string from, to;
        int amount, bv1, bv2;
        object from_ob, to_ob;
        object me;

        me = this_player();                                                     

        if (me->is_busy())
                return notify_fail("你还是等有空了再说吧！\n");

        if (this_object()->is_fighting())
                return notify_fail("哟，抱歉啊，我这儿正忙着呢……您请稍候。\n");

        if (! arg || sscanf(arg, "%d %s to %s", amount, from, to) != 3)
        {
                return notify_fail("命令格式：convert|duihuan <数量> <货币单位> to <新货币单位>\n");
        }

        from_ob = present(from + "_money", me);
        to_ob = present(to + "_money", me);

        if (! to_ob && file_size("/clone/money/" + to + ".c") < 0)
                return notify_fail("你想兑换成什么？\n");

        if (! from_ob)
                return notify_fail("你身上没有带这种钱。\n");

        if (from_ob == to_ob)
                return notify_fail("你有毛病啊？\n");

        if (amount < 1)
                return notify_fail("你想白赚啊？\n");

        if ((int)from_ob->query_amount() < amount)
                return notify_fail("你带的" + from_ob->query("name") +
                                   "不够。\n");

        bv1 = from_ob->query("base_value");
        if (! bv1)
                return notify_fail("这样东西不值钱。\n");

        bv2 = to_ob ? to_ob->query("base_value")
                    : call_other("/clone/money/" + to, "query", "base_value");
        if (bv1 < bv2)  amount -= amount % (bv2 / bv1);
        if (amount == 0)
                return notify_fail("这些" + from_ob->query("name") +
                                   "不够换。\n ");

        if (bv1 > bv2 && bv1 / bv2 * amount > 10000)
                return notify_fail("哦呦...我这一下子还拿不出这么多散钱...\n");

        // allowed to convert now
        me->start_busy(1);

        from_ob->add_amount(-amount);

        if (! to_ob)
        {
                to_ob = new("/clone/money/" + to);
                to_ob->set_amount(amount * bv1 / bv2);
                to_ob->move(me, 1);
        }
        else
                to_ob->add_amount(amount * bv1 / bv2);

        message_vision(sprintf("$N从身上取出%s%s%s，换成了%s%s%s。\n",
                               chinese_number(amount),
                               from_ob->query("base_unit"),
                               from_ob->query("name"),
                               chinese_number(amount * bv1 / bv2),
                               to_ob->query("base_unit"),
                               to_ob->query("name")), me);

        return 1;
}                                                                               

int do_deposit(string arg)                                                      
{
        string what;
        int amount, money_limit;
        object what_ob, me;

        me = this_player();

        if (me->is_busy())
                return notify_fail("你还是等有空了再说吧！\n");

        if (this_object()->is_fighting())
                return notify_fail("哟，抱歉啊，我这儿正忙着呢……您请稍候。\n");

        if (! arg || sscanf(arg, "%d %s", amount, what) != 2)
                return notify_fail("命令格式：deposit:cun <数量> <货币单位>\n");

        what_ob = present(what + "_money", me);
        if (! what_ob)
                return notify_fail("你身上没有带这种钱。\n");

        if (amount < 1)
                return notify_fail("你想存多少" + what_ob->query("name") +
                                   "？\n");

        if ((int)what_ob->query_amount() < amount)
                return notify_fail("你带的" + what_ob->query("name") +
                                   "不够。\n");

        // deposit it
        me->start_busy(1);

        me->add("balance", what_ob->query("base_value") * amount);
        what_ob->add_amount(-amount);
        message_vision(sprintf("$N拿出%s%s%s，存进了银号。\n",
        chinese_number(amount), what_ob->query("base_unit"),
        what_ob->query("name")), me);

        return 1;
}


int do_withdraw(string arg)
{
        string what, banghui;
        int amount, money_limit, tax;
        object what_ob, me, area;
        int v, s;

        me = this_player();

        if (me->is_busy())
                return notify_fail("你还是等有空了再说吧！\n");

        if (this_object()->is_fighting())
                return notify_fail("哟，抱歉啊，我这儿正忙着呢……您请稍候。\n");

        if (!arg || sscanf(arg, "%d %s", amount, what) != 2)
                return notify_fail("命令格式：withdraw|qu <数量> <货币单位>\n");

        if (amount < 1)
                return notify_fail("你想取出多少钱？\n");

        if(amount >= 10000)
                return notify_fail("这么大的数目。本店没这么多零散现金。\n");

        if (file_size("/clone/money/" + what + ".c") < 0)
                return notify_fail("你想取出什么钱？\n");

        what = "/clone/money/" + what;
        v = amount * what->query("base_value");
        
        area = environment(this_object());
        if (! area->is_area_room() || ! stringp(area->query("bunch/bunch_name")) ||
            area->query("bunch/npc_file") != base_name(this_object()) ||
            ! intp(area->query("bunch/tax")) || (int)area->query("bunch/tax") < 1 ||     
            (int)area->query("bunch/tax") > 10)     
                tax = v * 1 / 10;
        else
                tax = v * (int)area->query("bunch/tax") / 100;
                
        banghui = (string)this_player()->query("bunch/bunch_name");
        if(! stringp(banghui) || banghui != (string)this_object()->query("bunch/bunch_name")) 
               s = v + tax;
        else
               s = v;
        if (s > me->query("balance") || v <= 0)
               return notify_fail("你存的钱不够取。\n");

        me->start_busy(1);

        me->add("balance",  -s);
        if (s > v && stringp(banghui = this_object()->query("bunch/bunch_name")))
               BUNCH_D->add_info_into_bunch(banghui, "npc_money", tax);
               
        MONEY_D->pay_player(me, v);

        message_vision(sprintf("$N从银号里取出%s。\n", MONEY_D->money_str(v)), me);

        return 1;
}

int do_tax(string arg)
{
        object me, area;
        string bunch;
        int tax;
        
        me = this_player();
        
        if (! arg || sscanf(arg, "%d", tax) != 1) 
               return notify_fail("你要设定百分之多少的取款手续费？\n"); 

        if (! intp(tax) || tax < 1 || tax > 10)
                return notify_fail("设定取款手续费要介于百分之一和百分之十之间。\n");
                
        if (! stringp(bunch = me->query("bunch/bunch_name")) ||
            bunch != this_object()->query("bunch/bunch_name"))
                return notify_fail("敝商号没有被你控制，你无权设定取款手续费。\n");
                
        if (me->query("bunch/level") != 9)
                return notify_fail("只有帮主才有权利设定这里的取款手续费。\n");

        area = environment(this_object());
        
        if (! area->is_area_room() || ! stringp(area->query("bunch/bunch_name")) ||
            area->query("bunch/npc_file") != base_name(this_object()))
                return notify_fail("设定取款手续费失败。\n");                
                          
        area->set("bunch/tax", tax);
        area->save();
        
        write("你设定敝商号的取钱的手续费为百分之" + chinese_number(tax) + "成功。\n");   
        return 1;
}
        
