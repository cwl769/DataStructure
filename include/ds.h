#ifndef _DS_H_
#define _DS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "stddef.h"
#include "stdlib.h"

#ifdef DS_RBTREE_C

#define DS_RBTREE_C_RED 0
#define DS_RBTREE_C_BLACK 1

typedef struct ds_rbtree_c_node {
    uint8_t color;
    struct ds_rbtree_c_node *father, *son[2];
    void * data;
} ds_rbtree_c_node;

typedef struct ds_rbtree_c {
    ds_rbtree_c_node vir_root;
    void (*modify)(ds_rbtree_c_node*);
} ds_rbtree_c;

extern void ds_rbtree_c_modify_default(ds_rbtree_c_node*);
extern ds_rbtree_c_node* ds_rbtree_c_insert(ds_rbtree_c*, ds_rbtree_c_node*, uint8_t, void*);
extern void ds_rbtree_c_delete(ds_rbtree_c*, ds_rbtree_c_node*);
extern ds_rbtree_c_node* ds_rbtree_c_prev(ds_rbtree_c_node*);
extern ds_rbtree_c_node* ds_rbtree_c_next(ds_rbtree_c_node*);
extern ds_rbtree_c_node* ds_rbtree_c_getroot(ds_rbtree_c*);

#endif

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif