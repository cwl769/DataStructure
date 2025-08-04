#include "set.h"
#include "string.h"

void ds_set_create(void*p, size_t key_size, ds_set_compare cmp) {
    ds_set *set = (ds_set*)p;
    set->tree = malloc(sizeof(ds_rbtree));
    ds_rbtree_create(set->tree);
    set->key_size = key_size;
    set->size = 0;
    set->cmp = cmp;
}

void ds_set_insert(ds_set*set, void*key) {
    ds_rbtree_node *p = ds_rbtree_getroot(set->tree);
    ds_rbtree_node *fa = &set->tree->vir_root;
    uint8_t wh = 0;

    while (p != NULL) {
        if (set->cmp(key, p->data) < 0) {
            fa = p;
            p = p->son[0];
            wh = 0;
        } else if (set->cmp(key, p->data) == 0) {
            return;
        } else {
            fa = p;
            p = p->son[1];
            wh = 1;
        }
    }

    ++ set->size;
    void *key_copy = malloc(set->key_size);
    memcpy(key_copy, key, set->key_size);
    ds_rbtree_insert(set->tree, fa, wh, key_copy);
}

void ds_set_erase(ds_set*set, void*key) {
    ds_rbtree_node *p = ds_rbtree_getroot(set->tree);

    while (p != NULL) {
        if (set->cmp(key, p->data) < 0) {
            p = p->son[0];
        } else if (set->cmp(key, p->data) == 0) {
            --set->size;
            ds_rbtree_erase(set->tree, p);
            return;
        } else {
            p = p->son[1];
        }
    }
}

uint8_t ds_set_empty(ds_set*set) {
    return (set->size == 0) ? 1 : 0 ;
}

size_t ds_set_size(ds_set*set) {
    return set->size;
}

uint8_t ds_set_find(ds_set*set, void*key) {
    ds_rbtree_node *p = ds_rbtree_getroot(set->tree);

    while (p != NULL) {
        if (set->cmp(key, p->data) < 0) {
            p = p->son[0];
        } else if (set->cmp(key, p->data) == 0) {
            return 1;
        } else {
            p = p->son[1];
        }
    }
    return 0;
}

void* ds_set_upper_bound(ds_set*set, void*key) {
    ds_rbtree_node *p = ds_rbtree_getroot(set->tree);
    void* ans = NULL;

    while (p != NULL) {
        if (set->cmp(key, p->data) < 0) {
            ans = p->data;
            p = p->son[0];
        } else {
            p = p->son[1];
        }
    }

    return ans;
}

void* ds_set_lower_bound(ds_set*set, void*key) {
    ds_rbtree_node *p = ds_rbtree_getroot(set->tree);
    void* ans = NULL;

    while (p != NULL) {
        if (set->cmp(key, p->data) < 0) {
            ans = p->data;
            p = p->son[0];
        } else if(set->cmp(key, p->data) == 0) {
            return p->data;
        } else {
            p = p->son[1];
        }
    }

    return ans;
}