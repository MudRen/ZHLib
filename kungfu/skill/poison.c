// poison.c 基本毒技
// Modified by Java Mar.1998
inherit SKILL;

void create() { seteuid(getuid()); }
string type() { return "poison"; }

int valid_learn(object me)
{
	int lv;
	lv = (int)me->query_skill("poison", 1);
	
	if (me->query("family/family_name") == "关外胡家")
		return 1;

    if (me->query("family/family_name") == "欧阳世家" || me->query("baituo/breed") >0 ) {
		if ( lv > 100 && me->query("baituo/breed") < lv )
			return notify_fail("你对毒术缺乏实际应用，难以继续提高。\n");
	}
	else {
		if (lv < 101 && lv > 50 && me->query("body_poison") < lv/10)
			return notify_fail("你体内聚毒过多，难以继续提高。\n");
		if (lv > 100 && me->query("body_poison") < lv)
			return notify_fail("你体内聚毒过多，难以继续提高。\n");
	}
	return 1;
}
