// user list
// Smallfish@Huaxia

inherit F_CLEAN_UP;

int main(object me, string str)
{
        object *ob,*ob1,*ob2,*user,*the_user;
        int i,j;
        string msg;

        if (! SECURITY_D->valid_grant(me, "(wizard)"))
                return 0;

        if (!str || str != "-l")
        {
                ob=users();
                if (!str || str != "-u")
                {
                        i = sizeof(ob);
                        while (i--) {
                                write(sprintf("%15s : %30s\n",ob[i]->query("id"),
                                file_name(ob[i])));
                        }
                } else
                {
                        ob = filter_array(ob,(: intp($1->query_busy()) && $1->query_busy() > 10 :));
                        i = sizeof(ob);
                        while (i--) {
                                write(sprintf("%15s : %-5d\n",ob[i]->query("id"),
                                ob[i]->query_busy()));
                        }
                }
        } else
        {
                ob = children("/clone/user/login");
                user = users();
                ob1 = filter_array(ob, (: !$1->query("id") && query_ip_number($1) :));
                ob2 = filter_array(ob, (: $1->query("id") && query_ip_number($1) :));
                ob2 = filter_array(ob2, (: !find_player($1->query("id")) :));
                i = sizeof(ob1);
                if (i>0)
                {
                        while(i--)
                        {
                                the_user = filter_array(user, (: query_ip_number($1) == $2 :), query_ip_number(ob1[i]));
                                if (sizeof(the_user))
                                        msg = "[有玩家在线]";
                                else
                                        msg = "[无玩家在线]";
                                write(sprintf("%15s : %30s\n",
                                        "无ID",
                                        query_ip_number(ob1[i])+msg,
                                        ));
                        }
                }
                i = sizeof(ob2);
                if (i>0)
                {
                        while(i--)
                        {
                                the_user = filter_array(user, (: query_ip_number($1) == $2 :), query_ip_number(ob1[i]));
                                if (sizeof(the_user))
                                        msg = "[有玩家在线]";
                                else
                                        msg = "[无玩家在线]";
                                write(sprintf("%15s : %30s\n",
                                        ob2[i]->query("id"),
                                        query_ip_number(ob2[i])+msg,
                                        ));
                        }
                }
        }
        return 1;
}

int help(object me)
{
write(@HELP
指令格式 : ulist [-l] [-u]

将线上所有玩家的/obj/user number 显示出来。
-l参数查询可疑连线物品。
-u参数查看所有busy超过10秒的玩家。
HELP
    );
    return 1;
}

