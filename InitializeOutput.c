#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <float.h>
#include "wofost.h"
#include "extern.h"


void InitializeOutput(FILE *****output, int NumberOfFiles)
{
    size_t j, k;
    SimUnit *initial  = NULL;
    char name[MAX_STRING];
    
    /* Allocate memory for the file pointers */
    (*output) = malloc(NLongitude * sizeof(*(*output)));
    if((*output) == NULL){
        fprintf(stderr, "Could not malloc");
        exit(0); 
    }
    for (j = 0; j < NLongitude; j++) {
        (*output)[j] = malloc(NLatitude * sizeof(*(*output)[j]));
        if((*output)[j] == NULL){
            fprintf(stderr, "Could not malloc");
            exit(0); 
        }
        for (k = 0; k < NLatitude; k++) {
            (*output)[j][k] = malloc(NumberOfFiles * sizeof(*(*output)[j][k]));
            if((*output)[j][k] == NULL){
                fprintf(stderr, "Could not malloc");
                exit(0); 
            }
        }
    }
    
    /* Open the output files */
    for (j = 0; j < NLongitude; j++) {
        for(k = 0; k < NLatitude; k++) {
            
            initial = Grid[j][k];
            while (Grid[j][k])
            {   
                /* Make valgrind happy  */
                memset(name,'\0',MAX_STRING);
                strncpy(name, Grid[j][k]->output, strlen(Grid[j][k]->output));

                (*output)[j][k][Grid[j][k]->file] = fopen(name, "w");
                if((*output)[j][k][Grid[j][k]->file] == NULL){
                    fprintf(stderr, "Cannot initialize output file %s.\n", name);
                    exit(0);
                }
                
                header((*output)[j][k][Grid[j][k]->file]);
                Grid[j][k] = Grid[j][k]->next;
            }
            
            /* Go back to the beginning of the list */
            Grid[j][k] = initial;
            initial = NULL;
        }
    }
}
