#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <float.h>
#include <netcdf.h>
#include "wofost.h"
#include "extern.h"

/* Handle errors by printing an error message and exiting with a
 * non-zero status. */
#define ERR(e) {printf("Error: %s\n", nc_strerror(e)); exit(2);}

int main(int argc, char **argv)
{
    
    FILE **outputTXT = NULL;
    int *outputNCDF = NULL;
    int retval;
    
    SimUnit *initial  = NULL;
    SimUnit *sampleGrid = NULL;
    Weather *head;
      
    int CycleLength;
    int NumberOfFiles;
    int Emergence;
    
    char domain[MAX_STRING];
    char list[MAX_STRING];
    char meteolist[MAX_STRING];
    char name[MAX_STRING];
    
    Step = 1.;
    
    if (argc != 4) exit(0);
    if (strlen(argv[1]) >= MAX_STRING) exit(0);
    if (strlen(argv[2]) >= MAX_STRING) exit(0);
    if (strlen(argv[3]) >= MAX_STRING) exit(0);
    
    memset(domain,'\0',MAX_STRING);
    memset(list,'\0',MAX_STRING);
    memset(meteolist,'\0',MAX_STRING);
    
    strncpy(domain,argv[1],strlen(argv[1]));
    strncpy(list,argv[2],strlen(argv[2]));
    strncpy(meteolist,argv[3],strlen(argv[3]));
    
    /* Fill the domain placeholder */
    GetDomainData(domain);
    
    /* Fill the crop, soil, site and management place holders*/
    NumberOfFiles = GetSimInput(list, &sampleGrid);
    
    /* Set the initial Grid address */
    initial = sampleGrid;    
    
    /* Get the meteo filenames and put them in the placeholder */
    GetMeteoInput(meteolist);
    
    /* Allocate memory for the file pointers */
    outputTXT = malloc(sizeof(*outputTXT) * NumberOfFiles);
    outputNCDF = malloc(sizeof(*outputNCDF) * NumberOfFiles);
    
    /* Go back to the beginning of the list */
    sampleGrid = initial;
    
    /* Open the output files */
    while (sampleGrid)
    {
        /* Make valgrind happy  */
        memset(name,'\0',MAX_STRING);
        strncpy(name, sampleGrid->output, strlen(sampleGrid->output));

        if (sampleGrid->outputType == OUTPUT_TXT) {
            if((outputTXT[sampleGrid->file] = fopen(name, "w")) == NULL) {
                fprintf(stderr, "Cannot initialize output file %s.\n", name);
                exit(0);
            }
            headerTXT(outputTXT[sampleGrid->file]);
        } else if (sampleGrid->outputType == OUTPUT_NCDF) {
            if((retval = nc_create(name, NC_NETCDF4, &outputNCDF[sampleGrid->file])))
                ERR(retval);
            headerNCDF(outputNCDF[sampleGrid->file]);
        }
        
        sampleGrid = sampleGrid->next;
    }
    /* Go back to the beginning of the list */
    sampleGrid = initial;
        

    while (Meteo)
    {
        /* Initialize the meteodata */
        if(InitializeMeteo(Meteo) != 1) {
            fprintf(stderr, "Cannot initialize meteo data.\n");
            exit(0);
        }
        printf("Running meteo: %d - %d\n", Meteo->StartYear, Meteo->EndYear);
        
        for (Day = 0; Day < NTime; Day++) //assume that the series start January first
        {                   

            fprintf(stdout, "Date: %d-%d\n", MeteoDay[Day], MeteoYear[Day]);
            
            /* Get the meteodata */
            if(GetMeteoData(Meteo) != 1) {
                fprintf(stderr, "Cannot get meteo data.\n");
                exit(0);
            }
            
            for (Lon = 0; Lon < NLongitude; Lon++) {
                for(Lat = 0; Lat < NLatitude; Lat++) {
                    if(Mask[Lon][Lat] != 1){
                        continue;
                    }

                    /* Set the meteo data */
                    cshift(TminPrev[Lon][Lat], 1, 7, 1, -1);
                    TminPrev[Lon][Lat][0] = Tmin[Lon][Lat];
                    Temp = 0.5 * (Tmax[Lon][Lat] + Tmin[Lon][Lat]);
                    DayTemp = 0.5 * (Tmax[Lon][Lat] + Temp);

                    /* Set the date struct */
                    memset(&current_date, 0, sizeof(current_date)); 
                    current_date.tm_year = MeteoYear[Day] -1900;
                    current_date.tm_mday =  0 + MeteoDay[Day];
                    mktime(&current_date);

                    initial = Grid[Lon][Lat];
                    while (Grid[Lon][Lat])
                    {
                        /* Get data, states and rates from the Grid structure and */
                        /* put them in the place holders */
                        Crop      = Grid[Lon][Lat]->crp;
                        WatBal    = Grid[Lon][Lat]->soil;
                        Mng       = Grid[Lon][Lat]->mng;
                        Site      = Grid[Lon][Lat]->ste;
                        Emergence = Grid[Lon][Lat]->emergence; /* Start simulation at sowing or emergence */
                        
                        /* Set crop cycle length */
                        if (Grid[Lon][Lat]->start < Grid[Lon][Lat]->end) {
                            CycleLength = Grid[Lon][Lat]->end - Grid[Lon][Lat]->start;
                        } else {
                            CycleLength = leap_year(MeteoYear[Day]) - Grid[Lon][Lat]->start + Grid[Lon][Lat]->end;
                        }

                        /* Determine if the sowing already has occurred */
                        IfSowing(Grid[Lon][Lat]->start);

                        /* If sowing has occurred than determine the emergence */
                        if (Crop->Sowing >= 1 && Crop->Emergence == 0)
                        {
                            if (EmergenceCrop(Emergence))
                            {                 
                                /* Initialize: set state variables */
                                InitializeCrop();
                                InitializeWatBal();
                                InitializeNutrients(); 
                            }  
                        }

                        if (Crop->Sowing >= 1 && Crop->Emergence == 1)
                        {   
                            if (Crop->st.Development <= (Crop->prm.DevelopStageHarvest) && Crop->GrowthDay < CycleLength) 
                            {
                                Astro();
                                CalcPenman();
                                CalcPenmanMonteith();

                               /* Calculate the evapotranspiration */
                                EvapTra();

                                /* Set the rate variables to zero */
                                RatesToZero();

                                 /* Rate calculations */
                                RateCalulationWatBal();
                                Partioning();
                                RateCalcultionNutrients();
                                RateCalculationCrop();

                                /* Write to the output files */
                                //Output(output[Grid->file]);   

                                /* Calculate LAI */
                                Crop->st.LAI = LeaveAreaIndex();             

                                /* State calculations */
                                IntegrationCrop();
                                IntegrationWatBal();
                                IntegrationNutrients();

                                /* Update the number of days that the crop has grown*/
                                Crop->GrowthDay++;
                                
                                /* Write to the output files */
                                if (Grid[Lon][Lat]->outputType == OUTPUT_TXT) {
                                    OutputTXT(outputTXT[Grid[Lon][Lat]->file]);
                                }
                            }
                            else
                            {
                                CleanHarvest(Grid[Lon][Lat]);
                                //printf("%7d %7d\n", MeteoYear[Day], Crop->GrowthDay);
                                Emergence = 0;
                                Crop->TSumEmergence = 0;
                                Crop->Emergence = 0;
                                Crop->Sowing    = 0;
                            }
                        }

                        /* Store the daily calculations in the Grid structure */
                        Grid[Lon][Lat]->crp  = Crop;
                        Grid[Lon][Lat]->soil = WatBal;
                        Grid[Lon][Lat]->mng  = Mng;
                        Grid[Lon][Lat]->ste  = Site;
                        Grid[Lon][Lat] = Grid[Lon][Lat]->next;
                    }
            
                    /* Return to the beginning of the list */
                    Grid[Lon][Lat] = initial;
                }
            }
            
            /* Write to the output files */
            OutputNCDF(outputNCDF, sampleGrid);
        }
        
        head = Meteo;
        Meteo = Meteo->next;
        CleanMeteo(head);
        free(head);
    }
    
    /* Return to the beginning of the list */
    sampleGrid = initial;
    
    /* Close the output files and free the allocated memory */
    while(sampleGrid)
    {
        if (sampleGrid->outputType == OUTPUT_TXT) {
            fclose(outputTXT[sampleGrid->file]);
        } else if (sampleGrid->outputType == OUTPUT_NCDF) {
            if((retval = nc_close(outputNCDF[sampleGrid->file])))
                ERR(retval);
        }
        sampleGrid = sampleGrid->next;
    }
    free(outputTXT);
    free(outputNCDF);

    /* Go back to the beginning of the list */
    sampleGrid = initial;
    for (Lon = 0; Lon < NLongitude; Lon++) {
        for(Lat = 0; Lat < NLatitude; Lat++) {
            Clean(Grid[Lon][Lat]);
        }
        free(Grid[Lon]);
    }
    free(Grid);

    CleanDomain();

    return 1;
}
