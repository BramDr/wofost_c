#include <stdio.h>#include <string.h>#include <stdlib.h>#include <limits.h>#include <netcdf.h>#include <math.h>#include "wofost.h"#include "extern.h"/* Handle errors by printing an error message and exiting with a * non-zero status. */#define ERR(e) {printf("Error: %s\n", nc_strerror(e)); exit(2);}int InitializeMeteo(Weather* Meteo){    int i;    size_t j, k, l;        int retval;    int lat_dimid, lon_dimid, time_dimid;    int lat_varid, lon_varid;        size_t lat_length, lon_length, time_length;    double tmpLatitude[DOMAIN_LENGTH], tmpLongitude[DOMAIN_LENGTH];        float ***variable;        for (i = 0; i < WEATHER_NTYPES; i++) {                // open file        if ((retval = nc_open(Meteo->file[i], NC_NOWRITE, &Meteo->ncid[i])))            ERR(retval);                // get lat & lon        if ((retval = nc_inq_dimid(Meteo->ncid[i], "lat", &lat_dimid)))            ERR(retval);        if ((retval = nc_inq_dimid(Meteo->ncid[i], "lon", &lon_dimid)))            ERR(retval);        if ((retval = nc_inq_dimlen(Meteo->ncid[i], lat_dimid, &lat_length)))           ERR(retval);         if ((retval = nc_inq_dimlen(Meteo->ncid[i], lon_dimid, &lon_length)))           ERR(retval);        if (lat_length > DOMAIN_LENGTH) {            fprintf(stderr, "Latitude domain %zu is bigger than maximum %d\n",                     lat_length, DOMAIN_LENGTH);            exit(2);         }        if (lon_length > DOMAIN_LENGTH) {            fprintf(stderr, "Longitude domain %zu is bigger than maximum %d\n",                     lon_length, DOMAIN_LENGTH);            exit(2);         }        if ((retval = nc_inq_varid(Meteo->ncid[i], "lat", &lat_varid)))            ERR(retval);        if ((retval = nc_inq_varid(Meteo->ncid[i], "lon", &lon_varid)))            ERR(retval);        if ((retval = nc_get_var_double(Meteo->ncid[i], lat_varid, &tmpLatitude[0])))           ERR(retval);        if ((retval = nc_get_var_double(Meteo->ncid[i], lon_varid, &tmpLongitude[0])))           ERR(retval);                // check lat & lon        for (j = 0; j < NLatitude; j++) {            if(Latitude[j] != tmpLatitude[j]) {                fprintf(stderr, "Latitude and/or longitude weather domain "                                "[%lf -> %lf N %lf -> %lf E] "                                "is different from mask domain "                                "[%lf -> %lf N %lf -> %lf E]\n",                         tmpLatitude[0], tmpLatitude[NLatitude - 1],                         tmpLongitude[0], tmpLongitude[NLongitude - 1],                         Latitude[0], Latitude[NLatitude - 1],                         Longitude[0], Longitude[NLongitude - 1]);                //exit(2);             }        }        for (j = 0; j < NLongitude; j++) {            if(Longitude[j] != tmpLongitude[j]) {                fprintf(stderr, "Latitude and/or longitude weather domain "                                "[%lf -> %lf N %lf -> %lf E] "                                "is different from mask domain "                                "[%lf -> %lf N %lf -> %lf E]\n",                         tmpLatitude[0], tmpLatitude[NLatitude - 1],                         tmpLongitude[0], tmpLongitude[NLongitude - 1],                         Latitude[0], Latitude[NLatitude - 1],                         Longitude[0], Longitude[NLongitude - 1]);                //exit(2);             }        }                // get time        // TODO: load time based on actual netcdf values        if ((retval = nc_inq_dimid(Meteo->ncid[i], "time", &time_dimid)))            ERR(retval);        if ((retval = nc_inq_dimlen(Meteo->ncid[i], time_dimid, &time_length)))           ERR(retval);         if (time_length > METEO_LENGTH) {            fprintf(stderr, "Time %zu is bigger than maximum %d\n",                     time_length, METEO_LENGTH);            exit(2);         }        for (l = 0; l < NTime; l++) {            if (l == 0) {                MeteoYear[l] = Meteo->StartYear;                MeteoDay[l] = 1; //assume that the series start January first            } else {                MeteoYear[l] = MeteoYear[l - 1];                MeteoDay[l] = MeteoDay[l - 1] + 1;                                if(MeteoDay[l] > leap_year(MeteoYear[l])) {                    MeteoYear[l] = MeteoYear[l] + 1;                    MeteoDay[l] = 1;                }            }        }                // check time        if(MeteoYear[0] != Meteo->StartYear ||            MeteoDay[0] != 1 ||           MeteoYear[NTime - 1] < Meteo->EndYear ||            MeteoDay[NTime - 1] < leap_year(Meteo->EndYear)) {            fprintf(stderr, "Year and/or day weather time "                            "[%d-%d -> %d-%d] "                            "is different from supplied time "                            "[%d:%d -> %d:%d]\n",                      MeteoYear[0], MeteoDay[0],                      MeteoYear[NTime - 1], MeteoDay[NTime - 1],                      Meteo->StartYear, 1,                      Meteo->EndYear, leap_year(Meteo->EndYear));            exit(0);         }                // allocate variable        if ((retval = nc_inq_varid(Meteo->ncid[i], Meteo->var[i], &Meteo->varid[i])))            ERR(retval);        if (i == WEATHER_TMIN) {            variable = &Tmin;        } else if (i == WEATHER_TMAX) {            variable = &Tmax;        } else if (i == WEATHER_RADIATION) {            variable = &Radiation;        } else if (i == WEATHER_RAIN) {            variable = &Rain;        } else if (i == WEATHER_WINDSPEED) {            variable = &Windspeed;        } else if (i == WEATHER_VAPOUR) {            variable = &Vapour;        }        (*variable) = malloc(NLongitude * sizeof(*(*variable)));        if((*variable) == NULL){            fprintf(stderr, "Could not malloc");            exit(0);         }        for (j = 0; j < NLongitude; j++) {            (*variable)[j] = malloc(NLatitude * sizeof(*(*variable)[j]));            if((*variable)[j] == NULL){                fprintf(stderr, "Could not malloc");                exit(0);             }        }    }        TminPrev = malloc(NLongitude * sizeof(*TminPrev));    if(TminPrev == NULL){        fprintf(stderr, "Could not malloc");        exit(0);     }    for (j = 0; j < NLongitude; j++) {        TminPrev[j] = malloc(NLatitude * sizeof(*TminPrev[j]));        if(TminPrev[j] == NULL){            fprintf(stderr, "Could not malloc");            exit(0);         }        for(k = 0; k < NLatitude; k++) {            TminPrev[j][k] = malloc(7 * sizeof(*TminPrev[j][k]));            if(TminPrev[j][k] == NULL){                fprintf(stderr, "Could not malloc");                exit(0);             }        }    }            return 1;}