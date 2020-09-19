/*
    交换模块
    swap
*/

#ifndef __SWAP__H
#define __SWAP__H
void swap(int* a, int* b){
    int tmp=*a;
    *a=*b;
    *b=tmp;
}

#endif