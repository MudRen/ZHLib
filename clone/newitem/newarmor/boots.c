// �����硤���μǡ��汾��������
/* <SecCrypt CPL V3R05> */
 
// shoupi.c

#include <armor.h>

inherit BOOTS;
       inherit "/clone/newitem/newitems.c";

void create()
{
        set_name("ѥ��", ({"boots"}));
   set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "leather");
                set("unit", "˫");
     set("armor_prop/armor", 1);
        }
        setup();
}
