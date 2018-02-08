#include <time.h>

#ifndef WOFOST_H
#define WOFOST_H

#define NR_VARIABLES_CRP	64
#define NR_TABLES_CRP   	19
#define NR_VARIABLES_SITE       12
#define NR_TABLES_SITE          1
#define NR_VARIABLES_SOIL       12
#define NR_TABLES_SOIL          2
#define NR_VARIABLES_MANAGEMENT 6
#define NR_TABLES_MANAGEMENT    7
#define NUMBER_OF_TABLES        31
#define NR_SIMUNITS             4

typedef struct TABLE {
	float x;
	float y;
	struct TABLE *next;
	} AFGEN;

AFGEN *AfgenTable[30];

typedef struct FIELD {
        float AngstA;
        float AngstB;
        float SoilName;
        float FlagGroundWater;
        float InfRainDependent;
        float FlagDrains;
        float MaxSurfaceStorage;     
        float InitSoilMoisture;
        float GroundwaterDepth;
        float DD;
        float SoilLimRootDepth;
        float NotInfiltrating;
        float SurfaceStorage;
        float MaxInitSoilM;
        
        /** Table for the fraction of precipitation that does not infiltrate **/
        AFGEN *NotInfTB;
        } Field;
Field Site;
   
typedef struct MANAGEMENT {
        /** Tables for fertilizer application and recovery fraction **/
        AFGEN *N_Fert_table;
        AFGEN *P_Fert_table;
        AFGEN *K_Fert_table;
        AFGEN *N_Uptake_frac;
        AFGEN *P_Uptake_frac;
        AFGEN *K_Uptake_frac;
        AFGEN *Irrigation;
        
        float N_Mins;
        float NRecoveryFrac;
        float P_Mins;
        float PRecoveryFrac;
        float K_Mins; 
        float KRecoveryFrac;
        } Management;
Management Mng;

typedef struct CONSTANTS {
        float MaxEvapWater;
        float MoistureFC;
        float MoistureWP;
        float MoistureSAT;
        float CriticalSoilAirC;
        float MaxPercolRTZ;
        float MaxPercolSubS;
        float MaxSurfaceStorge;
        float K0;
        } Constants;

typedef struct PARAMETERS {
          /** Tables for Crop **/
        AFGEN *Roots;
        AFGEN *Stems;
        AFGEN *Leaves;
        AFGEN *Storage;

        AFGEN *DeltaTempSum;
        AFGEN *SpecificLeaveArea;
        AFGEN *SpecificStemArea;
        AFGEN *KDiffuseTb;
        AFGEN *EFFTb;
        AFGEN *MaxAssimRate; 
        AFGEN *FactorAssimRateTemp;
        AFGEN *FactorGrossAssimTemp;
        AFGEN *FactorSenescence;
        AFGEN *DeathRateStems;
        AFGEN *DeathRateRoots; 
        
        /** Tables to account for the atmospheric CO2 concentration **/
        AFGEN *CO2AMAXTB;
        AFGEN *CO2EFFTB;
        AFGEN *CO2TRATB;

        /** Tables for the maximum nutrient content in leaves as a function of DVS **/
        AFGEN *N_MaxLeaves;
        AFGEN *P_MaxLeaves;
        AFGEN *K_MaxLeaves;

        /** Static Variables  **/
        /**  Emergence  **/
        float TempBaseEmergence;
        float TempEffMax;
        float TSumEmergence;                      	     

        /**  Phenology  **/
        int   IdentifyAnthesis; 
        float OptimumDaylength;	            
        float CriticalDaylength;
        float TempSum1;       
        float TempSum2; 
        float InitialDVS;
        float DevelopStageHarvest;

        /** Initial Values  **/
        float InitialDryWeight;
        float LAIEmergence;
        float RelIncreaseLAI;

        /**  Green Area  **/
        float SpecificPodArea;
        float LifeSpan;
        float TempBaseLeaves;

        /** Conversion assimilates into biomass **/
        float ConversionLeaves;
        float ConversionStorage;
        float ConversionRoots;
        float ConversionStems;

        /** Maintenance Respiration **/
        float Q10;
        float RelRespiLeaves;
        float RelRespiStorage;
        float RelRespiRoots;
        float RelRespiStems;

        /** Death Rates  **/
        float MaxRelDeathRate;

        /** Water Use  **/
        float CorrectionTransp;
        float CropGroupNumber;
        float Airducts;

        /** Rooting **/
        float InitRootingDepth;
        float MaxIncreaseRoot;
        float MaxRootingDepth;

        /** Nutrients **/
        float DyingLeaves_NPK_Stress; 
        float DevelopmentStageNLimit; 
        float DevelopmentStageNT;
        float FracTranslocRoots;  
        float Opt_N_Frac;   
        float Opt_P_Frac;   
        float Opt_K_Frac;   
        float N_MaxRoots;   
        float N_MaxStems;   
        float P_MaxRoots;   
        float P_MaxStems;   
        float K_MaxRoots;   
        float K_MaxStems;   
        float NitrogenStressLAI;   
        float NLUE;   
        float Max_N_storage; 
        float Max_P_storage; 
        float Max_K_storage; 
        float N_lv_partitioning;  
        float NutrientStessSLA;   
        float N_ResidualFrac_lv;  
        float N_ResidualFrac_st;  
        float N_ResidualFrac_ro;  
        float P_ResidualFrac_lv;  
        float P_ResidualFrac_st;  
        float P_ResidualFrac_ro;  
        float K_ResidualFrac_lv;  
        float K_ResidualFrac_st;   
        float K_ResidualFrac_ro;   
        float TCNT;   
        float TCPT;   
        float TCKT;   
        float N_fixation; 
        } Parameters;


