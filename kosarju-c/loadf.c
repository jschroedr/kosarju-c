/**
 * 
 * load file module
 * `````````````````````````````````````````````````````````````````````````````
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


FILE * loadFile( char * fname ) {
    FILE * f = fopen(fname, "r");
    if (f == NULL) {
        perror("loadf.c: Error opening input file");
        exit(EXIT_FAILURE);
    }
    return f;
}

char ** loadFromAdjacencyList( char * fname ) {
    
    // generate a valid file pointer
    FILE * f = loadFile(fname);
    
    char ** rows = NULL;
    int rlen = 0;  // counter for rows
    
    int nread;
    
    size_t len;
    
    char * line = NULL;
    
    while((nread = getline(&line, &len, f)) != -1) {
        
        // calculate the length of the line in characters
        int slen = strlen(line);
        
        // append the row to our list of rows
        rows = realloc(rows, sizeof(char **) * (rlen + 2));
        rows[rlen] = realloc(rows[rlen], sizeof(char *) * (slen + 1));
        
        strncpy(rows[rlen], line, len);
        
        rlen ++;  // aka new row
        
    } 
    return rows;
}
