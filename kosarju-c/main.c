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


char * getExampleFileName() {
   return "./test-files/input_mostlyCycles_16_64.txt";
}

/*
 * 
 */
int main(int argc, char** argv) {
    char * fname = getExampleFileName();
    int nrows = 0;
    char ** rows = loadFromAdjacencyList(fname, &nrows);
    graph * g = loadd_adj_list(rows, &nrows);

    printf("\n***** Graph After Kosarju *******");
    kosarju_scc_twopass(g);
    for(int i = 0; i < g->vlen; i ++) {
        vertex * leader = g->vertices[i]->leader;
        printf("\n vertex: %s, scc: %s", g->vertices[i]->label, leader->label);
    }
    
    free_graph(g);
    free_rows(rows, nrows);
    return (EXIT_SUCCESS);
}

