#include "../../global.h"
#include "../BST.h"
int main(){
    BST root=NULL;
    BST_Insert(root,8);
    BST_Insert(root,10);
    BST_Insert(root,5);
    BST_Insert(root,6);
    BST_Insert(root,3);
    BST_Insert(root,4);
    BST prv=NULL;
    BST_Delete(root,8,prv);
    BST_Delete(root,10,prv);
    pre_trave(root);
}
