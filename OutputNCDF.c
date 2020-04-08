#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netcdf.h>
#include "extern.h"
#include "wofost.h"

/* Handle errors by printing an error message and exiting with a
 * non-zero status. */
#define ERR(e) {printf("Error: %s\n", nc_strerror(e)); exit(2);}

void headerNCDF(int ncid, int freq) 
{
    
    size_t i;
    int retval;
    int lat_dimid, lon_dimid, time_dimid;
    int lat_varid, lon_varid, time_varid;
    int missval_int = NC_FILL_INT;
    float missval_float = NC_FILL_FLOAT;
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
    if ((retval = nc_def_var(ncid, "GROW", NC_INT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_put_att_int(ncid, varid, "_FillValue", NC_INT, 1, &missval_int)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "CULTIVATE", NC_INT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_put_att_int(ncid, varid, "_FillValue", NC_INT, 1, &missval_int)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "DVS", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_put_att_float(ncid, varid, "_FillValue", NC_FLOAT, 1, &missval_float)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "WLV", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_put_att_float(ncid, varid, "_FillValue", NC_FLOAT, 1, &missval_float)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "WST", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_put_att_float(ncid, varid, "_FillValue", NC_FLOAT, 1, &missval_float)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "WSO", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_put_att_float(ncid, varid, "_FillValue", NC_FLOAT, 1, &missval_float)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "WRT", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_put_att_float(ncid, varid, "_FillValue", NC_FLOAT, 1, &missval_float)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "LAI", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_put_att_float(ncid, varid, "_FillValue", NC_FLOAT, 1, &missval_float)))
        ERR(retval);
    
    if ((retval = nc_def_var(ncid, "WSTR", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_put_att_float(ncid, varid, "_FillValue", NC_FLOAT, 1, &missval_float)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "SOILM", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_put_att_float(ncid, varid, "_FillValue", NC_FLOAT, 1, &missval_float)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "Rain", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_put_att_float(ncid, varid, "_FillValue", NC_FLOAT, 1, &missval_float)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "INF", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_put_att_float(ncid, varid, "_FillValue", NC_FLOAT, 1, &missval_float)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "RUNF", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_put_att_float(ncid, varid, "_FillValue", NC_FLOAT, 1, &missval_float)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "LOSS", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_put_att_float(ncid, varid, "_FillValue", NC_FLOAT, 1, &missval_float)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "SEVAP", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_put_att_float(ncid, varid, "_FillValue", NC_FLOAT, 1, &missval_float)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "TRANS", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_put_att_float(ncid, varid, "_FillValue", NC_FLOAT, 1, &missval_float)))
        ERR(retval);
    
    if ((retval = nc_def_var(ncid, "NNI", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_put_att_float(ncid, varid, "_FillValue", NC_FLOAT, 1, &missval_float)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "PNI", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_put_att_float(ncid, varid, "_FillValue", NC_FLOAT, 1, &missval_float)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "KNI", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_put_att_float(ncid, varid, "_FillValue", NC_FLOAT, 1, &missval_float)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "SOILN", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_put_att_float(ncid, varid, "_FillValue", NC_FLOAT, 1, &missval_float)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "SOILP", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_put_att_float(ncid, varid, "_FillValue", NC_FLOAT, 1, &missval_float)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "SOILK", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_put_att_float(ncid, varid, "_FillValue", NC_FLOAT, 1, &missval_float)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "NUPT", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_put_att_float(ncid, varid, "_FillValue", NC_FLOAT, 1, &missval_float)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "PUPT", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_put_att_float(ncid, varid, "_FillValue", NC_FLOAT, 1, &missval_float)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "KUPT", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_put_att_float(ncid, varid, "_FillValue", NC_FLOAT, 1, &missval_float)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "NDEM", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_put_att_float(ncid, varid, "_FillValue", NC_FLOAT, 1, &missval_float)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "PDEM", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_put_att_float(ncid, varid, "_FillValue", NC_FLOAT, 1, &missval_float)))
        ERR(retval);
    if ((retval = nc_def_var(ncid, "KDEM", NC_FLOAT, 3, &dimids[0], &varid)))
        ERR(retval);
    if ((retval = nc_def_var_deflate(ncid, varid, 1, 1, 9)))
        ERR(retval);
    if ((retval = nc_put_att_float(ncid, varid, "_FillValue", NC_FLOAT, 1, &missval_float)))
        ERR(retval);
    
    // Add output attriutes
    // TODO
    
    // End define stage
    if ((retval = nc_enddef(ncid)))
        ERR(retval);
    
    // Fill dimension variables
    pstart[0] = 0;
    
    pcount[0] = NLatitude;
    if ((retval = nc_put_vara_double(ncid, lat_varid, pstart, pcount, &Latitude[0])))
        ERR(retval);
    pcount[0] = NLongitude;
    if ((retval = nc_put_vara_double(ncid, lon_varid, pstart, pcount, &Longitude[0])))
        ERR(retval);
    
    if (freq == OUTPUT_SEASONALLY) {
        pcount[0] = NYears;
        time_vals = malloc(NYears * sizeof(*time_vals));
        for (i = 0; i < NYears; i++) {
            if (i == 0) {
                time_vals[i] = 0;
            } else {
                time_vals[i] = time_vals[i - 1] + (double)leap_year(Meteo->StartYear + i);
            }
        }
    } else if (freq == OUTPUT_DAILY) {
        pcount[0] = NTime;
        time_vals = malloc(NTime * sizeof(*time_vals));
        for (i = 0; i < NTime; i++) {
            if (i == 0) {
                time_vals[i] = 0;
            } else {
                time_vals[i] = time_vals[i - 1] + 1;
            }
        }
    } else {
        fprintf(stderr, "Undefined output frequency %d", freq);
    }
    
    if ((retval = nc_put_vara_double(ncid, time_varid, pstart, pcount, time_vals)))
        ERR(retval);
    
    free(time_vals);
}

void OutputNCDF(int ncid, int freq) 
{
    int retval;
    int varid;
    float data;
    size_t pstart[3];
    size_t pcount[3];
    
    if (freq == OUTPUT_SEASONALLY) {
        pstart[0] = MeteoYear[Day] - Meteo->StartYear;
    } else if (freq == OUTPUT_DAILY) {
        pstart[0] = Day;
    } else {
        fprintf(stderr, "Undefined output frequency %d", freq);
    }
    
    pstart[1] = Lat;
    pstart[2] = Lon;
    pcount[0] = 1;
    pcount[1] = 1;
    pcount[2] = 1;
    
    if ((retval = nc_inq_varid(ncid, "GROW", &varid)))
        ERR(retval);
    if ((retval = nc_put_vara_int(ncid, varid, &pstart[0], &pcount[0], &(Crop->GrowthDay))))
        ERR(retval);
    
    if ((retval = nc_inq_varid(ncid, "CULTIVATE", &varid)))
        ERR(retval);
    if ((retval = nc_put_vara_int(ncid, varid, &pstart[0], &pcount[0], &(Crop->CultivateDay))))
        ERR(retval);
        
    if ((retval = nc_inq_varid(ncid, "DVS", &varid)))
        ERR(retval);
    if ((retval = nc_put_vara_float(ncid, varid, &pstart[0], &pcount[0], &(Crop->st.Development))))
        ERR(retval);

    if ((retval = nc_inq_varid(ncid, "WLV", &varid)))
        ERR(retval);
    if ((retval = nc_put_vara_float(ncid, varid, &pstart[0], &pcount[0], &(Crop->st.leaves))))
        ERR(retval);

    if ((retval = nc_inq_varid(ncid, "WST", &varid)))
        ERR(retval);
    if ((retval = nc_put_vara_float(ncid, varid, &pstart[0], &pcount[0], &(Crop->st.stems))))
        ERR(retval);

    if ((retval = nc_inq_varid(ncid, "WSO", &varid)))
        ERR(retval);
    if ((retval = nc_put_vara_float(ncid, varid, &pstart[0], &pcount[0], &(Crop->st.storage))))
        ERR(retval);

    if ((retval = nc_inq_varid(ncid, "WRT", &varid)))
        ERR(retval);
    if ((retval = nc_put_vara_float(ncid, varid, &pstart[0], &pcount[0], &(Crop->st.roots))))
        ERR(retval);

    data = Crop->LAIAvg / Crop->GrowthDay;
    if ((retval = nc_inq_varid(ncid, "LAI", &varid)))
        ERR(retval);
    if ((retval = nc_put_vara_float(ncid, varid, &pstart[0], &pcount[0], &data)))
        ERR(retval);

    data = WatBal->WaterStressAvg / Crop->GrowthDay;
    if ((retval = nc_inq_varid(ncid, "WSTR", &varid)))
        ERR(retval);
    if ((retval = nc_put_vara_float(ncid, varid, &pstart[0], &pcount[0], &data)))
        ERR(retval);

    if ((retval = nc_inq_varid(ncid, "Rain", &varid)))
        ERR(retval);
    if ((retval = nc_put_vara_float(ncid, varid, &pstart[0], &pcount[0], &(WatBal->st.Rain))))
        ERR(retval);

    if ((retval = nc_inq_varid(ncid, "SOILM", &varid)))
        ERR(retval);
    if ((retval = nc_put_vara_float(ncid, varid, &pstart[0], &pcount[0], &(WatBal->st.Moisture))))
        ERR(retval);

    if ((retval = nc_inq_varid(ncid, "INF", &varid)))
        ERR(retval);
    if ((retval = nc_put_vara_float(ncid, varid, &pstart[0], &pcount[0], &(WatBal->st.Infiltration))))
        ERR(retval);

    if ((retval = nc_inq_varid(ncid, "RUNF", &varid)))
        ERR(retval);
    if ((retval = nc_put_vara_float(ncid, varid, &pstart[0], &pcount[0], &(WatBal->st.Runoff))))
        ERR(retval);

    if ((retval = nc_inq_varid(ncid, "LOSS", &varid)))
        ERR(retval);
    if ((retval = nc_put_vara_float(ncid, varid, &pstart[0], &pcount[0], &(WatBal->st.Loss))))
        ERR(retval);

    if ((retval = nc_inq_varid(ncid, "SEVAP", &varid)))
        ERR(retval);
    if ((retval = nc_put_vara_float(ncid, varid, &pstart[0], &pcount[0], &(WatBal->st.EvapSoil))))
        ERR(retval);

    if ((retval = nc_inq_varid(ncid, "TRANS", &varid)))
        ERR(retval);
    if ((retval = nc_put_vara_float(ncid, varid, &pstart[0], &pcount[0], &(WatBal->st.Transpiration))))
        ERR(retval);

    if ((retval = nc_inq_varid(ncid, "SOILN", &varid)))
        ERR(retval);
    if ((retval = nc_put_vara_float(ncid, varid, &pstart[0], &pcount[0], &(Site->st_N_tot))))
        ERR(retval);

    if ((retval = nc_inq_varid(ncid, "SOILP", &varid)))
        ERR(retval);
    if ((retval = nc_put_vara_float(ncid, varid, &pstart[0], &pcount[0], &(Site->st_P_tot))))
        ERR(retval);

    if ((retval = nc_inq_varid(ncid, "SOILK", &varid)))
        ERR(retval);
    if ((retval = nc_put_vara_float(ncid, varid, &pstart[0], &pcount[0], &(Site->st_K_tot))))
        ERR(retval);
    
    if ((retval = nc_inq_varid(ncid, "NUPT", &varid)))
        ERR(retval);
    if ((retval = nc_put_vara_float(ncid, varid, &pstart[0], &pcount[0], &(Crop->N_st.Uptake))))
        ERR(retval);

    if ((retval = nc_inq_varid(ncid, "PUPT", &varid)))
        ERR(retval);
    if ((retval = nc_put_vara_float(ncid, varid, &pstart[0], &pcount[0], &(Crop->P_st.Uptake))))
        ERR(retval);

    if ((retval = nc_inq_varid(ncid, "KUPT", &varid)))
        ERR(retval);
    if ((retval = nc_put_vara_float(ncid, varid, &pstart[0], &pcount[0], &(Crop->K_st.Uptake))))
        ERR(retval);
    if ((retval = nc_inq_varid(ncid, "NDEM", &varid)))
        ERR(retval);
    if ((retval = nc_put_vara_float(ncid, varid, &pstart[0], &pcount[0], &(Crop->N_st.Demand))))
        ERR(retval);

    if ((retval = nc_inq_varid(ncid, "PDEM", &varid)))
        ERR(retval);
    if ((retval = nc_put_vara_float(ncid, varid, &pstart[0], &pcount[0], &(Crop->P_st.Demand))))
        ERR(retval);

    if ((retval = nc_inq_varid(ncid, "KDEM", &varid)))
        ERR(retval);
    if ((retval = nc_put_vara_float(ncid, varid, &pstart[0], &pcount[0], &(Crop->K_st.Demand))))
        ERR(retval);
}
