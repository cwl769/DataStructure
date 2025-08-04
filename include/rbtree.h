#ifndef _RBTREE_H_
#define _RBTREE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "stddef.h"
#include "stdlib.h"

#define DS_RBTREE_RED 0
#define DS_RBTREE_BLACK 1

typedef struct ds_rbtree_node {
    uint8_t color;
    struct ds_rbtree_node *father, *son[2];
    void * data;
} ds_rbtree_node;

typedef struct ds_rbtree {
    ds_rbtree_node vir_root;
    void (*modify)(ds_rbtree_node*);
} ds_rbtree;

extern void ds_rbtree_create(void*);
extern void ds_rbtree_modify_default(ds_rbtree_node*);
extern ds_rbtree_node* ds_rbtree_insert(ds_rbtree*, ds_rbtree_node*, uint8_t, void*);
extern void ds_rbtree_erase(ds_rbtree*, ds_rbtree_node*);
extern ds_rbtree_node* ds_rbtree_prev(ds_rbtree_node*);
extern ds_rbtree_node* ds_rbtree_next(ds_rbtree_node*);
extern ds_rbtree_node* ds_rbtree_getroot(ds_rbtree*);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif