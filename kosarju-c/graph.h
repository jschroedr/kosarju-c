/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   graph.h
 * Author: jake
 *
 * Created on November 16, 2020, 7:16 PM
 */

#ifndef GRAPH_H
#define GRAPH_H

#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

#endif /* GRAPH_H */

typedef struct Vertex {
    char * label;
    int elen;
    void ** edges;
    int discovered;
    void * leader;
    int isLeader;
} vertex;


typedef struct Edge {
    vertex * head;
    vertex * tail;
} edge;


typedef struct Graph {
    vertex ** vertices;
    int vlen;
    edge ** edges;
    int elen;
} graph;