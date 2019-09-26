#include <stdio.h>
#include "extern.h"
#include "wofost.h"

void header(FILE *fp)
{
    fprintf(fp,"Lat\t\tLon\t\tYear\tDay\t\t\tDVS\t\tWLV\t\tWST\t\tWSO\t\tWRT\t\tLAI\t\t\tWSTR\tSOILM\tRain\tINF\t\tRUNOFF\tLOSS\t"
            "\tNNI\t\tPNI\t\tKNI\t\tSOILN\tSOILP\tSOILK\tNUPT\tPUPT\tKUPT\tNDEM\tPDEM\tKDEM\n");
}

void Output(FILE *fp)
{
    fprintf(fp,"%4.2f\t%4.2f\t%4d\t%4d\t\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t"
            "\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\n",
        Meteo->lat,
        Meteo->lon,
        MeteoYear[Day],
        MeteoDay[Day],
        Crop->st.Development,
        Crop->st.leaves,
        Crop->st.stems,
        Crop->st.storage,
        Crop->st.roots,
        Crop->st.LAI,
        WatBal->WaterStress,
        WatBal->st.Moisture,
        Rain[Day],
        WatBal->rt.Infiltration,
        WatBal->rt.Runoff,
        WatBal->rt.Loss,
        Crop->N_st.Indx,
        Crop->P_st.Indx,
        Crop->K_st.Indx,
        Site->st_N_tot,
        Site->st_P_tot,
        Site->st_K_tot,
        Crop->N_rt.Uptake,
        Crop->P_rt.Uptake,
        Crop->K_rt.Uptake,
        Crop->N_rt.Demand_lv + Crop->N_rt.Demand_st + Crop->N_rt.Demand_ro,
        Crop->P_rt.Demand_lv + Crop->P_rt.Demand_st + Crop->P_rt.Demand_ro,
        Crop->K_rt.Demand_lv + Crop->K_rt.Demand_st + Crop->K_rt.Demand_ro);
}

