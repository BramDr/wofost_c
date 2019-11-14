#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "wofost.h"
#include "extern.h"

void
CopyTable(TABLE *from, TABLE *to)
{
    to->x = from->x;
    to->y = from->y;
    to->next = NULL;
}

void
CopyTableList(TABLE **from, TABLE **to)
{
    TABLE *from_start, *to_start;
    
    to_start = NULL;
    from_start = (*from);
    
    while((*from)){
        if (to_start == NULL) {
            (*to) = to_start = malloc(sizeof(TABLE));
        } else {
            (*to)->next = malloc(sizeof(TABLE));
            (*to) = (*to)->next;
        }
        
        CopyTable((*from), (*to));
        (*from) = (*from)->next;
    }
    
    (*from) = from_start;
    (*to) = to_start;
}

void
CopyTableD(TABLE_D *from, TABLE_D *to)
{
    to->amount = from->amount;
    to->day = from->day;
    to->month = from->month;
    to->next = NULL;
}

void
CopyTableDList(TABLE_D **from, TABLE_D **to)
{
    TABLE_D *from_start, *to_start;
    
    to_start = NULL;
    from_start = (*from);
    
    while((*from)){
        if (to_start == NULL) {
            (*to) = to_start = malloc(sizeof(TABLE_D));
        } else {
            (*to)->next = malloc(sizeof(TABLE_D));
            (*to) = (*to)->next;
        }
        
        CopyTableD((*from), (*to));
        (*from) = (*from)->next;
    }
    
    (*from) = from_start;
    (*to) = to_start;
}

void
CopyRates(Rates *from, Rates *to)
{
    to->EvapWater = from->EvapWater;
    to->EvapSoil = from->EvapSoil;
    to->Infiltration = from->Infiltration;
    to->Irrigation = from->Irrigation;
    to->Loss = from->Loss;
    to->Moisture = from->Moisture;
    to->MoistureLOW = from->MoistureLOW;
    to->Percolation = from->Percolation;
    to->RootZoneMoisture = from->RootZoneMoisture;
    to->Runoff = from->Runoff;
    to->Transpiration = from->Transpiration;
    to->WaterRootExt = from->WaterRootExt;
}

void
CopyStates(States *from, States *to)
{
    to->EvapWater = from->EvapWater;
    to->EvapSoil = from->EvapSoil;
    to->Infiltration = from->Infiltration;
    to->Irrigation = from->Irrigation;
    to->Loss = from->Loss;
    to->Moisture = from->Moisture;
    to->MoistureLOW = from->MoistureLOW;
    to->Percolation = from->Percolation;
    to->Rain = from->Rain;
    to->RootZoneMoisture = from->RootZoneMoisture;
    to->Runoff = from->Runoff;
    to->SurfaceStorage = from->SurfaceStorage;
    to->Transpiration = from->Transpiration;
    to->WaterRootExt = from->WaterRootExt;
}

void
CopyConstants(Constants *from, Constants *to)
{
    to->MaxEvapWater = from->MaxEvapWater;
    to->MoistureFC = from->MoistureFC;
    to->MoistureWP = from->MoistureWP;
    to->MoistureSAT = from->MoistureSAT;
    to->CriticalSoilAirC = from->CriticalSoilAirC;
    to->MaxPercolRTZ = from->MaxPercolRTZ;
    to->MaxPercolSubS = from->MaxPercolSubS;
    to->MaxSurfaceStorge = from->MaxSurfaceStorge;
    to->K0 = from->K0;
}

void
CopyGreen(Green *from, Green *to)
{
    to->age = from->age;
    to->area = from->area;
    to->weight = from->weight;
    to->next = NULL;
}

void
CopyGreenList(Green **from, Green **to)
{
    Green *from_start, *to_start;
    
    to_start = NULL;
    from_start = (*from);
    
    while((*from)){
        if (to_start == NULL) {
            (*to) = to_start = malloc(sizeof(Green));
        } else {
            (*to)->next = malloc(sizeof(Green));
            (*to) = (*to)->next;
        }
        
        CopyGreen((*from), (*to));
        (*from) = (*from)->next;
    }
    
    (*from) = from_start;
    (*to) = to_start;
}

void
CopyGrowthRates(growth_rates *from, growth_rates *to)
{
    to->Development = from->Development;
    to->LAIExp = from->LAIExp;
    to->RootDepth = from->RootDepth;
    to->leaves = from->leaves;
    to->roots = from->roots;
    to->stems = from->stems;
    to->storage = from->storage;
    to->vernalization = from->vernalization;
}

