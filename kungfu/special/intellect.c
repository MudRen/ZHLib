// intellect.c �����
// Created by Vin 1/9/2001

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIG "�����" NOR; }

int perform(object me, string skill)
{
        return notify_fail("������ܹ�ʹ�����Ը��ߣ�����Ҫ���á�\n");
}
