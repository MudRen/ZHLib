// skills.c

#include <ansi.h>

inherit F_CLEAN_UP;

string bar_string = "                                    ";

string *valid_types = ({
        "force",
        "dodge",
        "unarmed",
        "cuff",
        "strike",
        "finger",
        "hand",
        "claw",
        "sword",
        "blade",
        "staff",
	"hammer",
        "club",
        "whip",
        "dagger",
        "throwing",
        "parry",
        "magic",
	"medical",
        "poison",
        "chuixiao-jifa",
        "tanqin-jifa",
        "guzheng-jifa",
//        "cooking",
        "array",
});

string *skill_level_desc = ({
        NOR GRN "³õÑ§Õ§Á·" NOR,
        NOR HIG "´ÖÍ¨Æ¤Ã«" NOR,
        NOR BLU "°ëÉú²»Êì" NOR,
        NOR HIB "ÂíÂí»¢»¢" NOR,
        NOR YEL "¼İÇá¾ÍÊì" NOR,
        NOR HIY "³öÀà°ÎİÍ" NOR,
        NOR CYN "ÉñºõÆä¼¼" NOR,
        NOR HIC "³öÉñÈë»¯" NOR,
        NOR WHT "µÇ·åÔì¼«" NOR,
        NOR HIW "Ò»´ú×ÚÊ¦" NOR,
        NOR HIM "Éî²»¿É²â" NOR
});

string *knowledge_level_desc = ({
        NOR GRN "ĞÂÑ§Õ§ÓÃ" NOR,
        NOR HIG "³õ¿úÃÅ¾¶" NOR,
        NOR BLU "ÂÔÖªÒ»¶ş" NOR,
        NOR HIB "ÂíÂí»¢»¢" NOR,
        NOR YEL "ÒÑÓĞĞ¡³É" NOR,
        NOR HIY "ĞÄÁìÉñ»á" NOR,
        NOR CYN "ÁËÈ»ì¶ĞØ" NOR,
        NOR HIC "»íÈ»¹áÍ¨" NOR,
        NOR WHT "¾ÙÊÀÎŞË«" NOR,
        NOR HIW "Õğ¹Åîå½ñ" NOR,
        NOR HIM "Éî²»¿É²â" NOR
});

int all_skill(object me,object ob);
string skill_level(string, int);
int sort_skill(string sk1, string sk2, mapping spos);
int filter_for_enable(string skill, string skill1);
int filter_for_main(string skill, string skill1);
int filter_for_combine(string skill, string skill1);
string tribar_graph(int a);