void
CopyGrowthStates(growth_states *from, growth_states *to)
{
    to->Development = from->Development;
    to->LAI = from->LAI;
    to->LAIExp = from->LAIExp;
    to->RootDepth = from->RootDepth;
    to->RootDepth_prev = from->RootDepth_prev;
    to->leaves = from->leaves;
    to->roots = from->roots;
    to->stems = from->stems;
    to->storage = from->storage;
    to->vernalization = from->vernalization;
}

void
CopyDyingRates(dying_rates *from, dying_rates *to)
{
    to->leaves = from->leaves;
    to->roots = from->roots;
    to->stems = from->stems;
}

void
CopyDyingStates(dying_states *from, dying_states *to)
{
    to->leaves = from->leaves;
    to->roots = from->roots;
    to->stems = from->stems;
}

void
CopyNutrientRates(nutrient_rates *from, nutrient_rates *to)
{
    to->roots = from->roots;
    to->stems = from->stems;
    to->leaves = from->leaves;
    to->storage = from->storage;
    to->Demand_lv = from->Demand_lv;
    to->Demand_st = from->Demand_st;
    to->Demand_ro = from->Demand_ro;
    to->Demand_so = from->Demand_so;
    to->Supply = from->Supply;
    to->Transloc = from->Transloc;
    to->Transloc_lv = from->Transloc_lv;
    to->Transloc_st = from->Transloc_st;
    to->Transloc_ro = from->Transloc_ro;
    to->Uptake = from->Uptake;
    to->Uptake_lv = from->Uptake_lv;
    to->Uptake_st = from->Uptake_st;
    to->Uptake_ro = from->Uptake_ro;
    to->death_lv = from->death_lv;
    to->death_st = from->death_st;
}

void
CopyNutrientStates(nutrient_states *from, nutrient_states *to)
{
    to->roots = from->roots;
    to->stems = from->stems;
    to->leaves = from->leaves;
    to->storage = from->storage;
    to->Max_lv = from->Max_lv;
    to->Max_st = from->Max_st;
    to->Max_ro = from->Max_ro;
    to->Max_so = from->Max_so;
    to->Optimum_lv = from->Optimum_lv;
    to->Optimum_st = from->Optimum_st;
    to->Indx = from->Indx;
    to->Uptake = from->Uptake;
    to->Uptake_lv = from->Uptake_lv;
    to->Uptake_st = from->Uptake_st;
    to->Uptake_ro = from->Uptake_ro;
    to->death_lv = from->death_lv;
    to->death_st = from->death_st;
    to->Avail = from->Avail;
    to->Avail_lv = from->Avail_lv;
    to->Avail_st = from->Avail_st;
    to->Avail_ro = from->Avail_ro;
}

