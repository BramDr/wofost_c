#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <netcdf.h>
#include "wofost.h"
#include "extern.h"

/* Handle errors by printing an error message and exiting with a
 * non-zero status. */
#define ERR(e) {printf("Error: %s\n", nc_strerror(e)); exit(2);}

/* ------------------------------------------------------------------------*/
/*  function GetCropData()                                                 */
/*  Purpose: Read the Wofost crop file and store the parameters and tables */
/* ------------------------------------------------------------------------*/

void GetStartData(int ***Start, char *startfile)
{
    size_t j, k;
    
    int retval;
    int ncid, varid;
    int *data = NULL;
    
    // open file
    if ((retval = nc_open(startfile, NC_NOWRITE, &ncid)))
        ERR(retval);

    // Fill start
    data = malloc(NLongitude * NLatitude * sizeof(*data));
    if(data == NULL){
        fprintf(stderr, "Could not malloc");
        exit(0); 
    }
    if ((retval = nc_inq_varid(ncid, "start", &varid)))
        ERR(retval);
    if((retval = nc_get_var_int(ncid, varid, data)))
        ERR(retval);
    for (k = 0; k < NLatitude; k++) {
        for (j = 0; j < NLongitude; j++) {
            (*Start)[j][k] = data[k * NLongitude + j];
        }
    }
    free(data);
    
    // close file
    if ((retval = nc_close(ncid)))
        ERR(retval);
}

void GetEndData(int ***End, char *endfile)
{
    size_t j, k;
    
    int retval;
    int ncid, varid;
    int *data;
    
    // open file
    if ((retval = nc_open(endfile, NC_NOWRITE, &ncid)))
        ERR(retval);

    // Fill start
    data = malloc(NLongitude * NLatitude * sizeof(*data));
    if(data == NULL){
        fprintf(stderr, "Could not malloc");
        exit(0); 
    }
    if ((retval = nc_inq_varid(ncid, "end", &varid)))
        ERR(retval);
    if((retval = nc_get_var_int(ncid, varid, data)))
        ERR(retval);
    for (k = 0; k < NLatitude; k++) {
        for (j = 0; j < NLongitude; j++) {
            (*End)[j][k] = data[k * NLongitude + j];
        }
    }
    free(data);
    
    // close file
    if ((retval = nc_close(ncid)))
        ERR(retval);
}