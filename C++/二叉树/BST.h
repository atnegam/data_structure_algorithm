/*
    二叉搜索树BST以Bintree在基础上实现，
*/

#ifndef __BST__H
#define __BST__H
#include "Bintree.h"
typedef Bintree BST;


Bintree Find(Bintree bst, int e, Bintree& prv){
    while(bst){
        if(e>bst->val){
            prv=bst;//prv记录父节点方便操作
            bst=bst->right;
        }else if(e<bst->val){
            prv=bst;
            bst=bst->left;
        }else
            return bst;
    }
    return NULL;
}//查找节点

Bintree Findmin(Bintree bst){
    if(bst){
        while(bst->left){
            bst=bst->left;
        }
    }
    return bst;
}//查找最小元素

Bintree Findmax(Bintree bst){
    if(bst){
        while(bst->right){
            bst=bst->right;
        }
    }
    return bst;
}//查找最大元素

BST BST_Insert(BST &bst, int e){//返回被插入节点,初第一次插入外，其他情况根节点不变
    if(!bst){
        bst=Node_create(e,NULL);
        return bst; //返回根节点
    }//空树插入根节点直接返回
    BST prv=NULL;
    BST res=Find(bst,e,prv);
    if(res){
        printf("already exist!\n");
        return res;
    }//节点已存在，直接返回

    //节点不存在，开始插入
    BST child=Node_create(e,prv);//创建孩子节点
    e<prv->val?prv->left=child:prv->right=child;//插入节点
    UpdateHeightAbove(child);
    return child;//返回新插入节点
}//BST插入方法

BST BST_Delete(BST &root, int e, BST& prv){//每次删除操作都可能使根发生变化
    BST bst=root;
    BST res=Find(bst,e,prv);
    if(!res) return NULL;
    BST child=NULL;
    if(res->left&&res->right){
        BST min=Findmin(bst->right);//一定存在
        res->val=min->val;
        res=min;
        prv=res->parents;//更新prv
    }
    if(res->left){//只存在左子树
        child=res->left;
        FromParentTo(res)=res->left;
        child->parents=res->parents;
        free(res);
        res=NULL;
    }else if(res->right){//只有右子树
        child=res->right;
        FromParentTo(res)=child;
        child->parents=res->parents;
        free(res);
        res=NULL;
    }
    else{//无子树节点
        free(res);
        FromParentTo(res)=NULL;
        UpdateHeightAbove(prv);
        return NULL;
    }
    UpdateHeightAbove(prv);
    if(!child->parents) root=child;//更新根节点
    return child;
}//BST删除方法







/*BST BST_Delete(BST& bst, int e, BST& prv){//返回被删除节点的替代节点
    //BST prv=NULL;
    BST res=Find(bst,e,prv);
    if(!res){
        return bst;
    }
    if(res->left&&res->right){//待删除节点左右子树都存在
        BST min=Findmin(res->right);
        res->val=min->val;
        BST p;
        BST_Delete(res->right,min->val,p);//第归删除已交换节点
    }else{
        if(res->left){//只有左子树
            res->val=res->left->val;
            free(res->left);
            res->left=NULL;
        }else if(res->right){//只有右子树
            res->val=res->right->val;
            free(res->right);
            res->right=NULL;
        }else{//没有子树
            if(!prv){
                free(bst);
                bst=NULL;
            }
            else if(IsLChild(res)){
                free(prv->left);
                prv->left=NULL;
            }else{
                free(prv->right);
                prv->right=NULL;
            }
            return NULL;//无子树节点被删除后替代它的是NULL
        }
        UpdateHeightAbove(prv);
    }
    return res;//有子树节点被删除后替代他的是子树节点    
}//BST删除操作
*/

/*
BST BST_Insert_Rer(BST bst, int e){
    if(!bst){//若树为空，生成根节点
        bst=Node_create(e,RB_RED,NULL);
    }else{//开始查找插入位置
        if(e<bst->val)
            bst->left=BST_Insert_Rer(bst->left,e);//向左递归插入
        else if(e>bst->val)
            bst->right=BST_Insert_Rer(bst->right,e);//向右递归插入
    }
    return bst;
}//BST插入操作递归版

BST BST_Delete_Rer(BST bst, int e){
    BST tmp;
    if(!bst)
        printf("not found");
    else{
        if(e<bst->val)
            bst->left=BST_Delete_Rer(bst->left, e);//向左递归删除
        else if(e>bst->val)
            bst->right=BST_Delete_Rer(bst->right, e);//向右递归删除
        else{//找到要删除的元素节点
            if(bst->left && bst->right){//该节点有双儿子
                tmp=Findmin(bst->right);
                bst->val=tmp->val;
                bst->right=BST_Delete_Rer(bst->right,bst->val);
            }else{
                tmp=bst;
                if(!bst->left)//该节点无左儿子
                    bst=bst->right;
                else//该节点有左儿子
                    bst=bst->left;
                free(tmp);
            }
        }   
    }
    return bst;
}//BST删除操作递归版
*/
#endif
