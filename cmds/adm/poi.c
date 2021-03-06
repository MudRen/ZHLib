// sp.c

#include <ansi.h>
#include <mudlib.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
      me->affect_by("ss_poison",  
          ([ "level" : 400, "id"    : "rcwiz", "duration" : 60 ]));

      me->affect_by("poison",  
          ([ "level" : 400, "id"    : "rcwiz", "duration" : 60 ]));

      me->affect_by("fire_poison",  
          ([ "level" : 400, "id"    : "rcwiz", "duration" : 60 ]));

      me->affect_by("xuanming_poison",  
          ([ "level" : 400, "id"    : "rcwiz", "duration" : 60 ]));

      return 1;
}

int help (object me)
{
        write(@HELP
指令格式: sp <class> <info>

授权给本地站点某些方面的使用权限。info 如果为空或是 clear 则
表示取消这类的使用权限。
HELP );
        return 1;
}
