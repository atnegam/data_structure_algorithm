/*
    选择排序 O(n^2)
    selectionsort
*/

#ifndef __SELECTIONSORT__H
#define __SELECTIONSORT__H


#include "swap.h"
void selectionsort(int a[], int n){
    for(int i=0; i<n; i++){
        int min=i;//初始化最小元素秩min为i
        for(int j=i; j<n; j++){//内层循环，每趟找出最小元素的秩min
            min=a[j]<a[min]? j:min;
        }
        swap(&a[min],&a[i]);
    }
}

#endif