typedef struct STATES {
        float EvapWater;
        float EvapSoil;
        float Infiltration;
        float Irrigation;
        float Loss;
        float Moisture;
        float MoistureLOW;
        float Percolation;
        float Rain;
        float RootZoneMoisture;
        float Runoff;
        float SurfaceStorage;
        float Transpiration;
        float WaterRootExt;
        } States;

typedef struct RATES {
        float EvapWater;
        float EvapSoil;
        float Infiltration;
        float Irrigation;
        float Loss;
        float Moisture;
        float MoistureLOW;
        float Percolation;
        float RootZoneMoisture;
        float Runoff;
        float SurfaceStorage;
        float Transpiration;
        float WaterRootExt;
        } Rates;
 
typedef struct SOIL {
        float DaysSinceLastRain;
        float SoilMaxRootingDepth;
        float WaterStress;
        float SoilMoisture;
        Constants ct;
        States st;
        Rates rt;
        } Soil;
    
Soil WatBal;

typedef struct MINERALS {
        float st_N_tot;
        float st_P_tot;
        float st_K_tot;

        float st_N_mins;
        float st_P_mins;
        float st_K_mins;

        float rt_N_tot;
        float rt_P_tot;
        float rt_K_tot;

        float rt_N_mins;
        float rt_P_mins;
        float rt_K_mins;
        } Minerals;

Minerals SoilNtrs;

typedef struct NUTRIENT_RATES {
        float roots;
        float stems;
        float leaves;
        float storage;
        float Demand_lv;
        float Demand_st;
        float Demand_ro;
        float Demand_so;
        float Transloc;
        float Transloc_lv;
        float Transloc_st;
        float Transloc_ro;
        float Uptake;
        float Uptake_lv;
        float Uptake_st;
        float Uptake_ro;
        float death_lv;
        float death_st;
        float death_ro;
        } nutrient_rates;

typedef struct NUTRIENT_STATES {
        float roots;
        float stems;
        float leaves;
        float storage;
        float Max_lv;
        float Max_st;
        float Max_ro;
        float Max_so;
        float Optimum_lv;
        float Optimum_st;
        float Indx;
        float Uptake;
        float Uptake_lv;
        float Uptake_st;
        float Uptake_ro;
        float death_lv;
        float death_st;
        float death_ro;
        } nutrient_states;

typedef struct GROWTH_RATES {
        float roots;
        float stems;
        float leaves;
        float LAIExp;
        float storage;
} growth_rates;

typedef struct GROWTH_STATES {
        float roots;
        float stems;
        float leaves;
        float LAIExp;
        float storage;
        } growth_states;

typedef struct DYING_RATES {
        float roots;
        float stems;
        float leaves;
        } dying_rates; 


typedef struct GREEN {
	float weight;
	float age;
	float area;
	struct GREEN *next;
	} Green;

typedef struct PLANT {
        float RootDepth;
        float RootDepth_prev;
        float MaxRootingDepth;
        float NPK_Indx;
        float NutrientStress;
        float DaysOxygenStress;
        
        Parameters prm;
        
        growth_rates  rt;
        growth_states st;
        dying_rates   drt;
        
        nutrient_states N_st;
	nutrient_states P_st;
        nutrient_states K_st;
        
        nutrient_rates N_rt;
	nutrient_rates P_rt;
        nutrient_rates K_rt;            
        
        Green *LeaveProperties;
	} Plant;
        
Plant Crop;

/* Simulation time */
struct tm simTime;


/* Tables for Soil */
AFGEN *VolumetricSoilMoisture;
AFGEN *HydraulicConductivity; /* currently not used */

typedef struct SIMUNIT {
        Plant crp;
        Field ste;
        Management mng;
        Soil  soil;
        struct SIMUNIT *next;
        } SimUnit;
 
        
float CO2;

/** Meteorological Variables  **/
int Station, Year;
float Longitude, Latitude, Altitude;
float Tmin[367], Tmax[367], Radiation[367], Rain[367];
float Windspeed[367], Vapour[367];

/* Time step */
float Step;

        
        
#endif	// 

