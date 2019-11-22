#include <stdio.h>
#include <string.h>
#include "wofost.h"
#include "extern.h"

float limit(float a, float b, float c)
{
    if (c < a) return a;
    else if (c >= a && c <= b)  return c;
    else return b;
   }


float notnul(float x)
{
    if (x != 0.) return x;
    else return 1.;
   }

float insw(float x1, float x2, float x3)
{
    return ((x1 < 0) ? x2 : x3);
}


int leap_year(int year)
{
    if ((year % 400 == 0) || ( ( year % 100 != 0) && (year % 4 == 0 )))
        return 366;
    else
        return 365;
}

void datestring_doy(int doy, int year, char *dateString, size_t length)
{
    int monthdays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    int i;
    int month, day;
    
    monthdays[1] += leap_year(year) - 365;
    
    memset(dateString,'\0', length);
    for(i = 0; i < 12; i++) {
        if (doy <= monthdays[i]) {
            month = i + 1;
            day = doy;
            snprintf(dateString, length, "%d-%d", month, day);
            return;
        }
        doy -= monthdays[i];
    }
    
    snprintf(dateString, length, "%d-%d", i, monthdays[i - 1]);
}

float min(float a, float b)
{
    return ((a < b) ? a : b);
}


float max(float a, float b)
{
    return ((a > b) ? a : b);
}