int main(object me, string arg)
{
	object ob;
	mapping skl, lrn, map;
	string *sname, *mapped, str, str1, str2, skill1;
        string skillname, skcolor;
        string *basic;
        mixed  *lists;
        string *others;
        string fname;
        int valid_check;
        int lvl;
	int i, k;

	seteuid(getuid());

        skill1 = 0;
	if (! arg)
		ob = me;
	else
	{
                string *temp;
		if (sscanf(arg, "%s of %s", skill1, arg) == 2)
                        ; else
                if (temp = explode(arg, " "))
                {
                        if (sizeof(temp) < 2)
                                arg = "me";
                        else
                                arg = implode(temp[0..sizeof(temp) - 2], " ");
                        skill1 = temp[sizeof(temp) - 1];

                        if (file_size(SKILL_D(skill1) + ".c") <= 0)
                        {
                                if (sizeof(temp) < 2)
                                        arg = skill1;
                                else
                                        arg += " " + skill1;
                                ob = present(arg, environment(me));
                                skill1 = 0;
                        }
                } else
                {
                        // if the user was not wizard, I will
                        // treat the arg as skill1, and the
                        // object he check is hiself.
                        if (! wizardp(me) && (! (ob = present(arg, environment(me))) ||
                            ! ob->is_character() ||
			    ! me->is_apprentice_of(ob)))
                        {
                                skill1 = arg;
                                arg = "me";
                        }
                }

		if (ob && ! ob->is_character())
			ob = 0;

                if (skill1 && file_size(SKILL_D(skill1) + ".c") <= 0)
                {
                        if (objectp(ob))
                        {
                                arg = 0;
                                skill1 = 0;
                        } else
                                return notify_fail("Ã»ÓĞ(" + skill1 +
						   ")ÕâÖÖ¼¼ÄÜ¡£\n");
                }

                if (! ob || ! ob->is_character())
                {
        		if (arg == "me")
        			ob = me;
        		else
        			ob = present(arg, environment(me));
        
        		if (! ob || ! ob->is_character()) ob = find_player(arg);
        		if (! ob || ! ob->is_character()) ob = find_living(arg);
                }

		if (! ob || ! ob->is_character())
			return notify_fail("ÄãÒª²ì¿´Ë­µÄ¼¼ÄÜ£¿\n");
	}

        if (ob != me)
        {
                // call the player, if the player has override the
                // the function & return a nonzero valud, I will
                // return success.
                if ((int)ob->skills(me, skill1))
                        return 1;
        }

        if (ob == me || wizardp(me) ||
            ob->is_apprentice_of(me) ||
            me->is_apprentice_of(ob) ||
            ob->query("owner") == me->query("id") ||
            me->query("couple/couple_id") == ob->query("id") ||
            me->is_brother(ob))
                valid_check = 1;
        else
        {
                fname = me->query("league/league_name");
                if (stringp(fname) && fname == ob->query("league/league_name"))
                        valid_check = 1;
                else
                        valid_check = 0;
        }

        if (! valid_check)
		return notify_fail("Ö»ÓĞÎ×Ê¦»òÓĞÊ¦Í½/·òÆŞ/½á°İ/Í¬ÃË¹ØÏµµÄÈË"
				   "²ÅÄÜ²ì¿´ËûÈËµÄ¼¼ÄÜ¡£\n");

	skl = ob->query_skills();
	if (! sizeof(skl))
	{
		write((ob==me ? "Äã" : ob->name()) +
		      "Ä¿Ç°²¢Ã»ÓĞÑ§»áÈÎºÎ¼¼ÄÜ¡£\n");
		return 1;
	}

        // calucate spos to sort
        sname = keys(skl);

        str = (ob == me ? "Äã" : ob->name()) + "Ä¿Ç°ËùÑ§µ½µÄ";
        // filter array by skill1
        if (skill1)
        {
                // filter the skill array by skill1
                if (member_array(skill1, valid_types) != -1)
                {
                        // skill1 is a basic skill
                        sname = filter_array(sname, (: filter_for_enable :), skill1);
                        str1 = to_chinese(skill1) + "¼°Ïà¹Ø¼¼ÄÜ";
                } else
                if (SKILL_D(skill1)->main_skill() &&
                    member_array(SKILL_D(skill1)->main_skill(), sname) == -1)
                {
                        // skill1 is a sub skill
                        skill1 = SKILL_D(skill1)->main_skill();
                        sname = filter_array(sname, (: filter_for_main :), skill1);
                        str1 = to_chinese(skill1) + "ÖĞµÄÕĞÊ½";
                } else
                {
                        sname = filter_array(sname, (: filter_for_combine :), skill1);
                        str1 = to_chinese(skill1) + "ºÍ¿ÉÒÔ¼¤·¢µÄ»ù´¡Îä¼¼ÓëÄÜ¹»»¥±¸µÄ¼¼ÄÜ";
                }
        } else
        {
                all_skill(me,ob);
                return 1;
        }

        str += str1;
        if (! sizeof(sname))
        {
                write("ÄãÄ¿Ç°»¹Ã»ÓĞÕÆÎÕ¸Ã¼¼ÄÜ¡£\n");
                return 1;
        }

        // sort all the skills
        // select all the basic skill of the skill list
        basic = filter_array(valid_types, (: member_array($1, $(sname)) != -1 :));

        // allocate the string array for each basic skill
        lists = allocate(sizeof(basic));

        // allocate the other skill for none apply to all the basic skill
        others = ({ });

        // select out all the special skill & other skill
        sname -= basic;
        for (i = 0; i < sizeof(sname); i++)
        {
                // let's check every special skill & other skill
                if (! sname[i]) continue;

                // enable for basic skill
                for (k = 0; k < sizeof(basic); k++)
                {
                        string main_skill;

                        if (SKILL_D(sname[i])->valid_enable(basic[k]))
                        {
                                // yes, I record this special skill
                                if (! lists[k])
                                        lists[k] = ({ sname[i] });
                                else
                                        lists[k] += ({ sname[i] });

                                // Is this a sub skill ?
                                if (main_skill = SKILL_D(sname[i])->main_skill())
                                {
                                        // yes, I select out all the other sub skills
                                        int st;
                                        for (st = i + 1; st < sizeof(sname); st++)
                                                if (sname[st] &&
                                                    SKILL_D(sname[st])->main_skill() == main_skill)
                                                {
                                                        // record it
                                                        lists[k] += ({ sname[st] });
                                                        sname[st] = 0;
                                                }
                                }

                                break;
                        }
                }

                if (k == sizeof(basic))
                        // It can enable on basic skill, it must be a others skill
                        others += ({ sname[i] });
        }

        // let me combine all the skill in string array: sname
        sname = ({ });
        for (i = 0; i < sizeof(basic); i++)
        {
                sname += ({ basic[i] });
                if (lists[i]) sname += lists[i];
        }

        sname += others;

        // get the skill map
	map = ob->query_skill_map();
	if (mapp(map)) mapped = values(map);
	if (! mapped) mapped = ({});

	lrn = ob->query_learned();
	if (! mapp(lrn)) lrn = ([]);
       str2 = "                                                                   ";
       str2 = str + str2[strlen(str)..strlen(str2)];
       str = BBLU HIY + str2 + NOR;
	str += "\n\n";
       str2 = "©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©´";
       str2 = str2[strlen(str1)..strlen(str2)];
	str += sprintf(YEL "©°" NOR BYEL HIC "%" + sprintf("%d",strlen(str1)) + "s" + NOR YEL + "%s\n" NOR,
                     str1,str2);
 
       	for (i = 0; i < sizeof(sname); i++)
	{
		int percent;
                skillname = to_chinese(sname[i]);
                switch (strlen(skillname))
                {
                case 6:
                        skillname = sprintf("%c%c %c%c %c%c", skillname[0], skillname[1],
                                             skillname[2], skillname[3],
                                             skillname[4], skillname[5]);
                        break;
                case 4:
                        skillname = sprintf("%c%c    %c%c", skillname[0], skillname[1],
                                             skillname[2], skillname[3]);
                        break;
                }

                if (member_array(sname[i], valid_types) != -1)
                        skcolor = GRN;
                else
                        skcolor = WHT;

                if (! objectp(find_object(SKILL_D(sname[i]))) &&
                    ! objectp(load_object(SKILL_D(sname[i]))))
                {
                        write(HIR "Error(No such skill):" + sname[i] + "\n" NOR);
                        continue;
                }
                lvl = skl[sname[i]];
		percent = lrn[sname[i]] * 100 / ((lvl + 1) * (lvl + 1) + 1);
		if (percent > 100) percent = 100;
		str += sprintf(YEL "©¦" NOR "%s%s%s%-40s" NOR WHT " - %-10s %4d/%3d%%"NOR YEL " ©¦\n" NOR, 
                        skcolor,
			(lrn[sname[i]] >= (skl[sname[i]]+1) * (skl[sname[i]]+1)) ? HIM : "",
			(member_array(sname[i], mapped)==-1? "  ": NOR HIG "¡õ" NOR + skcolor),
			skillname + " (" + sname[i] + ")",
                     skill_level(SKILL_D(sname[i])->type(), lvl),
			lvl, percent);
	}

	str += YEL "©¸©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¼\n" NOR;
	me->start_more(str);
	return 1;
}

