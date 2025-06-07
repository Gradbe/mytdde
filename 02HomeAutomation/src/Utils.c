#include "Utils.h"
#include <stdio.h>

/*static int FormatOutput_Impl(const char * format, ...)
{
    return 1;
}*/

//int (*FormatOutput)(const char * format, ...) = FormatOutput_Impl;
int (*FormatOutput)(const char * format, ...) = printf;