void
CopyParameters(Parameters *from, Parameters *to)
{
    CopyTableList(&from->Roots, &to->Roots);
    CopyTableList(&from->Stems, &to->Stems);
    CopyTableList(&from->Leaves, &to->Leaves);
    CopyTableList(&from->Storage, &to->Storage);
    CopyTableList(&from->VernalizationRate, &to->VernalizationRate);
    CopyTableList(&from->DeltaTempSum, &to->DeltaTempSum);
    CopyTableList(&from->SpecificLeaveArea, &to->SpecificLeaveArea);
    CopyTableList(&from->SpecificStemArea, &to->SpecificStemArea);
    CopyTableList(&from->KDiffuseTb, &to->KDiffuseTb);
    CopyTableList(&from->EFFTb, &to->EFFTb);
    CopyTableList(&from->MaxAssimRate, &to->MaxAssimRate);
    CopyTableList(&from->FactorAssimRateTemp, &to->FactorAssimRateTemp);
    CopyTableList(&from->FactorGrossAssimTemp, &to->FactorGrossAssimTemp);
    CopyTableList(&from->FactorSenescence, &to->FactorSenescence);
    CopyTableList(&from->DeathRateStems, &to->DeathRateStems);
    CopyTableList(&from->DeathRateRoots, &to->DeathRateRoots);
    CopyTableList(&from->CO2AMAXTB, &to->CO2AMAXTB);
    CopyTableList(&from->CO2EFFTB, &to->CO2EFFTB);
    CopyTableList(&from->CO2TRATB, &to->CO2TRATB);
    CopyTableList(&from->N_MaxLeaves, &to->N_MaxLeaves);
    CopyTableList(&from->P_MaxLeaves, &to->P_MaxLeaves);
    CopyTableList(&from->K_MaxLeaves, &to->K_MaxLeaves);
    
    to->TempBaseEmergence          = from->TempBaseEmergence;
    to->TempEffMax          = from->TempEffMax;
    to->TSumEmergence          = from->TSumEmergence;
    to->IdentifyAnthesis          = from->IdentifyAnthesis;
    to->OptimumDaylength          = from->OptimumDaylength;
    to->CriticalDaylength          = from->CriticalDaylength;
    to->SatVernRequirement          = from->SatVernRequirement;
    to->BaseVernRequirement          = from->BaseVernRequirement;
    to->TempSum1          = from->TempSum1;
    to->TempSum2          = from->TempSum2;
    to->InitialDVS          = from->InitialDVS;
    to->DevelopStageHarvest          = from->DevelopStageHarvest;
    to->InitialDryWeight          = from->InitialDryWeight;
    to->RelIncreaseLAI          = from->RelIncreaseLAI;
    to->SpecificPodArea          = from->SpecificPodArea;
    to->LifeSpan          = from->LifeSpan;
    to->TempBaseLeaves          = from->TempBaseLeaves;
    to->ConversionLeaves          = from->ConversionLeaves;
    to->ConversionStorage          = from->ConversionStorage;
    to->ConversionRoots          = from->ConversionRoots;
    to->ConversionStems          = from->ConversionStems;
    to->Q10          = from->Q10;
    to->RelRespiLeaves          = from->RelRespiLeaves;
    to->RelRespiStorage          = from->RelRespiStorage;
    to->RelRespiRoots          = from->RelRespiRoots;
    to->RelRespiStems          = from->RelRespiStems;
    to->MaxRelDeathRate          = from->MaxRelDeathRate;
    to->CorrectionTransp          = from->CorrectionTransp;
    to->CropGroupNumber          = from->CropGroupNumber;
    to->Airducts          = from->Airducts;
    to->InitRootingDepth          = from->InitRootingDepth;
    to->MaxIncreaseRoot          = from->MaxIncreaseRoot;
    to->MaxRootingDepth          = from->MaxRootingDepth;
    to->DyingLeaves_NPK_Stress          = from->DyingLeaves_NPK_Stress;
    to->DevelopmentStageNLimit          = from->DevelopmentStageNLimit;
    to->DevelopmentStageNT          = from->DevelopmentStageNT;
    to->FracTranslocRoots          = from->FracTranslocRoots;
    to->Opt_N_Frac          = from->Opt_N_Frac;
    to->Opt_P_Frac          = from->Opt_P_Frac;
    to->Opt_K_Frac          = from->Opt_K_Frac;
    to->N_MaxRoots          = from->N_MaxRoots;
    to->P_MaxRoots          = from->P_MaxRoots;
    to->K_MaxRoots          = from->K_MaxRoots;
    to->N_MaxStems          = from->N_MaxStems;
    to->P_MaxStems          = from->P_MaxStems;
    to->K_MaxStems          = from->K_MaxStems;
    to->NitrogenStressLAI = from->NitrogenStressLAI;
    to->NLUE = from->NLUE;
    to->Max_N_storage          = from->Max_N_storage;
    to->Max_P_storage          = from->Max_P_storage;
    to->Max_K_storage          = from->Max_K_storage;
    to->N_lv_partitioning          = from->N_lv_partitioning;
    to->NutrientStessSLA          = from->NutrientStessSLA;
    to->N_ResidualFrac_lv          = from->N_ResidualFrac_lv;
    to->N_ResidualFrac_st          = from->N_ResidualFrac_st;
    to->N_ResidualFrac_ro          = from->N_ResidualFrac_ro;
    to->P_ResidualFrac_lv          = from->P_ResidualFrac_lv;
    to->P_ResidualFrac_st          = from->P_ResidualFrac_st;
    to->P_ResidualFrac_ro          = from->P_ResidualFrac_ro;
    to->K_ResidualFrac_lv          = from->K_ResidualFrac_lv;
    to->K_ResidualFrac_st          = from->K_ResidualFrac_st;
    to->K_ResidualFrac_ro          = from->K_ResidualFrac_ro;
    to->TCNT          = from->TCNT;
    to->TCPT          = from->TCPT;
    to->TCKT          = from->TCKT;
    to->N_fixation                 = from->N_fixation;
}