int all_skill(object me,object ob)
{
        mapping skl, lrn, map;
        string *sname, *mapped, name;
        string skillname, skcolor;
        int i,j,lvl,percent;

        skl = ob->query_skills();
        if(!sizeof(skl)) {
                write( (ob==me ? "Äã" : ob->name()) + "Ä¿Ç°²¢Ã»ÓĞÑ§»áÈÎºÎ¼¼ÄÜ¡£\n");
                return 1;
        }
	if(ob==me)name="Äã";
	else name=ob->name();
	write( "[44;1m[1;33m"+name+"[44;1m[1;33mÄ¿Ç°ËùÑ§¹ıµÄ¼¼ÄÜ£º£¨¹²"+chinese_number(sizeof(skl))+"Ïî¼¼ÄÜ£©"+tribar_graph(strlen(name)+strlen(chinese_number(sizeof(skl))))+"[37;0m\n\n");
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
        if(j>0) { printf(YEL "©°" NOR BYEL HIC "%16s    " NOR YEL "©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©´\n" NOR, chinese_number(j)+"ÏîÖªÊ¶");}
        for(i=0; i<sizeof(skl); i++) {
        	if(SKILL_D(sname[i])->type()=="knowledge"){
                skillname = to_chinese(sname[i]);
                switch (strlen(skillname))
                {
                case 6:
                        skillname = sprintf("%c%c %c%c %c%c", skillname[0], skillname[1],
                                             skillname[2], skillname[3],
                                             skillname[4], skillname[5]);
                        break;
                case 4:
                        skillname = sprintf("%c%c    %c%c", skillname[0], skillname[1],
                                             skillname[2], skillname[3]);
                        break;
                }

                if (member_array(sname[i], valid_types) != -1)
                        skcolor = GRN;
                else
                        skcolor = WHT;

                if (! objectp(find_object(SKILL_D(sname[i]))) &&
                    ! objectp(load_object(SKILL_D(sname[i]))))
                {
                        write(HIR "Error(No such skill):" + sname[i] + "\n" NOR);
                        continue;
                }
                lvl = skl[sname[i]];
		percent = lrn[sname[i]] * 100 / ((lvl + 1) * (lvl + 1) + 1);
		if (percent > 100) percent = 100;
		printf(YEL "©¦" NOR "%s%s%s%-40s" NOR WHT " - %-10s %4d/%3d%%"NOR YEL " ©¦\n" NOR, 
                        skcolor,
			(lrn[sname[i]] >= (skl[sname[i]]+1) * (skl[sname[i]]+1)) ? HIM : "",
			(member_array(sname[i], mapped)==-1? "  ": NOR HIG "¡õ" NOR + skcolor),
			skillname + " (" + sname[i] + ")",
                     skill_level(SKILL_D(sname[i])->type(), lvl),
			lvl, percent);
                }
        }
        if(j>0) { write(YEL "©¸©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¼\n" NOR);}

	j=0;
        for(i=0; i<sizeof(skl); i++) {
        	if(member_array(sname[i],valid_types) != -1){
        	j=j+1;
                }
        }
        if(j>0) { printf(YEL "©°" NOR BYEL HIC "%16s    " NOR YEL "©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©´\n" NOR, chinese_number(j)+"Ïî»ù±¾Îä¹¦");}
        for(i=0; i<sizeof(skl); i++) {
        	if(member_array(sname[i],valid_types) != -1){
                skillname = to_chinese(sname[i]);
                switch (strlen(skillname))
                {
                case 6:
                        skillname = sprintf("%c%c %c%c %c%c", skillname[0], skillname[1],
                                             skillname[2], skillname[3],
                                             skillname[4], skillname[5]);
                        break;
                case 4:
                        skillname = sprintf("%c%c    %c%c", skillname[0], skillname[1],
                                             skillname[2], skillname[3]);
                        break;
                }

                if (member_array(sname[i], valid_types) != -1)
                        skcolor = GRN;
                else
                        skcolor = WHT;

                if (! objectp(find_object(SKILL_D(sname[i]))) &&
                    ! objectp(load_object(SKILL_D(sname[i]))))
                {
                        write(HIR "Error(No such skill):" + sname[i] + "\n" NOR);
                        continue;
                }
                lvl = skl[sname[i]];
		percent = lrn[sname[i]] * 100 / ((lvl + 1) * (lvl + 1) + 1);
		if (percent > 100) percent = 100;
		printf(YEL "©¦" NOR "%s%s%s%-40s" NOR WHT " - %-10s %4d/%3d%%"NOR YEL " ©¦\n" NOR, 
                        skcolor,
			(lrn[sname[i]] >= (skl[sname[i]]+1) * (skl[sname[i]]+1)) ? HIM : "",
			(member_array(sname[i], mapped)==-1? "  ": NOR HIG "¡õ" NOR + skcolor),
			skillname + " (" + sname[i] + ")",
                     skill_level(SKILL_D(sname[i])->type(), lvl),
			lvl, percent);
                }
        }
        if(j>0) { write(YEL "©¸©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¼\n" NOR);}

	j=0;
        for(i=0; i<sizeof(skl); i++) {
        	if(SKILL_D(sname[i])->type() != "knowledge" && SKILL_D(sname[i])->type() != "knowledge2" && member_array(sname[i],valid_types) == -1){
        	j=j+1;
                }
        }
        if(j>0) { printf(YEL "©°" NOR BYEL HIC "%16s    " NOR YEL "©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©´\n" NOR, chinese_number(j)+"ÏîÌØÊâÎä¹¦");}
        for(i=0; i<sizeof(skl); i++) {
        	if(SKILL_D(sname[i])->type() != "knowledge" && SKILL_D(sname[i])->type() != "knowledge2" && member_array(sname[i],valid_types) == -1){
                skillname = to_chinese(sname[i]);
                switch (strlen(skillname))
                {
                case 6:
                        skillname = sprintf("%c%c %c%c %c%c", skillname[0], skillname[1],
                                             skillname[2], skillname[3],
                                             skillname[4], skillname[5]);
                        break;
                case 4:
                        skillname = sprintf("%c%c    %c%c", skillname[0], skillname[1],
                                             skillname[2], skillname[3]);
                        break;
                }

                if (member_array(sname[i], valid_types) != -1)
                        skcolor = GRN;
                else
                        skcolor = WHT;

                if (! objectp(find_object(SKILL_D(sname[i]))) &&
                    ! objectp(load_object(SKILL_D(sname[i]))))
                {
                        write(HIR "Error(No such skill):" + sname[i] + "\n" NOR);
                        continue;
                }
                lvl = skl[sname[i]];
		percent = lrn[sname[i]] * 100 / ((lvl + 1) * (lvl + 1) + 1);
		if (percent > 100) percent = 100;
		printf(YEL "©¦" NOR "%s%s%s%-40s" NOR WHT " - %-10s %4d/%3d%%"NOR YEL " ©¦\n" NOR, 
                        skcolor,
			(lrn[sname[i]] >= (skl[sname[i]]+1) * (skl[sname[i]]+1)) ? HIM : "",
			(member_array(sname[i], mapped)==-1? "  ": NOR HIG "¡õ" NOR + skcolor),
			skillname + " (" + sname[i] + ")",
                     skill_level(SKILL_D(sname[i])->type(), lvl),
			lvl, percent);
                }
        }
        if(j>0) { write(YEL "©¸©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¼\n" NOR);}

        j=0;

        for(i=0; i<sizeof(skl); i++) {
                if(SKILL_D(sname[i])->type()=="knowledge2"){
                j=j+1;
                }
        }
        if(j>0) { printf(YEL "©°" NOR BYEL HIC "%16s    " NOR YEL "©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©´\n" NOR, chinese_number(j)+"ÏîÖ°Òµ¼¼ÄÜ");}
        for(i=0; i<sizeof(skl); i++) {
        	if(SKILL_D(sname[i])->type()=="knowledge2"){
                skillname = to_chinese(sname[i]);
                switch (strlen(skillname))
                {
                case 6:
                        skillname = sprintf("%c%c %c%c %c%c", skillname[0], skillname[1],
                                             skillname[2], skillname[3],
                                             skillname[4], skillname[5]);
                        break;
                case 4:
                        skillname = sprintf("%c%c    %c%c", skillname[0], skillname[1],
                                             skillname[2], skillname[3]);
                        break;
                }

                if (member_array(sname[i], valid_types) != -1)
                        skcolor = GRN;
                else
                        skcolor = WHT;

                if (! objectp(find_object(SKILL_D(sname[i]))) &&
                    ! objectp(load_object(SKILL_D(sname[i]))))
                {
                        write(HIR "Error(No such skill):" + sname[i] + "\n" NOR);
                        continue;
                }
                lvl = skl[sname[i]];
		percent = lrn[sname[i]] * 100 / ((lvl + 1) * (lvl + 1) + 1);
		if (percent > 100) percent = 100;
		printf(YEL "©¦" NOR "%s%s%s%-40s" NOR WHT " - %-10s %4d/%3d%%"NOR YEL " ©¦\n" NOR, 
                        skcolor,
			(lrn[sname[i]] >= (skl[sname[i]]+1) * (skl[sname[i]]+1)) ? HIM : "",
			(member_array(sname[i], mapped)==-1? "  ": NOR HIG "¡õ" NOR + skcolor),
			skillname + " (" + sname[i] + ")",
                     skill_level(SKILL_D(sname[i])->type(), lvl),
			lvl, percent);
                }
        }
        if(j>0) { write(YEL "©¸©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¼\n" NOR);}

        return 1;
}

