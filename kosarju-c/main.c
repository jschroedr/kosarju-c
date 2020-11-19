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
   return "./test-files/input_mostlyCycles_1_8.txt";
}

/*
 * 
 */
int main(int argc, char** argv) {
    char * fname = getExampleFileName();
    printf("\nfile: %s", fname);
    int nrows = 0;
    char ** rows = loadFromAdjacencyList(fname, &nrows);
    graph * g = loadd_adj_list(rows, &nrows);

    printf("\n***** Graph After Kosarju *******");
    kosarju_scc_twopass(g);
    for(int i = 0; i < g->vlen; i ++) {
        vertex * leader = g->vertices[i]->leader;
        printf("\n vertex: %s, scc: %s", g->vertices[i]->label, leader->label);
    }
    
    garray * groups = groups_from_graph(g);
   
    printf("\n***** Graph Groups Unordered *******");
    for(int j = 0; j < groups->glen; j ++) {
        group * gr = groups->groups[j];
        printf("\n group: %s, glen: %d", gr->leader->label, gr->len);
    }
    printf("\n**************************************");
    
    sort_groups_by_size(groups);
    
    printf("\n***** Graph Groups By Size *******");
    for(int k = 0; k < groups->glen; k ++) {
        group * gr = groups->groups[k];
        printf("\n group: %s, glen: %d", gr->leader->label, gr->len);
    }
    
    printf("\n");
    for(int k = 0; k < 5; k ++) {
        if (k < groups->glen) {
            printf("%d,", groups->groups[k]->len);
        } else {
            printf("0,");
        }
    }
    
    
    free_graph(g);
    free_rows(rows, nrows);
    return (EXIT_SUCCESS);
}

