/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   group.h
 * Author: jake
 *
 * Created on November 17, 2020, 8:10 PM
 */

#ifndef GROUP_H
#define GROUP_H

#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

#endif /* GROUP_H */


typedef struct Group {
    vertex * leader;
    int len;
} group;


typedef struct GroupArray {
    group ** groups;
    int glen;
} garray;

garray * groups_from_graph(graph * g);
void sort_groups_by_size(garray * groups);