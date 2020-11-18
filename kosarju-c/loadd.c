/**
 *
 * load directed graph module
 * `````````````````````````````````````````````````````````````````````````````
 * 
 * read in a file and produce a directed graph data structure in memory
 * 
 */
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "graph.h"



int __loadd_check_exists_vertex(graph * g, char * label) {
    for(int i = 0; i < g->vlen; i++) {
        int label_match = strcmp(
            g->vertices[i]->label, 
            label
        );
        if (label_match == 0) {
            return i;
        }
    }
    return 0;
}


graph * __loadd_create_vertex(graph * g, char * label, int llen) {
    int len = llen + 1;  // +1 for null terminator
    char * cpy = malloc(sizeof(cpy) * len);
    strncpy(cpy, label, len);
    
    g->vlen ++;
    g->vertices = realloc(g->vertices, sizeof(vertex **) * g->vlen);
    if(!g->vertices) {
        perror("loadd.c: g->vertices allocation failed");
        exit(EXIT_FAILURE);
    }
    
    vertex * v = malloc(sizeof(*v));
    v->elen = 0;
    v->label = cpy;
    v->edges = malloc(sizeof(edge));
    
    v->discovered = 0;
    v->leader = NULL;
    v->isLeader = 0;
    
    g->vertices[g->vlen - 1] = v;
    
    return g;
}


graph * _loadd_check_and_create_vertex(graph * g, char * label, int llen, int * idx) {
    int exists = __loadd_check_exists_vertex(g, label);
    if(exists == 0) {
        g = __loadd_create_vertex(g, label, llen);
        *idx = g->vlen - 1;
    } else {
        *idx = exists;
    }
    return g;
}


int __loadd_check_exists_edge(graph * g, int hidx, int tidx) {
    char * head_label = g->vertices[hidx]->label;
    char * tail_label = g->vertices[tidx]->label;
    for(int i = 0; i < g->elen; i ++) {
        edge * e = g->edges[i];
        int exact_match = (
            strcmp(e->head->label, head_label) &&
            strcmp(e->tail->label, tail_label)
        );
        int reverse_match = (
            strcmp(e->tail->label, head_label) && 
            strcmp(e->head->label, tail_label)
        );
        if (exact_match == 1 || reverse_match == 1) {
            return i;
        }
    }
    return 0;
}


graph * __loadd_create_edge(graph * g, int hidx, int tidx) {
    
    edge * e = malloc(sizeof(*e));
    e->head = g->vertices[hidx];
    e->tail = g->vertices[tidx];
    
    g->elen ++;
    g->edges = realloc(g->edges, sizeof(edge**) * g->elen);
    g->edges[g->elen - 1] = e;
    
    // vertex * head = g->vertices[hidx];
    // head->elen ++;
    // head->edges = __loadd_add_edge_to_edges(head->edges, head->elen, e);
    
    // vertex * tail = g->vertices[tidx];
    // tail->elen ++;
    // tail->edges = __loadd_add_edge_to_edges(tail->edges, tail->elen, e);
    
    return g;
}


graph * _loadd_check_and_create_edge(graph * g, int hidx, int tidx) {
    int exists = __loadd_check_exists_edge(g, hidx, tidx);
    if(exists == 0) {
        g = __loadd_create_edge(g, hidx, tidx);
    }
    return g;
}


// provide a graph pointer to a graph pointer, g
// and rows of file data from an adjancecy matrix
graph * loadd_adj_list(char ** rows, int * nrows) {
    
    graph * g = malloc(sizeof(graph));
    g->elen = 0;
    g->vlen = 0;
    g->directed = 1;
    g->vertices = NULL;
    g->edges = NULL;
    
    char * label = NULL;
    int llen = 0;  // length of the label
    
    for(int i = 0; i < *nrows; i ++) {
        // declare a clean variable for the row in question
        char * row = rows[i];
        
        // column count
        int clen = 0;
        
        // keep track of the char index
        int cIdx = 0;
        
        // keep track of head/tail index for all the tails to follow
        int hidx = -1;
        int tidx = -1;
        
        while(1) {
            char c = row[cIdx];
            // all vertex labels are assumed to be numeric
            if (isdigit(c) == 0) {
                // null terminate the label we have
                label[llen] = '\0';
                
                if (clen == 0) {
                    g = _loadd_check_and_create_vertex(g, label, llen, &hidx);
                } else {
                    // throw an error if the head index is not set but 
                    // column count is greater than 0
                    if (hidx == -1) {
                        perror("loadd.c: head index not set but column index greater than 0");
                        exit(EXIT_FAILURE);
                    }
                    g = _loadd_check_and_create_vertex(g, label, llen, &tidx);
                    g = _loadd_check_and_create_edge(g, hidx, tidx);
                }
                llen = 0;
                clen ++;
                
                if (c == '\n') {
                    break;
                }
            } else {
                llen ++;
                label = realloc(label, sizeof(char *) * (llen + 1));
                label[llen - 1] = c;
            }
            cIdx ++;
        }
    }
    // clean up local memory allocation for the function
    free(label);
    
    return g;
}
