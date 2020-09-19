/*
    B-树
*/

#ifndef __BTREE__H
#define __BTREE__H
#include "../向量/Vec.h"
#include <malloc.h>
#include <queue>
using namespace std;
#define M 11    //阶数=4，元素个数小于等于3

typedef struct Node{
    int n;
    int val[M];
    struct Node* parent;
    struct Node* child[M];    
}BTNode,*BTree;
int up(int a, int b){
    return (a+b-1)/b;
}
void traver(BTree bt){
    if(!bt){
        return;
    }
    int i;
    for(i=0;i<M;i++){
        traver(bt->child[i]);
        cout<<bt->val[i]<<endl;
    }
    traver(bt->child[i]);
}//中序遍历

/*层序遍历*/

BTree Node_create(int e){
    BTree bt=(BTree)malloc(sizeof(BTNode)+1);
    bt->parent=NULL;
    bt->n=1;
    bt->val[0]=e;
    bt->child[0]=bt->child[1]=NULL;
    return bt;
}

BTree Find(BTree bt,int e,BTree& hot){
    while(bt){
        hot=bt;//
        Rank r=Vsearch(bt->val,bt->n,e);
        if(0<=r && e==bt->val[r]) return bt;
        bt=bt->child[r+1];
    }
    return NULL;
}//B树查找方法

void splveOverflow(BTree& hot){
    //hot为溢出节点
    int mi=hot->val[M/2];//待上移元素
    hot->val[M/2]=0;//hot分割出上移元素，清零
    hot->n--;       //hot元素个数--
    if(!hot->parent){
        hot->parent=Node_create(mi);
    }//根节点溢出，创建新根

    BTree right=Node_create(0);//新建右节点
    
    int i,j;
    
    for(i=(M/2)+1,j=0; i<M; i++,j++){
        right->val[j]=hot->val[i];//right复制hot右半部
        hot->val[i]=0;            //hot当做左半部,分割出去的元素清零
        hot->n--;                 //hot元素个数--  
        right->n++;               //right元素个数++
    }//for循环用于
    
    right->n=M%2==0? (M/2)-1:M/2;
    
    for(i=(M/2)+1,j=0; i<M+1; i++,j++){
        right->child[j]=hot->child[i];
        if(right->child[j]!=NULL)
            right->child[j]->parent=right;//换父亲节点
        hot->child[i]=NULL;
    }

    right->parent=hot->parent;//右节点创建节点

    Rank r=Vsearch(hot->parent->val,hot->parent->n,mi);
    if(hot->parent->val[r]!=mi){//父节点不是新创建的根节点
        for(i=hot->parent->n;i>r+1;i--){
            hot->parent->val[i]=hot->parent->val[i-1];
        }
        hot->parent->val[i]=mi;
        hot->parent->n++;
        for(i=hot->parent->n; i>r+2; i--){
            hot->parent->child[i]=hot->parent->child[i-1];
        }
        hot->parent->child[i]=right;
        hot->parent->child[i-1]=hot;
    }else{//父节点是新创建的根节点
        hot->parent->child[0]=hot;
        hot->parent->child[1]=right;
    }

}//上溢分裂hot

void solveUnderflow(BTree& hot){
    while(hot->n==up(M,2)-2){
        if(!hot->parent) return; 
        BTree parent=hot->parent;
        Rank r=0;
        while(parent->child[r]!=hot) r++; 
        if(r>0 &&parent->child[r-1]->n>up(M,2)-1){//有左胖兄弟
            for(int i=0; i<hot->n; i++) hot->val[i+1]=hot->val[i];
            hot->val[0]=parent->val[r-1];//下溢节点借到元素
            hot->n++;
            parent->val[r-1]=parent->child[r-1]->val[parent->child[r-1]->n-1];//父节点失去元素从左儿子得到
            parent->child[r-1]->val[parent->child[r-1]->n-1]=0;//左兄弟最大元素被借出，清零
            parent->child[r-1]->n--;
        }//顺时针旋转
        else if(r<parent->n && parent->child[r+1]->n>up(M,2)-1){//有右边胖兄弟 逆时针旋转
            hot->val[hot->n]=parent->val[r];
            hot->n++;
            parent->val[r]=parent->child[r+1]->val[0];
            for(int i=1; i<parent->child[r+1]->n; i++){
                parent->child[r+1]->val[i-1]=parent->child[r+1]->val[i];
            }
            parent->child[r+1]->val[parent->child[r+1]->n-1]=0;
            parent->child[r+1]->n--;
        }else{

        }//合并
    }
}//下溢处理(旋转or合并)

bool Insert(BTree& bt, int e){
    if(!bt){//空树
        bt=Node_create(e);
    }
    BTree hot=NULL;
    if(Find(bt,e,hot))//元素已存在不必插入
        return false;
    //hot为待插入元素节点
    Rank r= Vsearch(hot->val,hot->n,e);
    int i;
    for(i=hot->n;i>r+1;i--){//插入元素前调整元素数组
        hot->val[i]=hot->val[i-1];
    }
    hot->val[i]=e;//插入元素e
    hot->n++;//插入e后节点包含元素个数加1

    hot->child[i+1]=NULL;//增加元素右边分路    //元素和分路的逻辑排列方式：_-_-_-_ - _-_-_
    while(hot!=NULL && hot->n==M){
        splveOverflow(hot);//上溢需分割处理 n==M
        if(hot==bt){
            bt=hot->parent;
        }//上溢至根，更新节点   
        hot=hot->parent;
    }
    return true;
}//B树插入元素

bool Delete(BTree& bt, int e){
    if(!bt)
        return false;
    BTree hot=NULL;
    if(!Find(bt,e,hot))
        return false;
    Rank r=Vsearch(hot->val,hot->n,e);
    int i;
    if(hot->child[0]){
        BTree child = hot->child[r+1];
        while(child->child[0]){
            child=child->child[0];
        }
        hot->val[r]=child->val[0];
        hot=child;
        r=0;
    }//如果hot非叶子节点,需交换处理.
    for(i=r+1; i<hot->n; i++){
        hot->val[i-1]=hot->val[i];
    }
    hot->val[i-1]=0;
    hot->n--;
    //solveUnderflow(hot);
    return true;
}


#endif
