#include <stdio.h>
#include "extern.h"
#include "wofost.h"

void headerTXT(FILE *fp)
{
    fprintf(fp,"Lat\t\t\t\tLon\t\t\tYear\t\tDay\t\tDVS\t\tWLV\t\tWST\t\tWSO\t\tWRT\t\tLAI\t\t\tWSTR\tRain\tSOILM\tINF\t\tRUNF\tLOSS\t\t"
            "SOILN\tSOILP\tSOILK\tNUPT\tPUPT\tKUPT\tNDEM\tPDEM\tKDEM\n");
}

void OutputTXT(FILE *fp)
{
    fprintf(fp,"%7.2f\t%7.2f\t\t%4d\t\t%3d\t\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t"
            "\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\n",
        Latitude[Lat],
        Longitude[Lon],
        MeteoYear[Day],
        MeteoDay[Day],
        Crop->st.Development,
        Crop->st.leaves,
        Crop->st.stems,
        Crop->st.storage,
        Crop->st.roots,
        Crop->LAIAvg / Crop->GrowthDay,
        WatBal->WaterStressAvg / Crop->GrowthDay,
        WatBal->st.Rain,
        WatBal->st.Moisture,
        WatBal->st.Infiltration,
        WatBal->st.Runoff,
        WatBal->st.Loss,
        Site->st_N_tot,
        Site->st_P_tot,
        Site->st_K_tot,
        Crop->N_st.Uptake,
        Crop->P_st.Uptake,
        Crop->K_st.Uptake,
        Crop->N_st.Demand,
        Crop->P_st.Demand,
        Crop->K_st.Demand);
}

