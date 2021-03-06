// jiedong.c

inherit F_CLEAN_UP;
 
int main(object me, string arg)
{
        object ob;
 
        if (me != this_player(1)) return 0;

                if (!arg) return notify_fail("格式:jiedong <id>\n");

        if (stringp(arg))
        {
                seteuid(getuid());
                ob = find_player(arg);
                if (! ob)
                {
                        ob = new(LOGIN_OB);
                        ob->set("id", arg);
                        if (! ob->restore())
                        {
                                destruct(ob);
                                return notify_fail("没有这个玩家。\n");
                        }
                        ob->set_temp("create_temp", 1);
                } else
                {
                        ob = ob->query_temp("link_ob");
                        while (ob && ob->is_character())
                                ob = ob->query_temp("link_ob");
                        if (! ob)
                                return notify_fail("这个人物缺少连接信息，请重新LOGIN。\n");
                }

                                
                                if (!ob->query("is_dongjie"))
				{
					destruct(ob);
					return notify_fail("该ID没有被冻结啊？！\n");
				}
				if ((int)ob->query("dongjie_time") > time() && !wizardp(me))
				{
					destruct(ob);
return notify_fail("被冻结的ID需要在两天后才能进行解冻!\n");
				}

                write("请输入(" + ob->query("id") + ")的冻结密码：");
                input_to("get_jiedong_pass",1,me,ob);
                return 1;
        }

}

private void get_jiedong_pass(string pass, object me, object ob)
{
        string old_pass;
        object link_ob;

        write("\n");
                //检查冻结密码是否正确
        old_pass = ob->query("djpassword");
        if (crypt(pass, old_pass) != old_pass)
        {
                write("密码错误！\n");
                return;
        }
                //尝试解冻用户
	        if (! ob->delete("is_dongjie"))
        {
                write("解冻用户失败！\n");
                return;
        }

                //开始发送各类私人、公共信息
        tell_object(me, "你把用户" + ob->query("id") + "解冻了！\n"); 
        CHANNEL_D->do_channel(this_object(), "rumor", 
                                sprintf("据说用户%s被%s解冻了。",
				ob->query("id"),me->name()));

	catch(ob->save());
        if (ob->query_temp("create_temp"))
                destruct(ob);
}

int help(object me)
{
        write(@HELP
指令格式 : jiedong <id>
 
这个指令可以解冻指定ID。
被解冻得ID可以重新使用登录密码登录系统。
 
HELP );
    return 1;
}


