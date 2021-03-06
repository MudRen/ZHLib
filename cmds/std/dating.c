// skills.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob, man, *all;
	mapping fam, skl, lrn, map;
	string *sname, *mapped;
	int sp, dp;
	int i, cost, check_level;

	seteuid(getuid());

	all = all_inventory(environment(me));
	for (i = 0; i < sizeof(all); i++)
	{
		if (living(all[i]) && ! userp(all[i]) &&
		    all[i]->query("can_speak") &&
		    ! all[i]->query("not_living"))
		{
			man = all[i];
			break;
		}
	}

        if ((! (fam = me->query("family")) || fam["family_name"] != "丐帮"))
		return notify_fail("只有乞丐才能打探别人的技能！\n");

	if (! objectp(man))
		return notify_fail("周围没人能帮你去了解别人的技能！\n");

        if (me->query_skill("checking", 1) < 10)
		return notify_fail("你的打探本领尚未纯熟，无法"
				   "了解别人的技能！\n");

	if (! arg)
		return notify_fail("你要打听谁的技能？\n");

        if (present(arg, environment(me)))
		return notify_fail("你要打听的人就在边上，在这里"
				   "问不大妥当吧？\n");

	ob = find_player(arg);
	if (! ob) ob = find_living(arg);
	if (! ob) return notify_fail("你要打听谁的技能？\n");

	if (ob == me)
		return notify_fail("你没这麽笨吧，要别人"
				   "告诉你自己的技能？\n");

	cost = me->query("max_jing") / (me->query_skill("checking", 1) / 10) - 10;

	if (me->query("jing") <= cost)
		return notify_fail("现在你太累了，无法去打听别人的技能。\n");

	tell_object(me, "你走上前去，小心翼翼地向" + man->name() +
			"打听关于" + ob->name() + "的情况 ...\n");
	message("vision", "只见" + me->name() + "陪着笑脸跟" +
			  man->name() + "说着话，好象在打听些什么。\n", 
		environment(me), ({ me, man }) );

	sp = me->query_skill("checking") * 10 + 
	     me->query("jing") + man->query("jing");
	dp = ob->query("kar")*5 + ob->query("jing") * 2;
	
	if (random(sp) < random(dp))
		return notify_fail(man->name() + "摇了摇头，说道：这事"
				   "我可不清楚，" + RANK_D->query_respect(me) +
				   "还是去向别人打听一下吧！\n");

	me->receive_damage("jing", cost );

	skl = ob->query_skills();
	if (! sizeof(skl))
	{
		write(man->name() + "告诉你： " + ob->name() +
		      "目前并没有学会任何技能。\n");
		return 1;
	}
	write(man->name() + "告诉你： " + ob->name() +
	      "目前所学过的技能：\n\n");
	sname  = sort_array(keys(skl), (: strcmp :));
	
	map = ob->query_skill_map();
	if (mapp(map)) mapped = values(map);
	if (! mapped) mapped = ({});

	lrn = ob->query_learned();
	if (! mapp(lrn)) lrn = ([]);
	
	i = random(sizeof(skl));

	write(sprintf("%s%s%-40s" NOR " - %3d\n", 
		(lrn[sname[i]] >= (skl[sname[i]]+1) * (skl[sname[i]]+1)) ? HIM : "",
		(member_array(sname[i], mapped)==-1? "  ": "□"),
		to_chinese(sname[i]) + " (" + sname[i] + ")",
		skl[sname[i]]));
	check_level = me->query_skill("checking", 1);

	if (me->can_improve_skill("checking"))
		me->improve_skill("checking", random(me->query("int")));
	return 1;
}

int help(object me)
{
	write(@HELP
指令格式 : check|dating [<某人>]

这个指令可以让你打听别人所学过的技能。

你也可以指定一个和你有师徒关系的对象，用 skills|cha 可以查知对方的技能状况。

此命令为丐帮弟子专用，并需学习相应的技能。

HELP );
    return 1;
}
