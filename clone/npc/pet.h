// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// ����

#include <ansi.h>
#include <command.h>

#define RIDE_CMD              "/cmds/std/ride"
#define UNRIDE_CMD            "/cmds/std/unride"

inherit NPC;
inherit F_NOCLONE;
inherit F_OBSAVE;
inherit F_UNIQUE;

int is_pet() { return 1; }

int is_stay_in_room() { return 1; }

void create()
{
        set_name("����", ({ "pet" }) );
        set("race", "Ұ��");
        set("gender", "����");
        set("age", 2 + random(3));
        set("long", "��ҿ���������ȥָ���ĵط�(rideto)��\n");
        set("ridable", 1);
        set("no_sell", 1);
        set("no_put", 1);
        
        set("int", 30);
        set("kee", 300);
        set("max_kee", 300);
        set("sen", 100);
        set("max_sen", 100);
        set("shen_type", 0);
        set("combat_exp",50000);
        set("attitude", "peaceful");        
        set("limbs", ({ "ͷ��", "����", "β��","����","ǰ��" }) );
        set("verbs", ({ "bite", "hoof" }) );

        set_temp("apply/attack", 100);
        set_temp("apply/damage", 100);
        set_temp("apply/defence",100);
        set_temp("apply/armor", 100);
        
        set_temp("owner_id", "lonely");
        
        if (! check_clone()) return 0;

        setup();
        ::restore();
        // set_heart_beat(30); 
}
                           
void heart_beat() 
{
        if (! this_object()->query_temp("is_rided_by"))
                this_object()->add_temp("stay_in_room", 1);

        if (this_object()->query_temp("stay_in_room") >= 2)
        {
                tell_object(environment(this_object()), HIM + name() + 
                             HIM "��Ȼ��Զ����ȥ��һ�̾�û����Ӱ��\n" NOR);
                destruct(this_object());
        }
}
int receive_whistle(object me)
{
        object env;
        object temp;

        if ((env = environment()) && env == me)
        {
                write(name() + "�㲻�������������ٻ���ʲô����\n");
                return 1;
        }

        if (env == environment(me))
        {
        } else
        {
                if (env)
                {
                        if (env->is_character() && environment(env))
                                        env = environment(env);

                        message("vision", HIG "ͻȻ" + name() + HIG "��"
                                HIG "��ȥ��˲����ʧ�ˣ�\n\n" NOR, env);

                        if (interactive(env = environment()))
                        {
                                env->delete_temp("is_riding"); 
                                this_object()->delele_temp("is_rided_by");
                                tell_object(env, HIM + name() +
                                                 HIM "��Ȼ�����ȥ�ˣ�\n" NOR);
                        }
                }

                message_vision(HIG "$n" HIG "��֪������ܵ�$N" HIG "��ǰ��\n\n" NOR,
                               me, this_object());
        }

        move(environment(me));

        if (environment() != environment(me))
                return 1;
                
        if (objectp(temp = query_temp("is_riding")))
                UNRIDE_CMD->main(me);
                                
        RIDE_CMD->main(me, query("id"));
        return 1;
}

// ���ܴ������ݵĽӿں���
int receive_dbase_data(mixed data)
{
        if (! mapp(data))
                return 0;

        if (stringp(data["user"]))
                set_temp("owner_id", data["user"]);

        return 1;
}

// ���б������ݵĽӿں���
mixed save_dbase_data()
{
        mapping data;
        object  user;

        data = ([ ]);

        if (! objectp(user = environment()))
                data += ([ "user" : query_temp("owner_id") ]);
        else
        if (playerp(user))
                data += ([ "user" : user->query("id") ]);

        return data;
}

/*
// ��ȡ���̵�����
int restore()
{
        int r;

        if (base_name(this_object()) + ".c" == __FILE__)
                return 0;

        r = ::restore();
        set("no_sell", 1);
        return r;
}

// ��������
int save()
{
int res;

        if (base_name(this_object()) + ".c" == __FILE__)
                return 0;

return ::save();
}
*/

void die()
{
        destruct(this_object());
        return;
}
