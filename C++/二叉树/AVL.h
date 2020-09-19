/*
    平衡二叉搜索树-->AVL树
*/

#ifndef __AVL__H
#define __AVL__H

#include "BST.h"
typedef Bintree AVL;

int Max(int a,int b){
    return a>=b? a:b;
}

int GetHeight(Bintree node){
    if(!node) return 0;
    return Max(GetHeight(node->left),GetHeight(node->right))+1;
}//递归计算节点高度

AVL AdjustLL(AVL A){
    AVL B=A->left;
    A->left=B->right;
    B->right=A;
    A->height=Max(GetHeight(A->left),GetHeight(A->right))+1;
    B->height=Max(GetHeight(B->left),A->height)+1;

    return B;
}//LL调整

AVL AdjustRR(AVL A){
    AVL B=A->right;
    A->right=B->left;
    B->left=A;
    A->height=Max(GetHeight(A->left),GetHeight(A->right))+1;
    B->height=Max(GetHeight(B->left),A->height)+1;

    return B;
}//RR调整

AVL AdjustLR(AVL A){
    A->left=AdjustRR(A->left);
    return AdjustLL(A);
}//LR的理论方法 先RR再LL

AVL AdjustRL(AVL A){
    AVL B=A->right;
    AVL C=B->left;
    A->right=C->left;
    B->left=C->right;
    C->left=A;
    C->right=B;
    A->height=Max(GetHeight(A->left),GetHeight(A->right))+1;
    B->height=Max(GetHeight(B->left),GetHeight(B->right))+1;
    C->height=Max(A->height,B->height);
    return C;
}//RL的普通方法


AVL Insert(AVL avl, int e){
    if(!avl){
        return Node_create(e,RB_BLACK,NULL);
    }
    else if(e<avl->val){//向左递归插入
        avl->left=Insert(avl->left,e);
        if(GetHeight(avl->left)-GetHeight(avl->right)==2){
            if(e<avl->left->val){//LL调整:   调整最早不平衡节点和其左儿子及其左儿子的左儿子
                avl=AdjustLL(avl);
            }
            else{//LR调整:  调整最早不平衡节点和其左儿子及其左儿子的右儿子
                avl=AdjustLR(avl);
            }
        }
    }
    else if(e>avl->val){//向右递归插入
        avl->right=Insert(avl->right,e);
        if(GetHeight(avl->right)-GetHeight(avl->left)==2){
            if(e>avl->right->val){//RR调整:   调整最早不平衡节点和其右儿子及其右儿子的右儿子
                avl=AdjustRR(avl);
            }
            else{//RL调整:   调整最早不平衡节点和其右儿子及其右儿子的左儿子
                avl=AdjustRL(avl);
            }
        }
    }
    avl->height=Max(GetHeight(avl->left),GetHeight(avl->right))+1;
    return avl;
}//AVL树的插入操作


AVL Delete(AVL avl,int e){
    if(!avl)
        return NULL;
    if(e<avl->val){
        avl->left=Delete(avl->left,e);//删除左子树节点等价于右子树增加节点，可用插入的镜像思维来调整平衡
        if(GetHeight(avl->right)-GetHeight(avl->left)==2){
            if(GetHeight(avl->right->right)>GetHeight(avl->right->left))
                avl=AdjustRR(avl);
            else 
                avl=AdjustRL(avl);
        }
    }else if(e>avl->val){
        avl->right=Delete(avl->right,e);//与删除左子树节点相反
        if(GetHeight(avl->left)-GetHeight(avl->right)==2){
            if(GetHeight(avl->left->left)>GetHeight(avl->left->right))
                avl=AdjustLL(avl);
            else 
                avl=AdjustLR(avl);
        }
    }else{
        if(avl->left && avl->right){//待删除节点左右儿子都有
            if(GetHeight(avl->left)>GetHeight(avl->right)){//若左子树比右子树高
                AVL max=Findmax(avl->left);
                avl->val=max->val;
                avl->left=Delete(avl->left,max->val);//将左子树最大节点与待删除节点替换，删除子树中被替换的节点
            }else{//相反的
                AVL min=Findmin(avl->right);
                avl->val=min->val;
                avl->right=Delete(avl->right,min->val);//将左子树最小节点与待删除节点替换，删除子树中被替换节点
            }
        }else{//待删除节点只有一个儿子
            AVL tmp=avl;
            avl=avl->left? avl->left:avl->right;
            free(tmp);
        }         
    }
    return avl;
}

#endif