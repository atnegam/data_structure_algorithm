/*
    冒泡排序
    bubblesort0：每趟依次比较相邻元素，逆序则交换，走完所有趟（n-1）  O(n^2)
    bubblesort1：每趟依次比较相邻元素，逆序则交换，若整趟无逆序交换则排序完毕
    bubblesort2：
*/
#ifndef __BUBBLESORT__H
#define __BUBBLESORT__H
#include "swap.h"

void bubblesort0(int a[], int n){
    for(int j=0; j<n; j++){//外层循环j个元素已排好序
        for(int i=1; i<n-j; i++){//内层循环排序剩下n-1-j个
            if(a[i-1]>a[i]){
                swap(&a[i-1],&a[i]);
            }
        }
    }
}//版本0

void bubblesort1(int a[], int n){
    bool sorted=true;   //sorted 未排序元素状态，false表示可能有逆对，true表示已有序
    for(int j=0; j<n; j++){//外层循环j个元素已排好序
        for(int i=1; i<n-j; i++){//内层循环排序剩下n-1-j个
            if(a[i-1]>a[i]){
                swap(&a[i-1],&a[i]);
                sorted=false;
            }
        }
        if(sorted) return;
        sorted=true;
    }
}//版本1

#endif