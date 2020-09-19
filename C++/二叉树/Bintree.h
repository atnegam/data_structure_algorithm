/*
    二叉树
    Bintree
    Bintree是二叉树的基础结构，也是搜索树/查找树(BST，AVLtree，R_Btree)的基础结构。
*/

#ifndef __BINTREE__H
#define __BINTREE__H
#include "../global.h"
#include <stack>
#include <queue>
using namespace std;
#define IsRoot(x) (!x->parents)
#define HasLchild(x) (x->left)
#define HasRchild(x) (x->right)
#define IsBlack(x) (!(x)||(x->color==RB_BLACK))//外部空节点也是黑节点
#define IsRed(x) (!IsBlack(x))
#define IsLChild(x) (!IsRoot(x)&&(x==x->parents->left))
#define Height(x) ((x)?(x)->height:-1)
#define FromParentTo(x) (IsRoot(x))?NULL:(IsLChild(x)?(x)->parents->left:(x)->parents->right)
typedef enum {RB_RED, RB_BLACK} RBColor; //节点颜色
typedef struct Treenode* Bintree;

typedef struct Treenode{
    int val;
    int height;//红黑树节点初始高度为-1，因为默认插入红色节点
    RBColor color;//实现红黑树(RBTree)使用
    Bintree parents;
    Bintree left;
    Bintree right;
}Tnode;//二叉树节点

Bintree Node_create(int e,Bintree p){//color非红黑树节点默认黑色
    Bintree node=(Bintree)malloc(sizeof(Tnode));
    node->val=e;
    node->height=0;
    node->color=RB_RED;//
    node->parents=p;
    node->left=node->right=NULL;
    return node;
}//生成新节点

void pre_trave(Bintree root){
    if(!root) return;
    printf("%d\n", root->val);
    pre_trave(root->left);
    pre_trave(root->right);
}//先序遍历递归版 *先序遍历：先访问父节点再左子树然后右子树

void mid_trave(Bintree root){
    if(!root) return;
    mid_trave(root->left);
    printf("%d: %d : %d\n ", root->val,root->color,root->height);
    mid_trave(root->right);
}//中序遍历递归版 *中序遍历：先访问左子树再父节点然后右子树

void post_trave(Bintree root){
    if(!root) return;
    post_trave(root->left);
    post_trave(root->right);
    printf("%d\n", root->val);
}//后序遍历递归版 *后序遍历：先访问左子树再右子树然后父节点

void pre_trave_1(Bintree root){
    stack<Bintree> s;
    Bintree tmp=root;
    while(tmp||!s.empty()){
        while(tmp){
            printf("%d\n", tmp->val);//先序遍历，第一次经过节点即访问
            s.push(tmp);
            tmp=tmp->left;
        }
        if(!s.empty()){
            tmp=s.top();
            s.pop();
            tmp=tmp->right;
        }
    }
}//先序遍历非递归版

void mid_trave_1(Bintree root){
    if(!root) return;
    stack<Bintree> s;
    Bintree tmp=root;
    while(tmp||!s.empty()){
        while(tmp){ //第一次经过未访问
            s.push(tmp);
            tmp=tmp->left;
        }
        if(!s.empty()){
            tmp=s.top();
            s.pop();
            printf("%d\n", tmp->val);//中序遍历，第二次经过节点才访问
            tmp=tmp->right;
        }
    }
}//中序遍历非递归版

void post_trave_1(Bintree root){
    if(!root) return;
    stack<Bintree> s;
    Bintree tmp=root;
    Bintree pre=NULL;
    Bintree top;
    while(tmp||!s.empty()){
        while(tmp){
            s.push(tmp);
            tmp=tmp->left;
        }
        top=s.top();
        if(!top->right||top->right==pre){//如果该节点无右子树或右子树已访问过，则访问该节点
            printf("%d\n", top->val);
            pre=top;
            s.pop();
        }else{
            tmp=top->right;
        }
    }
}//后序遍历非递归版

void lev_trave(Bintree root){
    queue<Bintree> q;
    Bintree n;
    if(!root) return;
    q.push(root);
    while(!q.empty()){
        n=q.front();
        printf("%d: %d\n", n->val,n->color);
        if(n->left) q.push(n->left);
        if(n->right) q.push(n->right);
        q.pop();
    }
}//层序遍历

int Max(int a,int b){
    return a>=b? a:b;
}

int UpdateHeight(Bintree x){
    return x->height=1+Max(Height(x->left),Height(x->right));
}

void UpdateHeightAbove(Bintree x){
    while(x){
        UpdateHeight(x);
        x=x->parents;
    }
}//更新历代祖先

#endif