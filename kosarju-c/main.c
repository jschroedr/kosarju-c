/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: jake
 *
 * Created on November 15, 2020, 6:39 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "loadf.h"
#include "loadd.h"
#include "kosarju.h"
#include "group.h"


char * getExampleFileName() {
   // return "/home/jake/Documents/Learning/kosarju-c/kosarju-c/test-files/input_mostlyCycles_64_160000.txt";
   return "/home/jake/Documents/Learning/kosarju-c/kosarju-c/test-files/assn.txt";
}

/*
 * 
 */
int main(int argc, char** argv) {
    char * fname = getExampleFileName();
    printf("\nfile: %s", fname);
    long long nrows = 0;
    char ** rows = loadFromAdjacencyList(fname, &nrows);
    
    graph * g = loadd_adj_list(rows, &nrows);
    free_rows(rows, nrows);
    
    
    kosarju_scc_twopass(g);
    
    garray * groups = groups_from_graph(g);
   
    sort_groups_by_size(groups);
    
    printf("\n");
    for(int k = 0; k < 5; k ++) {
        if (k < groups->glen) {
            printf("%lld", groups->groups[k]->len);
            
        } else {
            printf("0");
        }
        if (k < 4) {
            printf(",");
        } 
    }
    
    free_graph(g);
    
    return (EXIT_SUCCESS);
}

