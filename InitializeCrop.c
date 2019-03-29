#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "wofost.h"
#include "extern.h"


/*---------------------------------------------------*/
/* function EmergenceCrop                            */
/* Purpose: determine if crop emergence has occurred */
/*---------------------------------------------------*/

int EmergenceCrop(int Emergence)
{
    float DeltaTempSum;
     
    /*  Emergence has not taken place yet*/
    if (!Emergence)
	{
            DeltaTempSum = limit(0, Crop->prm.TempEffMax - Crop->prm.TempBaseEmergence, 
                Temp - Crop->prm.TempBaseEmergence);
	    Crop->TSumEmergence += DeltaTempSum;
	    if (Crop->TSumEmergence >= Crop->prm.TSumEmergence)
            {
                Emergence = 1;
	    }
	}
    return Emergence;
}
    

/* ----------------------------------------------------------*/
/*  function InitializeCrop                                  */
/*  Purpose: Set the initial crop state and leave variables  */
/*  ---------------------------------------------------------*/ 

void InitializeCrop()
{ 
    float FractionRoots;
    float FractionShoots; 
    float InitialShootWeight;
    float LAIEmergence;
   
    /* Initialize the crop states */
    Crop->st.Development = Crop->prm.InitialDVS;

    FractionRoots      = Afgen(Crop->prm.Roots, &(Crop->st.Development));
    FractionShoots     = 1 - FractionRoots;
    InitialShootWeight = Crop->prm.InitialDryWeight * FractionShoots;

    Crop->st.roots     = Crop->prm.InitialDryWeight * FractionRoots;
    Crop->st.RootDepth = Crop->prm.InitRootingDepth;
    Crop->st.stems     = InitialShootWeight * Afgen(Crop->prm.Stems, &(Crop->st.Development));                   
    Crop->st.leaves    = InitialShootWeight * Afgen(Crop->prm.Leaves, &(Crop->st.Development));
    Crop->st.storage   = InitialShootWeight * Afgen(Crop->prm.Storage, &(Crop->st.Development));

    /* Adapt the maximum rooting depth */
    Crop->prm.MaxRootingDepth = max(Crop->prm.InitRootingDepth, min(Crop->prm.MaxRootingDepth,
         Site->SoilLimRootDepth));
    
    /* Calculate the LAI at emergence */
    LAIEmergence  = Crop->st.leaves * Afgen(Crop->prm.SpecificLeaveArea, &(Crop->st.Development)); 

    Crop->st.LAIExp = LAIEmergence;

    Crop->st.LAI = LAIEmergence + Crop->st.stems * 
           Afgen(Crop->prm.SpecificStemArea, &(Crop->st.Development)) +
           Crop->st.storage*Crop->prm.SpecificPodArea;
    
    /* Initialize the leaves */
    Crop->LeaveProperties         = malloc(sizeof (Green));
    Crop->LeaveProperties->age    = 0.;
    Crop->LeaveProperties->weight = Crop->st.leaves;
    Crop->LeaveProperties->area   = Afgen(Crop->prm.SpecificLeaveArea, &(Crop->st.Development));
    Crop->LeaveProperties->next   = NULL;
    
    /* Emergence true */
    Crop->Emergence = 1;
    Crop->GrowthDay = 1;
    
    /* No dead material */
    Crop->dst.leaves = 0.;
    Crop->dst.stems =  0.;
    Crop->dst.roots =  0.;
    
    /* No vernalization yet */
    Crop->st.vernalization = 0.;
            
}  