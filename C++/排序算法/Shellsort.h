/*
    希尔排序
    shellsort

*/

#ifndef __SHELLSORT__H
#define __SHELLSORT__H

void shellsort(int a[], int n){
    for(int d=n/2; d>0; d/=2){//d增量 dk=n/(2^k)
        for(int i=d; i<n; i++){//内层insertsort
            int j;
            int min=a[i];
            for(j=i; j>=d&&a[j-d]>min; j-=d){
                a[j]=a[j-d];
            }
            a[j]=min;
        }
    }
}//原始希尔排序

//Hibbard增量序列 dk=2^k-1     
//Sedgewick增量序列{1,5,19,41,109,....}-->9x4^i-9x2^i+1或4^i-3x2^i+1
#endif