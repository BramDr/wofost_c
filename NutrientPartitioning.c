#include <stdio.h>
#include <stdlib.h>
#include "wofost.h"
#include "extern.h"
#include "penman.h"

/* -------------------------------------------------------------------------*/
/*  function NutrientPartioning()                                           */
/*  Purpose: To compute the partitioning of the total N/P/K uptake rate     */
/*           (N,P,K UPTR) over leaves, stem, and roots kg  ha-1 d-1         */
/* -------------------------------------------------------------------------*/
void NutrientPartioning()
{     
    float NutrientLimit;
    float N_Fix_rt;
    
    float tiny = 0.001;      
    
    Crop->N_st.Demand = Crop->N_rt.Demand_lv + Crop->N_rt.Demand_st + Crop->N_rt.Demand_ro;
    Crop->P_st.Demand = Crop->P_rt.Demand_lv + Crop->P_rt.Demand_st + Crop->P_rt.Demand_ro;
    Crop->K_st.Demand = Crop->K_rt.Demand_lv + Crop->K_rt.Demand_st + Crop->K_rt.Demand_ro;
    
    /* No nutrients are absorbed from the soil after development stage DevelopmentStageNLimit or */
    /* when severe water shortage occurs                                           */
    NutrientLimit = 0.;
    if (Crop->st.Development < Crop->prm.DevelopmentStageNLimit && WatBal->rt.Transpiration/Evtra.MaxTranspiration > 0.01)
        NutrientLimit = 1.;
    
    //N_Fix_rt= max(0.,Crop->N_rt.Uptake * Crop->prm.N_fixation / max(0.02, 1.-Crop->prm.N_fixation));
    N_Fix_rt = (max(0., Crop->prm.N_fixation * Crop->N_st.Demand) * NutrientLimit);
    
    /* Nutrient uptake cannot be larger than the availability and is larger or equal to zero */
    Crop->N_rt.Uptake = max(0.,min(Crop->N_st.Demand - N_Fix_rt, (Site->st_N_tot + Site->rt_N_mins))) * NutrientLimit/Step;
    Crop->P_rt.Uptake = max(0.,min(Crop->P_st.Demand, (Site->st_P_tot + Site->rt_P_mins)))* NutrientLimit/Step;
    Crop->K_rt.Uptake = max(0.,min(Crop->K_st.Demand, (Site->st_K_tot + Site->rt_K_mins)))* NutrientLimit/Step;

    /* N uptake per crop organ kg ha-1 d-1*/
    if (Crop->N_st.Demand > tiny)
    {
        Crop->N_rt.Uptake_lv = (Crop->N_rt.Demand_lv / Crop->N_st.Demand) * (Crop->N_rt.Uptake + N_Fix_rt);
        Crop->N_rt.Uptake_st = (Crop->N_rt.Demand_st / Crop->N_st.Demand) * (Crop->N_rt.Uptake + N_Fix_rt);
        Crop->N_rt.Uptake_ro = (Crop->N_rt.Demand_ro / Crop->N_st.Demand) * (Crop->N_rt.Uptake + N_Fix_rt);
    }
    else
    {
        Crop->N_rt.Uptake_lv = 0.;
        Crop->N_rt.Uptake_st = 0.;
        Crop->N_rt.Uptake_ro = 0.;  
    }
    
    
    /* P uptake per crop organ kg ha-1 d-1 */
    if (Crop->P_st.Demand > tiny)
    {
        Crop->P_rt.Uptake_lv = (Crop->P_rt.Demand_lv / Crop->P_st.Demand) * Crop->P_rt.Uptake;
        Crop->P_rt.Uptake_st = (Crop->P_rt.Demand_st / Crop->P_st.Demand) * Crop->P_rt.Uptake;
        Crop->P_rt.Uptake_ro = (Crop->P_rt.Demand_ro / Crop->P_st.Demand) * Crop->P_rt.Uptake; 
    }
    else
    {
        Crop->P_rt.Uptake_lv = 0.;
        Crop->P_rt.Uptake_st = 0.;
        Crop->P_rt.Uptake_ro = 0.;         
    }
    
   /* K uptake per crop organ kg ha-1 d-1*/
    if (Crop->K_st.Demand > tiny)
    {
        Crop->K_rt.Uptake_lv = (Crop->K_rt.Demand_lv / Crop->K_st.Demand) * Crop->K_rt.Uptake;
        Crop->K_rt.Uptake_st = (Crop->K_rt.Demand_st / Crop->K_st.Demand) * Crop->K_rt.Uptake;
        Crop->K_rt.Uptake_ro = (Crop->K_rt.Demand_ro / Crop->K_st.Demand) * Crop->K_rt.Uptake;   
    }
    else
    {
        Crop->K_rt.Uptake_lv = 0.;
        Crop->K_rt.Uptake_st = 0.;
        Crop->K_rt.Uptake_ro = 0.;          
    }
}    