void
CopyPlant(Plant *from, Plant *to)
{
    to->DaysOxygenStress = from->DaysOxygenStress;
    to->Emergence = from->Emergence;
    to->GrowthDay = from->GrowthDay;
    to->NPK_Indx = from->NPK_Indx;
    to->NutrientStress = from->NutrientStress;
    to->Sowing = from->Sowing;
    to->TSumEmergence = from->TSumEmergence;
    to->fac_lv = from->fac_lv;
    to->fac_ro = from->fac_ro;
    to->fac_so = from->fac_so;
    to->fac_st = from->fac_st;
    
    CopyParameters(&from->prm, &to->prm);
    CopyGrowthRates(&from->rt, &to->rt);
    CopyGrowthStates(&from->st, &to->st);
    CopyDyingRates(&from->drt, &to->drt);
    CopyDyingStates(&from->dst, &to->dst);
    CopyNutrientRates(&from->N_rt, &to->N_rt);
    CopyNutrientStates(&from->N_st, &to->N_st);
    CopyNutrientRates(&from->K_rt, &to->K_rt);
    CopyNutrientStates(&from->K_st, &to->K_st);
    CopyNutrientRates(&from->P_rt, &to->P_rt);
    CopyNutrientStates(&from->P_st, &to->P_st);
    
    CopyGreenList(&from->LeaveProperties, &to->LeaveProperties);
}

void
CopyField(Field *from, Field *to)
{
    to->FlagGroundWater = from->FlagGroundWater;
    to->InfRainDependent = from->InfRainDependent;
    to->FlagDrains = from->FlagDrains;
    to->MaxSurfaceStorage = from->MaxSurfaceStorage;
    to->InitSoilMoisture = from->InitSoilMoisture;
    to->GroundwaterDepth = from->GroundwaterDepth;
    to->DD = from->DD;
    to->SoilLimRootDepth = from->SoilLimRootDepth;
    to->NotInfiltrating = from->NotInfiltrating;
    to->SurfaceStorage = from->SurfaceStorage;
    to->MaxInitSoilM = from->MaxInitSoilM;
    to->st_N_tot = from->st_N_tot;
    to->st_P_tot = from->st_P_tot;
    to->st_K_tot = from->st_K_tot;
    to->st_N_mins = from->st_N_mins;
    to->st_P_mins = from->st_P_mins;
    to->st_K_mins = from->st_K_mins;
    to->rt_N_tot = from->rt_N_tot;
    to->rt_P_tot = from->rt_P_tot;
    to->rt_K_tot = from->rt_K_tot;
    to->rt_N_mins = from->rt_N_mins;
    to->rt_P_mins = from->rt_P_mins;
    to->rt_K_mins = from->rt_K_mins;
    
    CopyTableList(&from->NotInfTB, &to->NotInfTB);
}

void
CopySoil(Soil *from, Soil *to)
{
    to->DaysSinceLastRain = from->DaysSinceLastRain;
    to->InfPreviousDay = from->InfPreviousDay;
    to->SoilMaxRootingDepth = from->SoilMaxRootingDepth;
    to->WaterStress = from->WaterStress;
    
    CopyStates(&from->st, &to->st);
    CopyRates(&from->rt, &to->rt);
    CopyConstants(&from->ct, &to->ct);
    
    CopyTableList(&from->HydraulicConductivity, &to->HydraulicConductivity);
    CopyTableList(&from->VolumetricSoilMoisture, &to->VolumetricSoilMoisture);
}

void
CopyManagement(Management *from, Management *to)
{
    to->N_Mins = from->N_Mins;
    to->NRecoveryFrac = from->NRecoveryFrac;
    to->P_Mins = from->P_Mins;
    to->PRecoveryFrac = from->PRecoveryFrac;
    to->K_Mins = from->K_Mins;
    to->KRecoveryFrac = from->KRecoveryFrac;
    to->N_Uptake_frac = from->N_Uptake_frac;
    to->P_Uptake_frac = from->P_Uptake_frac;
    to->K_Uptake_frac = from->K_Uptake_frac;
    
    CopyTableDList(&from->N_Fert_table, &to->N_Fert_table);
    CopyTableDList(&from->P_Fert_table, &to->P_Fert_table);
    CopyTableDList(&from->K_Fert_table, &to->K_Fert_table);
    CopyTableDList(&from->Irrigation, &to->Irrigation);
}

void
CopySim(SimUnit *from, SimUnit *to)
{
    to->emergence = from->emergence;
    to->file = from->file;
    to->start = from->start;
    to->end = from->end;
    to->outputType = from->outputType;
    
    memset(to->output, '\0', MAX_STRING);
    strncpy(to->output, from->output, strlen(from->output));
    
    CopyPlant(from->crp, to->crp);
    CopyManagement(from->mng, to->mng);
    CopyField(from->ste, to->ste);
    CopySoil(from->soil, to->soil);
}