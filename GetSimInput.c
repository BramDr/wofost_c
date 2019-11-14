#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "wofost.h"
#include "extern.h"

/* ----------------------------------------------------------------------------*/
/*  function GetMeteoInput()                                                   */
/*  Purpose: Get the names of the crop, soil, management and site files as     */
/*           as well if the simulation starting day and whether the simulation */
/*           starts at emergence (1) or sowing (0)                             */
/*-----------------------------------------------------------------------------*/

int GetSimInput(char *list, SimUnit **sampleGrid)
{
    FILE *ifp;
     
    SimUnit *tmpGrid;
     
    size_t j, k;
    int Emergence;
    int count;
  
    char line[MAX_STRING];
    char path[MAX_STRING];
    char cropfile[MAX_STRING];
    char soilfile[MAX_STRING];
    char sitefile[MAX_STRING];
    char management[MAX_STRING];
    char startfile[MAX_STRING];
    char endfile[MAX_STRING];
    char output[MAX_STRING];
    char type[MAX_STRING];
    char cf[MAX_STRING], sf[MAX_STRING], mf[MAX_STRING], site[MAX_STRING], start[MAX_STRING], end[MAX_STRING];
  
    SimUnit ***initial;
    int **Start;
    int **End;
    
    // Allocate temporary data
    Start = malloc(NLongitude * sizeof(*Start));
    End = malloc(NLongitude * sizeof(*End));
    initial = malloc(NLongitude * sizeof(*initial));
    if(Start == NULL || End == NULL || initial == NULL){
        fprintf(stderr, "Could not malloc");
        exit(0); 
    }
    for (j = 0; j < NLongitude; j++) {
        Start[j] = malloc(NLatitude * sizeof(*Start[j]));
        End[j] = malloc(NLatitude * sizeof(*End[j]));
        initial[j] = malloc(NLatitude * sizeof(*initial[j]));
        if(Start[j] == NULL || End[j] == NULL || initial[j] == NULL){
            fprintf(stderr, "Could not malloc");
            exit(0); 
        }
    }
    
    /* NULL initial */
    for (j = 0; j < NLongitude; j++) {
        for(k = 0; k < NLatitude; k++) {
            initial[j][k] = NULL;
        }
    }
    
    ifp = fopen(list, "r");

    if (ifp == NULL) 
    {
        fprintf(stderr, "Can't open input, %s\n", list);
        exit(0);
    }
    
    count = 0;
    while(fgets(line, MAX_STRING, ifp)) {
        if(line[0] == '*' || line[0] == ' ' || line[0] == '\n'){
            continue;
        }
        
        fprintf(stdout, "Loading crop %d\n", count);
        
        sscanf(line,"%s %s %s %s %s %s %s %d %s %s" ,
            path, cf, sf, mf, site, start, end, &Emergence, output, type);

        if (strlen(path) >= MAX_STRING) exit(0);
        if (strlen(cf) >= MAX_STRING) exit(0);
        if (strlen(sf) >= MAX_STRING) exit(0);
        if (strlen(mf) >= MAX_STRING) exit(0);
        if (strlen(site) >= MAX_STRING) exit(0);
        if (strlen(start) >= MAX_STRING) exit(0);
        if (strlen(end) >= MAX_STRING) exit(0);
        if (strlen(output) >= MAX_STRING) exit(0); 
        if (strlen(type) >= MAX_STRING) exit(0); 
    
        memset(cropfile,'\0',MAX_STRING);
        memset(sitefile,'\0',MAX_STRING);
        memset(soilfile,'\0',MAX_STRING);
        memset(management,'\0',MAX_STRING);
        memset(startfile,'\0',MAX_STRING);
        memset(endfile,'\0',MAX_STRING);
                
        strncpy(cropfile, path, strlen(path));
        strncat(cropfile, cf, strlen(cf));

        strncpy(soilfile, path, strlen(path));
        strncat(soilfile, sf, strlen(sf));

        strncpy(management, path, strlen(path));
        strncat(management, mf, strlen(mf));

        strncpy(sitefile, path, strlen(path));
        strncat(sitefile, site, strlen(site));

        strncpy(startfile, path, strlen(path));
        strncat(startfile, start, strlen(start));

        strncpy(endfile, path, strlen(path));
        strncat(endfile, end, strlen(end));
        
        tmpGrid = malloc(sizeof(SimUnit));
        GetCropData(tmpGrid->crp   = malloc(sizeof(Plant)), cropfile); 
        GetSiteData(tmpGrid->ste   = malloc(sizeof(Field)), sitefile);
        GetManagement(tmpGrid->mng = malloc(sizeof(Management)), management);
        GetSoilData(tmpGrid->soil  = malloc(sizeof(Soil)), soilfile);
        GetStartData(&Start, startfile);
        GetEndData(&End, endfile);
        
        memset(tmpGrid->output,'\0',MAX_STRING);
        strncpy(tmpGrid->output,output,strlen(output)); // Name og output file
        
        if (strcmp(type,"TXT") == 0) {
            tmpGrid->outputType = OUTPUT_TXT;
        } else if (strcmp(type, "NCDF") == 0) {
            tmpGrid->outputType = OUTPUT_NCDF;
        } else {
            fprintf(stderr, "Unknown output type %s\n", type);
            exit(0);
        }
        
        tmpGrid->file  = count++;            // number of elements in Grid carousel
        tmpGrid->emergence = Emergence;      // Start the simulations at emergence (1) or at sowing (0)                
        tmpGrid->crp->Sowing = 0;
        tmpGrid->crp->Emergence = 0;         // Crop emergence has not yet occurred
        tmpGrid->next = NULL;

        /* Loop lat/lon and copy */
        for (j = 0; j < NLongitude; j++) {
            for(k = 0; k < NLatitude; k++) {
                if (Mask[j][k] == 1) {
                
                    if (initial[j][k] == NULL) 
                    {
                        Grid[j][k] = initial[j][k] = malloc(sizeof(SimUnit));
                    }
                    else 
                    {
                        Grid[j][k]->next = malloc(sizeof(SimUnit));
                        Grid[j][k] = Grid[j][k]->next;  
                    }
                    
                    if ((*sampleGrid) == NULL) {
                        (*sampleGrid) = initial[j][k];
                    }

                    Grid[j][k]->crp = malloc(sizeof(Plant));
                    Grid[j][k]->ste = malloc(sizeof(Field));
                    Grid[j][k]->mng = malloc(sizeof(Management));
                    Grid[j][k]->soil = malloc(sizeof(Soil));
                    Grid[j][k]->next = NULL;

                    tmpGrid->start = Start[j][k];
                    tmpGrid->end = End[j][k];
                    CopySim(tmpGrid, Grid[j][k]);
                }
            }
        }
        Clean(tmpGrid);
    }
    
    fclose(ifp);
    
    /* Return to start of list */
    for (j = 0; j < NLongitude; j++) {
        for(k = 0; k < NLatitude; k++) {
            Grid[j][k] = initial[j][k];
        }
    }

    /* Clear temporary data */
    for (j = 0; j < NLongitude; j++) {
        free(Start[j]);
        free(End[j]);
        free(initial[j]);
    }
    free(Start);
    free(End);
    free(initial);
    
    /* Return the number of meteo files */
    return count;
}   
