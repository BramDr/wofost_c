#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "wofost.h"
#include "extern.h"

/* --------------------------------------------------------------------------*/
/*  function GetMeteoInput()                                                 */
/*  Purpose: Get the names of meteo files and the start and end year of the  */
/*           of the simulations. Read the la and lon of the boxes. Store the */
/*           information of each cell in the Meteo struct.                   */
/* --------------------------------------------------------------------------*/

void GetMeteoInput(char *meteolist)
{
    FILE *ifp;
    
    Weather *initial = NULL;
    int i;
    
    char line[MAX_STRING];
    unsigned int type;
    int StartYear;
    int EndYear;
    char path[MAX_STRING];
    char filename[MAX_STRING];
    char filetype[MAX_STRING];
    char varname[MAX_STRING];
    char varunits[MAX_STRING];
    
    ifp = fopen(meteolist, "r");

    if (ifp == NULL) 
    {
        fprintf(stderr, "Can't open %s\n", meteolist);
        exit(0);
    }
    
    while(fgets(line, MAX_STRING, ifp)) {
        if(line[0] == '*' || line[0] == ' ' || line[0] == '\n'){
            continue;
        }
        
        sscanf(line,"%s %d %d" , path, &StartYear, &EndYear);
        
        if (initial == NULL) 
        {
            Meteo = initial = malloc(sizeof(Weather));
        }
        else 
        {
            Meteo->next = malloc(sizeof(Weather));
            Meteo = Meteo->next;  
        }  

        Meteo->StartYear = StartYear;
        Meteo->EndYear = EndYear;
        Meteo->next = NULL;
        
        if (Meteo->EndYear < Meteo->StartYear) {
            fprintf(stderr, "Meteo start year [%d] is bigger than end year [%d]?\n",
                            Meteo->StartYear, Meteo->EndYear);
            exit(0);
        }
        
        NTime = 0;
        NYears = 0;
        for (i = Meteo->StartYear; i <= Meteo->EndYear; i++) {
            NTime += leap_year(i);
            NYears++;
        }
        
        for (i = 0; i < WEATHER_NTYPES; i++) {
            if(fgets(line, MAX_STRING, ifp) == NULL){
                fprintf(stderr, "Missing meteo types\n");
                exit(0);
            }
            
            if(line[0] == '*' || line[0] == ' ' || line[0] == '\n'){
                continue;
            }
        
            sscanf(line,"%s %s %s %s" , filename, filetype, varname, varunits);
                    
            if (strlen(filename) >= MAX_STRING) exit(0);
            if (strlen(filetype) >= MAX_STRING) exit(0);
            if (strlen(varname) >= MAX_STRING) exit(0);
            if (strlen(varunits) >= MAX_STRING) exit(0);

            if (strcmp(filetype,"TMIN") == 0) {
                type = WEATHER_TMIN;
            } else if (strcmp(filetype, "TMAX") == 0) {
                type = WEATHER_TMAX;
            } else if (strcmp(filetype, "RADIATION") == 0) {
                type = WEATHER_RADIATION;
            } else if (strcmp(filetype, "RAIN") == 0) {
                type = WEATHER_RAIN;
            } else if (strcmp(filetype, "WINDSPEED") == 0) {
                type = WEATHER_WINDSPEED;
            } else if (strcmp(filetype, "VAPOUR") == 0) {
                type = WEATHER_VAPOUR;
            } else {
                fprintf(stderr, "Unknown meteo type %s\n", filetype);
                exit(0);
            }
            
            memset(Meteo->file[type],'\0',MAX_STRING);
            strncpy(Meteo->file[type], path, strlen(path));
            strncat(Meteo->file[type], filename, strlen(filename));
            memset(Meteo->type[type],'\0',MAX_STRING);
            strncpy(Meteo->type[type], filetype, strlen(filetype));
            memset(Meteo->var[type],'\0',MAX_STRING);
            strncpy(Meteo->var[type], varname, strlen(varname));
            memset(Meteo->units[type],'\0',MAX_STRING);
            strncpy(Meteo->units[type], varunits, strlen(varunits));
        }
    }
          
    Meteo = initial;
    fclose(ifp);
  
}