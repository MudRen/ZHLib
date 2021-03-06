// feng.c 打狗棒封字决
// Rama 2001/11/11
// 提高了命中率
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
inherit F_DBASE;

int perform(object me, object target)
{
        string* msghit, msg;
        object weapon;
        int  feng_busy;
        int feng_addspeed;
        int feng_cost;
        int feng_duration;
        int feng_parry;
        int ap,dp;
        string *limb, type, limb_hurt;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) 
        ||          !living (target) )
                return notify_fail("封字诀只能对战斗中的对手使用。\n");

        if( target->is_busy() ) {
                me->add("neili", -10);
                me->add("jingli", -5);
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧　\n");
        }

        if( me->query_temp("ban",1) )
                return notify_fail("你已在使用拌字诀！\n");

        if(! living(target))
                return notify_fail("对手已经这样，你不用再使用封字诀！\n");

        if( me->query_temp("pfmfeng",1) )
                return notify_fail("你已在使用封字诀！\n");

        if( me->query_skill_mapped("force") != "huntian-qigong" )
                return notify_fail("你所用的并非混天气功，无法施展封字诀！\n");

        if( me->query_skill("force") < 250 )
                return notify_fail("你的混天气功火候未到，无法施展封字诀！\n");

        if( me->query_skill("staff") < 250 )
                return notify_fail("你的打狗棒法修为不足，还不能使用封字诀！\n");

        if( me->query("neili") <= 1000 )
                return notify_fail("你的内力不够！\n");

        if( me->query("jingli") <= 600 )
                return notify_fail("你的精力不够！\n");

        if( !objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "staff")
                 return notify_fail("空手如何使用封字决？？\n");

        msghit = ({
                "\n$N运起打狗棒法中的「封」字诀，棒法全是横使，并不攻击敌身，一条"+(string)weapon->query("name")+HIG"化成一片碧墙，挡在面门。\n",
                "\n$N大喝一声，运起"+(string)weapon->query("name")+HIG"，使出打狗棒法的「封」字诀，紧紧守住门户。\n",
                "\n$N提起"+(string)weapon->query("name")+HIG"，使个打狗棒法的「封」字诀，护住身前，挡住攻势。\n",
                "\n$N挥起"+(string)weapon->query("name")+HIG"，使出打狗棒法中的一招「恶犬拦路」，乃属「封」字诀。\n"
        });
        msg = HIG"\n"+ msghit[random(sizeof(msghit))] +"\n" NOR;
        message_vision(msg, me, target);

        ap = me->query_skill("force") + me->query_skill("staff") + me->query_str()*10 + me->query("jiali");
        dp = target->query_skill("dodge") + target->query_skill("parry") + target->query_dex()*10 + target->query("jiali");

        if (ap/3 + random(ap) > dp)
        {
                msghit = ({
                        "「封」字诀甚是精妙，东突西冲，$n立感不支，当下攻势全被挡住。\n",
                        "只见棒影飘飘，「封」字诀登时将$n身前数尺之地尽数封住了。\n",
                        "$n突见"+(string)weapon->query("name")+HIY"来势神妙无方，一时竟然被封得难以攻入。\n"
                });
                msg = HIY"\n"+ msghit[random(sizeof(msghit))] +"\n" NOR;
                message_vision(msg, me, target);

                feng_busy= me->query_skill("staff")/15;
                feng_parry = feng_busy * 5;
                
                me->add_temp("apply/parry", feng_parry);
                target->add("qi",-me->query_skill("staff")/5);
                target->add("jing",-me->query_skill("staff")/5);
                target->set_temp("feng",1);
                me->set_temp("pfmfeng",1);
                target->start_busy(1+random(3));

                feng_duration= 2 + feng_busy/( weapon->weight()/1000);
                
                call_out("remove_effect",feng_duration,me,target,feng_parry);
        }
        else
        {
                msghit = ({
                        "$n攻时敬，守时严，并没有被封住。\n",
                        "$n快速变招，百忙中急退两步，避开了「封」字诀。\n"
                });
                msg = CYN"\n"+ msghit[random(sizeof(msghit))] +"\n" NOR;
                me->start_busy( 2 + random(3));
                message_vision(msg, me, target);
        }

        feng_cost = me->query_skill("staff") / 2;
        me->add("neili", -feng_cost );
        me->add("jingli", -feng_cost/3 );

        return 1;
}

private int remove_effect(object me, object target, int feng_parry)
{
        int skills;
        object weapon;
        if (objectp(me))
        {
                me->add_temp("apply/parry",  -feng_parry);
                me->delete_temp("pfmfeng");
        }
        if (objectp(target))
                target->delete_temp("feng");

        if(objectp(me) && objectp(target) && target->is_fighting(me) )
                message_vision(HIG"\n$N的棒招陡变，打狗棒的「封」字诀已然瓦解。\n"NOR ,me,target); 
        return 1;
}

