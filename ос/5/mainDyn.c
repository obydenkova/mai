#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#include "btree.h"

void help()
{
    printf("\n________________________\n");
	printf("This is runtime linking\n\n");
	printf("Choose an operation:\n");
	printf(">> Press 1 to Add key\n");
	printf(">> Press 2 to Remove key\n");
	printf(">> Press 3 to Find key\n");
	printf(">> Press 4 to Print tree\n");
	printf(">> Press 0 to Exit\n");
    printf("________________________\n");
}

int main(void)
{
    void (*TreeInsert)(BTREE *root, ElemType* newKey);
    BTREE (*TreeFind)(BTREE root, ElemType* key);
    BTREE (*TreeRemove)(BTREE root, ElemType* key);
    void (*TreePrint)(BTREE root);
    void (*TreeDestroy)(BTREE root);
    char *err;

    void *libHandle;
    libHandle = dlopen("libbtree.so", RTLD_LAZY);
    if (!libHandle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(FAILURE);
    }

    TreeInsert = dlsym(libHandle, "TreeInsert");
    TreeRemove = dlsym(libHandle, "TreeRemove");
    TreeFind = dlsym(libHandle, "TreeFind");
    TreePrint = dlsym(libHandle, "TreePrint");
    TreeDestroy = dlsym(libHandle, "TreeDestroy");

    if(err = dlerror()) {
        fprintf(stderr, "%s\n", err);
        exit(FAILURE);
    }

    int act = 0;
    ElemType key [MD5 + 1] = "";
    BTREE tree = NULL;
    help();
    while (scanf("%d", &act) && act) {
        switch(act) {
        case 1:
            printf("Enter key: ");
            scanf("%s", &key);

            while( (strlen(key) != 32)) {
                printf("Error: insert correct MD5\n");
                scanf("%s\n", &key);
            }

            (*TreeInsert)(&tree, key);
            break;
        case 2:
            printf("Enter key: ");
            scanf("%s", &key);

            while( (strlen(key) != 32)) {
                printf("Error: insert correct MD5\n");
                scanf("%s\n", &key);
            }

            if ((*TreeFind)(tree, key)) {
                tree = (*TreeRemove)(tree, key);
            } else {
                printf("This key doesn't exist\n");
            }
            break;
        case 3:
            printf("Enter key: ");

            while( (strlen(key) != 32)) {
                printf("Error: insert correct MD5\n");
                scanf("%s\n", &key);
            }


            scanf("%s", &key);
            if ((*TreeFind)(tree, key)) {
                printf("Key found\n");
            } else {
                printf("Key not found\n");
            }
            break;
        case 4:
            if (tree) {
                printf("\n");
                (*TreePrint)(tree);
                printf("\n");
            } else {
                printf("Tree is empty\n");
            }
            break;
        default:
            printf("Error: incorrect command\n");
            break;
        }
        help();
    }
    (*TreeDestroy)(tree);
    dlclose(libHandle);
    return SUCCESS;
}
