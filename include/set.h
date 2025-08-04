#ifndef _SET_H_
#define _SET_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "rbtree.h"

typedef int8_t (*ds_set_compare)(void*, void*);

typedef struct ds_set {
    ds_rbtree * tree;
    size_t key_size;
    size_t size;
    ds_set_compare cmp;
} ds_set;

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif

extern void ds_set_create(void *, size_t, ds_set_compare);
extern void ds_set_insert(ds_set*, void*);
extern void ds_set_erase(ds_set*, void*);
extern uint8_t ds_set_empty(ds_set*);
extern size_t ds_set_size(ds_set*);
extern uint8_t ds_set_find(ds_set*, void*);
extern void *ds_set_upper_bound(ds_set*, void*);
extern void *ds_set_lower_bound(ds_set*, void*);