#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netcdf.h>
#include "extern.h"
#include "wofost.h"

/* Handle errors by printing an error message and exiting with a
 * non-zero status. */
#define ERR(e) {printf("Error: %s\n", nc_strerror(e)); exit(2);}

void headerNCDF(int ncid) 
{
    
    size_t i;
    int retval;
    int lat_dimid, lon_dimid, time_dimid;
    int lat_varid, lon_varid, time_varid;
    char units[MAX_STRING];
    int varid;
    int dimids[3];
    size_t pstart[1];
    size_t pcount[1];
    double *time_vals;
    
    // Add dimensions
    if ((retval = nc_def_dim(ncid, "lat", NLatitude, &lat_dimid)))
        ERR(retval);
    if ((retval = nc_def_dim(ncid, "lon", NLongitude, &lon_dimid)))
        ERR(retval);
    if ((retval = nc_def_dim(ncid, "time", NC_UNLIMITED, &time_dimid)))
        ERR(retval);
    
    // Add dimension variables
    dimids[0] = time_dimid;
    dimids[1] = lat_dimid;
    dimids[2] = lon_dimid;
    if ((retval = nc_def_var(ncid, "lat", NC_DOUBLE, 1, &dimids[1], &lat_varid)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "lon", NC_DOUBLE, 1, &dimids[2], &lon_varid)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "time", NC_DOUBLE, 1, &dimids[0], &time_varid)))
        ERR(retval);
    
    // Add dimension units
    // TODO: this is assuming only 1 weather file, should be changed later
    snprintf(units, MAX_STRING, "Days since %d-01-01", Meteo->StartYear);
    if ((retval = nc_put_att_text(ncid, time_varid, "units", strlen(units), units)))
        ERR(retval);
    
    // Add output variables
    if ((retval = nc_def_var(ncid, "DVS", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "WLV", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "WST", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "WSO", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "WRT", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "LAI", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "WSTR", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "SOILM", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "Rain", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "INF", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "RUNF", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "LOSS", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "NNI", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "PNI", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "KNI", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "SOILN", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "SOILP", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "SOILK", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "NUPT", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "PUPT", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "KUPT", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "NDEM", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "PDEM", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "KDEM", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    
    // Add output units
    // TODO
    
    // End define stage
    if ((retval = nc_enddef(ncid)))
        ERR(retval);
    
    // Fill dimension variables
    pstart[0] = 0;
    time_vals = malloc(NTime * sizeof(*time_vals));
    for (i = 0; i < NTime; i++) {
        time_vals[i] = (double)i;
    }
    
    pcount[0] = NLatitude;
    if ((retval = nc_put_vara_double(ncid, lat_varid, pstart, pcount, &Latitude[0])))
        ERR(retval);
    pcount[0] = NLongitude;
    if ((retval = nc_put_vara_double(ncid, lon_varid, pstart, pcount, &Longitude[0])))
        ERR(retval);
    pcount[0] = NTime;
    if ((retval = nc_put_vara_double(ncid, time_varid, pstart, pcount, time_vals)))
        ERR(retval);
    
    free(time_vals);
}

void OutputNCDF(int *output, SimUnit* sampleGrid) 
{
    size_t j, k;
    int retval;
    int ncid, varid;
    SimUnit ***initial;
    SimUnit *sampleInitial;
    float *data;
    size_t pstart[3];
    size_t pcount[3];
    
    /* Allocate temporary data */
    initial = malloc(NLongitude * sizeof(*initial));
    if(initial == NULL){
        fprintf(stderr, "Could not malloc");
        exit(0); 
    }
    for (j = 0; j < NLongitude; j++) {
        initial[j] = malloc(NLatitude * sizeof(*initial[j]));
        if(initial[j] == NULL){
            fprintf(stderr, "Could not malloc");
            exit(0); 
        }
    }
    data = malloc(NLatitude * NLongitude * sizeof(*data));
    if(data == NULL){
        fprintf(stderr, "Could not malloc");
        exit(0); 
    }
    
    /* Initialize data */
    for (j = 0; j < NLongitude; j++) {
        for(k = 0; k < NLatitude; k++) {
            if (Mask[j][k] == 1){
                initial[j][k] = Grid[j][k];
            } else {
                initial[j][k] = NULL;
            }
        }
    }
    for (j = 0; j < NLatitude * NLongitude; j++) {
        data[j] = NC_FILL_FLOAT;
    }
    
    pstart[0] = Day;
    pstart[1] = 0;
    pstart[2] = 0;
    pcount[0] = 1;
    pcount[1] = NLatitude;
    pcount[2] = NLongitude;
    
    sampleInitial = sampleGrid;
    
    while (sampleGrid) {
        if (sampleGrid->outputType != OUTPUT_NCDF) {
            continue;
        }
        
        ncid = output[sampleGrid->file];
        
        /* Reopen meteo file once-a-year to flush memory*/
        if ((Day % 365) == 0 && Day != 0) {
            nc_sync(ncid);
        }
        
        for(k = 0; k < NLatitude; k++) {
            for (j = 0; j < NLongitude; j++) {
                if (Mask[j][k] == 1) {
                    data[k * NLongitude + j] = Grid[j][k]->crp->st.Development;
                }
            }
        }
        if ((retval = nc_inq_varid(ncid, "DVS", &varid)))
            ERR(retval);
        if ((retval = nc_put_vara_float(ncid, varid, &pstart[0], &pcount[0], data)))
            ERR(retval);

        for(k = 0; k < NLatitude; k++) {
            for (j = 0; j < NLongitude; j++) {
                if (Mask[j][k] == 1) {
                data[k * NLongitude + j] = Grid[j][k]->crp->st.leaves;
                }
            }
        }
        if ((retval = nc_inq_varid(ncid, "WLV", &varid)))
            ERR(retval);
        if ((retval = nc_put_vara_float(ncid, varid, &pstart[0], &pcount[0], data)))
            ERR(retval);

        for(k = 0; k < NLatitude; k++) {
            for (j = 0; j < NLongitude; j++) {
                if (Mask[j][k] == 1) {
                data[k * NLongitude + j] = Grid[j][k]->crp->st.stems;
                }
            }
        }
        if ((retval = nc_inq_varid(ncid, "WST", &varid)))
            ERR(retval);
        if ((retval = nc_put_vara_float(ncid, varid, &pstart[0], &pcount[0], data)))
            ERR(retval);

        for(k = 0; k < NLatitude; k++) {
            for (j = 0; j < NLongitude; j++) {
                if (Mask[j][k] == 1) {
                data[k * NLongitude + j] = Grid[j][k]->crp->st.storage;
                }
            }
        }
        if ((retval = nc_inq_varid(ncid, "WSO", &varid)))
            ERR(retval);
        if ((retval = nc_put_vara_float(ncid, varid, &pstart[0], &pcount[0], data)))
            ERR(retval);

        for(k = 0; k < NLatitude; k++) {
            for (j = 0; j < NLongitude; j++) {
                if (Mask[j][k] == 1) {
                data[k * NLongitude + j] = Grid[j][k]->crp->st.roots;
                }
            }
        }
        if ((retval = nc_inq_varid(ncid, "WRT", &varid)))
            ERR(retval);
        if ((retval = nc_put_vara_float(ncid, varid, &pstart[0], &pcount[0], data)))
            ERR(retval);

        for(k = 0; k < NLatitude; k++) {
            for (j = 0; j < NLongitude; j++) {
                if (Mask[j][k] == 1) {
                data[k * NLongitude + j] = Grid[j][k]->crp->st.LAI;
                }
            }
        }
        if ((retval = nc_inq_varid(ncid, "LAI", &varid)))
            ERR(retval);
        if ((retval = nc_put_vara_float(ncid, varid, &pstart[0], &pcount[0], data)))
            ERR(retval);

        for(k = 0; k < NLatitude; k++) {
            for (j = 0; j < NLongitude; j++) {
                if (Mask[j][k] == 1) {
                data[k * NLongitude + j] = Grid[j][k]->soil->WaterStress;
                }
            }
        }
        if ((retval = nc_inq_varid(ncid, "WSTR", &varid)))
            ERR(retval);
        if ((retval = nc_put_vara_float(ncid, varid, &pstart[0], &pcount[0], data)))
            ERR(retval);

        for(k = 0; k < NLatitude; k++) {
            for (j = 0; j < NLongitude; j++) {
                if (Mask[j][k] == 1) {
                data[k * NLongitude + j] = Grid[j][k]->soil->st.Moisture;
                }
            }
        }
        if ((retval = nc_inq_varid(ncid, "SOILM", &varid)))
            ERR(retval);
        if ((retval = nc_put_vara_float(ncid, varid, &pstart[0], &pcount[0], data)))
            ERR(retval);

//        for(k = 0; k < NLatitude; k++) {
//            for (j = 0; j < NLongitude; j++) {
//                if (Mask[j][k] == 1) {
//                data[k * NLongitude + j] = Rain[j][k];
//                }
//            }
//        }
//        if ((retval = nc_inq_varid(ncid, "Rain", &varid)))
//            ERR(retval);
//        if ((retval = nc_put_vara_float(ncid, varid, &pstart[0], &pcount[0], data)))
//            ERR(retval);

        for(k = 0; k < NLatitude; k++) {
            for (j = 0; j < NLongitude; j++) {
                if (Mask[j][k] == 1) {
                data[k * NLongitude + j] = Grid[j][k]->soil->st.Infiltration;
                }
            }
        }
        if ((retval = nc_inq_varid(ncid, "INF", &varid)))
            ERR(retval);
        if ((retval = nc_put_vara_float(ncid, varid, &pstart[0], &pcount[0], data)))
            ERR(retval);

        for(k = 0; k < NLatitude; k++) {
            for (j = 0; j < NLongitude; j++) {
                if (Mask[j][k] == 1) {
                data[k * NLongitude + j] = Grid[j][k]->soil->st.Runoff;
                }
            }
        }
        if ((retval = nc_inq_varid(ncid, "RUNF", &varid)))
            ERR(retval);
        if ((retval = nc_put_vara_float(ncid, varid, &pstart[0], &pcount[0], data)))
            ERR(retval);

        for(k = 0; k < NLatitude; k++) {
            for (j = 0; j < NLongitude; j++) {
                if (Mask[j][k] == 1) {
                data[k * NLongitude + j] = Grid[j][k]->soil->st.Loss;
                }
            }
        }
        if ((retval = nc_inq_varid(ncid, "LOSS", &varid)))
            ERR(retval);
        if ((retval = nc_put_vara_float(ncid, varid, &pstart[0], &pcount[0], data)))
            ERR(retval);

//        for(k = 0; k < NLatitude; k++) {
//            for (j = 0; j < NLongitude; j++) {
//                if (Mask[j][k] == 1) {
//                data[k * NLongitude + j] = Grid[j][k]->crp->N_st.Indx;
//                }
//            }
//        }
//        if ((retval = nc_inq_varid(ncid, "NNI", &varid)))
//            ERR(retval);
//        if ((retval = nc_put_vara_float(ncid, varid, &pstart[0], &pcount[0], data)))
//            ERR(retval);
//
//        for(k = 0; k < NLatitude; k++) {
//            for (j = 0; j < NLongitude; j++) {
//                if (Mask[j][k] == 1) {
//                data[k * NLongitude + j] = Grid[j][k]->crp->P_st.Indx;
//                }
//            }
//        }
//        if ((retval = nc_inq_varid(ncid, "PNI", &varid)))
//            ERR(retval);
//        if ((retval = nc_put_vara_float(ncid, varid, &pstart[0], &pcount[0], data)))
//            ERR(retval);
//
//        for(k = 0; k < NLatitude; k++) {
//            for (j = 0; j < NLongitude; j++) {
//                if (Mask[j][k] == 1) {
//                data[k * NLongitude + j] = Grid[j][k]->crp->K_st.Indx;
//                }
//            }
//        }
//        if ((retval = nc_inq_varid(ncid, "KNI", &varid)))
//            ERR(retval);
//        if ((retval = nc_put_vara_float(ncid, varid, &pstart[0], &pcount[0], data)))
//            ERR(retval);
//
//        for(k = 0; k < NLatitude; k++) {
//            for (j = 0; j < NLongitude; j++) {
//                if (Mask[j][k] == 1) {
//                data[k * NLongitude + j] = Grid[j][k]->ste->st_N_tot;
//                }
//            }
//        }
//        if ((retval = nc_inq_varid(ncid, "SOILN", &varid)))
//            ERR(retval);
//        if ((retval = nc_put_vara_float(ncid, varid, &pstart[0], &pcount[0], data)))
//            ERR(retval);
//
//        for(k = 0; k < NLatitude; k++) {
//            for (j = 0; j < NLongitude; j++) {
//                if (Mask[j][k] == 1) {
//                data[k * NLongitude + j] = Grid[j][k]->ste->st_P_tot;
//                }
//            }
//        }
//        if ((retval = nc_inq_varid(ncid, "SOILP", &varid)))
//            ERR(retval);
//        if ((retval = nc_put_vara_float(ncid, varid, &pstart[0], &pcount[0], data)))
//            ERR(retval);
//
//        for(k = 0; k < NLatitude; k++) {
//            for (j = 0; j < NLongitude; j++) {
//                if (Mask[j][k] == 1) {
//                data[k * NLongitude + j] = Grid[j][k]->ste->st_K_tot;
//                }
//            }
//        }
//        if ((retval = nc_inq_varid(ncid, "SOILK", &varid)))
//            ERR(retval);
//        if ((retval = nc_put_vara_float(ncid, varid, &pstart[0], &pcount[0], data)))
//            ERR(retval);
//
//        for(k = 0; k < NLatitude; k++) {
//            for (j = 0; j < NLongitude; j++) {
//                if (Mask[j][k] == 1) {
//                data[k * NLongitude + j] = Grid[j][k]->crp->N_st.Uptake;
//                }
//            }
//        }
//        if ((retval = nc_inq_varid(ncid, "NUPT", &varid)))
//            ERR(retval);
//        if ((retval = nc_put_vara_float(ncid, varid, &pstart[0], &pcount[0], data)))
//            ERR(retval);
//
//        for(k = 0; k < NLatitude; k++) {
//            for (j = 0; j < NLongitude; j++) {
//                if (Mask[j][k] == 1) {
//                data[k * NLongitude + j] = Grid[j][k]->crp->P_st.Uptake;
//                }
//            }
//        }
//        if ((retval = nc_inq_varid(ncid, "PUPT", &varid)))
//            ERR(retval);
//        if ((retval = nc_put_vara_float(ncid, varid, &pstart[0], &pcount[0], data)))
//            ERR(retval);
//
//        for(k = 0; k < NLatitude; k++) {
//            for (j = 0; j < NLongitude; j++) {
//                if (Mask[j][k] == 1) {
//                data[k * NLongitude + j] = Grid[j][k]->crp->K_st.Uptake;
//                }
//            }
//        }
//        if ((retval = nc_inq_varid(ncid, "KUPT", &varid)))
//            ERR(retval);
//        if ((retval = nc_put_vara_float(ncid, varid, &pstart[0], &pcount[0], data)))
//            ERR(retval);
//
//        for(k = 0; k < NLatitude; k++) {
//            for (j = 0; j < NLongitude; j++) {
//                if (Mask[j][k] == 1) {
//                data[k * NLongitude + j] = Grid[j][k]->crp->N_rt.Demand_lv + Grid[j][k]->crp->N_rt.Demand_st + Grid[j][k]->crp->N_rt.Demand_ro;
//                }
//            }
//        }
//        if ((retval = nc_inq_varid(ncid, "NDEM", &varid)))
//            ERR(retval);
//        if ((retval = nc_put_vara_float(ncid, varid, &pstart[0], &pcount[0], data)))
//            ERR(retval);
//
//        for(k = 0; k < NLatitude; k++) {
//            for (j = 0; j < NLongitude; j++) {
//                if (Mask[j][k] == 1) {
//                data[k * NLongitude + j] = Grid[j][k]->crp->P_rt.Demand_lv + Grid[j][k]->crp->P_rt.Demand_st + Grid[j][k]->crp->P_rt.Demand_ro;
//                }
//            }
//        }
//        if ((retval = nc_inq_varid(ncid, "PDEM", &varid)))
//            ERR(retval);
//        if ((retval = nc_put_vara_float(ncid, varid, &pstart[0], &pcount[0], data)))
//            ERR(retval);
//
//        for(k = 0; k < NLatitude; k++) {
//            for (j = 0; j < NLongitude; j++) {
//                if (Mask[j][k] == 1) {
//                data[k * NLongitude + j] = Grid[j][k]->crp->K_rt.Demand_lv + Grid[j][k]->crp->K_rt.Demand_st + Grid[j][k]->crp->K_rt.Demand_ro;
//                }
//            }
//        }
//        if ((retval = nc_inq_varid(ncid, "KDEM", &varid)))
//            ERR(retval);
//        if ((retval = nc_put_vara_float(ncid, varid, &pstart[0], &pcount[0], data)))
//            ERR(retval);
        
        sampleGrid = sampleGrid->next;
        for(k = 0; k < NLatitude; k++) {
            for (j = 0; j < NLongitude; j++) {
                if (Grid[j][k] != NULL){
                    Grid[j][k] = Grid[j][k]->next;
                }
            }
        }
    }
    
    /* Go back to the beginning of the list */
    sampleGrid = sampleInitial;
    for(k = 0; k < NLatitude; k++) {
        for (j = 0; j < NLongitude; j++) {
            Grid[j][k] = initial[j][k];
        }
    }
    
    /* Clear temporary data */
    for (j = 0; j < NLongitude; j++) {
        free(initial[j]);
    }
    free(initial);
    free(data);
}
