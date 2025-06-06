#include "Utils.h"
#include <stdio.h>

#if 0 
static int FormatOutput_Impl(const char * format, ...)
{
    /* snip */
}

int (*FormatOutput)(const char * format, ...) = FormatOutput_Impl;
#endif 

int (*FormatOutput)(const char * format, ...) = printf;
