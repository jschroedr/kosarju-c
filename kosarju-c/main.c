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
   return "./test-files/input_mostlyCycles_60_80000.txt";
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
    
    kosarju_scc_twopass(g);
    
    garray * groups = groups_from_graph(g);
   
    sort_groups_by_size(groups);
    
    /*
    printf("\n");
    for(int v = 0; v < g->vlen; v ++) {
        printf("\nvertex: %s, leader: %s", g->vertices[v]->label, ((vertex *)g->vertices[v]->leader)->label);
    }
    */
    
    printf("\n");
    for(int k = 0; k < 5; k ++) {
        if (k < groups->glen) {
            // printf("(leader: %s, len: %d),", groups->groups[k]->leader->label, groups->groups[k]->len);
            if (k < 4) {
                printf("%d,", groups->groups[k]->len);
            } else {
                printf("%d", groups->groups[k]->len);
            }
            
        } else {
            printf("0,");
        }
    }
    
    
    
    free_graph(g);
    free_rows(rows, nrows);
    return (EXIT_SUCCESS);
}

