#include <stdio.h>
#include "extern.h"
#include "wofost.h"

void header(FILE *fp)
{
    fprintf(fp,"Lat\t\t\t\tLon\t\t\tYear\t\tDay\t\tDVS\t\tWLV\t\tWST\t\tWSO\t\tWRT\t\tLAI\t\t\tWSTR\tSOILM\tRain\tINF\t\tRUNF\tLOSS\t"
            "\tNNI\t\tPNI\t\tKNI\t\tSOILN\tSOILP\tSOILK\tNUPT\tPUPT\tKUPT\tNDEM\tPDEM\tKDEM\n");
}

void Output(FILE *fp)
{
    fprintf(fp,"%7.2f\t%7.2f\t\t%4d\t\t%3d\t\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t"
            "\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\n",
        Latitude[Lat],
        Longitude[Lon],
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
        Rain[Lon][Lat][Day],
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

