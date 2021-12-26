#ifndef _BTREE_H_
#define _BTREE_H_

#define SUCCESS 0
#define FAILURE 1
#define MD5 32

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <string.h>

typedef char ElemType;

typedef struct btree {
    struct btree *left;
    struct btree *right;
    ElemType key [MD5 + 1];
} *BTREE;

extern void TreeInsert(BTREE *root, ElemType* newKey);
extern BTREE TreeFind(BTREE root, ElemType* key);
extern BTREE TreeRemove(BTREE root, ElemType* key);
extern void TreePrint(BTREE root);
extern void TreeDestroy(BTREE root);
extern bool TreeIsEmpty(BTREE root);
#endif /* _BTREE_H */
