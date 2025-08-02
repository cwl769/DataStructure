#include "ds.h"

static ds_rbtree_c * cur_tree;

/**
 * @brief Know node is the left(0) or right(1) son of its father
 * @return which son
 * @retval -1 error occurred
 * @retval 0 left
 * @retval 1 right
 */
static uint8_t which_son(ds_rbtree_c_node * node) {
    return (node->father->son[0] == node) ? 0 : 1 ;
}

static inline uint8_t getcol(ds_rbtree_c_node * node) {
    return (node == NULL) ? DS_RBTREE_C_BLACK : node->color ;
}

/**
 * @brief Make node be the root of the subtree of its original father
 */
static void rotate(ds_rbtree_c_node * node) {
    uint8_t which = which_son(node);
    ds_rbtree_c_node * fa = node->father;
    ds_rbtree_c_node * gfa = fa->father;
    ds_rbtree_c_node * s = node->son[which^1];

    gfa->son[which_son(fa)] = node;
    node->son[which^1] = fa;
    fa->son[which] = s;
    if(s != NULL) s->father = fa;
    fa->father = node;
    node->father = gfa;

    cur_tree->modify(fa);
    cur_tree->modify(node);/*the order of modify should not be changed*/
}

static ds_rbtree_c_node* prev(ds_rbtree_c_node * node) {
    ds_rbtree_c_node *tar = node->son[0];
    while(tar != NULL) {
        if(tar->son[1] == NULL)
            return tar;
        else
            tar = tar->son[1];
    }
    return tar;
}

static ds_rbtree_c_node* next(ds_rbtree_c_node * node) {
    ds_rbtree_c_node *tar = node->son[1];
    while(tar != NULL) {
        if(tar->son[0] == NULL)
            return tar;
        else
            tar = tar->son[0];
    }
    return tar;
}

static void insert_fixup(ds_rbtree_c_node * node) {
    if(node->father == &cur_tree->vir_root) {
        node->color = DS_RBTREE_C_BLACK;
        return;
    }
    while(node->father->color == DS_RBTREE_C_RED) {
        ds_rbtree_c_node * fa = node->father;
        ds_rbtree_c_node * gfa = fa->father;
        ds_rbtree_c_node * unc = gfa->son[which_son(fa)^1];
        if(getcol(unc) == DS_RBTREE_C_RED) {
            fa->color = DS_RBTREE_C_BLACK;
            unc->color = DS_RBTREE_C_BLACK;
            gfa->color = DS_RBTREE_C_RED;
            node = gfa;
            if(node->father == &cur_tree->vir_root) {
                node->color = DS_RBTREE_C_BLACK;
                return;
            }
            continue;
        }
        if(which_son(fa) != which_son(node)) {
            rotate(node);
            node = fa;
            fa = node->father;
        }
        rotate(fa);
        fa->color = DS_RBTREE_C_BLACK;
        gfa->color = DS_RBTREE_C_RED;
        break;
    }
}

static void delete_fixup(ds_rbtree_c_node * node) {
    while(node->color == DS_RBTREE_C_BLACK && node->father != &cur_tree->vir_root) {
        ds_rbtree_c_node *fa = node->father;
        ds_rbtree_c_node *sil = fa->son[which_son(node)^1];
        if(getcol(sil) == DS_RBTREE_C_RED) {
            rotate(sil);
            sil->color = DS_RBTREE_C_BLACK;
            fa->color = DS_RBTREE_C_RED;
            sil = fa->son[which_son(node)^1];
        }
        if(getcol(sil->son[0]) == DS_RBTREE_C_BLACK && getcol(sil->son[1]) == DS_RBTREE_C_BLACK) {
            sil->color = DS_RBTREE_C_RED;
            if(getcol(fa)==DS_RBTREE_C_BLACK) {
                node = fa;
                continue;
            } else {
                fa->color = DS_RBTREE_C_BLACK;
                break;
            }
        }
        if(getcol(sil->son[which_son(sil)]) == DS_RBTREE_C_BLACK && getcol(sil->son[which_son(sil)^1]) == DS_RBTREE_C_RED) {
            rotate(sil->son[which_son(sil)^1]);
            sil->father->color = DS_RBTREE_C_BLACK;
            sil->color = DS_RBTREE_C_RED;
            sil = sil->father;
        }
        sil->color = fa->color;
        fa->color = sil->son[which_son(sil)]->color = DS_RBTREE_C_BLACK;
        rotate(sil);
        break;
    }
}

ds_rbtree_c_node* ds_rbtree_c_insert(ds_rbtree_c * tree, ds_rbtree_c_node * node, uint8_t which, void * data) {
    cur_tree = tree;
    ds_rbtree_c_node * new_node = (ds_rbtree_c_node*)malloc(sizeof(ds_rbtree_c_node));
    new_node->color = DS_RBTREE_C_RED;
    new_node->father = node;
    new_node->son[0] = new_node->son[1] = NULL;
    new_node->data = data;
    node->son[which] = new_node;
    insert_fixup(new_node);
    for(ds_rbtree_c_node*p=new_node->father;p!=&cur_tree->vir_root;p=p->father) {
        cur_tree->modify(p);
    }
    return new_node;
}

void ds_rbtree_c_delete(ds_rbtree_c * tree, ds_rbtree_c_node * node) {
    cur_tree = tree;
    if(node->son[0] != NULL && node->son[1] != NULL) {
        ds_rbtree_c_node *s = prev(node);
        void * tmp = s->data;
        s->data = node->data;
        node->data = tmp;
        node = s;
    }
    if(node->son[0] == NULL && node->son[1] == NULL && node->father != &cur_tree->vir_root && node->color == DS_RBTREE_C_BLACK)
        delete_fixup(node);
    ds_rbtree_c_node * rep = NULL;
    if(node->son[0] != NULL) {
        rep = node->son[0];
    }
    if(node->son[1] != NULL) {
        rep = node->son[1];
    }
    if(rep != NULL) {
        rep->father = node->father;
        rep->color = DS_RBTREE_C_BLACK;
    }
    node->father->son[which_son(node)] = rep;

    for(ds_rbtree_c_node*p=node->father;p!=&cur_tree->vir_root;p=p->father) {
        cur_tree->modify(p);
    }
    free(node);
}

ds_rbtree_c_node* ds_rbtree_c_prev(ds_rbtree_c_node*node) {
    return prev(node);
}

ds_rbtree_c_node* ds_rbtree_c_next(ds_rbtree_c_node*node) {
    return next(node);
}

void ds_rbtree_c_modify_default(ds_rbtree_c_node*) {
    // do nothing
}

ds_rbtree_c_node* ds_rbtree_c_getroot(ds_rbtree_c*tree) {
    return tree->vir_root.son[0];
}