int filter_for_enable(string skill, string skill1)
{
        return (skill == skill1) || (SKILL_D(skill)->valid_enable(skill1));
}

int filter_for_main(string skill, string skill1)
{
        return (SKILL_D(skill)->main_skill() == skill1);
}

int filter_for_combine(string skill, string skill1)
{
        return (SKILL_D(skill1)->valid_enable(skill)) ||
               (SKILL_D(skill)->valid_combine(skill1)) ||
               (skill == skill1);
}

string skill_level(string type, int level)
{
        int grade;

        grade = level / 50;

        switch(type) {
                case "knowledge":
                        if( grade >= sizeof(knowledge_level_desc) )
                                grade = sizeof(knowledge_level_desc)-1;
                        return knowledge_level_desc[grade];
                case "knowledge2":
                        if( grade >= sizeof(knowledge_level_desc) )
                                grade = sizeof(knowledge_level_desc)-1;
                        return knowledge_level_desc[grade];
                default:
                        if( grade >= sizeof(skill_level_desc) )
                                grade = sizeof(skill_level_desc)-1;
                        return skill_level_desc[grade];
        }
}

string tribar_graph(int a)
{
	return bar_string[0..(36 - a)];
}

int help(object me)
{
	write(@HELP
Ö¸Áî¸ñÊ½ : skills|cha [<¼¼ÄÜÃû> of <Ä³ÈË | me >] | [<Ä³ÈË>]

Õâ¸öÖ¸Áî¿ÉÒÔÈÃÄã(Äã)²éÑ¯ËùÑ§¹ıµÄ¼¼ÄÜ¡£

ÄãÒ²¿ÉÒÔÖ¸¶¨Ò»¸öºÍÄãÓĞÊ¦Í½¹ØÏµµÄ¶ÔÏó£¬ÓÃ skills ¿ÉÒÔ²éÖª¶Ô·½µÄ¼¼ÄÜ×´¿ö¡£
Ò²¿ÉÒÔ²éÑ¯Ä³ÈËÄ³Ïî¼¼ÄÜµÄÇé¿ö£¬±ÈÈçskills taiji-shengong of song£¬ »òÕß
ÊÇskills literate of me£¬ ÓÃÕâÖÖ·½·¨²éÑ¯Ê±·ÖÒÔÏÂ¼¸ÖÖÇé¿ö£º

1 Èç¹û²éÑ¯µÄ¼¼ÄÜÊÇÒ»ÖÖ»ù±¾Îä¼¼£¬½«Í¬Ê±·µ»ØËùÓĞÔÚÕâÖÖ»ù±¾Îä¼¼µÄ»ù´¡ÉÏÄÜ
  ¹»¼¤·¢µÄÎä¹¦¼¼ÄÜ¡£

2 Èç¹û²éÑ¯µÄ¼¼ÄÜÊÇÒ»ÖÖÎä¼¼ÖĞµÄÄ³Ğ©ÕĞÊ½Â·Êı£¬±ÈÈç½µÁúÊ®°ËÕÆ£¬»òÊÇ½µÁúÊ®
  °ËÕÆÖĞµÄÉñÁú°ÚÎ²µÈ£¬ÔòÏÔÊ¾Íæ¼ÒÑ§µ½ÓëÖ®Ïà¹ØµÄÕĞÊ½Â·Êı¡£Èç¹ûÍæ¼ÒÒÑ¾­½«
  ÕâÖÖÎä¼¼ÈÚ»á¹áÍ¨£¬Ôò°´ÕÕÆÕÍ¨¼¼ÄÜÏÔÊ¾(3)¡£

3 Èç¹û²éÑ¯µÄ¼¼ÄÜÊÇÒ»ÖÖÆÕÍ¨µÄÎä¼¼£¬ÔòÏÔÊ¾¿ÉÒÔ¼¤·¢µÄ»ù±¾Îä¼¼»ù´¡ºÍ¿ÉÒÔÓë
  Ö®»¥±¸µÄÎä¹¦¡£

Ê¹ÓÃ¸ÃÃüÁî¿ÉÒÔÁË½âÄãÑ§µ½µÄÎä¹¦¼¼ÄÜ¡£Íæ¼Ò²éÑ¯µÄÊ±ºò²»ĞèÒªÖ¸Ã÷me²ÎÊı£¬¿É
ÒÔÖ±½ÓÊäÈë<¼¼ÄÜÃû>²ÎÊı¡£

Î×Ê¦¿ÉÒÔ²éÑ¯ÈÎºÎÈË»ò NPC µÄ¼¼ÄÜ×´¿ö¡£

HELP
    );
    return 1;
}
