/*
    红黑树:高级平衡二叉搜索树
*/

#ifndef __RBTREE__HH
#define __RBTREE__HH

#include "../global.h"
#include "BST.h"

typedef Bintree RBTree;

#define BlackHeightUpdated(x) (\
    (Height((x)->left)==Height((x)->right)) && \
    ((x)->height==(IsRed(x)?Height((x)->left):Height((x)->left)+1))\
)

int RB_UpdateHeight(RBTree node){
    node->height=Max(Height(node->left),Height(node->right));
    return IsBlack(node)?node->height++:node->height;//若是黑节点黑高度+1
}//红黑树节点黑高更新

RBTree Transconnect(RBTree a, RBTree b, RBTree c, \
RBTree t0,RBTree t1, RBTree t2, RBTree t3){
    a->left=t0; if(t0)t0->parents=a;
    a->right=t1; if(t1)t1->parents=a; RB_UpdateHeight(a);
    c->left=t2; if(t2)t2->parents=c;
    c->right=t3; if(t3)t3->parents=c; RB_UpdateHeight(c);
    b->left=a; a->parents=b;
    b->right=c; c->parents=b; RB_UpdateHeight(b);
    return b;
}//3+4转换

RBTree Adjust(RBTree v){
    RBTree p=v->parents; RBTree g=p->parents;
    if(IsLChild(p))
        if(IsLChild(v)){//LL
            p->parents=g->parents;
            return Transconnect(v,p,g,v->left,v->right,p->right,g->right);
        }else{//LR
            v->parents=g->parents;
            return Transconnect(p,v,g,p->left,v->left,v->right,g->right);
        }
    else
        if(!IsLChild(v)){//RR
            p->parents=g->parents;
            return Transconnect(g,p,v,g->left,p->left,v->left,v->right);
        }else{//RL
            v->parents=g->parents;
            return Transconnect(g,v,p,g->left,v->left,v->right,p->right);
        }
}//树调整统一方法


RBTree SolveDoubleRed(RBTree rb,RBTree v){
    while(v){
        if(IsRoot(v)){//节点是根节点，直接染黑
            v->color=RB_BLACK;
            v->height++;
            return v;
        }
        RBTree p=v->parents;
        if(IsBlack(p)) return rb;//如果父节点NULL或黑色则不存在双黑缺陷，直接返回
        RBTree g=p->parents;
        RBTree u=IsLChild(p)?g->right:g->left;
        if (IsBlack(u)){//叔父节点u为黑色
            if(IsLChild(v)==IsLChild(p)) p->color=RB_BLACK;//rb, p同侧
            else v->color=RB_BLACK;//rb, p异侧
            g->color=RB_RED;
            RBTree gg=g->parents;
            RBTree res=Adjust(v);
            if(!gg) return res;//返回新树根
            //IsLChild(g)?gg->right=res:gg->left=res;
            if(gg->left==g) gg->left=res;
            else gg->right=res;
            return rb; 
        }else{//叔父节点u为红色
            p->color=u->color=RB_BLACK;//
            p->height++;u->height++;//p,u染黑后黑高度+1
            if(!IsRoot(g))g->color=RB_RED;//若g不是根节点，则染红
            v=g;
        }
    }
}//双红缺陷修复方法

RBTree SolveDoubleBlack(RBTree rb,RBTree prv,RBTree v){
        RBTree p=v?v->parents:prv;
        if(!p)return rb;
        RBTree s=(v==p->left)?p->right:p->left;//v的兄弟s
        if(IsBlack(s)){//s为黑色
            RBTree t=NULL;
            if(HasLchild(s) && IsRed(s->left)) t=s->left;
            else if(HasRchild(s) && IsRed(s->right)) t=s->right;
            if(t){//黑s有红孩子 BB-1
                RBColor old_color=p->color;
                RBTree b=FromParentTo(p)=Adjust(t);
                b->color=old_color;
                UpdateHeight(b);
                if(!b->parents) return b;
                else return rb;
            }else{//黑s没有红节点
                s->color=RB_RED;
                s->height--;
                if(IsRed(p)){//BB-2R
                    p->color=RB_BLACK;
                    return rb;
                }else{//BB-2-B
                    p->height--;

                }
            }
        }else{//s为红色 BB-3
            s->color=RB_BLACK;
            p->color=RB_RED;
            RBTree t=IsLChild(s)?s->left:s->right;
            prv=p;FromParentTo(p)=Adjust(t);
            return SolveDoubleBlack(rb,p->parents,p);
        }
}//双黑缺陷修复


bool RB_Insert(RBTree &rb, int e){
    RBTree v=BST_Insert(rb,e);//调用BST插入方法,返回成功插入节点v
    v->height=-1;//红节点默认黑高度 -1
    //如有必要,双红缺陷修复
    //传入树根，因为树
    rb=SolveDoubleRed(rb,v);//如果调整之后树根发生变化则返回新树根，否则返回原树根
    return true;
}//RBTree插入方法


bool RB_Delete(RBTree& rb, int e){//每次删除，根节点都可能发生变化
    RBTree prv=NULL,res;
    res=BST_Delete(rb,e,prv);//BST删除操作返回的是被删除节点的替代节点
    if(!res && !prv){//空树或只有根节点的树BST删除操作后res和prv都为空.
        return true;
    }
    if(!prv){//BST删除操作后只剩一个根节点,将节点染黑返回
        res->color=RB_BLACK;
        RB_UpdateHeight(res);
        return true;
    }
    if(BlackHeightUpdated(prv)) return true;//若所有祖先黑高度依然平衡则无需调整(被删除节点为红的情况)
    if(IsRed(res)){//若res是红色则直接染黑(被删除节点为黑，替代节点为红的情况) 
        res->color=RB_BLACK;res->height++;return true;
    }
    //双黑缺陷(被删除节点和替代节点都为黑)
    rb=SolveDoubleBlack(rb,res,prv); 
    return true;
}//RBTree删除方法u


#endif