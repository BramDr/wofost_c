#include <stdio.h>
#include "wofost.h"
#include "extern.h"

/* ---------------------------------------------------------------------------*/
/*  function void IfSowing    ()                                              */
/*  Purpose: Checks whether sowing has occurred. Note that if the emergence   */
/*           flag is set to 1 the crop simulation starts the next day. If it  */
/*           is set to 0 the Emergence date has to be established.            */
/* ---------------------------------------------------------------------------*/

void IfSowing(int start, int year)
{
    int month, start_day;
    char dateString[MAX_STRING];

    datestring_doy(start, year, &dateString[0], MAX_STRING);
    sscanf(dateString, "%d-%d", &month, &start_day);
      
    if (current_date.tm_mon == (month - 1) &&
        current_date.tm_mday == start_day && 
        MeteoYear[Day] <= Meteo->EndYear)
    {
        Crop->Sowing = 1;
    }
}
