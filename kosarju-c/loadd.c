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
    int label_int = atoi(label);
    for(int i = 0; i < g->vlen; i++) {
        int v_label_int = atoi(g->vertices[i]->label);
        if (label_int == v_label_int) {
            return i;
        }
    }
    return -1;
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
    v->edges = malloc(sizeof(edge**));
    
    v->discovered = 0;
    v->leader = NULL;
    v->is_leader = 0;
    v->finish_time = -1;
    
    g->vertices[g->vlen - 1] = v;
    
    return g;
}


graph * _loadd_check_and_create_vertex(graph * g, char * label, int llen, int * idx) {
    int exists = __loadd_check_exists_vertex(g, label);
    if(exists == -1) {
        g = __loadd_create_vertex(g, label, llen);
        *idx = g->vlen - 1;
    } else {
        *idx = exists;
    }
    return g;
}


int __loadd_check_edge_by_vertex(vertex * v, int head_label, int tail_label) {
    for(int i = 0; i < v->elen; i ++) {
        edge * e = v->edges[i];
        // directed graph, so only check for exact match
        int cmp_head_label = atoi(e->head->label);
        int cmp_tail_label = atoi(e->tail->label);
        if (head_label == cmp_head_label && tail_label == cmp_tail_label) {
            return i;
        }
    }
    return -1;
}


int __loadd_check_exists_edge(graph * g, int hidx, int tidx) {
    int head_label = atoi(g->vertices[hidx]->label);
    int tail_label = atoi(g->vertices[tidx]->label);
    
    // check the head edges
    vertex * head = g->vertices[hidx];
    int head_check = __loadd_check_edge_by_vertex(head, head_label, tail_label);
    if(head_check != -1) {
        return head_check;
    }
    
    // check the tail edges
    vertex * tail = g->vertices[tidx];
    int tail_check = __loadd_check_edge_by_vertex(tail, head_label, tail_label);
    if (tail_check != -1) {
        return tail_check;
    }
    
    return -1;
}


graph * __loadd_create_edge(graph * g, int hidx, int tidx) {
    
    edge * e = malloc(sizeof(*e));
    e->head = g->vertices[hidx];
    e->tail = g->vertices[tidx];
    
    g->elen ++;
    g->edges = realloc(g->edges, sizeof(edge**) * g->elen);
    g->edges[g->elen - 1] = e;
    
    vertex * head = g->vertices[hidx];
    head->elen ++;
    head->edges = realloc(head->edges, sizeof(edge**) * head->elen);
    head->edges[head->elen - 1] = e;
    
    vertex * tail = g->vertices[tidx];
    tail->elen ++;
    tail->edges = realloc(tail->edges, sizeof(edge**) * tail->elen);
    tail->edges[tail->elen - 1] = e;
    
    return g;
}


graph * _loadd_check_and_create_edge(graph * g, int hidx, int tidx) {
    int exists = __loadd_check_exists_edge(g, hidx, tidx);
    if(exists == -1) {
        g = __loadd_create_edge(g, hidx, tidx);
    }
    return g;
}

int __loadd_cmp_vertex_by_label(const void * a, const void * b) {
    vertex * x = *((vertex **)a);
    vertex * y = *((vertex **)b);
    return (atoi(x->label) - atoi(y->label));
}


graph * _loadd_initialize_orphan_vertices(graph * g) {
    // first, sort the graph's vertices by label
    size_t size = sizeof(g->vertices[0]);
    qsort(g->vertices, g->vlen, size, __loadd_cmp_vertex_by_label);
    
    for(int i = 0; i < g->vlen; i ++) {
        if (i > 0) {
            int first = atoi(g->vertices[i - 1]->label);
            int second = atoi(g->vertices[i]->label);
            int diff = second - first;
            // potential orphan
            if (diff > 1) {
                // use the length of the larger value as a conservative
                // sizing estimate
                int llen = strlen(g->vertices[i]->label);
                char * label = malloc(sizeof(char * ) * llen);
                sprintf(label, "%d", (first + 1));
                int idx = g->vlen;
                g = _loadd_check_and_create_vertex(g, label, llen, &idx);
            }
        }
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
        if (i % 10000 == 0) {
            printf("\nloadd.c: total: %d, processed: %d", *nrows, i);
        }
        
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
    
    // ensure to add any orphaned vertices not included in rows!
    g = _loadd_initialize_orphan_vertices(g);
    
    return g;
}
