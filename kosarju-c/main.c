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


char * getExampleFileName() {
   return "./test-files/input_mostlyCycles_1_8.txt";
}

/*
 * 
 */
int main(int argc, char** argv) {
    char * fname = getExampleFileName();
    int nrows = 0;
    char ** rows = loadFromAdjacencyList(fname, &nrows);
    graph * g = loadd_adj_list(rows, &nrows);
    free_graph(g);
    free_rows(rows, nrows);
    return (EXIT_SUCCESS);
}

