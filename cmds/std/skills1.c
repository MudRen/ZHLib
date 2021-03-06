//Cracked by Roath
// skills.c

#include <ansi.h>

inherit F_CLEAN_UP;

string *skill_level_desc = ({
        BLU "初学乍练" NOR,
        HIB "粗通皮毛" NOR,
        HIB "半生不熟" NOR,
        HIB "马马虎虎" NOR,
        HIB "驾轻就熟" NOR,
        CYN "出类拔萃" NOR,
        CYN "神乎其技" NOR,
        CYN "出神入化" NOR,
        HIC "登峰造极" NOR,
        HIC "一代宗师" NOR,
        HIW "深不可测" NOR
});

string *knowledge_level_desc = ({
        BLU "新学乍用" NOR,
        HIB "初窥门径" NOR,
        HIB "略知一二" NOR,
        HIB "马马虎虎" NOR,
        HIB "已有小成" NOR,
        CYN "心领神会" NOR,
        CYN "了然於胸" NOR,
        CYN "豁然贯通" NOR,
        HIC "举世无双" NOR,
        HIC "震古铄今" NOR,
        HIW "深不可测" NOR
});

string skill_level(string, int);

int main(object me, string arg)
{
        object ob;
        mapping skl, lrn, map;
        string *sname, *mapped;
        int i,j;

        seteuid(getuid());

        if(!arg)
                ob = me;
        else{
                ob = present(arg, environment(me));
//        if ( ob->query("SPSKILLS",1)  ) return ob->skills();           
                if (!ob) ob = find_player(arg);
                if (!ob) ob = find_living(arg);
                if (!ob) return notify_fail("你要察看谁的技能？\n");
        }

        if( ob!=me && !wizardp(me) && !ob->is_apprentice_of(me)
        && !me->is_apprentice_of(ob) && !ob->is_spouse_of(me) && !ob->is_baby_of(me))
                return notify_fail("你要察看谁的技能？\n");
			//Add !me->visible(me) by play 2002.7.28  
			// temp removed !me->visible(me) because bug by Xuanyuan

        skl = ob->query_skills();
        if(!sizeof(skl)) {
                write( (ob==me ? "你" : ob->name()) + "目前并没有学会任何技能。\n");
                return 1;
        }
        write( "[44;1m[1;33m"+(ob==me ? "你" : ob->name()) +"[44;1m[1;33m目前所学过的技能：（共"+chinese_number(sizeof(skl))+"项技能）                               [37;0m\n\n");
        sname  = sort_array( keys(skl), (: strcmp :) );
        
        map = ob->query_skill_map();
        if( mapp(map) ) mapped = values(map);
        if( !mapped ) mapped = ({});

        lrn = ob->query_learned();
        if( !mapp(lrn) ) lrn = ([]);
        j=0;

        for(i=0; i<sizeof(skl); i++) {
                if(SKILL_D(sname[i])->type()=="knowledge"){
                j=j+1;
                }
        }
        if(j>0) { printf("[32m┌[42m%21s    [40m[32m──────────────────────┐[37;0m\n", "[37m"+chinese_number(j)+"项知识");}
        for(i=0; i<sizeof(skl); i++) {
        	if(SKILL_D(sname[i])->type()=="knowledge"){
                printf("[32m│[37;0m%s%s%-40s" NOR " - %-10s %3d/%6d[32m│[37;0m\n", 
                        (member_array(sname[i], mapped)==-1? "  ": "[1;32m□[37;0m"),
                        ((lrn[sname[i]] >= (skl[sname[i]]+1) * (skl[sname[i]]+1)) ? HIM : ""),
                        (to_chinese(sname[i]) + " (" + sname[i] + ")"),
                        skill_level(SKILL_D(sname[i])->type(), skl[sname[i]]),
                        skl[sname[i]], (int)lrn[sname[i]]
                );
                }
        }
        if(j>0) { write("[32m└────────────────────────────────┘[37;0m\n");}

	j=0;
        for(i=0; i<sizeof(skl); i++) {
        	if(SKILL_D(sname[i])->type() != "knowledge" && (sname[i] == "force" || sname[i] == "cuff" || sname[i] == "strike" || sname[i] == "finger" || sname[i] == "claw" || sname[i] == "hand" || sname[i] == "kick" || sname[i] == "sword" || sname[i] == "blade" || sname[i] == "club" || sname[i] == "pike" || sname[i] == "staff" || sname[i] == "stick" || sname[i] == "hook" ||  sname[i] == "dodge" ||  sname[i] == "parry" || sname[i] == "whip" || sname[i] == "hammer" || sname[i] == "begging" || sname[i] == "training" || sname[i] == "checking" || sname[i] == "digging" || sname[i] == "swimming" || sname[i] == "feixing-shu" || sname[i] == "archery" || sname[i] == "throwing" || sname[i] == "jinshe-zhuifa" || sname[i] == "axe" || sname[i] == "beidou-zhenfa" )){
        	j=j+1;
                }
        }
        if(j>0) { printf("[32m┌[42m%21s    [40m[32m──────────────────────┐[37;0m\n", "[37m"+chinese_number(j)+"项基本功夫");}
        for(i=0; i<sizeof(skl); i++) {
        	if(SKILL_D(sname[i])->type() != "knowledge" && (sname[i] == "force" || sname[i] == "cuff" || sname[i] == "strike" || sname[i] == "finger" || sname[i] == "claw" || sname[i] == "hand" || sname[i] == "kick" || sname[i] == "sword" || sname[i] == "blade" || sname[i] == "club" || sname[i] == "pike" || sname[i] == "staff" || sname[i] == "stick" || sname[i] == "hook" ||  sname[i] == "dodge" ||  sname[i] == "parry" || sname[i] == "whip" || sname[i] == "hammer" || sname[i] == "begging" || sname[i] == "training" || sname[i] == "checking" || sname[i] == "digging" || sname[i] == "swimming" || sname[i] == "feixing-shu" || sname[i] == "archery" || sname[i] == "throwing" || sname[i] == "jinshe-zhuifa" || sname[i] == "axe" || sname[i] == "beidou-zhenfa" )){
                printf("[32m│[37;0m%s%s%-40s" NOR " - %-10s %3d/%6d[32m│[37;0m\n", 
                        (member_array(sname[i], mapped)==-1? "  ": "[1;32m□[37;0m"),
                        ((lrn[sname[i]] >= (skl[sname[i]]+1) * (skl[sname[i]]+1)) ? HIM : ""),
                        (to_chinese(sname[i]) + " (" + sname[i] + ")"),
                        skill_level(SKILL_D(sname[i])->type(), skl[sname[i]]),
                        skl[sname[i]], (int)lrn[sname[i]]
                );
                }
        }
        if(j>0) { write("[32m└────────────────────────────────┘[37;0m\n");}

	j=0;
        for(i=0; i<sizeof(skl); i++) {
        	if(SKILL_D(sname[i])->type() != "knowledge" && (sname[i] != "force" && sname[i] != "cuff" && sname[i] != "strike" && sname[i] != "finger" && sname[i] != "claw" && sname[i] != "hand" && sname[i] != "kick" && sname[i] != "sword" && sname[i] != "blade" && sname[i] != "club" && sname[i] != "pike" && sname[i] != "staff" && sname[i] != "stick" && sname[i] != "hook" && sname[i] != "dodge" && sname[i] != "parry" && sname[i] != "whip" && sname[i] != "hammer" && sname[i] != "begging" && sname[i] != "training" && sname[i] != "checking" && sname[i] != "digging" && sname[i] != "swimming" && sname[i] != "feixing-shu" && sname[i] != "archery" && sname[i] != "throwing" && sname[i] != "jinshe-zhuifa" && sname[i] != "axe" && sname[i] != "beidou-zhenfa" )){
        	j=j+1;
                }
        }
        if(j>0) { printf("[32m┌[42m%21s    [40m[32m──────────────────────┐[37;0m\n", "[37m"+chinese_number(j)+"项特殊功夫");}
        for(i=0; i<sizeof(skl); i++) {
        	if(SKILL_D(sname[i])->type() != "knowledge" && (sname[i] != "force" && sname[i] != "cuff" && sname[i] != "strike" && sname[i] != "finger" && sname[i] != "claw" && sname[i] != "hand" && sname[i] != "kick" && sname[i] != "sword" && sname[i] != "blade" && sname[i] != "club" && sname[i] != "pike" && sname[i] != "staff" && sname[i] != "stick" && sname[i] != "hook" && sname[i] != "dodge" && sname[i] != "parry" && sname[i] != "whip" && sname[i] != "hammer" && sname[i] != "begging" && sname[i] != "training" && sname[i] != "checking" && sname[i] != "digging" && sname[i] != "swimming"  && sname[i] != "feixing-shu" && sname[i] != "archery" && sname[i] != "throwing" && sname[i] != "jinshe-zhuifa" && sname[i] != "axe" && sname[i] != "beidou-zhenfa" )){
                printf("[32m│[37;0m%s%s%-40s" NOR " - %-10s %3d/%6d[32m│[37;0m\n", 
                        (member_array(sname[i], mapped)==-1? "  ": "[1;32m□[37;0m"),
                        ((lrn[sname[i]] >= (skl[sname[i]]+1) * (skl[sname[i]]+1)) ? HIM : ""),
                        (to_chinese(sname[i]) + " (" + sname[i] + ")"),
                        skill_level(SKILL_D(sname[i])->type(), skl[sname[i]]),
                        skl[sname[i]], (int)lrn[sname[i]]
                );
                }
        }
        if(j>0) { write("[32m└────────────────────────────────┘[37;0m\n");}


        return 1;
}

string skill_level(string type, int level)
{
        int grade;

        grade = level / 40;

        switch(type) {
                case "knowledge":
                        if( grade >= sizeof(knowledge_level_desc) )
                                grade = sizeof(knowledge_level_desc)-1;
                        return knowledge_level_desc[grade];
                default:
                        if( grade >= sizeof(skill_level_desc) )
                                grade = sizeof(skill_level_desc)-1;
                        return skill_level_desc[grade];
        }
}

int help(object me)
{
        write(@HELP
指令格式 : skills|cha [<某人>]

这个指令可以让你(你)查询所学过的技能。

你也可以指定一个和你有师徒关系的对象，用 skills 可以查知对方的技能状况。

巫师可以查询任何人或 NPC 的技能状况。

HELP
    );
    return 1;
}
