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

char ** loadFromAdjacencyList( char * fname, int * nrows ) {
    
    // generate a valid file pointer
    FILE * f = loadFile(fname);
    
    char ** rows = NULL;
    int rlen = 0;  // counter for rows
    
    int nread;
    
    // len: size of the resulting string in bytes from getline()
    size_t len;
    
    // line: 
    char * line = NULL;
    
    while((nread = getline(&line, &len, f)) != -1) {
        
        // calculate the length of the line in characters
        int slen = strlen(line);  // plus null terminator
        
        rlen ++;
        rows = realloc(rows, sizeof(char **) * rlen);
        rows[rlen - 1] = malloc(sizeof(char *) * (slen + 1));
        
        // append the row to our list of rows
        strncpy(rows[rlen - 1], line, slen);
        
    } 
    *nrows = rlen;
    return rows;
}
