/*
    插入排序
    insertsort
*/
#ifndef __INSERTSORT__H
#define __INSERTSORT__H

void insertsort(int a[], int n){
    for(int i=1; i<n; i++){
        int j;
        int min=a[i];   //min保存每趟待插入元素
        for(j=i-1; min<a[j]&&j>=0; j--){//内层循环定位min应该的位置
            a[j+1]=a[j];
        }
        a[j+1]=min;
    }
}

#endif