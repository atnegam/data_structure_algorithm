/*
    快速排序
    quicksort
*/

#ifndef __QUICKSORT__H
#define __QUICKSORT__H

#include "swap.h"
#include "Insertsort.h"
#define cutoff 2

int mid3(int a[], int left, int right){//中位数法取Pivot
    int mid=(left+right)/2;
    if(a[left]>a[mid])
        swap(&a[left],&a[mid]);
    if(a[left]>a[right])
        swap(&a[left],&a[right]);
    if(a[mid]>a[right])
        swap(&a[mid],&a[right]);    //a[left]<=a[mid]<=a[right]

    swap(&a[mid],&a[right-1]); //返回值放于a[right-1]方便后续操作
    return a[right-1];
}

void _quicksort(int a[], int left, int right){//递归将元素一次就位
    if(cutoff<=right-left){
        int Pivot = mid3(a,left,right);//取Pivot
        int i=left, j=right-1;
        for(; ; ){
            while(a[++i]<Pivot){}
            while(a[--j]>Pivot){}
            if(i<j)
                swap(&a[i], &a[j]);
            else break;
        }
        swap(&a[i], &a[right-1]);
        _quicksort(a,left,i-1);
        _quicksort(a,i+1,right);
    }
    else{
        insertsort(a,right-left+1);//规模小于cutoff时，使用插入排序，因为递归在规模小时不合算
    }
}

void quicksort(int a[], int n){//快排
    _quicksort(a,0,n-1);
}

#endif