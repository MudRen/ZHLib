#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
 
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("夺魂绝迹只能在战斗中对对手使用。\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
              (string)weapon->query("skill_type") != "whip")
                return notify_fail("你使用的武器不对。\n");

        if (me->query_skill("force") < 120)
                return notify_fail("你的内功火候不够，使不了夺魂绝迹。\n");

        if (me->query_skill("chanhun-suo", 1) < 80)
                return notify_fail("你的缠魂索功力太浅，使不了夺魂绝迹。\n");

        if (me->query("neili") < 200)
                return notify_fail("你的真气不够，无法使用夺魂绝迹。\n");

        msg = HIY "$N" HIY "诡异的一笑，手中" + weapon->name() +
              HIY "抖得笔直，劈向$n" HIY "手腕，可是待到中途却又停滞，转往$n"
              HIY "胸口挥去！\n\n" NOR;

        ap = me->query_skill("whip") + me->query_skill("force");
        if(living(target))
              dp = target->query_skill("force") + target->query_skill("parry");
        else  dp = 0;

        if (ap / 2 + random(ap) > dp)
        {
                damage = random(ap / 4);
                me->add("neili", -100);
                me->start_busy(1 + random(1));

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 10,
                                           HIR "结果$n" HIR "一声惨叫，未能看破$N"
                                           HIR "的企图，被这一鞭硬击在胸口，鲜血飞"
                                           "溅，皮肉绽开！\n" NOR);
        } else
        {
                me->add("neili", -100);
                me->start_busy(3);
                msg += CYN "可是$p" CYN "飞身一跃而起，躲避开了"
                       CYN "$P" CYN "的攻击！\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
