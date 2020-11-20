/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdlib.h>
#include "graph.h"


void reverse_edges(edge ** edges, int elen) {
    for(long long i = 0; i < elen; i ++) {
        vertex * head = edges[i]->head;
        edges[i]->head = edges[i]->tail;
        edges[i]->tail = head;
    }
}

void reverse_graph(graph * g) {
    reverse_edges(g->edges, g->elen);
    for (long long i = 0; i < g->vlen; i ++) {
        vertex * v = g->vertices[i];
        reverse_edges((edge**)v->edges, v->elen);
    }
}


void free_vertex(vertex * v) {
    free(v->label);
    free(v->edges);
    free(v);
}


void free_edge(edge * e) {
    free(e);
}


void free_graph(graph * g) {
    
    int vlen = g->vlen - 1;
    for(long long j = vlen; j >= 0; j --) {
        free_vertex(g->vertices[j]);
    }
    free(g->vertices);
    
    int elen = g->elen - 1;
    for(long long i = elen; i >= 0; i --) {
        free_edge(g->edges[i]);
    }
    free(g->edges);
    
    free(g);
}